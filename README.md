# sudoku-solver

This is my submission for Assignment 1 of COMP10002 Foundations of Algorithms. The goal of sudoku is to complete a square grid of 9x9=81 cells using only the numbers from 1 to 9, in a way that has exactly one instance of each digit appearing in each column, in each row, and in each 3x3 sub-square.

## Overview
The task for this assignment is to develop a sudoku assistant that helps people solve their sudoku puzzles. I used a one-dimensional C array to store a linearized version of the sudoku matrix, and write functions that carry out useful operations, including checking for numbering violations, identifying any "it must be that value" cells, and perhaps even solving some easy puzzles through to completion.

![image](https://user-images.githubusercontent.com/95140934/224545414-dddcd9bd-92e4-4e28-bce1-1d48f0d1009f.png)

## Stage 1 - Reading and Printing
The input to the program will always be a set of 81 one-digit numbers, laid out as a sudoku grid, and with "0" used to represent empty cells. The program reads the input using a sequence of 81 calls to **scanf("%d", &val)** to avoid the need to deal with blank and newline characters. The use of a one-dimensional array of 81 values in the program is encouraged, rather than a 9x9 two-dimensional array.

![image](https://user-images.githubusercontent.com/95140934/224545447-f008a2a7-060e-4a7c-aa03-d8ff390a9841.png)

## Stage 2 - Grid Checking
The program checks the input grid for mistakes, to ensure that none of the 27 sets in the supplied puzzle have duplicate elements. Errors are reported according to their set number, from 0 to 26, and also by the set type ("row", "col", or "sqr") and the ordinal (counting from one) number of that set.

![image](https://user-images.githubusercontent.com/95140934/224545498-bc3fe2e4-ae3d-4805-85b2-d629e05eea52.png)

## Stage 3 - Implementing Strategy One
The program implements the simplest of the strategies, called "Strategy One," which is sufficient to solve "Easy"-grade sudokus. In Strategy One, each cell is considered in turn. The three sets that cell is a member of are examined, accumulating label counts from the (up to) 24 labeled cells in those three sets. If there is only one of the nine possible numbers that does not yet occur anywhere in the three sets, then it must be the label for cell c.

To implement this strategy, the program iterates over all cells, in row-major order, computing the valid options for each cell. Then it goes through again, using that information, looking for cells that have only one valid option and filling them in.

Note that further strategies must be added before even "Medium"-grade puzzles can be solved.
