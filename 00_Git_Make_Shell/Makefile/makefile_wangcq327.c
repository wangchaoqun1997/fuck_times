Makefile 总结
/：make规则
target:perrequisites
	command
/：make 只管文件依赖性
在找寻的过程中，如果出现错误，比如最后被依赖的文件找不到，那么
make 就会直接退出，并报错，而对于所定义的命令的错误，或是编译不成功，make 根本不
理
/：Makefile主要包含五个东西，显式规则，隐晦规则，变量定义，文件指示，注释
/：文件指示包含3部分，一个Makefile包含另外一个Makefile(include),指定Makefile中有效部分，定义一个多行命令
/：注释用#
/：make命令会在当前目录顺序查找GUNmakefile,makefile,Makefile；可以用-f   --file参数指定特定Makefile文件
/：include关键字会把别的Makefile包含进来，被包含的文件会原样放在当前包含的位置，语法为：include <filename>，文件搜索路径可以在filename中体现，如没有，则根据‘-I’或‘--include-dir’参数
/：建议不要使用环境变量MAKEFILES
/：make执行步骤：读入Makefile，读入被include包含的Makefile，初始化文件中的变量，推到隐晦规则分析所有规则，给所有目标创建依赖关系链，生成目标
/：一个Makefile规则包含三部分：规则目标(以空格分割，可以用通配符)，规则依赖，规则命令(跟在依赖之后用;另起一行以TAB开始，命令太长可以用\换行，以shell来执行命令)
/：第一条规则中的第一个目标被确定为最终目标
/：make规则中可以使用三种通配符   *   ?   [...]    ~表示当前用户的$(HOME)
/：通配符可用于可以用在变量中，如object = *.o (object值就是*.o)
/：工程的源文件在各个目录，当make去寻找依赖文件或者目标文件时，可以用VPATH变量指定搜索目录，这种情况下，当make在当前文件夹找不到时，回去VPATH指定目录找，如VPATH=src:../headers(按目录顺序搜索)
另外一种设置文件搜索路径的方法是用vpath关键字(不是变量)，这个关键字可指定不同文件在不同搜索目录
/：伪目标不是文件，是一个标签，可以用.PHONY显示指明一个目标为伪目标，如.PHONY : clean clear  伪目标总是被执行的
/：make规则目标可以不止一个，这时，规则命令可能用到自动化变量
/：make的静态模式(可以更加容易的定义多目标规则),
语法  <targets...>:<target-pattern>:<prereq-patterns>;<commands>
targets定义一系列的目标文件，可以用通配符，是目标的集合
target-pattern指明targets的模式，也就是规则目标的集合
target-patterns之名规则依赖模式
如：object = foo.o bar.o c.c
all ： $(object)
$(object):%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@
(规则依赖中的%.c中的%取%.o中的%,$<表示所有依赖的目标,$@表示规则目标集合%.o)
这个静态规则拆开是两条规则
/：Makefile中，规则依赖可能包含一系列的头文件，可以利用c编译器的功能，自动生成依赖关系
/：make的规则命令会一条一条执行，默认用/bin/sh，如果希望上一条命令结果应用在下一条命令，这两条命令需要放在同一行，并用;分隔
/：make执行一条命令会检测命令返回码，成功则执行下一条命令，失败则终止执行当前规则，这有可能会终止所有规则，为了防止，可在这条规则命令前加 - 号
/：make默认将 ‘规则命令’ 在执行前输出到屏幕，可以将@放在规则命令前，这样，规则命令的‘命令’将不被显示
/：make带-n或--just-print只显示命令，不会执行命令，这有利于调试Makefile
/：make带-s或--slient是全面禁止命令的显示
/：大型工程各个目录下也会有Makefile,这时总控Makefile要嵌套执行make   如$(MAKE) -C 目录名
总控Makefile中的变量可以传递到下级的Makefile中(要用export声明export 变量=值)，但不会覆盖下层的Makefile(除非指定了-e参数)，如果想传递所有变量，只需一个export就可以，通过命令行传入的变量会自动传递到下层
/：SHELL和MAKEFLAGS总是会传递到下层的Makefile中的，MAKEFLAGS变量包含了make的参数信息，如果执行时带了参数或者上层Makefile中定义了这个变量，这些参数将会传给下层Makefile，但是make命令中的-C -f -h -o -W不会传递
/：make带-w或--print-directory会在执行过程中输出进入和退出的目录，当使用-C时，-w会自动加上，当使用-s时，-w总是失效
/：命令包(规则命令集合)  define开始endef结束
如：define run-yacc  (注意要加TAB键)
		yacc $(firstword $^)
		mv y.tab.c $@
	endef
