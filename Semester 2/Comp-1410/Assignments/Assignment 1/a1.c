//I would recommend if you can to just close the 2 assertion functions as
// they are big and make reading the code annoying. I do not regret a thing...
/* ===========================================================================
COMP-1410 Assignment 1
==============================================================================
Student name: Evan Morrison

Cite any other sources of outside help
(e.g., websites, other students):
 Generated all the assertions in void asserts_combo with
 Python 3.8 itertools combinations library
 Below is a copy of the program I used to generate the asserts for choose in case
 that is considered external help.
 My Crazy Brain

=========================================================================== */
/*
 I originally wrote the fib way of doing since I didn't understand what the Prof wanted me to do exactly
 but it eventually came to me in a dream so you get both ways.

 This is the python program I wrote for generating the asserts. I wrote it myself.
    """ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ """
    from itertools import combinations, tee
    from multiprocessing import Pool
    from os import cpu_count

    def generator(o, p) -> int:
        temp_gen = combinations(o, p)
        for i in temp_gen:
            yield i

    def multiFunction(tup_1):
        list_1, num_1 = tup_1
        list_length = 0
        generated_combination = generator(list_1, num_1)
        for _ in generated_combination:
            list_length += 1
        print(f"assert(choose({len(list_1)}, {num_1}) == {list_length});\n", end='')

    if __name__ == '__main__':
        all_combos = []
        max_n = 40
        for n in range(max_n):
            lis = [i for i in range(n)]
            for m in range(n + 1):
                all_combos.append(tuple((lis, m)))
                # generated_combination = generator(lis, m)
        list_of_combos = []
        with Pool(processes=cpu_count() - 1) as p:
            p.map(multiFunction, all_combos)
        print(len(all_combos))
    """ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ """
*/



#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

// choose(n,m) returns how many ways there are to choose m items from
//   a set of n items
// requires: 0 <= m, 0 <= n
long int choose_factorials(int n, int m);
int choose(int n, int m);
long long int factorial(long long int n);
    /**
     * If you were wondering there are 403 assertion statements here have fun
     * These were all generated with a python program I wrote
     * see above for details on the program
     * There used to be 820 assertions but it took a few minutes on my system to check
     * them all so I removed a good half of them Very sad I know.
     * NOTE: This does not break any rule he said at least 3 I did not do less then 3 so I should be fine...
    **/
