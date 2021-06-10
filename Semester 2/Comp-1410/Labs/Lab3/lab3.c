/* ===========================================================================
COMP-1410 Lab 3
==============================================================================
Student name: Evan Morrison

Cite any other sources of outside help
(e.g., websites, other students):
None

=========================================================================== */
/* Was tested in OnlineGDB, repl.it and cLion IDE, C version C99.
 * Sorry about handing this in twice. I am handing this in again since I forgot
 * to change the Cite section and not sure if not putting None is bad or not.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define ROW_MAX 3 // This allows you to change the Amount of Rows in the Array 1 <= ROW_MAX <= 3
#define COLUMN_MAX 3 // This allows you to change the Amount of Columns in the Array 1 <= COLUMN_MAX <= 3
#define MatrixValueMaxRange 100 // Change this for larger matrix values NOTE: too high and it'll break
#define LoopAssertions 25 // Change this for more or less assertion cases

// matrix_add(n, a, b, c) computes the sum of the n x 3 matrices a and b;
//   the result is stored in the n x 3 matrix c
// requires: n >= 1
void matrix_add(const int n, const int a[][3], const int b[][3], int c[][3]);

// negate_column(n, c, a) negates the entries in column c of the n x 3
//   matrix a
// requires: n >= 1, 0 <= c < 3
void negate_column(const int n, const int c, int a[][3]);

// negate_row(n, r, a) negates the entries in row r of the n x 3 matrix a
// requires: n >= 1, 0 <= r < n
//           a points to the (0, 0) element of an n x 3 matrix
void negate_row(const int n, const int r, int * a);

void Copy(int old[][3], int new[][3]);
int count_digits(float x);
void printSpaceOfMatrix(int lC, int lSC, signed int Pointer[][3]);
void holdAndMeasureSpace(signed int x[][3]);
void buildAllTheMatrices();
void buildAsserts(signed int matrix[][3],
                  signed int matrixAdd[][3],
                  signed int matrixColumn1[][3], signed int matrixColumn2[][3], signed int matrixColumn3[][3],
                  signed int matrixRow1[][3], signed int matrixRow2[][3], signed int matrixRow3[][3]);

int main(void) {
    buildAllTheMatrices();// LoopAssertions
    // Perform testing here, e.g., that a + b = c
    printf("All tests passed successfully.\n");
    printf("If this message appears, that means that the program ran through the functions completing "
           "these number of assertions\n"
           "matrix_add ran: %d\n"
           "negate_column ran: %d\n"
           "negate_row ran: %d\n"
           "and ALL of these were Correct/Successful",
           LoopAssertions, LoopAssertions*COLUMN_MAX, LoopAssertions*ROW_MAX);
}

void matrix_add(const int n, const int a[][3], const int b[][3], int c[][3]){
    if (!(n >= 1))
        return;
    for (int i = 0; i < ROW_MAX; i++)
        for (int j = 0; j < COLUMN_MAX; j++)
            c[i][j] = a[i][j] + b[i][j];
    printf("\n ▼ This is the resulting matrix when addition is applied\n");
    holdAndMeasureSpace(c);
}

void negate_column(const int n, const int c, int a[][3]){
    if (!(n >= 1 && 0 <= c && c < 3)) // This is stupid
        return;
    int * aPointer = *a;
    for (int i = 0; i < ROW_MAX; i++)
        for (int j = 0; j < COLUMN_MAX; j++)
            if (j == c)
                *(aPointer + (i * (3)) + j) *= -1;
    printf("\n ▼ This is the resulting matrix when negation is done to column %d\n", c);
    holdAndMeasureSpace(a);
}

void negate_row(const int n, const int r, int * a){
    /* THIS is just for printing stuff since int * a is annoying and doesn't send
     * over the entire array meaning I would have to reconfigure the function a little
     * to compensate for it, And I don't want to.
     */
    if (!(n >= 1 && 0 <= r && r < 3)) // This is stupid
        return;
    int b[3][3];
    for (int i = 0; i < ROW_MAX; i++)
        for (int j = 0; j < COLUMN_MAX; j++) {
            if (i == r)
                *(a + (i*(3)) + j) *= -1;
            b[i][j] = *(a + (i*(3)) + j);
        }
    printf("\n ▼ This is the resulting matrix when negation is done to row %d \n", r);
    holdAndMeasureSpace(b);
}

