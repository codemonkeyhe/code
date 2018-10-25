#!/usr/bin/python
# -*- coding: utf-8 -*-
# Filename : recommend_daily_report.py
# Author: monkeyhe
# Date: 20150112

import os
import sys
import MySQLdb as mdb
import subprocess
import datetime
import time
import logging
import traceback
import warnings
import string
import json

reload(sys)
sys.setdefaultencoding('utf8')

#today format 20150113
ctime = datetime.datetime.now().strftime("%H%M%S")
today = datetime.date.today()
oneday = datetime.timedelta(days=1)
yestoday = today - oneday
today = today.strftime("%Y%m%d")
yestoday = yestoday.strftime("%Y%m%d")
logTag = today + "_" + ctime

#warning and logging config 
warnings.filterwarnings('error', category = mdb.Warning)

#CRITICAL > ERROR > WARNING > INFO > DEBUG > NOTSET
logging.basicConfig(level=logging.DEBUG,
        format='%(asctime)s|[%(levelname)s][line:%(lineno)d] | %(funcName)s | %(message)s',
        datefmt='%H:%M:%S',
        filename= 'recommend_' + logTag + '.log',
        filemode='w')

#日志流输出到屏幕
console = logging.StreamHandler()
console.setLevel(logging.INFO)
formatter = logging.Formatter('[%(levelname)s][line:%(lineno)d] | %(funcName)s | %(message)s')
console.setFormatter(formatter)
logging.getLogger('').addHandler(console)

logName = "MTT.VideoHtmlServer_report_recommend_%s.log" % yestoday
localPath = '/data/home/monkeyhe/log/' 
logServerIpList = ["10.10.10.10", "10.10.10.10"]
remotePath = "app/taf/remote_app_log/MTT/VideoHtmlServer/"

tablePrifix = "t_log_recommend_"
tableName = tablePrifix + today
logging.info("tableName = %s" % tableName)
logging.info("logName = %s" % logName)
#tableName = "t_log_recommend_20150112"
#logName = "MTT.VideoHtmlServer_report_recommend_20150113.log" 

## 日志记录分批插入到DB时每批的数目
batchNum = 250

## 邮件标题设置
mailTitle = "播放器推荐数据日报" + today
#receivers = ['monkeyhe']

## html模板设置
logView = """
<html>
	<head>
		<style type="text/css">
			body {background-color: white}
			p {margin-left: 20px}
            .tab {
                text-align: center;
                overflow:hidden;
                border:1px solid #d3d3d3;
                background:#fefefe;
                margin:10px 20px;
                border-radius:5px;
            }
            .tab th, td {
                padding:10px 28px; 
                text-align:center; 
             }
            .tab th {
                background: #87CEFA;
            }
            .tab td {
                border-top:1px solid #e0e0e0; 
                border-right:1px solid #e0e0e0;
            }
            .tab tr.odd-row td {
                background:#f6f6f6;
            }

            .warning {
                color: red;
            }
            
		</style>	
	</head>
	<body>
        <h2>播放器推荐分平台数据</h2>
        <hr></hr>
        <div >
        <h3>视频推荐-分平台数据</h3>
		<table class="tab">
			<tr>
				<th>平台</th>
				<th>二级分类</th>
				<th>曝光UV</th>
				<th>曝光PV</th>
				<th>点击UV</th>
				<th>点击PV</th>
				<th>点击率</th>
			</tr>
            ${TR_REC}
		</table>
        </div>
        <div>
        <h3>广告推荐-分平台数据</h3>
		<table class="tab">
			<tr>
				<th>平台</th>
				<th>广告ID</th>
				<th>曝光UV</th>
				<th>曝光PV</th>
				<th>点击UV</th>
				<th>点击PV</th>
				<th>点击率</th>
			</tr>
            ${TR_AD}
		</table>
        </div>
	</body>
</html>
"""

trHeadTemplate = string.Template(
"""
<tr>
    <th rowspan=${size}>${platform}</th> 
    <th>${reclassify}</th> 
    <td>${visuv}</td> 
    <td>${vispv}</td> 
    <td>${clickuv}</td> 
    <td>${clickpv}</td> 
    <td>${ratio}</td> 
</tr>""")

