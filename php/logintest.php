    <html>  
        <head>  
 
        </head>  
        <body> 
		<form>
		<tr>
            <td><input name="textfield2" type="text" class="wenbenkuang"  style="height:23px;	border:#CCCCCC 1px solid;
	width:100px;
	margin:0px 0px 0px 0px;
	color:#CCCCCC;
	font-size:11px;"> </td>
            <td><input type="password"   name="image"  style="height:23px;border:#CCCCCC 1px solid;
			width:100px;
	margin:0px 0px 0px 0px;
	color:#CCCCCC;
	font-size:11px;" ></td>
          </tr></form>
		
<h1 align="center"><font size="5">�û���Ϣ����ϵͳ</font></h1>
    <form name="f1" id="f1" action="" method="post" >
      <table border="1"  align="center">
        <tr >
          <td>�û���</td>
          <td><input type="text" name="login" id="login" style="width:150px"></td>
        </tr>
        <tr >
          <td>���룺</td>
          <td><input type="password" name="password" id="password" style="width:150px"></td>
        </tr> 
        <tr>
           <td colspan="2" align="center"><input type="submit" value="��¼" >&nbsp&nbsp&nbsp&nbsp<input type="reset" value="ȡ��"></td>  
        </tr>
        <tr >
        <td align="center" colspan="2"><a href="register.jsp">�û�ע��</a></td>
        </tr>
      </table>

    </form>

		
<input name="" type="text" value="����" class="inputText_1" id="tx" style="width:100px;"  />
<input name="" type="password" style="display:none;width:100px;" id="pwd" />
            <script type="text/javascript">  
			   var tx = document.getElementById("tx"), pwd = document.getElementById("pwd");
			tx.onfocus = function(){
				if(this.value != "����") 
				return;
				this.style.display = "none";
				pwd.style.display = "";
				pwd.value = "";
				pwd.focus();
			}
			pwd.onblur = function(){
				if(this.value != "") return;
				this.style.display = "none";
				tx.style.display = "";
				tx.value = "����";
			}
	
	// onfocus="passwordFocus()"  onblur="passwordBlur()"
	
    </script> 
        </body>  
    </html>  

<?php 
	// echo "Hello,world!!";
	
	// echo md5("Hello,world!!");
	// $val=10;
	// $res=SetZero($val,1);
	// echo $res;
	// echo '</br>';
	// echo $val;


		


?>


