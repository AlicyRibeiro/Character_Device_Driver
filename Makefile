obj-m += meu_driver_char.o

MODULES_DIR=${PWD}

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(MODULES_DIR) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(MODULES_DIR) clean

load:
	sudo insmod meu_driver.ko

remove:
	sudo rmmod meu_driver
