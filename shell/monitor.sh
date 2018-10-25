#!/bin/bash
#*************************************************************************************#
#   Author:   monkeyhe
#     Mail:   328679181@qq.com
#     Date:   2014-08-13
# Function:
#             周期地检查cpu、内存、硬盘是否超过指标，如果超过指标，发送告警邮件到指定的邮箱中         
#    Notes:   
#             邮件发送依赖send_mail.pl脚本,内容、标题、收信人、发信人需手动配置
#*************************************************************************************#

scriptName=`basename $0`


#-- global config --#

## 邮件发送模块路径 
mailPath="/usr/local/support/bin/send_mail.pl"
## 收信人清单,多个收件人之间用;分割
mailTo="monkeyhe@tencent.com"
## 发信人
sender="monkeyhe"
## 邮件标题
title="MIG-监控告警 Warning!"
## 邮件内容
content="<p>This is a test mail!<br />这是一封测试测试！</p>"



#-- 监控阈值设置 --#
## 硬盘已用空间 百分比
hdUsed=0.50

## 内存已用空间 百分比
memUsed=0.50

## 虚存已用空间 百分比
swapUsed=0.95

function configMail()
{
    local ip=$(getIPAddress)
    body="<span style='color:red' >Warning:</span> Space resource <strong>$service</strong> at $ip is NOT enough!<br /><hr /><p>$content</p>"
    body=$(utf8ToGbk "$body")
    mTitle=$(utf8ToGbk "$title")
}

