#!/bin/bash
#*************************************************************************************#
#   Author:   monkeyhe
#     Mail:   328679181@qq.com
#     Date:   2014-08-12
# Function:
#             周期地检查某服务是否在运行，如果已经挂掉，发送告警邮件到指定的邮箱中         
#    Notes:   
#             邮件发送依赖send_mail.pl脚本,内容、标题、收信人、发信人需手动配置
#*************************************************************************************#

scriptName=`basename $0`

#-- global config --#

## 邮件发送模块路径 
mailPath="/usr/local/support/bin/send_mail.pl"
## 收信人清单,多个收件人之间用;分割
mailTo="monkeyhe@tencent.com;crystallan@tencent.com"
## 发信人
sender="monkeyhe"
## 邮件标题
title="MIG-服务告警 Warning!"
## 邮件内容
content="<p>This is a test mail!<br />这是一封测试测试！</p>"

function configMail()
{
    local ip=$(getIPAddress)
    body="<span style='color:red' >Warning:</span> Service <strong>$service</strong> at $ip is crash.<br /><hr/><p>$content</p>"
    body=$(utf8ToGbk "$body")
    mTitle=$(utf8ToGbk "$title")
}

function sendWarnMail ()
{
    $($mailPath "$mailTo"  "$body" "--title=$mTitle" "--sender=$sender" >>chkservice.log 2>&1) 	
}

function utf8ToGbk ()
{
    echo $(echo $1 | iconv -f utf8 -t gbk//IGNORE 2>>chkservice.log)
}

function usage ()
{
    echo "Usage: $scriptName -s [Service] -t [Time] -n [TryTimes](Opt.) -m [MailTimes](Opt.)"
    printf "       -s 服务名\n       -t 时间间隔（单位为秒）\n       -n 尝试次数（可选项)  达到这个次数，检查脚本将停止。若缺失,则检查程序永远执行下去\n       -m 发现服务停止后发送告警邮件的次数（可选项）若不提供参数，则每次检查服务停止时都会发送告警邮件 \n"
    echo " Ex.1: 以10秒的间隔查询crond服务是否执行"
    echo "       $scriptName -s crond -t 10"
    echo " Ex.2: 以10秒的间隔查询crond服务是否执行,尝试100次后停止"
    echo "       $scriptName -s crond -t 10 -n 100"
    echo " Ex.3: 以10秒的间隔查询httpd服务是否执行,尝试100次后停止,当httpd服务停止时最多发送3封告警邮件"
    echo "       $scriptName -s httpd -t 10 -n 100 -m 3"
}


function getIPAddress ()
{
    ifconfig -a | grep 'inet addr:' | grep -v '127.0.0.1' | awk '{print $2}' | cut -d ':' -f 2
}

function getServicePIDs ()
{
    ps aux | egrep "[[:space:]|/]$service\$" | egrep -v "grep|$scriptName" | awk '{print $2}'
}

if [ "$#" -lt 1 -o "$#" -gt 8 ]; then
    usage
    exit 1
fi 

while getopts "s:t:n:m:h" arg
do
    case $arg in
        s)
            service=$OPTARG
        ;;
        t)
            interval=$OPTARG
        ;;
        n)
            tryTimes=$OPTARG
        ;;
        m)
            mailTimes=$OPTARG
        ;;
        h)
            usage
            exit 0
        ;;
        ?)
            echo '非法参数!'
            exit 1
        ;;
    esac
done 

#echo "$service  $interval $tryTimes $mailTimes"
if [  -z "$tryTimes" ]; then
    eternal=true
else
    eternal=false
fi

configMail

i=0
mt=0
while $eternal ||  [ $i -lt $tryTimes ]
do
    da=`date +%Y/%m/%d-%H:%M:%S`
    pids=$(getServicePIDs)
    #echo $pids
    if [ -z "$pids" ]; then
       if [ $mt  -lt $mailTimes ]; then 
           sendWarnMail
           let mt++
       fi
       echo "$da : [Warning] Service $service is crash!!!"  | tee -a chkservice.log
    else
       echo "$da : Service $service is running..."  | tee -a chkservice.log
       let mt=0
    fi   
    sleep $interval 
    let i++
done

exit 0
