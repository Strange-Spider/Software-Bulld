#pragma once
//�ӵ����趨�ӵ�
class Bullet {
public:
	int bullet_x;
	int bullet_y;
public:
	Bullet(int x, int y) : bullet_x(x), bullet_y(y) {};//��ʼ���б��ʼ�ӵ�����
	Bullet() : bullet_x(0), bullet_y(0) {}//�趨�ӵ���ʼ����Ϊ��0,0��;
};
