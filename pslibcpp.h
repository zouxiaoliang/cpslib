#ifndef PSLIBCPP_H
#define PSLIBCPP_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <string>
#include <list>

namespace psutil {

enum proc_status {
    STATUS_RUNNING,
    STATUS_SLEEPING,
    STATUS_DISK_SLEEP,
    STATUS_STOPPED,
    STATUS_TRACING_STOP,
    STATUS_ZOMBIE,
    STATUS_DEAD,
    STATUS_WAKE_KILL,
    STATUS_WAKING,
    STATUS_IDLE,
    STATUS_LOCKED,
    STATUS_WAITING
};

enum ioprio_class {
    IOPRIO_CLASS_NONE,
    IOPRIO_CLASS_RT,
    IOPRIO_CLASS_BE,
    IOPRIO_CLASS_IDLE
};

/*enum rlimit {
  RLIMIT_INFINITY,
  RLIMIT_AS,
  RLIMIT_CORE,
  RLIMIT_CPU,
  RLIMIT_DATA,
  RLIMIT_FSIZE,
  RLIMIT_LOCKS,
  RLIMIT_MEMLOCK,
  RLIMIT_MSGQUEUE,
  RLIMIT_NICE,
  RLIMIT_NOFILE,
  RLIMIT_NPROC,
  RLIMIT_RSS,
  RLIMIT_RTPRIO,
  RLIMIT_RTTIME,
  RLIMIT_SIGPENDING,
  RLIMIT_STACK
};*/

enum con_status {
    ESTABLISHED,
    SYN_SENT,
    SYN_RECV,
    FIN_WAIT1,
    FIN_WAIT2,
    TIME_WAIT,
    CLOSE,
    CLOSE_WAIT,
    LAST_ACK,
    LISTEN,
    CLOSING,
    NONE,
    DELETE_TCB,
    IDLE,
    BOUND
};

enum proc_priority {
    ABOVE_NORMAL_PRIORITY_CLASS,
    BELOW_NORMAL_PRIORITY_CLASS,
    HIGH_PRIORITY_CLASS,
    IDLE_PRIORITY_CLASS,
    NORMAL_PRIORITY_CLASS,
    REALTIME_PRIORITY_CLASS
};

typedef struct {
    uint64_t total;
    uint64_t used;
    uint64_t free;
    float percent;
} DiskUsage;

typedef struct {
    std::string device;
    std::string mountpoint;
    std::string fstype;
    std::string opts;
} DiskPartition; /* TODO: Pluralise */

typedef struct {
    uint32_t nitems;
    DiskPartition *partitions;
} DiskPartitionInfo;

typedef struct {
    std::string name;
    uint64_t readbytes;
    uint64_t writebytes;
    uint64_t reads;
    uint64_t writes;
    uint64_t readtime;
    uint64_t writetime;
} DiskIOCounters;

typedef struct {
    uint32_t nitems;
    DiskIOCounters *iocounters;
} DiskIOCounterInfo;

typedef struct {
    std::string name;
    uint64_t bytes_sent;
    uint64_t bytes_recv;
    uint64_t packets_sent;
    uint64_t packets_recv;
    uint64_t errin;
    uint64_t errout;
    uint64_t dropin;
    uint64_t dropout;
} NetIOCounters;

typedef struct {
    uint32_t nitems;
    NetIOCounters *iocounters;
} NetIOCounterInfo;

typedef struct {
    std::string username;
    std::string tty;
    std::string hostname;
    float tstamp;
} Users;

typedef struct {
    uint32_t nitems;
    Users *users;
} UsersInfo;

typedef struct {
    uint64_t total;
    uint64_t available;
    float percent;
    uint64_t used;
    uint64_t free;
    uint64_t active;
    uint64_t inactive;
    uint64_t buffers;
    uint64_t cached;
    uint64_t wired;
} VmemInfo;

typedef struct {
    uint64_t total;
    uint64_t used;
    uint64_t free;
    float percent;
    uint64_t sin;
    uint64_t sout;
} SwapMemInfo;

typedef struct {
    double user;
    double system;
    double idle;
    double nice;
    double iowait;
    double irq;
    double softirq;
    double steal;
    double guest;
    double guest_nice;
} CpuTimes;

typedef struct {
    pid_t pid;
    pid_t ppid;
    std::string name;
    std::string exe;
    std::string cmdline;
    double create_time;
    uint32_t uid;
    uint32_t euid;
    uint32_t suid;
    uint32_t gid;
    uint32_t egid;
    uint32_t sgid;
    std::string username;
    std::string terminal;
} Process;

bool disk_usage(const char[], DiskUsage *);

bool disk_partitions(bool, DiskPartitionInfo&);

bool disk_io_counters(DiskIOCounterInfo &);

bool net_io_counters(NetIOCounterInfo &);

bool get_users(UsersInfo &);

uint32_t get_boot_time(void);

bool virtual_memory(VmemInfo &);

bool swap_memory(SwapMemInfo &);

bool cpu_times(bool, CpuTimes&);

CpuTimes *cpu_times_percent(bool, CpuTimes *);

bool cpu_util_percent(bool percpu, CpuTimes &prev_times, std::list<double> &);

uint32_t cpu_count(bool);

bool pid_exists(pid_t);

bool get_process(pid_t, Process &);

/* Required to avoid [-Wimplicit-function-declaration] for python bindings */
void gcov_flush(void);

// disk_io_counters_per_disk
// net_io_counters_per_nic

}

#endif // PSLIBCPP_H
