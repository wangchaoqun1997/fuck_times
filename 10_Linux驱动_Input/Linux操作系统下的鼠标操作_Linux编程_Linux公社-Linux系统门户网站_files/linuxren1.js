document.writeln("<script type=\"text\/javascript\">");
document.writeln("document.body.oncopy = function () { setTimeout( function () { var text = clipboardData.getData(\"text\"); if (text) { text = text + \"\\r\\n本篇文章来源于 Linux公社网站(www.linuxidc.com)  原文链接：\"+location.href; clipboardData.setData(\"text\", text); } }, 100 ) }");
document.writeln("<\/script>")