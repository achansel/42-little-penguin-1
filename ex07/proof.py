# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    proof.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achansel <achansel@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 22:28:19 by achansel          #+#    #+#              #
#    Updated: 2023/02/08 22:28:25 by achansel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import time
import mmap
import os
import random


#
# Since this file is not very clear, this comment will be an attempt to explain it
#
# functions:
# - log_status(): just prints if a test passed and increments the test number
#
# - file(): opens the tested file and closes the old one, it is used because a lot of times
#   we want to reset the cursor of the file, which is not doable with seek() since it is not asked to implement it in the driver.
#
# - read_test(): check for equality of res and expected and prints the test result using log_status 
#
# - write_test(): tries to write and according to the parameter should_work, prints the test results
#
# globals:
# - no: current test id
# - PATH: current tested file PATH
# - old: the last file opened by the function file()
#
# other:
#  buffering=0: disables buffering so we get the exception instantly on writes and reads

no = 1
def log_status(t, good):
    global no
    status = '\033[0;32m\033[1mPassed\033[0m' if good else '\033[0;31m\033[1mFailure\033[0m'
    print(f"{no}-{t}: {status}")
    no += 1

PATH = ""
old = None
def file():
    global old
    if old:
        old.close()
    old = open(PATH, "wb+", buffering=0)
    return old

def read_test(t, res, expected):
    log_status(t, res == expected);

def write_test(t, data, should_work):
    try:
        file().write(data)
        log_status(t, should_work)
    except OSError:
        log_status(t, not should_work)

def main():
    global PATH

    #
    # FOO FILE TESTS
    #
    PATH="/sys/kernel/debug/fortytwo/foo"
    print(f"\n**** {PATH} TESTS ****")

    write_test("Max write", b"t"*mmap.PAGESIZE, True)
    read_test("Max write read", file().read(), b"t"*mmap.PAGESIZE)

    write_test("Max write + 1", b"t"*(mmap.PAGESIZE + 1), False)
    read_test("Max write + 1 read", file().read(), b"t"*mmap.PAGESIZE)

    write_test("Write of len 0", b"", True)
    read_test("Len 0 write read", file().read(), b"")

    for i in range(5):
        s = os.urandom(random.randrange(4096))
        write_test("Random write", s, True)
        read_test("Random read", file().read(), s)

    #
    # JIFFIES FILE TESTS
    # Read it 10 times and check if time is always >, after try to write to it and ensure it fails
    #
    PATH="/sys/kernel/debug/fortytwo/jiffies"
    print(f"\n**** {PATH} TESTS ****")

    old = 0
    for i in range(10):
        f = open(PATH, "r")
        new = int(f.read()[:-1], 10)
        if new <= old:
            log_status("Jiffies read", False)
        else:
            old = new
        log_status("Jiffies read", True)
        f.close()
        time.sleep(0.100)
    write_test("Jiffies write", b"test", False)

    #
    # ID FILE TESTS
    #
    PATH="/sys/kernel/debug/fortytwo/id"
    print(f"\n**** {PATH} TESTS ****")
    with open(PATH, "rb+", buffering=0) as g:
        read_test("Read", g.read(1024), b"achansel")
    write_test("Different write", b"inval", False)
    write_test("Different write same len", b"invalid!", False)
    write_test("Good write", b"achansel", True)

if __name__ == "__main__":
    main()
