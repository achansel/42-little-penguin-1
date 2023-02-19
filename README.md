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
  - [Compliant file](ex03/corrected.c)
 
**What I did**:
  - I applied the coding style on the given file using the documentation.

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


 ----------

### ex05:
**Instructions**:
  - Take the kernel module written for [ex01](ex01/) and modify it to be a misc char device driver.
  - Make it behave specifically on reads and writes and prove it.

**Turn-in**:
  - [Misc device driver](ex05/misc_device.c)
  - [Makefile](ex05/Makefile)
  - [Proof python3 script](ex05/proof.py)
 
**What I did**:
  - I read documentation online about misc device drivers.
  - I implemented my device using those resources.
  - I made a python script to test it quickly.

---------

### ex06:
**Instructions**:
  - Download the linux-next kernel, build it, compile it and boot it.

**Turn-in**:
  - [Kernel boot log](ex06/boot.log)
 
**What I did**:
  - I used `make defconfig` to quickly generate a config file, then I compiled it and moved the bzImage to my boot partition.
  - After booting it using grub, I ran the command `dmesg` in order to obtain the logfile.

---------

### ex07:
**Instructions**:
  - Write a kernel module that uses debugfs
  - You have to create a subdirectory in which you can find 3 special files handled by your driver.
  - They all must have specific access rights and behavior and you must prove it.

**Turn-in**:
  - [The module](ex07)
  - [Proof python3 script](ex07/proof.py)
 
**What I did**:
  - I read kernel documentation to learn about [debugfs](https://docs.kernel.org/filesystems/debugfs.html).
  - I also had to read about [synchronization primitives in kernel space](https://docs.kernel.org/locking/mutex-design.html) and [jiffies](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/include/linux/jiffies.h).
  - With the help of these resources and others I wrote the code to handle these 3 files.
  - Finally, in order to test everything, I took my proof script from ex05 and heavily modified it.

---------

### ex08:
**Instructions**:
  - Take a given file, fix the coding style, and fix the behaviour of the code.

**Turn-in**:
  - [Corrected file](ex08/corrected.c)
 
**What I did**:
  - I downloaded the file, I fixed the file and I tested it to check if it behaved correctly.

---------

### ex09:
**Instructions**:
 - Write a kernel module that exposes a file called mymounts on the root of the procfs.
 - It has to list mount points on the system and their associated names

**Turn-in**:
  - [The module](ex09)

**What I did**:
 - I read kernel documentation about [VFS](https://www.kernel.org/doc/html/latest/filesystems/vfs.html), [linked lists](https://www.oreilly.com/library/view/linux-device-drivers/0596000081/ch10s05.html), [mounts](https://www.oreilly.com/library/view/understanding-the-linux/0596002130/ch12s04.html), [namespaces](https://en.wikipedia.org/wiki/Linux_namespaces) and the [seq_file interface](https://www.kernel.org/doc/html/latest/filesystems/seq_file.html).
 - I used [strace](https://strace.io/) on `mount` binary to discover how filesystems were mounted and the needed syscalls.
 - I read [mount](https://elixir.bootlin.com/linux/v6.1.12/source/fs/namespace.c#L3568)/[umount](https://elixir.bootlin.com/linux/v6.1.12/source/fs/namespace.c#L1828) source code in an attempt to improve my understanding of what was going on.
 - Using those previous resources and the kernel headers, I tried to do it my own way, without success. My *working solution* used functions not [exported](https://lkw.readthedocs.io/en/latest/doc/04_exporting_symbols.html) for kernel modules.
 - I resigned myself to do it the way the kernel does it, by looking at the `/proc/mounts` file [implementation](https://elixir.bootlin.com/linux/v6.1.12/source/fs/proc_namespace.c#L101), which I fully understood thanks to my previous readings.
