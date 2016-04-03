#include<iostream>
#include<cstdlib>
using namespace std;
class Sudoku{
	public:
		Sudoku();//constructor
		void giveQuestion();//1
		void readIn();//2
		int getFirstZeroIndex();
		int checkRow(int blank);
		int checkCol(int blank);
		int checkSubGrid(int blank);
		void setLastIndex(int blank);
		int getLastIndex();
		bool isCorrect();
		void solve();//3
		void changeNum(int a,int b);//4
		void changeRow(int a,int b);//5
		void changeCol(int a,int b);//6
		void rotate(int n);//7
		void flip(int n);//8
		void change();
		void printOut();
		void transform();//9
		void setMap(const int set_map[]);//no use
		static const int sudokuSize=81;
    private:
		int map[sudokuSize];
		int copyMap[sudokuSize];
		int record[sudokuSize];//紀錄上次是填的Index
		int firstAnswer[sudokuSize];//存第一組解
		int times;
		bool checkUnity(int arr[]);
};
