#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void createPipe(int fd) {
    int res, num, flag = 0;
    if(read(fd, &res, sizeof(int)) == 0)
        return;
    printf("prime %d\n", res);

    int p[2];

    while(read(fd, &num, sizeof(int)) != 0) {
        if(!flag) {
            flag = 1;
            pipe(p);
            if(fork() == 0) {
                close(p[1]);
                createPipe(p[0]);
                return;
            } else {
                close(p[0]);
            }

        }
        if(num % res != 0) 
            write(p[1], &num, sizeof(int));   
    }
    close(fd);
    close(p[1]);
    wait(0);

}

int
main(int argc, char *argv[]){
    int p[2];
    pipe(p);
    if(fork() == 0) {
        close(p[1]);
        createPipe(p[0]);
        close(p[0]);
    } else {
        close(p[0]);
        for(int i = 2; i <= 35; i++)
            write(p[1], &i, sizeof(int));
        close(p[1]);
        wait(0);
    }
    exit(0);
}

