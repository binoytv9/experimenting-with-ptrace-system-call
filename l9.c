#include<stdio.h>
#include<sys/ptrace.h>
#include<signal.h>
#include<sys/user.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

main()
{
    int addr = 0x601040;
    int data;
    int i, status = 0, pid;
    struct user_regs_struct uregs;

    if((pid = fork()) == 0){
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execl("./child4", "child4", NULL);
        printf("execl error...\n");
    }
    else{
        wait(&status);
        data = ptrace(PTRACE_PEEKDATA, pid, addr, 0);
        printf("data = %d\n", data);
        data = 245;
        ptrace(PTRACE_POKEDATA, pid, addr, data);
        ptrace(PTRACE_CONT, pid, 0, 0);
        wait(&status);
    }
}
