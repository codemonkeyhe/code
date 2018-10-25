#!/bin/bash
hour=`date +%H`
da=`date -d yesterday  +%Y%m%d`
echo -e "Time Info: hour=$hour\t  date=$da"  

#remove core file if need
coreDir="/usr/local/app/taf/app_log/"
rmTime=$(($hour%6))
if [ $rmTime -eq 0 ]; then
    if [ -d $coreDir ]; then
        echo -e "Begin  remove core file per 6 hours, such as at 0 6 12 18 olock\n"
        cd $coreDir
        if [ $? -eq 0 ]; then
            echo "removing core in `pwd`"
            echo `rm core* `
            echo -e "remove core Done!\n"
        else
            echo -e "CAN NOT open core dir!Core dir=i$coreDir\n"
        fi
    else
        echo -e "CAN NOT find core dir in $coreDir\n"
    fi
else
   echo "No need to rm core!rmTime=$rmTime"
fi
wait

#remove server log
logDir="/usr/local/app/taf/app_log/MTT/"
logName="*$da.log"
echo -e "Begin rm $logName ..."
#this server only keep on day log
myserverlist=`ls $logDir | egrep "Video|Fun|Tag|ZiXun|Read|Cool|Novel"`
for server in $myserverlist
do 
    serverDir="$logDir$server"
    cd $serverDir
    if [ $? -eq 0 ]; then
        echo "`pwd`: Removing Log ..." 
	echo `rm $logName `
        echo -e "$serverDir: Remove Log Done!\n"

    else
        echo "cd $serverDir failed!"
    fi
done

#reomove all the log
allLog="/usr/local/app/taf/app_log/MTT/*Server/"$logName
echo "remove all the log in $allLog"
rm $allLog
echo -e "$allLog: remove done!\n"

strict=1
#remove the server dir if not our server
otherserverlist=`ls $logDir | egrep -v "Video|Fun|Tag|ZiXun|Read|Cool|Novel"`
if [ $strict -eq 1 -a $hour -lt 6 ]; then
    echo "rm other server"
    for ser in $otherserverlist
    do 
        serDir="$logDir$ser"
        if [ -d $serDir ]; then
           echo "rm -rf $serDir "
           rm -rf $serDir 
        fi
    done
fi
wait
echo "Well Done!"