function sendWarnMail ()
{
    par1="$1"
    res=${par1//\\n/<br\/>}
    $($mailPath "$mailTo"  "$body<hr />$res" "--title=$mTitle" "--sender=$sender" >>monitor.log 2>&1) 	
}

function usage ()
{
    echo "Usage: $scriptName -t [Time] -n [TryTimes](Opt.) -m [MailTimes](Opt.)"
    printf "       -t 时间间隔（单位为秒）\n       -n 监控次数（可选项)  达到这个次数，监控程序将停止。若缺失,则监控程序永远执行下去\n       -m 监控参数超过指标后发送告警邮件的次数（可选项）若不提供参数，则每次超过指标时都会发送告警邮件 \n"
    echo " Ex.1: 以10秒的间隔监控设备，每次参数超标发报警邮件"
    echo "       $scriptName -t 10"
    echo " Ex.2: 以10秒的间隔监控设备,每次超标发报警邮件，监控100次后停止"
    echo "       $scriptName -t 10 -n 100"
    echo " Ex.3: 以10秒的间隔监控设备，监控100次后停止,当参数超过指标时最多发送3封告警邮件"
    echo "       $scriptName -t 10 -n 100 -m 3"
}

function utf8ToGbk ()
{
    echo $(echo $1 | iconv -f utf8 -t gbk//IGNORE 2>>monitor.log)
}

function getIPAddress ()
{
    ifconfig -a | grep 'inet addr:' | grep -v '127.0.0.1' | awk '{print $2}' | cut -d ':' -f 2
}

function clearScreen ()
{
    col=`tput cols`
    line=`tput lines`
    let sum=col*line
    tput cup 0 0
    printf "%${sum}s\n" " "
}

cpuNums=`cat /proc/cpuinfo |grep "processor"|wc -l`

function cpustat()
{
    eval $(cat /proc/stat | grep '^cpu' | awk '{print "cpu"NR-1"=("$0")"}')
    for ((i=0; i<=$cpuNums; i++))
    do
        eval cpus=(\${cpu${i}[@]})
        unset cpus[0]
        echo ${cpus[*]} 
        idle=${cpus[$id]}
        #echo $idle
        
        total=0
        for val in ${cpus[@]} 
        do
            let total+=$val
        done
        #echo $total
        
        let dIdle=$idle-${pIdle[$i]}
        let dTotal=$total-${pTotal[$i]}
        let "usage=(100000*($dTotal-$dIdle))/$dTotal"
        let units=$usage/1000
        let deci=$usage%1000
        if [ $deci -eq 0 ];then
            deci="000"
        fi
        if [ $i -eq  0 ] ;then
            echo -e "\rUsage-CPU-AVG: $units.$deci% "
        else
            echo -e "\rUsage-CPU-$i: $units.$deci% "
        fi
        pTotal[$i]=$total
        pIdle[$i]=$idle
    done
}

function checkDevice()
{
    local mu=$(free | awk 'NR==2' | awk '{print $3}')
    local ma=$(free | awk 'NR==2' | awk '{print $2}')
    local useMem=$(echo "scale=1;$mu/$ma" | bc)
    local su=$(free | awk 'NR==4' | awk '{print $3}')
    local sa=$(free | awk 'NR==4' | awk '{print $2}')
    local useSwap=$(echo "scale=1;$su/$sa" | bc)
    local useHd=$(df -h | grep '^/dev/' | awk '{print int($5)}')
    local hdName=($(df -h | grep '^/dev/' | awk '{print $1}'))
    # echo $mu $ma $useMem $su $sa $useSwap $useHd
    local msg=""
    local i=0
    local hdWarn=false
    local hdUsed=$(echo "scale=0;$hdUsed*100/1" | bc)
    for devHd in $useHd
    do
        if [ "$devHd" -gt "$hdUsed" ]; then
            hdWarn=true
            msg="Harddisk space will be exhausted!\n Disk Name: ${hdName[$i]}\n Used Pencentage: $devHd%\n"
            break
        fi
        let i++
    done 
    local memWarn=false
    if [ `echo "$useMem>$memUsed" | bc` -eq 1  -o `echo "$useSwap>$swapUsed" | bc` -eq 1 ]; then
        useMem=$(echo "scale=0;$useMem*100/1" | bc)
        useSwap=$(echo "scale=0;$useSwap*100/1" | bc)
        msg="$msg \nMemory space will be exhausted!\n Mem Used Percentage:$useMem%\n Swap Used Percentage:$useSwap%\n" 
        memWarn=true
    fi
    echo $da >> monitor.log
    if $hdWarn || $memWarn; then
        if [ $mt  -lt $mailTimes ]; then 
            sendWarnMail "$msg"
            let mt++
        fi
        echo -e "[Warning] No Enough Space!\n$msg"  | tee -a monitor.log
    else
        echo -e "Everything is fine!"  | tee -a monitor.log
        let mt=0
    fi
}


if [ "$#" -lt 1 -o "$#" -gt 8 ]; then
    usage
    exit 1
fi 

while getopts "p:t:n:m:h" arg
do
    case $arg in
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

#echo "$choice  $interval $tryTimes $mailTimes"

if [  -z "$tryTimes" ]; then
    eternal=true
else
    eternal=false
fi

configMail

tt=0
mt=0
id=4
showT=4

for ((i=0; i<=$cpuNums; i++))
do
    pTotal[i]=0
	pIdle[i]=0
done


clear
while $eternal ||  [ $tt -lt $tryTimes ]
do
    da=`date +%Y/%m/%d-%H:%M:%S`
    echo -ne "\033[?25l\033[0;0H"    
    echo  $da
    if [ $showT -eq 1 -o $showT -eq 4 ];then
        printf "\n#=============================CPU监控==============================#\n"
        printf "  user    nice   system   idle   iowait   irq softIrq stealTime guest\n"
        cpustat 
    fi
    if [ $showT -eq 2 -o $showT -eq 4 ];then
        printf "\n#=========================内存 & 虚存监控==========================#\n"
        free
    fi
    if [ $showT -eq 3 -o $showT -eq 4 ];then
        printf "\n#=============================硬盘监控=============================#\n"
        df -m
    fi
    echo -en "\033[?25h"
    printf "\n#=============================报警信息=============================#\n"
    checkDevice
    echo
    read -t $interval -n1 -p "输入选择[c|m|h|a|q]: " select
    echo 
    case $select in
        c)
            showT=1
            clearScreen
        ;;
        m)
            showT=2
            clearScreen
        ;;
        h)
            showT=3
            clearScreen
        ;;
        a)
            showT=4
            clearScreen
        ;;
        q)
            exit 0
        ;;
        *)
        ;;
    esac
    let tt++
done

exit 0
