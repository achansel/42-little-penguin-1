# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achansel <achansel@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 22:35:12 by achansel          #+#    #+#              #
#    Updated: 2023/02/08 03:24:54 by achansel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# If KERNELRELEASE is defined, we've been invoked from the kernel build system
# and can use its language
ifneq ($(KERNELRELEASE),)
	obj-m := keyboard_dd.o

# We need to invoke kernel build system ourselves
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

fclean: clean
	rm -f keyboard_dd.ko

.PHONY: clean fclean all

endif

