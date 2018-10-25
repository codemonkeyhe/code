# _*_ coding:utf-8 _*_

import re 
import urllib

print("hello");

def ChangeCoding(s):
    ''' 处理中文文件名的编码 '''
    #pattern=re.compile(r'^".*?((\\\d\d\d){3,})(/(?P<s>(\\\d\d\d){3,}))*.+"$')
    #match=pattern.match(a)
    p=re.compile(r'(?P<s>(\\\d\d\d){3,})')
    for i in p.finditer(s):
        old=i.group('s')
        name=old.split('\\')
        name=['%x' %int(g,8) for g in name if g.isdigit() ]
        name='%'+'%'.join(name)
        CN_name= urllib.unquote(name).decode('utf-8')
        s = s.replace(old,CN_name)
    print s.strip('"')



ss="\000\000\000\000\000\000\000\000\224\274a蘼a\350\000\000\000\000\000,a\350\200\000\000\000\271\354v\b\000\000\000\000\071\060\060_1350091900_1850GT\375\261\b\032\225d\247\372\000\000\350\310\000`\350\000\000\000\000\000\000\000\000\320L`\350\001\000\000\000\000\000\000\000\330\346\377\350\001dnt\000\000\000\000\060\000\000\000\064\000\000\000\320\065`\350\250\346"
ChangeCoding(ss)

#ss='"\\346\\226\\260\\345\\273\\272\\346\\226\\207\\344\\273\\266\\345\\244\\271/\\345\\226\\260\\345\\273\\272\\346\\226\\207\\344\\273\\266\\345\\244\\271/\\346\\226\\260\\345\\273\\272\\346\\226\\207\\346\\234\\254\\346\\226\\207\\346\\241\\243.txt"'
#ss="\\345\\245\\275"
#ss="\345\245\275"
#ss="\345\250\261\344\271\220/\351\237\263\351\242\221\344\270\212\350\241\214\351\211\264\346\235\203/auth_audio_route/\345\244\261\350\264\245/\345\216\237\345\233\240-F_USER_LEAVE(\347\246\273\345\274\200\351\242\221\351\201\223)"
#ss="\346\257\224\344\270\212\346\254\241\346\267\267\347\224\273\347\211\210\346\234\254\345\217\267\345\260\217"



