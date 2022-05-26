#pragma warning(disable:4996)
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
#include <Windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
int height, width;//游戏窗口大小
int mypos_x, mypos_y;//自机位置
int mybltpos_x, mybltpos_y;//自机子弹位置
int mypower,mybomb,myplayer;//自机子弹伤害、保险数量、残机数量
int enmpos_x, enmpos_y;//敌机位置
int enmbltpos_x, enmbltpos_y;//敌机子弹位置
int grace,score;//自机擦弹分数、总得分
int enmhp, enmmaxhp, enmminhp;//敌机血量与血量上下限
int enmspeedind;//敌机速度指标（越大越慢）
void gotoxy(int x, int y)//类似于清屏函数，光标移动到原点位置进行重画
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void showgamemanu() {//显示主菜单
	cout <<"背水者纪事v1.0 by BirdX"<<endl<< "Welcome!" << endl << "1.Press z to begin." << endl << "2.Press a to exit." << endl;
input0:
	char input = _getch();
	if (input == 'z') 
		system("cls");
	else if (input == 'a') 
		exit(0);
	else 
		goto input0;
}
void showgamehelp() {//显示游戏帮助
	system("cls");
	cout << "Game Help" << endl;
	cout << "1.Protect YOURSELF and your BASE from enemies." << endl;
	cout << "2.Enemies will become stronger and faster with time going on." << endl;
	cout << "3.Use w,a,s,d to move." << endl;
	cout << "4.Use space to shoot." << endl;
	cout << "5.Use x to release bomb." << endl;
	_sleep(1000);
	cout << endl << "begin in";
	for (int i = 5; i >= 1; i--) {
		cout << " " << i << "\a";
		_sleep(1000);
	}
	system("cls");
}
void startupgame() {//游戏初始化用
	height = 20;
	width = 40;
	mypos_x = width / 2;
	mypos_y = height - 2;
	mybltpos_x = mypos_x;
	mybltpos_y = -2;
	enmpos_x = mypos_x;
	enmpos_y = 2;
	enmbltpos_x = enmpos_x;
	enmbltpos_y = -2;
	mypower = 1;
	mybomb = 3;
	myplayer = 3;
	enmhp = 1;
	enmmaxhp = 5;
	enmminhp = 1;
	enmspeedind = 15;
	score = grace = 0;
}
void show() {
	//system("cls");
	gotoxy(0, 0);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if ((i == mypos_y) && (j == mypos_x))
				cout << '*';
			else if ((i == mybltpos_y) && (j == mybltpos_x))
				cout << '|';
			else if ((i == enmpos_y) && (j == enmpos_x))
				cout << '#';
			else if ((i == enmbltpos_y) && (j == enmbltpos_x))
				cout << '.';
			else cout << ' ';
		}
		cout << '|';
		if (i == 3) {
			cout << " Player: " << myplayer;
		}
		if (i == 4) {
			cout << " Bomb: " << mybomb;
		}
		if (i == 12) cout << "   背";
		if (i == 13) cout << "    水";
		if (i == 14) cout << "     者";
		if (i == 15) cout << "      纪";
		if (i == 16) cout << "       事";
		if (i == 18) cout << "  By BirdX";
		cout << endl;
	}
	cout << "++++++++++++++++++BASE+++++++++++++++++++" << endl << endl;
	cout /*<< "Grace: " << grace << endl */<< "Score: " << score << endl;
}
int updatewithoutinput() {
	if (mybltpos_y > -1) mybltpos_y--;//自机子弹运动
	if ((mybltpos_x == enmpos_x) && (mybltpos_y == enmpos_y)){
		enmhp--;
		mybltpos_y = -2;
	}//击中敌机
	if (enmhp <= 0) { 
		if (enmhp <= 0) {
			score++;
		}//敌机被击落
		enmpos_x = rand() % width;
		enmpos_y = 0; 
		enmhp = rand() % enmmaxhp+enmminhp;
	}//敌机退出屏幕（被击落或越过下边界）
	else {

	}//敌机放子弹
	static int enmspeed = 0;
	if (enmspeed < enmspeedind)enmspeed++;
	if (enmspeed == enmspeedind) { enmpos_y++; enmspeed = 0; }//敌机移动
	enmmaxhp = 5 + score / 2;
	enmminhp = 1 + score / 4;//随分数提高而增加敌机血量上下限
	if (enmspeedind > 5) enmspeedind = 15 - score / 8;//随分数提高而增加敌机速度
	if ((enmpos_x == mypos_x) && (enmpos_y == mypos_y) || (enmbltpos_x == mypos_x) && (enmbltpos_y == mypos_y) || (enmpos_y >= height)) {
		cout << "\a";
		myplayer--;
		mybomb = 3;
		mypos_x = width / 2;
		mypos_y = height - 2;
		enmhp -= 114514;
		if(score>=2)score -= 2;
		_sleep(200);
	}//MISS或失守
	if (myplayer == 0) return 0;
	else return 1;//死亡判定
}
void updatewithinput() {
	char input;
	if (_kbhit())  // 判断是否有输入
	{
		input = _getch();  // 根据用户的不同输入来移动，不必输入回车
		if ((input == 'a') && (mypos_x > 0))
			mypos_x--;  // 位置左移
		if ((input == 'd') && (mypos_x < width-1))
			mypos_x++;  // 位置右移
		if ((input == 'w') && (mypos_y > 0))
			mypos_y--;  // 位置上移
		if ((input == 's') && (mypos_y < height-1))
			mypos_y++;  // 位置下移
		if (input == ' ')  // 发射子弹
		{
			mybltpos_y = mypos_y - 1;  // 发射子弹的初始位置在飞机的正上方
			mybltpos_x = mypos_x;
		}
		if ((input == 'x') && (mybomb > 0)) //释放保险
		{
			cout << "\a"<<"\a";
			enmhp -= 114514;
			mybomb--;
			_sleep(750);
		}
	}
}
int main() {
	showgamemanu();
	showgamehelp();
	startupgame();
	int gamegoingon = 1;
	//PlaySound(TEXT("CompleteDarkness.wav"), NULL, SND_FILENAME | SND_NOSTOP | SND_LOOP | SND_ASYNC);
	while (1) {
		updatewithinput();
		show();
		gamegoingon=updatewithoutinput();
		if (gamegoingon == 0) break;
	}
	//PlaySound(NULL, NULL, NULL);
	system("cls");
	cout <<'\a'<< "Game Over!" << endl << "You(or your base) have been destroyed." << endl << "Your score: " << score << endl;
	_sleep(3000);
	system("pause");
	return 0;
}