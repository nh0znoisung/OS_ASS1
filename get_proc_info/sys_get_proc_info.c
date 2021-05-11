#include <linux/kernel.h> 
#include <linux/unistd.h> //*
#include <linux/sched.h> //*
#include <linux/pid.h> //*
#include <linux/list.h>
#include <linux/signal.h>
#include <linux/types.h>
#include <linux/linkage.h>
#include <linux/sched/signal.h>
#include <linux/mm_types.h>
#include <linux/string.h>
#include <linux/syscalls.h>
#include <linux/proc_fs.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/errno.h>

#define EINVAL 22
struct proc_info{
	pid_t pid; //pid of this process
	char name[16]; // file name of the program executed
};

struct procinfos{
	long studentID; //testing
	struct proc_info proc; //proc with pid or current process
	struct proc_info parent_proc; // parent process
	struct proc_info oldest_child_proc; // oldest child process
};

//pid -> of the process or -1 is current process
//if find process have PID => get info => in *info and return 0. 
// Every time get_proc_info => studentID printed in kernel
SYSCALL_DEFINE2(get_proc_info, pid_t, pid, struct procinfos*, info){
	pid_t p; //current process
	struct procinfos temp; // use to store
	struct task_struct* task;
	struct task_struct* child;

	p = current->pid;
	printk("***************************************");
	printk("This current process Id is: %d \n", p);
	
	if(pid == -1) pid = p; // -1 is the current process
	printk("The Pid that we are running: %d \n", pid);

	task = pid_task(find_vpid (pid), PIDTYPE_PID);//find the process with pid

	for_each_process(child){
		if(child->parent->pid == pid) break;
	}
	
	if(task != NULL){
		//studentID
		temp.studentID = 1910663;
		//proc_
		temp.proc.pid = task->pid;
		strcpy(temp.proc.name, task->comm); //find which is length 16
		printk("This current process Id is: %d , The Pid name: %s \n", temp.proc.pid,temp.proc.name);
		//parent
		if(task->parent->pid != 0){
			//if parent exist
			temp.parent_proc.pid = task->parent->pid;
			strcpy(temp.parent_proc.name, task->parent->comm);
			printk("The PPID is: %d, The name of PPID is: %s \n", temp.parent_proc.pid, temp.parent_proc.name);
		}else{
			temp.parent_proc.pid = -1;
			strcpy(temp.parent_proc.name, "NONE");
			printk("There is no parent node, this is a root. \n");			
		}
		//children
		if(child->pid != 0){
			temp.oldest_child_proc.pid = child->pid;
			strcpy(temp.oldest_child_proc.name, child->comm);
			printk("The Child ID is: %d, The name of Child is: %s \n", temp.oldest_child_proc.pid, temp.oldest_child_proc.name);
		}else{
			temp.oldest_child_proc.pid = -1;
			strcpy(temp.oldest_child_proc.name, "NONE");
			printk("This process do not have any children \n");
		}
		//finally
		copy_to_user(info, &temp, sizeof(temp));
		//printk("");
		return 0;		
	}else{
		printk("There is no process have this pid \n");
		return EINVAL;	
	}
	
		

}
