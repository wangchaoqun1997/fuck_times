function remark(){
}

remark.container=null;		// 表单所在div
remark.sourceEle=null;		// 开启表单的链接
remark.faceTimer=null;		// 显示表情定时隐藏
remark.reId=0;			// 回复的评论id

// 评论投票
remark.vote = function(ele,rid,s){
	var voted = iwms.cookie("iwmsRVoted");
	voted = voted.length==0 ? [] : voted.split(',');
	if (voted.include(rid)){
		iwms.popMsg("rvote",ele,"您已经对该评论投过票!");
		iwms.hideMsg("rvote",2000);
		return;
	}
	iwms.ajSrc=ele;
	$.post(iwms.urlPrefix+'remark.aspx',{act:'ajax',cmd:'vote',rid:rid,support:s},function(r){
		if (r.success){
			iwms.popMsg("rvote",ele,"谢谢您参与投票!");
		}else{
			iwms.popMsg("rvote",ele,"评论已不存在，提交失败!");
		}
		iwms.hideMsg("rvote",2000);
		if(voted.length>9){
			voted=voted.slice(voted.length-9);
		}
		voted.push(rid);
		iwms.cookie("iwmsRVoted",voted.toString(),30);
		ele.innerHTML="已"+ele.innerHTML;
		ele=ele.nextSibling;
		var n = parseInt(ele.innerHTML.replace(/\D/g,""));
		ele.innerHTML="&nbsp;("+(n+1)+")";
	},'json');
	
};

// 页面插入新评论
remark.add = function(r)
{
	var str="<div class='reHead'><div class='reLayer'>第 "+
		r.layer+" 楼</div><img src='"+ iwms.urlPrefix +"pic/b.gif' class='face"+
		r.face+"' alt=''/> <span class='reName'>"+
		r.username+"</span> 发表于 <span class='reDate'>"+
		r.date+"</span></div><div class='reBody'>"+
		r.body+"</div><div class='reFun'><a href='###'>回复</a> <a href='###'>支持</a> (0) <a href='###'>反对</a> (0)</div>";
	var $con=$("#reContainer");
	if ($con.length>0){
		$con.prepend(str);
	}
};

// 显示评论表单
remark.disp = function(ele, rid)
{
	if (remark.container){
		var sourceChg=false;	// 事件源改变的话直接显示
		var o=remark.container;
		if (remark.sourceEle && ele && remark.sourceEle!=ele){
			sourceChg=true;
		}
		remark.sourceEle=ele;
		if (o.style.display=="none" || o.style.display=="" || sourceChg){
			var o_f=document.fmRemark;
			var u=o_f.username.disabled ? "" : o_f.username.value;
			o_f.reset();
			if(u.isSpace()){
				$i("rmAnonymity").click();
			}else{
				o_f.username.value=u;
			}
			var pos=iwms.msgPos(ele,o);
			with(o.style){
				left=pos.x+"px";
				top=pos.y+"px";
				display="block";
				zIndex=100;
			}
			remark.reId=rid ? rid : 0;
			iwms.dropShadow("remark",o);
			$(o_f.body).focus();
		}else{
			iwms.clearShadow("remark");
			o.style.display="none";
			
		}
	}else{
		iwms.ajSrc=ele;
		$.get(iwms.urlPrefix+'remark.xml',function(r){
			var html=$(r).find("html:eq(0)").text();
			if(iwms.urlPrefix.length>0){
				html=html.replace("pic/b.gif",iwms.urlPrefix+"pic/b.gif");
			}
			var $o=$("<div/>").addClass("aj_form").html(html).appendTo("body");
//			o.className="aj_form";
//			o.innerHTML= ? html : 
//			document.body.appendChild(o);
			remark.container=$o.get(0);
			if (iwms.user.name.length>0){
				document.fmRemark.username.value=iwms.user.name;
			}
			remark.needLogin();
			remark.disp(ele, rid);
		},'xml');
		return;
	}
};

// 设置匿名
remark.anony = function(o_c)
{
	var o_f=o_c.form;
	var o_n,os;
	var $n=$("input[name='username']:eq(0)",o_f);
	if ($n.length<1){
		return;
	}
	if (o_c.checked){
		$n.val("匿名").attr("disabled","disabled");
	}else{
		$n.val(iwms.user.name).removeAttr("disabled");
	}
};

// ctrl+enter提交
remark.handle = function(e,ele){
	if (e.ctrlKey && e.keyCode==13){
		remark.post(ele.form);
		return false;
	}else{
		return true;
	}
};

// 显示内容长度
remark.dispLen = function(obj){
	$("#bodyLen",obj.form).val(obj.value.length);
};

