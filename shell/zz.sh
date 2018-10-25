#!/bin/bash
##############################################
#   Author:   monkeyhe
#     Mail:   328679181@qq.com
#     Date:   2014-08-12
# Function:
#           后台僵尸程序 
###############################################

id=4


for (( i=0;i<=8;i++))
do
    pTotal[i]=0
	pIdle[i]=0
done

while true
do
    eval $(cat /proc/stat | grep '^cpu' | awk '{print "cpu"NR-1"=("$0")"}')
    for ((i=0;i<=8;i++))
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
        let "usage=(100000000*($dTotal-$dIdle))/$dTotal"
        let units=$usage/1000000
        let deci=$usage%1000000
        
        
        if [ $i -eq  0 ] ;then
            echo  "CPU AVG: $units.$deci% "
        else
            echo  "CPU$i: $units.$deci% "
        fi
        pTotal[$i]=$total
        pIdle[$i]=$idle
    done
    sleep 2
done
