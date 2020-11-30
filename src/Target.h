#pragma once
#ifndef __TARGET__
#define __TARGET__

#include "DisplayObject.h"
class Target final : public DisplayObject {
public:
	Target();
	~Target();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void doThrow();
	void bounce();
	bool hasGravity = false;

	/*double RampAngle = 0;*/
	//glm::vec2 SpeedOnRamp;
	glm::vec2 throwPosition;
	glm::vec2 throwSpeed;
	float PPM;
	float TargetMass;
	float ObjectType;
	//glm::vec2 SpeedOffRamp;
	void reset();
private:
	void m_move();
	void m_checkBounds();

};


#endif /* defined (__TARGET__) */