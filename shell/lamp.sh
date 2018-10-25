#!/bin/bash
#
#Author: hehao
#Email:  mickeymousesysu@gmail.com
#Date: 2013-11-07
#Function:
#
#      install LAMP automatically
#Note:
#    Please open 80 port at iptables!Or others CAN NOT access your web services! 
#    The following requirement is need for install LAMP
#	yum install make 
#    The following requirements exist for building Apache Httpd Version 2.4:
#	APR and APR-Util
#	Perl-Compatible Regular Expressions Library (PCRE)
#       ANSI-C Compiler and Build System(gcc | g++)     
#       Perl 5 [OPTIONAL]
#
#    The following requirements exist for building php
#	yum install libxml2
#	yum install libxml2-devel -y
#
#    The following requirements exist for building mysql 5.6.14 
#	cmake
#	yum -y install ncurses-devel
#


APR_VER='1.5.0'
APR_UTIL_VER='1.5.3'
PCRE_VER='8.33'
APACHE_VER='2.4.6'
PHP_VER='5.5.6'
CMAKE_VER='2.8.3'
MYSQL_VER='5.6.14'

#the LAMP installing dir
LAMP_DIR='/root/web'

#the LAMP Software Pack Dir
packDir='/root/softpack/lamp'

function extract()
{
        if [ -f $1.tar.bz2 ] ;then
                echo "$1.tar.bz2"
                tar -jxf $1.tar.bz2
        elif [ -f $1.tar.gz ] ;then

                echo "$1.tar.gz"
                tar -zxf $1.tar.gz
        elif [ -f $1.zip ] ;then
                echo "$1.zip"                                                                         
                unzip $1.zip                                                                          
        else                                                                                          
                echo -e "\033[31m  $1.tar package is NOT exist!!  \033[0m"                            
                exit 1                                                                                
        fi                                                                                            
}                                                                                                     
                                                                                                      
                                                                                                      
#if exist lamp,the installing script will exit                                                        
if [ -d ${LAMP_DIR}/apr  -o  -d ${LAMP_DIR}/apr-util -o -d ${LAMP_DIR}/pcre \
      -o -d ${LAMP_DIR}/apache -o -d ${LAMP_DIR}/php -o -d ${LAMP_DIR}/cmake -o -d ${LAMP_DIR}/mysql ] ;then
        echo -e "\033[31m  LAMP has been installed in ${LAMP_DIR}! \033[0m"                           
        echo -e "\033[31m  Please remove ${LAMP_DIR} and then excute this script! \033[0m"            
        exit 1                                                                                        
else                                                                                                  
      mkdir ${LAMP_DIR}/apr                                                                           
      mkdir ${LAMP_DIR}/apr-util                                                                      
      mkdir ${LAMP_DIR}/pcre                                                                          
      mkdir ${LAMP_DIR}/apache                                                                        
      mkdir ${LAMP_DIR}/php 
      mkdir ${LAMP_DIR}/cmake
      mkdir ${LAMP_DIR}/mysql                                                                         
fi  

#create installing log 
logDir=$packDir/log-$(date "+%Y%m%d-%H:%M")
mkdir $logDir
touch $logDir/apr.install.log
touch $logDir/apr-util.install.log
touch $logDir/pcre.install.log
touch $logDir/apache.install.log
touch $logDir/php.install.log
touch $logDir/cmake.install.log
touch $logDir/mysql.install.log


echo -e "\033[32m========= Begin Decompress LAMP Software Pack  ==========\033[0m"
extract apr-${APR_VER}
extract apr-util-${APR_UTIL_VER}
extract pcre-${PCRE_VER}
extract httpd-${APACHE_VER}
extract cmake-${CMAKE_VER}
extract mysql-${MYSQL_VER}
extract php-${PHP_VER}
echo -e "\033[32m========= Decompress LAMP Software Pack Finished! ==========\033[0m"


echo -e "\033[32m========= Begin Install Apr ==========\033[0m"
cd $packDir/apr-${APR_VER}
if [ $? != 0 ] ;then
        echo -e "\033[31m  apr-${APR_VER} is NOT exist!!  \033[0m"
        exit 1
fi
echo -e "\033[36m=== Dir:$(pwd) === \033[0m"
./configure --prefix=${LAMP_DIR}/apr >$logDir/apr.install.log 2>&1
make >>$logDir/apr.install.log 2>&1
make install  >>$logDir/apr.install.log 2>&1
echo -e "\033[32m========= Install Apr Successfully! ==========\033[0m"


echo -e "\033[32m========= Begin Install Apr-util ==========\033[0m"
cd $packDir/apr-util-${APR_UTIL_VER}
if [ $? != 0 ] ;then
        echo -e "\033[31m  apr-util-${APR_UTIL_VER} is NOT exist!!  \033[0m"
        exit 1
