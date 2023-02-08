# Little penguin 1
[![Generic badge](https://img.shields.io/static/v1?label=Skills&message=C%2C%20Linux%2C%20Kernel&color=red&style=for-the-badge)](https://shields.io/)
[![achansel's 42 little-penguin-1 Score](https://badge42.vercel.app/api/v2/cl23cxs1j002509mbpg1bd1bu/project/2943565)](https://github.com/JaeSeoKim/badge42)
#### This projet, the 2nd project in the Kernel/Low-level specialization of 42 school, is a series of challenges inspired by [Eudyptula](http://eudyptula-challenge.org/).

It is an opportunity to get acquainted with many points of Kernel development.
The code in this project will be run on the first project of the specialization, ft_linux, an [LFS](https://www.linuxfromscratch.org/) system.

## Assignements
### ex00:
**Instructions**:
  - Download Linus' latest git tree from git.kernel.org, build, compile and boot it.
  - Enable CONFIG_LOCALVERSION_AUTO=y

**Turn-in**:
  - [Kernel boot log](ex00/boot.log)
  - [Kernel config file](ex00/config)
  
**What I did**:
- I used `make menuconfig` to generate a config file, then I compiled it and moved the bzImage to my boot partition.
- After booting it using grub, I ran the command `dmesg` in order to obtain the logfile.

----------

### ex01:
**Instructions**:
  - Build a "Hello World module" that outputs specific messages on load and unload.
  - It must compile on any system

**Turn-in**:
  - [Makefile](ex01/Makefile)
  - [Code](ex01/module.c)
 
**What I did**:
  - I used *Linux Device Drivers 3rd Edition, Chapter 02* to learn about the basics of kernel module creation.
  - I used init and exit functions to output what was asked.

----------

### ex02:
**Instructions**:
  - Take the same kernel git tree as in ex00 and modify it to have -thor_kernel in the version string
  - Make a patch for the change, it has to be compliant with Linux standards

**Turn-in**:
  - [Kernel boot log](ex02/boot.log)
  - [Makefile patch](ex02/0001-Added-thor_kernel-in-version-string.patch)
 
**What I did**:
  - I modified the variable EXTRAVERSION in the Makefile, as it was asked
  - I read the [documentation](https://www.kernel.org/doc/html/v4.17/process/submitting-patches.html) on kernel.org
  
----------

### ex03:
**Instructions**:
  - Take a given file and and modify it to match the [Linux coding style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html)

**Turn-in**:
  - [The compliant file](ex03/norme.patch)
 
**What I did**:
  - I applied the coding style on the given file using the documentation.
  - I generated a patch of the original file using the `diff` command, as, in my humble opinion, it makes it easier to see the changes.
  
 ----------

### ex04:
**Instructions**:
  - Take the kernel module written for [ex01](ex01/) and modify it so that when any USB keyboard is plugged in, the module will be automatically loaded
  - Write a rules file for hotplug userspace tools, if needed.

**Turn-in**:
  - [Kernel module source](ex04/keyboard_dd.c)
  - [Makefile](ex04/Makefile)
  - [The rules file for udev](ex04/69-keyboard.rules)
  - [The proof](ex04/proof.log)
 
**What I did**:
  - I read *Linux Device Drivers 3rd Edition, Chapter 14* to learn about hotplugging.
  - I read [USB HID Documentation](https://www.usb.org/sites/default/files/hid1_11.pdf) to figure out how to recognize a USB Keyboard (bInterfaceProtocol).
  - I used both of these references and local udev rules on my system to write this udev rule.



