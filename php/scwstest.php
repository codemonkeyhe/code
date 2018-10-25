<?php


//zoro
function ch_word_segment1($text) {  
    $so = scws_new();        //创建并返回一个SimpledCWS类操作对象  
    $so->set_charset('utf8');       //设定分词词典、规则集、欲分文本字符串的字符集  
	//$so->set_charset('gbk');       //设定分词词典、规则集、欲分文本字符串的字符集  
    $so->set_multi(SCWS_MULTI_SHORT | SCWS_MULTI_DUALITY);    //设定分词返回结果时是否复式分割，这里设定短词和二元词  
	$so->set_rule('d:/wamp/scws/etc/rules.utf8.ini');
	$so->set_dict('d:/wamp/scws/etc/dict.utf8.xdb');
	//$so->set_rule('d:/wamp/scws/etc/rules.ini');
	//$so->set_dict('d:/wamp/scws/etc/dict.xdb');
    $so->send_text($text);    //发送要分词的文本
    $first = true;
	$word="";
	while ($res = $so->get_result()) {
        foreach ($res as $tmp) {
            if ($tmp['len'] == 1 && $tmp['word'] == "\r")
                continue;
            if ($tmp['len'] == 1 && $tmp['word'] == "\n")
                $word .= unicode_encode($tmp['word']);
				//$word .= $tmp['word'];
            else
                $word .= unicode_encode($tmp['word']) . " ";
				//$word .= $tmp['word'] . " ";
        }
    }
	return $word;
}

function unicode_encode($word) {  
	$word=iconv('UTF-8','UCS-2LE',$word); //编码转换，假设PHP默认编码为UTF-8，将UTF-8转换为UCS-2LE  
	$len=strlen($word);
	$code="";
	for($i=0;$i<$len-1;$i=$i+2) { //UCS-2LE编码是一个汉字占用两个字节  
		$ch1=$word[$i];       //获取第一个字节的ASCII字符      
		$ch2=$word[$i+1];     //获取第二个字节的ASCII字符  
		$code.=base_convert(ord($ch2),10,16);
		$code.=base_convert(ord($ch1),10,16); //获取字符的ASCII码，再转换为十六进制  
	}
	return $code;  
} 

function str_replace_once($needle, $replace, $haystack) {
	//函数作用，只替换一个字符
	//$needle --- 需要替换的字符
	//$replace --- 替换成什么字符
	//$haystack --- 需要操作的字符串
	$pos = strpos($haystack, $needle);
	if ($pos === false) {
		return $haystack;
	}
	return substr_replace($haystack, $replace, $pos, strlen($needle));
}

function ch_word_segment($text) {  
        $so = scws_new();        
        $so->set_charset('utf8');       
        $so->set_multi(SCWS_MULTI_SHORT | SCWS_MULTI_DUALITY);    
		//$so->set_rule('d:/wamp/scws/etc/rules.ini');
		//$so->set_dict('d:/wamp/scws/etc/dict.xdb');
		$so->set_rule('d:/wamp/scws/etc/rules.utf8.ini');
		$so->set_dict('d:/wamp/scws/etc/dict.utf8.xdb');
        $so->send_text($text);    
       // $result = $so->get_result();  
        $first = true;  
		$word="";
		while ($result = $so->get_result()) {
			foreach ($result as $key => $value) {  
				if ($first) {
					$word.=$value['word'];  
					$first = false;  
				} else {  
					$word.=' ' . $value['word'];  
				}  
			}  
		}
        return $word;  
}

function html_2_string($html) {
	$html = strip_tags($html);		//去掉 HTML 及 PHP 的标记
	$html = str_replace("\r\n"," ",$html);		//去掉换行符
	$html = str_replace("\n"," ",$html);		//去掉换行符
	$html = str_replace("&nbsp;"," ",$html);		//替换html的转义字符
	$html = str_replace("&lt;","<",$html);
	$html = str_replace("&gt;",">",$html);
	$html = str_replace("&amp;","&",$html);
	$html = str_replace("&quot;","\"",$html);
	$html = str_replace("&apos;","'",$html);
	$html = str_replace("&cent;","￠",$html);
	$html = str_replace("&pound;","£",$html);
	$html = str_replace("&yen;","¥",$html);
	$html = str_replace("&euro;","€",$html);
	$html = str_replace("&sect;","§",$html);
	$html = str_replace("&copy;","©",$html);
	$html = str_replace("&reg;","®",$html);
	$html = str_replace("&trade;","™",$html);
	$html = str_replace("&times;","×",$html);
	$html = str_replace("&divide;","÷",$html);
	return $html;
}


$so = scws_new();
$so->set_charset('utf8');

$so->send_text("我是一个中国人, hello world! 精通C++");
while ($tmp = $so->get_result())
{
  print_r($tmp);
}
$so->close();

echo "<h1>他人的</h1>";
print(ch_word_segment('高新诚聘Hello World! 注册造价工程师'));
echo "<br></br>";
echo "<h1>Zoro</h1>";
print(ch_word_segment1('高薪诚聘Hello World! 注册造价工程师'));
echo "<br></br>";
echo "<h1>Zoro1</h1>";
print(ch_word_segment1('+ - * ( ) < > \ " “ '));
echo "<br></br>";
echo "<h1>Zoro2</h1>";
$str=ch_word_segment1('"+apple" +(>banana <orange)');
echo "<br></br>";

		$str = str_replace("02b ","+",$str);
		$str = str_replace("02d ","-",$str);
		$str = str_replace("02a ","*",$str);
		$str = str_replace("028 ","(",$str);
		$str = str_replace(" 029",")",$str);
		$str = str_replace("03c ","<",$str);
		$str = str_replace("03e ",">",$str);
		for ($i=substr_count($str,"022");$i>0;$i-=2) {
			$str = str_replace_once("022 ","\"",$str);
			$str = str_replace_once(" 022","\"",$str);
		}
print($str);
echo "<br></br>";


?>

<?php 
 
echo "<br></br>";
$text='<p><a href="http://localhost/MCISP/data/upload/file/1364381565.doc">doc下砸</a></p>';
$text1='<p><object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,40,0" height="400" width="600"><param name="quality" value="high" /><param name="movie" value="http://localhost/MCISP/data/upload/flash/1364379158.swf" /><embed height="400" pluginspage="http://www.macromedia.com/go/getflashplayer" quality="high" src="http://localhost/MCISP/data/upload/flash/1364379158.swf" type="application/x-shockwave-flash" width="600"></embed></object></p>
';
//echo $text1;
echo html_2_string($text); 
echo "<br></br>";
echo ch_word_segment1(html_2_string($text)); 

echo "<br></br>";
$new = html_2_string("<a href='test'>Test</a>&lt;");  
echo $new; 
echo "<br></br>";
$new =ch_word_segment1("歧关车发车时刻表");  
echo $new; 
?> 

