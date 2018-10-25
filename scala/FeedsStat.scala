/**
 * Created by monkeyhe on 2016/4/19.
 */
package FeedsStat


import java.text.{SimpleDateFormat}
import java.util.Date
import java.util.regex.Pattern

import com.mig.tbf.DBConnectionPool.MySqlConnectionPool
import org.apache.spark.rdd.RDD
import org.apache.spark.sql.hive.HiveContext
import org.apache.spark.{Logging, SparkContext, SparkConf}
import org.apache.spark.storage.StorageLevel

import scala.collection.mutable.ArrayBuffer


object FeedsStat extends Logging {

  val test=0
  //val jdbc =  if (test==1)  "jdbc:mysql://10.123.123.123:4018/db_video_center?characterEncoding=utf8" else "jdbc:mysql://10.123.123.123:3360/db_video_center?characterEncoding=utf8"
  val jdbc =  if (test==1)  "jdbc:mysql://test.mdb.mig:15013/db_video_center?characterEncoding=utf8" else "jdbc:mysql://fun.mdb.mig:15011/db_video_center?characterEncoding=utf8"
  val dbuser = if (test==1) "testuser" else "funuser"
  val dbpass = if (test==1)  "testuser@dbpass" else "funuser@dbpass"

  MySqlConnectionPool.initialize(jdbc, dbuser, dbpass)

  def getStrFromTimeStamp(formatStr: String, timeStamp: Int): String = {
    val dateTimeFormat = new SimpleDateFormat(formatStr)
    dateTimeFormat.format(new Date(timeStamp * 1000L))
  }

  def updateBatch(tableName: String, fields: ArrayBuffer[String], dataType: Int, dataSet: ArrayBuffer[ArrayBuffer[Any]] ): Unit = {
    var rows:ArrayBuffer[String] = new ArrayBuffer[String]()
    dataSet.foreach(row=> {
      rows += ("(" + row.mkString(",") + ")")
    })
    var updSql = "";
    if (dataType==1) {
      updSql = "insert into %s (%s) values %s on duplicate key update vis_count=vis_count+VALUES(vis_count), sub_type=VALUES(sub_type)"
        .format(tableName, fields.mkString(","), rows.mkString(","))
    } else if (dataType==2) {
      updSql = "insert into %s (%s) values %s on duplicate key update click_count=click_count+VALUES(click_count)"
        .format(tableName, fields.mkString(","), rows.mkString(","))
    } else if (dataType==3) {
      updSql = "insert into %s (%s) values %s on duplicate key update show_count=show_count+VALUES(show_count)"
        .format(tableName, fields.mkString(","), rows.mkString(","))
    }
    logInfo("updSql=" + updSql)
    MySqlConnectionPool.executeUpdate(updSql)
  }

  def makeVisRowData(row: ((Long, Byte), (Short, Int)) , datetime: String): collection.mutable.ArrayBuffer[Any] = {
    val values: collection.mutable.ArrayBuffer[Any] = new collection.mutable.ArrayBuffer[Any]
    values += row._1._1
    values += row._1._2
    values += row._2._1
    values += row._2._2
    values += "'" + datetime + "'"
    values
  }

  def makeClickOrShowRowData(row: ((Long, Byte), Int) , datetime: String): collection.mutable.ArrayBuffer[Any] = {
    val values: collection.mutable.ArrayBuffer[Any] = new collection.mutable.ArrayBuffer[Any]
    values += row._1._1
    values += row._1._2
    values += row._2
    values
  }


