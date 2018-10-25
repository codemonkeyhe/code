#单纯的make 不会有并发问题
#make -j8就会有并发问题，all依赖的foo1-foo8可能同时执行
#但是 all本身的命令一定是最后执行,并且是等待foo3的sleep3之后才执行
# make -j1 一定会阻塞3秒
# make -j2 只有一路会阻塞
# make -j3 只有一路会阻塞

.PHONY: foo1 foo2 foo3 foo4 foo5 foo6 foo7 foo8


all: foo1 foo2 foo3 foo4 foo5 foo6 foo7 foo8
	@echo "all"

foo1:
	@echo "foo1"

foo2:
	@echo "foo2"

foo3:
	sleep 3
	@echo "foo3"

foo4:
	@echo "foo4"

foo5:
	@echo "foo5"

foo6:
	@echo "foo6"

foo7:
	@echo "foo7"

foo8:
	@echo "foo8"

