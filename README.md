# Extend Mini Library C to handle Signal
## Introduction
In this program, it extends the mini C library to support signal relevant system calls. It implements the following C library functions shown at Explanation session in Assembly and C using the syntax supported by yasm x86_64 assembler.

## Execution
### Write1
```console
$ make && make write1 
$ LD_LIBRARY_PATH=. ./write1
```
### Alarm1
```console
$ make && make alarm1
$ LD_LIBRARY_PATH=. ./alarm1
```

### Alarm2
```console
$ make && make alarm2
$ LD_LIBRARY_PATH=. ./alarm2
```

### Alarm3
```console
$ make && make alarm3
$ LD_LIBRARY_PATH=. ./alarm3
```

### Jmp1
```console
$ make && make jmp1 
$ LD_LIBRARY_PATH=. ./jmp1
```

## Explanation
* **setjmp**: Prepare for long jump by saving the current CPU state. In addition, preserve the signal mask of the current process.
* **longjmp**: Perform the long jump by restoring a saved CPU state. In addition, restore the preserved signal mask.
* **signal** and **sigaction**: Setup the handler of a signal.
* **sigprocmask**: Can be used to block or unblock signals, and get or set the current signal mask.
* **sigpending**: Check if there is any pending signal.
* **alarm**: Setup a timer for the current process.
* **write**: Write to a file descriptor.
* **pause**: Wait for signal.
* **sleep**: Sleep for a specified number of seconds.
* **exit**: Cause normal process termination.
* **strlen**: Calculate the length of the string, excluding the terminating null byte ('\0').
* Functions to handle sigset_t data type: **sigemptyset**, **sigfillset**, **sigaddset**, **sigdelset**, and **sigismember**.