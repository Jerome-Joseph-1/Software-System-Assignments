/*
============================================================================
Name : 2.c
Author : Jerome Joseph
Description : Write a simple program to execute in an infinite loop at the background. Go to /proc directory and
identify all the process related information in the corresponding proc directory.
Date: 31st Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = getpid();

printf("PID: %d\n", pid);                       
    while(1);
}

/*
❯ ./main                                                                ─╯
PID: 77252

❯ cd /proc/77252                                                                                                   ─╯

❯ cat status                                                                                                       ─╯
Name:   main
Umask:  0022
State:  R (running)
Tgid:   77252
Ngid:   0
Pid:    77252
PPid:   2651
TracerPid:      0
Uid:    1000    1000    1000    1000
Gid:    1000    1000    1000    1000
FDSize: 128
Groups: 3 108 981 998 1000 
NStgid: 77252
NSpid:  77252
NSpgid: 77252
NSsid:  2651
Kthread:        0
VmPeak:     2588 kB
VmSize:     2540 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:      1448 kB
VmRSS:      1448 kB
RssAnon:               0 kB
RssFile:            1448 kB
RssShmem:              0 kB
VmData:      204 kB
VmStk:       132 kB
VmExe:         4 kB
VmLib:      1648 kB
VmPTE:        48 kB
VmSwap:        0 kB
HugetlbPages:          0 kB
CoreDumping:    0
THP_enabled:    1
untag_mask:     0xffffffffffffffff
Threads:        1
SigQ:   1/125553
SigPnd: 0000000000000000
ShdPnd: 0000000000000000
SigBlk: 0000000000000000
SigIgn: 0000000000000000
SigCgt: 0000000000000000
CapInh: 0000000000000000
CapPrm: 0000000000000000
CapEff: 0000000000000000
CapBnd: 000001ffffffffff
CapAmb: 0000000000000000
NoNewPrivs:     0
Seccomp:        0
Seccomp_filters:        0
Speculation_Store_Bypass:       thread vulnerable
SpeculationIndirectBranch:      conditional enabled
Cpus_allowed:   fff
Cpus_allowed_list:      0-11
Mems_allowed:   00000001
Mems_allowed_list:      0
voluntary_ctxt_switches:        0
nonvoluntary_ctxt_switches:     138805
x86_Thread_features:
x86_Thread_features_locked:      
*/
