#!/bin/bash
#Date: 20131110
#Author: Yang wen huan
#Function:
#Email: 

function nav()
{
   echo  "(c) cpu info"  
   echo  "(m) memory info"
   echo  "(e) exit"
   echo  -n "your choose:"
}


function subnav1()
{
   echo "(d) date"
   echo "(c) cpu load"
   echo "(b) back"
   echo "(e) exit"
   echo -n "your choose:"
}


function subnav2()
{
   echo "(m) memory left"
   echo "(s) swap left"
   echo "(b) back"
   echo "(e) exit"
   echo -n "your choose:"
}

nav
read  choose 
while [ "$choose" != "e" ]
do
	if [ $choose  == "c" ] ;then
    		echo ; subnav1
		read cupchoice
		while true
		do
			case $cupchoice in
			"d")
				date +%Y/%m/%d ; echo
				;;
			"c")
				top | head -n 3 | tail -n 1 ; echo
				;;
			"b")
				echo ; break 
				;;
			*)
				exit 1
				;;
			esac
			subnav1
			read cupchoice
		done
	elif [ "$choose" == "m" ] ;then
    		echo ; subnav2
		read memchoice
		while true
		do
			case $memchoice in
			"m")	
				top | head -n 4 | tail -n 1 | cut -d ',' -f 3 ; echo
				;;
			"s")
				top | head -n 5 | tail -n 1 | cut -d ',' -f 3 ; echo  
				;;
			"b")
			  	echo ; break
				;;
			*)
				exit 1
				;;
			esac
			subnav2
			read memchoice
		done
	else
    		exit 1
	fi
	nav
	read choose	
done
exit 0


