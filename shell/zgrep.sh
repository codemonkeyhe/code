#!/bin/sh
if [ $# -ne 1 ];
    then echo "Invalid input, please input 1 arguments: order_id"
        exit 1
fi
orderid="$1"
#grep "${orderid}" /data/yy/log/gua_wallet_d/gua_wallet_d.log; zgrep "${orderid}" /data/yy/log/gua_wallet_d/gua_wallet_d.log.*.gz;
ssh -p 32200 221.228.89.250 "zgrep ${orderid} /data/yy/log/gua_wallet_d/gua_wallet_d.log.*.gz;      zgrep "${orderid}" /data/yy/log/gua_wallet_d/gua_wallet_d.log.*.gz"   
ssh -p 32200 221.228.89.251 "zgrep ${orderid} /data/yy/log/gua_wallet_d/gua_wallet_d.log.*.gz; zgrep "${orderid}" /data/yy/log/gua_wallet_d/gua_wallet_d.log.*.gz"
ssh -p 32200 113.107.237.67 "zgrep ${orderid} /data/yy/log/gua_wallet_d/gua_wallet_d.log.*.gz; zgrep "${orderid}" /data/yy/log/gua_wallet_d/gua_wallet_d.log.*.gz"
ssh -p 32200 113.107.237.68 "zgrep ${orderid} /data/yy/log/gua_wallet_d/gua_wallet_d.log.*.gz; zgrep "${orderid}" /data/yy/log/gua_wallet_d/gua_wallet_d.log.*.gz"
ssh -p 32200 221.228.89.251 "zgrep ${orderid} /data/yy/log/gua_withdraw_d/gua_withdraw_d.log.*.gz; zgrep "${orderid}" /data/yy/log/gua_withdraw_d/gua_withdraw_d.log.*.gz"


 zgrep '_onClientMajorRegisterReqV2'  /data/yy/log/stream_manager_s.t772062.0503.r/stream_manager_s.t772062.0503.r.log.8.gz 
 zgrep '_onClientMajorRegisterReqV2'  /data/yy/log/stream_manager_s.t772062.0503.r/stream_manager_s.t772062.0503.r.log.8.gz  | grep "{ret: 1}" | head -n 2
 zgrep '_onClientMajorRegisterReqV2'  /data/yy/log/stream_manager_s.t772062.0503.r/stream_manager_s.t772062.0503.r.log.8.gz  | grep "{ret: 1}" | awk -F ',' '{print $3}' |  awk '{print $2}'  |  sort | uniq | wc -l 
 head -n 2
 
ssh -p 32200 221.228.89.241  "zgrep 'instreammanager.cpp:474'  /data/yy/log/stream_manager_s.t772062.0503.r/stream_manager_s.t772062.0503.r.log.8.gz | head -n 2   " 

grep "_RegisterStreamInfos" err |  awk -F ',' '{print $3}' | awk '{print $2}' | head -n 2 
grep "SetStreamSnapshot" err |  awk -F ',' '{print $4}' | awk '{print $2}' | sort | uniq | wc -l
 

