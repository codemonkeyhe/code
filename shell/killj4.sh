#!/bin/bash
##############################################
#   Author:   monkeyhe
#     Mail:   328679181@qq.com
#     Date:   2014-08-12
# Function:
#           后台僵尸程序 
###############################################

ps -elf | grep make | awk '{print $4}' | xargs kill -9 

