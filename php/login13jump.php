<html>
<body>
<script type="text/javascript">
function noNumbers(e)
{
var keynum;
var keychar;
var numcheck;

if(window.event) // IE
  {
  keynum = e.keyCode;
  }
else if(e.which) // Netscape/Firefox/Opera
  {
  keynum = e.which;
  }

keychar = String.fromCharCode(keynum);
alert(keynum);
//numcheck = /\d/;
//return !numcheck.test(keychar);
}
</script>
<input type="text" onkeydown="noNumbers(event)" />
<form>

</form>

</html>