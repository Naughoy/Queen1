//���ݷ����ݹ��㷨��

#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;


bool Check(int rowCurrent, int *&NQueen){          // �жϺ��������Ǻ����г�ͻ������б�����г�ͻ������FALSE
	int i = 0;
	while (i < rowCurrent){
		if (NQueen[i] == NQueen[rowCurrent] ||(abs(NQueen[i] - NQueen[rowCurrent]) == abs(i - rowCurrent))){
			return false;
		}
		i++;
	}
	return true;
}


void Print(ofstream &os, int n, int *&NQueen){                    // ������NQeen������Ԫ�ضԱȣ�����֪��ÿ�лʺ�����λ��
	os << n << "�ʺ�\n";
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			os << (NQueen[i] == j ? 1 : 0);
			os << setw(2);
		}
		os << "\n";
	}

}

// �ݹ���N �ʺ����⣬�������һ������д�ӡ
void Solve(int rowCurrent, int *&NQueen, int n, int &count, ofstream &os){
	if (count == 0){
		if (rowCurrent == n)    // ��ǰ�������ף��������һ�����󣬽������
		{
			Print(os, n, NQueen);
			count++;
			return;
		}
		for (int i = 0; i < n; i++){
			NQueen[rowCurrent] = i;                   //�ӵ�һ�п�ʼ������һ�Ų飬ÿһ�д���������һ����             
			if (Check(rowCurrent, NQueen)){
				Solve(rowCurrent + 1, NQueen, n, count, os);  // ������һ��
			}
		}
	}
}

int main(){
	clock_t start, finish;
	while (1){
		ofstream open;
		open.open("result.txt", ios_base::app);    //����ļ��г�ʼ���ݣ�����ı�ĩ��ʼ��ӣ��޸���
		if (!open.is_open()) // �ж��ļ��Ƿ���ڡ�
		{
			cerr << "�Ҳ����ļ��� " << endl;
		}
		int count = 0;       // ��ļ���
		int n;
		cout << "����������Ĺ�ģn" << endl;
		cin >> n;
		if (n<4){
			cerr<< "�����ģ�������4" << endl;
			return 0;
		}
		int *NQueen = new int[n];
		start = clock();
		Solve(0, NQueen, n, count, open);
		finish = clock();
		open << n << "�ʺ����ʱ��Ϊ�� "<< finish - start <<endl<< endl;
		cout << n << "�ʺ����ʱ��Ϊ�� "<< finish - start << endl;
		delete NQueen;
		open.close();
		cout << endl;
	}
	return 0;
}