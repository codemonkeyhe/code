<?php
//�������ʵ���Ƕ�ά����ı�����ͳ�ƣ�����PHP����ϸ�﷨��û��������ϤC++���
//array_key_exists���������������õĻ������ټӶ�һ��forѭ���жϼ�ֵ
$i=1;
$arrs=array(array('a','b','c','d','e','f','g','h'),array('ad','ad','ed','s','e','h','d'),array('k','y','re','g')); //�������ݣ��������Ԫ�ص����飬Ԫ��ΪN������
$res=array();  //������ݣ����ͳ�ƺ��ÿ��Ԫ�صĸ�������ΪԪ�أ�ֵΪԪ�صĸ���
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
