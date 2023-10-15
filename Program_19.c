/*
============================================================================
Name : Program 19
Author : Hari Prasad C
Description : Create a FIFO file by
                1) mknod command
                2) mkfifo command
                3) use strace command to find out, which command (mknod or mkfifo) is better.
                4) mknod system call
                5) mkfifo library function
Date: 4th Oct, 2023.
============================================================================
*/

// using mknod command  : mknod -m 0666 mypipe p
// using mkfifo command : mkfifo -m 0666 mypipe

/*
// using strace for command mknod :
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ strace -c mknod -m 0666 mypipe p
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 31.62    0.000983          54        18           mmap
 25.60    0.000796         796         1           execve
  7.59    0.000236          33         7           openat
  5.85    0.000182          30         6           mprotect
  4.08    0.000127          18         7           newfstatat
  3.96    0.000123          13         9           close
  3.60    0.000112          22         5           read
  3.25    0.000101         101         1           mknodat
  2.61    0.000081          81         1           chmod
  2.35    0.000073          18         4           pread64
  1.74    0.000054          54         1           munmap
  1.51    0.000047          23         2         2 access
  1.51    0.000047          23         2         2 statfs
  1.19    0.000037          12         3           brk
  0.87    0.000027          13         2         1 arch_prctl
  0.61    0.000019          19         1           set_robust_list
  0.58    0.000018           9         2           umask
  0.48    0.000015          15         1           set_tid_address
  0.35    0.000011          11         1           getrandom
  0.32    0.000010          10         1           prlimit64
  0.32    0.000010          10         1           rseq
------ ----------- ----------- --------- --------- ----------------
100.00    0.003109          40        76         5 total

// using strace for command mkfifo :
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 27.73    0.000652         652         1           execve
 24.97    0.000587          32        18           mmap
  6.59    0.000155          22         7           openat
  6.25    0.000147          24         6           mprotect
  4.89    0.000115         115         1           mknodat
  4.21    0.000099          14         7           newfstatat
  4.17    0.000098          10         9           close
  3.74    0.000088          17         5           read
  3.32    0.000078          78         1           chmod
  2.34    0.000055          18         3           brk
  2.00    0.000047          23         2         2 access
  1.83    0.000043          43         1           munmap
  1.79    0.000042          21         2         1 arch_prctl
  1.70    0.000040          20         2         2 statfs
  1.53    0.000036           9         4           pread64
  0.89    0.000021          10         2           umask
  0.47    0.000011          11         1           getrandom
  0.43    0.000010          10         1           prlimit64
  0.38    0.000009           9         1           set_tid_address
  0.38    0.000009           9         1           set_robust_list
  0.38    0.000009           9         1           rseq
------ ----------- ----------- --------- --------- ----------------
100.00    0.002351          30        76         5 total

// mkfifo is better

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    if ( argc <= 2 ) {
        printf("Execute with required paramenters\n./Executable pipe1_name pipe2_name\n");
        return 0;
    }
    // using mknod system call to create named pipe
    if ( -1 == mknod(argv[1], __S_IFIFO | S_IRWXU, 0)) {
        perror ("mknode error");
        return -1;
    }

    // using mkfifo system call to create named pipe
    if ( -1 == mkfifo(argv[2], S_IRWXU)) {
        perror ("mkfifo error");
        return -1;
    }

    return 0;
}