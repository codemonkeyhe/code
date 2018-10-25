function saveLoadErr(d, b) {
	var a = localStorage.getItem("jException") || "";
	var c = null;
	var e = d.srcElement.href || d.srcElement.src;
	if (a && a.length > 0) {
		c = JSON.parse(a)
	}
	if (c == null || typeof c.sJException == "undefined") {
		c = {
			sJException: []
		}
	}
	var f = {};
	f.args = [];
	f.callStack = "";
	f.errorMessage = "";
	f.hash = window.location.hash;
	f.host = window.location.host;
	f.timeStamp = new Date().toString();
	f.type = b;
	if (e) {
		f.args.push(e)
	}
	c.sJException.push(f);
	console.log(f);
	localStorage.setItem("jException", JSON.stringify(c))
}

function heatMap() {
	var c = "http://statistics.html5.qq.com/click";
	var b = "hotVideo_Phone";
	var a = function() {
			var l = "";
			var e = ["index", "detail", "history", "innerSearch", "feedBack", "statement"];
			for (var k = 0, g = e.length; k < g; k++) {
				var h = $.E(e[k]);
				if (h && !$.hasClass(h, "none")) {
					l = e[k];
					break
				}
			}
			if (l == "index") {
				var m = $.E("indexNav");
				var f = m.querySelector(".current");
				if (f) {
					l += ("_" + $.getDomData(f, "groupid"))
				}
			} else {
				if (l == "innerSearch") {
					var d = $.E("innerSearchScrollContent");
					if (d && !$.hasClass(d, "none")) {
						l += "_Result"
					}
				}
			}
			return l
		};
	if (window.HeatmapReport) {
		HeatmapReport.init({
			url: c,
			businessName: b,
			onProcessUrl: a
		})
	}
}

function allLoaded() {
	if (typeof Video != "undefined" || window.swiperReady !== true) {
		if (typeof(Page.index) == "undefined" || typeof(Page.detail) == "undefined" || typeof(Page.innerSearch) == "undefined" || typeof(Page.history) == "undefined" || typeof(Page.night) == "undefined") {
			return false
		}
		return true
	} else {
		return false
	}
}

function startApp() {
	heatMap();
	(function() {
		if (allLoaded()) {
			window.Cube.ajax.addCacheRequest(CONF.ajaxUrl + "?action=getStartPage", 2000);
			window.Cube.ajax.addCacheRequest(CONF.ajaxUrl + "?action=getHotWords", 2000);
			document.body.style.display = "block";
			Video.start();
			$.uploadExceptionFromLocalStorage()
		} else {
			setTimeout(arguments.callee, 1000)
		}
	}())
}

window.onload = startApp;



function tmpl(str, data) {
	if (!tmpl.cache) {
		tmpl.cache = {};
	}
	var cache = tmpl.cache;
	var fn = ! /\W/.test(str) ? 
	cache[str] = cache[str] || tmpl(document.getElementById(str).innerHTML) : 
	new Function(
	"obj", 
	"var p=[];" + "with(obj){try{p.push('" + str.replace(/[\r\t\n]/g, " ").replace(/'(?=[^%]*%>)/g, "\t").split("'").join("\\'").split("\t").join("'").replace(/<%=(.+?)%>/g, "',$1,'").split("<%").join("');").split("%>").join("p.push('") + "');
	
	}catch(ex){$.jsRuntimeError(ex,\"tmplµ˜”√“Ï≥£ \");}}return p.join('');");
	
	return data ? fn(data) : fn;
}