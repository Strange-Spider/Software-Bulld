#include"bullet.h"
//设定敌机
class EnemyFighter {
public:
	int enemy_x;
	int enemy_y;
	int width;

public:
	EnemyFighter(int x, int y, int width) :enemy_x(x), enemy_y(y), width(width) {};//生成敌机
	EnemyFighter() :enemy_x(0), enemy_y(0), width(0){};
};