#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */
#define NDIM 3 /* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM) /* total number of values in each row */

#define NGRP 3 /* number of sets each cell is a member of */
#define NSET (NGRP*NDIG) /* total number of sets in the sudoku */

#define NCLL (NDIG*NDIG) /* total number of cells in the sudoku */
#define ERROR (−1) /* error return value from some functions */

/* there are 27 different different sets of elements that need to be
checked against each other, this array converts set numbers to cells,
that’s why its called s2c */

int s2c[NSET][NDIM*NDIM] = {
  /* the first group of nine sets describe the sudoku’s rows */
  { 0, 1, 2, 3, 4, 5, 6, 7, 8 },
  { 9, 10, 11, 12, 13, 14, 15, 16, 17 },
  { 18, 19, 20, 21, 22, 23, 24, 25, 26 },
  { 27, 28, 29, 30, 31, 32, 33, 34, 35 },
  { 36, 37, 38, 39, 40, 41, 42, 43, 44 },
  { 45, 46, 47, 48, 49, 50, 51, 52, 53 },
  { 54, 55, 56, 57, 58, 59, 60, 61, 62 },
  { 63, 64, 65, 66, 67, 68, 69, 70, 71 },
  { 72, 73, 74, 75, 76, 77, 78, 79, 80 },
  /* the second group of nine sets describes the sudoku’s columns */
  { 0, 9, 18, 27, 36, 45, 54, 63, 72 },
  { 1, 10, 19, 28, 37, 46, 55, 64, 73 },
  { 2, 11, 20, 29, 38, 47, 56, 65, 74 },
  { 3, 12, 21, 30, 39, 48, 57, 66, 75 },
  { 4, 13, 22, 31, 40, 49, 58, 67, 76 },
  { 5, 14, 23, 32, 41, 50, 59, 68, 77 },
  { 6, 15, 24, 33, 42, 51, 60, 69, 78 },
  { 7, 16, 25, 34, 43, 52, 61, 70, 79 },
  { 8, 17, 26, 35, 44, 53, 62, 71, 80 },
  /* the last group of nine sets describes the inner squares */
  { 0, 1, 2, 9, 10, 11, 18, 19, 20 },
  { 3, 4, 5, 12, 13, 14, 21, 22, 23 },
  { 6, 7, 8, 15, 16, 17, 24, 25, 26 },
  { 27, 28, 29, 36, 37, 38, 45, 46, 47 },
  { 30, 31, 32, 39, 40, 41, 48, 49, 50 },
  { 33, 34, 35, 42, 43, 44, 51, 52, 53 },
  { 54, 55, 56, 63, 64, 65, 72, 73, 74 },
  { 57, 58, 59, 66, 67, 68, 75, 76, 77 },
  { 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};

/* there are 81 cells in a dimension−3 sudoku, and each cell is a
member of three sets, this array gets filled by the function
fill_c2s(), based on the defined contents of the array s2c[][] */

int c2s[NCLL][NGRP];

void
fill_c2s() {
  int s=0, d=0, c;
  for ( ; s<NSET; s++) {
    /* record the first set number each cell is part of */
    for (c=0; c<NDIM*NDIM; c++) {
      c2s[s2c[s][c]][d] = s;
    }
     if ((s+1)%(NGRP*NDIM) == 0) {
        d++;
     } 
   }
  
#if 0
  /* this code available here if you want to see the array
  cs2[][] that gets created, just change that 0 two lines back
  to a 1 and recompile */
  
  for (c=0; c<NCLL; c++) {
    printf("cell %2d: sets ", c);
    for (s=0; s<NGRP; s++) {
      printf("%3d", c2s[c][s]);
     }
     printf("\n");
   }
   printf("\n");
#endif
   return;
}

/* find the row number a cell is in, counting from 1 */
int
rownum(int c) {
  return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1 */

int
colnum(int c) {
  return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1 */
int
sqrnum(int c) {
  return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

#define MIN_CELL_NUM 1 /* Minimum and maximum values of each cell in sudoku */
#define MAX_CELL_NUM 9
#define MIN_SET_NUM 0 /* Minimum and maximum values of each set in sudoku */
#define MAX_SET_NUM 27
#define SET_CELL_VALUE 9 /* Number of cells in each set */

void sudoku_print(int sudoku[81], int val);
void viol_checker(int sudoku[81]);
void strategy_one(int sudoku[81], int zerocount);
void viol_display(int setnum,int count,int num);
void option_checker(int ptr[27],int *tally_num,int *label_num);
int *cellmate_finder(int zeroes_address[81],int sudoku[81],int zeronum,int *cellmates);
void run_pass(int sudoku[81],int label_ctr,int label_update[][2],int zerocount,
int label_loop[],int nochange_labelctr);

/****************************************************************/

/* main program controls all the action */
int
main(int argc, char *argv[]) {
  int sudoku[81];
  int i=0,zerocount=0;
  void fill_c2s();
  void exit(int status);

  fill_c2s();

  printf("\n");
  
  /* Read in the values for each cell in the sudoku and store it in an
  81−element array, simoultaneously counting blank cells */
  
  for (i=0;i<81;i++) {
    scanf("%d",&sudoku[i]);
    if (sudoku[i]==0) {
      zerocount++;
    }
  }
  
  /* Prints the sudoku */
  sudoku_print(sudoku,0);

  printf("\n\n");

  /* Checks for any violations in the cells */
  viol_checker(sudoku);
  
  /* Attempts to solve the sudoku by applying strategy one */
  strategy_one(sudoku,zerocount);
  
  return 0;
}

/******************************************************************************/

/* Prints the sudoku */
void
sudoku_print(int sudoku[81],int val) {
  int i=0,unknown=0;
  int square_block,row_block,row_num,square_row;
  
  for (square_block=0;square_block<NDIM;square_block++) {
    for (row_block=0;row_block<NDIM;row_block++) {
      for (row_num=0;row_num<NDIM;row_num++){
        for (square_row=0;square_row<NDIM;square_row++) {
          scanf("%d",&sudoku[i]);
          if (sudoku[i]==0) {
            if (colnum(i)!=1) {
              printf(" .");
            } else {
              printf(".");
            }
            unknown +=1;
          } else {
            if (colnum(i)!=1) {
              printf(" %d", sudoku[i]);
            } else {
              printf("%d", sudoku[i]);
            }
          }
          i++;
        }
        if (row_num<2) {
          printf(" |");
        }
      }
      printf("\n");
    }
    if (square_block<2) {
      printf("−−−−−−+−−−−−−−+−−−−−−\n");
    }
  }
  if (val==0) {
    printf("\n%d cells are unknown", unknown);
  } else {
    printf("\n %d cells are unknown", unknown);
  }
}

/*****************************************************************************/
/* Checks for any violation in the cells of sudoku */
void
viol_checker(int sudoku[81]) {
  int setnum,num,count,setcell;
  int find=0,uniqset=0,viol=0;

  /* Check for multiple instances of any number from 1 to 9 in each set */
  for (setnum=MIN_SET_NUM;setnum<MAX_SET_NUM;setnum++) {
    for(num=MIN_CELL_NUM;num<=MAX_CELL_NUM;num++) {
      count=0;
      for (setcell=0;setcell<SET_CELL_VALUE;setcell++) {
        if (sudoku[s2c[setnum][setcell]]==num &&
          sudoku[s2c[setnum][setcell]]!=0) {
        }
      }
     
      /* If atleast 2 instances found, count it as a violation */
      if (count>=2) {
        viol++;
        
        /* Find unique number of sets by checking for multiple
        violations in each set */
        if (setnum!=find) {
          uniqset++;
        }
        
        /* Displays the violations found in sudoku */
        viol_display(setnum,count,num);
        
        find = setnum;
      }
    }
  }
  /* Summary of violations found */
  if (viol!=0) {
    printf("\n%d different sets have violations\n",uniqset);
    printf("%d violations in total",viol);
    printf("\n");
    exit(0);
  }
}

/******************************************************************************/
/* Displays violations found in cells of sudoku */
void
viol_display(int setnum,int count,int num) {
  int set=0;
  
  /* Calculate set numbers for each of the violations and display it */
  if ((MIN_SET_NUM<=setnum)&& (setnum<9)) {
    set=setnum+1;
    printf("set %2d (row %d): %d instances of %d\n",setnum,set,
      count,num);
  } else if ((9<setnum) && (setnum<=17)) {
    set=setnum−8;
    printf("set %2d (col %d): %d instances of %d\n",setnum,set,
      count,num);
  } else {
    set=setnum−17;
    printf("set %2d (sqr %d): %d instances of %d\n",setnum,set,
      count,num);
  }
}
/*****************************************************************************/
/*Attempts to solve the sudoku by applying strategy one */

void
strategy_one(int sudoku[81], int zerocount) {
  int zeronum,y,tally_num,label_num,previous_labelctr;
  int x=0,label_ctr=0,s1_looper=1;
  int label_update[zerocount][2],cellmates[27],zeroes_address[zerocount];
  int label_loop[2]={0,1};
  int *ptr;
  
  /* Find the location of each blank cell and add to an array */
  for (y=0;y<81;y++) {
    if (sudoku[y]==0) {
      zeroes_address[x]=y;
      x++;
    }
  }
  
  while (s1_looper==1) {
    for (zeronum=0;zeronum<zerocount;zeronum++) {
      tally_num=0;

      /* Finds the cellmates of each blank cell and stores it in array */
      ptr=cellmate_finder(zeroes_address,sudoku,zeronum,cellmates);
      
      /* Checks available options to assign for each blank cell */
      option_checker(ptr,&tally_num,&label_num);

      /* If there is only one option left, assign number to cell */
      if (tally_num==1) {
      label_ctr++;
      
        /* Store the number assigned and location of each blank cell */
          label_update[label_ctr−1][0]=zeroes_address[zeronum];
          label_update[label_ctr−1][1]=label_num;
      }
    }
    previous_labelctr=label_loop[0];

    /* Runs through each pass and tries to assign values to blank cells */
    run_pass(sudoku,label_ctr,label_update,zerocount,label_loop,
      previous_labelctr);

    s1_looper=label_loop[1];

  }
}

/*****************************************************************************/
/* Finds the cellmates of each blank cell */
int
*cellmate_finder(int zeroes_address[81],int sudoku[81],int zeronum,int
  *cellmates) {
  int cellmate_num;
  int zeroset_cell=0,a=0;
  int zeroset[3];

  /* Find the cellmates of each blank cell */
  for (cellmate_num=MIN_SET_NUM;cellmate_num<MAX_SET_NUM;cellmate_num++) {
    if (cellmate_num==9 || cellmate_num==18) {
      a++;
      zeroset_cell=0;
    }
    /* Find all the sets each blank cell is a part of */
    zeroset[a]=c2s[zeroes_address[zeronum]][a];

    /* The values in these sets are the cellmates of the
    blank cell */
    cellmates[cellmate_num]=sudoku[s2c[zeroset[a]][zeroset_cell]];
    zeroset_cell++;
  }
  return cellmates;
}

/*****************************************************************************/
/* Checks available options to assign for each blank cell */

void
option_checker(int ptr[27],int *tally_num,int *label_num) {
  int q,find_num,cellmate_num;
  int magic9[9];
  
  /* Array consisting of numbers 1 to 9 */
  for (q=MIN_CELL_NUM;q<=MAX_CELL_NUM;q++) {
    magic9[q−1]=q;
  }
  
  /* Deducing options for blank cell */
  /* Find if numbers 1 to 9 are already in cellmates */
  for (find_num=MIN_CELL_NUM;find_num<=MAX_CELL_NUM;find_num++) {
    for(cellmate_num=MIN_SET_NUM;cellmate_num<MAX_SET_NUM;cellmate_num++) {

      /* If a number is already there */
      if (ptr[cellmate_num]==find_num) {

        /* Number is removed from options for blank cell */
        for (q=MIN_CELL_NUM;q<=MAX_CELL_NUM;q++) {
          if (magic9[q−1]==find_num) {
            magic9[q−1]=0;
          }
        }
      }
    }
  }
  for (q=MIN_CELL_NUM;q<=MAX_CELL_NUM;q++) {
    /* Count number of options remaining for blank cell */
    if (magic9[q−1]!=0) {
      *label_num=magic9[q−1];
      *tally_num=*tally_num+1;
    }
  }
}

/*****************************************************************************/
void
run_pass(int sudoku[81],int label_ctr,int label_update[][2],int zerocount, int
  label_loop[], int previous_labelctr) {
  int p=0,z;

  /* Check if there are any new values assigned to cells since the
  previous pass */

  /* Print sudoku if there is no change */
  if (previous_labelctr==label_ctr) {
    sudoku_print(sudoku,0);
    printf("\n");
    exit(0);
  }
  
  printf("strategy one\n");
  
  /* Print details of newly assigned values to cells since the previous
  pass */
  for (p=previous_labelctr+1;p<label_ctr+1;p++) {
    printf("row %d col %d must be %d\n",rownum(label_update[p−1][0]),
      colnum(label_update[p−1][0]),label_update[p−1][1]);
  }
  
  printf("\n");

  /* Update sudoku’s cell values */
  for (z=0;z<label_ctr;z++) {
    sudoku[label_update[z][0]]=label_update[z][1];
  }
  
  previous_labelctr=label_ctr;
  label_loop[0]=previous_labelctr;
  
  /* If all cells of the sudoku have been assigned a value, print solved
  sudoku */
  if (zerocount−label_ctr==0) {
    sudoku_print(sudoku,1);
    printf("\n\nta daa!!!\n");
    label_loop[1]=0;
  }
}
/* Algorithms are fun! */
/****************************************************************/
