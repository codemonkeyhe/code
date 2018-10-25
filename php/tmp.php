<?php
//这道题其实就是二维数组的遍历与统计，本人PHP连详细语法都没看过，熟悉C++多点
//array_key_exists这个函数如果不给用的话，那再加多一个for循环判断键值
$i=1;
$arrs=array(array('a','b','c','d','e','f','g','h'),array('ad','ad','ed','s','e','h','d'),array('k','y','re','g')); //输入数据：存放数组元素的数组，元素为N个数组
$res=array();  //输出数据：存放统计后的每个元素的个数，键为元素，值为元素的个数
foreach($arrs as $ar){
	foreach($ar as $a){
		if(array_key_exists($a,$res))
			$res[$a]++;
		else
			$res[$a]=1;
	}
}
print_r($res)

?>
