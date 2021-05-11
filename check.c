#include <get_proc_info.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

int main(){
	pid_t mypid = getpid();
	printf("PID: %d\n", mypid);
	struct procinfos info;
	if(get_proc_info(mypid, &info) == 0){
		printf("Student ID : %lu \n", info.studentID);
		printf("                PID	     NAME \n");
		printf("------------------------------------ \n");
		printf("Current         %4d         %5s \n", info.proc.pid, info.proc.name);
		printf("Parent          %4d         %5s \n", info.parent_proc.pid, info.parent_proc.name);
		printf("Oldest Child    %4d         %5s \n", info.oldest_child_proc.pid, info.oldest_child_proc.name);
	}else{
		printf("Cannot get information from the process %d\n", mypid);	
	}

}	
