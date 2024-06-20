#include <iostream>
#include <conio.h>
#include"game.h"
using namespace std;



Game g1;
int width = 0;
int fighter_x = 0;
int fighter_y = 0;
int bullet_x = 0;
int bullet_y = 0;
int bullet_x2 = 0;
int bullet_y2 = 0;
int enemy_x = 0;
int enemy_y = 0;
int score = 0;
int life = 0;
int height = 0;
Bullet b1(bullet_x, bullet_y);

Bullet b2(bullet_x2, bullet_y2);

Data d1(life, score, height, width);
EnemyFighter e1(enemy_x, enemy_y, width);
Fighter f1(fighter_x, fighter_y);

int main() {
	cout << "输入1游戏开始" << endl;
	cout << "输入0关闭" << endl;
	char input = _getch();
	if (input == '1') {
		g1.init(b1, d1, e1, f1);
		while (1) {
			g1.drawPicture(b1, b2, d1, e1, f1);

			g1.pcOperate(b1, b2, d1, e1, f1);

			g1.operateFighger(b1, b2, d1, e1, f1);
		}
	}
	if (input == '0') {
		cout << "游戏退出....." << endl;
		return 0;
	}

}
