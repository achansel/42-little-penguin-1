no = 1

def log_status(t, good):
    global no
    print(f"{no}-{t}: {'Passed' if good else 'Failure'}")
    no += 1

def read_test(t, res, expected):
    log_status(t, res == expected);


# Do not buffer the file so we can directly receive write result
with open("/dev/fortytwo", "rb+", buffering=0) as device:
    print("**** /dev/fortytwo TESTS ****")

    # test 1
    read_test("Read", device.read(1024), b"achansel")
    
    # test 2
    try:
        device.write(b"inval");
        log_status("Different write 1", False)
    except OSError:
        log_status("Different write 1", True)

    # test 3
    try:
        device.write(b"invalid!");
        log_status("Different write 2", False)
    except OSError:
        log_status("Different write 2", True)

    # test 4
    try:
        device.write(b"achansel");
        log_status("Good write", True)
    except OSError:
        log_status("Good write", False)
        
