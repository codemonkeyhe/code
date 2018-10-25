#!/usr/bin/python
# -*- coding: utf-8 -*-
# FileName : video_play_stat.py

import os
import time
import datetime
import MySQLdb 
import sys

today = datetime.date.today() 
oneday = datetime.timedelta(days=1)
yestoday = today - oneday
lastday = yestoday - oneday - oneday - oneday - oneday - oneday - oneday 

video = {}

def countVideoPlay(myfile) :
    global video
    while True : 
        line = myfile.readline()
        if len(line) == 0 :
            break
        
        infos = line.split("|")
        
        if len(infos) < 9 : 
            continue
            
        vid = infos[8]
        if vid not in video : 
            vinfo = {}
            vinfo["type"] = infos[7]
            vinfo["times"] = 0 
            video[vid] = vinfo
            
        video[vid]["times"] += 1

filename = "/usr/local/app/taf/remote_app_log/MTT/VideoHtmlServer/MTT.VideoHtmlServer_play_" + yestoday.strftime("%Y%m%d") + ".log"
countVideoPlay(file(filename))

conn = MySQLdb.connect(host="10.206.30.118", user="video", passwd="video@2013", db="db_video_center", port=3360)
cursor = conn.cursor()

#sql = 'delete from t_video_playstat where stat_date<"%s"' % (lastday.strftime("%Y%m%d"))
#cursor.execute(sql)
#conn.commit()

for item in video :  
    sql = "insert into t_video_playstat(video_id, type, stat_date, play_times) values(%s, %s, %s, %d)" % (item, video[item]["type"], yestoday.strftime("%Y%m%d"), video[item]["times"])
    try : 
        ret = cursor.execute(sql)
        conn.commit()
        if ret > 0 : 
            print "insert ", item
    except : 
        print "exc ", sql 
    
videototal = {}

sql = 'select video_id, type, play_times from t_video_playstat where stat_date>="%s"' % (lastday.strftime("%Y%m%d"))
cursor.execute(sql)
rets = cursor.fetchall()
for item in rets : 
    if str(item[0]) not in videototal : 
        info = {}
        info["times"] = 0
        info["type"] = item[1]
        videototal[str(item[0])] = info
        
    videototal[str(item[0])]["times"] += int(item[2])

for item in videototal : 
    sql = "select video_id, type, seven_cnt, total_cnt from t_video_playstat_result where video_id=%s" % (item)
    try : 
        cursor.execute(sql)
        ret = cursor.fetchall()
        op = ""
        if len(ret) == 1 :
            op = "update"
            totalcnt = int(ret[0][3])
            if item in video : 
                totalcnt += video[item]["times"] 
            print int(ret[0][3]), totalcnt, videototal[item]["times"]
            sql = "update t_video_playstat_result set seven_cnt=%d, total_cnt=%d, stat_date=%s where video_id=%s" % (videototal[item]["times"], totalcnt, yestoday.strftime("%Y%m%d"), item)
        else : 
            op = "insert"
            sql = "insert into t_video_playstat_result(video_id, type, seven_cnt, total_cnt, stat_date) values (%s, %s, %d, %d, %s)" % (item, videototal[item]["type"], videototal[item]["times"], videototal[item]["times"], yestoday.strftime("%Y%m%d"))
            
        ret = cursor.execute(sql)
        conn.commit()
        if ret > 0 : 
            print "result ok, ", op, item
        else : 
            print "result fail, ", op, item
    except : 
        print "exc ", sql 

cursor.execute("update t_video_playstat_result a join t_video b on a.video_id=b.video_id set a.type=b.type")
conn.commit()
print "Done"
