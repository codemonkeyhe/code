package HelloWorld

import java.text.{SimpleDateFormat}
import java.util.Date
import java.util.regex.Pattern


import com.mig.tbf.DBConnectionPool.MySqlConnectionPool
import org.apache.spark.rdd.RDD
import org.apache.spark.sql.hive.HiveContext
import org.apache.spark.{Logging, SparkContext, SparkConf}
import org.apache.spark.storage.StorageLevel
import scala.collection.mutable.ArrayBuffer

/**
 * Created by monkeyhe on 2016/4/6.
 */
/*

object HelloWorld extends Logging {
  def main (args: Array[String]){
    var conf = new SparkConf().setAppName("MonkeyHelloWorld")
    var spark = new SparkContext(conf)
    println("Hello World!!");
  }
}

*/


object HelloWorld extends Logging {

  val jdbc = "jdbc:mysql://10.206.30.118:4018/db_video_center?characterEncoding=utf8"
  val dbuser = "OPTtest"
  val dbpass = ""
  MySqlConnectionPool.initialize(jdbc, dbuser, dbpass)

  def main(args: Array[String]) {
    var conf = new SparkConf().setAppName("MonkeyMysql")
    var spark = new SparkContext(conf)
    val hiveContext = new HiveContext(spark)
    println("Hello World!!");
    logInfo("done")
    println("done")

  }
}



