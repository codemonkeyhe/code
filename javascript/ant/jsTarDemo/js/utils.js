(function() {
    var $ = {};

    $.E = function(s) {
        return document.getElementById(s);
    };

    $.Q = function(s) {
        return document.querySelector(s);
    };

    $.each = function(arr, func) {
        Array.prototype.forEach.call(arr, func);
    };

    function tmpl(str, data) {
        if (!tmpl.cache) {
            tmpl.cache = {};
        }
        var cache = tmpl.cache;
        var fn = ! /\W/.test(str) ? cache[str] = cache[str] || tmpl(document.getElementById(str).innerHTML) : new Function("obj", "var p=[];" + "with(obj){try{p.push('" + str.replace(/[\r\t\n]/g, " ").replace(/'(?=[^%]*%>)/g, "\t").split("'").join("\\'").split("\t").join("'").replace(/<%=(.+?)%>/g, "',$1,'").split("<%").join("');").split("%>").join("p.push('") + "');}catch(ex){$.jsRuntimeError(ex,\"tmpl调用异常 \");}}return p.join('');");
        return data ? fn(data) : fn;
    }

    $.tmpl = tmpl;

    function Template(templateID, data, isList) {
        try {
            if ($.isNullOrEmpty(templateID)) {
                return "";
            }
            var tmplObj = $.tmpl(templateID);
            var html = "";
            if (isList) {
                for (var i = 0; i < data.length; i++) {
                    html += tmplObj(data[i]);
                }
            }
            else {
                html = tmplObj(data);
            }
            return html;
        } catch(ex) {
            $.jsRuntimeError(ex, "Template调用异常:" + templateID);
        }
    }

    $.Template = Template;

    $.cache = {
        sdb: ( !! window.sessionStorage) ? window.sessionStorage: undefined,

        get: function(key) {
            var res = localStorage.getItem(key);
            return (res !== null) ? JSON.parse(res) : res;
        },
        set: function(key, value) {
            localStorage.setItem(key, JSON.stringify(value));
        },
        remove: function(key) {
            var res = $.cache.get(key);
            if (!$.isNullOrEmpty(res)) {
                localStorage.removeItem(key);
            }
        },

        setSessionItem: function(key, value) {
            if (this.sdb) {
                this.sdb.setItem(key, JSON.stringify(value));
            }
        },

        getSessionItem: function(key, defaultValue) {
            if (this.sdb) {
                var res = this.sdb.getItem(key);
                if (!$.isNullOrEmpty(res)) {
                    return JSON.parse(res);
                }
            }
            return defaultValue;
        },

        removeSessionItem: function(key) {
            if (this.sdb && key) {
                this.sdb.removeItem(key);
            }
        }
    };

    $.getDomData = function(element, key) {
        //如果元素为空，则返回空
        if (typeof element == 'undefined' || element == null) {
            return "";
        }

        if (typeof element.dataset != 'undefined' && element.dataset) {
            return element.dataset[key];
        } else if(typeof element.getAttribute != 'undefined' && element.getAttribute){
            return element.getAttribute('data-' + key);
        } else {
            return "";
        }
    };

    $.setDomData = function(element, key, value) {
        //如果元素为空，则跳出
        if (typeof element == 'undefined' || element == null) {
            return;
        }

        if (typeof element.dataset != 'undefined' && element.dataset) {
            return element.dataset[key] = value;
        } else {
            return element.setAttribute('data-' + key, value);
        }
    };

    $.attr = function(c, a, b) {
        if (b == undefined) {
            return c.getAttribute(a)
        } else {
            c.setAttribute(a, b)
        }
    };

    $.parentAsAttr = function(dom, attr) {
        if (!dom) return null;

        if (dom.hasAttribute && dom.hasAttribute(attr)) {
            return dom;
        }
        else {
            var parentNode = dom.parentNode;
            if (parentNode && parentNode.tagName != 'BODY') return $.parentAsAttr(parentNode, attr);
            else return null;
        }
    };

    // css
    $.classRE = function(name) {
        return new RegExp("(^|\\s)" + name + "(\\s|$)")
    };

    $.hasClass = function(ele, name) {
        if (!ele) {
            return false;
        }
        return $.classRE(name).test(ele.className);
    };

    $.hasClassCount = function(eles, name) {
        var count = 0;

        for (var i = 0, j = eles.length; i < j; i++) {
            if ($.hasClass(eles[i], name)) count++;
        }

        return count;
    };

    $.hasClassAll = function(eles, name) {
        return $.hasClassCount(eles) == eles.length;
    };

    $.addClass = function(ele, name) {
        if (ele && ! $.hasClass(ele, name)) {
            ele.className = (ele.className + ' ' + name).trim();
        }
    };

    $.addClassAll = function(eles, name) {
        for (var i = 0, j = eles.length; i < j; i++) {
            $.addClass(eles[i], name);
        }
    };

    $.removeClass = function(ele, name) {
        if (ele) ele.className = ele.className.replace($.classRE(name), ' ').trim();
    };

    $.removeClassAll = function(eles, name) {
        for (var i = 0, j = eles.length; i < j; i++) {
            $.removeClass(eles[i], name);
        }
    };

    $.swapClass = function(el, o, c) {
        var oc = el.className;
        var arr = oc.split(' '),
        temp = [];
        for (var i = 0, j = arr.length; i < j; i++) {
            if (arr[i] === o) {
                temp.push(c);
            } else {
                temp.push(arr[i]);
            }
        }

        el.className = temp.join(' ');
    };

    $.parent = function(dom, tagName, topTagName) {

        if (!dom) return null;
        if (topTagName == undefined) {
            topTagName = "BODY";
        } else {
            topTagName = topTagName.toUpperCase();
        }
        tagName = tagName.toUpperCase();
        if (dom.tagName == tagName) {
            return dom;
        }
        else {
            var parentNode = dom.parentNode;
            if (parentNode && parentNode.tagName != topTagName) return $.parent(parentNode, tagName);
            else return null;
        }
    };

    $.emf = function() {};

    $.hide = function(dom, keepLayout) {
        if (keepLayout) $.addClass(dom, "hidden");
        else $.addClass(dom, "none");
    };

    $.show = function(dom, keepLayout) {
        if (keepLayout) $.removeClass(dom, "hidden");
        else $.removeClass(dom, "none");
    };

    $.activeHide = function(dom) {
        $.removeClass(dom, "active");
    };

    $.activeShow = function(dom) {
        $.addClass(dom, "active");
    };

    $.breakPoint = function() {
        try {
            throw new Error("Break Point")
        } catch(ex) {}
    };

    $.isNullOrEmpty = function(obj) {
        if (typeof obj == "undefined") return true;

        if (obj == null) return true;

        if (typeof obj == "string" && obj.length == 0) return true;

        return false;
    };

    //检查网络类型（WIFI/3G）
    $.getApnType = function(notWifiCallback) {
        var currentNetType, isWIFI = false,
        connectionType = "unknown";
        var ua = navigator.userAgent;
        var isIQB = /iphone|ipod/ig.test(ua) && /mqq/ig.test(ua);
        if (isIQB && x5) {
            var options = {
                "appname": "热门视频"
            };
            x5.exec(
            function(result) {
                currentNetType = result.netType;
                isWIFI = (result.netType === 'WIFI');
                if (!isWIFI) {
                    notWifiCallback && notWifiCallback();
                }
            },
            function(code, message) {},
            "common", "getApnType", options);
        }

        return {
            isWifi: isWIFI,
            netType: currentNetType
        };
    };

    //深度克隆对象
    $.cloneObject = function(obj) {
        if (typeof(JSON) !== "undefined") {
            return JSON.parse(JSON.stringify(obj));
        } else {
            if (obj === null) {
                return null;
            }
            var o = obj.constructor === Array ? [] : {};
            for (var i in obj) {
                if (obj.hasOwnProperty(i)) {
                    o[i] = typeof obj[i] === "object" ? cloneObject(obj[i]) : obj[i];
                }
            }
            return o;
        }
    };

    $.preventDefault = function(e) {
        console.log("$.preventDefault Call");
        e.preventDefault();
    };

    $.getNavigatorInfo = function() {
        try {
            var ua = navigator.userAgent.toLowerCase();
            var qua = '';
            var isAndroid = /android/ig.test(ua);
            var isIos = /iphone|ipod/ig.test(ua);
            var isQb = /mqq/ig.test(ua);
            var isX5Core = false;
            var qbVer = 0;
            var isInLightApp = false;
            var fullVersionInfo = '0';
            var isIos51Err = false;

            var versionInfo = x5.getQQBrowerVer();

            if (versionInfo === null) {
                isQb = false;
            } else {
                var version = versionInfo.version;
                qua = versionInfo.qua + "";

                if(version > 0) {
                    isQb = true;
                    qbVer = version;
                } else {
                    isQb = false;
                    qbVer = 0;
                }
            }

            try {
                if (typeof window.x5mtt !== "undefined" && typeof window.x5mtt.packages === "function") {
                    var apkInfo = '{"packagename":"com.tencent.mtt"}';
                    var isInstalled = window.x5mtt.packages().isApkInstalled(apkInfo);
                    if (isInstalled !== - 1) {
                        var info = window.x5mtt.packages().getSingleApp("com.tencent.mtt");
                        var fullVersionInfoBuffer = JSON.parse(info).versionname.split(".");

                        for (var i = 0; i < Math.min(fullVersionInfoBuffer.length, 3); i++) {
                            fullVersionInfo += fullVersionInfoBuffer[i].toString();
                        }
                    }
                }
            } catch(ex) {}

            try {
                if (isQb && isAndroid) {
                    //检测是否是轻应用
                    var browserParam = null;
                    //此两行代码不可互换，轻应用APP应当优先使用mtt.getBrowserParam
                    if (typeof(mtt) !== "undefined" && typeof(mtt.getBrowserParam) !== "undefined") {
                        browserParam = mtt.getBrowserParam();
                    } else {
                        isInLightApp = true;
                    }

                    if (browserParam) {
                        browserParam = eval('(' + browserParam + ')');
                        qua = browserParam.qua + "";
                        qua = qua.toLowerCase();
                        if (qua.indexOf('adrqbx50_sdk') !== - 1) {
                            isInLightApp = true;
                        }
                        if (qua.indexOf('_lapp') !== - 1) {
                            isInLightApp = true;
                        }
                    }


                    //检测是否是小包版
                    if(qua.toUpperCase().indexOf("ADRQBX") !== -1) {
                        isX5Core = true;
                    } else {
                        isX5Core = false;
                    }
                }
            } catch(ex) {}

            var isQb51 = (isInLightApp === false && qbVer >= 51) ? true: false;
            var isQb52 = (isInLightApp === false && qbVer >= 52) ? true: false;

            try {
                if (isQb51 && isQb && isAndroid) {
                    isQb51 = $.checkQb51CoreAndroid();
                }
            } catch(ex) {}

            try {
                if (isQb52 && isQb && isAndroid) {
                    isQb52 = $.checkQb52CoreAndroid();
                }
            } catch(ex) {}

            if (isQb && isAndroid) {
                isQb51 = isX5Core === true ? isQb51 : false;
                isQb52 = isX5Core === true ? isQb52 : false;
            }

            if (isQb51 === true && isIos === true) {
                try {
                    x5.getQUAInfo(function(info) {
                        qua = info;

                        var quaBlock = [];
                        quaBlock = qua.match(/([0-9\.]+)/ig, '');
                        if (quaBlock && quaBlock.length > 0) {
                            if (quaBlock[1] === "510045" || quaBlock[1] === "510028" || quaBlock[1] === "510015") {

                                isIos51Err = true;
                                window.navigatorInfo.isIos51Err = true;
                            } else {
                                isIos51Err = false;
                                window.navigatorInfo.isIos51Err = false;
                            }
                        }
                    });
                } catch(ex) {
                }
            }

            return {
                ua: ua,
                qua: qua,
                isAndroid: isAndroid,
                isIos: isIos,
                isQb: isQb,
                isQb51: isQb51,
                isQb52: isQb52,
                isAndroidQb: isQb && isAndroid,
                isIosQb: isQb && isIos,
                isIos51Err: isIos51Err,
                isX5Core: isX5Core,
                isInLightApp: isQb && isAndroid && isInLightApp,
                qbVer: qbVer,
                qbVerFull: parseInt(fullVersionInfo)
            };
        } catch(ex) {
            $.jsRuntimeError(ex, "获取浏览器信息（Local）异常");
        }
    };

    $.checkQb51CoreAndroid = function() {
        if (typeof(x5mtt) === "undefined") {
            return false;
        }

        if (typeof(x5mtt.getLastHistory) === "undefined" || typeof(x5mtt.getHistory) === "undefined" || typeof(x5mtt.playLastHistory) === "undefined" || typeof(x5mtt.doFollowShows) === "undefined" || typeof(x5mtt.deleteFollowShows) === "undefined" || typeof(x5mtt.checkIsFollowsUpdate) === "undefined" || typeof(x5mtt.canDownload) === "undefined" || typeof(x5mtt.doMultiCache) === "undefined" || typeof(x5mtt.playEpisode) === "undefined") {
            return false;
        }

        return true;
    };

    $.checkQb52CoreAndroid = function() {
        if (typeof(x5mtt) === "undefined") {
            return false;
        }

        if (typeof(x5mtt.getSpecificHistory) === "undefined") {
            return false;
        }

        return true;
    };

    window.$ = $;
    window.navigatorInfo = $.getNavigatorInfo();
} ());

