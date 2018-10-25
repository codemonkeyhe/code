Video = (function() {
    /*
     hashchange后调用的方法，主要负责显示和隐藏DOM元素，然后拉取数据显示页面
     @author:kevenfeng
     @date:2013-03-14
     */
    var oldPageName = "";
    //记录用户进入详情页前的状态信息
    var userInfo = {};
    var debugInfoElement = null;

    //请求路由函数，用于负责APP整体请求的处理
    var onhashChange = function() {
        var hashObj = Video.getNavObj();
        //判断P参数是否合法
        var isValidPage = false;

        //如果没有任何hash值，则使用默认的
        if (location.hash == "") {
            location.hash = "#p=index&g=" + CONF.defaultGroupId;
            return;
        }

        //判断页面是否启动
        for (var x in CONF.TOGA) {
            if (CONF.TOGA.hasOwnProperty(x) && CONF.TOGA[x] === true && x === hashObj.p) {
                isValidPage = true;
                break;
            }
        }

        if (isValidPage === false) {
            location.hash = "#p=index&g=" + CONF.defaultGroupId;
            return;
        }

        if (hashObj.p === "index") {
            var groupInfoLocal = com.Bll.getGroupInfo(hashObj.g, true);

            //如果hash中的p为首页且g不属于任何一个合法的频道页
            if ($.isNullOrEmpty(groupInfoLocal) || groupInfoLocal.hasChannel == false) {
                //查找出正确的频道编号并构造出新的地址并继续跳转
                var smartGroupId = com.Bll.getFitGroupId(hashObj.g);
                hashObj.g = smartGroupId;
                location.hash = Video.buildNavObj(hashObj);
                return;
            }
        }

        var pageName = hashObj.p;
        var groupId = Video.getNavObj().g;

        try {
            //显示内容
            Page[pageName].show();

            if (oldPageName == "") {
                oldPageName = "index";
            } else {
                if (oldPageName !== pageName) {
                    Page[oldPageName].hide();
                }
            }

            if (com.Bll.getscrollYIndicator() != - 1) {
                window.scrollTo(0, com.Bll.getscrollYIndicator());
            }

            oldPageName = pageName;

            showDebugInfo();

            document.title = com.Bll.getPageTitle();

        } catch(ex) {
            $.jsRuntimeError(ex, "Page Show Faild " + String.format("newPage:{0} oldPage:{1}", pageName, oldPageName));
        }
    };

    var originalAlert = alert;
    alert = function(content) {
        if (CONF.debugMode.alert === true) {
            originalAlert.call(this, content);
        }
    };

    var showDebugInfo = function() {
        var requestObj = Video.getRequestObj();
        //如果在地址中携带调试信息，则显示
        var debugInfo = $.E("debugInfo");
        if (requestObj.debug === "1") {
            $.removeClass(debugInfo, "none");
            var debugInfoHTML = "";
            for (var x in window.navigatorInfo) {
                debugInfoHTML += String.format("<p><b style=\"font-weight:bold;\">{0}</b>: {1}</p>", x, window.navigatorInfo[x]);
            }

            if (window.jsStamp) {
                for (var x in window.jsStamp) {
                    debugInfoHTML += "<p>" + x + "&nbsp;" + window.jsStamp[x] + "</p>";
                }
            }
            var divs = debugInfo.querySelectorAll("div");

            divs[0].innerHTML = debugInfoHTML;
        } else {
            $.addClass(debugInfo, "none");
        }
    }

    //专区内部记录用户路径
    var modifyUserInfo = function(type, position, indexGroup) {
        userInfo.type = type;
        userInfo.position = position;
        userInfo.indexGroup = indexGroup;

        return buildUserInfo(oldPageName);
    };

    //专区内部进入详情页记录用户路径
    var buildUserInfo = function(oldPageName) {
        var pageType;

        if (typeof userInfo.type == "undefined") userInfo.type = 0;

        if (typeof userInfo.position == "undefined") userInfo.position = 0;

        var channel = Video.getRequestObj().ch || Video.getNavObj().ch || "";

        //专区内首页banner
        if (userInfo.type == "enterToBanner") {
            var bannerId = userInfo.position ? userInfo.position: 0;
            var vType = userInfo.indexGroup ? userInfo.indexGroup: 0;
            pageType = "&ref=" + "banner" + "_" + bannerId + "_" + vType + "_" + channel;
            return pageType;
        }

        //专区内首页非banner、分类TAB、个人中心、搜索结果页
        if (oldPageName == "index" && userInfo.type == 1) {
            userInfo.indexGroup = userInfo.indexGroup ? userInfo.indexGroup: 0;
            pageType = "index" + "_" + userInfo.indexGroup;
        }
        else if (oldPageName == "index") {
            pageType = "group" + "_" + userInfo.indexGroup;
        }
        else if (userInfo.type == "saved") {
            pageType = "saved" + "_" + userInfo.indexGroup;
        }
        else {
            pageType = oldPageName + "_" + userInfo.indexGroup;
        }
        return "&ref=" + pageType + "_" + userInfo.position + "_" + channel;
    }

    //专区外部根据渠道号记录用户路径
    var buildUserInfoBaseCh = function() {
        var channel = Video.getRequestObj().ch || Video.getNavObj().ch || "";
        if (channel != "") {
            //专区外视频位置等信息，可拓展
            var para = Video.getNavObj().para ? Video.getNavObj().para: "";
            return "out_" + para + "_" + channel;
        }
        return "inValidChanel";
    }

    /*
     解析url上面的Hash参数
     @author:kevenfeng
     @date:2013-03-14
     */
    var getNavObj = function() {
        var hash = location.hash.split("?")[0];
        if (hash === '') {
            return {};
        } else {
            return buildObj(hash);
        }
    };

    var buildObj = function(obj) {
        if (obj[0] === "#") {
            obj = obj.substr(1);
        }

        var buffer = obj.split("&");
        var navObj = {};

        for (var i = 0; i < buffer.length; i++) {
            if ($.isNullOrEmpty(buffer[i])) continue;

            var block = buffer[i].split("=");
            if (block.length == 2) {
                navObj[block[0]] = block[1];
            } else if (block.length == 1) {
                navObj[block[0]] = "";
            }
        }

        return navObj;
    }

    //将一个指定的navObj拼装成hash字符串
    var buildNavObj = function(navObj) {
        var newNav = "";
        for (var x in navObj) {
            if (navObj.hasOwnProperty(x)) {
                newNav += (x + "=" + navObj[x] + "&");
            }
        }

        if (newNav.length > 0) newNav = "#" + newNav.substr(0, newNav.length - 1);

        return newNav;
    }

    /*
    解释url上面的Request参数
    */
    var getRequestObj = function() {
        var url = location.search; //获取url中"?"符后的字串,至#截止
        var theRequest = {};
        if (url.indexOf("?") != - 1) {
            var str = url.substr(1);
            strs = str.split("&");
            for (var i = 0; i < strs.length; i++) {
                theRequest[strs[i].split("=")[0]] = unescape(strs[i].split("=")[1]);
            }
        }
        return theRequest;
    }

    var count = 0;
    var checkResourceValid = function() {
        console.log("checkResourceValid...");
        //根模块检查
        if (typeof com === "undefined") {
            return false;
        }
        //基础模块检查
        if (typeof com.Dal === "undefined") {
            return false;
        }
        if (typeof com.Bll === "undefined") {
            return false;
        }
        if (typeof com.Vis === "undefined") {
            return false;
        }
        //应用模块检查
        if (typeof com.Bll.hideTimeout === "undefined") {
            return false;
        }
        if (typeof com.Vis.createPlaySource === "undefined") {
            return false;
        }
        if (typeof com.Vis.createBackToTop === "undefined") {
            return false;
        }
        //插件模块检查
        if (typeof Slide === "undefined") {
            return false;
        }

        return true;
    }

    //页面进入首先执行的函数
    var start = function() {
        try {
            if (checkResourceValid() === false) {
                setTimeout(arguments.callee, 500);
                return;
            }

            com.Bll.getNavigatorInfo();

            window.addEventListener("popstate", com.Bll.onPopState);
            window.addEventListener('hashchange', onhashChange);

            if (location.hash == "") {
                location.hash = "#p=index&g=" + CONF.defaultGroupId;
            } else {
                onhashChange();
            }

            //此处使用replaceState用于记忆推荐页的跳转位置
            var stateObj = {
                jumpIndex: 0,
                to: location.hash,
                action: "forward",
                scrollY: 0,
                circleJump: false
            };

            //此处必须使用replaceState用于防止之前的hash改变造成的重复历史插入
            //部分ROM并不支持此方法，故在使用之前需要进行判断
            if (history.replaceState) history.replaceState(stateObj, "", location.hash);

            if (debugInfoElement === null) debugInfoElement = $.E("debugInfo");

            //清理所有详情页的localStorage
            //这个是用于对应之前详情页的缺陷
            for (var i = localStorage.length - 1; i >= 0; i--) {
                var key = localStorage.key(i)
                if (Number(key) > 0) {
                    console.log("cleanning Key :" + key);
                    localStorage.removeItem(key);
                }
            }

            //如果是Android，且版本号为4.5，且未对用户弹出过授权框，则在此处不做testTokenPush检查
            //以免在4.5下意外的弹出了授权框
            if (! (navigatorInfo.isAndroidQb && window.x5.getQQBrowerVer() == 45 && ! com.Dal.isAndroid45Authorized())) {
                com.Bll.testTokenPush();
            }
            com.Bll.mergeFavData();

            com.Vis.createBackToTop();
        } catch(ex) {
            $.jsRuntimeError(ex, 'APP启动失败');
        }
    }
    $.breakPoint();
    debugger;
    return {
        start: start,
        getNavObj: getNavObj,
        getRequestObj: getRequestObj,
        modifyUserInfo: modifyUserInfo,
        buildObj: buildObj,
        buildNavObj: buildNavObj,
        buildUserInfoBaseCh: buildUserInfoBaseCh,
        onhashChange: onhashChange
    }
} ());

