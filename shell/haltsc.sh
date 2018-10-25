#!/bin/bash
#
#Author: hehao
#Email:  mickeymousesysu@gmail.com
#Date: 2013-11-07
##Function:
#
#      exit all the screen session 
#Note:
#       must install screen firstly

str=$(screen -ls)  

array=$(echo $str|tr "." "\n")  

for V in $array  
do  
if [ $V -gt 0  ]  
then screen -S $V -X quit  
fi  
done
