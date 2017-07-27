
$(function(){
   var url = window.location.host;
   var type = url.split('.');
   $.ajax({
	url: 'http://www.51cto.com/php/getRecommendJob.php',
	type: 'get',
	data: {category:type[0]}, 
	dataType: 'jsonp',
	jsonp: 'callback',
	success: function(result){
		if(result.error_code == 0){
		   var str = '';
		   var data = result.data;
		   for (var i in data) {
			if (data[i].salary) {
				var salary = data[i].salary;
			} else {
				var salary = data[i].salary_min +'-'+data[i].salary_max;
			}
			str += '<dl><dt><a href="'+data[i].url+'" target="_blank" > '+data[i].position+' </a></dt>';
			str += '<dd><h2>' + data[i].job_nature + '/' + data[i].work_year + '/' + data[i].lowest_degrees + '</h2>';
			str += '<span>' + salary + '</span><a href=" '+ data[i].company_url +' " target="_blank">'+ data[i].short_name +'</a></dd></dl>';
		   }
		   $(".rmzwn_xx").html(str);
		} else {
		   $(".rmzwn_xx").html('暂无推荐职位');
		}
	},
	error: function(result){
		$(".rmzwn_xx").html('暂无推荐职位');
	}
   })
})
