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

//����Ч��
void Game::HideC() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//���ع�꺯��
void Game::zeroXy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//��Ϸ����ʱ���ƻ���
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
	if (data.life > 0) { // ֻ�е�����ֵ����0ʱ�Ŵ�������
		if (_kbhit()) {
			static int flag;
			char input = _getch();
			switch (input) {
			case 'a': fighter.fighter_y--;//����
				break;
			case 'w': fighter.fighter_x--;//����
				break;
			case 's': fighter.fighter_x++;//����
				break;
			case 'd': fighter.fighter_y++;//����
				break;
			case ' ':
				// �����ӵ��߼�
				if (flag < 500) { // ȷ������ͬʱ���䳬�������ӵ�
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

			// �߽��鲢��������ֵ
			if (fighter.fighter_x < 2 || fighter.fighter_x > data.height - 3) {
				data.life--; // ��������ֵ
				fighter.fighter_x = (2 * data.height) / 3; // ����ս���� x ����
				fighter.fighter_y = data.width / 2; // ����ս���� y ����
			}
			if (fighter.fighter_y < 2 || fighter.fighter_y > data.width - 3) {
				data.life--; // ��������ֵ
				fighter.fighter_x = (2 * data.height) / 3;
				fighter.fighter_y = data.width / 2;
			}
			// �л���ս������ײ���,
			if ((fighter.fighter_x == enemyFighter.enemy_x && fighter.fighter_y == enemyFighter.enemy_y)) {
				data.life--;
				fighter.fighter_x = (2 * data.height) / 3;
				fighter.fighter_y = data.width / 2;
			}
			//�Ľ���Ϊս�����з�Χ���ᱻ��⵽

		// ���Ƶ�ǰ��Ϸ״̬
			drawPicture(bullet1, bullet2, data, enemyFighter, fighter);
		}
	}
	else if (data.life == 0) {
		// ����ֵΪ0����ʾ��Ϸ�������棬���˳�����
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
		//��Ϸ����������

		drawEndScreen(data);
		return;
	}
	//��Ϸ���±߿�ͷɻ��ӵ��л�
	else {
		zeroXy(0, 0);
		for (int x = 0; x < data.height + 1; x++) {
			for (int y = 0; y < data.width + 1; y++) {
				if (x == 1 && y == 1 * data.width / 5.0) {
					cout << "Score��" << data.score;
				}
				if (x == 1 && y == 3 * data.width / 5.0) {
					cout << "Life��" << data.life;
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
	// ������ɵл��� x �� y ����
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
	}//���мӷ�

	//û�л��п۷�,�����µĵл�
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