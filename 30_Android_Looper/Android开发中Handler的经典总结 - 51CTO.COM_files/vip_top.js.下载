var show_vip = function(){
	var timer;
	function delayShow(obj){
	clearTimeout(timer);
	$('#vip_mes_top').show();
	}
	function delayHide(obj,self){
		timer = setTimeout(function(){$('#vip_mes_top').hide();}, 1000);
	};

	$('#login_status .jsVipDrop').live('mouseover',function(){
			delayShow($(this));
		}
	).live('mouseout', function(){
			delayHide($(this));
		});
}
show_vip();