/* mash.c
 *
 * This program sets up a simple shell to read in commands from a user, and
 * forks() a new process to the OS to take care of the command.  The reading
 * is already done, all that is left is to fork() the process to the OS.
 */

 
/* YOUR NAME GOES HERE
 * Date Completed: MM-DD-YY
 *
 * Description of what you did:
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>


#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */

/**
 * setup() reads in the next command line, separating it into distinct tokens
 * using whitespace as delimiters. setup() sets the args parameter as a 
 * null-terminated string.
 */

void setup(char inputBuffer[], char *args[])
{
    int length, /* # of characters in the command line */
        i,      /* loop index for accessing inputBuffer array */
        start,  /* index where beginning of next command parameter is */
        ct;     /* index of where to place the next parameter into args[] */
    
    ct = 0;
    
    /* Read what the user enters on the command line */
    length = read(STDIN_FILENO, inputBuffer, MAX_LINE);  

    start = -1;

    if (length == 0)
        exit(0);         /* CTRL-D was entered, end of user command stream */

    /* If the process is in the read() system call and is interrupted, then
       read() will return -1, even though it is not a problem. In this case
       errno will be set to EINTR.  We can check this value to ignore the 
       error condition. */
 
    if ( (length < 0) && (errno != EINTR) ) {
        perror("error reading the command");
	exit(-1);           /* terminate with error code of -1 */
    }

    /* Examine every character in the inputBuffer */
    for (i=0; i<length; i++) { 
        switch (inputBuffer[i]){
	    case ' ':
	    case '\t' :               /* argument separators */
		if(start != -1){
                    args[ct] = &inputBuffer[start];    /* set up pointer */
		    ct++;
		}
                inputBuffer[i] = '\0'; /* add a null char; make a C string */
		start = -1;
		break;

            case '\n':                 /* should be the final char examined */
		if (start != -1){
                    args[ct] = &inputBuffer[start];     
		    ct++;
		}
                inputBuffer[i] = '\0';
                start = -1;
                args[ct] = NULL; /* no more arguments to this command */
		break;

	    default :             /* some other character */
		if (start == -1)
		    start = i;
	} 
     }    

    args[ct] = NULL; /* just in case the input line was > 80 */ 

    /* Use the following for debugging.  Comment out before submitting. */
    printf("\n");
    for (i=0; i < ct; i++) 
        printf( "args %d = %s\n", i, args[i]);
    printf("\n");

} /* End of setup() routine */


int main(void) {

    char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
    char *args[MAX_LINE/2];     /* max of 40 arguments */
    int child,                  /* process id of the child process */
        status;                 /* result from execvp() call */
    
    while (1) {            /* Program terminates normally inside setup */

        fputs(">> ", stdout);
        setup(inputBuffer,args);       /* get next command */

        /* CODE GOES HERE.  DO NOT MODIFY ANYTHING ABOVE THIS LINE. */
	/* The steps are:
	 (1) fork a child process using fork()
	 (2) the child process invokes execvp(args[0], args). This
             should return 0, otherwise it is a perror() and exit(-2).
	 (3) the parent waits for the child to complete, but does not
             exit - this will allow setup() to be invoked again. */

    }
}

