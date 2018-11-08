/*
 *37. 解数独
 *
 *描述 编写一个程序，通过已填充的空格来解决数独问题。
 *		一个数独的解法需遵循如下规则：
 *		数字 1-9 在每一行只能出现一次。
 *		数字 1-9 在每一列只能出现一次。
 *		数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
 *		空白格用 '.' 表示。
 *
 *说明:
 *		给定数独序列只包含数字 1-9 和字符 '.' 。
 *		你可以假设给定的数独只有唯一解。
 *		给定数独永远是 9x9 形式的。
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h> 

 bool isRowValid(char **board, int nRow)
 {
	 if(nRow < 1 || nRow > 9)
		 return false;

	 int numCnt[9] = {0};
	 int i = 0;
	 int num = 0;
	 for(i=0; i<9; i++) {
		 num = board[nRow-1][i] - '0';
		 if(num < 1 || num > 9)
			 continue;
		 numCnt[num-1]++;
		 if(numCnt[num-1] > 1) {
			 return false;
		 }
	 }
 
	 return true;
 }
 
 bool isColValid(char **board, int nCol)
 {
	 if(nCol < 1 || nCol > 9)
		 return false;
 
	 int numCnt[9] = {0};
	 int i = 0;
	 int num;
	 for(i=0; i<9; i++) {
		 num = board[i][nCol-1] - '0';
		 if(num < 1 || num > 9)
			 continue;
		 numCnt[num-1]++;
		 if(numCnt[num-1] > 1){
			 return false;
		 }
	 }
 
	 return true;
 }
 bool isChunkValid(char **board, int nChunk)
 {
	 if(nChunk < 1 || nChunk > 9)
		 return false;
 
	 int numCnt[9] = {0};
	 int i = 0, j = 0;
	 int num;
 
	 int startRow = 0;
	 int startCol = 0;
 
	 switch(nChunk)
	 {
		 case 1:
			 startRow = 1;
			 startCol = 1;
			 break;
		 case 2:
			 startRow = 1;
			 startCol = 4;
			 break;
		 case 3:
			 startRow = 1;
			 startCol = 7;
			 break;
		 case 4:
			 startRow = 4;
			 startCol = 1;
			 break;
		 case 5:
			 startRow = 4;
			 startCol = 4;
			 break;
		 case 6:
			 startRow = 4;
			 startCol = 7;
			 break;
		 case 7:
			 startRow = 7;
			 startCol = 1;
			 break;
		 case 8:
			 startRow = 7;
			 startCol = 4;
			 break;
		 case 9:
			 startRow = 7;
			 startCol = 7;
			 break;
		 default:
			 return false;
	 }
	 
	 for(i=0; i<3; i++) {
		 for(j=0; j<3; j++) {
			 num = board[startRow+i-1][startCol+j-1] - '0';
			 if(num < 1 || num > 9)
				 continue;
			 numCnt[num-1]++;
			 if(numCnt[num-1] > 1){
				 return false;
			 }
		 }
	 }
 
	 return true;
 }
 
 bool isValidSudoku(char **board, int boardRowSize, int boardColSize) {
	 if(boardRowSize != 9 || boardColSize != 9)
		 return false;
	 
	 int i = 1, j = 0;
	 for(i=1; i<=9; i++) {
		 if(isRowValid(board, i) == false) {
			 return false;
		 }
	 }
 
	 for(i=1; i<=9; i++) {
		 if(isColValid(board, i) == false) {
			 return false;
		 }
	 }
 
	 for(i=1; i<=9; i++) {
		 if(isChunkValid(board, i) == false) {
			 return false;
		 }
	 }
 
	 return true;
}
 
 typedef struct {
	 int size;
	 char value[9];
 } BoardValue;

int getChunkIndex(int row, int col)
{
	int i = (row + 2) / 3;
	int j = (col - 1) / 3;

	if(i == 1) 
		return 1+j;
	else if(i == 2)
		return 4+j;
	else if(i == 3)
		return 7+j;
	else
		return 0;
}

int getAvailableValue(char** board, BoardValue valueTmp[9][9])
{
	int i,j,k;
	char c;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++) {
			if(board[i][j] >= '1'  && board[i][j] <= '9') {
				valueTmp[i][j].size = 1;
				valueTmp[i][j].value[0] = board[i][j];
			}
		}

	int nChunk;
	for(i=0; i<9; i++)
		for(j=0; j<9; j++) {
			if(board[i][j] == '.') {
				nChunk = getChunkIndex(i+1, j+1);
				for(c='1'; c<='9'; c++) {
					board[i][j] = c;
					if(isRowValid(board, i+1) == true && isColValid(board, j+1) && isChunkValid(board, nChunk) == true) {
						valueTmp[i][j].value[valueTmp[i][j].size++] = c;
					}
				}
				board[i][j] = '.';
			}
		}

	return 0;
}
bool testSolve(char** board, int startRow, int startCol, BoardValue valueTmp[9][9])
{
	int i, j, k;
	char c;
	int flagTmp = 0;

	for(i=startRow-1; i<9; i++) {
		for(j=startCol-1; j<9; j++) {
			if(board[i][j] == '.') {
				flagTmp = 1;
				for(k=0; k<valueTmp[i][j].size; k++) {
					board[i][j] = valueTmp[i][j].value[k];
					if((isRowValid(board, i+1) == true && isColValid(board, j+1) && isChunkValid(board, getChunkIndex(i+1, j+1)) == true))
					//if(isValidSudoku(board, 9, 9) == true) 
					{
						if(testSolve(board, i+1, j+1, valueTmp) == true)
							return true;
					} else
						continue;
				}
				board[i][j] = '.';
				return false;
			}
		}
		startCol = 1;
	}
	if(flagTmp == 0) {
		return isValidSudoku(board, 9, 9);
	}
	
	return false;
}

void solveSudoku(char** board, int boardRowSize, int boardColSize) {
	int i = 0, j = 0, k;
	char flag[9][9] = {0};
	for(i=0; i<9; i++)
		for(j=0; j<9; j++) {
			if(board[i][j] >= '1' && board[i][j] <= '9')
				flag[i][board[i][j]-'1'] = 1;
		}
	BoardValue valueTmp[9][9];
	memset(valueTmp, 0, sizeof(valueTmp));
	getAvailableValue(board, valueTmp);

	if (testSolve(board, 1, 1, valueTmp) == true)
		printf("Solve success\n");

	return;
}

int main()
{
	char board[9][10] =  {
						"53..7....",
						"6..195...",
						".98....6.",
						"8...6...3",
						"4..8.3..1",
						"7...2...6",
						".6....28.",
						"...419..5",
						"....8..79"
						};
	int i = 0;
	char *boardTmp[9];
	for(; i<9; i++)
		boardTmp[i] = board[i];

	struct timeval t1, t2;
	gettimeofday(&t1, NULL);

	solveSudoku(boardTmp, 9, 9);
	gettimeofday(&t2, NULL);
	
	printf("result is :\n");
	for(i=0; i<9; i++)
		printf("%s\n", board[i]);

	long tms = (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec / 1000) - (t1.tv_usec / 1000);
	printf("solve cost %lds, %ldms\n", tms/1000, tms%1000);
}