  def updateToDBBatch[T](resultRDD: RDD[T], tableName: String, fields: ArrayBuffer[String], dataType: Int,
                          func: (T, String) => collection.mutable.ArrayBuffer[Any], batchSize: Int = 50): Unit = {
    val writeToDB = (dataSet: Iterator[T]) => {
      var dataSet4Insert: ArrayBuffer[ArrayBuffer[Any]] = new ArrayBuffer[ArrayBuffer[Any]]
      val dateFormat = new SimpleDateFormat("Y-M-d H:m:s")
      val datetime=dateFormat.format(new Date())
      while (dataSet.hasNext) {
        //50条一插，防止数据过大
        if (dataSet4Insert.length >= batchSize) {
          logInfo("[FeedsCTR] Will batch insert 50 datas-------------------------------------------------------")
          updateBatch(tableName, fields, dataType, dataSet4Insert)
          dataSet4Insert.clear
        }
        val rec = dataSet.next()
        //对应一条数据，注意当中数据的顺序要和fields中列名对应
        val dataRec = func(rec, datetime)
        dataSet4Insert += dataRec
      }
      if (dataSet4Insert.length > 0) {
        logInfo("[FeedsCTR] Will batch insert left " + dataSet4Insert.length + " datas-------------------------------------------------------")
        updateBatch(tableName, fields, dataType, dataSet4Insert)
      }
    }
    resultRDD.context.runJob(resultRDD, writeToDB)
  }

  def main(args: Array[String]) {
    val conf = new SparkConf().setAppName("FeedsStatCTR")
    val sc = new SparkContext(conf)
    val hc = new HiveContext(sc)
    val len = args.length
    val tableName = "t_fun_ctr_stat"
    logInfo("Init success!args legnth=" + len + " args:" + args.mkString("|"))
    if (len == 0) {
      logError("Error params!task needs timestamp!")
      return
    }
    val startTimeStamp: Int = args(len - 1).toInt
    val dateHourNoDash = sc.broadcast(getStrFromTimeStamp("yyyyMMddHH", startTimeStamp))
    logInfo("Hour=" + dateHourNoDash.value)
    val sqlVis = "select feedsid, maintype, subtype from feedsstat.feedsstatvis where hour='" +
      dateHourNoDash.value + "' and guid!='' and channel!= ''"
    logInfo("VisSql=" + sqlVis)
    val dataVis: RDD[((Long, Byte), (Short, Int))]= hc.sql(sqlVis).map(row => {
      val feedsId: Long = row.getAs[Long]("feedsid")
      val mainType: Byte = row.getAs[Byte]("maintype")
      val subType: Short = row.getAs[Short]("subtype")
      ((feedsId, mainType), (subType, 1))
    }).reduceByKey((x,y) => (x._1, x._2 + y._2))
    val visfields: ArrayBuffer[String] = ArrayBuffer[String]("feeds_id", "main_type","sub_type", "vis_count", "create_time")
    updateToDBBatch(dataVis, tableName, visfields, 1, makeVisRowData)
    logInfo("Vis data finish!")

    val sqlClick = "select feedsid, maintype from feedsstat.feedsstatclick where hour='" +
      dateHourNoDash.value + "' and guid!='' and channel!= '' and action!='DETAIL_SHOW'"
    logInfo("ClickSql=" + sqlClick)
    val dataClick: RDD[((Long, Byte), Int)] = hc.sql(sqlClick).map(row => {
      val feedsId: Long = row.getAs[Long]("feedsid")
      val mainType: Byte = row.getAs[Byte]("maintype")
      ((feedsId, mainType), 1)
    }).reduceByKey(_ + _)
    val clickfields: ArrayBuffer[String] = ArrayBuffer[String]("feeds_id", "main_type", "click_count")
    updateToDBBatch(dataClick, tableName, clickfields, 2, makeClickOrShowRowData)
    logInfo("Click data finish!")


    val sqlShow = "select feedsid, maintype from feedsstat.feedsstatclick where hour='" +
      dateHourNoDash.value + "' and guid!='' and channel!= '' and action='DETAIL_SHOW'"
    logInfo("ShowSql=" + sqlShow)
    val dataShow: RDD[((Long, Byte), Int)] = hc.sql(sqlShow).map(row => {
      val feedsId: Long = row.getAs[Long]("feedsid")
      val mainType: Byte = row.getAs[Byte]("maintype")
      ((feedsId, mainType), 1)
    }).reduceByKey(_ + _)
    val showfields: ArrayBuffer[String] = ArrayBuffer[String]("feeds_id", "main_type", "show_count")
    updateToDBBatch(dataShow, tableName, showfields, 3, makeClickOrShowRowData)
    logInfo("Show data finish!")
    logInfo("work finish!")
  }

}
