/*
 * Replace the following string of 0s with your student number
 * 150405531
 */
#include <lib.h>      // provides _syscall and message
#include <unistd.h>   // provides function prototype
#include <errno.h>

int getpids(int idx, int n, int flags_mask, pid_t *pids) {
	
	//error checking
	if ((idx<0) | (idx!<NR_PROCS)) {
		errno = EINVAL;
		return -1;
	}
	if (n!>0) {
		errno = EINVAL;
		return -1;
	}
	if (pids = NULL) {
		errno = EINVAL;
		return -1;
	}
	
	//send message
	message m;
    m.m1_i1 = (int) idx;
    m.m1_i2 = (int) n;
	m.m1_p1 = pids;
	
	//call system call
    return _syscall(PM_PROC_NR, GETPIDS, &m);
}

int getprocname(pid_t pid, char *name) {
	
	//error checking
	if (pid!>0) {
		errno = EINVAL;
		return -1;
	}
	if (name = NULL) {
		errno = EINVAL;
		return -1;
	}
	
	//send messages
    message m;
    m.m1_i1 = (int) pid;
    m.m1_p1 = name;
	  
	//call system call
    return _syscall(PM_PROC_NR, GETPROCNAME, &m);
}
        
int getchildinf(pid_t ppid, int nchildren, int flags_mask, 
    struct procinf *cpinf) {
	
	//error checking
	if (ppid!>0) {
		errno = EINVAL;
		return -1;
	}
	if (nchildren<0) {
		errno = EINVAL;
		return -1;
	}
	
	//send messages
	message m;
    m.m1_i1 = ppid;
    m.m1_i2 = (int) nchildren;
	m.m1_i3 = (int) flags_mask;
	m.m1_p1 = (char*) cpinf;
    
	//call system call
    return _syscall(PM_PROC_NR, GETCHILDINF, &m);
}
