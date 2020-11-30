#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "Sprite.h"
#include "Label.h"

class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters
	float RotAmount;
	float PlayerMass;
	float PaddleScaler;
	bool isColliding(GameObject*);
	float getDistance(GameObject*);

private:


	glm::vec2 m_direction;
};

#endif /* defined (__PLAYER__) */