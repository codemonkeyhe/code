function saveLoadErr(ex,logMsg){var cJson=localStorage.getItem("jException")||"";var exceptions=null;var logUrl=ex.srcElement.href||ex.srcElement.src;if(cJson&&cJson.length>0){exceptions=JSON.parse(cJson);}if(exceptions==null||typeof exceptions.sJException=="undefined"){exceptions={sJException:[]};}var newException={};newException.args=[];newException.callStack="";newException.errorMessage="";newException.hash=window.location.hash;newException.host=window.location.host;newException.timeStamp=new Date().toString();newException.type=logMsg;if(logUrl){newException.args.push(logUrl);}exceptions.sJException.push(newException);console.log(newException);localStorage.setItem("jException",JSON.stringify(exceptions));}function heatMap(){var reportUrl="http://statistics.html5.qq.com/click";var businessName="hotVideo_Phone";var getBusinessKeyFromUrl=function(){var key="";var domIds=["index","detail","history","innerSearch","feedBack","statement"];for(var i=0,j=domIds.length;i<j;i++){var element=$.E(domIds[i]);if(element&&!$.hasClass(element,"none")){key=domIds[i];break;}}if(key=="index"){var indexNav=$.E("indexNav");var currentElement=indexNav.querySelector(".current");if(currentElement){key+=("_"+$.getDomData(currentElement,"groupid"));}}else{if(key=="innerSearch"){var scrollContent=$.E("innerSearchScrollContent");if(scrollContent&&!$.hasClass(scrollContent,"none")){key+="_Result";}}}return key;};if(window.HeatmapReport){HeatmapReport.init({url:reportUrl,businessName:businessName,onProcessUrl:getBusinessKeyFromUrl});}}function allLoaded(){if(typeof Video!="undefined"||window.swiperReady!==true){if(typeof(Page.index)=="undefined"||typeof(Page.detail)=="undefined"||typeof(Page.innerSearch)=="undefined"||typeof(Page.history)=="undefined"||typeof(Page.night)=="undefined"){return false;}return true;}else{return false;}}function startApp(){heatMap();(function(){if(allLoaded()){window.Cube.ajax.addCacheRequest(CONF.ajaxUrl+"?action=getStartPage",2000);window.Cube.ajax.addCacheRequest(CONF.ajaxUrl+"?action=getHotWords",2000);document.body.style.display="block";Video.start();$.uploadExceptionFromLocalStorage();}else{setTimeout(arguments.callee,1000);}}());breakPoint;}$.breakPoint();window.onload=startApp;$.breakPoint();Video=(function(){var oldPageName="";var userInfo={};var debugInfoElement=null;var onhashChange=function(){var hashObj=Video.getNavObj();var isValidPage=false;if(location.hash==""){location.hash="#p=index&g="+CONF.defaultGroupId;return;}for(var x in CONF.TOGA){if(CONF.TOGA.hasOwnProperty(x)&&CONF.TOGA[x]===true&&x===hashObj.p){isValidPage=true;break;}}if(isValidPage===false){location.hash="#p=index&g="+CONF.defaultGroupId;return;}if(hashObj.p==="index"){var groupInfoLocal=com.Bll.getGroupInfo(hashObj.g,true);if($.isNullOrEmpty(groupInfoLocal)||groupInfoLocal.hasChannel==false){var smartGroupId=com.Bll.getFitGroupId(hashObj.g);hashObj.g=smartGroupId;location.hash=Video.buildNavObj(hashObj);return;}}var pageName=hashObj.p;var groupId=Video.getNavObj().g;try{Page[pageName].show();if(oldPageName==""){oldPageName="index";}else{if(oldPageName!==pageName){Page[oldPageName].hide();}}if(com.Bll.getscrollYIndicator()!=-1){window.scrollTo(0,com.Bll.getscrollYIndicator());}oldPageName=pageName;showDebugInfo();document.title=com.Bll.getPageTitle();}catch(ex){$.jsRuntimeError(ex,"Page Show Faild "+String.format("newPage:{0} oldPage:{1}",pageName,oldPageName));}};var originalAlert=alert;alert=function(content){if(CONF.debugMode.alert===true){originalAlert.call(this,content);}};var showDebugInfo=function(){var requestObj=Video.getRequestObj();var debugInfo=$.E("debugInfo");if(requestObj.debug==="1"){$.removeClass(debugInfo,"none");var debugInfoHTML="";for(var x in window.navigatorInfo){debugInfoHTML+=String.format('<p><b style="font-weight:bold;">{0}</b>: {1}</p>',x,window.navigatorInfo[x]);}if(window.jsStamp){for(var x in window.jsStamp){debugInfoHTML+="<p>"+x+"&nbsp;"+window.jsStamp[x]+"</p>";}}var divs=debugInfo.querySelectorAll("div");divs[0].innerHTML=debugInfoHTML;}else{$.addClass(debugInfo,"none");}};var modifyUserInfo=function(type,position,indexGroup){userInfo.type=type;userInfo.position=position;userInfo.indexGroup=indexGroup;return buildUserInfo(oldPageName);};var buildUserInfo=function(oldPageName){var pageType;if(typeof userInfo.type=="undefined"){userInfo.type=0;}if(typeof userInfo.position=="undefined"){userInfo.position=0;}var channel=Video.getRequestObj().ch||Video.getNavObj().ch||"";if(userInfo.type=="enterToBanner"){var bannerId=userInfo.position?userInfo.position:0;var vType=userInfo.indexGroup?userInfo.indexGroup:0;pageType="&ref=banner_"+bannerId+"_"+vType+"_"+channel;return pageType;}if(oldPageName=="index"&&userInfo.type==1){userInfo.indexGroup=userInfo.indexGroup?userInfo.indexGroup:0;pageType="index_"+userInfo.indexGroup;}else{if(oldPageName=="index"){pageType="group_"+userInfo.indexGroup;}else{if(userInfo.type=="saved"){pageType="saved_"+userInfo.indexGroup;}else{pageType=oldPageName+"_"+userInfo.indexGroup;}}}return"&ref="+pageType+"_"+userInfo.position+"_"+channel;};var buildUserInfoBaseCh=function(){var channel=Video.getRequestObj().ch||Video.getNavObj().ch||"";if(channel!=""){var para=Video.getNavObj().para?Video.getNavObj().para:"";return"out_"+para+"_"+channel;}return"inValidChanel";};var getNavObj=function(){var hash=location.hash.split("?")[0];if(hash===""){return{};}else{return buildObj(hash);}};var buildObj=function(obj){if(obj[0]==="#"){obj=obj.substr(1);}var buffer=obj.split("&");var navObj={};for(var i=0;i<buffer.length;i++){if($.isNullOrEmpty(buffer[i])){continue;}var block=buffer[i].split("=");if(block.length==2){navObj[block[0]]=block[1];}else{if(block.length==1){navObj[block[0]]="";}}}return navObj;};var buildNavObj=function(navObj){var newNav="";for(var x in navObj){if(navObj.hasOwnProperty(x)){newNav+=(x+"="+navObj[x]+"&");}}if(newNav.length>0){newNav="#"+newNav.substr(0,newNav.length-1);}return newNav;};var getRequestObj=function(){var url=location.search;var theRequest={};if(url.indexOf("?")!=-1){var str=url.substr(1);strs=str.split("&");for(var i=0;i<strs.length;i++){theRequest[strs[i].split("=")[0]]=unescape(strs[i].split("=")[1]);}}return theRequest;};var count=0;var checkResourceValid=function(){console.log("checkResourceValid...");if(typeof com==="undefined"){return false;}if(typeof com.Dal==="undefined"){return false;}if(typeof com.Bll==="undefined"){return false;}if(typeof com.Vis==="undefined"){return false;}if(typeof com.Bll.hideTimeout==="undefined"){return false;}if(typeof com.Vis.createPlaySource==="undefined"){return false;}if(typeof com.Vis.createBackToTop==="undefined"){return false;}if(typeof Slide==="undefined"){return false;}return true;};var start=function(){try{if(checkResourceValid()===false){setTimeout(arguments.callee,500);return;}com.Bll.getNavigatorInfo();window.addEventListener("popstate",com.Bll.onPopState);window.addEventListener("hashchange",onhashChange);if(location.hash==""){location.hash="#p=index&g="+CONF.defaultGroupId;}else{onhashChange();}var stateObj={jumpIndex:0,to:location.hash,action:"forward",scrollY:0,circleJump:false};if(history.replaceState){history.replaceState(stateObj,"",location.hash);}if(debugInfoElement===null){debugInfoElement=$.E("debugInfo");}for(var i=localStorage.length-1;i>=0;i--){var key=localStorage.key(i);if(Number(key)>0){console.log("cleanning Key :"+key);localStorage.removeItem(key);}}if(!(navigatorInfo.isAndroidQb&&window.x5.getQQBrowerVer()==45&&!com.Dal.isAndroid45Authorized())){com.Bll.testTokenPush();}com.Bll.mergeFavData();com.Vis.createBackToTop();}catch(ex){$.jsRuntimeError(ex,"APP启动失败");}};$.breakPoint();return{start:start,getNavObj:getNavObj,getRequestObj:getRequestObj,modifyUserInfo:modifyUserInfo,buildObj:buildObj,buildNavObj:buildNavObj,buildUserInfoBaseCh:buildUserInfoBaseCh,onhashChange:onhashChange};}());(function(){var $={};$.E=function(s){return document.getElementById(s);};$.Q=function(s){return document.querySelector(s);};$.each=function(arr,func){Array.prototype.forEach.call(arr,func);};function tmpl(str,data){if(!tmpl.cache){tmpl.cache={};}var cache=tmpl.cache;var fn=!/\W/.test(str)?cache[str]=cache[str]||tmpl(document.getElementById(str).innerHTML):new Function("obj","var p=[];with(obj){try{p.push('"+str.replace(/[\r\t\n]/g," ").replace(/'(?=[^%]*%>)/g,"\t").split("'").join("\\'").split("\t").join("'").replace(/<%=(.+?)%>/g,"',$1,'").split("<%").join("');").split("%>").join("p.push('")+"');}catch(ex){$.jsRuntimeError(ex,\"tmpl调用异常 \");}}return p.join('');");return data?fn(data):fn;}$.tmpl=tmpl;function Template(templateID,data,isList){try{if($.isNullOrEmpty(templateID)){return"";}var tmplObj=$.tmpl(templateID);var html="";if(isList){for(var i=0;i<data.length;i++){html+=tmplObj(data[i]);}}else{html=tmplObj(data);}return html;}catch(ex){$.jsRuntimeError(ex,"Template调用异常:"+templateID);}}$.Template=Template;$.cache={sdb:(!!window.sessionStorage)?window.sessionStorage:undefined,get:function(key){var res=localStorage.getItem(key);return(res!==null)?JSON.parse(res):res;},set:function(key,value){localStorage.setItem(key,JSON.stringify(value));},remove:function(key){var res=$.cache.get(key);if(!$.isNullOrEmpty(res)){localStorage.removeItem(key);}},setSessionItem:function(key,value){if(this.sdb){this.sdb.setItem(key,JSON.stringify(value));}},getSessionItem:function(key,defaultValue){if(this.sdb){var res=this.sdb.getItem(key);if(!$.isNullOrEmpty(res)){return JSON.parse(res);}}return defaultValue;},removeSessionItem:function(key){if(this.sdb&&key){this.sdb.removeItem(key);}}};$.getDomData=function(element,key){if(typeof element=="undefined"||element==null){return"";}if(typeof element.dataset!="undefined"&&element.dataset){return element.dataset[key];}else{if(typeof element.getAttribute!="undefined"&&element.getAttribute){return element.getAttribute("data-"+key);}else{return"";}}};$.setDomData=function(element,key,value){if(typeof element=="undefined"||element==null){return;}if(typeof element.dataset!="undefined"&&element.dataset){return element.dataset[key]=value;}else{return element.setAttribute("data-"+key,value);}};$.attr=function(c,a,b){if(b==undefined){return c.getAttribute(a);}else{c.setAttribute(a,b);}};$.parentAsAttr=function(dom,attr){if(!dom){return null;}if(dom.hasAttribute&&dom.hasAttribute(attr)){return dom;}else{var parentNode=dom.parentNode;if(parentNode&&parentNode.tagName!="BODY"){return $.parentAsAttr(parentNode,attr);}else{return null;}}};$.classRE=function(name){return new RegExp("(^|\\s)"+name+"(\\s|$)");};$.hasClass=function(ele,name){if(!ele){return false;}return $.classRE(name).test(ele.className);};$.hasClassCount=function(eles,name){var count=0;for(var i=0,j=eles.length;i<j;i++){if($.hasClass(eles[i],name)){count++;}}return count;};$.hasClassAll=function(eles,name){return $.hasClassCount(eles)==eles.length;};$.addClass=function(ele,name){if(ele&&!$.hasClass(ele,name)){ele.className=(ele.className+" "+name).trim();}};$.addClassAll=function(eles,name){for(var i=0,j=eles.length;i<j;i++){$.addClass(eles[i],name);}};$.removeClass=function(ele,name){if(ele){ele.className=ele.className.replace($.classRE(name)," ").trim();}};$.removeClassAll=function(eles,name){for(var i=0,j=eles.length;i<j;i++){$.removeClass(eles[i],name);}};$.swapClass=function(el,o,c){var oc=el.className;var arr=oc.split(" "),temp=[];for(var i=0,j=arr.length;i<j;i++){if(arr[i]===o){temp.push(c);}else{temp.push(arr[i]);}}el.className=temp.join(" ");};$.parent=function(dom,tagName,topTagName){if(!dom){return null;}if(topTagName==undefined){topTagName="BODY";}else{topTagName=topTagName.toUpperCase();}tagName=tagName.toUpperCase();if(dom.tagName==tagName){return dom;}else{var parentNode=dom.parentNode;if(parentNode&&parentNode.tagName!=topTagName){return $.parent(parentNode,tagName);}else{return null;}}};$.emf=function(){};$.hide=function(dom,keepLayout){if(keepLayout){$.addClass(dom,"hidden");}else{$.addClass(dom,"none");}};$.show=function(dom,keepLayout){if(keepLayout){$.removeClass(dom,"hidden");}else{$.removeClass(dom,"none");}};$.activeHide=function(dom){$.removeClass(dom,"active");};$.activeShow=function(dom){$.addClass(dom,"active");};$.breakPoint=function(){try{throw new Error("Break Point");}catch(ex){}};$.isNullOrEmpty=function(obj){if(typeof obj=="undefined"){return true;}if(obj==null){return true;}if(typeof obj=="string"&&obj.length==0){return true;}return false;};$.getApnType=function(notWifiCallback){var currentNetType,isWIFI=false,connectionType="unknown";var ua=navigator.userAgent;var isIQB=/iphone|ipod/ig.test(ua)&&/mqq/ig.test(ua);if(isIQB&&x5){var options={appname:"热门视频"};x5.exec(function(result){currentNetType=result.netType;isWIFI=(result.netType==="WIFI");if(!isWIFI){notWifiCallback&&notWifiCallback();}},function(code,message){},"common","getApnType",options);}return{isWifi:isWIFI,netType:currentNetType};};$.cloneObject=function(obj){if(typeof(JSON)!=="undefined"){return JSON.parse(JSON.stringify(obj));}else{if(obj===null){return null;}var o=obj.constructor===Array?[]:{};for(var i in obj){if(obj.hasOwnProperty(i)){o[i]=typeof obj[i]==="object"?cloneObject(obj[i]):obj[i];}}return o;}};$.preventDefault=function(e){console.log("$.preventDefault Call");e.preventDefault();};$.getNavigatorInfo=function(){try{var ua=navigator.userAgent.toLowerCase();var qua="";var isAndroid=/android/ig.test(ua);var isIos=/iphone|ipod/ig.test(ua);var isQb=/mqq/ig.test(ua);var isX5Core=false;var qbVer=0;var isInLightApp=false;var fullVersionInfo="0";var isIos51Err=false;var versionInfo=x5.getQQBrowerVer();if(versionInfo===null){isQb=false;}else{var version=versionInfo.version;qua=versionInfo.qua+"";if(version>0){isQb=true;qbVer=version;}else{isQb=false;qbVer=0;}}try{if(typeof window.x5mtt!=="undefined"&&typeof window.x5mtt.packages==="function"){var apkInfo='{"packagename":"com.tencent.mtt"}';var isInstalled=window.x5mtt.packages().isApkInstalled(apkInfo);if(isInstalled!==-1){var info=window.x5mtt.packages().getSingleApp("com.tencent.mtt");var fullVersionInfoBuffer=JSON.parse(info).versionname.split(".");for(var i=0;i<Math.min(fullVersionInfoBuffer.length,3);i++){fullVersionInfo+=fullVersionInfoBuffer[i].toString();}}}}catch(ex){}try{if(isQb&&isAndroid){var browserParam=null;if(typeof(mtt)!=="undefined"&&typeof(mtt.getBrowserParam)!=="undefined"){browserParam=mtt.getBrowserParam();}else{isInLightApp=true;}if(browserParam){browserParam=eval("("+browserParam+")");qua=browserParam.qua+"";qua=qua.toLowerCase();if(qua.indexOf("adrqbx50_sdk")!==-1){isInLightApp=true;}if(qua.indexOf("_lapp")!==-1){isInLightApp=true;}}if(qua.toUpperCase().indexOf("ADRQBX")!==-1){isX5Core=true;}else{isX5Core=false;}}}catch(ex){}var isQb51=(isInLightApp===false&&qbVer>=51)?true:false;var isQb52=(isInLightApp===false&&qbVer>=52)?true:false;try{if(isQb51&&isQb&&isAndroid){isQb51=$.checkQb51CoreAndroid();}}catch(ex){}try{if(isQb52&&isQb&&isAndroid){isQb52=$.checkQb52CoreAndroid();}}catch(ex){}if(isQb&&isAndroid){isQb51=isX5Core===true?isQb51:false;isQb52=isX5Core===true?isQb52:false;}if(isQb51===true&&isIos===true){try{x5.getQUAInfo(function(info){qua=info;var quaBlock=[];quaBlock=qua.match(/([0-9\.]+)/ig,"");if(quaBlock&&quaBlock.length>0){if(quaBlock[1]==="510045"||quaBlock[1]==="510028"||quaBlock[1]==="510015"){isIos51Err=true;window.navigatorInfo.isIos51Err=true;}else{isIos51Err=false;window.navigatorInfo.isIos51Err=false;}}});}catch(ex){}}return{ua:ua,qua:qua,isAndroid:isAndroid,isIos:isIos,isQb:isQb,isQb51:isQb51,isQb52:isQb52,isAndroidQb:isQb&&isAndroid,isIosQb:isQb&&isIos,isIos51Err:isIos51Err,isX5Core:isX5Core,isInLightApp:isQb&&isAndroid&&isInLightApp,qbVer:qbVer,qbVerFull:parseInt(fullVersionInfo)};}catch(ex){$.jsRuntimeError(ex,"获取浏览器信息（Local）异常");}};$.checkQb51CoreAndroid=function(){if(typeof(x5mtt)==="undefined"){return false;}if(typeof(x5mtt.getLastHistory)==="undefined"||typeof(x5mtt.getHistory)==="undefined"||typeof(x5mtt.playLastHistory)==="undefined"||typeof(x5mtt.doFollowShows)==="undefined"||typeof(x5mtt.deleteFollowShows)==="undefined"||typeof(x5mtt.checkIsFollowsUpdate)==="undefined"||typeof(x5mtt.canDownload)==="undefined"||typeof(x5mtt.doMultiCache)==="undefined"||typeof(x5mtt.playEpisode)==="undefined"){return false;}return true;};$.checkQb52CoreAndroid=function(){if(typeof(x5mtt)==="undefined"){return false;}if(typeof(x5mtt.getSpecificHistory)==="undefined"){return false;}return true;};window.$=$;window.navigatorInfo=$.getNavigatorInfo();}());