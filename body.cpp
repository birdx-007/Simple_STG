#pragma warning(disable:4996)
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
#include <Windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
int height, width;//��Ϸ���ڴ�С
int mypos_x, mypos_y;//�Ի�λ��
int mybltpos_x, mybltpos_y;//�Ի��ӵ�λ��
int mypower,mybomb,myplayer;//�Ի��ӵ��˺��������������л�����
int enmpos_x, enmpos_y;//�л�λ��
int enmbltpos_x, enmbltpos_y;//�л��ӵ�λ��
int grace,score;//�Ի������������ܵ÷�
int enmhp, enmmaxhp, enmminhp;//�л�Ѫ����Ѫ��������
int enmspeedind;//�л��ٶ�ָ�꣨Խ��Խ����
void gotoxy(int x, int y)//��������������������ƶ���ԭ��λ�ý����ػ�
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void showgamemanu() {//��ʾ���˵�
	cout <<"��ˮ�߼���v1.0 by BirdX"<<endl<< "Welcome!" << endl << "1.Press z to begin." << endl << "2.Press a to exit." << endl;
input0:
	char input = _getch();
	if (input == 'z') 
		system("cls");
	else if (input == 'a') 
		exit(0);
	else 
		goto input0;
}
void showgamehelp() {//��ʾ��Ϸ����
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
void startupgame() {//��Ϸ��ʼ����
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
		if (i == 12) cout << "   ��";
		if (i == 13) cout << "    ˮ";
		if (i == 14) cout << "     ��";
		if (i == 15) cout << "      ��";
		if (i == 16) cout << "       ��";
		if (i == 18) cout << "  By BirdX";
		cout << endl;
	}
	cout << "++++++++++++++++++BASE+++++++++++++++++++" << endl << endl;
	cout /*<< "Grace: " << grace << endl */<< "Score: " << score << endl;
}
int updatewithoutinput() {
	if (mybltpos_y > -1) mybltpos_y--;//�Ի��ӵ��˶�
	if ((mybltpos_x == enmpos_x) && (mybltpos_y == enmpos_y)){
		enmhp--;
		mybltpos_y = -2;
	}//���ел�
	if (enmhp <= 0) { 
		if (enmhp <= 0) {
			score++;
		}//�л�������
		enmpos_x = rand() % width;
		enmpos_y = 0; 
		enmhp = rand() % enmmaxhp+enmminhp;
	}//�л��˳���Ļ���������Խ���±߽磩
	else {

	}//�л����ӵ�
	static int enmspeed = 0;
	if (enmspeed < enmspeedind)enmspeed++;
	if (enmspeed == enmspeedind) { enmpos_y++; enmspeed = 0; }//�л��ƶ�
	enmmaxhp = 5 + score / 2;
	enmminhp = 1 + score / 4;//�������߶����ӵл�Ѫ��������
	if (enmspeedind > 5) enmspeedind = 15 - score / 8;//�������߶����ӵл��ٶ�
	if ((enmpos_x == mypos_x) && (enmpos_y == mypos_y) || (enmbltpos_x == mypos_x) && (enmbltpos_y == mypos_y) || (enmpos_y >= height)) {
		cout << "\a";
		myplayer--;
		mybomb = 3;
		mypos_x = width / 2;
		mypos_y = height - 2;
		enmhp -= 114514;
		if(score>=2)score -= 2;
		_sleep(200);
	}//MISS��ʧ��
	if (myplayer == 0) return 0;
	else return 1;//�����ж�
}
void updatewithinput() {
	char input;
	if (_kbhit())  // �ж��Ƿ�������
	{
		input = _getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if ((input == 'a') && (mypos_x > 0))
			mypos_x--;  // λ������
		if ((input == 'd') && (mypos_x < width-1))
			mypos_x++;  // λ������
		if ((input == 'w') && (mypos_y > 0))
			mypos_y--;  // λ������
		if ((input == 's') && (mypos_y < height-1))
			mypos_y++;  // λ������
		if (input == ' ')  // �����ӵ�
		{
			mybltpos_y = mypos_y - 1;  // �����ӵ��ĳ�ʼλ���ڷɻ������Ϸ�
			mybltpos_x = mypos_x;
		}
		if ((input == 'x') && (mybomb > 0)) //�ͷű���
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