trTemplate = string.Template( 
"""
<tr>
    <th>${reclassify}</th> 
    <td>${visuv}</td> 
    <td>${vispv}</td> 
    <td>${clickuv}</td> 
    <td>${clickpv}</td> 
    <td>${ratio}</td> 
</tr>""")

## Global  var
gDataType = ["rec", "ad"]
gPlatform = ["android", "iphone", "wxSDK", "wxTBS"]   
#gReclassify = ["opconf", "zonest", "sdk", "txst", "txr"]
gReclassify = ["zonest", "txst", "txr"]
gActType = ["vis", "click"]

gClassifyToName = {
    "opconf": "运营视频",
    "zonest": "专区保底视频",
    "sdk": "推荐系统视频",
    "txst": "腾讯热门短视频",
    "txr": "腾讯视频推荐"
}

gIdToTitle = {}

conn = None
cursor = None

## send mail
def sendMail(sender, receivers, text, title):
    receivers = ';'.join(receivers)
    title = title.decode('utf8').encode('gbk') 
    text = text.decode('utf8').encode('gbk') 
    open('report.html', 'wR').write(text)
    cmd = """/usr/local/support/bin/send_mail.pl '%s' '%s' --title='%s' --sender='%s' """ % (receivers, 'report.html', title, sender) 
    logging.info("Send Mail: %s" % cmd)
    return os.system(cmd)

## 拉取远程日志
def getRemoteLog(remotePath, localPath, logName):
    if(os.path.isfile(localPath + logName)):
        logging.info("Log file is exist!")
        return 0
    logging.info("Begin rsync log...")
    for ip in logServerIpList:
        cmd =  "/usr/bin/rsync -artzv mqq@%s::%s%s %s%s_%s " % (ip, remotePath, logName, localPath, ip, logName)
        logging.info(cmd)
        os.system(cmd)
        logging.info("Remote log on %s download successfully!" % ip)
 
    # merge file
    logging.info("Merge log file begin...")
    for ip in logServerIpList:
        cmd = 'cat %s%s_%s >> %s%s' % (localPath, ip, logName, localPath, logName)
        logging.info(cmd)
        os.system(cmd)
        logging.info(ip + " log merged successfully!")
    
    # remove temp file
    logging.info("Clean log file cache...")
    for ip in logServerIpList:
        cmd = 'rm ' + localPath + ip + "_" + logName;
        logging.info(cmd)
        os.system(cmd)
        logging.info(ip + "log file delete!")


## 按天建立日志
def createLogTable(conn, cursor, tableName):
    try:
        sql = """CREATE TABLE IF NOT EXISTS %s 
        (
                id            int             NOT NULL AUTO_INCREMENT,
                ip            varchar(32)     NOT NULL DEFAULT '',
                edit_time     datetime        NOT NULL DEFAULT '1900-00-00 08:00:00',
                guid          varchar(64)     NOT NULL DEFAULT '',
                qua           varchar(256)    NOT NULL DEFAULT '',
                package_name  varchar(64)     NOT NULL DEFAULT '',
                reclassify    varchar(64)     NOT NULL DEFAULT '', 
                data_type     varchar(32)     NOT NULL DEFAULT '',
                report_src    varchar(64)     NOT NULL DEFAULT '',
                page_id       varchar(128)    NOT NULL DEFAULT '',  
                pos           varchar(64)     NOT NULL DEFAULT '',
                cont_id       varchar(256)    NOT NULL DEFAULT '',
                cont_name     varchar(256)    NOT NULL DEFAULT '',
                act_type      varchar(32)     NOT NULL DEFAULT '',
                platform      varchar(32)     NOT NULL,
                PRIMARY KEY (id),
                index rec_index(reclassify, platform, guid),
                index ad_index(cont_id, platform, guid)
        ) ENGINE=InnoDB  DEFAULT CHARSET=utf8; 
        """ % tableName
        cursor.execute(sql)
        conn.commit()
        logging.info( "create table %s successfully!" % tableName )
        return 0
    except mdb.Warning as w:
        logging.warn("Warning: %s" % str(w))
        return 0
    except mdb.Error as e:
        logging.error("Create Table Error! \nTableName: %s \nErrCode: %d \nErrMsg: %s" % (tableName, e.args[0], e.args[1]))
        return 1