void sleep(double secs) {
    double sleep = clock();
    while ((clock() - sleep)/CLOCKS_PER_SEC < secs);
}
void asserts_combos(){
    assert(choose(0, 0) == 1);
    assert(choose(0, 0) == 1);
    assert(choose(1, 0) == 1);
    assert(choose(1, 1) == 1);
    assert(choose(2, 0) == 1);
    assert(choose(2, 1) == 2);
    assert(choose(2, 2) == 1);
    assert(choose(3, 0) == 1);
    assert(choose(3, 1) == 3);
    assert(choose(3, 2) == 3);
    assert(choose(3, 3) == 1);
    assert(choose(4, 0) == 1);
    assert(choose(4, 1) == 4);
    assert(choose(4, 2) == 6);
    assert(choose(4, 3) == 4);
    assert(choose(4, 4) == 1);
    assert(choose(5, 0) == 1);
    assert(choose(5, 1) == 5);
    assert(choose(5, 2) == 10);
    assert(choose(5, 3) == 10);
    assert(choose(5, 4) == 5);
    assert(choose(5, 5) == 1);
    assert(choose(6, 0) == 1);
    assert(choose(6, 1) == 6);
    assert(choose(6, 2) == 15);
    assert(choose(6, 3) == 20);
    assert(choose(6, 4) == 15);
    assert(choose(6, 5) == 6);
    assert(choose(6, 6) == 1);
    assert(choose(7, 0) == 1);
    assert(choose(7, 1) == 7);
    assert(choose(7, 2) == 21);
    assert(choose(7, 3) == 35);
    assert(choose(7, 4) == 35);
    assert(choose(7, 5) == 21);
    assert(choose(7, 6) == 7);
    assert(choose(7, 7) == 1);
    assert(choose(8, 0) == 1);
    assert(choose(8, 1) == 8);
    assert(choose(8, 2) == 28);
    assert(choose(8, 3) == 56);
    assert(choose(8, 4) == 70);
    assert(choose(8, 5) == 56);
    assert(choose(8, 6) == 28);
    assert(choose(8, 7) == 8);
    assert(choose(8, 8) == 1);
    assert(choose(9, 0) == 1);
    assert(choose(9, 1) == 9);
    assert(choose(9, 2) == 36);
    assert(choose(9, 3) == 84);
    assert(choose(9, 4) == 126);
    assert(choose(9, 5) == 126);
    assert(choose(9, 6) == 84);
    assert(choose(9, 7) == 36);
    assert(choose(9, 8) == 9);
    assert(choose(9, 9) == 1);
    assert(choose(10, 0) == 1);
    assert(choose(10, 1) == 10);
    assert(choose(10, 2) == 45);
    assert(choose(10, 3) == 120);
    assert(choose(10, 4) == 210);
    assert(choose(10, 5) == 252);
    assert(choose(10, 6) == 210);
    assert(choose(10, 7) == 120);
    assert(choose(10, 8) == 45);
    assert(choose(10, 9) == 10);
    assert(choose(10, 10) == 1);
    assert(choose(11, 0) == 1);
    assert(choose(11, 1) == 11);
    assert(choose(11, 2) == 55);
    assert(choose(11, 3) == 165);
    assert(choose(11, 4) == 330);
    assert(choose(11, 5) == 462);
    assert(choose(11, 6) == 462);
    assert(choose(11, 7) == 330);
    assert(choose(11, 8) == 165);
    assert(choose(11, 9) == 55);
    assert(choose(11, 10) == 11);
    assert(choose(11, 11) == 1);
    assert(choose(12, 0) == 1);
    assert(choose(12, 1) == 12);
    assert(choose(12, 2) == 66);
    assert(choose(12, 3) == 220);
    assert(choose(12, 4) == 495);
    assert(choose(12, 5) == 792);
    assert(choose(12, 6) == 924);
    assert(choose(12, 7) == 792);
    assert(choose(12, 8) == 495);
    assert(choose(12, 9) == 220);
    assert(choose(12, 10) == 66);
    assert(choose(12, 11) == 12);
    assert(choose(12, 12) == 1);
    assert(choose(13, 0) == 1);
    assert(choose(13, 1) == 13);
    assert(choose(13, 2) == 78);
    assert(choose(13, 3) == 286);
    assert(choose(13, 4) == 715);
    assert(choose(13, 5) == 1287);
    assert(choose(13, 6) == 1716);
    assert(choose(13, 7) == 1716);
    assert(choose(13, 8) == 1287);
    assert(choose(13, 9) == 715);
    assert(choose(13, 10) == 286);
    assert(choose(13, 11) == 78);
    assert(choose(13, 12) == 13);
    assert(choose(13, 13) == 1);
    assert(choose(14, 0) == 1);
    assert(choose(14, 1) == 14);
    assert(choose(14, 2) == 91);
    assert(choose(14, 3) == 364);
    assert(choose(14, 4) == 1001);
    assert(choose(14, 5) == 2002);
    assert(choose(14, 6) == 3003);
    assert(choose(14, 7) == 3432);
    assert(choose(14, 8) == 3003);
    assert(choose(14, 9) == 2002);
    assert(choose(14, 10) == 1001);
    assert(choose(14, 11) == 364);
    assert(choose(14, 12) == 91);
    assert(choose(14, 13) == 14);
    assert(choose(14, 14) == 1);
    assert(choose(15, 0) == 1);
    assert(choose(15, 1) == 15);
    assert(choose(15, 2) == 105);
    assert(choose(15, 3) == 455);
    assert(choose(15, 4) == 1365);
    assert(choose(15, 5) == 3003);
    assert(choose(15, 6) == 5005);
    assert(choose(15, 7) == 6435);
    assert(choose(15, 8) == 6435);
    assert(choose(15, 9) == 5005);
    assert(choose(15, 10) == 3003);
    assert(choose(15, 11) == 1365);
    assert(choose(15, 12) == 455);
    assert(choose(15, 13) == 105);
    assert(choose(15, 14) == 15);
    assert(choose(15, 15) == 1);
    assert(choose(16, 0) == 1);
    assert(choose(16, 1) == 16);
    assert(choose(16, 2) == 120);
    assert(choose(16, 3) == 560);
    assert(choose(16, 4) == 1820);
    assert(choose(16, 5) == 4368);
    assert(choose(16, 6) == 8008);
    assert(choose(16, 7) == 11440);
    assert(choose(16, 8) == 12870);
    assert(choose(16, 9) == 11440);
    assert(choose(16, 10) == 8008);
    assert(choose(16, 11) == 4368);
    assert(choose(16, 12) == 1820);
    assert(choose(16, 13) == 560);
    assert(choose(16, 14) == 120);
    assert(choose(16, 15) == 16);
    assert(choose(16, 16) == 1);
    assert(choose(17, 0) == 1);
    assert(choose(17, 1) == 17);
    assert(choose(17, 2) == 136);
    assert(choose(17, 3) == 680);
    assert(choose(17, 4) == 2380);
    assert(choose(17, 5) == 6188);
    assert(choose(17, 6) == 12376);
    assert(choose(17, 7) == 19448);
    assert(choose(17, 9) == 24310);
    assert(choose(17, 8) == 24310);
    assert(choose(17, 10) == 19448);
    assert(choose(17, 11) == 12376);
    assert(choose(17, 12) == 6188);
    assert(choose(17, 13) == 2380);
    assert(choose(17, 14) == 680);
    assert(choose(17, 15) == 136);
    assert(choose(17, 16) == 17);
    assert(choose(17, 17) == 1);
    assert(choose(18, 0) == 1);
    assert(choose(18, 9) == 48620);
    assert(choose(18, 1) == 18);
    assert(choose(18, 2) == 153);
    assert(choose(18, 3) == 816);
    assert(choose(18, 4) == 3060);
    assert(choose(21, 21) == 1);
    assert(choose(22, 0) == 1);
    assert(choose(22, 1) == 22);
    assert(choose(22, 2) == 231);
    assert(choose(18, 5) == 8568);
    assert(choose(18, 6) == 18564);
    assert(choose(19, 8) == 75582);
    assert(choose(18, 10) == 43758);
    assert(choose(21, 3) == 1330);
    assert(choose(22, 3) == 1540);
    assert(choose(21, 4) == 5985);
    assert(choose(18, 7) == 31824);
    assert(choose(22, 4) == 7315);
    assert(choose(20, 6) == 38760);
    assert(choose(21, 5) == 20349);
    assert(choose(18, 11) == 31824);
    assert(choose(22, 5) == 26334);
    assert(choose(18, 12) == 18564);
    assert(choose(18, 13) == 8568);
    assert(choose(18, 14) == 3060);
    assert(choose(18, 15) == 816);
    assert(choose(18, 16) == 153);
    assert(choose(18, 17) == 18);
    assert(choose(18, 18) == 1);
    assert(choose(19, 0) == 1);
    assert(choose(19, 1) == 19);
    assert(choose(19, 2) == 171);
    assert(choose(19, 3) == 969);
    assert(choose(19, 9) == 92378);
    assert(choose(21, 6) == 54264);
    assert(choose(19, 4) == 3876);
    assert(choose(18, 8) == 43758);
    assert(choose(19, 5) == 11628);
    assert(choose(20, 7) == 77520);
    assert(choose(22, 6) == 74613);
    assert(choose(19, 6) == 27132);
    assert(choose(22, 17) == 26334);
    assert(choose(22, 18) == 7315);
    assert(choose(22, 19) == 1540);
    assert(choose(22, 20) == 231);
    assert(choose(22, 21) == 22);
    assert(choose(22, 22) == 1);
    assert(choose(23, 0) == 1);
    assert(choose(23, 1) == 23);
    assert(choose(23, 2) == 253);
    assert(choose(23, 3) == 1771);
    assert(choose(23, 4) == 8855);
    assert(choose(19, 7) == 50388);
    assert(choose(19, 10) == 92378);
    assert(choose(21, 7) == 116280);
    assert(choose(23, 5) == 33649);
    assert(choose(20, 8) == 125970);
    assert(choose(19, 11) == 75582);
    assert(choose(22, 7) == 170544);
    assert(choose(23, 6) == 100947);
    assert(choose(19, 12) == 50388);
    assert(choose(19, 13) == 27132);
    assert(choose(19, 14) == 11628);
    assert(choose(19, 15) == 3876);
    assert(choose(21, 8) == 203490);
    assert(choose(19, 16) == 969);
    assert(choose(19, 17) == 171);
    assert(choose(19, 18) == 19);
    assert(choose(19, 19) == 1);
    assert(choose(20, 0) == 1);
    assert(choose(20, 1) == 20);
    assert(choose(20, 2) == 190);
    assert(choose(20, 3) == 1140);
    assert(choose(20, 4) == 4845);
    assert(choose(20, 9) == 167960);
    assert(choose(20, 5) == 15504);
    assert(choose(24, 24) == 1);
    assert(choose(25, 0) == 1);
    assert(choose(25, 1) == 25);
    assert(choose(25, 2) == 300);
    assert(choose(25, 3) == 2300);
    assert(choose(25, 4) == 12650);
    assert(choose(25, 5) == 53130);
    assert(choose(27, 0) == 1);
    assert(choose(27, 1) == 27);
    assert(choose(27, 2) == 351);
    assert(choose(23, 7) == 245157);
    assert(choose(20, 10) == 184756);
    assert(choose(27, 3) == 2925);
    assert(choose(24, 6) == 134596);
    assert(choose(27, 4) == 17550);
    assert(choose(21, 9) == 293930);
    assert(choose(22, 8) == 319770);
    assert(choose(27, 5) == 80730);
    assert(choose(25, 6) == 177100);
    assert(choose(20, 11) == 167960);
    assert(choose(20, 12) == 125970);
    assert(choose(24, 7) == 346104);
    assert(choose(27, 6) == 296010);
    assert(choose(20, 13) == 77520);
    assert(choose(23, 8) == 490314);
    assert(choose(21, 10) == 352716);
    assert(choose(20, 14) == 38760);
    assert(choose(20, 15) == 15504);
    assert(choose(20, 16) == 4845);
    assert(choose(20, 17) == 1140);
    assert(choose(20, 18) == 190);
    assert(choose(20, 19) == 20);
    assert(choose(20, 20) == 1);
    assert(choose(21, 0) == 1);
    assert(choose(21, 1) == 21);
    assert(choose(21, 2) == 210);
    assert(choose(22, 9) == 497420);
    assert(choose(25, 7) == 480700);
    assert(choose(21, 11) == 352716);
    assert(choose(28, 26) == 378);
    assert(choose(28, 27) == 28);
    assert(choose(28, 28) == 1);
    assert(choose(29, 0) == 1);
    assert(choose(29, 1) == 29);
    assert(choose(29, 2) == 406);
    assert(choose(23, 12) == 1352078);
    assert(choose(24, 8) == 735471);
    assert(choose(29, 3) == 3654);
    assert(choose(29, 4) == 23751);
    assert(choose(21, 12) == 293930);
    assert(choose(29, 5) == 118755);
    assert(choose(23, 9) == 817190);
    assert(choose(27, 7) == 888030);
    assert(choose(21, 13) == 203490);
    assert(choose(22, 10) == 646646);
    assert(choose(21, 14) == 116280);
    assert(choose(21, 15) == 54264);
    assert(choose(21, 16) == 20349);
    assert(choose(21, 17) == 5985);
    assert(choose(21, 18) == 1330);
    assert(choose(21, 19) == 210);
    assert(choose(21, 20) == 21);
    assert(choose(25, 8) == 1081575);
    assert(choose(29, 6) == 475020);
    assert(choose(25, 17) == 1081575);
    assert(choose(24, 9) == 1307504);
    assert(choose(23, 13) == 1144066);
    assert(choose(23, 10) == 1144066);
    assert(choose(22, 11) == 705432);
    assert(choose(26, 9) == 3124550);
    assert(choose(25, 18) == 480700);
    assert(choose(23, 14) == 817190);
    assert(choose(25, 19) == 177100);
    assert(choose(25, 20) == 53130);
    assert(choose(25, 21) == 12650);
    assert(choose(25, 22) == 2300);
    assert(choose(25, 23) == 300);
    assert(choose(25, 24) == 25);
    assert(choose(25, 25) == 1);
    assert(choose(26, 0) == 1);
    assert(choose(26, 1) == 26);
    assert(choose(26, 2) == 325);
    assert(choose(26, 3) == 2600);
    assert(choose(26, 4) == 14950);
    assert(choose(26, 5) == 65780);
    assert(choose(29, 7) == 1560780);
    assert(choose(28, 8) == 3108105);
    assert(choose(26, 6) == 230230);
    assert(choose(23, 15) == 490314);
    assert(choose(23, 11) == 1352078);
    assert(choose(30, 3) == 4060);
    assert(choose(30, 4) == 27405);
    assert(choose(30, 5) == 142506);
    assert(choose(22, 12) == 646646);
    assert(choose(23, 16) == 245157);
    assert(choose(23, 17) == 100947);
    assert(choose(23, 18) == 33649);
    assert(choose(23, 19) == 8855);
    assert(choose(23, 20) == 1771);
    assert(choose(23, 21) == 253);
    assert(choose(23, 22) == 23);
    assert(choose(23, 23) == 1);
    assert(choose(24, 0) == 1);
    assert(choose(24, 1) == 24);
    assert(choose(24, 2) == 276);
    assert(choose(24, 3) == 2024);
    assert(choose(24, 4) == 10626);
    assert(choose(24, 5) == 42504);
    assert(choose(24, 10) == 1961256);
    assert(choose(25, 9) == 2042975);
    assert(choose(22, 13) == 497420);
    assert(choose(30, 6) == 593775);
    assert(choose(27, 8) == 2220075);
    assert(choose(26, 7) == 657800);
    assert(choose(22, 14) == 319770);
    assert(choose(22, 15) == 170544);
    assert(choose(22, 16) == 74613);
    assert(choose(27, 18) == 4686825);
    assert(choose(26, 8) == 1562275);
    assert(choose(30, 7) == 2035800);
    assert(choose(31, 26) == 169911);
    assert(choose(31, 27) == 31465);
    assert(choose(31, 28) == 4495);
    assert(choose(31, 29) == 465);
    assert(choose(31, 30) == 31);
    assert(choose(31, 31) == 1);
    assert(choose(32, 0) == 1);
    assert(choose(32, 1) == 32);
    assert(choose(32, 2) == 496);
    assert(choose(32, 3) == 4960);
    assert(choose(32, 4) == 35960);
    assert(choose(24, 11) == 2496144);
    assert(choose(32, 5) == 201376);
    assert(choose(32, 6) == 906192);
    assert(choose(29, 8) == 4292145);
    assert(choose(25, 10) == 3268760);
    assert(choose(26, 10) == 5311735);
    assert(choose(27, 19) == 2220075);
    assert(choose(24, 12) == 2704156);
    assert(choose(27, 20) == 888030);
    assert(choose(27, 9) == 4686825);
    assert(choose(27, 21) == 296010);
    assert(choose(27, 22) == 80730);
    assert(choose(27, 23) == 17550);
    assert(choose(27, 24) == 2925);
    assert(choose(27, 25) == 351);
    assert(choose(27, 26) == 27);
    assert(choose(27, 27) == 1);
    assert(choose(28, 0) == 1);
    assert(choose(28, 1) == 28);
    assert(choose(28, 2) == 378);
    assert(choose(28, 3) == 3276);
    assert(choose(28, 4) == 20475);
}

