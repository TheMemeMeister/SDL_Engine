#include "Target.h"
#include "TextureManager.h"
#include "Util.h"

Target::Target()
{
	TextureManager::Instance()->load("../Assets/textures/roundball.png","ball");
	TextureManager::Instance()->load("../Assets/textures/Bullet1.png", "Rect");
	const auto size = TextureManager::Instance()->getTextureSize("ball");
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
	if (ObjectType == 1) {
		TextureManager::Instance()->draw("ball", x, y, 0, 255, true);

	}
	else if (ObjectType == 0) {
		TextureManager::Instance()->draw("Rect", x, y, 0, 255, true);
	}
	

}

void Target::update()
{
	m_move();
	m_checkBounds();
}

void Target::clean()
{
}

//void Target::m_move()
//{
//	float deltaTime = 1.0 / 60.0f;
//	glm::vec2 gravity = glm::vec2(0, 9.81f);
//	bool StaticFric = false;
//	//glm::vec2 VNorm = Util::normalize(getRigidBody()->velocity);
//	/*if (hasGravity == false) {
//	
//		getTransform()->position += getRigidBody()->velocity * deltaTime;
//
//	}*/
//
//		if (getTransform()->position.y >= 400  && getRigidBody()->velocity.x >= 0) {
//			getRigidBody()->acceleration = -SpeedOffRamp;
//			getRigidBody()->velocity.y = 0;
//			/*if ((Util::magnitude(getRigidBody()->velocity) < Util::magnitude(getRigidBody()->acceleration) > 0)) {
//				getRigidBody()->acceleration = (getRigidBody()->velocity);
//				
//
//			}*/
//			/*if (Util::magnitude(getRigidBody()->acceleration) < 1.0f) {
//				getRigidBody()->acceleration = -getRigidBody()->velocity;
//				getRigidBody()->velocity.y = 0;
//			}*/
//			if ((Util::magnitude(getRigidBody()->acceleration) > Util::magnitude(getRigidBody()->velocity))) {
//					getRigidBody()->velocity.y = 0;
//					getRigidBody()->velocity = glm::vec2(0, 0);
//					getRigidBody()->acceleration = glm::vec2(0, 0);
//			}
//			else {
//				getRigidBody()->velocity.y = 0;
//				getRigidBody()->velocity += getRigidBody()->acceleration;
//
//			}
//			/*if (Util::magnitude(getRigidBody()->velocity) < 1.0f ) {
//				getRigidBody()->velocity.y = 0;
//				getRigidBody()->velocity = glm::vec2(0, 0);
//				getRigidBody()->acceleration = glm::vec2(0, 0);
//
//			}*/
//			
//			/*else
//				getRigidBody()->acceleration = -getRigidBody()->velocity;*/
//			//if (getRigidBody()->velocity.x > 0) {
//			//	/*getRigidBody()->velocity -= SpeedOffRamp * deltaTime;*/
//			//	getTransform()->position += getRigidBody()->velocity * deltaTime;
//			//}
//			/*else
//				getRigidBody()->velocity = glm::vec2(0, 0);*/
//		}
//		/*if (Util::magnitude(getRigidBody()->velocity) < 1.0f) {
//			getRigidBody()->velocity = glm::vec2(0, 0);
//			getRigidBody()->acceleration = glm::vec2(0, 0);
//
//		}*/
//		/*else if ((Util::magnitude(getRigidBody()->velocity) < Util::magnitude(getRigidBody()->acceleration) > 0)) {
//			getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
//			getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
//		}*/
//		getRigidBody()->velocity += getRigidBody()->acceleration  * deltaTime;
//		getTransform()->position += getRigidBody()->velocity * deltaTime;
//	
//}
void Target::m_move()
{
	float deltaTime = 1.0 / 60.0f;
	glm::vec2 gravity = glm::vec2(0, 9.8f);

	if (hasGravity == false) {

		getTransform()->position += getRigidBody()->velocity * deltaTime * PPM * TargetMass;

	}
	else {
		getRigidBody()->velocity += (getRigidBody()->acceleration + gravity) * deltaTime;
		getTransform()->position += getRigidBody()->velocity * deltaTime * PPM * TargetMass;
	}
}
void Target::m_checkBounds()
{
	if (getTransform()->position.y > 600) //Ball hits floor. {
	{
		getTransform()->position.y = 600 - getHeight();
		getRigidBody()->velocity.y *= -1;
	}
	else if (getTransform()->position.y < 1) //Ball hits Ciel. {
	{
		getTransform()->position.y = 0+  getHeight();
		getRigidBody()->velocity.y *= -1 ;
	}
	if (getTransform()->position.x > 800) //Ball hits Right. {
	{
		getTransform()->position.x = 800 - getWidth();
		getRigidBody()->velocity.x *= -1 ;
	}
	else if (getTransform()->position.x < 1) //Ball hits Left. {
	{

		getTransform()->position.x = 0 + getWidth();
		getRigidBody()->velocity.x *= -1 ;
	}
}

void Target::doThrow() {
	getTransform()->position = throwPosition;
	getRigidBody()->velocity = throwSpeed * PPM;
	 
}

void Target::bounce()
{

}

void Target::reset()
{
	getTransform()->position = throwPosition;
}
