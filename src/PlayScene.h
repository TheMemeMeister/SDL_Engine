#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Target.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Plane.h"
#include "CollisionManager.h"
#include "SoundManager.h"
class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;
	Plane* m_pPlaneSprite;
	Target* m_pBall;
	Player* m_pPlayer;
	bool m_playerFacingRight;
	/*bool* m_GravityBool = false;*/

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	//Label* m_pMaxThrowLabel;   //maybe use this for max throw
};

#endif /* defined (__PLAY_SCENE__) */