// num_divisors_up_to_k(n,k) returns the number of positive divisors
//   of n that are less than or equal to k
// requires: 1 <= k <= n
int num_divisors_up_to_k(int n, int k);


// is_prime(n) returns true if n is a prime number and false otherwise
// requires: 1 <= n
bool is_prime(int n);

// collatz(n) returns the number of steps it takes to reach 1 by
//   by repeatedly applying the Collatz mapping on n; prints each
//   number in the sequence starting at n
// requires: 1 <= n
int collatz(int n);

// everyones favorite part is below this message. Some people have even seen the depths of stupidity here
void asserting_status(){
    assert(choose(15, 4) == 1365);
    assert(choose(15, 15) == 1);
    assert(choose(0, 0) == 1);
    assert(choose(25, 4) == 12650);
    assert(choose(15, 16) == 0);  // 0 means that the entire thing is a failure and producing 0 combinations
    assert(choose(-5, -10) == 0); // 0 means that the entire thing is a failure and producing 0 combinations
    assert(choose(-5, 10) == 0);  // 0 means that the entire thing is a failure and producing 0 combinations
    assert(choose(5, -10) == 0);  // 0 means that the entire thing is a failure and producing 0 combinations
    asserts_combos();
    printf("All asserts for The Choose function were successful\n\n");
    assert(num_divisors_up_to_k(9, 9) == 3);
    assert(num_divisors_up_to_k(9, 3) == 2);
    assert(num_divisors_up_to_k(10, 10) == 4);
    assert(num_divisors_up_to_k(24, 24) == 8);
    assert(num_divisors_up_to_k(24, 6) == 5);
    assert(num_divisors_up_to_k(100, 50) == 8);
    assert(num_divisors_up_to_k(100, 101) == 0);
    assert(num_divisors_up_to_k(0, -1) == 0);
    printf("All asserts for The num_divisors_up_to_k function were successful\n\n");
    assert(is_prime(5) == 1);
    assert(is_prime(6) == 0);
    assert(is_prime(11) == 1);
    assert(is_prime(22) == 0);
    assert(is_prime(23) == 1);
    assert(is_prime(57) == 0);
    assert(is_prime(59) == 1);
    assert(is_prime(1) == 0);
    assert(is_prime(0) == 0);
    assert(is_prime(-5) == 0);
    printf("All asserts for The is_prime function were successful\n\n");
    assert(collatz(6) == 9);
    assert(collatz(5) == 6);
    assert(collatz(4) == 3);
    assert(collatz(3) == 8);
    assert(collatz(0) == 0);
    assert(collatz(-1) == 0);
    printf("All asserts for The collatz function were successful\n\n\n");


}

