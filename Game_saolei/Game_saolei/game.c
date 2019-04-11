#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_ROW 9
#define MAX_COL 9
#define MINE_COUNT 10
int Menu(){
	printf("=================\n");
	printf("1.开始游戏\n");
	printf("0.退出游戏\n");
	printf("=================\n");
	int choose = 0;
	printf("请输入您的选择:");
	scanf("%d", &choose);
	printf("\n");
	return choose;
}
void Init(char show_map[MAX_ROW][MAX_COL],char mine_map[MAX_ROW][MAX_COL]){
	for (int row = 0; row < MAX_COL; row++){
		for (int col = 0; col < MAX_COL; col++){
			show_map[row][col]= '*';
		}
	}
	for (int row = 0; row < MAX_COL; row++){
		for (int col = 0; col < MAX_COL; col++){
			mine_map[row][col] = '0';
		}
	}
	int mine_count = MINE_COUNT;
	for (; mine_count>0; mine_count--){
		int row = rand() % MAX_ROW;  
		int col = rand() % MAX_COL;
		if (mine_map[row][col] == '1'){
			continue;
		}
		mine_map[row][col] = '1';
	}
}
void Print(char map[MAX_ROW][MAX_COL]){
	printf(" |");
	for (int col = 0; col < MAX_COL; col++){
		printf(" %d", col);
	}
	printf("\n");
	printf("  ");
	for (int row = 0; row < MAX_ROW; row++){
		printf("--");
	}
	printf("\n");
	for (int row = 0; row < MAX_ROW; row++){
		printf("%d|", row);
		for (int col = 0; col < MAX_COL; col++){
			printf(" %c", map[row][col]);
		}
		printf("\n");
	}
}
UpDateShowMap(int row,int col,char mine_map[MAX_ROW][MAX_COL],char show_map[MAX_ROW][MAX_COL] ){
	int count = 0;
	if (row - 1 >= 0 && col - 1 >= 0 && mine_map[row-1][col-1] == '1'){
		count++;
	}
	if (row - 1 >= 0 && mine_map[row-1][col] == '1'){
		count++;
	}
	if (row - 1 >= 0 && col+1<=MAX_COL && mine_map[row-1][col+1] == '1'){
		count++;
	}
	if (col - 1 >=0 && mine_map[row][col-1] == '1'){
		count++;
	}
	if (col + 1 <=MAX_COL && mine_map[row][col+1] == '1'){
		count++;
	}
	if (row + 1 <= MAX_ROW && col - 1 >= 0 && mine_map[row+1][col-1] == '1'){
		count++;
	}
	if (row + 1 <= MAX_ROW && mine_map[row+1][col] == '1'){
		count++;
	}
	if (row + 1 <= MAX_ROW && col + 1 <= MAX_COL && mine_map[row+1][col+1] == '1'){
		count++;
	}
	show_map[row][col] = count+'0';
}
void Game(){
	char show_map[MAX_ROW][MAX_COL];
	char mine_map[MAX_ROW][MAX_COL];
	Init(show_map, mine_map); //初始化棋盘
	int open_count = 0;
	while (1){
		system("cls");
		//Print(mine_map);     //调试用
		Print(show_map);       //打印棋盘
		printf("请输入您要翻开的坐标(row col):");
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		if (row >= MAX_ROW || row < 0 || col >= MAX_ROW || col < 0){
			printf("您的输入非法!\n");
			Sleep(1000);
			continue;
		}
		if (show_map[row][col] != '*'){
			printf("您输入的坐标已被翻开,请重新输入!\n");
			Sleep(1000);
			continue;
		}
		if (mine_map[row][col] == '1'){
			printf("啊偶!您踩中地雷了!\n");
			Print(mine_map);
			Sleep(1000);
			return;
		}
		++open_count;
		if (open_count == MAX_ROW*MAX_COL - MINE_COUNT){
			printf("VICTORY!");
			return;
		}
		UpDateShowMap(row,col,mine_map,show_map);  //判断被翻开格子的周围有几个雷
	}
}
int main(){
	srand((unsigned int)time(0));   //时间戳,随机数种子
	int choose = Menu();
	if (choose == 1){
		Game();
	}
	else if(choose==0) {
		printf("goodby!\n");
	}
	else{
		printf("你的输入有误\n");
	}
	system("pause");
	return 0;
}
