#include<stdio.h>

fun()
{
    while(1)
        printf("hello\n");
}

main()
{
    printf("pid: %d\n", getpid());
    printf("fun: %p\n", fun);
    while(1);
}
