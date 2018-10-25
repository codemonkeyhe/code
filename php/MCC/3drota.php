
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>

<title>Rotate3Di Nav List Demo</title>



<style type="text/css" media="screen">


h2 a {
    display: block;
    padding: 48px 0;
}

p a {
    display: block;
    padding: 36px 24px;
}

#nav-list-example {
    height: 132px;
    width: 624px;
    margin: 48px 0;
}

#nav-list-example li {
    width: 132px;
    height: 132px;
    float: left;
    margin-right: 24px;
    position: relative;
}

#nav-list-example li div {
    width: 132px;
    height: 132px;
    overflow: hidden;
    background: white;
    position: absolute;
    top: 0;
    left: 0;
}

#nav-list-example li div.back {
    left: -999em;
    background: #999;
}
</style>

<script type="text/javascript" src="./jquery-1.8.3.min.js"></script>
<script type="text/javascript" src="./rotate3di.js"></script>

<script type="text/javascript" language="javascript" charset="utf-8">
$(document).ready(function () {
    $('#nav-list-example li div.back').hide().css('left', 0);
    
    function mySideChange(front) {
        if (front) {
            $(this).parent().find('div.front').show();
            $(this).parent().find('div.back').hide();
            
        } else {
            $(this).parent().find('div.front').hide();
            $(this).parent().find('div.back').show();
        }
    }
    
    $('#nav-list-example li').hover(
        function () {
            $(this).find('div').stop().rotate3Di('flip', 250, {direction: 'clockwise', sideChange: mySideChange});
        },
        function () {
            $(this).find('div').stop().rotate3Di('unflip', 500, {sideChange: mySideChange});
        }
    );
});
</script>

</head>
<body>

<div id="nav-list-example">
    <li>
        <div class="front"><h2><a href="#">Apple</a></h2></div>
        <div class="back"><a href="#">Apples are a round fruit.</a></div>
    </li>
    <li>
        <div class="front"><h2><a href="#">Banana</a></h2></div>
        <div class="back"><p><a href="#">Bananas are a yellow fruit.</a></p></div>
    </li>
    <li>
        <div class="front"><h2><a href="#">Cherry</a></h2></div>
        <div class="back"><p><a href="#">Cherries are a delicious fruit.</a></p></div>
    </li>
    <li>
        <div class="front"><h2><a href="#">Durian</a></h2></div>
        <div class="back"><p><a href="#">Durians are a stinky fruit.</a></p></div>
    </li>
	<li>
        <div class="front"><h2><a href="#">Apple</a></h2></div>
        <div class="back"><a href="#">Apples are a round fruit.</a></div>
    </li>
    <li>
        <div class="front"><h2><a href="#">Banana</a></h2></div>
        <div class="back"><p><a href="#">Bananas are a yellow fruit.</a></p></div>
    </li>
    <li>
        <div class="front"><h2><a href="#">Cherry</a></h2></div>
        <div class="back"><p><a href="#">Cherries are a delicious fruit.</a></p></div>
    </li>
    <li>
        <div class="front"><h2><a href="#">Durian</a></h2></div>
        <div class="back"><p><a href="#">Durians are a stinky fruit.</a></p></div>
    </li>
	<li>
        <div class="front"><h2><a href="#">Apple</a></h2></div>
        <div class="back"><a href="#">Apples are a round fruit.</a></div>
    </li>
    <li>
        <div class="front"><h2><a href="#">Banana</a></h2></div>
        <div class="back"><p><a href="#">Bananas are a yellow fruit.</a></p></div>
    </li>
    <li>
        <div class="front"><h2><a href="#">Cherry</a></h2></div>
        <div class="back"><p><a href="#">Cherries are a delicious fruit.</a></p></div>
    </li>
    <li>
        <div class="front"><h2><a href="#">Durian</a></h2></div>
        <div class="back"><p><a href="#">Durians are a stinky fruit.</a></p></div>
    </li>
</div>

</body>
</html>
