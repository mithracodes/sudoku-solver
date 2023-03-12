# sudoku-solver

This is my submission for ***Assignment 1 of COMP10002 Foundations of Algorithms in Sem 2 2021***. The goal of sudoku is to complete a square grid of 9x9=81 cells using only the numbers from 1 to 9, in a way that has exactly one instance of each digit appearing in each column, in each row, and in each 3x3 sub-square.

## Overview
The task for this assignment is to develop a sudoku assistant that helps people solve their sudoku puzzles. I used a one-dimensional C array to store a linearized version of the sudoku matrix, and write functions that carry out useful operations, including checking for numbering violations, identifying any "it must be that value" cells, and perhaps even solving some easy puzzles through to completion.

## Stage 1 - Reading and Printing
The input to the program will always be a set of 81 one-digit numbers, laid out as a sudoku grid, and with "0" used to represent empty cells. The program reads the input using a sequence of 81 calls to **scanf("%d", &val)** to avoid the need to deal with blank and newline characters. The use of a one-dimensional array of 81 values in the program is encouraged, rather than a 9x9 two-dimensional array.


*Fig. 1: Input data1.txt*
```
0 5 1  0 7 0  9 2 3
0 0 6  9 0 2  4 1 0
2 9 3  0 1 4  0 0 7

0 8 0  0 5 0  1 0 9
6 0 0  0 9 7  0 0 0
5 1 9  0 0 3  0 6 0

1 2 5  0 8 0  0 0 6
0 6 0  0 2 0  0 9 0
9 3 8  0 0 0  0 0 0

``` 

*Fig. 2: corresponding Stage 1 output*
``` 
. 5 1 | . 7 . | 9 2 3
. . 6 | 9 . 2 | 4 1 .
2 9 3 | . 1 4 | . . 7
------+-------+------
. 8 . | . 5 . | 1 . 9
6 . . | . 9 7 | . . .
5 1 9 | . . 3 | . 6 .
------+-------+------
1 2 5 | . 8 . | . . 6
. 6 . | . 2 . | . 9 .
9 3 8 | . . . | . . .

41 cells are unknown
``` 
*Fig. 3: input data2.txt*
``` 
0 5 1  0 7 0  9 2 3
0 0 6  9 0 2  4 1 0
2 9 3  0 1 4  0 0 7

0 8 0  0 5 0  1 0 9
6 0 0  0 9 7  0 0 0
5 1 9  0 0 3  0 6 0

1 2 5  2 8 0  0 0 6
0 6 0  0 2 0  0 9 0
9 3 8  9 0 2  2 0 9
```  

## Stage 2 - Grid Checking
The program checks the input grid for mistakes, to ensure that none of the 27 sets in the supplied puzzle have duplicate elements. Errors are reported according to their set number, from 0 to 26, and also by the set type ("row", "col", or "sqr") and the ordinal (counting from one) number of that set.


*Fig. 4: Stage 2 output (data2.txt)*
``` 
set 6 (row 7): 2 instances of 2
set 8 (row 9): 2 instances of 2
set 8 (row 9): 3 instances of 9
set 12 (col 4): 2 instances of 9
set 14 (col 6): 2 instances of 2
set 17 (col 9): 2 instances of 9
set 25 (sqr 8): 3 instances of 2
set 26 (sqr 9): 2 instances of 9

7 different sets have violations
8 violations in total
``` 

## Stage 3 - Implementing Strategy One
The program implements the simplest of the strategies, called "Strategy One," which is sufficient to solve "Easy"-grade sudokus. In Strategy One, each cell is considered in turn. The three sets that cell is a member of are examined, accumulating label counts from the (up to) 24 labeled cells in those three sets. If there is only one of the nine possible numbers that does not yet occur anywhere in the three sets, then it must be the label for cell c.

To implement this strategy, the program iterates over all cells, in row-major order, computing the valid options for each cell. Then it goes through again, using that information, looking for cells that have only one valid option and filling them in.

Note that further strategies must be added before even "Medium"-grade puzzles can be solved.


*Fig. 5: Stage 3 (Strategy One) output for file data1.txt.*
``` 
strategy one

row 2 col 2 must be 7
row 2 col 5 must be 3
row 4 col 6 must be 6
row 5 col 2 must be 4
row 6 col 5 must be 4
row 7 col 6 must be 9

strategy one
row 1 col 6 must be 8
row 2 col 1 must be 8
row 4 col 4 must be 2
row 5 col 3 must be 2
row 9 col 5 must be 6

....

4 5 1 | 6 7 8 | 9 2 3
8 7 6 | 9 3 2 | 4 1 5
2 9 3 | 5 1 4 | 6 8 7
------+-------+------
3 8 7 | 2 5 6 | 1 4 9
6 4 2 | 1 9 7 | 5 3 8
5 1 9 | 8 4 3 | 7 6 2
------+-------+------
1 2 5 | 4 8 9 | 3 7 6
7 6 4 | 3 2 5 | 8 9 1
9 3 8 | 7 6 1 | 2 5 4

0 cells are unknown
ta daa!!!
``` 
