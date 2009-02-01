/*  nosync1.c
 *
 * Source code for a process that updates a counter in a file.
 * This process is unsynchronized with other processes that might
 * update the counter concurrently with this process.  Therefore,
 * the final result in the file will be unpredictable.
 *
 * This process assumes there is a file named "datafile" initialized
 * to the value 0.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXSIZE 80

int main(int argc, char *argv[]) {

  /* function prototype for file access */
  void fileaccess(int fd, int count);

  int fd, count;

  /* Check for command line arguments */
  if (argc != 2) {
    printf("Usage: nosync1 count\n");
    return;
  }

  count = atoi(argv[1]);

  /* Use UNIX input/output system calls for accessing the file */
  fd = open("datafile", O_RDWR, 0);
  fileaccess(fd, count);

  return 0;
}

/* Access the file with the given fd, and increment the only integer
 * value in that file count times. */
void fileaccess(int fd, int count) {
  
  int i, k, value;
  pid_t pid;
  char buff[MAXSIZE];

  pid = getpid();
  for (i = 0; i < count; i++) {
    
    /* Read value from file */
    lseek(fd, 0L, 0);
    k = read(fd, buff, MAXSIZE);
    buff[k] = '\0';
    sscanf(buff, "%d\n", &value);

    /* Increment value */
    value++;

    /* Write back into file */
    sprintf(buff, "%d\n", value);
    lseek(fd, 0L, 0);
    k = strlen(buff);
    write(fd, buff, k);
    //printf("pid = %d, new value = %d\n", pid, value);
    
  }
}
