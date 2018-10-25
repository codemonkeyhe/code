#!/bin/bash
##############################################
#   Author:   monkeyhe
#     Mail:   328679181@qq.com
#     Date:   2014-08-12
# Function:
#           后台僵尸程序 
###############################################


ipstr="192.168.1.152,192.168.1.153";  
declare -a arr;  

eval $(cat /proc/stat | grep '^cpu' | awk '{print "cpu"NR-1"=("$0")"}')  

echo ${cpu1[@]}
<<HHH
#echo ${cpu[@]}
for line in ${cpu[@]}
do
   # arr="( $line)"
   # echo ${arr[@]}a
   echo "$line"
done
HHH

exit 0
 eval $(echo $ipstr | awk '{split($0, filearray, ",");for(i in filearray)print "arr["i"]="filearray[i]}')  
#eval 把print的内容，和javascript的eval一样的功能  
#echo ${arr[1]}  
for i in ${arr[*]}  
do  
 echo $i
done
