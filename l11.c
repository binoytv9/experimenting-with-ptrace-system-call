#include<stdio.h>
#include<sys/ptrace.h>
#include<signal.h>
#include<sys/user.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

main()
{
    int addr = 0x601044;
    int data;
    int i, status = 0, pid;
    struct user_regs_struct uregs;

    if((pid = fork()) == 0){
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execl("./child5", "child5", NULL);
        printf("execl error...\n");
    }
    else{
        wait(&status);
        while(1){
            ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
			wait(&status);
			if(WIFEXITED(status)) break;

			data = ptrace(PTRACE_PEEKDATA, pid, addr, 0);
			if(data == 10){
				ptrace(PTRACE_POKEDATA, pid, addr, 2341);
				ptrace(PTRACE_CONT, pid, 0, 0);
				break;
			}
		}
        wait(&status);
        if(WIFEXITED(status))
            printf("child over\n");
    }
}