## 根据QUA和包名来获取平台
def getPlatForm(qua, packageName):
    platform = "error"
    quaHead = ""
    if len(qua) > 3:
        quaHead = qua[0:3]
    if packageName == "com.tencent.mm:tools" :
        if qua == "":
            platform = "wxTBS"
        else: 
            platform = "wxSDK"
    elif packageName == "com.tencent.mttlite" or packageName == "com.tencent.mtt":
        if quaHead == "ADR":
            platform = "android"
        elif quaHead == "IQB":
            platform = "iphone"
        elif quaHead == "APQ":
            platform = "apad"
        else:
            logging.debug("Not find platform!packageName = %s QUA = %s" % (packageName, qua))
    elif packageName == "com.tencent.mobileqq:web":
        if quaHead == "ADR":
            platform = "sq_android"
        elif quaHead == "IQB":
            platform = "sq_iphone"
        elif quaHead == "APQ":
            platform = "sq_apad"
        else:
            logging.debug("Not find sq platform!packageName = %s QUA = %s" % (packageName, qua))
    else:
        logging.error("Invalid packageName: %s" % packageName)
    return platform 


## 解析日志后存入到DB
def transLogToDb(conn, cursor, logName, tableName):
    logHd = open(logName, "r")
    global batchNum
    try:
        sqlPrifix = "insert into %s (ip, edit_time, guid, qua, package_name, reclassify, data_type, report_src, page_id, pos, cont_id, cont_name, act_type, platform) values " % tableName
        sql = sqlPrifix
        i = 0
        while True:
            if i < batchNum:
                line = logHd.readline().strip("\n") #剔除结尾换行符
                if len(line) == 0:      # Zero length indicates EOF
                    if sql == sqlPrifix:
                        break
                    sql = sql.rstrip(',') 
                    logging.debug(sql)
                    cursor.execute(sql)
                    conn.commit() 
                    break
                info = line.split("|") 
                # 正式环境日志修复为13
                if len(info) < 13 : 
                    logging.error("Invalid line data: %s" % line)
                    continue
                #info format 
                #0:ip, 1:edit_time, 2:guid, 3:qua, 4:package_name, 5:reclassify, 6:data_type, 7:report_src, 8:page_id, 9:pos, 10:cont_id, 11:cont_name, 12:act_type
                #分批次插入，每次最多插入batchNum 条记录 
                platform = getPlatForm(info[3], info[4])
                rowData = '("%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s"),'\
                % (info[0], info[1], info[2], info[3], info[4], info[5], info[6], info[7], info[8], info[9], info[10], info[11], info[12], platform) 
                sql += rowData
                i = i+1
            else:
                try:
                    sql = sql.rstrip(',') 
                    cursor.execute(sql)
                    conn.commit() 
                    i = 0 
                    sql = sqlPrifix
                except mdb.Warning as w:
                    logging.warn("Warning: %s" % str(w))
                except mdb.Error as e:
                    logging.error("SQL Error: %s \nSQL: %s" % (str(e), sql)) 
                    # MySQL server has gone away 
                    if int(e.args[0]) == 2006: 
                        conn = mdb.connect(host="10.148.142.121", user="OPTtest", db="db_video_center", port=3330, charset="UTF8")
                        conn.ping(True) 
                        cursor = conn.cursor(mdb.cursors.DictCursor) 
                        cursor.execute("set names utf8;")
                except Exception as ex:
                    logging.critical("Eeception: %s \nSQL: %s" % (str(ex), sql))
                finally:
                    i = 0 
                    sql = sqlPrifix
    except mdb.Warning as w:
        logging.warn("Warning: %s" % str(w))
        return 0
    except mdb.Error as e:
        logging.error("SQL Error: %s\n Sql: %s" % (str(e), sql))
        return 1
    finally:
        logHd.close()
        return 0



