#pragma once
//子弹，设定子弹
class Bullet {
public:
	int bullet_x;
	int bullet_y;
public:
	Bullet(int x, int y) : bullet_x(x), bullet_y(y) {};//初始化列表初始子弹坐标
	Bullet() : bullet_x(0), bullet_y(0) {}//设定子弹初始坐标为（0,0）;
};
