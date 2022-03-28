#pragma once

#include <vector>

class Sprite;


class Collision_detector {
public:
	static Collision_detector* getInstance();
	void detectCollisions();
	void addSprite(Sprite* sprite);
private:
	static Collision_detector* instance;
	Collision_detector();
	std::vector<Sprite*> sprites;
	bool collide(Sprite* sprite_1, Sprite* sprite_2);

	class Collision_rect {
	public:
		Collision_rect(Sprite* sprite);
		bool isColliding(Collision_rect* rect);
	private:
		int x1, y1, x2, y2;
		bool isHuman;
	};
};


