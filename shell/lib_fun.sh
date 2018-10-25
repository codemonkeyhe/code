#!/bin/bash
#name:sec_func_lib
#autor:superxiao@sec 
#vre:20100812
#Bash公共函数代码,运营分析，程序维护， 数据管理使用，2周年纪念版
#感谢cctv,感谢党,部分代码copy自rossliu,部分自samli的func-common Bash公共函数库,部分来源于网络

PATH="/usr/local/mysql/bin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:/bin:/sbin:/home/oicq/script/data_center/"

#变量区
#报警程序路径
ALARM_BIN="/home/oicq/alarm_bin/alarm"    
#数据中心主db与mysql执行语句
DATABASE_NAME="data_center"
MYSQL_CONTEXT="mysql -B -N -uroot -pdogoicq"
LOCAL_MYSQL_CONTEXT="${MYSQL_CONTEXT} ${DATABASE_NAME}"    
#简单提取ip地址与机器名称
SVR_IP=`/sbin/ifconfig|grep "inet addr"|grep -v "192.168.0"|grep -v "127.0.0.1"|
sed -n 's/^.*addr:\(1*.*\) [[:space:]]Bcast:.*$/\1/p'|head -1 2>/dev/null`
SVR_NAME=`cat /etc/HOSTNAME`

# 函数区
##################################################################################
#所有的函数,返回0为成功 返回1或以上为失败 $?读取返回状态 错误信息都输出到了stderr
#部分函数需要使用命令替换"$(函数 参数)"来获取实际输出,请采用echo "参数",避免出现echo *的情况
#exec_mysql/exec_mysql_remote执行失败会调用exit,采用命令替换将忽略exit命令,否则会导致脚本退出
##########################################################################################

#######################################告警/log类函数################
#
#
#
#echo颜色列表
#经典案例参考,将make中产生的错误加上颜色输出
#alias make_c='make 2>&1 | sed -e "s/.*warning:.*/\o33[33;1m&\o033[0m/g" 
#              -e "s/.*error:.*/\o033[31;1m&\o033[0m/g" -e "s/.*no makefile found.*/\o033[31;1m&\o033[0m/g"'
COLOR_MAGENTA=$(echo -e "\e[35;49m" )
COLOR_YELLOW=$( echo -e "\e[33;49m" )
COLOR_GREEN=$(  echo -e "\e[32;49m" )
COLOR_RED=$(    echo -e "\e[31;49m" ) 
COLOR_BLUE=$(   echo -e "\e[34;49m" )
COLOR_CYAN=$(   echo -e "\e[36;49m" )
COLOR_RESET=$(  echo -e "\e[0m"     )