void buildAllTheMatrices(){
    for (int _ = 0; _ < LoopAssertions; _++) {
        signed int matrix[3][3];
        signed int matrixAdd[3][3];
        signed int matrixColumn1[3][3];
        signed int matrixColumn2[3][3];
        signed int matrixColumn3[3][3];
        signed int matrixRow1[3][3];
        signed int matrixRow2[3][3];
        signed int matrixRow3[3][3];
        srand(time(NULL));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                signed int temp_num = rand() % (MatrixValueMaxRange * 2) - MatrixValueMaxRange;
                matrix[i][j] = temp_num;
                matrixAdd[i][j] = temp_num * 2;
                matrixColumn1[i][j] = temp_num;
                matrixColumn2[i][j] = temp_num;
                matrixColumn3[i][j] = temp_num;
                matrixRow1[i][j] = temp_num;
                matrixRow2[i][j] = temp_num;
                matrixRow3[i][j] = temp_num;
                switch(j) {
                    case (0):
                        matrixColumn1[i][j] = matrixColumn1[i][j] * -1;
                        break;
                    case (1):
                        matrixColumn2[i][j] = matrixColumn2[i][j] * -1;
                        break;
                    case (2):
                        matrixColumn3[i][j] = matrixColumn3[i][j] * -1;
                        break;
                    default:
                        break;
                }
                switch (i) {
                    case (0):
                        matrixRow1[i][j] = matrixRow1[i][j] * -1;
                        break;
                    case (1):
                        matrixRow2[i][j] = matrixRow2[i][j] * -1;
                        break;
                    case (2):
                        matrixRow3[i][j] = matrixRow3[i][j] * -1;
                        break;
                    default:
                        break;
                }
            }
        }

        printf("\n"// This is not a maze
               "████████╗██╗  ██╗██╗███████╗    ██╗███████╗    ████████╗██╗  ██╗███████╗    ███╗   ██╗███████╗██╗    ██╗"
               "███████╗███████╗████████╗    ███╗   ███╗ █████╗ ████████╗██████╗ ██╗██╗  ██╗    ████████╗██╗  ██╗ █████╗ "
               "████████╗    ██╗    ██╗██╗██╗     ██╗          ██████╗  ██████╗     ████████╗██╗  ██╗██████╗  ██████╗ ██╗ "
               "  ██╗ ██████╗ ██╗  ██╗    ████████╗██╗  ██╗███████╗     █████╗ ███████╗███████╗███████╗██████╗ ████████╗"
               "██╗ ██████╗ ███╗   ██╗    ████████╗██████╗ ██╗ █████╗ ██╗     ███████╗\n"
               " ══██╔══╝██║  ██║██║██╔════╝    ██║██╔════╝    ╚══██╔══╝██║  ██║██╔════╝    ████╗  ██║██╔════╝██║    ██║"
               "██╔════╝██╔════╝╚══██╔══╝    ████╗ ████║██╔══██╗╚══██╔══╝██╔══██╗██║╚██╗██╔╝    ╚══██╔══╝██║  ██║██╔══██╗"
               "╚══██╔══╝    ██║    ██║██║██║     ██║         ██╔════╝ ██╔═══██╗    ╚══██╔══╝██║  ██║██╔══██╗██╔═══██╗██║"
               "   ██║██╔════╝ ██║  ██║    ╚══██╔══╝██║  ██║██╔════╝    ██╔══██╗██╔════╝██╔════╝██╔════╝██╔══██╗╚══██╔══╝"
               "██║██╔═══██╗████╗  ██║    ╚══██╔══╝██╔══██╗██║██╔══██╗██║     ██╔════╝\n"
               "   ██║   ███████║██║███████╗    ██║███████╗       ██║   ███████║█████╗      ██╔██╗ ██║█████╗  ██║ █╗ ██║"
               "█████╗  ███████╗   ██║       ██╔████╔██║███████║   ██║   ██████╔╝██║ ╚███╔╝        ██║   ███████║███████║"
               "   ██║       ██║ █╗ ██║██║██║     ██║         ██║  ███╗██║   ██║       ██║   ███████║██████╔╝██║   ██║██║"
               "   ██║██║  ███╗███████║       ██║   ███████║█████╗      ███████║███████╗███████╗█████╗  ██████╔╝   ██║   "
               "██║██║   ██║██╔██╗ ██║       ██║   ██████╔╝██║███████║██║     ███████╗\n"
               "   ██║   ██╔══██║██║╚════██║    ██║╚════██║       ██║   ██╔══██║██╔══╝      ██║╚██╗██║██╔══╝  ██║███╗██║"
               "██╔══╝  ╚════██║   ██║       ██║╚██╔╝██║██╔══██║   ██║   ██╔══██╗██║ ██╔██╗        ██║   ██╔══██║██╔══██║"
               "   ██║       ██║███╗██║██║██║     ██║         ██║   ██║██║   ██║       ██║   ██╔══██║██╔══██╗██║   ██║██║"
               "   ██║██║   ██║██╔══██║       ██║   ██╔══██║██╔══╝      ██╔══██║╚════██║╚════██║██╔══╝  ██╔══██╗   ██║   "
               "██║██║   ██║██║╚██╗██║       ██║   ██╔══██╗██║██╔══██║██║     ╚════██║\n"
               "   ██║   ██║  ██║██║███████║    ██║███████║       ██║   ██║  ██║███████╗    ██║ ╚████║███████╗╚███╔███╔╝"
               "███████╗███████║   ██║       ██║ ╚═╝ ██║██║  ██║   ██║   ██║  ██║██║██╔╝ ██╗       ██║   ██║  ██║██║  ██║"
               "   ██║       ╚███╔███╔╝██║███████╗███████╗    ╚██████╔╝╚██████╔╝       ██║   ██║  ██║██║  ██║╚██████╔╝"
               "╚██████╔╝╚██████╔╝██║  ██║       ██║   ██║  ██║███████╗    ██║  ██║███████║███████║███████╗██║  ██║   ██║"
               "   ██║╚██████╔╝██║ ╚████║       ██║   ██║  ██║██║██║  ██║███████╗███████║\n"
               "   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝    ╚═╝╚══════╝       ╚═╝   ╚═╝  ╚═╝╚══════╝    ╚═╝  ╚═══╝╚══════╝ ╚══╝╚══╝ "
               "╚══════╝╚══════╝   ╚═╝       ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝       ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝"
               "   ╚═╝        ╚══╝╚══╝ ╚═╝╚══════╝╚══════╝     ╚═════╝  ╚═════╝        ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝  "
               "╚═════╝  ╚═════╝ ╚═╝  ╚═╝       ╚═╝   ╚═╝  ╚═╝╚══════╝    ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝   ╚═╝"
               "   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝       ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚══════╝╚══════╝\n"
               "▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼"
               " ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ "
               "▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼"
               " ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼"
               " ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼\n");
        holdAndMeasureSpace(matrix);
        buildAsserts(matrix, matrixAdd, matrixColumn1, matrixColumn2, matrixColumn3, matrixRow1, matrixRow2, matrixRow3);
    }
}