fi
echo -e "\033[36m=== Dir:$(pwd) === \033[0m"
./configure --prefix=${LAMP_DIR}/apr-util  --with-apr=${LAMP_DIR}/apr  >$logDir/apr-util.install.log 2>&1
make >>$logDir/apr-util.install.log 2>&1
make install  >>$logDir/apr-util.install.log 2>&1
echo -e "\033[32m========= Install Apr-util Successfully! ==========\033[0m"
 
 
echo -e "\033[32m========= Begin Install PCRE ==========\033[0m"
cd $packDir/pcre-${PCRE_VER}
if [ $? != 0 ] ;then
        echo -e "\033[31m  pcre-${PCRE_VER} is NOT exist!!  \033[0m"
        exit 1
fi
echo -e "\033[36m=== Dir:$(pwd) === \033[0m"
./configure --prefix=${LAMP_DIR}/pcre  --with-apr=${LAMP_DIR}/apr  >$logDir/pcre.install.log 2>&1
make >>$logDir/pcre.install.log 2>&1
make install  >>$logDir/pcre.install.log 2>&1
echo -e "\033[32m========= Install PCRE Successfully! ==========\033[0m"


echo -e "\033[32m========= Begin Install Apache ==========\033[0m"
cd $packDir/httpd-${APACHE_VER}
if [ $? != 0 ] ;then
        echo -e "\033[31m  httpd-${APACHE_VER} is NOT exist!!  \033[0m"
        exit 1
fi
echo -e "\033[36m=== Dir:$(pwd)=== \033[0m"
./configure --prefix=${LAMP_DIR}/apache \
		     --with-apr=${LAMP_DIR}/apr \
		     --with-apr-util=${LAMP_DIR}/apr-util \
		     --with-pcre=${LAMP_DIR}/pcre  >$logDir/apache.install.log 2>&1
make >>$logDir/apache.install.log 2>&1
make install  >>$logDir/apache.install.log 2>&1
echo -e "\033[32m========= Install Apache Successfully! ==========\033[0m"



echo -e "\033[32m========= Begin Config Httpdconf ==========\033[0m"
httpdconf=${LAMP_DIR}/apache/conf/httpd.conf
IP=$( ifconfig eth0 | grep 'inet addr' | awk '{print $2}' | cut -d ':' -f 2 )
ServerNameLineNu=$( grep -n 'ServerName www.example.com' $httpdconf | cut -d ':' -f 1)
sed -i "${ServerNameLineNu}a ServerName ${IP}:80"  $httpdconf
DirectoryIndexLineNu=$( grep -n 'DirectoryIndex index.html' $httpdconf | cut -d ':' -f 1)
sed -i "${DirectoryIndexLineNu}c DirectoryIndex index.html index.htm index.php"  $httpdconf
AddTypeLineNu=$( grep -n 'AddType application/x-gzip .gz' $httpdconf | cut -d ':' -f 1 )
sed -i "${AddTypeLineNu}a AddType application/x-httpd-php .php" $httpdconf
echo -e "\033[32m========= Config Httpdconf Successfully! ==========\033[0m"



echo -e "\033[32m========= Begin Install Cmake ==========\033[0m"
cd $packDir/cmake-${CMAKE_VER}
if [ $? != 0 ] ;then
        echo -e "\033[31m  cmake-${CMAKE_VER} is NOT exist!!  \033[0m"
        exit 1
fi
./bootstrap >$logDir/cmake.install.log 2>&1
./configure --prefix=${LAMP_DIR}/cmake  >>$logDir/cmake.install.log 2>&1
make >>$logDir/cmake.install.log 2>&1
make install >>$logDir/cmake.install.log 2>&1
echo -e "\033[32m========= Install Cmake Successfully! ==========\033[0m"


echo -e "\033[32m========= Begin Install Mysql ==========\033[0m"
cd $packDir/mysql-${MYSQL_VER}
if [ $? != 0 ] ;then
        echo -e "\033[31m  mysql-${MYSQL_VER} is NOT exist!!  \033[0m"
        exit 1
fi
echo -e "\033[36m=== Dir:$(pwd) === \033[0m"
${LAMP_DIR}/cmake/bin/cmake -DCMAKE_INSTALL_PREFIX=${LAMP_DIR}/mysql \
			     -DMYSQL_UNIX_ADDR=/tmp/mysql.sock \
			     -DDEFAULT_CHARSET=utf8 \
			     -DDEFAULT_COLLATION=utf8_general_ci \
			     -DWITH_EXTRA_CHARSETS:STRING=all \
			     -DWITH_MYISAM_STORAGE_ENGINE=1 \
			     -DWITH_INNOBASE_STORAGE_ENGINE=1 \
			     -DWITH_READLINE=1 \
			     -DENABLED_LOCAL_INFILE=1 \
			     -DMYSQL_DATADIR=${LAMP_DIR}/mysql/data >$logDir/mysql.install.log 2>&1

