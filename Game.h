#include"bullet.h"
#include"Data.h"
#include"enemyFighter.h"
#include"fighter.h"

class Game {
public:
	Bullet bullet;
	Data data;
	EnemyFighter enemyFighter;
	Fighter fighter;
public:
	Game();
	EnemyFighter generateNewEnemyFighter(int width);
	void init(Bullet& bullet,
		Data& data,
		EnemyFighter& enemyFighter,
		Fighter& fighter);
	void HideC();
	void drawEndScreen(Data data);
	void zeroXy(int x, int y);
	/*
	void drawPicture(Bullet bullet,
		Data data,
		EnemyFighter enemyFighter,
		Fighter fighter);
		*/
	void drawPicture(Bullet bullet1, Bullet bullet2,
		Data data,
		EnemyFighter enemyFighter,
		Fighter fighter);
	//�����ɻ�
	void operateFighger(Bullet& bullet, Bullet& bullet2,
		Data& data,
		EnemyFighter& enemyFighter,
		Fighter& fighter);

	void pcOperate(Bullet& bullet, Bullet& bullet2,
		Data& data,
		EnemyFighter& enemyFighter,
		Fighter& fighter);
	//�ӵ��ƶ�
	void floatBullet(Bullet& bullet, Bullet& bullet2,
		Data& data,
		EnemyFighter& enemyFighter,
		Fighter& fighter);
};
