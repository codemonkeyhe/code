#!/bin/bash
##############################################
#   Author:   monkeyhe
#     Mail:   328679181@qq.com
#     Date:   2014-08-12
# Function:
#           后台僵尸程序 
###############################################


i=1
while [ $i > 0 ]
do
    sleep 1
	echo $i
    if [ $i == 3 ]; then
        echo "done"
    fi
	let i++
done