#select distinct(guid) from t_log_recommend where  platform = "x5|ip|wxSdk|wxTbs" and data_type="rec" and reclassify = "opconf|zonest|sdk|txst|txr" and act_type="vis|click"
## 计算统计数据
def actionStat(conn, cursor, tableName, data):
    try:
        data["ad"] = {} 
        sql = "select distinct cont_id from %s where data_type = 'ad'" % tableName
        cursor.execute(sql)
        conn.commit() 
        contIds = cursor.fetchall()
        logging.info("Ad contId num = %d" % len(contIds) )

        for platform in gPlatform:
            data["ad"][platform] = {}
            for mContId in contIds:
                contId = mContId["cont_id"]
                if len(contId) > 2:
                    continue
                data["ad"][platform][contId] = {}
                for actType in gActType:
                    key = "ad_" + platform + "_" + contId + "_" + actType
                    uvKey = key + "_uv"
                    sql = "select count(distinct guid) as %s from %s where cont_id = '%s' and  platform = '%s' and data_type='ad' and act_type='%s'" % \
                    (uvKey, tableName, contId, platform, actType)
                    cursor.execute(sql)
                    conn.commit() 
                    ret = cursor.fetchone()
                    logging.info("%s : %s" % (uvKey, ret[uvKey]))
                    data["ad"][platform][contId][actType+"uv"] = ret[uvKey]
                     
                    pvKey = key + "_pv"
                    sql = "select count(guid) as %s from %s where cont_id = '%s' and  platform = '%s' and data_type='ad' and act_type='%s'" % \
                    (pvKey, tableName, contId, platform, actType)
                    cursor.execute(sql)
                    conn.commit() 
                    ret = cursor.fetchone()
                    logging.info("SQL: %s key: %s  value: %s" % (sql, pvKey, ret[pvKey]))
                    data["ad"][platform][contId][actType+"pv"] = ret[pvKey]

        data["rec"] = {}
        for platform in gPlatform:
            data["rec"][platform] = {}
            for reclassify in gReclassify:
                data["rec"][platform][reclassify] = {}
                for actType in gActType:
                    key = "rec_" + platform + "_" + reclassify + "_" + actType
                    uvKey = key + "_uv"
                    sql = "select count(distinct guid) as %s from %s where reclassify = '%s' and  platform = '%s' and data_type='rec' and act_type='%s'" % \
                    (uvKey, tableName, reclassify, platform, actType)
                    cursor.execute(sql)
                    conn.commit() 
                    ret = cursor.fetchone()
                    logging.info("%s : %s" % (uvKey, ret[uvKey]))
                    data["rec"][platform][reclassify][actType+"uv"] = ret[uvKey]
                     
                    pvKey = key + "_pv"
                    sql = "select count(guid) as %s from %s where reclassify = '%s' and platform = '%s' and data_type='rec' and  act_type='%s'" % \
                    (pvKey, tableName, reclassify, platform, actType)
                    cursor.execute(sql)
                    conn.commit() 
                    ret = cursor.fetchone()
                    logging.info("SQL: %s key: %s value: %s" % (sql, pvKey, ret[pvKey]))
                    data["rec"][platform][reclassify][actType+"pv"] = ret[pvKey]

        #ratio compute 
        for type in gDataType:
            if type not in data:
                continue
            for (platform, value) in data[type].items():
                for (reclassify, statData) in value.items():
                    visuv = string.atof(statData["visuv"])
                    clickuv = string.atof(statData["clickuv"])
                    ratio = 0.0
                    if visuv > 1.0:
                        ratio = clickuv / visuv
                    ratio = ratio * 100
                    sratio = "%.2f%%" % ratio 
                    data[type][platform][reclassify]["ratio"] = sratio
        logging.info("STAT_DATA: %s" % str(data))
        dataHd = open("statdata_" + logTag + ".dict", "w") 
        dataHd.write(str(data))
        dataHd.close()
        logging.info("BackUp data to statdata.dict successfully!")
    except mdb.Warning as w: 
        logging.warn("Warning: %s" % str(w))
        return 0
    except mdb.Error as e:
        logging.error("Error: %s\n Sql: %s" % (str(e), sql))
        return 1