void holdAndMeasureSpace(signed int x[][3]){ // I disliked the dumbly spaced matrices being printed so this is my answer.
    int largestCount = 0;
    int largestStartCount = 0;
//    int *xPointer = *x;
    for (int i = 0; i < ROW_MAX; i++){
        for (int j = 0; j < COLUMN_MAX; j++){
            int temp = count_digits((float) x[i][j]);
            if (temp > largestCount)
                largestCount = temp;
            if (j == 0 && temp > largestStartCount)
                largestStartCount = temp;
        }
    }
    printSpaceOfMatrix(largestCount, largestStartCount, x);
//    for (int point = 0; point < ROW_MAX * COLUMN_MAX; point++){
//        int temp = count_digits((float) xPointer[point]);
//        if (temp > largestCount)
//            largestCount = temp;
//        if (point % ROW_MAX == 0 && temp > largestStartCount)
//            largestStartCount = temp;
//    }
//    printSpaceOfMatrix(largestCount, largestStartCount, xPointer);
}

void checkAssert(int x[][3], int y[][3]){
    for (int i = 0; i < ROW_MAX; i++) {
        for (int j = 0; j < COLUMN_MAX; j++) {
            assert(x[i][j] == y[i][j]);
        }
    }
}

void buildAsserts(signed int matrix[][3],
                  signed int matrixAdd[][3],
                  signed int matrixColumn1[][3],
                  signed int matrixColumn2[][3],
                  signed int matrixColumn3[][3],
                  signed int matrixRow1[][3],
                  signed int matrixRow2[][3],
                  signed int matrixRow3[][3]){

    printf("=====================================================================================================\n");
    int blankArray[3][3];
    matrix_add(ROW_MAX, matrix, matrix, blankArray);
    printf("\n ▼ This is what the matrix will assert against\n");
    holdAndMeasureSpace(matrixAdd);
    checkAssert(blankArray, matrixAdd);
    printf("=====================================================================================================\n");

    int copyMatrix[3][3];
    if (COLUMN_MAX >= 1) {
        printf("\n=====================================================================================================\n");
        Copy(matrix, copyMatrix);
        negate_column(ROW_MAX, 0, copyMatrix);
        printf("\n ▼ This is what the matrix will assert against\n");
        holdAndMeasureSpace(matrixColumn1);
        checkAssert(copyMatrix, matrixColumn1);
        printf("=====================================================================================================\n");
    }

    if (COLUMN_MAX >= 2) {
        printf("\n=====================================================================================================\n");
        Copy(matrix, copyMatrix);
        negate_column(ROW_MAX, 1, copyMatrix);
        printf("\n ▼ This is what the matrix will assert against\n");
        holdAndMeasureSpace(matrixColumn2);
        checkAssert(copyMatrix, matrixColumn2);
        printf("=====================================================================================================\n");
    }

    if (COLUMN_MAX >= 3) {
        printf("\n=====================================================================================================\n");
        Copy(matrix, copyMatrix);
        negate_column(ROW_MAX, 2, copyMatrix);
        printf("\n ▼ This is what the matrix will assert against\n");
        holdAndMeasureSpace(matrixColumn3);
        checkAssert(copyMatrix, matrixColumn3);
        printf("=====================================================================================================\n");
    }

    if (ROW_MAX >= 1) {
        printf("\n=====================================================================================================\n");
        Copy(matrix, copyMatrix);
        negate_row(ROW_MAX, 0, *copyMatrix);
        printf("\n ▼ This is what the matrix will assert against\n");
        holdAndMeasureSpace(matrixRow1);
        checkAssert(copyMatrix, matrixRow1);
        printf("=====================================================================================================\n");
    }

    if (ROW_MAX >= 2) {
        printf("\n=====================================================================================================\n");
        Copy(matrix, copyMatrix);
        negate_row(ROW_MAX, 1, *copyMatrix);
        printf("\n ▼ This is what the matrix will assert against\n");
        holdAndMeasureSpace(matrixRow2);
        checkAssert(copyMatrix, matrixRow2);
        printf("=====================================================================================================\n");
    }

    if (ROW_MAX >= 3) {
        printf("\n=====================================================================================================\n");
        Copy(matrix, copyMatrix);
        negate_row(ROW_MAX, 2, *copyMatrix);
        printf("\n ▼ This is what the matrix will assert against\n");
        holdAndMeasureSpace(matrixRow3);
        checkAssert(copyMatrix, matrixRow3);
        printf("=====================================================================================================\n");
    }
}

void printSpaceOfMatrix(int lC, int lSC, signed int Pointer[][3]){
    for (int rPointyPointer = 0; rPointyPointer < ROW_MAX; rPointyPointer++){
        for (int cPointyPointer = 0; cPointyPointer < COLUMN_MAX; cPointyPointer++) {
            if (cPointyPointer == 0){
                int count = lSC - count_digits((float) Pointer[rPointyPointer][cPointyPointer]);
                for (int m = 0; m < count; m++){
                    printf(" ");
                }
            }
            else{
                int count = lC - count_digits((float) Pointer[rPointyPointer][cPointyPointer]);
                for (int m = 0; m < count; m++){
                    printf(" ");
                }
            }
            printf("%d ", Pointer[rPointyPointer][cPointyPointer]);
        }
        printf("\n");
    }
    printf("\n");
}

int count_digits(float x){ // Counts how much whitespace this number will not need relative to a digit.
    // I could use something like allocating a certain amount of space to each number but that doesn't scale well
    int count = 0;
    if (x < 0)
        count += 1;
    while (x >= 10 || x <= -10){
        x /= 10;
        count++;
    }
    return count;
}

void Copy(int old[][3], int new[][3]){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            new[i][j] = old[i][j];
        }
    }
}