make >>$logDir/mysql.install.log 2>&1
make install  >>$logDir/mysql.install.log 2>&1
echo -e "\033[32m========= Install Mysql Successfully! ==========\033[0m"



echo -e "\033[32m========= Begin Config Mysql ==========\033[0m"
groupadd mysql
useradd -r -g mysql mysql
chown -R mysql:mysql ${LAMP_DIR}/mysql/
cp ${LAMP_DIR}/mysql/support-files/my-default.cnf /etc/my.cnf
sed -i "\$i basedir = ${LAMP_DIR}/mysql" /etc/my.cnf
sed -i "\$i datadir = ${LAMP_DIR}/mysql/data" /etc/my.cnf
sed -i "\$i port = 3306" /etc/my.cnf
cp ${LAMP_DIR}/mysql/support-files/mysql.server /etc/rc.d/init.d/mysqld
${LAMP_DIR}/mysql/scripts/mysql_install_db --user=mysql \
      --basedir=${LAMP_DIR}/mysql \
      --datadir=${LAMP_DIR}/mysql/data \
      --defaults-file=/etc/my.cnf >>$logDir/mysql.install.log 2>&1
chkconfig --add mysqld
chkconfig --level 345 mysqld on
echo -e "\033[32m========= Config Mysql Successfully! ==========\033[0m"



echo -e "\033[32m========= Begin Install Php  ==========\033[0m"
cd $packDir/php-${PHP_VER}
if [ $? != 0 ] ;then
        echo -e "\033[31m  php-${PHP_VER} is NOT exist!!  \033[0m"
        exit 1
fi
echo -e "\033[36m=== Dir:$(pwd) === \033[0m"
./configure --prefix=${LAMP_DIR}/php \
		     --with-config-file-path=${LAMP_DIR}/php/etc \
		     --with-apxs2=${LAMP_DIR}/apache/bin/apxs \
		     --with-mysql=${LAMP_DIR}/mysql \
		     --with-mysqli=${LAMP_DIR}/mysql/bin/mysql_config >$logDir/php.install.log 2>&1
make clean >>$logDir/php.install.log 2>&1
make >>$logDir/php.install.log 2>&1
make install  >>$logDir/php.install.log 2>&1
cp $packDir/php-${PHP_VER}/php.ini-development ${LAMP_DIR}/php/etc/php.ini
cp ${LAMP_DIR}/php/etc/php.ini  ${LAMP_DIR}/php/etc/php.ini.bak

echo -e "\033[32m========= Install Php Successfully! ==========\033[0m"


echo -e "\033[32m========= Begin Config Php.ini ==========\033[0m"
phpini=${LAMP_DIR}/php/etc/php.ini
ExtensionDirLineNu=$( grep -n '; extension_dir = "./"' $phpini | cut -d ':' -f 1)
sed -i "${ExtensionDirLineNu}a extension_dir = \"${LAMP_DIR}/php/lib/php/extensions/no-debug-non-zts-20121212/\""  $phpini
DateTimeZoneLineNu=$( grep -n ';date.timezone =' $phpini | cut -d ':' -f 1)
sed -i "${DateTimeZoneLineNu}a date.timezone = Asia/Shanghai"  $phpini
ShortOpenTagLineNu=$( grep -n 'short_open_tag = Off' $phpini | cut -d ':' -f 1)
sed -i "${ShortOpenTagLineNu}c short_open_tag = On"  $phpini
echo -e "\033[32m========= Config Php.ini Successfully! ==========\033[0m"


echo -e "\033[32m========= Add Man to /etc/man.config ==========\033[0m"
sed -i "1i  MANPATH ${LAMP_DIR}/apache/man" /etc/man.config
sed -i "1i  MANPATH ${LAMP_DIR}/mysql/man" /etc/man.config
sed -i "1i  MANPATH ${LAMP_DIR}/php/man" /etc/man.config
sed -i "1i  MANPATH ${LAMP_DIR}/camke/man" /etc/man.config
echo -e "\033[32m========= Add PATH to ~/.bash_profile ==========\033[0m"
sed -i "1i PATH=\$PATH:${LAMP_DIR}/apache/bin:${LAMP_DIR}/mysql/bin:${LAMP_DIR}/php/bin:${LAMP_DIR}/cmake/bin" ~/.bash_profile
source ~/.bash_profile
echo -e "\033[32m========= Install LAMP Successfully! ==========\033[0m"
exit 0

