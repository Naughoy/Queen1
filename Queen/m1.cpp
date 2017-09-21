//回溯法（递归算法）

#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;


bool Check(int rowCurrent, int *&NQueen){          // 判断函数，凡是横竖有冲突，或是斜线上有冲突，返回FALSE
	int i = 0;
	while (i < rowCurrent){
		if (NQueen[i] == NQueen[rowCurrent] ||(abs(NQueen[i] - NQueen[rowCurrent]) == abs(i - rowCurrent))){
			return false;
		}
		i++;
	}
	return true;
}


void Print(ofstream &os, int n, int *&NQueen){                    // 各列与NQeen数组中元素对比，即可知道每行皇后所在位置
	os << n << "皇后\n";
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			os << (NQueen[i] == j ? 1 : 0);
			os << setw(2);
		}
		os << "\n";
	}

}

// 递归解决N 皇后问题，到达最后一行则进行打印
void Solve(int rowCurrent, int *&NQueen, int n, int &count, ofstream &os){
	if (count == 0){
		if (rowCurrent == n)    // 当前行数触底，即完成了一个矩阵，将它输出
		{
			Print(os, n, NQueen);
			count++;
			return;
		}
		for (int i = 0; i < n; i++){
			NQueen[rowCurrent] = i;                   //从第一行开始往下逐一排查，每一行从左往右逐一检验             
			if (Check(rowCurrent, NQueen)){
				Solve(rowCurrent + 1, NQueen, n, count, os);  // 移向下一行
			}
		}
	}
}

int main(){
	clock_t start, finish;
	while (1){
		ofstream open;
		open.open("result.txt", ios_base::app);    //如果文件有初始内容，则从文本末开始添加，无覆盖
		if (!open.is_open()) // 判断文件是否存在。
		{
			cerr << "找不到文件！ " << endl;
		}
		int count = 0;       // 解的计数
		int n;
		cout << "请输入问题的规模n" << endl;
		cin >> n;
		if (n<4){
			cerr<< "问题规模必须大于4" << endl;
			return 0;
		}
		int *NQueen = new int[n];
		start = clock();
		Solve(0, NQueen, n, count, open);
		finish = clock();
		open << n << "皇后求解时间为： "<< finish - start <<endl<< endl;
		cout << n << "皇后求解时间为： "<< finish - start << endl;
		delete NQueen;
		open.close();
		cout << endl;
	}
	return 0;
}