调用  foo.c:foo.y
	  $(run-yacc)
$^：所有规则依赖的集合，以空格分隔
$@：规则目标集，如果规则目标是以模式(%)定义的，则$@将是符合模式的文件集，不过是一个一个取出的
$<：规则依赖中的第一个依赖，如果规则依赖是以模式(%)定义的，则$<将是符合模式的文件集，不过是一个一个取出的
/:Makefile中定义的变量代表一个文本字串，在使用的地方会原模原样的展开，变量可以使用在规则目标、规则依赖、规则命令或则其他地方(如新的变量)
/：变量可包含字符、数字、下划线，数字可以作为开头，变量大小写敏感
/：变量声明时需给初值，使用时加$符号，最好用()或者{}包起变量，$$表示真实的$符号
/：变量的值可以使用其他变量来构造，有两种方法定义变量的值
    变量=变量的值,等号左侧是变量，右侧是变量的值，右侧变量的值可以定义在文件的任何一处
    变量:=变量的值,其中变量的值只能使用前面定义变量的值
	变量?=值,如果变量没被定义过，这定义，如定义过，则什么也不做
	变量+=值,给变量追加值
如果+=左边变量之前没定义过，+=会变成=，如果前一次是:=则+=会变成:= .
/：系统变量MAKELEVEL,这个变量记录我们当前Makefile的调用层次
/：变量的2种高级用法1：变量值的交换
可以替换变量中的共有部分，格式为$(var:a=b)或${var:a=b},将var变量中以a结尾(空格或者结束符)的a替换成b;
	如：foo := a.o b.o c.o      bar := $(foo:.o=.c)  则bar值为a.c b.c c.c
另外一种变量替换的技术是以"静态模式"定义的
	如：foo := a.o b.o c.o      bar := $(foo:%.o=%.c)
/：变量的2种高级用法2：把变量值再当成变量(可以使用很多变量来组成一个变量的名字，再取其值)
	如：x=y
		y=z
		a:=$($(X))  -->a:=$(y)    a:=z
这种方法可以用在操作符的左边和右边
/：也可以用define和endef定义多行变量，跟=操作符一样
/：make运行时系统环境变量会载入到Makefile中，如果Makefile中定义了这个变量，或则这个变量由make 命令行带入，则系统环境变量不起作用，make指定-e,Makefile中定义的变量无效
不推荐将许多变量定义在系统环境中
/:前面的定义的变量是全局变量，$@等变量是规则型变量，我们可以为某个目标设置局部变量，可与全局变量重名，作用范围只在这个目标规则链中
语法：<target ..> : <variable-assignment>
/:模式变量，模式变量跟上面的目标变量一样，只不过，目标变量给定了目标，模式变量是指给定目标的通式，符合这个同事的目标都行
语法：<pattern ..> :<variable-assignment>

/:make中的条件判断，条件表达式可以比较变量的值，变量与常量的值,make 函数
语法:<conditional-directive>   //有四个ifeq  ifneq  ifdef  ifndef  
	 <text-if-true>
	 else
	 <text-if-false>
	 endif

	 ifdef和ifndef <variable-name> 同样可以是函数的返回值

/：函数的调用语法
$(<function> <arguments>)  或者  ${<function> <arguments>}
函数名与参数用空格分开，参数之间用逗号分开，参数可以使用变量
/：字符串处理函数
$(subst <from>,<to>,<text>)  		//test中的from字符串替换成to，返回替换后的字符串
$(subst ee,EE,feet on the street)   //返回fEEt on the strEEt

$(patsubst <pattern>,<replacement>,<text>)//查找test中的单词，符合pattern模式则用replacement替换掉
$(patsubst %.c,%.o,x.c.c bar.c) 	//返回x.c.o bar.o
注意等同于：object=x.c.c bar.c   $(object:.c=.o)或者(object:%.c=%.o)

$(strip <string>)   				//去掉string字符串中 开头 和 结尾 的空字符
$(strip a b  c  )					//返回abc

$(findstring <find>,<test>)			//在test中查找find字串，找到返回find，否则返回空字符
$(findstring a,a b  c )  			//返回a

