#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//#include <sys/types.h> Dunno why this was here but I am leaving it anyways but commented.
#include <sys/wait.h>

/// I am using bit manipulation for getting the core dump since it doesn't seem like a retrieving core dump macro was discussed, I am writing it as a macro though so as to stay within the gist of the assignment.
/// I also have WCOREDUMP(_w) here because I didn't know if it was wanted or not so I just used it.
#define GETCOREDUMP(_w) (WCOREDUMP(_w) ? (_w) & 0x80 : 0)  // I don't know where the macro do show the core dump is since I could only find WCOREDUMP() which gets the flag for if a core dump was given.

void statusCheck(int status){
    printf("Macros:    Child Status = %d ", WIFEXITED(status) ? WEXITSTATUS(status) : WIFEXITED(status));   // WEXITSTATUS(status) : WIFEXITED(status) could also be WEXITSTATUS(status) : 0 but meh.
    printf("Signal = %d ", WIFSIGNALED(status) ? WTERMSIG(status) : WIFSIGNALED(status));                   // WTERMSIG(status) : WIFSIGNALED(status) could also be WTERMSIG(status) : 0 but meh.
    printf("Core = %d\n", GETCOREDUMP(status));
}

int main() {
    int newpid;

    printf("before: mypid is %d\n", getpid());

    if ((newpid = fork()) == -1 )
        perror("fork");
    else if (newpid == 0){
        printf("I am the child %d now sleeping...\n",getpid());
        sleep(5);
        abort();
    }
    else{
        printf("I am the parent %d\n",getpid());

        int status;
        int child_pid  = wait(&status);

        printf("My child %d has terminated\n",child_pid);
        printf("I have received the status = %d\n",status);
        statusCheck(status);        // This is the function to the macro, it will print a copy of the stuff similar in style to the hard coded bit manipulation.
        int child_status = status >> 8; // I am leaving these here so as to be able to produce a comparison with the macros
        int signal = status & 0x7F;     // I am leaving these here so as to be able to produce a comparison with the macros
        int core = status & 0x80;       // I am leaving these here so as to be able to produce a comparison with the macros

        printf("Hard Code: Child status = %d Signal = %d Core = %d\n", child_status, signal, core);  // I am leaving this in so as to compare it with the macros so as to easily tell that they are doing the same thing.
    }
}


