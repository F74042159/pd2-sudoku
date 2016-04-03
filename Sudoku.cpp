#include"Sudoku.h"
Sudoku::Sudoku(){//constructor
	times=-1;
	for(int i=0;i<81;i++)
		record[i]=0;//初始化record[]
}
void Sudoku::giveQuestion(){
	int give_q[sudokuSize]={1,0,0,0,5,0,0,0,0,7,0,6,0,0,3,1,0,0,9,0,3,0,1,8,0,6,7,3,6,0,0,2,7,8,4,1,8,7,2,0,0,4,6,0,9,0,0,5,0,0,0,3,0,0,6,3,8,9,4,1,0,0,5,5,9,7,3,0,2,4,1,0,0,4,0,8,7,5,9,3,6};
	for(int i=0;i<sudokuSize;i++){
		cout<<give_q[i]<<" ";
		if(i%9==8)
			cout<<endl;
	}
}
void Sudoku::readIn(){
	for(int i=0;i<sudokuSize;i++){
		cin>>map[i];
	}
}
int Sudoku::getFirstZeroIndex(){
	for(int i=0;i<81;i++){
		if(copyMap[i]==0)
			return i;
	}
	return 81;
}
int Sudoku::checkRow(int blank){
	int row=blank/9;//check ?th row
	int rep=0;
	int check_row[9];
	for(int i=0;i<9;i++)
		check_row[i]=copyMap[row*9+i];
	for(int i=0;i<9;i++){//若與該列數字有重複 rep+1
		if((i+row*9)!=blank && check_row[i]==copyMap[blank])
			rep++;
	}
	return rep;
}
int Sudoku::checkCol(int blank){
	int col=blank % 9;//check ?th column
	int rep=0;
	int check_col[9];
	for(int i=0;i<9;i++)
		check_col[i]=copyMap[col+9*i];
	for(int i=0;i<9;i++){//若與該行數字有重複 rep+1
		if((i*9+col)!=blank && check_col[i]==copyMap[blank])
			rep++;
	}
	return rep;
}
int Sudoku::checkSubGrid(int blank){
	int sub = (blank/9)/3*27 + ((blank%9)/3)*3;//check which subgrid(0,3,6,27,30,33,54,57,60)
	int rep=0;
	int check_sub[9];
	for(int i=0;i<9;i++)
		check_sub[i]=copyMap[sub+(i/3)*9+(i%3)];
	for(int i=0;i<9;i++){//若與該九宮格數字有重複 rep+1
		if(sub+(i/3)*9+(i%3)!=blank && check_sub[i]==copyMap[blank])
			rep++;
	}
	return rep;
}
void Sudoku::setLastIndex(int blank){
	record[times]=blank;
}
int Sudoku::getLastIndex(){
	times--;
	return record[times];
}
bool Sudoku::isCorrect(){//check 一棋盤是否符合數獨規則(teacher)
	bool check_result;
	int check_arr[9];
	int location;
	for(int i=0;i<81;i+=9){//check rows
		for(int j=0;j<9;j++)
			check_arr[j]=map[i+j];
		check_result=checkUnity(check_arr);
		if(check_result==false)
			return false;
	}
	for(int i=0;i<9;i++){//check columns
		for(int j=0;j<9;j++)
			check_arr[j]=map[i+9*j];
		check_result=checkUnity(check_arr);
		if(check_result==false)
			return false;
	}
	for(int i=0;i<9;i++){//check cells
		for(int j=0;j<9;j++){
			location=27*(i/3)+3*(i%3)+9*(j/3)+(j%3);
			check_arr[j]=map[location];
		}
		check_result=checkUnity(check_arr);
		if(check_result==false)
			return false;
	}
	return true;
}

