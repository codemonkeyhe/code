#!/bin/bash
while getopts "a:b:c:" arg #选项后面的冒号表示该选项需要参数
do
        case $arg in
             a)
                echo "a's arg:$OPTARG" #参数存在$OPTARG中
                ;;
             b)
                echo "b's arg:$OPTARG"
                ;;
             c)
                echo "c's arg:$OPTARG"
                ;;
             ?)  #当有不认识的选项的时候arg为?
            echo "unkonw argument"
            ;;
        esac
done


