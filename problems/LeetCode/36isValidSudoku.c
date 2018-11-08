/*
 *36. 有效的数独
 *
 *描述 判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。
 *		1.数字 1-9 在每一行只能出现一次。
 *		2.数字 1-9 在每一列只能出现一次。
 *		3.数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
 *
 *示例 1:
 *		输入:
 *		[
 *		  ["5","3",".",".","7",".",".",".","."],
 *		  ["6",".",".","1","9","5",".",".","."],
 *		  [".","9","8",".",".",".",".","6","."],
 *		  ["8",".",".",".","6",".",".",".","3"],
 *		  ["4",".",".","8",".","3",".",".","1"],
 *		  ["7",".",".",".","2",".",".",".","6"],
 *		  [".","6",".",".",".",".","2","8","."],
 *		  [".",".",".","4","1","9",".",".","5"],
 *		  [".",".",".",".","8",".",".","7","9"]
 *		]
 *		输出: true
 *示例 2:
 *		输入: 
 *		[
 *		  ["8","3",".",".","7",".",".",".","."],
 *		  ["6",".",".","1","9","5",".",".","."],
 *		  [".","9","8",".",".",".",".","6","."],
 *		  ["8",".",".",".","6",".",".",".","3"],
 *		  ["4",".",".","8",".","3",".",".","1"],
 *		  ["7",".",".",".","2",".",".",".","6"],
 *		  [".","6",".",".",".",".","2","8","."],
 *		  [".",".",".","4","1","9",".",".","5"],
 *		  [".",".",".",".","8",".",".","7","9"]
 *		]
 *		输出：false
 *		解释: 除了第一行的第一个数字从 5 改为 8 以外，空格内其他数字均与 示例1 相同。
 *    	 	   但由于位于左上角的 3x3 宫内有两个 8 存在, 因此这个数独是无效的。
 *说明:一个有效的数独（部分已被填充）不一定是可解的。
 *		只需要根据以上规则，验证已经填入的数字是否有效即可。
 *		给定数独序列只包含数字 1-9 和字符 '.' 。
 *		给定数独永远是 9x9 形式的。
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isRowValid(unsigned char **board, int nRow)
{
	if(nRow < 1 || nRow > 9)
		return false;

	int numCnt[9] = {0};
	int i = 0;
	int num = 0;
	printf("%s:check ", __FUNCTION__);
	for(i=0; i<9; i++) {
		printf("%c ", board[nRow-1][i]);
		num = board[nRow-1][i] - '0';
		if(num < 1 || num > 9)
			continue;
		numCnt[num-1]++;
		if(numCnt[num-1] > 1) {
			printf("\nnum = %d, col = %d\n", num, i+1);
			return false;
		}
	}
	printf("\n");

	return true;
}
bool isColValid(unsigned char **board, int nCol)
{
	if(nCol < 1 || nCol > 9)
		return false;

	int numCnt[9] = {0};
	int i = 0;
	int num;
	printf("%s:check ", __FUNCTION__);
	for(i=0; i<9; i++) {
		printf("%c ", board[i][nCol-1]);
		num = board[i][nCol-1] - '0';
		if(num < 1 || num > 9)
			continue;
		numCnt[num-1]++;
		if(numCnt[num-1] > 1){
			printf("num = %d, row = %d\n", num, i+1);
			return false;
		}
	}
	printf("\n");

	return true;
}
bool isChunkValid(unsigned char **board, int nChunk)
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
	
	printf("%s:check ", __FUNCTION__);
	for(i=0; i<3; i++) {
		for(j=0; j<3; j++) {
			printf("%c ", board[startRow+i-1][startCol+j-1]);
			num = board[startRow+i-1][startCol+j-1] - '0';
			if(num < 1 || num > 9)
				continue;
			numCnt[num-1]++;
			if(numCnt[num-1] > 1){
				printf("num = %d, row = %d, col = %d, startRow = %d, startCol = %d\n", num, startRow+i, startCol+j, startRow, startCol);
				return false;
			}
		}
	}
	printf("\n");

	return true;
}

bool isValidSudoku(unsigned char** board, int boardRowSize, int boardColSize) {
	if(boardRowSize != 9 || boardColSize != 9)
		return false;

	int i = 1;
	for(i=1; i<=9; i++) {
		if(isRowValid(board, i) == false) {
			printf("%d row is not valid\n", i);
			return false;
		}
	}

	for(i=1; i<=9; i++) {
		if(isColValid(board, i) == false) {
			printf("%d col is not valid\n", i);
			return false;
		}
	}

	for(i=1; i<=9; i++) {
		if(isChunkValid(board, i) == false) {
			printf("%d chunk is not valid\n", i);
			return false;
		}
	}

	return true;
}
int main()
{
	unsigned char *board[9] =  {
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
	printf("result is %s\n", isValidSudoku((unsigned char **)board, 9, 9) == true ? "true" : "false");
}
