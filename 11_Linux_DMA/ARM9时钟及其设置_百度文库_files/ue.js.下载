(function(){
    var href = location.href + "";    
    var win = window;
    var body = document.body;
    var nav = win.navigator
    var doc = document.documentElement;

    // ifr 框架中测试
    window.DSPUIIFRTest = {
        values: {
            // 判断是否在iframe里面
            infr: function(){
                return self === top ? 1: 0;
            },
            // 是否可以跨域
            cross: function(){
                try {
                    top.location.toString();
                } catch(e){
                    // 有跨域情况
                    return 1;
                }
                // 没有跨域
                return 0;
            },
            // 文本状态
            drs: function(){
                var statusMap = {
                    'uninitialized': 0,
                    'loading': 1,
                    'loaded': 2,
                    'interactive': 3,
                    'complete': 4
                };
                return function(){
                    try {
                        return statusMap[document.readyState];
                    } catch (e) {
                        return -1;
                    }
                }
            }(),
            // 浏览器窗口可视区域大小
            pcs: function(){
                return [
                    win.innerWidth || Math.max(doc.clientWidth,body.clientWidth),
                    win.innerHeight || Math.max(doc.clientHeight,body.clientHeight)
                ].join('x');
            },
            // 页面大小（包含滚动条）
            pss: function(){
                return [
                    Math.max(body.scrollWidth, doc.scrollWidth,body.offsetWidth,doc.offsetWidth,doc.clientWidth),
                    Math.max(body.scrollHeight, doc.scrollHeight,body.offsetHeight,doc.offsetHeight,doc.clientHeight)
                ].join('x');
            },
            // 获取当前flash版本号
            cfv: function(){
                var retv = 0;

                try {
                    if (nav.plugins && nav.mimeTypes.length) {
                        var macth = nav.plugins["Shockwave Flash"];
                        if (match && match.description) {
                            retv = match.description
                                .replace(/([a-zA-Z]|\s)+/, "")
                                .replace(/(\s)+r/, ".") + ".0";
                        }
                    }

                    if ( retv === 0 && (win.ActiveXObject || win.hasOwnProperty('ActiveXObject'))) {
                        for(var i=30; i>=2; i--){
                            try{
                                var n = new ActiveXObject("ShockwaveFlash.ShockwaveFlash." + i);
                                if (n) {
                                    var o = n.GetVariable("$version");
                                        retv  = o.replace(/WIN/g, "").replace(/,/g, ".");
                                    if (retv > 0){
                                        break;
                                    }
                                }
                            }catch(e){}
                        }
                    }

                    retv = parseInt(retv, 10);
                } catch(e) {
                    retv = 0
                }

                return retv;
            },
            // plugin插件数量
            cpl: function(){
                return nav.plugins.length || 0;
            },
            // 历史记录
            chi: function(){
                return win.history.length || 0;
            },
            // 是否启用cookie
            cce: function(){
                return nav.cookieEnabled ? 1 : 0; 
            },
            // 字符编码
            cec: function(){
                return (document.characterSet || document.charset || '').replace(/[^0-9a-z]/ig,'');
            },
            // 文档最后修改时间
            tlm: function(){
                return Date.parse(document.lastModified) / 1000;
            },
            // 是否支持跨域
            ecd: function(){
                return !!window.postMessage ? 1 : 0;
            }
        },
        getCode: function(width,height){
            var value = this.values,
                val = '',
                put = [];

            for(var p in value) {

                val = value[p]();

                put.push(p + ':' + val);
            }
            put.push('adw:' + width + 'x' + height);

            return put.join('_');
        }
    };
})();
/*
 * PC 端自定义代码统一 
 * PC 嵌入的代码统一，
 * 和联盟接入方式一样
 */
 
 (function(){
    var BDEmbed = {
        init: function(){

            this.data = [];
            this.iframeurl  = (window.DSPUIIFRAMEURI
                             || (location.protocol + '//entry.baidu.com/rp/home'))+'?';

            this.script();
            this.render();
        },
        render: function(url){
            if ( this.data.length ){
                for( var i=0,l=this.data.length;i<l;i++ ) {
                    this.done(this.data[i]);
                }
                try {
                    window.cpro_psid = null;
                } catch(e){}
            }
        },
        getParam: function(data){
            var param = [];

                try{
                    if (typeof DSPUIIFRTest !=='undefined'){
                        data.ifr =  DSPUIIFRTest.getCode(data.rsi0, data.rsi1);
                    }
                }catch(e){}
            
                data.di    = data.psid;
                data.rsi0  = data.pswidth;
                data.rsi1  = data.psheight;
                data.title = document.title;
                data.ref   = document.referrer;
                data.ltu   = window.location+'';
                data.t = +new Date;



            //配置数据
            if ( window.cpro_psdata ) {
                for( var p in cpro_psdata ){
                    data[p] = cpro_psdata[p];
                }
                window.cpro_psdata = undefined;
            }

            for (var p in data) {
                if (typeof data[p] !== 'object') {
                    param.push(p + '=' + encodeURIComponent(data[p]));
                }
            }

            return param;
        },
        done: function(data){
            var iframe = document.createElement('iframe'),
                param  = this.getParam(data);

            iframe.src    = this.iframeurl+param.join('&');
            iframe.width  = data.pswidth;
            iframe.height = data.psheight;

            iframe.scrolling = 'no';
            iframe.frameBorder = '0';
            iframe.allowTransparency = true;
            iframe.style.width  = data.pswidth+'px';
            iframe.style.height = data.psheight+'px';
            iframe.style.backgroundColor = 'transparent';

            try{
                data.script.parentNode.insertBefore(iframe,data.script);
            }catch(e){}
        },
        script: function(){
            var scripts = document.getElementsByTagName('script'),
                script,html,psid,pswidth,psheight;

            for( var i=0,l=scripts.length;i<l;i++ ) {
                script = scripts[i];
                //只对没有src的script标签生效
                if (!script.getAttribute('src')) {
                    html = script.innerHTML
                                .replace(/\/\/[^\n]+/g,'')//单行注释
                                .replace(/\n/g,';')//换行符
                                .replace(/\/\*.+\*\//ig,'')//多行注释
                                .replace(/[\s\uFEFF\xA0\t]/ig,'');//空白tab
                    
                    
                    if ( !script.id  ){

                        psid     = this.getMatch('psid',html);
                        pswidth  = this.getMatch('pswidth',html);
                        psheight = this.getMatch('psheight',html);
                        //3项都找到的情况
                        if ( psid && pswidth && psheight ) {
                            script.id = 'BDEMBED_PSID'+psid;

                            this.data.push({
                                script: script,
                                psid: psid,
                                pswidth: pswidth,
                                psheight: psheight
                            })
                        }
                    }
                }
            }
        },
        getMatch: function(){
            var regex = {
                psid: /cpro_psid[\s\uFEFF\xA0]*=[\s\uFEFF\xA0]*['"]([a-z0-9]{4,20})/i,
                pswidth: /cpro_pswidth[\s\uFEFF\xA0]*=[\s\uFEFF\xA0]*['"]*([0-9a-z]{1,10})/i,
                psheight: /cpro_psheight[\s\uFEFF\xA0]*=[\s\uFEFF\xA0]*['"]*([0-9]{1,10})/i
            };
            return function(type,value){
                var match = value.match(regex[type]);

                if ( match ) {
                    return match[1];
                }
            }
        }()
    };

    BDEmbed.init();
 })();
