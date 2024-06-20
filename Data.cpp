#include"Data.h"
Data::Data(int& life, int& score, int height, int width) {
	this->life = life;
	this->score = score;
	this->height = height;
	this->width = width;
}
Data::Data() {
	life = 0;
	score = 0;
	height = 0;
	width = 0;
}
