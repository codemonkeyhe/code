#!/usr/bin/python
# -*- coding: utf-8 -*-
# @file fun_ctr_to_mdb.py
# @brief  趣发现统计表从CDB迁移到MDB 
# @author MonkeyHe[editor]
# @version 1.0
# @date 2016-09-01


import os
import time
import datetime
import MySQLdb as mdb
import sys
import logging
import traceback
import warnings

reload(sys)
sys.setdefaultencoding('utf8')

ctime = datetime.datetime.now().strftime("%H%M%S")
today = datetime.date.today() 
oneday = datetime.timedelta(days=1)
#用于测试 指定具体一天的日志
#yestoday = datetime.date(2015, 4, 13)
logTag = today.strftime("%Y%m%d") + "_" + ctime
logName = "t_fun_ctr_stat_CDB2MDB_%s.log" % today.strftime("%Y%m%d")
localPath = "/data/home/monkeyhe/log/"

#warning and logging config 
warnings.filterwarnings('error', category = mdb.Warning)

#CRITICAL > ERROR > WARNING > INFO > DEBUG > NOTSET
logging.basicConfig(level=logging.DEBUG,
        format='%(asctime)s|[%(levelname)s][line:%(lineno)d] | %(funcName)s | %(message)s',
        datefmt='%H:%M:%S',
        filename= localPath +'FunCtrStat_CDB2MDB_' + logTag + '.log',
        filemode='w')

#日志流输出到屏幕
console = logging.StreamHandler()
console.setLevel(logging.INFO)
formatter = logging.Formatter('[%(levelname)s][line:%(lineno)d] | %(funcName)s | %(message)s')
console.setFormatter(formatter)
logging.getLogger('').addHandler(console)

connCDB = None
cursor = None
connMDB = None
cursorMDB = None

batchNum = 200

##############################################################################
if __name__ == '__main__':
    try:
        #0 拉取CDB数据
        #connCDB = mdb.connect(host="123.123.123.123", user="user", db="db_video_center", port=4018, charset="UTF8")
        connCDB = mdb.connect(host="123.123.123.123", user="user", passwd="video@user", db="db_video_center", port=3333, charset="UTF8")
        connCDB.ping(True)
        cursor = connCDB.cursor(mdb.cursors.DictCursor)
        cursor.execute("set names utf8;")
        timebegin = time.time()
        sql = 'select main_type, sub_type, feeds_id, src, vis_count, click_count, update_time, show_count  from  t_fun_ctr_stat;'
        cursor.execute(sql)
        rets = cursor.fetchall()
        logging.info ("ctr data sql: %s " % (sql))
        dataSize = len(rets)
        logging.info("ctrdata size = %d" % dataSize)
        time0 = time.time()
        logging.info ("-0- get CDB data cost: %s seconds" % (time0-timebegin))

        #1 更新MDB
        #connMDB = mdb.connect(host="test.mdb.mig", user="testuser", passwd="testuser@user", db="db_video_center", port=33333, charset="UTF8")
        connMDB = mdb.connect(host="fun.mdb.mig", user="funuser", passwd="funuser@user", db="db_video_center", port=33333, charset="UTF8")
        connMDB.ping(True)
        cursorMDB = connMDB.cursor(mdb.cursors.DictCursor)
        cursorMDB.execute("set names utf8;")

        sqlHead = 'insert ignore into t_fun_ctr_stat(main_type, sub_type, feeds_id, src, vis_count, click_count, update_time, show_count) values '
        sqlTail = ' on duplicate key update sub_type=VALUES(sub_type), src=VALUES(src), vis_count=VALUES(vis_count), click_count=VALUES(click_count), update_time=VALUES(update_time), show_count=VALUES(show_count)'
        sql = sqlHead
        i = 0
        k = 0
        for item in rets : 
            try : 
                rowData = '(%d, %d, %d, %d, %d, %d, "%s", %d),' % (item["main_type"], item["sub_type"], item["feeds_id"], item["src"], item["vis_count"], item["click_count"], item["update_time"], item["show_count"] ) 
                if i < batchNum : 
                    sql += rowData
                    i = i+1
                    k = k+1
                    #最后一批数据
                    if k >= dataSize : 
                        sql = sql.rstrip(',') 
                        sql += sqlTail
                        logging.info ("Last data sql: %s " % (sql))
                        ret = cursorMDB.execute(sql)
                        connMDB.commit()
                        if ret < 0 : 
                            logging.error("rCode=%s \n insert fail, %s"  % (str(ret), sql))
                else: 
                    i = 0
                    k = k+1
                    sql += rowData
                    sql = sql.rstrip(',') 
                    sql += sqlTail
                    #logging.info ("data sql: %s " % (sql))
                    #分流均匀插入
                    time.sleep(0.001)
                    ret = cursorMDB.execute(sql)
                    connMDB.commit()
                    sql = sqlHead
                    if ret < 0 : 
                        logging.error("rCode=%s \n insert fail, %s"  % (str(ret), sql))
            except mdb.Warning as w:
                logging.warn("Warning: %s" % str(w))
            except mdb.Error as e:
                logging.error("SQL Error: %s \nSQL: %s" % (str(e), sql)) 
            except Exception as ex: 
                logging.critical("Eeception: %s \nSQL: %s" % (str(ex), sql))
        time1 = time.time()
        logging.info ("-1- write MDB time cost: %s seconds" % (time1-time0))
        print "Done"
    except mdb.Warning as w:
        logging.warn("Warning: %s" % str(w))
        sys.exit(1)
    except mdb.Error as e:
        logging.error("Error: %s" % str(e))
        sys.exit(1)
    except Exception as ex:
        logging.critical("Critical Eeception: %s", str(ex))
        exStackInfo = traceback.format_exc()
        print exStackInfo
        sys.exit(1)
    finally:    
        if cursor:
            cursor.close()
        if connCDB:    
            connCDB.close()
        if cursorMDB:
            cursorMDB.close()
        if connMDB:    
            connMDB.close()

