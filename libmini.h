#ifndef __LIBMINI_H__
#define __LIBMINI_H__   // avoid reentrant

#define _NSIG       64
#define _NSIG_BPW   64
#define _NSIG_WORDS (_NSIG / _NSIG_BPW)

typedef int         pid_t;
typedef int         uid_t;
typedef long long   size_t;
typedef long long   ssize_t;
typedef int         clock_t;
typedef char        jmp_buf[1];
typedef void        (*sighandler_t)(int);

typedef union sigval {
    int     sival_int;
    void*   sival_ptr;
} sigval_t;
typedef struct sigset_t { 
    unsigned int sig[_NSIG_WORDS];
} sigset_t;
typedef struct siginfo_t {
    int             si_signo;       // Signal Number
    int             si_errno;       // An errno value
    int             si_code;        // Signal code
    int             si_trapno;      // Trap number that caused hardware-generated signal (unused on most architectures)
    pid_t           si_pid;         // Sending process ID
    uid_t           si_uid;         // Real user ID of sending process
    int             si_status;      // Exit value or signal
    clock_t         si_utime;       // User time consumed
    clock_t         si_stime;       // System time consumed
    sigval_t        si_value;       // Signal value
    int             si_int;         // POSIX.1b signal
    void*           si_ptr;         // POSIX.1b signal
    int             si_overrun;     // Timer overrun count; POSIX.1b timers
    int             si_timerid;     // Timer ID; POSIX.1b timers
    void*           si_addr;        // Memory location which caused fault
    long            si_band;        // Band event (was `int` in glibc 2.3.2 and earlier)
    int             si_fd;          // File descriptor
    short           si_addr_lsb;    // Least significant bit of address (since Linux 2.6.32)
    void*           si_lower;       // Lower bound when address violation occurred (since Linux 3.19)
    void*           si_upper;       // Upper bound when address violation occurred (since Linux 3.19)
    int             si_pkey;        // Protection key on PIE that caused fault (since Linux 4.6)
    void*           si_call_addr;   // Address of system call instruction (since Linux 3.5)
    int             si_syscall;     // Number of attempted system call (since Linux 3.5)
    unsigned int    si_arch;        // Architecture of attempted system call (since Linux 3.5)
} siginfo_t;

extern long errno;

#define NULL        ((void *) 0)

// from /usr/lnclude/asm-generic/fcntl.h
#define O_ACCCMODE  00000003
#define O_RDONLY    00000000
#define O_WRONLY    00000001
#define O_RDWR      00000002
#ifndef O_CREAT
#define O_CREAT     00000100    // not fcntl
#endif
#ifndef O_EXCL
#define O_EXCL      00000200    // not fcntl
#endif
#ifndef O_NOCTTY
#define O_NOCTTY    00000400    // not fcntl
#endif
#ifndef O_TRUNC
#define O_TRUNC     00001000    // not fcntl
#endif
#ifndef O_APPEND
#define O_APPEND    00002000
#endif
#ifndef O_NONBLOCK
#define O_NONBLOCK  00004000
#endif
#ifndef O_DSYNC
#define O_DSYNC     00010000    // used to be O_SYNC, see below
#endif
#ifndef FASYNC
#define FASYNC      00020000    // fcntl, for BSD compatibility
#endif
#ifndef O_DIRECT
#define O_DIRECT    00040000    // direct disk access hint
#endif
#ifndef O_LARGEFILE
#define O_LARGEFILE 00100000
#endif
#ifndef O_DIRECTORY
#define O_DIRECTORY 00200000    // must be a directory
#endif 
#ifndef O_NOFOLLOW
#define O_NOFOLLOW  00400000    // don't follow this
#endif
#ifndef O_NOATIME
#define O_NOATIME   01000000
#endif
#ifndef O_CLOEXEC
#define O_CLOEXEC   02000000    // set close_on_exec
#endif

