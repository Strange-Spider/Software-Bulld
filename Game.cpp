#include"game.h"
#include<Windows.h>
#include<conio.h>
#include <iostream>
using namespace std;
Game::Game() : bullet(), data(), enemyFighter(), fighter() {
	bullet;
	data;
	enemyFighter;
	fighter;
}
void Game::init(Bullet& bullet,
	Data& data,
	EnemyFighter& enemyFighter,
	Fighter& fighter) {
	HideC();
	data.height = 28;
	data.width = 60;
	data.life = 3;
	data.score = 0;

	fighter.fighter_x = (2 * data.height) / 3;
	fighter.fighter_y = data.width / 2;
	bullet.bullet_x = fighter.fighter_x - 1;
	bullet.bullet_y = fighter.fighter_y;
	enemyFighter.enemy_x = 2;
	enemyFighter.enemy_y = rand() % (data.width - 5) + 2;
}

//清屏效果
void Game::HideC() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//隐藏光标函数
void Game::zeroXy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//游戏结束时绘制画面
void Game::drawEndScreen(Data data) {
	zeroXy(0, 0);
	for (int x = 0; x < data.height + 1; x++) {
		for (int y = 0; y < data.width + 1; y++) {
			if (x == data.height / 2 && y == data.width / 2) {
				cout << "Final Score: " << data.score;
			}
			else if (x == (data.height / 2) - 1 && y == data.width / 2) {
				cout << "Life: " << data.life;
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}


void Game::operateFighger(Bullet& bullet1, Bullet& bullet2,
	Data& data,
	EnemyFighter& enemyFighter,
	Fighter& fighter) {
	if (data.life > 0) { // 只有当生命值大于0时才处理输入
		if (_kbhit()) {
			static int flag;
			char input = _getch();
			switch (input) {
			case 'a': fighter.fighter_y--;//左移
				break;
			case 'w': fighter.fighter_x--;//上移
				break;
			case 's': fighter.fighter_x++;//下移
				break;
			case 'd': fighter.fighter_y++;//右移
				break;
			case ' ':
				// 发射子弹逻辑
				if (flag < 500) { // 确保不会同时发射超过两颗子弹
					bullet1.bullet_x = fighter.fighter_x - 1;
					bullet1.bullet_y = fighter.fighter_y;
					if (flag == 1) {
						bullet2.bullet_x = fighter.fighter_x - 1;
						bullet2.bullet_y = fighter.fighter_y;
					}
					flag++;
				}
				break;
			}

			// 边界检查并减少生命值
			if (fighter.fighter_x < 2 || fighter.fighter_x > data.height - 3) {
				data.life--; // 减少生命值
				fighter.fighter_x = (2 * data.height) / 3; // 重置战斗机 x 坐标
				fighter.fighter_y = data.width / 2; // 重置战斗机 y 坐标
			}
			if (fighter.fighter_y < 2 || fighter.fighter_y > data.width - 3) {
				data.life--; // 减少生命值
				fighter.fighter_x = (2 * data.height) / 3;
				fighter.fighter_y = data.width / 2;
			}
			// 敌机与战斗机碰撞检测,
			if ((fighter.fighter_x == enemyFighter.enemy_x && fighter.fighter_y == enemyFighter.enemy_y)) {
				data.life--;
				fighter.fighter_x = (2 * data.height) / 3;
				fighter.fighter_y = data.width / 2;
			}
			//改进后：为战机所有范围都会被检测到

		// 绘制当前游戏状态
			drawPicture(bullet1, bullet2, data, enemyFighter, fighter);
		}
	}
	else if (data.life == 0) {
		// 生命值为0，显示游戏结束界面，并退出函数
		drawEndScreen(data);
		return;
	}
}

void Game::drawPicture(
	Bullet bullet1,
	Bullet bullet2,
	Data data,
	EnemyFighter enemyFighter,
	Fighter fighter) {
	if (data.life <= 0) {
		//游戏结束，界面

		drawEndScreen(data);
		return;
	}
	//游戏上下边框和飞机子弹敌机
	else {
		zeroXy(0, 0);
		for (int x = 0; x < data.height + 1; x++) {
			for (int y = 0; y < data.width + 1; y++) {
				if (x == 1 && y == 1 * data.width / 5.0) {
					cout << "Score：" << data.score;
				}
				if (x == 1 && y == 3 * data.width / 5.0) {
					cout << "Life：" << data.life;
				}
				else if (x > 0 && x < data.height - 1 && y == 1) {
					cout << "|";
				}
				if (x > 0 && x < data.height - 1 && y == data.width - 1) {
					cout << "|";
				}
				else if (x == 0) {
					cout << "=";
				}
				else if (x == data.height) {
					cout << "=";
				}
				else if ((x == fighter.fighter_x) && (y == fighter.fighter_y)) {
					cout << "*";
				}
				else if ((x == fighter.fighter_x + 1) && (y == fighter.fighter_y)) {
					cout << "*";
				}
				else if ((x == fighter.fighter_x + 1) && (y == fighter.fighter_y - 1)) {
					cout << "*";
				}
				else if ((x == fighter.fighter_x + 1) && (y == fighter.fighter_y + 1)) {
					cout << "*";
				}
				else if ((x == fighter.fighter_x + 2) && (y == fighter.fighter_y - 1)) {
					cout << "|";
				}
				else if ((x == fighter.fighter_x + 2) && (y == fighter.fighter_y + 1)) {
					cout << "|";
				}
				else if ((x == enemyFighter.enemy_x) && (y == enemyFighter.enemy_y)) {
					cout << "@";
				}
				else if ((x == bullet1.bullet_x) && (y == bullet1.bullet_y)) {
					cout << "|";
				}
				else if ((x == bullet2.bullet_x) && (y == bullet2.bullet_y)) {
					cout << "|";
				}
				else {
					cout << " ";
				}
			}
			cout << endl;
		}
	}
}
s


EnemyFighter Game::generateNewEnemyFighter(int width) {
	// 随机生成敌机的 x 和 y 坐标
	int newX = 2;
	int newY = rand() % (width - 5) + 2;
	return EnemyFighter(newX, newY, width );
}
void Game::floatBullet(Bullet& bullet, Bullet& bullet2,
	Data& data,
	EnemyFighter& enemyFighter,
	Fighter& fighter) {
	bullet2.bullet_x--;
	bullet.bullet_x--;

	if ((bullet.bullet_x == enemyFighter.enemy_x) && (bullet.bullet_y == enemyFighter.enemy_y)) {
		data.score++;
		enemyFighter = generateNewEnemyFighter(data.width);
		EnemyFighter nf(enemyFighter.enemy_x, enemyFighter.enemy_y, data.width);

		while (1) {
			drawPicture(bullet, bullet2, data, nf, fighter);
			pcOperate(bullet, bullet2, data, nf, fighter);
			operateFighger(bullet, bullet2, data, nf, fighter);
		}

	}

	if ((bullet2.bullet_x == enemyFighter.enemy_x) && (bullet2.bullet_y == enemyFighter.enemy_y)) {
		data.score++;
		EnemyFighter nf(enemyFighter.enemy_x, enemyFighter.enemy_y, data.width);

		while (1) {
			drawPicture(bullet, bullet2, data, nf, fighter);
			pcOperate(bullet, bullet2, data, nf, fighter);
			operateFighger(bullet, bullet2, data, nf, fighter);
		}

	}

}


void Game::pcOperate(Bullet& bullet, Bullet& bullet2,
	Data& data,
	EnemyFighter& enemyFighter,
	Fighter& fighter) {

	static int speed = 0;
	if (data.score <= 3 && speed < 15) {
		speed++;
		if (speed == 15) {
			enemyFighter.enemy_x++;
			speed = 0;
		}
	}
	static int speed2 = 0;
	if (data.score <= 10 && data.score > 3 && speed2 < 10) {
		speed2++;
		if (speed2 == 10) {
			enemyFighter.enemy_x++;
			speed2 = 0;
		}
	}
	static int speed3 = 0;
	if (data.score > 10 && speed3 < 7) {
		speed3++;
		if (speed3 == 7) {
			enemyFighter.enemy_x++;
			speed3 = 0;
		}
	}

	if ((bullet.bullet_x == enemyFighter.enemy_x) && (bullet.bullet_y == enemyFighter.enemy_y)) {
		// EnemyFighter enemyFighter(enemyFighter.enemy_x, enemyFighter.enemy_y,data.width);
		data.score++;
	}//击中加分

	//没有击中扣分,生成新的敌机
	if ((enemyFighter.enemy_x > data.height)) {

		EnemyFighter nf(enemyFighter.enemy_x, enemyFighter.enemy_y, data.width);

		while (1) {
			drawPicture(bullet, bullet2, data, nf, fighter);
			pcOperate(bullet, bullet2, data, nf, fighter);
			operateFighger(bullet, bullet2, data, nf, fighter);
		}
	}
	for (int i = 0; i < 2; i++) {
		floatBullet(bullet, bullet2, data, enemyFighter, fighter);
	}

}