## 把数据绑定到Html模板，生成Html视图
def getHtmlView(data):
    global logView
    global trHeadTemplate
    global trTemplate
    recData = data["rec"]
    adData = data["ad"]
    recHtmlData = ""
    adHtmlData = ""
    node = {}
    for (platform, value) in  recData.items():
        size = len(value)
        node["size"] = size
        node["platform"] = platform
        firstLine = True
        for (reclassify, statData) in value.items():
            if reclassify in gClassifyToName:
                node["reclassify"] = gClassifyToName[reclassify]
            else:
                node["reclassify"] = reclassify
            node["visuv"] = statData["visuv"]
            node["vispv"] = statData["vispv"]
            node["clickuv"] = statData["clickuv"]
            node["clickpv"] = statData["clickpv"]
            node["ratio"] = statData["ratio"]
            if firstLine:
                firstLine = False
                trHtml = trHeadTemplate.substitute(node)
            else:
                trHtml = trTemplate.substitute(node )
            recHtmlData += trHtml
    logging.info("recHtml: %s\n" %  recHtmlData)
 
    node = {}
    for (platform, value) in  adData.items():
        size = len(value)
        for (reclassify, statData) in value.items():
            if statData["visuv"] == 0 and statData["vispv"] == 0:
                size = size -1
        node["size"] = size
        node["platform"] = platform
        firstLine = True
        for (reclassify, statData) in value.items():
            if statData["visuv"] == 0 and statData["vispv"] == 0:
                continue
            if reclassify in gIdToTitle:
                node["reclassify"] = gIdToTitle[reclassify]
            else: 
                node["reclassify"] = reclassify
            node["visuv"] = statData["visuv"]
            node["vispv"] = statData["vispv"]
            node["clickuv"] = statData["clickuv"]
            node["clickpv"] = statData["clickpv"]
            node["ratio"] = statData["ratio"]
            if firstLine:
                firstLine = False
                trHtml = trHeadTemplate.substitute(node)
            else:
                trHtml = trTemplate.substitute(node )
            adHtmlData += trHtml
    logging.info("adHtml: %s\n" % adHtmlData)

    dataHd = open("statdata_" + logTag + ".html", "w") 
    dataHd.write(recHtmlData)
    dataHd.write("\n")
    dataHd.write(adHtmlData)
    dataHd.close()
 
    logViewTemplate = string.Template(logView)
    logView = logViewTemplate.substitute({"TR_REC": recHtmlData, "TR_AD": adHtmlData})
    logging.info("logView: %s" % logView)


##############################################################################

if __name__ == '__main__':
    try:
        timebegin = time.time()
        connReal = mdb.connect(host="10.10.10.10", user="root", passwd="root2013", db="db_fool", port=3360, charset="UTF8")
        cursorReal = connReal.cursor(mdb.cursors.DictCursor)
        cursorReal.execute("set names utf8;")
        cursorReal.execute("select id, title from t_video_recom_ad")
        res = cursorReal.fetchall()
        for row in res:
            gIdToTitle[str(row["id"])] = str(row["id"]) + "_" + row["title"]
            logging.info("%d-%s" % (row["id"],  row["title"]))
        logging.info("get title from t_video_recom_ad done!")
        cursorReal.close() 
        connReal.close()

        getRemoteLog(remotePath, localPath, logName)
        time0 = time.time()
        logging.info ("getRemoteLog time cost: %s seconds" % (time0-timebegin))
    

        conn = mdb.connect(host="10.10.10.10", user="fool", db="db_fool", port=3330, charset="UTF8")
        conn.ping(True)
        cursor = conn.cursor(mdb.cursors.DictCursor)
        cursor.execute("set names utf8;")
    
        if createLogTable(conn, cursor, tableName):
            sys.exit(1)
        time1 = time.time()
        logging.info ("Create table time cost: %s seconds" % (time1-time0))
         
        if 0 == transLogToDb(conn, cursor, localPath+logName, tableName):
            logging.info ("Log To Db successfully!")
        else:
            logging.error ("Log To Db FAIL!")
            sys.exit(1)
        time2 = time.time()
        logging.info ("Log to Db time cost: %s seconds" % (time2-time1))
    
    
        res = {}
        actionStat(conn, cursor, tableName, res)
        time3 = time.time()
        logging.info ("Stat time cost: %s seconds" % (time3-time2))
    
        getHtmlView(res)
        
        sendMail('monkeyhe', receivers, logView, mailTitle)
        logging.info("Send mail successfully")
    
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
        if conn:    
            conn.close()
