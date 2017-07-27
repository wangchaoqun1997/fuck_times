var baidusearch = (function(){
	
	function init(tn){
		addEV(document, 'mouseup', fn);

		function fn(){
			var isStandard = "getSelection" in window;

			var ico_img = document.getElementById('selectsearch-icon');
			if(ico_img){
				ico_img.parentNode.removeChild(ico_img);
			}

			setTimeout(function(){
				selection = isStandard ? window.getSelection() : document.selection.createRange()
				var text = (isStandard ? selection+'' : selection.text).replace(/\n+/g, '');
				if(text && text.length){
					if(text.length > 76){
						text = text.substring(0, 76);
					}
					show(isStandard, selection, text);
				}
			}, 25);
		}

		function show(isStandard, selection, text){
			var scrollTop = document.body.scrollTop + document.documentElement.scrollTop;
			var scrollLeft = document.body.scrollLeft + document.documentElement.scrollLeft;

			if(isStandard){
				var rangePos = selection.getRangeAt(0).getBoundingClientRect();
				if(rangePos.top==0 && rangePos.right==0)
					return;
				var tempTop = rangePos.top>35 ? rangePos.top-35+scrollTop : scrollTop;
				var tempLeft = rangePos.right+70>document.documentElement.clientWidth ? document.documentElement.clientWidth-65+scrollLeft : rangePos.right+5+scrollLeft;				
			}else{
				var selectionLeft = selection.boundingLeft+selection.boundingWidth;
				var tempTop = selection.boundingTop>35 ? selection.boundingTop-35+scrollTop : scrollTop;
				var tempLeft = selectionLeft+70>document.documentElement.clientWidth ? document.documentElement.clientWidth-65+scrollLeft : selectionLeft+scrollLeft;
			}

			var text = encodeURI(text);
			var img = document.createElement('img');
			img.src = 'http://img.baidu.com/img/iknow/qb/select-search.png';
			img.alt = '搜索';
			img.style.cssText = "width:65px; height:31px; border:0px none;";

			var link = document.createElement('a');
			link.id = 'selectsearch-icon';
			link.style.cssText = "cursor:pointer; position:absolute;"
			link.href = 'http://www.baidu.com/s?wd='+text+'&tn='+tn+'&hl_tag=flayer';
			link.target = '_blank';

			link.onclick = function(){
				link.parentNode.removeChild(link);
			}

			link.style.left = tempLeft + 'px';
			link.style.top = tempTop + 'px';
			link.appendChild(img);
			document.body.appendChild(link);

			img.onmouseup = function(e){
				e = e || window.event;
				if(e.stopPropagation){
					e.stopPropagation();
				}else{
					e.cancelBubble = true;
				}
			}
		}

		function addEV(d,b,a){if(window.attachEvent){d.attachEvent("on"+b,a)}else{if(window.addEventListener){d.addEventListener(b,a,false)}}} 
	};

	return {
		'init' : init
	}
})();	