int fib(int n) { // It fibs to you... Hehehe ;P
    // Debuggers are the best of them all especially for OOP, Though that ain't here.
    if (n <= 1) {
        return n;
    }
    int F_nsub1 = fib(n - 1);
    int F_nsub2 = fib(n - 2);
    return F_nsub1 + F_nsub2;
}

void scanner(){ // Scans the collatz inputs
    int n, num;
    while (1){
        printf("Give a number and we will tell you your fortune: ");
        if (scanf("%d", &n) && n != 0){
            if (n >= 1)
                printf("This is the answer to your Collatz with it taking: %d levels\n", collatz(n));
            else
                printf("n = %d is an invalid input\n", n);
            printf("Do you want to quit?: (1 for yes, 0 for no): ");
            scanf("%d", &num);
            if (num == 1)
                return;
        }
        else { // I might have gone insane when doing this assignment not sure.
            printf("We got an Error Here\n");
            sleep(0.5); // Don't Judge me cause I'm dumb
            printf("...\n");
            sleep(0.75); // Don't Judge me cause I'm dumb
            printf("...\n");
            sleep(0.62); // Don't Judge me cause I'm dumb
            printf("I think something is supposed to appear just a sec\n");
            sleep(1.34); // Don't Judge me cause I'm dumb
            printf("Error: Invalid input\n");
            sleep(0.6); // Don't Judge me cause I'm dumb
        }
        while (getchar() != '\n'){} // cleans the buffer
    }
}