# 带颜色的echo输出系列
# @param $1:"$str"
# 红色
function echo_red()
{
    echo "${COLOR_RED}$*${COLOR_RESET}";    
}
# 绿色
function echo_green() 
{ 
    echo "${COLOR_GREEN}$*${COLOR_RESET}";  
}
# 黄色
function echo_yellow()
{
    echo "${COLOR_YELLOW}$*${COLOR_RESET}";   
}
# 蓝色
function echo_blue() 
{ 
    echo "${COLOR_BLUE}$*${COLOR_RESET}";    
}
# 紫色
function echo_magent() 
{ 
    echo "${COLOR_MAGENTA}$*${COLOR_RESET}"; 
}
#青色
function echo_cyan() 
{
    echo "${COLOR_CYAN}$*${COLOR_RESET}";    
}
# 告警头部
function LOG()
{
    echo "[`date +"%F %T"` at ${SVR_IP}] $*"
}
# 告警专用函数,邮件支持多人，短信只支持单人
# @param alarm_msg $USER_NAME|$MOBILE_PHONE $MSG
function alarm_msg()
{
    if [ $# -ne 2 ]; then
        echo_red "Usage: $FUNCNAME USER_NAME|MOBILE_PHONE $MSG" 1>&2
        echo_red "Example: $FUNCNAME rossliu \"Table OnlineLog_20080912_Hash0 doesn't exist!\"" 1>&2
        echo_red "Example: $FUNCNAME 13800138000 \"Table OnlineLog_20080912_Hash0 doesn't exist!\"" 1>&2
        return 1
    fi

    is_number "$1"
    if [ $? -eq 0 ]; then
        local MOBILE_PHONE="$1"
        local MSG="$2"
        LOG "${MSG}"
        ${ALARM_BIN} msg ${MOBILE_PHONE} "${MSG}"
    else
        local USER_NAME="$1"
        local MSG="$2"
        LOG "${MSG}"
        ${ALARM_BIN} mail -F warning -T ${USER_NAME} -S "Warning from ${SVR_IP}" -c "${MSG}" 2>/dev/null
    fi

    return 0
}

#######################判断类函数,结果直接用"$?"获取###########
#
#
# 检查起始日期与结束日期参数  
# @param $1-$2:起始日期 结束日期 例：20100420 20100421
function check_start_end_date()
{
    local USAGE_EXAMPLE="Example: $FUNCNAME `date --date="1 days ago" +%Y%m%d` `date --date= +%Y%m%d`"

    if [ $# -ne 2 ]; then
        echo_red "Usage: $FUNCNAME StartDate EndDate" 1>&2
        return 1
    fi

    local CHECK_DATE=`date --date="$1" +%Y%m%d 2>/dev/null`
    if [ ${CHECK_DATE:-"null"} != $1 ];then
        echo_red "Error first Date: $1" 1>&2
        echo_red ${USAGE_EXAMPLE} 1>&2
        return 1
    fi

    CHECK_DATE=`date --date="$2" +%Y%m%d 2>/dev/null`
    if [ ${CHECK_DATE:-"null"} != $2 ];then
        echo_red "Error Second Date: $2" 1>&2
        echo_red ${USAGE_EXAMPLE} 1>&2
        return 1
    fi  
    return 0
}
#
# 判断是否是数字串,返回0代表是数字串
# @param  $1:字符串  如:3242 或 test
# 注：对+1234这种判断会出错,expr的问题
function is_number()
{
    if [ $# -ne 1 ]; then
        echo_red "Usage: $FUNCNAME NUMBER" 1>&2
        return 1
    fi
    #输入0的时候会expr判断错误,特殊处理
    if [ "$1" = "0" ]; then
        return 0
    fi

    expr $1 + 0 1>/dev/null 2>&1
    return $?
}
#
# 检查日期是否符合格式YYYYMMDD  
# @param $1:日期 例：20100420 
function is_format_date()
{
    if [ $# -ne 1 ]; then
        echo_red "Usage: $FUNCNAME $CUR_DATE" 1>&2
        return 1
    fi

    local CHECK_DATE=`date --date="$1" +%Y%m%d 2>/dev/null`

    if [ ${CHECK_DATE:-"null"} != $1 ];then
        echo_red "Error Date: $1" 1>&2
        echo_red "Example: $FUNCNAME 20081228" 1>&2
        return 1
    fi  
    return 0
}
#
# 检查日期是否符合格式date,注意输入参数必须加上""
# @param $1:日期 例：Wed Aug 11 20:31:35 CST 2010  或者 20100808 08:08:08
function is_format_time()
{
    if [ $# -ne 1 ]; then
        echo_red "Usage: $FUNCNAME $CUR_DATE" 1>&2
        return 1
    fi

    local CHECK_TIME=`date --date="$1" +%Y%m%d 2>/dev/null`

    if [ $? -ne 0 ];then
        echo_red "Error Date: $1" 1>&2
        echo_red "Example: $FUNCNAME Wed Aug 11 20:31:35 CST 2010" 1>&2
        return 1
    fi  
    return 0
}
#
# 判断是否是正确的ip地址 
# @param $IP
function is_an_valid_ip()
{
    local ip=$1

    ## simple checking
    if [[ "$ip" == "0.0.0.0" ]] || [[ "$ip" == "255.255.255.255" ]]; then
        return 1
    fi

    ## not perfect checking ...
    echo "$ip" | grep -qE '^[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}$' 2>/dev/null
    return $?
}


#######################获取类函数,结果需要使用命令替换 x=$(函数)或者x=`函数` ###########
#
#
# 计算两天之间的日期差,参数1-参数2
# @param  $1:日期1 $2:日期2  如:20100309 20100308 
function cal_date_diff()
{
    if [ $# -ne 2 ]; then
        echo_red "Usage: $FUNCNAME DATE1 DATE2" 1>&2
        echo 0
        return 1
    fi

    check_start_end_date $1 $2 1>&2
    if [ $? -ne 0 ]; then
        echo_red "Example: $FUNCNAME 20100309 20100308" 1>&2
        echo 0
        return 2
    fi

    local fristday=$(($(date --date="$1" +%s)/86400))
    local nextday=$(($(date --date="$2" +%s)/86400))
    echo $((${fristday}-${nextday})) 
    return 0
}
#
# 判断是几位数,不包括符号位(带+号会出错,-正常),修改为调用#echo ${#x}将更加快捷
# @param  $1:数字串  如:1234
function digit_num()
{
    if [ $# -ne 1 ]; then
        echo_red "Usage: $FUNCNAME NUMBER" 1>&2
        echo 0
        return 1
    fi
    local TMP_NUM=$1
    is_number ${TMP_NUM}
    if [ $? -ne 0 ]; then
        echo_red "Example: $FUNCNAME 12345678" 1>&2
        echo 0
        return 2
    fi

    local DIGIT_NUM=1
    while [ ${TMP_NUM} -ge 10 -o ${TMP_NUM} -le -10 ]; do
        TMP_NUM=`expr ${TMP_NUM} / 10`
        let DIGIT_NUM=${DIGIT_NUM}+1
    done
    echo ${DIGIT_NUM}
    return 0
}

#
# 取反(取余和取模等可以同样处理)
# @param  $1:数字串  如:1234
function negate_digit()
{
    if [ $# -ne 1 ]; then
        echo_red "Usage: $FUNCNAME NUMBER" 1>&2
        echo 0
        return 1
    fi
    local TMP_NUM=$1
    is_number ${TMP_NUM}
    if [ $? -ne 0 ]; then
        echo_red "Example: $FUNCNAME 12345678" 1>&2
        echo 0
        return 2
    fi
    echo $((-${TMP_NUM}))
    return 0
}

# 查询输入日期的上个月第一天  
# @param $1:[日期](不输入默认为当天)  例如:20100810
function last_month_first_date()
{
    if [ $# -eq 0 ]; then
        local TMP_DATE=`date +%Y%m%d`
    else
        local TMP_DATE=$1
    fi

    is_format_date "${TMP_DATE}"
    if [ $? -ne 0 ]; then
        echo_red "Example: $FUNCNAME [20081228]" 1>&2
        return 1
    fi

    TMP_DATE=`date --date="$1" +%Y%m%d`
    while [ `date --date="${TMP_DATE}" +%e` -ne 1 ]
    do
        TMP_DATE=`date --date="${TMP_DATE} 1 days ago" +%Y%m%d`
    done

    while true
    do
        TMP_DATE=`date --date="${TMP_DATE} 1 days ago" +%Y%m%d`
        if [ `date --date="${TMP_DATE}" +%e` -eq 1 ]
        then
            echo ${TMP_DATE}
            return 0
        fi
    done
}
#
# 查询输入日期的上个月最后一天  
# @param $1:[日期](不输入默认为当天)  例如:20100810
function last_month_last_date()
{
    if [ $# -eq 0 ]; then
        local TMP_DATE=`date +%Y%m%d`
    else
        local TMP_DATE=$1
    fi

    is_format_date ${TMP_DATE}
    if [ $? -ne 0 ]; then
        echo_red "Example: $FUNCNAME [20081228]" 1>&2
        return 1
    fi

    TMP_DATE=`date --date="$1" +%Y%m%d`
    while [ `date --date="${TMP_DATE}" +%e` -ne 1 ]
    do
        TMP_DATE=`date --date="${TMP_DATE} 1 days ago" +%Y%m%d`
    done    
    echo `date --date="${TMP_DATE} 1 days ago" +%Y%m%d`
    return 0
}
#
# 获取本机所有的内网ip,注意有些机型用192.168.0.x挂载存储,需要排除,可能返回多个ip,请用head -1/tail -1获取一个
# @param 无
function get_inside_netip()
{
    local insideip=$(/sbin/ifconfig | grep "inet addr" | grep -v "192.168.0."|
    sed -n 's/^.*addr:\(192.168.*\) [[:space:]]Bcast:.*$/\1/p' 2>/dev/null ;
    /sbin/ifconfig | grep "inet addr" | sed -n 's/^.*addr:\(172.*\) [[:space:]]Bcast:.*$/\1/p' 2>/dev/null;
    /sbin/ifconfig | grep "inet addr" | sed -n 's/^.*addr:\(10.*\) [[:space:]]Bcast:.*$/\1/p' 2>/dev/null)

    if [ "x${insideip}" != "x" ]
    then
        echo ${insideip}
        return 0
    else 
        echo "127.0.0.1"
        return 1
    fi
}
#
# 获取本机所有的外网ip
# @param 无
function get_outside_netip()
{
    local outsideip=$(/sbin/ifconfig | grep "inet addr" | 
    grep -v "inet addr:127.0.0.1" | grep -v "inet addr:172\." | grep -v "inet addr:192\.168\." | grep -v "inet addr:10\."  |
    sed -n 's/^.*addr:\([0-9]*\.[0-9]*\.[0-9]*\.[0-9]*\) [[:space:]]Bcast:.*$/\1/p' 2>/dev/null)

    if [ "x${outsideip}" != "x" ]
    then
        echo ${outsideip}
        return 0
    else
        echo ""
        return 1
    fi
}
#
# 获取本机所有的内外网ip,注意有些机型用192.168.0.x挂载存储,需要排除,可能返回多个ip,请用head -1/tail -1获取一个
# @param 无
function get_all_netip()
{
    local allsideip=$(/sbin/ifconfig | grep "inet addr" | grep -v "inet addr:127.0.0.1" | grep -v "192.168.0." |
    sed -n 's/^.*addr:\([0-9]*\.[0-9]*\.[0-9]*\.[0-9]*\) [[:space:]]Bcast:.*$/\1/p' 2>/dev/null)

    if [ "x${allsideip}" != "x" ]
    then
        echo ${allsideip}
        return 0
    else
        echo ""
        return 1
    fi
}
#
# 获取文件的路径,如果没有，输出当前路径./,如 /data/ftp/ftp_ip_stat/IP_Stat_20080820.txt->/data/ftp/ftp_ip_stat/  1.txt->./ 
# @param $FILE_FULL_NAME
function get_file_path()
{
    if [ $# -ne 1 ]; then
        echo_red "Usage: $FUNCNAME FILE_NAME " 1>&2
        echo_red "Example: $FUNCNAME /data/ftp/ftp_ip_stat/IP_Stat_20080820.txt" 1>&2
        return 1
    fi
    local FULL_PATH="$1"
    local FILE_PATH="${FULL_PATH%/*}"

    if [ "${FILE_PATH}" =  "${FULL_PATH}" ]; then
        FILE_PATH="./"
    fi  
    echo "${FILE_PATH}"
    return 0
}
#
# 获取文件的名称,去掉路径,如 /data/ftp/ftp_ip_stat/IP_Stat_20080820.txt->IP_Stat_20080820.txt
# @param $FILE_FULL_NAME
function get_file_name()
{
    if [ $# -ne 1 ]; then
        echo_red "Usage: $FUNCNAME FILE_NAME " 1>&2
        echo_red "Example: $FUNCNAME /data/ftp/ftp_ip_stat/IP_Stat_20080820.txt" 1>&2
        return 1
    fi
    local FULL_PATH="$1"
    echo "${FULL_PATH##*/}"
    return 0
}
#
# 获取文件后缀类型,/data/ftp/ftp_ip_stat/IP_Stat_20080820.abc.txt->txt
# @param $FILE_FULL_NAME
function get_file_type()
{
    if [ $# -ne 1 ];  then
        echo_red "Usage: $FUNCNAME FILE_NAME " 1>&2
        echo_red "Example: $FUNCNAME /data/ftp/ftp_ip_stat/IP_Stat_20080820.txt" 1>&2
        return 1
    fi
    local FULL_PATH="$1"
    local FILE_TYPE="${FULL_PATH##*.}"

    if [ "x${FILE_TYPE}" =  "x${FULL_PATH}" ];  then
        FILE_TYPE=""
    fi
    echo "${FILE_TYPE}"
    return 0
}
#
# 获取文件前缀,/data/ftp/ftp_ip_stat/IP_Stat_20080820.abc.txt->IP_Stat_20080820.abc
# @param $FILE_FULL_NAME
function get_file_pre()
{
    if [ $# -ne 1 ]; then
        echo_red "Usage: $FUNCNAME FILE_NAME " 1>&2
        echo_red "Example: $FUNCNAME /data/ftp/ftp_ip_stat/IP_Stat_20080820.txt" 1>&2
        return 1
    fi
    local FULL_PATH="$1"
    local FILE_NAME="$(get_file_name "${FULL_PATH}")"
    echo "${FILE_NAME%.*}"
    return 0
}

#######################执行类函数,结果不定########################
#
#
#
# 执行一条mysql语句  执行失败会exit, 注意,熊出没!!!!!!!!!!!!!
# @param    $1:要执行的mysql语句
function exec_mysql()
{
    if [ $# -ne 1 ]; then
        echo_red "Usage: $FUNCNAME SQL" 1>&2
        echo_red "Example: $FUNCNAME \"show tables\"" 1>&2
        return 1
    fi
    local PARAM_SQL_STATEMENT="$1"
	echo "${PARAM_SQL_STATEMENT}" | ${LOCAL_MYSQL_CONTEXT}
    # check result
    if [ $? -ne 0 ]; then
        echo_red "Error: exec_mysql failed" 1>&2
        echo_red "PARAM_SQL_STATEMENT:${PARAM_SQL_STATEMENT}" 1>&2		
        exit 1
    fi
    return 0
}
#
# 执行一条mysql语句出错不退出 
# @param    $1:要执行的mysql语句 $2:mysql进入语句
function exec_mysql_force()
{
    if [ $# -ne 2 ]; then
        echo_red "Usage: $FUNCNAME SQL SQL_CONTEXT" 1>&2
        echo_red "Example: $FUNCNAME \"show tables\" \"mysql -N -B -uroot -pabc xyz\"" 1>&2 
        return 1
    fi
    local PARAM_SQL_STATEMENT="$1"
    local REMOTE_MYSQL_CONTEXT="$2"
    echo "${PARAM_SQL_STATEMENT}" | ${REMOTE_MYSQL_CONTEXT}
    if [ $? -ne 0 ]; then
        echo_red "Error: exec_mysql failed ${REMOTE_MYSQL_CONTEXT} " 1>&2
        echo_red "PARAM_SQL_STATEMENT:${PARAM_SQL_STATEMENT}" 1>&2
        local ALARM_BIN="/usr/local/support/bin/send_all.pl"
        ${ALARM_BIN} "janwang;tylerlong;carbonzhang;jamieliu;lightmanyu;mingqiuliao;shuqigao;ningjing;leevenluo;"  "SQL error in ${SERVER_IP}: ${PARAM_SQL_STATEMENT}" --smsmode=1 --title="SQL运行错误告警"
        return 2
    fi
    return 0
}
#
# 执行一条其余db的mysql语句，或者远程db的mysql语句
# @param    $1:要执行的mysql语句  $2:mysql进入语句
function exec_mysql_remote()
{
    if [ $# -ne 2 ]; then
        echo_red "Usage: $FUNCNAME SQL SQL_CONTEXT" 1>&2
        echo_red "Example: $FUNCNAME \"show tables\" \"mysql -N -B -uroot -pabc xyz\"" 1>&2 
        return 1
    fi
    local PARAM_SQL_STATEMENT="$1"
    local REMOTE_MYSQL_CONTEXT="$2"
	local ALARM_BIN="/usr/local/support/bin/send_all.pl"
    echo "${PARAM_SQL_STATEMENT}" | ${REMOTE_MYSQL_CONTEXT}
    if [ $? -ne 0 ]; then
        echo_red "Error: exec_mysql failed ${REMOTE_MYSQL_CONTEXT} " 1>&2
        echo_red "PARAM_SQL_STATEMENT:${PARAM_SQL_STATEMENT}" 1>&2
	${ALARM_BIN} "janwang;tylerlong;carbonzhang;jamieliu;lightmanyu;mingqiuliao;shuqigao;ningjing;leevenluo;"  "SQL error in ${SERVER_IP}: ${PARAM_SQL_STATEMENT}" --smsmode=1 --title="SQL运行错误告警"
        exit 1
    fi
    return 0
}

#
# 执行一条其余db的mysql语句，或者远程db的mysql语句，出错会退出程序，且发送告警
# @param    $1:要执行的mysql语句  $2:mysql进入语句
function exec_mysql_alarm()
{
    if [ $# -ne 3 ]; then
        echo_red "Usage: $FUNCNAME SQL SQL_CONTEXT ALARM_USERS" 1>&2
        echo_red "Example: $FUNCNAME \"show tables\" \"mysql -N -B -uroot -pabc xyz\"" "\"janwang\"" 1>&2 
        return 1
    fi
    local PARAM_SQL_STATEMENT="$1"
    local REMOTE_MYSQL_CONTEXT="$2"
	local ALARM_USERS="$3"
	local ALARM_BIN="/usr/local/support/bin/send_all.pl"
	local SERVER_IP=`/sbin/ifconfig eth1 |grep "inet addr"|grep -v "192.168.0"|grep -v "127.0.0.1"| sed -n 's/^.*addr:\(1*.*\) [[:space:]]Bcast:.*$/\1/p'|head -1 2>/dev/null`
    echo "${PARAM_SQL_STATEMENT}" | ${REMOTE_MYSQL_CONTEXT}
    if [ $? -ne 0 ]; then
        echo_red "Error: exec_mysql failed ${REMOTE_MYSQL_CONTEXT} " 1>&2
        echo_red "PARAM_SQL_STATEMENT:${PARAM_SQL_STATEMENT}" 1>&2
		${ALARM_BIN} "${ALARM_USERS}"  "SQL error in ${SERVER_IP}: ${PARAM_SQL_STATEMENT}" --smsmode=1 --title="SQL运行错误告警"
        exit 1
    fi
    return 0
}

#
# 调用ftp进行文件上传
# @param $SERVER_IP $SERVER_PORT $USER_NAME $PASSWD $FILE_NAME $LOCAL_DIR $REMOTE_DIR
function ftp_mput_file()
{
    if [ $# -ne 7 ];  then
        echo_red "Usage: $FUNCNAME SERVER_IP SERVER_PORT USER_NAME PASSWD FILE_NAME LOCAL_DIR REMOTE_DIR" 1>&2
        echo_red "Example: $FUNCNAME 172.16.23.108 20000 ftp_u ftp_p OL_20080328_* /data/mysql_data/raw_onlinelog ./" 1>&2
        return 1
    fi

    local FTP_SERVER_IP=$1
    local FTP_SERVER_PORT=$2
    local FTP_USER_NAME=$3
    local FTP_PASSWORD=$4
    local FTP_FILE_NAME=$5
    local FTP_LOCAL_DIR=$6
    local FTP_REMOTE_DIR=$7

    cd ${FTP_LOCAL_DIR}
    (
    echo "user ${FTP_USER_NAME} ${FTP_PASSWORD}"
    echo "binary"
    echo "prompt"    
    echo "cd ${FTP_REMOTE_DIR}"
    echo "mput ${FTP_FILE_NAME}"
    echo "quit"
    ) | ftp -n ${FTP_SERVER_IP} ${FTP_SERVER_PORT}
    return $?
}
#
# 调用ftp进行文件下载
# @param $SERVER_IP $SERVER_PORT $USER_NAME $PASSWD $FILE_NAME $LOCAL_DIR $REMOTE_DIR
function ftp_mget_file()
{
    if [ $# -ne 7 ];  then
        echo_red "Usage: $FUNCNAME SERVER_IP SERVER_PORT USER_NAME PASSWD FILE_NAME LOCAL_DIR REMOTE_DIR" 1>&2
        echo_red "Example: $FUNCNAME 172.16.23.108 20000 ftp_u ftp_p OL_20080328_* /data/mysql_data/raw_onlinelog ./" 1>&2
        return 1
    fi

    local FTP_SERVER_IP=$1
    local FTP_SERVER_PORT=$2
    local FTP_USER_NAME=$3
    local FTP_PASSWORD=$4
    local FTP_FILE_NAME=$5
    local FTP_LOCAL_DIR=$6
    local FTP_REMOTE_DIR=$7

    cd ${FTP_LOCAL_DIR}
    (
    echo "user ${FTP_USER_NAME} ${FTP_PASSWORD}"
    echo "binary"
    echo "prompt"    
    echo "cd ${FTP_REMOTE_DIR}"
    echo "mget ${FTP_FILE_NAME}"
    echo "quit"
    ) | ftp -n ${FTP_SERVER_IP} ${FTP_SERVER_PORT}
    return $?
}
#
# 简化参数版ftp文件上传:默认远程路径为主目录, 端口20000 本地文件为*
# @param $SERVER_IP $USER_NAME $PASSWD $LOCAL_DIR 
function ftp_mput_sample()
{
    if [ $# -ne 4 ];  then
        echo_red "Usage: $FUNCNAME SERVER_IP USER_NAME PASSWD LOCAL_DIR" 1>&2
        echo_red "Example: $FUNCNAME 172.16.23.108 ftp_user ftp_pass /data/mysql_data/raw_onlinelog " 1>&2
        return 1
    fi
    local FTP_SERVER_IP=$1    
    local FTP_USER_NAME=$2
    local FTP_PASSWORD=$3    
    local FTP_LOCAL_DIR=$4    
    cd ${FTP_LOCAL_DIR}
    (
    echo "user ${FTP_USER_NAME} ${FTP_PASSWORD}"
    echo "binary"
    echo "prompt"
    echo "mput *"
    echo "quit"
    ) | ftp -n ${FTP_SERVER_IP} 20000
    return $?
}
#
# 简化参数版ftp文件上传:默认远程路径为主目录, 端口20000 本地文件为*
# @param $SERVER_IP $USER_NAME $PASSWD $LOCAL_DIR 
function ftp_mget_sample()
{
    if [ $# -ne 4 ];  then
        echo_red "Usage: $FUNCNAME SERVER_IP USER_NAME PASSWD LOCAL_DIR" 1>&2
        echo_red "Example: $FUNCNAME 172.16.23.108 ftp_user ftp_pass /data/mysql_data/raw_onlinelog " 1>&2
        return 1
    fi
    local FTP_SERVER_IP=$1    
    local FTP_USER_NAME=$2
    local FTP_PASSWORD=$3    
    local FTP_LOCAL_DIR=$4    
    cd ${FTP_LOCAL_DIR}
    (
    echo "user ${FTP_USER_NAME} ${FTP_PASSWORD}"
    echo "binary"
    echo "prompt"
    echo "mget *"
    echo "quit"
    ) | ftp -n ${FTP_SERVER_IP} 20000
    return $?
}

#
# 通过mysql删除一系列hash表，如:Raw_Audit_Qzone 20100810_Hash*
# @param  $START_DATE $END_DATE $MIN_HASH_ID $MAX_HASH_ID $TABLE_PREFIX $DB_NAME
function drop_table_by_mysql()
{
    if [ $# -ne 6 ];  then
        echo_red "Usage: $FUNCNAME START_DATE END_DATE MIN_HASH_ID MAX_HASH_ID TABLE_PREFIX DB_NAME" 1>&2        
        return 1
    fi
    check_start_end_date $1 $2 1>&2
    if [ $? -ne 0 ]; then        
        echo_red "Example: $FUNCNAME 20080328 20080328 0 9 Daily_Cal_GameBill gamebill" 1>&2
        return 2
    fi
    local LIB_START_DATE=$1
    local LIB_END_DATE=$2
    local MIN_LIB_HASH=$3
    local MAX_LIB_HASH=$4
    local LIB_TABLE_PREFIX=$5
    local LIB_DB_NAME=$6
    local LIB_MERGE_CONTEXT="${MYSQL_CONTEXT} ${LIB_DB_NAME}"
    local LIB_CUR_DATE=${LIB_START_DATE}
    while ((${LIB_CUR_DATE} <= ${LIB_END_DATE}))
    do
        local LIB_HASH_ID=${MIN_LIB_HASH}
        while ((${LIB_HASH_ID} <= ${MAX_LIB_HASH}))
        do
            local LIB_TABLE_NAME="${LIB_TABLE_PREFIX}_${LIB_CUR_DATE}_Hash${LIB_HASH_ID}"
            exec_mysql_remote "drop table if exists ${LIB_TABLE_NAME};" ${LIB_MERGE_CONTEXT}
            let LIB_HASH_ID=${LIB_HASH_ID}+1
        done
        LIB_TABLE_NAME="${LIB_TABLE_PREFIX}_${LIB_CUR_DATE}_Merge"
        exec_mysql_remote "drop table if exists ${LIB_TABLE_NAME};" ${LIB_MERGE_CONTEXT}

        LIB_CUR_DATE=`date --date="${LIB_CUR_DATE} 1 day" +%Y%m%d`
    done

    return 0
}
#
# 通过文件目录暴力删除一系列hash表，如:Raw_Audit_Qzone 20100810_Hash*
# @param  $START_DATE $END_DATE $MIN_HASH_ID $MAX_HASH_ID $TABLE_PREFIX $FILE_DIR
function drop_table_by_file()
{
    if [ $# -ne 6 ];  then
        echo_red "Usage: $FUNCNAME START_DATE END_DATE MIN_HASH_ID MAX_HASH_ID TABLE_PREFIX FILE_DIR" 1>&2
        return 1
    fi
    check_start_end_date $1 $2 1>&2
    if [ $? -ne 0 ]; then        
        echo_red "Example: $FUNCNAME 20080328 20080328 0 9 Daily_Cal_GameBill /data/mysql_data/raw_onlinelog" 1>&2
        return 2
    fi
    local LIB_START_DATE=$1
    local LIB_END_DATE=$2
    local MIN_LIB_HASH=$3
    local MAX_LIB_HASH=$4
    local LIB_FILE_PREFIX=$5
    local LIB_FILE_DIR=$6
    cd  ${LIB_FILE_DIR}   
    local LIB_CUR_DATE=${LIB_START_DATE}
    while ((${LIB_CUR_DATE} <= ${LIB_END_DATE}))
    do
        local LIB_HASH_ID=${MIN_LIB_HASH}
        while ((${LIB_HASH_ID} <= ${MAX_LIB_HASH}))
        do
            local LIB_TABLE_NAME="${LIB_FILE_PREFIX}_${LIB_CUR_DATE}_Hash${LIB_HASH_ID}"
            rm -f "${LIB_TABLE_NAME}*"            
            let LIB_HASH_ID=${LIB_HASH_ID}+1
        done
        LIB_TABLE_NAME="${LIB_FILE_PREFIX}_${LIB_CUR_DATE}_Merge"
        rm -f "${LIB_TABLE_NAME}*"            
        LIB_CUR_DATE=`date --date="${LIB_CUR_DATE} 1 day" +%Y%m%d`
    done

    return 0
}
#
# 通过文件目录暴力删除一系列hash文件(不一定是表)，如:abs_20100808.txt,可以广泛使用的函数
# 注意GENDATE将会替换成为日期进行循环,GENHASH将会替换成为hashid循环,如果是全部文件后缀为*
# @param  $START_DATE $END_DATE $MIN_HASH_ID $MAX_HASH_ID $FILE_PREFIX $FILE_SUFFIX $FILE_DIR
function drop_filelist_bydateid()
{
    if [ $# -ne 7 ];  then
        echo_red "Usage: $FUNCNAME START_DATE END_DATE MIN_HASH_ID MAX_HASH_ID $FILE_PREFIX $FILE_SUFFIX $FILE_DIR" 1>&2
        return 1
    fi
    check_start_end_date $1 $2 1>&2
    if [ $? -ne 0 ]; then        
        echo_red "Example: $FUNCNAME 20080328 20080328 0 9 Daily_GENDATE_GBGENHASH \".frm *\" /data/mysql_data/raw_ol" 1>&2
        return 2
    fi
    local LIB_START_DATE=$1
    local LIB_END_DATE=$2
    local MIN_LIB_HASH=$3
    local MAX_LIB_HASH=$4
    local LIB_FILE_PREFIX="$5"
    local LIB_FILE_SUFFIX="$6"
    local LIB_FILE_DIR=$7
    cd  ${LIB_FILE_DIR}   
    local LIB_CUR_DATE=${LIB_START_DATE}
    while ((${LIB_CUR_DATE} <= ${LIB_END_DATE}))
    do
        local LIB_HASH_ID=${MIN_LIB_HASH}
        while ((${LIB_HASH_ID} <= ${MAX_LIB_HASH}))
        do
            TEMP_FILE_PREFIX=`echo ${LIB_FILE_PREFIX}|sed "s/GENDATE/${LIB_CUR_DATE}/g"|sed "s/GENHASH/${LIB_HASH_ID}/g"`
            for NOW_SUFFIX in "${LIB_FILE_SUFFIX}"
            do
                local LIB_TABLE_NAME="${TEMP_FILE_PREFIX}${NOW_SUFFIX}"
                rm -f "${LIB_TABLE_NAME}*"            
            done
            let LIB_HASH_ID=${LIB_HASH_ID}+1
        done                
        LIB_CUR_DATE=`date --date="${LIB_CUR_DATE} 1 day" +%Y%m%d`
    done

    return 0
}
#
# 检查单个文件是否存在+是否n分钟内没有被修改,返回0:文件存在且没有修改 1:文件存在但是可能被修改中 2:文件不存在  3:参数错误
# @param $FILE_NAME
function check_onefile_stat()
{
    if [ $# -ne 1 ]
    then
        echo_red "Usage: $FUNCNAME FILE_NAME " 1>&2
        echo_red "Example: $FUNCNAME /data/ftp/ftp_ip_stat/IP_Stat_20080820.txt" 1>&2
        return 3
    fi
    local LIB_FILE=$1
    if [ -e ${LIB_FILE} ]; then
        local FILE_NAME=$(get_file_name ${LIB_FILE})
        local FILE_PATH=$(get_file_path ${LIB_FILE})
        cd ${FILE_PATH}
        local TIME_STAT=$(find . -maxdepth 1  -name   "${FILE_NAME}" -mmin +5  |wc -l)
        return $((${TIME_STAT}==1?0:1)) 
    else
        return 2
    fi
}

# 检查文件列表是否存在+是否n分钟内没有被修改,返回0:文件存在且没有修改 1:部分文件存在但是可能被修改中 2:文件不存在  3/4:参数错误
# @param $FILE_NAME $FILE_NUM
# FILE_NAME=0 代表文件数目不定
function check_filelist_stat()
{
    if [ $# -ne 2 ]; then
        echo_red "Usage: $FUNCNAME FILE_NAME  FILE_NUM " 1>&2
        echo_red  "$# $?"
        return 4
    fi
    is_number $2
    if [ $? -ne 0 ]; then
        echo_red "Example: $FUNCNAME /data/ftp/ftp_ip_stat/IP_Stat_*.txt  2" 1>&2
        return 3
    fi
    local LIB_FILE="$1"
    local FILE_NUM="$2"
    local FILE_NAME=$(get_file_name "${LIB_FILE}")
    local FILE_PATH=$(get_file_path "${LIB_FILE}")
    #echo "p:${FILE_PATH} n:${FILE_NAME}"
    cd ${FILE_PATH}
    local TIME_STAT=$(find . -maxdepth 1  -name "${FILE_NAME}" -mmin +5  |wc -l)    
    if ((${TIME_STAT}!=0)); then      
        return $((${TIME_STAT}==${FILE_NUM}||${FILE_NUM}==0?0:1))        
    else
        return 2
    fi
}


# 检查文件是否存在,直到指定时刻
# @param $FILE_NAME $ALARM_TIME(HOUR:MIN)
function wait_file()
{
    if [ $# -ne 3 ]; then
        echo_red "Usage: $FUNCNAME FILE_NAME FILE_NUM ALARM_TIME(HOUR:MIN)" 1>&2
        echo_red "Example: $FUNCNAME /data/ftp/ftp_ip_stat/IP_Stat_20080820*.txt  3 15:30" 1>&2
        return 1
    fi

    local LIB_FILE="$1"
    local LIB_NUM="$2"
    local LIB_ALARM_TIME="$3"
    local LIB_SLEEP_SEC=47
    local LIB_ALARM_HOUR=`echo ${LIB_ALARM_TIME} | awk -F':' '{print $1}' | sed -e "s/^0//"`
    local LIB_ALARM_MIN=`echo ${LIB_ALARM_TIME} | awk -F':' '{print $2}' | sed -e "s/^0//"`
    check_filelist_stat "${LIB_FILE}" "${LIB_NUM}"
    while [ $? -ne 0 ]
    do
        local TMP_LIB_HOUR=`date +%k`
        if [ ${TMP_LIB_HOUR} -gt ${LIB_ALARM_HOUR:-0} ]
        then
            return 1
        elif [ ${TMP_LIB_HOUR} -eq ${LIB_ALARM_HOUR:-0} ]
        then
            TMP_LIB_MIN=`date +%M | sed -e "s/^0//"`
            if [ ${TMP_LIB_MIN:-0} -ge ${LIB_ALARM_MIN:-0} ]
            then
                return 1
            fi
        fi

        sleep ${LIB_SLEEP_SEC}
        check_filelist_stat "${LIB_FILE}" "${LIB_NUM}"
    done

    return 0
}

# sleep直到指定时刻
# @param $ALARM_TIME(YYMMDD HOUR:MIN:SEC)
function wait_until()
{
    if [ $# -ne 1 ]; then
        echo_red "Usage: $FUNCNAME ALARM_TIME(YYMMDD HOUR:MIN:SEC)"
        return 1
    fi
    is_format_time "$1"
    if [ $? -ne 0 ]; then
        echo_red "Example: $FUNCNAME [20081228 17:30:00]" 1>&2
        return 2
    fi
    local LIB_ALARM_SEC=`date --date="${1}" +%s`
    while ((${LIB_ALARM_SEC}>`date +%s`))
    do
        sleep 2
    done
    return 0
}
#
# 获取mysql中所有的heap/memory table的总和，
# 如果恰好有程序在执行，可能统计不了该db, 如果表和db太多了，也会产生杯具
# @param 无
function sum_memory_tablesize()
{
    local DATA_BASES=$(exec_mysql_remote "show databases;" "${MYSQL_CONTEXT}")
    echo_yellow "begin sum  heap/memory table size `date`................."
    local TOTAL_SIZE=0
    local DB_NOW
    for DB_NOW in ${DATA_BASES} ;
    do
        if [ "${DB_NOW}" = "information_schema" -o "${DB_NOW}" = "mysql" ] ; then
            continue
        fi
        local NOW_MYSQL_CONTEXT="${MYSQL_CONTEXT} ${DB_NOW}"
        exec_mysql_remote "show table status;" "${NOW_MYSQL_CONTEXT}"|grep "MEMORY"|awk '{printf("%s %dM\n",$1,$7/(1024*1024))}'
        local TABLE_SIZES=$(exec_mysql_remote "show table status;" "${NOW_MYSQL_CONTEXT}"|
        grep "MEMORY"|awk 'BEGIN{sum=0}{sum=sum+$7}END{print sum}')

        let TOTAL_SIZE=${TOTAL_SIZE}+${TABLE_SIZES:="0"}
    done
    echo_magent "${TOTAL_SIZE}"|awk '{printf("总量: %dM\n",$1/(1024*1024))}'
    echo_yellow "end sum  heap/memory table size `date`................."
}
#
# 统计单位时间内udp丢包数
# @param [secend]
function stat_udplost()
{
    if [ $# -eq 0 ]; then
        TMP_SEC=60
    else
        TMP_SEC=$1
    fi

    is_number ${TMP_SEC}
    if [ $? -ne 0 ]; then
        echo_red "Example: $FUNCNAME [60]" 1>&2
        return 1
    fi
    local udpsent1=`netstat -su | grep 'packets sent' | awk '{printf $1}'`
    local udprecv1=`netstat -su | grep 'packets received' | grep -v total | awk '{printf $1}'`
    local udperror1=`netstat -su | grep 'packet receive errors' | awk '{printf $1}'`
    sleep ${TMP_SEC}
    local udpsent2=`netstat -su | grep 'packets sent' | awk '{printf $1}'`
    local udprecv2=`netstat -su | grep 'packets received' | grep -v total | awk '{printf $1}'`
    local udperror2=`netstat -su |grep 'packet receive errors'|awk '{printf $1}'`
    local udpsent=$[udpsent2-udpsent1]
    local udprecv=$[udprecv2-udprecv1]
    local udpfail=$[udperror2-udperror1]

    echo_cyan "udp packets sent $udpsent packages in $SEC seconds"
    echo_cyan "udp packets received $udprecv packages in $SEC seconds"
    echo_cyan "udp packet receive errors $udpfail packages in $SEC seconds" 
    return 0
}



#######################Bin程序启停/检查类函数#################################
#
#
#
#
# 启动bin文件列表,注意启动列表请加上""
# @param $bin_list $dir
function start_binlist()
{
    if [ $# -ne 2 ];  then
        echo_red "Usage: $FUNCNAME \"binlist\" bin_dir" 1>&2
        return 99
    fi
    local BIN_DIR="$2"
    local BIN_LIST="$1"
    local START_ERROR=0
    cd ${BIN_DIR}
    echo "start begin ***********************************"
    for TARGET in "${BIN_LIST}"
    do
        if [ -e ${TARGET} ]; then
            chmod u+x ${TARGET}
            ${TARGET} &
            echo "start ${TARGET} at `date`"
            sleep 1
        else
            echo_magent "file ${TARGET} not exists at ${BIN_DIR}" 1>&2
            let START_ERROR=${START_ERROR}+1
        fi
    done
    echo "start finsh ***********************************"
    return ${START_ERROR}
}
#
# 用配置文件启动单个bin文件
# @param binfile bin_dir binconf
function start_bin_with_config()
{
    if [ $# -ne 3 ];  then
        echo_red "Usage: $FUNCNAME binfile bin_dir binconf" 1>&2
        return 99
    fi
    local BIN_DIR="$2"
    local TARGET="$1"
    local BIN_CONF="$3"
    cd ${BIN_DIR}
    echo "start begin ***********************************"
    if [ -e ${TARGET} ]; then
        chmod u+x ${TARGET}
        ${TARGET} "${BIN_CONF}" &
        echo "start ${TARGET}  ${BIN_CONF} at `date`"
        sleep 1
        return 0
    else
        echo_magent "file ${TARGET} not exists at ${BIN_DIR}" 1>&2  
        return 1
    fi
    echo "start finsh ***********************************"
}

#
# 检查bin文件有多少个在运行中
# @param binfile 
function get_bin_alive_num()
{
    if [ $# -ne 1 ];  then
        echo_red "Usage: $FUNCNAME binfile" 1>&2
        echo 0
        return 1
    fi
    local TARGET="$1"
    local CHECK_RESULT=`ps -ef|grep "${TARGET}"|grep -v grep | grep -v vi | grep -v tail | wc -l`
    echo "${CHECK_RESULT}"
    return 0
}
#
# 检查bin文件运行中的pid
# @param binfile 
function get_bin_alive_pid()
{
    if [ $# -ne 1 ];  then
        echo_red "Usage: $FUNCNAME binfile" 1>&2
        echo ""
        return 1
    fi
    local TARGET="$1"
    local PID_RESULT=`ps -ef|grep "${TARGET}"|grep -v grep | grep -v vi | grep -v tail | awk '{printf $2" "}'`
    echo "${PID_RESULT}"
    return 0
}

#
# kill 对应bin文件列表,注意bin列表请加上"",采取先kill然后检查再kill -9的策略
# @param $bin_list
function kill_alive_binlist()
{
    if [ $# -ne 1 ];  then
        echo_red "Usage: $FUNCNAME \"binlist\"" 1>&2
        return 99
    fi
    local BIN_LIST="$1"
    local KILL_ERROR=0
    echo "kill begin ***********************************"
    for TARGET in "${BIN_LIST}"
    do
        local FISRT_NUM=$(get_bin_alive_num "${TARGET}")
        if [ ${FISRT_NUM} -eq 0 ]; then
            echo_magent "kill ${TARGET} no process at `date`"
            let KILL_ERROR=${KILL_ERROR}+1
        else
            local FISRT_PID=$(get_bin_alive_pid "${TARGET}")
            kill ${FISRT_PID}
            sleep 1
            echo_yellow "kill ${TARGET} num:${FISRT_NUM}  pid:${FISRT_PID} at `date`"
            local SECOND_NUM=$(get_bin_alive_num "${TARGET}")
            if [ ${SECOND_NUM} -ne 0 ]; then
                local SECOND_PID=$(get_bin_alive_pid "${TARGET}")
                kill -9 ${SECOND_PID}
                sleep 2
                echo_cyan "kill -9 ${TARGET} num:${SECOND_NUM} pid:${SECOND_PID} at `date`"
            fi
            #检查是否还有小强存在
            local LAST_NUM=$(get_bin_alive_num "${TARGET}")
            if [ ${LAST_NUM} -ne 0 ]; then
                local LAST_PID=$(get_bin_alive_pid "${TARGET}")
                echo_green "kill -9 ${TARGET} failed  num:${LAST_NUM} pid:${LAST_PID} at `date`"
            fi
        fi
        sleep 1
    done
    echo "start finsh ***********************************"
    return ${START_ERROR}
}
#
# kill 启动时间超出n分钟的xx进程
# @param $bin_name $time_out
function kill_timeout_binlist()
{
    if [ $# -ne 2 ];  then
        echo_red "Usage: $FUNCNAME \"binlist\" \"time\" " 1>&2
        return 2
    fi
    local TARGET="$1"
    local TIME_OUT="$2"
    local H_DAY=`date +%H`
    local M_HOUR=`date +%M`
    local PID_RESULT=$(ps -ef|grep "${TARGET}"|grep -v grep | grep -v vi | grep -v tail |
    awk '{NUM=split($5,array,":");  if (match($5,":")==0 || 
    (NUM==2 && ((array[1]+0)*60+array[2]+'${TIME_OUT}')<(('${H_DAY}'+0)*60+'${M_HOUR}'))) print $0}'|awk '{printf $2" "}')

    if [ "xx${PID_RESULT}" == "xx" ]; then
        return 0
    else
        echo "kill ${TARGET} pid ${PID_RESULT} at `date`"
        kill ${PID_RESULT}
        return 1
    fi
}
#
# 没啥说的,启动mysql
# @param 无
function start_mysql()
{
    /usr/local/mysql/bin/safe_mysqld --user=mysql &
}
#
# 启动vsftp
# @param 无
function start_vsftp()
{
    /usr/local/sbin/vsftpd &
}
#
# 清空当前用户ipc中未使用的部分
# @param [用户]
function clearIPC()
{
    if [ $# -lt 1 ]
    then
        USER=`whoami`
    else    
        USER=$1
    fi
    local TEMP_FILE="/tmp/tmp_clear_ipc.out"
    echo_yellow "Now Start to Clear $USER's Share Memory"
    ipcs | awk '{if($6==0) printf "%s %s %s\n",$2, $3, $6}' | grep $USER| awk '{print $1}' > ${TEMP_FILE}
    local NUMS=`cat ${TEMP_FILE} | wc -l`
    echo_magent "${NUMS} Share Memroy will be clear!"
    while read LINE
    do
        if [ "x${LINE}" = "x" ]
        then
            exit 0  # 遇到空串
        fi
        ipcrm -m ${LINE}
        echo -n '.'
    done < ${TEMP_FILE}
    rm -f ${TEMP_FILE}
    echo_yellow "Share Memroy clear Done!"
}

#######################DB表拆分合并类函数#################################
#
#
#
#
# 为分散的hash表建立Merge表,可以广泛使用的函数
# @param start_date end_date HashID DBName.mergeTableName DBName.TableTemplate
function mysql_merge_table()
{
    if (($# != 5));then
        echo_red "Usage: $0 start_date end_date HashID DBName.mergeTableName DBName.TableTemplate"
        echo_red "    If HashID=-1, then merge 0 to 9; "
        echo_red "    If HashID=-2, then merge 0 to 99; "
        echo_red "    If HashID=-3, then merge 0 to 999; "
        echo_red "    If HashID> 0, then merge 0 to hashID; "
        return 1
    fi
    check_start_end_date $1 $2 1>&2
    if [ $? -ne 0 ]; then        
        echo_red "Example: $0 20100412 20100416 -2 raw_qzone_pack.Daily_Old_Qzone_Txt_Blog_GENDATE_Merge \
        raw_qzone_pack.Daily_Old_Qzone_Txt_Blog_GENDATE_HashGENHASH" 1>&2
        return 2
    fi
    local START_DATE=$1
    local END_DATE=$2
    #开始执行循环程序
    local CUR_DATE=${START_DATE}
    while ((${CUR_DATE} <= ${END_DATE}))
    do
        local START_HASH_ID=0
        local END_HASH_ID=$3
        if (( $3 == -1));then
            END_HASH_ID=9
        elif (($3 == -2));then
            END_HASH_ID=99
        elif (($3 == -3));then
            END_HASH_ID=999
        else
            END_HASH_ID=$3
        fi

        local MER_TABLE=`echo $4|sed "s/GENDATE/${CUR_DATE}/g"`
        local TEMPLATE_TABLE=`echo $5|sed "s/GENDATE/${CUR_DATE}/g"|sed "s/GENHASH/0/g"`
        exec_mysql "drop table if exists ${MER_TABLE};"
        exec_mysql "create table if not exists ${MER_TABLE} like ${TEMPLATE_TABLE};"
        exec_mysql "alter table ${MER_TABLE} ENGINE=INNODB;"
        local SQL="ALTER TABLE ${MER_TABLE} UNION=("
        for ((CUR_ID=${START_HASH_ID};CUR_ID<=${END_HASH_ID};CUR_ID++))
        do
            TABLE_NAME=`echo $5|sed "s/GENDATE/${CUR_DATE}/g"|sed "s/GENHASH/${CUR_ID}/g"`
            if ((${CUR_ID}==0))
            then
                SQL=`echo "${SQL}${TABLE_NAME}"`
            else
                SQL=`echo "${SQL},${TABLE_NAME}"`
            fi
        done
        SQL=`echo "${SQL});"`
        exec_mysql "$SQL"
        exec_mysql "Flush table ${MER_TABLE}; "
        CUR_DATE=`date --date="$CUR_DATE 1 days" +%Y%m%d`
    done
    return 0
}
# 采用暴力将每天单表拆分为多表,量大的情况下不建议使用,原始表命名必须符合 xxx_date的格式，如:Raw_Audit_Qzone_20100810
# @param $START_DATE $END_DATE $NEW_HASH_ID $SPLIT_FIELD $TABLE_PREFIX $DB_NAME
function split_one_table()
{
    if [ $# -ne 6 ];  then
        echo_red "Usage: $FUNCNAME START_DATE END_DATE NEW_HASH_ID SPLIT_FIELD TABLE_PREFIX DB_NAME" 1>&2 
        return 1
    fi
    check_start_end_date $1 $2 1>&2
    if [ $? -ne 0 ]; then        
        echo_red "Example: $FUNCNAME 20080228 20080328 100 fuin OnlineLog raw_onlinelog" 1>&2
        return 2
    fi
    LIB_START_DATE=$1
    LIB_END_DATE=$2
    NEW_LIB_HASH=$3
    SPLIT_FIELD=$4
    LIB_TABLE_PREFIX=$5
    LIB_DB_NAME=$6
    LIB_MERGE_CONTEXT="${MYSQL_CONTEXT} ${LIB_DB_NAME}"
    LIB_CUR_DATE=${LIB_START_DATE}
    while ((${LIB_CUR_DATE} <= ${LIB_END_DATE}))
    do
        LIB_HASH_ID=0
        while ((${LIB_HASH_ID} < ${NEW_LIB_HASH}))
        do
            LIB_HASH_TABLE="${LIB_TABLE_PREFIX}_${LIB_CUR_DATE}_Hash${LIB_HASH_ID}"
            ORIGINAL_TABLE="${LIB_TABLE_PREFIX}_${LIB_CUR_DATE}"
            exec_mysql_remote "drop table if exists ${LIB_HASH_TABLE};" ${LIB_MERGE_CONTEXT}
            exec_mysql_remote "create table ${LIB_HASH_TABLE} like $ORIGINAL_TABLE;" ${LIB_MERGE_CONTEXT}
            exec_mysql_remote "insert into ${LIB_HASH_TABLE} select * from $ORIGINAL_TABLE 
            where ${SPLIT_FIELD}%${NEW_LIB_HASH}=${LIB_HASH_ID};" ${LIB_MERGE_CONTEXT}

            exec_mysql_remote "flush table ${LIB_HASH_TABLE};" ${LIB_MERGE_CONTEXT}
            let LIB_HASH_ID=$LIB_HASH_ID+1
        done

        LIB_CUR_DATE=`date --date="${LIB_CUR_DATE} 1 day" +%Y%m%d`
    done
}
#
# 采用暴力将每天Hash表拆分为多表,会清洗原表,原始表命名必须符合 xxx_date_hash*的格式，如:Raw_Audit_Qzone 20100810_Hash*
# @param  $START_DATE $END_DATE $CUR_HASH_ID $OLD_HASH_NUM $NEW_HASH_NUM $SPLIT_FIELD $TABLE_PREFIX $OLD_DB $NEW_DB
function split_hash_table()
{
    if [ $# -ne 9 ];  then
        echo_red "Usage: $FUNCNAME START_DATE END_DATE HASH_ID OLD_HASH NEW_HASH SPLIT_FIELD TABLE_PREFIX OLD_DB NEW_DB" 1>&2       
        return 1
    fi
    check_start_end_date $1 $2 1>&2
    if [ $? -ne 0 ]; then        
        echo_red "Example: $FUNCNAME 20080228 20080328 0 10 200 fuin OnlineLog raw_onlinelog cal_onlinelog" 1>&2
        return 2
    fi
    LIB_START_DATE=$1
    LIB_END_DATE=$2
    LIB_CUR_HASH=$3
    OLD_HASH_NUM=$4
    NEW_HASH_NUM=$5
    SPLIT_FIELD=$6
    LIB_TABLE_PREFIX=$7
    OLD_DB=$8
    NEW_DB=$9
    LIB_MERGE_CONTEXT="${MYSQL_CONTEXT} ${NEW_DB}"

    LIB_CUR_DATE=${LIB_START_DATE}
    while ((${LIB_CUR_DATE} <= ${LIB_END_DATE}))
    do
        let LIB_HASH_ID=${NEW_HASH_NUM}-${OLD_HASH_NUM}+${LIB_CUR_HASH}
        while ((${LIB_HASH_ID} >= 0))
        do
            ORIGINAL_TABLE="${OLD_DB}.${LIB_TABLE_PREFIX}_${LIB_CUR_DATE}_Hash${LIB_CUR_HASH}"
            LIB_HASH_TABLE="${NEW_DB}.${LIB_TABLE_PREFIX}_${LIB_CUR_DATE}_Hash${LIB_HASH_ID}"
            if [ ${LIB_HASH_ID} -eq ${LIB_CUR_HASH} -a "$OLD_DB" = "$NEW_DB" ]
            then
                exec_mysql_remote "delete from $ORIGINAL_TABLE 
                where ${SPLIT_FIELD}%${NEW_HASH_NUM}!=${LIB_HASH_ID};"  ${LIB_MERGE_CONTEXT}
                exec_mysql_remote "optimize table ${ORIGINAL_TABLE};" ${LIB_MERGE_CONTEXT}
                exec_mysql_remote "flush table ${ORIGINAL_TABLE};" ${LIB_MERGE_CONTEXT}
            else
                exec_mysql_remote "drop table if exists ${LIB_HASH_TABLE};" ${LIB_MERGE_CONTEXT}
                exec_mysql_remote "create table ${LIB_HASH_TABLE} like $ORIGINAL_TABLE;" ${LIB_MERGE_CONTEXT}
                exec_mysql_remote "insert into ${LIB_HASH_TABLE} select * from $ORIGINAL_TABLE 
                where ${SPLIT_FIELD}%${NEW_HASH_NUM}=${LIB_HASH_ID};" ${LIB_MERGE_CONTEXT}
                exec_mysql_remote "flush table ${LIB_HASH_TABLE};" ${LIB_MERGE_CONTEXT}
            fi

            let LIB_HASH_ID=${LIB_HASH_ID}-${OLD_HASH_NUM}
        done

        LIB_CUR_DATE=`date --date="${LIB_CUR_DATE} 1 day" +%Y%m%d`
    done

    return 0
}
#
# 采用暴力将每天Hash表合并,不取消原表,原始表命名必须符合 xxx_date_hash*的格式，如:Raw_Audit_Qzone 20100810_Hash*
# @param  $CUR_DATE $OLD_HASH_NUM $NEW_HASH_NUM $DB_NAME $TABLE_PREFIX
function unite_hash_table()
{
    if [ $# -ne 8 ];  then
        echo_red "Usage: $FUNCNAME CUR_DATE OLD_HASH_NUM NEW_HASH_NUM DB_NAME TABLE_PREFIX" 1>&2
        return 1
    fi
    is_format_date $1 1>&2
    if [ $? -ne 0 ]; then        
        echo_red "Example: $FUNCNAME 20080328 10 39 raw_mqq Daily_Raw_Mqq_Online" 1>&2
        return 2
    fi
    LIB_CUR_DATE=$1
    LIB_OLD_HASH=$2
    LIB_NEW_HASH=$3
    LIB_DB_NAME=$4
    LIB_TABLE_PREFIX=$5
    LIB_MERGE_CONTEXT="${MYSQL_CONTEXT} ${LIB_DB_NAME}"
    LIB_HASH_ID=0
    while ((${LIB_HASH_ID} < ${LIB_NEW_HASH}))
    do
        LIB_NEW_TABLE="${TABLE_PREFIX}_${LIB_CUR_DATE}_Hash${LIB_HASH_ID}"
        let LIB_TMP_HASH=${LIB_HASH_ID}+${LIB_NEW_HASH}
        while ((${LIB_TMP_HASH} < ${LIB_OLD_HASH}))
        do
            LIB_OLD_TABLE="${TABLE_PREFIX}_${LIB_CUR_DATE}_Hash${LIB_TMP_HASH}"
            exec_mysql_remote "insert into $LIB_NEW_TABLE select * from $LIB_OLD_TABLE;" ${LIB_MERGE_CONTEXT}

            let LIB_TMP_HASH=${LIB_TMP_HASH}+${LIB_NEW_HASH}
        done
        exec_mysql_remote "flush table $LIB_NEW_TABLE;" ${LIB_MERGE_CONTEXT}
        let LIB_HASH_ID=${LIB_HASH_ID}+1
    done

    return 0
}

# 建立hash表，如:Raw_Audit_Qzone 20100810_Hash*
# @param  $START_DATE $END_DATE $MIN_HASH_ID $MAX_HASH_ID $TABLE_PREFIX $DB_NAME $CREATE_FIELD_SQL
function create_hash_table()
{
    if [ $# -ne 7 ];  then
        echo_red "Usage: $FUNCNAME START_DATE END_DATE MIN_HASH_ID MAX_HASH_ID TABLE_PREFIX DB_NAME CREATE_FIELD_SQL" 1>&2      
        return 1
    fi
    check_start_end_date $1 $2 1>&2
    if [ $? -ne 0 ]; then        
        echo_red "Example: $FUNCNAME 20080328 20080328 0 9 PtLogin_UinIP cal_uinipa \"uin int unsigned not null\"" 1>&2
        return 2
    fi
    LIB_START_DATE=$1
    LIB_END_DATE=$2
    MIN_LIB_HASH=$3
    MAX_LIB_HASH=$4
    LIB_TABLE_PREFIX=$5
    LIB_DB_NAME=$6
    LIB_SQL_EXPR=$7
    LIB_MERGE_CONTEXT="${MYSQL_CONTEXT} ${LIB_DB_NAME}"
    LIB_CUR_DATE=${LIB_START_DATE}
    while ((${LIB_CUR_DATE} <= ${LIB_END_DATE}))
    do
        LIB_HASH_ID=${MIN_LIB_HASH}
        while ((${LIB_HASH_ID} <= ${MAX_LIB_HASH}))
        do
            LIB_TABLE_NAME="${LIB_TABLE_PREFIX}_${LIB_CUR_DATE}_Hash${LIB_HASH_ID}"
            exec_mysql_remote "drop table if exists ${LIB_TABLE_NAME};" ${LIB_MERGE_CONTEXT}
            exec_mysql_remote "create table ${LIB_TABLE_NAME}(${LIB_SQL_EXPR});" ${LIB_MERGE_CONTEXT}

            let LIB_HASH_ID=${LIB_HASH_ID}+1
        done

        LIB_CUR_DATE=`date --date="${LIB_CUR_DATE} 1 day" +%Y%m%d`
    done

    return 0
}



##以下为copy samli的func-common Bash公共函数库,没有经过验证
## --------------------- OS / HW info ----------------------

## check if running on SUSE OS
## return true / false
function check_suseos()
{
    if [[ -f "/etc/SuSE-release" ]]; then
        grep -wqF 'SUSE' /etc/SuSE-release && return 0
    fi

    [[ -x /sbin/yast2 ]]  && return 0 || :

    return 1
}

## check if running on Slackware OS
## return true / false
function check_slkos()
{
    if [[ -f "/etc/slackware-version" ]]; then
        grep -wqF 'Slackware' /etc/slackware-version &>/dev/null && return 0
    fi

    [[ -x /sbin/installpkg ]]  && return 0 || :

    return 1
}

## check if running on RedHat OS
## return true / false
function check_rhos()
{
    if [[ -f /etc/redhat-release ]]; then
        grep -wqi red /etc/redhat-release &>/dev/null && return 0
    fi

    return 1
}

## print OS info, now just os version 
function get_osinfo()
{
    ## use xargs to delete '\n', I love xargs!
    if check_suseos; then
        xargs < /etc/SuSE-release
    elif check_slkos; then
        xargs < /etc/slackware-version
    elif check_rhos; then
        xargs < /etc/redhat-release
    else
        ## lsb_release may be found on ubuntu, debian, etc.
        lsb_release -d 2>/dev/null || echo 'UNKNOWD OS'
    fi
}

## print OS name
function get_osname()
{
    if check_suseos; then
        echo SUSE
    elif check_slkos; then
        echo SLK
    elif check_rhos; then
        echo RH
    else
        echo UNKNOWN
        return 1
    fi
}

## with bit flag
function get_osname2()
{
    echo $( get_osver )_$( get_cputype )
}

## return 32/64, based on OS but not hardware
function get_cputype()
{
    if uname -a | grep -Fq 'x86_64'; then
        echo 64
    else
        echo 32
    fi
}

function get_osver()
{
    if grep -Eq 'Slackware[[:blank:]]+8\.[0-9]'  /etc/slackware-version; then
        echo slk8
    elif grep -Eq 'Slackware[[:blank:]]+10\.[0-9]'  /etc/slackware-version; then
        echo slk10
    elif check_suseos; then
        echo "suse$( get_cputype )"
    elif check_rhos; then
        echo "rh$( get_cputype   )"
    else
        echo "UNKNOWN"
    fi 2>/dev/null
}

## return kernel version: 2.4 / 2.6
function get_kernver()
{
    /sbin/kernelversion 2>/dev/null ||
    uname -r | grep -o '^2\..'
}

## get free capacity of a partition by a filename/pathname
function get_free_cap()
{
    local path=$1

    if [[ ! -e "$path" ]]; then
        echo 0B
        return
    fi

    ## df so cool!
    df -h "$path" | awk 'NR==2 { print $4 }'
}


## get the size of files by du
## example: get_file_size "/var/log"
function get_file_size()
{
    ## do not quote [$file], may contain more than one filename
    local file=$1
    local size=$( du -sh $file 2>/dev/null | awk '{ print $1; exit }' || echo 0B )

    echo ${size:-1} | grep -q '^[0-9]$' && size=${size}B
    echo ${size:-0B}
}

## get the size of physical mem
function get_mem_size()
{
    local unit=$1
    local resut dividend

    case $unit in 
        k|K)
        dividend=1
        ;;
        m|M)
        dividend=1000
        ;;
        g|G)
        dividend=1000000
        ;;
        t|T)
        dividend=1000000000
        ;;
        *)
        dividend=1  ## default, K
        ;;
    esac

    resut=$( awk '/^MemTotal/ { print $2 }' /proc/meminfo )
    calculate2 "$resut / $dividend"
}

## get the size of all hard disks
function get_hdd_size()
{
    local unit=$1
    local resut dividend

    case $unit in 
        k|K)
        dividend=1
        ;;
        m|M)
        dividend=1000
        ;;
        g|G)
        dividend=1000000
        ;;
        t|T)
        dividend=1000000000
        ;;
        *)
        dividend=1  ## default, K
        ;;
    esac

    ## check /proc/partitions, fdisk -l not reliable
    resut=$( 
    awk 'BEGIN{ total = 0 }
    {
        if ( $1 !~ /^[[:space:]]*[0-9]+/ ) {
            next
        }

        if ( $NF ~ /cciss\/c[0-9]d[0-9][[:space:]]*$/ || $NF ~ /[sh]d[a-z][[:space:]]*$/ ) {
            total += $3
        }
    }
    END { printf("%d", total) }' /proc/partitions
    )

    calculate2 "$resut / $dividend"
}

## get cpu name: intel/amd x $core_num
function get_cpu_name()
{
    awk 'BEGIN{ num = 0; name = "unknow"; FS = ":" }
    {
        if ( $1 !~ /^model name/ ) {
            next
        }
        if ( $0 ~ /[Ii]ntel/ ) {
            name = "Intel"
        }
    else if ( $0 ~ /AMD/ ) {
        name = "Amd"
    }
else {
    name = 'unknow'
}
num++
    }
    END { print name"x"num }' /proc/cpuinfo
}

## get cpu cache sizes
function get_cpu_cachesize()
{
    awk 'BEGIN{ num = 0; size = 0; FS = ":"; }
    {
        if ( $1 ~ /^cache size/ ) {
            num++
            size = $2 + 0
        }
    }
    END { print size"Kx"num }' /proc/cpuinfo
}

## cnt of cpu core
function get_cpu_core_cnt()
{
    grep -c cores /proc/cpuinfo
}

function get_cpu_modename()
{
    awk -F: '/^model name/ { print $2 }' /proc/cpuinfo | sed 1q | trim
}


## 2009-01-14 samli, check if a partition readonly
## argv: $mountpoint / $pathname
## return true / false
function is_partition_readonly()
{
    local p=$1
    local mountpoint
    local rw_flag

    mountpoint=$( get_mountpoint_for_pathname "$p" )

    ## rw_flag: ro / rw
    rw_flag=$(
    awk -vp=$mountpoint '
    {
        if ( $1 != "/dev/root" && $2 == p ) {
            str=$4
            gsub(",.*", "", str)
            print str
            exit
        }
    }' /proc/mounts )

    if [[ $rw_flag == "ro" ]]; then
        return 0
    else
        return 1
    fi
}

## 2009-01-14 samli, check if a partition no space left
## argv: $mountpoint / $pathname
## return true / false
function is_partition_full()
{
    local p=$1
    local full_flag

    case $p in
        /*)
        ;;
        *)
        return 1
        ;;
    esac

    ## check inode and data area
    full_flag=$( 
    { df -Pi "$p"; df -Pk "$p"; } |
        awk '! /^Filesystem/ {
        usage = $(NF-1) + 0
        if ( usage == 100 ) {
            print "Y"
            exit
        }
    }'
    )

    if [[ $full_flag == "Y" ]]; then
        return 0
    else
        return 1
    fi
}  

## find the username we added manually
## see man shadow to find the detail of the policy
function find_non_sys_user()
{

    # need root privilege to access '/etc/shadow'
    (( UID == 0 )) || return 1

    perl -we '
    use strict;
    my @users;
    my $fd;
    my ( $user, $pass, $uid );

    ## find the username having password
    open ($fd, "<", "/etc/shadow") or die "Can not open /etc/shadow\n";
    while (<$fd>) {
        ($user, $pass ) = (split ":")[0,1];
        next if $user eq "root";

        if ( $pass =~ m{ [a-zA-Z0-9/\$] }x ) {
            push @users, $user;
        }            
        elsif ( $pass eq "" ) {
        push @users, $user;
    }
}
close $fd or die "Can not close $fd\n";

## find the username having uid >= normal uid
open ($fd, "<", "/etc/passwd") or die "Can not open /etc/passwd\n";
while (<$fd>) {
    ($user, $uid ) = (split ":")[0,2];
    next if $user eq "root";
    next if $user eq "nobody";

    if ( $uid >= 1000 ) { ## should  read this val from /etc/login.defs
        push @users, $user unless grep { /\b$user\b/ }  @users;
    }
    elsif ( $uid == 0 ) { ## make sure dangerous user with uid = 0
    push @users, $user unless grep { /\b$user\b/ }  @users;
}
    }
    close $fd or die "Can not close $fd\n";

    for my $u (sort @users) {
        print "$u", " ";
    }
    '
}

## ---------------------------------------------------------


## --------------------------- NUM -------------------------

## a simple int calculater
## argv: "$math_expression"
## example: calculate "10 / 2"
function calculate()
{
    local expr=$@

    if which bc &>/dev/null; then
        echo "scale = 0; $expr" | bc
    elif which perl &>/dev/null; then
        echo "$expr" | perl -lne ' print int (eval) '
    else
        echo $(( $expr ))
    fi
}

## support float
function calculate2()
{
    local expr=$@

    if which bc &>/dev/null; then
        echo "scale = 2; $expr" | bc
    elif which perl &>/dev/null; then
        echo "$expr" | perl -lne ' printf ("%0.2f",  (eval) ) '
    else    ## may try awk here
        return 1
    fi
}
## check if argv1 >= argv2
## argv1: $num_1
## argv2: $num_2
function compare_two_num()
{
    if (( $# != 2 )); then
        return 1
    fi

    ## hope perl is install in every OS ...
    perl -we ' my ($v1, $v2) = @ARGV; exit ( $v1 >= $v2 ? 0 : 1 ) ' $1 $2
}

## get a random num
## argv: $max, optionall
function get_a_random_num()
{
    local max=$1
    local rand=0

    if [[ -z $max ]]; then
        echo $(( RANDOM + 1 ))   ## 1 ~ 32768, see man bash
    else
        # echo $RANDOM$RANDOM % $1 | perl -lne ' print eval '
        while (( rand == 0 )); do
            ## 3276732767 < ( 2^32 = 4294967296 )
            rand=$( calculate "( $RANDOM$RANDOM + $RANDOM + $RANDOM ) % $max" )
        done
        echo $rand
    fi
}

## ------------------------- MISC --------------------------

function is_dos_file()
{
    local file=$1

    file "$file" | grep -q 'CRLF'
}

## dos2unix is lost on some servers -_-!
function my_dos2unix()
{
    local file=$1

    if which dos2unix ; then
        ## some strange dosunix will not work with abs-path
        (
        cd "$( dirname $file )"
        dos2unix "$file"
        )
    else
        perl -pi -e 's/\r$//' "$file"
    fi &> /dev/null
}

function dos2unix_if_necessary()
{
    local file=$1

    [[ -f $file ]] || return 1

    if is_dos_file "$file"; then
        my_dos2unix "$file"
    else
        return 0
    fi
}


#***************************************************************下面为扫盲内容************************************
#文件的 Access time，atime 是在读取文件或者执行文件时更改的。
#文件的 Modified time，mtime 是在写入文件时随文件内容的更改而更改的。
#文件的 Create time，ctime 是在写入文件、更改所有者、权限或链接设置时随 Inode 的内容更改而更改的。 
#因此，更改文件的内容即会更改 mtime 和 ctime，但是文件的 ctime 可能会在 mtime 未发生任何变化时更改 
#如在权限更改，但是文件内容没有变化的情况下。 
#ls(1) 命令可用来列出文件的 atime、ctime 和 mtime。
#ls -lc filename         列出文件的 ctime
#ls -lu filename         列出文件的 atime
#ls -l filename          列出文件的 mtime  
#
# ${ } 的一些功能：
#假设我们定义了一个变量为：
#file=/dir1/dir2/dir3/my.file.txt
#我们可以用 ${ } 分别替换获得不同的值：
#${file#*/}：拿掉第一条 / 及其左边的字串：dir1/dir2/dir3/my.file.txt
#${file##*/}：拿掉最后一条 / 及其左边的字串：my.file.txt
#${file#*.}：拿掉第一个 .   及其左边的字串：file.txt
#${file##*.}：拿掉最后一个 .   及其左边的字串：txt
#${file%/*}：拿掉最后条 / 及其右边的字串：/dir1/dir2/dir3
#${file%%/*}：拿掉第一条 / 及其右边的字串：(空值)
#${file%.*}：拿掉最后一个 .   及其右边的字串：/dir1/dir2/dir3/my.file
#${file%%.*}：拿掉第一个 .   及其右边的字串：/dir1/dir2/dir3/my
#记忆的方法为：
#     # 是去掉左边(在鉴盘上 # 在 $ 之左边)
#    % 是去掉右边(在鉴盘上 % 在 $ 之右边)
#    单一符号是最小匹配﹔两个符号是最大匹配。
#${file:0:5}：提取最左边的 5 个字节：/dir1
#${file:5:5}：提取第 5 个字节右边的连续 5 个字节：/dir2
#我们也可以对变量值里的字串作替换：
#${file/dir/path}：将第一个 dir 提换为 path：/path1/dir2/dir3/my.file.txt
#${file//dir/path}：将全部 dir 提换为 path：/path1/path2/path3/my.file.txt
#利用 ${ } 还可针对不同的变数状态赋值(没设定、空值、非空值)：
#${file-my.file.txt} ：假如 $file 没有设定，则使用 my.file.txt 作传回值。(空值及非空值时不作处理)
#${file:-my.file.txt} ：假如 $file 没有设定或为空值，则使用 my.file.txt 作传回值。 (非空值时不作处理)
#${file+my.file.txt} ：假如 $file 设为空值或非空值，均使用 my.file.txt 作传回值。(没设定时不作处理)
#${file:+my.file.txt} ：若 $file 为非空值，则使用 my.file.txt 作传回值。 (没设定及空值时不作处理)
#${file=my.file.txt} ：若 $file 没设定，则使用 my.file.txt 作传回值，同时将 $file 赋值为 my.file.txt (空值及非空值时不作处理)
#${file:=my.file.txt} ：若 $file 没设定或为空值，则使用 my.file.txt 作传回值，同时将 $file 赋值为 my.file.txt (非空值时不作处理)
#${file?my.file.txt} ：若 $file 没设定，则将 my.file.txt 输出至 STDERR。 (空值及非空值时不作处理)
#${file:?my.file.txt} ：若 $file 没设定或为空值，则将 my.file.txt 输出至 STDERR。 (非空值时不作处理)
#tips:
#以上的理解在于, 你一定要分清楚 unset 与 null 及 non-null 这三种赋值状态.
#一般而言, : 与 null 有关, 若不带 : 的话, null 不受影响, 若带 : 则连 null 也受影响.
#得到长度
#x="abcd"
#方法一
#expr length $x
# 方法二
#echo ${#x}
# 方法三
#expr "$x" : ".*"
#
#**************************************************************************************


#主程序，方便调用
if [ $# -ne 0 ]; then
    $*
fi