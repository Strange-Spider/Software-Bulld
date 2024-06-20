#pragma once
class Fighter {
public:
	int fighter_x;
	int fighter_y;
public:

	Fighter(int x, int y) :fighter_x(x) , fighter_y(y){};
	Fighter() :fighter_x(0), fighter_y(0){};
};
