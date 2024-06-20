class Data {
public:
	int life;
	int score;
	int height;
	int width;
public:
	Data(int& life, int& score, int height, int width) :life(life),score(score),height(height),width(width){};
	Data() :life(0),score(0),height(0),width(0){};
};
