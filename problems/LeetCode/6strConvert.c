/*
 *6. Z字形变换
 *
 *描述 将字符串 "PAYPALISHIRING" 以Z字形排列成给定的行数：
 *
 *		P   A   H   N
 *		A P L S I I G
 *		Y   I   R
 *		之后从左往右，逐行读取字符："PAHNAPLSIIGYIR"
 *
 *		实现一个将字符串进行指定行数变换的函数:
 *
 *		string convert(string s, int numRows);
 *示例	输入: s = "PAYPALISHIRING", numRows = 3
 *		输出: "PAHNAPLSIIGYIR"
 *
 *		输入: s = "PAYPALISHIRING", numRows = 4
 *		输出: "PINALSIGYAHRPI"
 *		解释:
 *
 *		P     I    N
 *		A   L S  I G
 *		Y A   H R
 *		P     I
 */

char* convert(char* s, int numRows) {
    if(NULL == s || strlen(s) <= 1 || numRows <= 1)
        return s;
	int numColumns = strlen(s);
	char arry[numRows][numColumns];
	memset(arry, 0, numColumns*numRows);

	int column = 0;
	int row = 0;

	int i = 0;
	for(i=0; i<numColumns; i++) {
		arry[row][column] = s[i];
		if(column%(numRows-1) == 0) {
			if(row == numRows - 1) {
				row--;
				column++;
			} else {
				row++;
			}
				
		} else {
			row--;
			column++;
		}
	}
	
	char *result = (char *)malloc(numColumns + 1);
	result[numColumns] = '\0';

	int j = 0;
	int k = 0;
	for(i=0; i<numRows; i++) {
		for(j=0; j<numColumns; j++) {
			if(arry[i][j] != 0){
				result[k] = arry[i][j];
				k++;
                if(k >= numColumns)
					break;
			}
        }
        if(k >= numColumns)
			break;
    }

	return result;  

}



