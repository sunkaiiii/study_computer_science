#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc,char *argv){
    int fd=open(argv[1],O_RDONLY);
    int fd2=open(argv[1],O_RDONLY);
}