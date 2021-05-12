#include <get_proc_info.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/wait.h>
//Compile with: gcc test.c -o test -lget_proc_info
int main() 
{
	pid_t mypid = getpid();
	printf("PID: %d\n", mypid);
	struct procinfos info;
	if (fork() == 0)
	{
		sleep(3);
		return 1;
	}
	if (fork() == 0)
	{
		sleep(3);
		return 1;
	}

	if (get_proc_info(-1, &info) == 0) {
	// TODO: print all information in struct procinfos info
		printf("Student ID: %ld\n", info.studentID);
		printf("\t\tPID\tNAME\n");
		printf("CURRENT\t\t%d\t%s\n", info.proc.pid, info.proc.name);
		printf("PARENT\t\t%d\t%s\n", info.parent_proc.pid, info.parent_proc.name);
		printf("CHILD\t\t%d\t%s\n", info.oldest_child_proc.pid, info.oldest_child_proc.name);
	} else {
		printf("Cannot get information from the process %d\n", mypid);
	}
	while(wait(NULL) >= 0);
}