// from /usr/include/asm-generic/errno-base.h
#define EPERM   1   // Operation not permitted
#define ENOENT  2   // No such file or directory
#define ESRCH   3   // No such process
#define EINTR   4   // Interrupted system call
#define EIO     5   // I/O error
#define ENXIO   6   // No such device or address
#define E2BIG   7   // Argument list too long
#define ENOEXEC 8   // Exec format error
#define EBADF   9   // Bad file number
#define ECHILD  10  // No child processes
#define EAGAIN  11  // Try again
#define ENOMEM  12  // Out of memory
#define EACCES  13  // Permission denied
#define EFAULT  14  // Bad address
#define ENOTBLK 15  // Block device required
#define EBUSY   16  // Device or resource busy
#define EEXIST  17  // File exist
#define EXDEV   18  // Cross-device link
#define ENODEV  19  // No such device
#define ENOTDIR 20  // Not a directory
#define EISDIR  21  // Is a directory
#define EINVAL  22  // Invalid argument
#define ENFILE  23  // File table overflow
#define EMFILE  24  // Too many open files
#define ENOTTY  25  // Not a typewriter
#define ETXTBSY 26  // Text file busy
#define EFBIG   27  // File too large
#define ENOSPC  28  // No space left on device
#define ESPIPE  29  // Illegal seek
#define EROFS   30  // Read-only file system
#define EMLINK  31  // Too many links
#define EPIPE   32  // Broken pipe
#define EDOM    33  // Math argument out of domain of func
#define ERANGE  34  // Math result not representable

// from /usr/include/x86_64-linux-gnu/asm/signal.h
#define SIGHUP      1
#define SIGINT      2
#define SIGQUIT     3
#define SIGILL      4
#define SIGTRAP     5
#define SIGABRT     6
#define SIGIOT      6
#define SIGBUS      7
#define SIGFPE      8
#define SIGKILL     9
#define SIGUSR1     10
#define SIGSEGV     11
#define SIGUSR2     12
#define SIGPIPE     13
#define SIGALRM     14
#define SIGTERM     15
#define SIGSTKFLT   16
#define SIGCHLD     17
#define SIGCONT     18
#define SIGSTOP     19
#define SIGTSTP     20
#define SIGTTIN     21
#define SIGTTOU     22
#define SIGURG      23
#define SIGXCPU     24
#define SIGXFSZ     25
#define SIGVTALRM   26
#define SIGPROF     27
#define SIGWINCH    28
#define SIGIO       29
#define SIGPOLL     SIGIO
#define SIGPWR      30
#define SIGSYS      31
#define SIGUNUSED   31

// from /usr/include/x86-64-linux-gnu/bits/sigaction.h
#define SA_NOCLDSTOP    1           // Don't send SIGCHLD when children stop.
#define SA_NOCLDWAIT    2           // Don't create zombie on child death.
#define SA_SIGINFO      4           // Invoke signal-catching function with three arguments instead of one.

#define SA_ONSTACK      0x08000000  // Use signal stack by using `sa_restorer`.
#define SA_RESTART      0x10000000  // Restart syscall on signal return.
#define SA_INTERRUPT    0x20000000  // Historical no-op.
#define SA_NODEFER      0x40000000  // Don't automatically block the signal when its handleris being executed.
#define SA_RESETHAND    0x80000000  // Reset to SIG_DEL on entry to handler

#define SIG_BLOCK       0           // Block signals.
#define SIG_UNBLOCK     1           // Unblock signals
#define SIG_SETMASK     2           // Set the set of blocked signals.

#define SIG_ERR         (void (*)()) -1
#define SIG_DEL         (void (*)()) 0
#define SIG_IGN         (void (*)()) 1

struct timespec {
    long tv_sec;        // seconds
    long tv_nsec;       // nanoseconds
};

struct sigaction {
    void        (*sa_handler)(int);
    void        (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t    sa_masks;
    int         sa_flags;
    void        (*sa_restorer)(void);
};

// system calls
long sys_write(int fd, const void *buf, size_t count);
long sys_pause();
long sys_nanosleep(struct timespec *rqtp, struct timespec *rmtp);
long sys_alarm(unsigned int seconds);
long sys_exit(int error_code) __attribute__ ((noreturn));

// wrapper
ssize_t         write(int fd, const void *buf, size_t count);
int             pause();
unsigned int    alarm(unsigned int seconds);
void            exit(int error_code) __attribute__ ((noreturn));
void            bzero(void *s, size_t size);
size_t          strlen(const char *s);
void            perror(const char *prefix);
unsigned int    sleep(unsigned int s);
int             sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
int             sigismember(const sigset_t *set, int sig);
int             sigaddset(sigset_t *set, int sig);
int             sigdelset(sigset_t *set, int sig);
int             sigemptyset(sigset_t *set);
int             sigfillset(sigset_t *set);
int             sigpending(sigset_t *set);
int             sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
sighandler_t    signal(int signum, sighandler_t handler);
int             setjmp(jmp_buf env);
void            longjmp(jmp_buf env, int val);

#endif  // __LIBMINI_H__