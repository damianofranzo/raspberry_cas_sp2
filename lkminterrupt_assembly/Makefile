obj-m := ISRgpiointerrupts.o
kv=$(shell uname -r)
path=$(shell pwd)
all:
	make -C /lib/modules/$(kv)/build M=$(path) modules
clean:
	make -C /lib/modules/$(kv)/build M=$(path) clean
