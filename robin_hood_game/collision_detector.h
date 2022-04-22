#pragma once

#include <vector>

class Sprite;

/*
	Singleton class that has a vector containing all existing sprites
	Checks for collisions between sprites and calls the kill function of sprites that collide
*/


class Collision_detector {
public:
	static Collision_detector* getInstance();
	void detectCollisions();
	void addSprite(Sprite* sprite);
	void removeSprite(Sprite* sprite);
	void clearSprites();
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
		bool isHuman, doesCollide;
	};
};


