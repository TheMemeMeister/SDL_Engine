#include "Target.h"
#include "TextureManager.h"
#include "Util.h"

Target::Target()
{
	TextureManager::Instance()->load("../Assets/textures/ball.png","circle");

	const auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(TARGET);
}

Target::~Target()
= default;

void Target::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("circle", x, y, RampAngle, 255, true);
}

void Target::update()
{
	m_move();
	m_checkBounds();
}

void Target::clean()
{
}

void Target::m_move()
{
	float deltaTime = 1.0 / 60.0f;
	glm::vec2 gravity = glm::vec2(0, 9.8f);
	bool StaticFric = false;
	//glm::vec2 VNorm = Util::normalize(getRigidBody()->velocity);
	/*if (hasGravity == false) {
	
		getTransform()->position += getRigidBody()->velocity * deltaTime;

	}*/
		if (getTransform()->position.y >= 400  && getRigidBody()->velocity.x >= 0) {
			getRigidBody()->acceleration = -SpeedOffRamp;
			getRigidBody()->velocity.y = 0;
			
			
			//if (getRigidBody()->velocity.x > 0) {
			//	/*getRigidBody()->velocity -= SpeedOffRamp * deltaTime;*/
			//	getTransform()->position += getRigidBody()->velocity * deltaTime;
			//}
			/*else
				getRigidBody()->velocity = glm::vec2(0, 0);*/
		}
		if (Util::magnitude(getRigidBody()->velocity) < 1.0f) {
			getRigidBody()->velocity = glm::vec2(0, 0);
			getRigidBody()->acceleration = glm::vec2(0, 0);

		}
		getRigidBody()->velocity += getRigidBody()->acceleration  * deltaTime;
		getTransform()->position += getRigidBody()->velocity * deltaTime;
	
}
void Target::m_checkBounds()
{
}

void Target::doThrow() {
	getTransform()->position = throwPosition;
	getRigidBody()->velocity = SpeedOnRamp;
	 
}

void Target::m_reset()
{
}
