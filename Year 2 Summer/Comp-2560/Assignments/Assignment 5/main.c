//
// Created by evanm on 2021-07-26.
//

#include    <stdio.h>
#include    <string.h>
#include    <math.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <fcntl.h>
#include    <signal.h>
#include    <time.h>
#include    <errno.h>


// Some Configurable Values

    // FIFO Configurations
    #define fifo                    "FileFIFO"      // What the General Name Will be When the Program is Run, The Name Will look like <fifo> <Player Number>. Example if Player Number is 1 and fifo is FileFIFO the Files name will be "FileFIFO 1"
    #define length                  strlen(fifo)    // Dunno Wanted to know if this was possible, and it Seems So
    #define maxNumberOfDigits       20              // Maximum Number of Digits, For Knowing How large char arrays need to be

    // Game Configurations
    #define numOfPlayers            2               // Number Of Players
    #define PointsNeededToWin       10              // Number of Points needed to Win
    #define timeBetweenPlayerMoves  2               // Time between each player rolling their dice

    // Signal Configurations
    #define SIGDONE                 34              // Wanted to be fancy with naming the run time signal

// Some Configurable Values


int gameOver = 0;  // Game over Global Variable.  So That sigDone isn't a dummy Function.

void player(int num, char *fifoParent, char *fifoChild);


void removeFifoFile(char *fifoFile){

    // tells the terminal to remove a file. In this case it will be removing a FIFO file
    char buffer[maxNumberOfDigits + length];
    sprintf(buffer, "rm \"%s\"", fifoFile);  // Generates the command line
    system(buffer);  // Calls the System terminal
}

void removeFifoFiles(char *fifoFiles[]){
    // Remove all the FIFO files after no longer of use.
    for (int i = 0; i < numOfPlayers * 2; i++)  removeFifoFile(fifoFiles[i]);
}

char *mkFifoFileName(int num){

    // Makes all of the FIFO Files needed. I could have just used a single FIFO using slightly sophisticated codes to tell each process if the parent is talking to you or not.
    // Like sending the Players number across as a reference then converting from char reference back to int.
    char *temp = (char*) malloc((strlen(fifo) + (int) log10(num) + 1) * (sizeof(char)));
    sprintf(temp, "%s %d", fifo, num);
    if (access(temp, F_OK) == 0) removeFifoFile(temp);
    // This is 100% necessary since it seems having a fifo file which may or may not have something in before official reading/writing can cause issues.
    // Not sure but I was having issues so here we are deleting all files.
    if (mkfifo(temp, 0777) < 0 && errno != EEXIST){  // Errno should only be checked if mkfifo returns a bad creation.
        printf("Not Made File\n");
        exit(0);
    }
    return temp;
}



void sigDone(){
    gameOver = 1;
    printf("\n\nReferee: \tA Winner has been recognised, I will now begin coordinating the closure of this game, \nBeep: \t\tPlease do not press anything\n");
}

int main(){
    char start = 'T';
    char *fifoArray[numOfPlayers * 2];  // Holds the Fifo File Names
    int fdfifoArray[numOfPlayers * 2];  // Holds the Fifo File Descriptors
    signal(SIGDONE, sigDone);  // Sets the Run time Signal 34 or SIGDONE to sigDone function for GameOver Registering

    for (int i = 0; i < numOfPlayers * 2; i++) {
        fifoArray[i] = mkFifoFileName(i + 1);  // Writes the Fifo File Names to this char* array.
    }

    for (int i = 0; i < numOfPlayers; i++){
        switch(fork()){
            case -1:
                printf("failed to fork\n");
                exit(0);
            case 0:
                player(i + 1, fifoArray[i * 2], fifoArray[i * 2 + 1]);
                break;
            default:
                fdfifoArray[i * 2] = open(fifoArray[i * 2], O_RDONLY);  // Open the Parents Reading Side
                fdfifoArray[i * 2 + 1] = open(fifoArray[i * 2 + 1], O_WRONLY);  // Open the Childs Writing Side
                break;
        }
    }
    printf("This is a %d-player game with a referee\n", numOfPlayers);
    printf("First person to %d points wins\n\n", PointsNeededToWin);

    while (!gameOver){  // Doesn't Quit Until Game Over
        for (int i = 0; i < numOfPlayers; i++){
            printf("\nReferee: \tPlayer %d plays\n\n", i+1);
            write(fdfifoArray[i * 2 + 1] , &start, 1);  // Writes for the go ahead to which ever players turn is next
            read(fdfifoArray[i * 2],  &start, 1);       // Reads for the go ahead to go to Next player
            if (gameOver) {
                break;  // Will Break the For loop once game over has been achieved
            }
        }
    }
    printf("\n\n");
    printf("Referee: \tClosing all FIFO Files currently open ...\n");
    for (int i = 0; i < numOfPlayers; i++){  // This will tell every child that someone has won and to begin closing downs its end. To Prevent a bunch of processes to clutter your computer and
        // FIFO files to remain open or something
        write(fdfifoArray[i * 2 + 1], "E", 1);  // E will tell children to close.
        // Closes its own side of the FIFO files.
        close(fdfifoArray[i * 2 + 1]);
        close(fdfifoArray[i * 2]);
    }
    printf("Referee: \tI have Closed all of the FIFO files\n");
    sleep(1);
    printf("Referee: \tAll FIFO Files have been closed\n");
    printf("Referee: \tDeleting FIFO Files ...\n");
    removeFifoFiles(fifoArray);  // Deletes the FIFO Files. To Prevent certain Issues I was having.
    printf("Referee: \tAll FIFO Files have been deleted\n");
    kill(0, SIGTERM);  // Kills all processes in case some managed to slip through the cracks.
    return 0;
}

void player(int num, char *fifoParent, char *fifoChild) {
    int Points = 0;
    int Dice;
    long ss = 0;
    char start;
    int fdParent = open(fifoParent, O_WRONLY);  // Parent Write Only FIFO File
    int fdChild = open(fifoChild, O_RDONLY);    // Child Read Only FIFO File
    while (1){
        read(fdChild, &start, 1);
        if (start == 'E') break; // Breaks once signal returned to Begin Closing The Process

        printf("Player %d: \tPlaying my Dice\n", num);
        Dice = (int) abs((int) (time(&ss) + num) * ((int) (time(&ss) - num) / 2)) % 10 + 1;
        printf("Player %d: \tGot %d Points\n", num, Dice);
        Points += Dice;
        printf("Player %d: \tTotal so far %d\n\n", num, Points);
        if(Points >= PointsNeededToWin){
            printf("Player %d: \tgame over I won\n", num);
            kill(getppid(), SIGDONE);
        }
        sleep(timeBetweenPlayerMoves);  // 3 is better then 5 since it gives even a small amount of change.

        write(fdParent, &start, 1);
    }

    // closing the Child Down
    close(fdParent);
    close(fdChild);
    char Child[strlen("Player : \tI Have Closed both FIFO Files on my end\n") + maxNumberOfDigits + 1];  // Should Produce an Array Large Enough To Hold What I need it to hold.


    sprintf(Child, "Player %d: \tI Have Closed both FIFO Files on my end\n", num);
    write(STDOUT_FILENO, Child, strlen(Child));
    exit(0);
}
