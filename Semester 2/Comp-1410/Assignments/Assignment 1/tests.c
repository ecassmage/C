/* ===========================================================================
COMP-1410 Assignment 1
==============================================================================
Student name: Evan Morrison

Cite any other sources of outside help
(e.g., websites, other students):
ERROR_NO_INTEGRITY_STATEMENT

=========================================================================== */

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

// choose(n,m) returns how many ways there are to choose m items from
//   a set of n items
// requires: 0 <= m, 0 <= n
long int choose(int n, int m);
int combos(int n, int m);
long long int factorial(long long int n);
void asserts_combos(){
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
    assert(choose(17, 8) == 24310);
    assert(choose(17, 9) == 24310);
    assert(choose(17, 10) == 19448);
    assert(choose(17, 11) == 12376);
    assert(choose(17, 12) == 6188);
    assert(choose(17, 13) == 2380);
    assert(choose(17, 14) == 680);
    assert(choose(17, 15) == 136);
    assert(choose(17, 16) == 17);
    assert(choose(17, 17) == 1);
    assert(choose(18, 0) == 1);
    assert(choose(18, 1) == 18);
    assert(choose(18, 2) == 153);
    assert(choose(18, 3) == 816);
    assert(choose(18, 4) == 3060);
    assert(choose(18, 5) == 8568);
    assert(choose(18, 6) == 18564);
    assert(choose(18, 7) == 31824);
    assert(choose(18, 8) == 43758);
    assert(choose(18, 9) == 48620);
    assert(choose(18, 10) == 43758);
    assert(choose(18, 11) == 31824);
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
    assert(choose(19, 4) == 3876);
    assert(choose(19, 5) == 11628);
    assert(choose(19, 6) == 27132);
    assert(choose(19, 7) == 50388);
    assert(choose(19, 8) == 75582);
    assert(choose(19, 9) == 92378);
    assert(choose(19, 10) == 92378);
    assert(choose(19, 11) == 75582);
    assert(choose(19, 12) == 50388);
    assert(choose(19, 13) == 27132);
    assert(choose(19, 14) == 11628);
    assert(choose(19, 15) == 3876);
    assert(choose(19, 16) == 969);
    assert(choose(19, 17) == 171);
    assert(choose(19, 18) == 19);
    assert(choose(19, 19) == 1);
    assert(choose(20, 0) == 1);
    assert(choose(20, 1) == 20);
    assert(choose(20, 2) == 190);
    assert(choose(20, 3) == 1140);
    assert(choose(20, 4) == 4845);
    assert(choose(20, 5) == 15504);
    assert(choose(20, 6) == 38760);
    assert(choose(20, 7) == 77520);
    assert(choose(20, 8) == 125970);
    assert(choose(20, 9) == 167960);
    assert(choose(20, 10) == 184756);
    assert(choose(20, 11) == 167960);
    assert(choose(20, 12) == 125970);
    assert(choose(20, 13) == 77520);
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
    assert(choose(21, 3) == 1330);
    assert(choose(21, 4) == 5985);
    assert(choose(21, 5) == 20349);
    assert(choose(21, 6) == 54264);
    assert(choose(21, 7) == 116280);
    assert(choose(21, 8) == 203490);
    assert(choose(21, 9) == 293930);
    assert(choose(21, 10) == 352716);
    assert(choose(21, 11) == 352716);
    assert(choose(21, 12) == 293930);
    assert(choose(21, 13) == 203490);
    assert(choose(21, 14) == 116280);
    assert(choose(21, 15) == 54264);
    assert(choose(21, 16) == 20349);
    assert(choose(21, 17) == 5985);
    assert(choose(21, 18) == 1330);
    assert(choose(21, 19) == 210);
    assert(choose(21, 20) == 21);
    assert(choose(21, 21) == 1);
    assert(choose(22, 0) == 1);
    assert(choose(22, 1) == 22);
    assert(choose(22, 2) == 231);
    assert(choose(22, 3) == 1540);
    assert(choose(22, 4) == 7315);
    assert(choose(22, 5) == 26334);
    assert(choose(22, 6) == 74613);
    assert(choose(22, 7) == 170544);
    assert(choose(22, 8) == 319770);
    assert(choose(22, 9) == 497420);
    assert(choose(22, 10) == 646646);
    assert(choose(22, 11) == 705432);
    assert(choose(22, 12) == 646646);
    assert(choose(22, 13) == 497420);
    assert(choose(22, 14) == 319770);
    assert(choose(22, 15) == 170544);
    assert(choose(22, 16) == 74613);
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
    assert(choose(23, 5) == 33649);
    assert(choose(23, 6) == 100947);
    assert(choose(23, 7) == 245157);
    assert(choose(23, 8) == 490314);
    assert(choose(23, 9) == 817190);
    assert(choose(23, 10) == 1144066);
    assert(choose(23, 11) == 1352078);
    assert(choose(23, 12) == 1352078);
    assert(choose(23, 13) == 1144066);
    assert(choose(23, 14) == 817190);
    assert(choose(23, 15) == 490314);
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
    assert(choose(24, 6) == 134596);
    assert(choose(24, 7) == 346104);
    assert(choose(24, 8) == 735471);
    assert(choose(24, 9) == 1307504);
    assert(choose(24, 10) == 1961256);
    assert(choose(24, 11) == 2496144);
    assert(choose(24, 12) == 2704156);
    assert(choose(24, 13) == 2496144);
    assert(choose(24, 14) == 1961256);
    assert(choose(24, 15) == 1307504);
    assert(choose(24, 16) == 735471);
    assert(choose(24, 17) == 346104);
    assert(choose(24, 18) == 134596);
    assert(choose(24, 19) == 42504);
    assert(choose(24, 20) == 10626);
    assert(choose(24, 21) == 2024);
    assert(choose(24, 22) == 276);
    assert(choose(24, 23) == 24);
    assert(choose(24, 24) == 1);
}
int printing(){
    printf("%d\n", choose(0, 0));
    printf("%d\n", choose(1, 0));
    printf("%d\n", choose(1, 1));
    printf("%d\n", choose(2, 0));
    printf("%d\n", choose(2, 1));
    printf("%d\n", choose(2, 2));
    printf("%d\n", choose(3, 0));
    printf("%d\n", choose(3, 1));
    printf("%d\n", choose(3, 2));
    printf("%d\n", choose(3, 3));
    printf("%d\n", choose(4, 0));
    printf("%d\n", choose(4, 1));
    printf("%d\n", choose(4, 2));
    printf("%d\n", choose(4, 3));
    printf("%d\n", choose(4, 4));
    printf("%d\n", choose(5, 0));
    printf("%d\n", choose(5, 1));
    printf("%d\n", choose(5, 2));
    printf("%d\n", choose(5, 3));
    printf("%d\n", choose(5, 4));
    printf("%d\n", choose(5, 5));
    printf("%d\n", choose(6, 0));
    printf("%d\n", choose(6, 1));
    printf("%d\n", choose(6, 2));
    printf("%d\n", choose(6, 3));
    printf("%d\n", choose(6, 4));
    printf("%d\n", choose(6, 5));
    printf("%d\n", choose(6, 6));
    printf("%d\n", choose(7, 0));
    printf("%d\n", choose(7, 1));
    printf("%d\n", choose(7, 2));
    printf("%d\n", choose(7, 3));
    printf("%d\n", choose(7, 4));
    printf("%d\n", choose(7, 5));
    printf("%d\n", choose(7, 6));
    printf("%d\n", choose(7, 7));
    printf("%d\n", choose(8, 0));
    printf("%d\n", choose(8, 1));
    printf("%d\n", choose(8, 2));
    printf("%d\n", choose(8, 3));
    printf("%d\n", choose(8, 4));
    printf("%d\n", choose(8, 5));
    printf("%d\n", choose(8, 6));
    printf("%d\n", choose(8, 7));
    printf("%d\n", choose(8, 8));
    printf("%d\n", choose(9, 0));
    printf("%d\n", choose(9, 1));
    printf("%d\n", choose(9, 2));
    printf("%d\n", choose(9, 3));
    printf("%d\n", choose(9, 4));
    printf("%d\n", choose(9, 5));
    printf("%d\n", choose(9, 6));
    printf("%d\n", choose(9, 7));
    printf("%d\n", choose(9, 8));
    printf("%d\n", choose(9, 9));
    printf("%d\n", choose(10, 0));
    printf("%d\n", choose(10, 1));
    printf("%d\n", choose(10, 2));
    printf("%d\n", choose(10, 3));
    printf("%d\n", choose(10, 4));
    printf("%d\n", choose(10, 5));
    printf("%d\n", choose(10, 6));
    printf("%d\n", choose(10, 7));
    printf("%d\n", choose(10, 8));
    printf("%d\n", choose(10, 9));
    printf("%d\n", choose(10, 10));
    printf("%d\n", choose(11, 0));
    printf("%d\n", choose(11, 1));
    printf("%d\n", choose(11, 2));
    printf("%d\n", choose(11, 3));
    printf("%d\n", choose(11, 4));
    printf("%d\n", choose(11, 5));
    printf("%d\n", choose(11, 6));
    printf("%d\n", choose(11, 7));
    printf("%d\n", choose(11, 8));
    printf("%d\n", choose(11, 9));
    printf("%d\n", choose(11, 10));
    printf("%d\n", choose(11, 11));
    printf("%d\n", choose(12, 0));
    printf("%d\n", choose(12, 1));
    printf("%d\n", choose(12, 2));
    printf("%d\n", choose(12, 3));
    printf("%d\n", choose(12, 4));
    printf("%d\n", choose(12, 5));
    printf("%d\n", choose(12, 6));
    printf("%d\n", choose(12, 7));
    printf("%d\n", choose(12, 8));
    printf("%d\n", choose(12, 9));
    printf("%d\n", choose(12, 10));
    printf("%d\n", choose(12, 11));
    printf("%d\n", choose(12, 12));
    printf("%d\n", choose(13, 0));
    printf("%d\n", choose(13, 1));
    printf("%d\n", choose(13, 2));
    printf("%d\n", choose(13, 3));
    printf("%d\n", choose(13, 4));
    printf("%d\n", choose(13, 5));
    printf("%d\n", choose(13, 6));
    printf("%d\n", choose(13, 7));
    printf("%d\n", choose(13, 8));
    printf("%d\n", choose(13, 9));
    printf("%d\n", choose(13, 10));
    printf("%d\n", choose(13, 11));
    printf("%d\n", choose(13, 12));
    printf("%d\n", choose(13, 13));
    printf("%d\n", choose(14, 0));
    printf("%d\n", choose(14, 1));
    printf("%d\n", choose(14, 2));
    printf("%d\n", choose(14, 3));
    printf("%d\n", choose(14, 4));
    printf("%d\n", choose(14, 5));
    printf("%d\n", choose(14, 6));
    printf("%d\n", choose(14, 7));
    printf("%d\n", choose(14, 8));
    printf("%d\n", choose(14, 9));
    printf("%d\n", choose(14, 10));
    printf("%d\n", choose(14, 11));
    printf("%d\n", choose(14, 12));
    printf("%d\n", choose(14, 13));
    printf("%d\n", choose(14, 14));
    printf("%d\n", choose(15, 0));
    printf("%d\n", choose(15, 1));
    printf("%d\n", choose(15, 2));
    printf("%d\n", choose(15, 3));
    printf("%d\n", choose(15, 4));
    printf("%d\n", choose(15, 5));
    printf("%d\n", choose(15, 6));
    printf("%d\n", choose(15, 7));
    printf("%d\n", choose(15, 8));
    printf("%d\n", choose(15, 9));
    printf("%d\n", choose(15, 10));
    printf("%d\n", choose(15, 11));
    printf("%d\n", choose(15, 12));
    printf("%d\n", choose(15, 13));
    printf("%d\n", choose(15, 14));
    printf("%d\n", choose(15, 15));
    printf("%d\n", choose(16, 0));
    printf("%d\n", choose(16, 1));
    printf("%d\n", choose(16, 2));
    printf("%d\n", choose(16, 3));
    printf("%d\n", choose(16, 4));
    printf("%d\n", choose(16, 5));
    printf("%d\n", choose(16, 6));
    printf("%d\n", choose(16, 7));
    printf("%d\n", choose(16, 8));
    printf("%d\n", choose(16, 9));
    printf("%d\n", choose(16, 10));
    printf("%d\n", choose(16, 11));
    printf("%d\n", choose(16, 12));
    printf("%d\n", choose(16, 13));
    printf("%d\n", choose(16, 14));
    printf("%d\n", choose(16, 15));
    printf("%d\n", choose(16, 16));
    printf("%d\n", choose(17, 0));
    printf("%d\n", choose(17, 1));
    printf("%d\n", choose(17, 2));
    printf("%d\n", choose(17, 3));
    printf("%d\n", choose(17, 4));
    printf("%d\n", choose(17, 5));
    printf("%d\n", choose(17, 6));
    printf("%d\n", choose(17, 7));
    printf("%d\n", choose(17, 8));
    printf("%d\n", choose(17, 9));
    printf("%d\n", choose(17, 10));
    printf("%d\n", choose(17, 11));
    printf("%d\n", choose(17, 12));
    printf("%d\n", choose(17, 13));
    printf("%d\n", choose(17, 14));
    printf("%d\n", choose(17, 15));
    printf("%d\n", choose(17, 16));
    printf("%d\n", choose(17, 17));
    printf("%d\n", choose(18, 0));
    printf("%d\n", choose(18, 1));
    printf("%d\n", choose(18, 2));
    printf("%d\n", choose(18, 3));
    printf("%d\n", choose(18, 4));
    printf("%d\n", choose(18, 5));
    printf("%d\n", choose(18, 6));
    printf("%d\n", choose(18, 7));
    printf("%d\n", choose(18, 8));
    printf("%d\n", choose(18, 9));
    printf("%d\n", choose(18, 10));
    printf("%d\n", choose(18, 11));
    printf("%d\n", choose(18, 12));
    printf("%d\n", choose(18, 13));
    printf("%d\n", choose(18, 14));
    printf("%d\n", choose(18, 15));
    printf("%d\n", choose(18, 16));
    printf("%d\n", choose(18, 17));
    printf("%d\n", choose(18, 18));
    printf("%d\n", choose(19, 0));
    printf("%d\n", choose(19, 1));
    printf("%d\n", choose(19, 2));
    printf("%d\n", choose(19, 3));
    printf("%d\n", choose(19, 4));
    printf("%d\n", choose(19, 5));
    printf("%d\n", choose(19, 6));
    printf("%d\n", choose(19, 7));
    printf("%d\n", choose(19, 8));
    printf("%d\n", choose(19, 9));
    printf("%d\n", choose(19, 10));
    printf("%d\n", choose(19, 11));
    printf("%d\n", choose(19, 12));
    printf("%d\n", choose(19, 13));
    printf("%d\n", choose(19, 14));
    printf("%d\n", choose(19, 15));
    printf("%d\n", choose(19, 16));
    printf("%d\n", choose(19, 17));
    printf("%d\n", choose(19, 18));
    printf("%d\n", choose(19, 19));
    printf("%d\n", choose(20, 0));
    printf("%d\n", choose(20, 1));
    printf("%d\n", choose(20, 2));
    printf("%d\n", choose(20, 3));
    printf("%d\n", choose(20, 4));
    printf("%d\n", choose(20, 5));
    printf("%d\n", choose(20, 6));
    printf("%d\n", choose(20, 7));
    printf("%d\n", choose(20, 8));
    printf("%d\n", choose(20, 9));
    printf("%d\n", choose(20, 10));
    printf("%d\n", choose(20, 11));
    printf("%d\n", choose(20, 12));
    printf("%d\n", choose(20, 13));
    printf("%d\n", choose(20, 14));
    printf("%d\n", choose(20, 15));
    printf("%d\n", choose(20, 16));
    printf("%d\n", choose(20, 17));
    printf("%d\n", choose(20, 18));
    printf("%d\n", choose(20, 19));
    printf("%d\n", choose(20, 20));
    printf("%d\n", choose(21, 0));
    printf("%d\n", choose(21, 1));
    printf("%d\n", choose(21, 2));
    printf("%d\n", choose(21, 3));
    printf("%d\n", choose(21, 4));
    printf("%d\n", choose(21, 5));
    printf("%d\n", choose(21, 6));
    printf("%d\n", choose(21, 7));
    printf("%d\n", choose(21, 8));
    printf("%d\n", choose(21, 9));
    printf("%d\n", choose(21, 10));
    printf("%d\n", choose(21, 11));
    printf("%d\n", choose(21, 12));
    printf("%d\n", choose(21, 13));
    printf("%d\n", choose(21, 14));
    printf("%d\n", choose(21, 15));
    printf("%d\n", choose(21, 16));
    printf("%d\n", choose(21, 17));
    printf("%d\n", choose(21, 18));
    printf("%d\n", choose(21, 19));
    printf("%d\n", choose(21, 20));
    printf("%d\n", choose(21, 21));
    printf("%d\n", choose(22, 0));
    printf("%d\n", choose(22, 1));
    printf("%d\n", choose(22, 2));
    printf("%d\n", choose(22, 3));
    printf("%d\n", choose(22, 4));
    printf("%d\n", choose(22, 5));
    printf("%d\n", choose(22, 6));
    printf("%d\n", choose(22, 7));
    printf("%d\n", choose(22, 8));
    printf("%d\n", choose(22, 9));
    printf("%d\n", choose(22, 10));
    printf("%d\n", choose(22, 11));
    printf("%d\n", choose(22, 12));
    printf("%d\n", choose(22, 13));
    printf("%d\n", choose(22, 14));
    printf("%d\n", choose(22, 15));
    printf("%d\n", choose(22, 16));
    printf("%d\n", choose(22, 17));
    printf("%d\n", choose(22, 18));
    printf("%d\n", choose(22, 19));
    printf("%d\n", choose(22, 20));
    printf("%d\n", choose(22, 21));
    printf("%d\n", choose(22, 22));
    printf("%d\n", choose(23, 0));
    printf("%d\n", choose(23, 1));
    printf("%d\n", choose(23, 2));
    printf("%d\n", choose(23, 3));
    printf("%d\n", choose(23, 4));
    printf("%d\n", choose(23, 5));
    printf("%d\n", choose(23, 6));
    printf("%d\n", choose(23, 7));
    printf("%d\n", choose(23, 8));
    printf("%d\n", choose(23, 9));
    printf("%d\n", choose(23, 10));
    printf("%d\n", choose(23, 11));
    printf("%d\n", choose(23, 12));
    printf("%d\n", choose(23, 13));
    printf("%d\n", choose(23, 14));
    printf("%d\n", choose(23, 15));
    printf("%d\n", choose(23, 16));
    printf("%d\n", choose(23, 17));
    printf("%d\n", choose(23, 18));
    printf("%d\n", choose(23, 19));
    printf("%d\n", choose(23, 20));
    printf("%d\n", choose(23, 21));
    printf("%d\n", choose(23, 22));
    printf("%d\n", choose(23, 23));
    printf("%d\n", choose(24, 0));
    printf("%d\n", choose(24, 1));
    printf("%d\n", choose(24, 2));
    printf("%d\n", choose(24, 3));
    printf("%d\n", choose(24, 4));
    printf("%d\n", choose(24, 5));
    printf("%d\n", choose(24, 6));
    printf("%d\n", choose(24, 7));
    printf("%d\n", choose(24, 8));
    printf("%d\n", choose(24, 9));
    printf("%d\n", choose(24, 10));
    printf("%d\n", choose(24, 11));
    printf("%d\n", choose(24, 12));
    printf("%d\n", choose(24, 13));
    printf("%d\n", choose(24, 14));
    printf("%d\n", choose(24, 15));
    printf("%d\n", choose(24, 16));
    printf("%d\n", choose(24, 17));
    printf("%d\n", choose(24, 18));
    printf("%d\n", choose(24, 19));
    printf("%d\n", choose(24, 20));
    printf("%d\n", choose(24, 21));
    printf("%d\n", choose(24, 22));
    printf("%d\n", choose(24, 23));
    printf("%d\n", choose(24, 24));
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


void asserting_status(){
    assert(choose(15, 4) == 1365);
    assert(choose(15, 15) == 1);
    assert(choose(15, 16) == 0); // 0 means that the entire thing is a failure and producing 0 combinations
    assert(choose(0, 0) == 1);
    assert(choose(25, 4) == 1);
    printf("All asserts for The Choose function were successful\n");
    assert(num_divisors_up_to_k(9, 9) == 3);
    assert(num_divisors_up_to_k(9, 3) == 2);
    printf("All asserts for The num_divisors_up_to_k function were successful\n");
    assert(is_prime(5) == 1);
    assert(is_prime(6) == 0);
    printf("All asserts for The is_prime function were successful\n");

}

int fib(int n) {
    if (n <= 1) {
        return n;
    }
    int F_nsub1 = fib(n - 1);
    int F_nsub2 = fib(n - 2);
    return F_nsub1 + F_nsub2;
}



int main(void) {
    //asserting_status();
//    printf("%d\n\n\n", combos(50, 10));
    printf("%ld\n", choose(10, 5));
    printf("%d\n", num_divisors_up_to_k(9, 3));
    printf("%d\n", is_prime(5));
    fib(5);
    //asserts_combos();
    printing();
    printf("We Won the Lottery");
}


long long int factorial(long long int n){
    if (n <= 1){
        return 1;
    }
    return n * factorial(n - 1);
}


long int choose(int n, int m){
    if (m > n) {
        printf("This is a failure of an input please try again.\nNote I am pushing through a zero as a sign I have zero"
               " respect for what was just inputted!\n");
        return 0;
    }
    long int calculations = (long int)(factorial(n) / (factorial(m) * factorial(n - m)));
    return calculations;
}

int num_divisors_up_to_k(int n, int k){
    int compt;
    if (n % k == 0)
        compt = 1;
    else
        compt = 0;
    if (k == 1)
        return compt;
    return compt + num_divisors_up_to_k(n, k-1);
}

bool is_prime(int n){
    int num = num_divisors_up_to_k(n, n);
    if (num == 2)
        return true;
    else
        return false;
}


int combos(int n, int m){
    if (m == 0 || n == m)
        return 1;
    return combos(n - 1, m) + combos(n - 1, m - 1);
}