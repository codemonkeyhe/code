#!/bin/bash
 # Draw-box.sh: 用ASCII字符画一个盒子.
 
 # Stefano Palmeri编写,文档作者作了少量编辑.
 # 征得作者同意在本书使用.
 
 
 ######################################################################
 ###  draw_box 函数的注释  ###
 
 #  "draw_box" 函数使用户可以在终端上画一个盒子.
 #
 #
 #  用法: draw_box ROW COLUMN HEIGHT WIDTH [COLOR] 
 #  ROW 和 COLUMN 定位要画的盒子的左上角.       
 #
 #  ROW 和 COLUMN 必须要大于0且小于目前终端的尺寸.
 #
 #  HEIGHT 是盒子的行数,必须 > 0. 
 #  HEIGHT + ROW 必须 <= 终端的高度. 
 #  WIDTH 是盒子的列数,必须 > 0.
 #  WIDTH + COLUMN 必须 <= 终端的宽度.
 #
 #  例如: 如果你当前终端的尺寸是 20x80,
 #  draw_box 2 3 10 45 是合法的
 #  draw_box 2 3 19 45 的 HEIGHT 值是错的 (19+2 > 20)
 #  draw_box 2 3 18 78 的 WIDTH 值是错的 (78+3 > 80)
 #
 #  COLOR 是盒子边框的颜色.
 #  它是第5个参数,并且它是可选的.
 #  0=黑色 1=红色 2=绿色 3=棕褐色 4=蓝色 5=紫色 6=青色 7=白色.
 #  如果你传给这个函数错的参数,
 #+ 它就会以代码65退出,
 #+ 没有其他的信息打印到标准出错上.
 #
 #  在画盒子之前要清屏.
 #  函数内不包含有清屏命令.
 #  这使用户可以画多个盒子,甚至叠接多个盒子.
 
 ###  draw_box 函数注释结束  ### 
 ######################################################################
 
 draw_box(){
 
 #=============#
 HORZ="-"
 VERT="|"
 CORNER_CHAR="+"
 
 MINARGS=4
 E_BADARGS=65
 #=============#
 
 
 if [ $# -lt "$MINARGS" ]; then                 # 如果参数小于4,退出.
     exit $E_BADARGS
 fi
 
 # 搜寻参数中的非数字的字符.
 # 能用其他更好的办法吗 (留给读者的练习?).
 if echo $@ | tr -d [:blank:] | tr -d [:digit:] | grep . &> /dev/null; then
    exit $E_BADARGS
 fi
 
 BOX_HEIGHT=`expr $3 - 1`   #  -1 是需要的,因为因为边角的"+"是高和宽共有的部分. 
 BOX_WIDTH=`expr $4 - 1`    #
 T_ROWS=`tput lines`        #  定义当前终端长和宽的尺寸, 
 T_COLS=`tput cols`         #
          
 if [ $1 -lt 1 ] || [ $1 -gt $T_ROWS ]; then    #  如果参数是数字就开始检查有效性.
    exit $E_BADARGS                             #
 fi
 if [ $2 -lt 1 ] || [ $2 -gt $T_COLS ]; then
    exit $E_BADARGS
 fi
 if [ `expr $1 + $BOX_HEIGHT + 1` -gt $T_ROWS ]; then
    exit $E_BADARGS
 fi
 if [ `expr $2 + $BOX_WIDTH + 1` -gt $T_COLS ]; then
    exit $E_BADARGS
 fi
 if [ $3 -lt 1 ] || [ $4 -lt 1 ]; then
    exit $E_BADARGS
 fi                                 # 参数检查完毕.
 
 plot_char(){                       # 函数内的函数.
    echo -e "\E[${1};${2}H"$3
 }
 
 echo -ne "\E[3${5}m"               # 如果传递了盒子边框颜色参数,则设置它.
 
 # start drawing the box
 
 count=1                                         #  用plot_char函数画垂直线
 for (( r=$1; count<=$BOX_HEIGHT; r++)); do      #
   plot_char $r $2 $VERT
   let count=count+1
 done 
 
 count=1
 c=`expr $2 + $BOX_WIDTH`
 for (( r=$1; count<=$BOX_HEIGHT; r++)); do
   plot_char $r $c $VERT
   let count=count+1
 done 
 
 count=1                                        #  用plot_char函数画水平线
 for (( c=$2; count<=$BOX_WIDTH; c++)); do      #
   plot_char $1 $c $HORZ
   let count=count+1
 done 
 
 count=1
 r=`expr $1 + $BOX_HEIGHT`
 for (( c=$2; count<=$BOX_WIDTH; c++)); do
   plot_char $r $c $HORZ
   let count=count+1
 done 
 
 plot_char $1 $2 $CORNER_CHAR                   # 画盒子的角.
 plot_char $1 `expr $2 + $BOX_WIDTH` +
 plot_char `expr $1 + $BOX_HEIGHT` $2 +
 plot_char `expr $1 + $BOX_HEIGHT` `expr $2 + $BOX_WIDTH` +
 
 echo -ne "\E[0m"             #  恢复最初的颜色.
 
 P_ROWS=`expr $T_ROWS - 1`    #  在终端的底部打印提示符.
 
 echo -e "\E[${P_ROWS};1H"
 }      
 
 
 # 现在, 让我们来画一个盒子.
 clear                       # 清屏.
 R=2      # 行
 C=3      # 列
 H=10     # 高
 W=45     # 宽
 col=1    # 颜色(红)
 draw_box $R $C $H $W $col   # 画盒子.
 
 exit 0
 

