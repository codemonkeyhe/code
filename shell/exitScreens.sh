#!/bin/bash
#
#Author: hehao
#Email:  mickeymousesysu@gmail.com
#Date: 2014-01-07
#Function:
#
#      exit all the screen session 
#Note:
#       must install screen firstly

screen_pids=$(screen -ls | grep 'pts' | cut -d '.' -f 1)
for screen_id in $screen_pids
do
#        $(screen -dr $screen_id)
        echo  'kill screen pid ='.$screen_id
        $(screen -S $screen_id  -X quit)
done
