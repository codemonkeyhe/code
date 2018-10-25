/**
 * Created by monkeyhe on 2016/4/27.
 */
package FeedsUserStat

import java.text.{SimpleDateFormat}
import java.util.Date
import java.util.regex.Pattern

import com.mig.tbf.DBConnectionPool.MySqlConnectionPool
import org.apache.spark.Logging
import org.apache.spark.SparkConf
import org.apache.spark.rdd.RDD
import org.apache.spark.sql.hive.HiveContext
import org.apache.spark.{Logging, SparkContext, SparkConf}
import org.apache.spark.storage.StorageLevel

import scala.collection.mutable.ArrayBuffer

object FeedsUserStat extends Logging {

  /*val jdbc = "jdbc:mysql://10.123.123.123:4018/db_video_center?characterEncoding=utf8"
  val dbuser = "OPTtest"
  val dbpass = ""*/
  val jdbc = "jdbc:mysql://10.123.123.123:3360/db_video_center?characterEncoding=utf8"
  val dbuser = "user"
  val dbpass = "video@dbpass"
  MySqlConnectionPool.initialize(jdbc, dbuser, dbpass)

  def getStrFromTimeStamp(formatStr: String, timeStamp: Int): String = {
    val dateTimeFormat = new SimpleDateFormat(formatStr)
    dateTimeFormat.format(new Date(timeStamp * 1000L))
  }


  def writeToDDBBatch[T](resultRDD: RDD[T], tableName: String, fields: ArrayBuffer[String], refreshType: String,
                         func: (T, String) => collection.mutable.ArrayBuffer[Any], batchSize: Int = 50): Unit = {
    val writeToDB = (dataSet: Iterator[T]) => {
      var dataSet4Insert: ArrayBuffer[ArrayBuffer[Any]] = new ArrayBuffer[ArrayBuffer[Any]]
      while (dataSet.hasNext) {
        //50条一插，防止数据过大
        if (dataSet4Insert.length >= batchSize) {
          logInfo("[TBI] Will batch insert 50 datas-------------------------------------------------------")
          MySqlConnectionPool.insertBatch(tableName, fields, dataSet4Insert, true)
          dataSet4Insert.clear
        }
        val rec = dataSet.next()
        //对应一条数据，注意当中数据的顺序要和fields中列名对应
        val dataRec = func(rec, refreshType)
        dataSet4Insert += dataRec
      }
      if (dataSet4Insert.length > 0) {
        logInfo("[TBI] Will batch insert left " + dataSet4Insert.length + " datas-------------------------------------------------------")
        MySqlConnectionPool.insertBatch(tableName, fields, dataSet4Insert, true)
      }
    }
    resultRDD.context.runJob(resultRDD, writeToDB)
  }

  def addDBData(row: (Short, Int), refreshType: String): collection.mutable.ArrayBuffer[Any] = {
    val values: collection.mutable.ArrayBuffer[Any] = new collection.mutable.ArrayBuffer[Any]
    values += refreshType
    values += row._1
    values += row._2
    values
  }


  def main(args: Array[String]) {
    val conf = new SparkConf().setAppName("FeedsUserStat")
    val sc = new SparkContext(conf)
    val hc = new HiveContext(sc)
    val len = args.length
    logInfo("Init success!args legnth=" + len + " args:" + args.mkString("|"))
    if (len == 0) {
      logError("Error params!task needs timestamp!")
      return
    }
    val startTimeStamp: Int = args(len - 1).toInt
    val dateHourNoDash = sc.broadcast(getStrFromTimeStamp("yyyyMMdd", startTimeStamp))
    logInfo("Hour=" + dateHourNoDash.value)

    val sqlguid = "select guid from feedsstat.feedsuserstatus where hour like '" + dateHourNoDash.value + "__'"
    val guidCount:Long = hc.sql(sqlguid).map(row => {
      val guid: String = row.getAs[String]("guid")
      (guid)
    }).distinct().count()
    logInfo("GuidCount=" + guidCount)

    //val sqlData = "select guid, refreshcount, loadmorecount, totalcount from feedsstat.feedsuserstatus where guid!='' and hour like '20160427__'"
    val sqlData = "select guid, refreshcount, loadmorecount, totalcount from feedsstat.feedsuserstatus where guid!='' and hour like '" + dateHourNoDash.value + "__'"
    logInfo("VisSql=" + sqlData)
    val originData: RDD[(String, (Short, Short, Short))] = hc.sql(sqlData).map(row => {
      val guid: String = row.getAs[String]("guid")
      val refreshCount: Short = row.getAs[Short]("refreshcount")
      val loadMoreCount: Short = row.getAs[Short]("loadmorecount")
      val totalCount: Short = row.getAs[Short]("totalcount")
      (guid, (refreshCount, loadMoreCount, totalCount))
    });
    logInfo("originData Size=" + originData.count())

    val originData1: RDD[(String, (Short, Short, Short))]  = originData.reduceByKey((x,y)=>( if (x._3 > y._3) {(x._1, x._2, x._3)} else {(y._1, y._2, y._3)} ))
      .persist(StorageLevel.MEMORY_AND_DISK).repartition(10)

    logInfo("reduce originData1 Size=" + originData1.count())

    val refreshCount: RDD[(Short, Int)] = originData1.map(row=>{
      (row._2._1, 1)
    }).reduceByKey(_ + _)

    val loadCount:  RDD[(Short, Int)] = originData1.map(row=>{
      (row._2._2, 1)
    }).reduceByKey(_ + _)

    val totalCount:  RDD[(Short, Int)] = originData1.map(row=>{
      (row._2._3, 1)
    }).reduceByKey(_ + _)

    val tableName = "t_feeds_user_stat"
    val fields: ArrayBuffer[String] = ArrayBuffer[String]("refresh_type", "refresh_num", "user_count")
    writeToDDBBatch(refreshCount, tableName, fields, "refresh", addDBData)
    writeToDDBBatch(loadCount, tableName, fields, "loadMore", addDBData)
    writeToDDBBatch(totalCount, tableName, fields, "total", addDBData)
    println("insert finish")
  }
}
