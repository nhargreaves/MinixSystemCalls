/*
 * Replace the following string of 0s with your student number
 * 150405531
 */
#include <stdio.h>
#include "pm.h"             // for glo.h:  mp, call_nr, who_p etc.
#include "mproc.h"          // for proc table
#include <string.h>         // for strlen or strnlen

#define INVALID_ARG -22     /* gets converted to errno and -1 return value
                             * return instead of -1 when detect invalid 
                             * argument. Do not set errno in system calls.
                             * See: See: /usr/src/lib/libc/sys-minix/syscall.c
                             */

int do_getpids() {
	//variables
	int idx = m_in.m1_i1;
	int n = m_in.m1_i2;
	int flags_mask = m_in.m1_i3;
	pid_t pids[n+1];
	pid_t current_pid = 0;
	
	//initialise array
	for (int i = 0; i<n+1; i++) {
		pids[i] = 0;
	}
	
	//error checking
	if ((idx<0)&&(idx<NR_PROCS))
		return INVALID_ARG;
	if (n<=1) 
		return INVALID_ARG;
	if (pids==NULL)
		return INVALID_ARG;

	//for all values
    for (int i = idx; i < n; i++) {
		if (idx == NR_PROCS) { //set index to beginning if reach end of table
		idx = 0;
		}
		current_pid = mproc[i].mp.pid; 
		//if flags match, add to array
		if ((flags_mask) != (MP_FLAGS_SWITCH)) {
			pids[i] = mproc[i].mp_pid;
		}
    }
	//array will have many empty values: this is an issue
	
	//set this so idx can be returned
	 int result = sys_vircopy(SELF, (vir_bytes) idx, who_e, (vir_bytes) m_in.m1_i1, strlen(idx)+1);
    return result;
}

int do_getprocname() {
	pid_t pid = (pid_t) m_in.m1_i1;
    char* name = m_in.m1_p1; 
    if (pid!>0)
        return INVALID_ARG;
    if (name==NULL)         
        return INVALID_ARG;
    

      char *name_found = "";
	  //while in process table
      for (int i = 0; i < NR_PROCS; i++) {
		  //if matching
           if (pid == mproc[i].mp_pid) {
			   //set name found as value needed
				name_found = mproc[i].mp_name;
				break;
            }
      }
     
	 //use vircopy so name found can be returned
	 int result = sys_vircopy(SELF, (vir_bytes) name_found, who_e, (vir_bytes) m_in.m1_p1, strlen(name_found)+1);

    return result;
}

int do_getchildinf() {
	pid_t ppid = (pid_t) m_in.m1_i1;
	int nchildren = m_in.m1_i2;
	int flags_mask = m_in.m1_i3;
	char* cpinf = m_in.m1_p1;
	
	if (ppid!>0)
		return INVALID_ARG;
	if (nchildren<0)
		return INVALID_ARG;
	
	//run while cpinf contains fewer than max childre
	while (sizeof(cpinf)<nchildren) {
		for (i = 0; i<sizeonf(cpinf); i++) {
			//if flags match add child process to cpinf
			if ((flags_mask) != (MP_FLAGS_SWITCH)) {
				cpinf[i]] = fork();
			}
		}	
	}
	
	//set vircopy so size of cpinf can be outputted
	int result = sys_vircopy(SELF, (vir_bytes) idx, who_e, (vir_bytes) m_in.m1_p1, strlen(sizeof(cpinf))+1);
    return result;
}