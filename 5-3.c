#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
int main (int argc, char *argv[]){
	int fd,fd2,n;
	caddr_t addr;
	struct stat statbuf;
	char buf[10];	
	pid_t pid;

	switch(pid = fork()) {
		case -1 :
			perror("fork");
			exit(1);
			break;
		case 0 :
			sleep(1);	
			write(1, addr,30);
		default : 
			if ( argc != 2) {
                         fprintf(stderr, "Usage : %s filename\n", argv[0]);
                           exit(1);
                             }
                          if (stat (argv[1], &statbuf) == -1) {
                                 perror("stat");
                                 exit(1);
                                   }

                      if ((fd = open(argv[1], O_RDWR))== -1) {
                          perror("open");
                         exit(1);
                          }
 addr = mmap( NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);
                         if (addr == MAP_FAILED) {
                          perror("mmap");
                            exit(1);
                          }
                          close(fd);

		}	
}

