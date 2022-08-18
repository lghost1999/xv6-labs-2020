#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"


int
main(int argc, char* argv[]) {

    if(argc < 2) {
        fprintf(2, "Usage: <file> <params>...\n");
        exit(1);
    }

    char buf[512], *p;
    if(read(0, buf, sizeof(buf)) == 0){
        fprintf(2, "no arguments\n");
    }
    p = buf;
    for(int i = 0; buf[i]; i++) {
        if(buf[i] == '\n') {
            buf[i] = 0;
            if(fork() == 0) {
                argv[argc++] = p;
                argv[argc] = 0;
                exec(argv[1], argv + 1);
                exit(0);
            } else {
                p = buf + i + 1;
                wait(0);
            }
        }
    }
    exit(0);
}