void Sudoku::solve(){
	 for(int i=0;i<sudokuSize;i++)
	      copyMap[i]=map[i];

	if(isCorrect()==false){//若題目就已經不符合數獨規則 直接判斷為無解
		cout<<"0"<<endl;
		exit(1);
	}

	int blank=0;
	int rep=0;
	int count=0;//填第幾組解
	blank=getFirstZeroIndex();
	times=times+1;//填第幾個(from 0)
	setLastIndex(blank);
	while(blank>=0 && blank<81){
		do{//第二次找解時copyMap[]裡面是第一組解的答案
			copyMap[blank]=copyMap[blank]+1;//guess from 1
			rep = checkRow(blank) + checkCol(blank) + checkSubGrid(blank);
		}while(rep!=0 && copyMap[blank]<=9);//若沒重複 找下一個空格
		
		if(copyMap[blank]>9){//若是因為填到超過9而跳出來的
			copyMap[blank]=0;//設回0 回上一個空格繼續找
			
			if(times==0){//若已經沒有上一格了 表無解 print out 0 並結束程式(第一次找解時無解 才是無解 第二次找解 若無解 表示只有一組解)
					if(count==0){//無解
						cout<<"0"<<endl;
						exit(1);
					}
					
					if(count==1){//若只有一組解 印出該解 並結束程式
						cout<<"1"<<endl;
						for(int i=0;i<81;i++){
							cout<<firstAnswer[i]<<" ";
							if(i % 9==8)
								cout<<endl;
						}
						exit(1);
					}
			}
			else blank=getLastIndex();//若已填到超過9 將該格設回0 回上一個空格繼續找
		}
		else{//若是因為沒重複而跳出來的 可填入數字 並找下一格
			blank=getFirstZeroIndex();//(找到沒有0的時候 getFirstZeroIndex()會回傳81 表示填完了)
			times=times+1;
			setLastIndex(blank);
		}

		if(blank==81 && count==0){//填完 blank會等於81 且 只有填完第一解時會進入
			record[times]=0;//前面多set一次record[] 設回0
			times=times-1;//前面多加了一次 減回來
			count++;//填完第一組解
			
			for(int i=0;i<81;i++){
				firstAnswer[i]=copyMap[i];//把第一組解存到firstAnswer
			}
			blank=record[times];//填第2解時 從上次填解時的最後一個空格開始填 進入while loop 不要把copyMap還原成原題目 留著第一組
		}//end if
	}//end while loop
	if(count==0 && blank==81){//若為沒有空格的棋盤
		cout<<"1"<<endl;
		for(int i=0;i<81;i++){//印出該解
			cout<<map[i]<<" ";
			if(i % 9==8)
				cout<<endl;
		}		
	}
	else{
		cout<<"2"<<endl;
		/*for(int i=0;i<81;i++){//印出第一解
	 		cout<<firstAnswer[i]<<" ";
	 		if(i % 9==8)
	 			cout<<endl;
	 	}
	 	cout<<endl;

	 	for(int i=0;i<81;i++){//印出第二解
	 		cout<<copyMap[i]<<" ";
			if(i % 9==8)
				cout<<endl;
		}*/
	}
}//end solve
void Sudoku::changeNum(int a,int b){
	for(int i=0;i<sudokuSize;i++){
		if(map[i]==a)
			map[i]=100;
	}
	for(int i=0;i<sudokuSize;i++){
		if(map[i]==b)
			map[i]=a;
	}
	for(int i=0;i<sudokuSize;i++){
		if(map[i]==100)
			map[i]=b;
	}
	  
}
void Sudoku::changeRow(int a,int b){
	int row_a[27]={0};
	int row_b[27]={0};
	for(int i=0;i<27;i+=9){//store 3 row in row_a[]
		for(int j=0;j<9;j++)
			row_a[i+j]=map[(i+a*27)+j];
	}
	for(int i=0;i<27;i+=9){//store 3 row in row_b[]
		for(int j=0;j<9;j++)
			row_b[i+j]=map[(i+b*27)+j];
	}
	for(int i=0;i<27;i+=9){//change 3*9 blocks of row
		for(int j=0;j<9;j++){
			map[(i+a*27)+j]=row_b[i+j];
			map[(i+b*27)+j]=row_a[i+j];
		}
	}
}
void Sudoku::changeCol(int a,int b){
	int col_a[27]={0};
	int col_b[27]={0};
	for(int i=0;i<3;i++){//store 3 column in col_a(3 row) and col_b(3 row)
		for(int j=0;j<9;j++){
			col_a[j+i*9]=map[(i+a*3)+9*j];
			col_b[j+i*9]=map[(i+b*3)+9*j];
		}
	}
	for(int i=0;i<3;i++){//change 9*3 blocks of column
		for(int j=0;j<9;j++){
			map[(i+a*3)+9*j]=col_b[j+i*9];
			map[(i+b*3)+9*j]=col_a[j+i*9];
		}
	}
}
void Sudoku::rotate(int n){
	int rotate[sudokuSize]={0};
	if(n%4==0){//rotate 0 degree
		for(int i=0;i<sudokuSize;i++)
			rotate[i]=map[i];
	}
	if(n%4==1){//rotate 90 degree
	    for(int i=0;i<81;i+=9){
			for(int j=0;j<9;j++)
				rotate[8*(j+1)+j-(i/9)]=map[i+j];
		}
	}
	if(n%4==2){//rotate 180 degree
		for(int i=0;i<81;i+=9){
			for(int j=0;j<9;j++)
				rotate[80-i-j]=map[i+j];
		}
	}
	if(n%4==3){//rotate 270 degree
		for(int i=0;i<81;i+=9){
			for(int j=0;j<9;j++)
				rotate[9*(8-j)+(i/9)]=map[i+j];
		}
	}
	for(int i=0;i<sudokuSize;i++){//assign rotate[81] to map[81]
		map[i]=rotate[i];
	}
}
void Sudoku::flip(int n){
	int flip[sudokuSize]={0};
	if(n==0){//flip vertically
		for(int i=0;i<81;i+=9){
			for(int j=0;j<9;j++){
				flip[72+j-i]=map[i+j];
			}
		}
	}
	if(n==1){//flip horizontally
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				flip[(8-i+9*j)]=map[i+9*j];
			}
		}
	}
	for(int i=0;i<81;i++)
		map[i]=flip[i];
}
void Sudoku::change(){
	srand(time(NULL));
	//int x=rand()%5+1;
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
}
void Sudoku::printOut(){
	cout<<endl;
	for(int i=0;i<sudokuSize;i++){
		cout<<map[i]<<" ";
		if(i%9==8)
			cout<<endl;
	}
}
void Sudoku::transform(){
	//readIn();
	change();
	printOut();
}
void Sudoku::setMap(const int set_map[]){
	for(int i=0;i<sudokuSize;i++)
		map[i]=set_map[i];
}
bool Sudoku::checkUnity(int arr[]){//check 1-9 是否每個數只出現一次(teacher)
	int arr_unity[9];
	for(int i=0;i<9;i++)
		arr_unity[i]=0;
	for(int i=0;i<9;i++){
		if((arr[i]-1)!=-1){//若測到0 不計次
			++arr_unity[arr[i]-1];
		}
	}
	for(int i=0;i<9;i++)
		if(arr_unity[i]>1)
			return false;
	return true;
}