int main(void) { // Where main things happen
    fib(5);
    asserts_combos();
    asserting_status();
    scanner();
    printf("We Won the Lottery"
           "\nThe Entire Program has executed successfully, quitting now.");
}

long long int factorial(long long int n){ // This should also be ignored
    // This was my original attempt with choose, it works but wasn't exactly what was asked of me + Factorials
    if (n <= 1){
        return 1;
    }
    return n * factorial(n - 1);
}

long int choose_factorials(int n, int m){ // Ignore this disgrace.
    // This was my original attempt with choose, it works but wasn't exactly what was asked of me
    if (m > n) {
        printf("This is a failure of an input please try again.\nNote that I am pushing through a zero as a sign I have"
               " zero respect for what was just inputted!\n");
        return 0;
    }
    long int calculations = (long int)(factorial(n) / (factorial(m) * factorial(n - m)));
    return calculations;
}

int num_divisors_up_to_k(int n, int k){ // What n can be divided by from 1 to k
    if (k < 1 || k > n){
        printf("n = %d and k = %d are invalid inputs\n", n, k);
        return 0;
    }
    if (k == 1)
        return 1;
    if (n % k == 0)
        return 1 + num_divisors_up_to_k(n, k-1);
    else
        return num_divisors_up_to_k(n, k-1);
}

bool is_prime(int n){ // Check for the is primes and is not primes
    if (n < 1){
        printf("n = %d is an invalid input\n", n);
        return 0;
    }
    int num = num_divisors_up_to_k(n, n);
    if (num == 2)
        return true;
    else
        return false;
}

int choose(int n, int m){ // Weird name, find combos that's about it
    if(m > n || n < 0 || m < 0){
        printf("n = %d and m = %d are invalid inputs\n", n, m);
        return 0;
    }
    if (m == 0 || n == m)
        return 1;
    return choose(n - 1, m) + choose(n - 1, m - 1);
}

int collatz(int n){ // Collatz find the path to 1
    if (n == 1) {
        printf("%d\n", n);
        return n;
    }
    else if (n < 1){
        printf("n = %d is an invalid input\n", n);
        return 0;
    }
    if (n % 2 == 1) {
        printf("%d -> ", n);
        return 1 + collatz(3 * n + 1);
    }
    else {
        printf("%d -> ", n);
        return 1 + collatz(n / 2);
    }
}