$(filter <pattern..>,<test>) 		//将test中的字符串只留下符合模式的单词，可以有多个模式
sources := foo.c bar.c baz.s ugh.h
$(filter %.c %.s,$(sources))		//返回值为foo.c bar.c baz.s

$(filter-out <pattern..>,<test>)    //同上，反过来

$(sort <list>)						//将list中的单词排序(升序)，返回排序后的字串
$(sort foo bar lose)				//返回bar foo lose  (会去掉list中相同的单词)

$(word <n>,<text>)					//取字符串text中的第n个单词,第一个单词序号为1
$(word 2,foo bar baz)				//返回bar

$(wordlist <n>,<m>,<text>)			//从text中取出第n到m的单词
$(word 2,4,foo bar baz loop tes) 	//返回bar baz loop

$(words <test>)						//统计test中单词的个数
$(words foot feet fout)				//返回3

$(firstword <test>)					//取test中的第一个单词
$(firstword foo bar)				//返回foo

/：文件名操作函数
$(dir <name...>)					//从文件名中取出目录部分
$(dir src/foo.c hacks)				//返回src/ ./

$(notdir <name...>)					//从文件名中取出非目录部分
$(notdir src/foo.c hacks)			//返回foo.c hacks

$(suffix <name...>)					//从文件名中取出文件名的后缀
$(suffix src/foo.c hacks)			//返回.c

$(basename <name...>)				//从文件名中取出文件名的前缀
$(basename src/foo.c hacks)			//返回src/foo hacks

$(addsuffix <suffix>,<name...>)		//把suffix加到每个单词的后面
$(addsuffix .c,foo bar)				//返回foo.c bar.c

$(addprefix <prefix>,<name...>)		//把prefix加到每个单词的前面
$(addprefix src/,foo bar)			//返回src/foo src/bar

$(join <list_1>,<list_2>)			//将list_2中的单词加到list_1后面
$(join aaa bbb,111 222 333)			//返回值aaa111 bbb222 333

/:重点函数
$(foreach <var>,<list>,<text>)      //逐一取出list(序列)中的单词，放到var(变量名)中，执行text表达式
name :=a b c d
$(foreach n,$(name),$(n).o)			//返回a.o b.o c.o d.o     注意，n变量是局部的，作用域只在foreach函数中

$(if <condition>,<then-part>)  或
$(if <condition>,<then-part>,<else-part> //如果表达式返回非空字符串，则为真

$(call <expression>,<parm1>,<parm2>,...)//自定义表达式expression
reverse = $(1),$(2)
foo = $(call reverse,a,b)			//返回a b

$(origin <variable>)				//variable是变量的名字，不是引用，返回这个变量的"出生情况"
undefined	变量没被定义过
default		默认的定义
file		在Makefile中定义
command line命令行定义的
override	被override重新定义
automatic	自动化变量

$(shell shell命令)					//返回命令的结果
$(shell cat foo)

/:控制make的函数
$(error <text ...>)					//产生一个致命的错误，退出make,错误信息为text ...
$(error found an error!)

$(warning <text ...>)				//产生一个警告信息，不退出make,警告信息为text ...
$(warning found an warnning)

/:makefile中的目标都可以制定为终极目标，但以 - 打头或包含 = 的目标

/:检查调试规则的一些参数
-n不执行参数，只打印命令

/:-C <dir>指定读取makefile的目录
-debug输出make的调试信息
-e 指明环境变量的值覆盖makefile中定义的值
-i 执行时忽略所有错误
-I 制定搜索目录
-r 禁止make使用任何隐含规则
-s 全面禁止命令的输出

/:make中的隐含规则
隐含规则可能使用一些预先设置的变量,可以在Makefile中改变这些变量的值，命令行传入这些值，环境变量中设置这些值
使用隐含规则生成需要的目标，所要做的就是不要写出这个规则，make会自动推导规则的依赖和命令

/：规则目标为<n>.o会自动推导规则依赖为<n>.c ,规则命令为$(CC) -c $(CPPFLAGS) $(CFLAGS)
/：隐含规则命令相关的变量
CC
/:关于规则命令参数变量
CFLAGS



/:模式规则就是指一个一般的规则，模式规则中规则目标或者规则依赖定义需要%，规则依赖%的取值取决于规则目标中的%

%.o:%.c
$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
$@:所有规则目标逐个取出
$<:所有规则依赖逐个取出






