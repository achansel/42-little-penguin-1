# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achansel <achansel@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 22:35:12 by achansel          #+#    #+#              #
#    Updated: 2023/02/08 20:21:44 by achansel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# If KERNELRELEASE is defined, we've been invoked from the kernel build system
# and can use its language
ifneq ($(KERNELRELEASE),)
	obj-m := dfsmodule.o
	dfsmodule-objs := src/debugfs_module.o src/id_file.o src/foo_file.o

# We need to invoke kernel build system ourselves
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

fclean: clean

.PHONY: clean fclean all

endif