// 显示表情
remark.dispFace = function(ele)
{
	window.clearTimeout(remark.faceTimer);
	var fname=$(ele).parent("form:first").attr("name");	// 表单名
	o=$i("iwmsRemarkFace");
	if (o==null){
		o=document.createElement("DIV");
		o.id="iwmsRemarkFace";
		with(o.style){
			display="none";
			position="absolute";
			border="1px solid #999";
			padding="3px";
			background="#FAFAD2";
			font="9pt 宋体 arial";
			color="#000";
			whiteSpace="nowrap";
			if (typeof(opacity)=="string"){
				opacity="0.7";
			}else{
				filter="alpha(opacity=70)"
			}
			zIndex=103;
		}
		o.onmouseout=function(){remark.hideFace()};
		o.onmouseover=function(){if (remark.faceTimer!=null)window.clearTimeout(remark.faceTimer);};
		ele.ownerDocument.body.appendChild(o);
	}
	if (o.style.display=="none"){
		var txt="";
		for(var i=1; i<19; i++){
			txt+="<img src='"+ iwms.urlPrefix +"pic/b.gif' class='face"+ i +"' style='border:2px solid #FAFAD2;margin:3px' onclick='remark.pickFace(this,"+i+",\""+fname+"\")' onmouseover=\"this.style.borderColor='#DEB887';\" onmouseout=\"this.style.borderColor='#FAFAD2';\"/>";
			if (i==9){
				txt+="<br/>";
			}
		}
		o.innerHTML=txt;
		var pos=iwms.msgPos(ele,o);
		o.style.left=pos.x+"px";
		o.style.top=pos.y+"px";
		// 高亮当前表情
		for(var i=0; i<o.childNodes.length; i++){
			if (o.childNodes[i].className==ele.className){
				o.childNodes[i].style.backgroundColor="#DEB887";
				break;
			}
		}
		o.style.display="block";
	}
};

// 隐藏表情
remark.hideFace = function()
{
	if (remark.faceTimer!=null){
		window.clearTimeout(remark.faceTimer);
	}
	remark.faceTimer=window.setTimeout(function(){var o=$i('iwmsRemarkFace');if(o){o.style.display='none';}},1000);
};

// 选择表情
remark.pickFace = function(ele,n,fname)
{
	var fm=document.forms[fname];
	var o_face=fm.face;
	var $faces=$("img[class^='face']:first",fm);
	o_face.value=n;
	$faces.attr("class",ele.className);
	$("#iwmsRemarkFace").hide();
	if (remark.faceTimer!=null){
		window.clearTimeout(remark.faceTimer);
	}
};

// 显示评论协议
remark.dispAgreement = function()
{
//	var o=document.fmRemark.nextSibling;
//	o.style.display = o.style.display=="none" ? "block" : "none";
	$(document.fmRemark).next().toggle();
	iwms.dropShadow("remark",remark.container);
};

// 提交评论
remark.post = function(fm)
{
	if (iwms.cookie("remarked").length>0){
		alert("为防灌水,请稍后重发");
		return false;
	}
	if (!$("input[id^='rmAgree']:first",fm).prop("checked")){
		alert("只有同意本站评论声明才可发布");
		return false;
	}
	if (fm.username.value.isSpace()){
		alert("请填写姓名");
		fm.username.focus();
		return false;
	}
	if (fm.body.value.isSpace()){
		alert("请填写评论内容");
		fm.body.focus();
		return false;
	}
	if (fm.body.value.length<remark.minSize){
		alert("评论内容至少"+ remark.minSize +"字");
		fm.body.focus();
		return false;
	}
	if (fm.body.value.length>remark.maxSize){
		fm.body.value = fm.body.value.substr(0,remark.maxSize);
		remark.dispLen(fm.body);
		fm.body.focus();
		alert("评论内容不可以超过"+remark.maxSize+"字,已帮你删除多余部分");
		return false;
	}
	if (fm.username.value.length>19){
		alert("姓名不可以超过10个字");
		fm.username.focus();
		return false;
	}

	iwms.ajSrc=remark.sourceEle;
	var v=iwms.ajForm(fm);
	v.act='ajax';
	v.cmd='add';
	v.id=iwms.aId;
	v.reId=remark.reId;
	v.vcode=iwms.vCode;
	$.post(iwms.urlPrefix+'remark.aspx',v,function(data){
		if (fm.name=="fmRemark"){
			remark.disp();
		}
		if (data.interval>0){
			iwms.cookie('remarked','1',data.interval/24/3600);
		}
		if (data.obj){
			remark.add(data.obj);
		}
		fm.body.value="";
		iwms.popMsg("remark",remark.sourceEle,data.msg);
		iwms.hideMsg("remark",2000);
		
	},'json');
	return false;
};

remark.memberOnly=true;	// 管理中修改时重生成此处
//非会员不可评论时处理
remark.needLogin=function(){
	if(remark.memberOnly && iwms.user.id==0){
		$fm=$("form[name^='fmRemark']");
		$("button[type='submit']",$fm).attr("disabled","disabled").css("padding","0").text("请登录");
		$("input,textarea",$fm).attr("disabled","disabled");
	}
}

$(function(){
	remark.needLogin();
});