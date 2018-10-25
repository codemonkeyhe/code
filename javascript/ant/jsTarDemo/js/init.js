//将指定的错误信息记入localStorage中方便发送
    function saveLoadErr(ex, logMsg) {
        var cJson = localStorage.getItem("jException") || "";
        var exceptions = null;
        var logUrl = ex.srcElement.href || ex.srcElement.src;

        if (cJson && cJson.length > 0)
            exceptions = JSON.parse(cJson);

        if (exceptions == null || typeof exceptions.sJException == "undefined") {
            exceptions = {
                sJException: []
            };
        }

        var newException = {};

        newException.args = [];
        newException.callStack = "";
        newException.errorMessage = "";
        newException.hash = window.location.hash;
        newException.host = window.location.host;
        newException.timeStamp = new Date().toString();
        newException.type = logMsg;

        if (logUrl) {
            newException.args.push(logUrl);
        }

        exceptions.sJException.push(newException);

        console.log(newException);

        localStorage.setItem("jException", JSON.stringify(exceptions));
    }
    
    // //for test
    // var tfCallBack = function(data) {
    // };

    //初始化热力图
    function heatMap() {
        var reportUrl = 'http://statistics.html5.qq.com/click';

        var businessName = 'hotVideo_Phone';

        var getBusinessKeyFromUrl = function() {
            var key = "";
            var domIds = ["index", "detail", "history", "innerSearch", "feedBack", "statement"];

            for (var i = 0, j = domIds.length; i < j; i++) {
                var element = $.E(domIds[i]);
                if (element && !$.hasClass(element, "none")) {
                    key = domIds[i];
                    break;
                }
            }

            if (key == "index") {
                var indexNav = $.E("indexNav");
                var currentElement = indexNav.querySelector(".current");
                if (currentElement) {
                    key += ("_" + $.getDomData(currentElement,'groupid'));
                }
            } else if (key == "innerSearch") {
                var scrollContent = $.E("innerSearchScrollContent");
                if (scrollContent && !$.hasClass(scrollContent, "none")) {
                    key += "_Result";
                }
            }

            return key;
        }

        if (window.HeatmapReport) {
            HeatmapReport.init({
                url: reportUrl,
                businessName: businessName,
                onProcessUrl: getBusinessKeyFromUrl
            });
        }
    }

    function allLoaded() {
        if (typeof Video != "undefined" || window.swiperReady !== true) {
            if (typeof(Page.index) == "undefined" ||
                typeof(Page.detail) == "undefined" ||
                typeof(Page.innerSearch) == "undefined" ||
                typeof(Page.history) == "undefined" ||
                typeof(Page.night) == "undefined") {
                return false;
            }

            return true;
        } else {
            return false;
        }
    }

    function startApp() {
        heatMap();

        //如果加载成功，则开始执行
        (function() {
            if (allLoaded()) {
                //添加数据缓存需求
                window.Cube.ajax.addCacheRequest(CONF.ajaxUrl + "?action=getStartPage", 2000);

                window.Cube.ajax.addCacheRequest(CONF.ajaxUrl + "?action=getHotWords", 2000);

                //显示出页面
                document.body.style.display = "block";

                Video.start();
                //上传上一次积累的异常
                $.uploadExceptionFromLocalStorage();
            } else {
                setTimeout(arguments.callee, 1000);
            }
        }());
        breakPoint
    }
    $.breakPoint()
    debugger;
    window.onload = startApp;
    $.breakPoint();


