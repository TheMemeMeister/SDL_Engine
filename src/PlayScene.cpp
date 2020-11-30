#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderClear(Renderer::Instance()->getRenderer());
	TextureManager::Instance()->draw("backround", 400, 300, 0, 255, true);
	drawDisplayList();
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

}

void PlayScene::update()
{
	
	updateDisplayList();
	int mouse_x, mouse_y;
	if (SDL_GetMouseState(&mouse_x, &mouse_y))
	{
		m_pPlayer->getTransform()->position.x = mouse_x;
		m_pPlayer->getTransform()->position.y = mouse_y;
	}
	m_pBall->update();
	if (m_pBall->ObjectType == 0) {
		CollisionManager::circleAABBCheck(m_pBall, m_pPlayer);
	}
	else if(m_pBall->ObjectType == 1) {
		CollisionManager::circleAABBCheck(m_pBall, m_pPlayer);
	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
	/*int mouse_x, mouse_y;
	if (SDL_GetMouseState(&mouse_x, &mouse_y))
	{
		m_pPlayer->getTransform()->position.x = mouse_x;
		m_pPlayer->getTransform()->position.y = mouse_y;
	}*/
	////Moving the player with A and D
	//if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	//{
	//	m_pPlayer->moveLeft();
	//}
	//else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	//{
	//	m_pPlayer->moveRight();
	//}
	//else {
	//	m_pPlayer->stopMovingX();
	//}
}

void PlayScene::start()
{
	//Loads backround texture from disk into RAM
	TextureManager::Instance()->load("../Assets/textures/Backround2.jpg", "backround");
	
	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_playerFacingRight = true;

	////stormtrooper
	//m_pPlaneSprite = new Plane(); 
	//addChild(m_pPlaneSprite);

	// Ball
	m_pBall = new Target();
	m_pBall->getTransform()->position = m_pPlayer->getTransform()->position;
	m_pBall->getTransform()->position.x += m_pBall->getWidth();
	addChild(m_pBall);
	const SDL_Color purple = { 255, 0, 255, 255 };
	//// Back Button
	//m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	//m_pBackButton->getTransform()->position = glm::vec2(300.0f, 400.0f);
	//m_pBackButton->addEventListener(CLICK, [&]()-> void
	//{
	//	m_pBackButton->setActive(false);
	//	TheGame::Instance()->changeSceneState(START_SCENE);
	//});

	//m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	//{
	//	m_pBackButton->setAlpha(128);
	//});

	//m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	//{
	//	m_pBackButton->setAlpha(255);
	//});
	//addChild(m_pBackButton);

	//// Next Button
	//m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	//m_pNextButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	//m_pNextButton->addEventListener(CLICK, [&]()-> void
	//{
	//	m_pNextButton->setActive(false);
	//	TheGame::Instance()->changeSceneState(END_SCENE);
	//});

	//m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	//{
	//	m_pNextButton->setAlpha(128);
	//});

	//m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	//{
	//	m_pNextButton->setAlpha(255);
	//});

	//addChild(m_pNextButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas", 10, purple, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	addChild(m_pInstructionsLabel);
}

//void PlayScene::GUI_Function() const
//{
//	// Always open with a NewFrame
//	ImGui::NewFrame();
//	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
//	//ImGui::ShowDemoWindow();
//	
//	ImGui::Begin("Physics Assignment 2", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
//	////Testing the Img::Button function
//	if (ImGui::Button("Start")) {
//		m_pBall ->doThrow();
//
//		}
//	//if (buttonPressed) {
//	//	std::cout << "ThrowPressed" << std::endl;
//	//}
//
//
//	/*if(ImGui::Button("Throw"))
//	{
//		std::cout << "Throw Pressed" << std::endl;
//	}*/
//
//	ImGui::Separator();
//
//	/*static bool GravityBool = false;
//	if ((ImGui::Checkbox("Gravity", &GravityBool)))
//	{
//		m_pBall->hasGravity = GravityBool;
//	}*/
//
//	//std::string grav = GravityBool ? "Gravity is turned ON" : "Gravity is turned OFF";
//	//std::cout << grav << std::endl;
//	static float xPlayerPos = 100;
//	static float RampHeight = 150;
//	static float grav = 9.81;
//	static float RampWidth;
//	static float initialAngle;
//	if (ImGui::SliderFloat("Hill Start x", &xPlayerPos, 0, 800)) {
//		m_pPlayer->getTransform()->position.x = xPlayerPos;
//		m_pBall->throwPosition = glm::vec2(xPlayerPos,(400 - RampHeight)); //TODO -> fix ball starting position
//		m_pBall->getTransform()->position = m_pPlayer->getTransform()->position;
//		m_pBall->getTransform()->position.x += m_pBall->getWidth();
//	
//
//	
//	}
//	static float xStormPos = 685;
//	if (ImGui::SliderFloat("Hill of Triangle x", &xStormPos, 0, 850)) {
//		m_pPlaneSprite->getTransform()->position.x = xStormPos;
//		RampWidth = xStormPos - xPlayerPos;
//		initialAngle = atan(RampHeight / RampWidth);
//		m_pBall->throwPosition = glm::vec2(xPlayerPos, (400 - RampHeight));
//	}
//	//static float RampWidth = xStormPos - xPlayerPos;
//	/*if (ImGui::SliderInt("delta X", &RampWidth, 0, 500)) {
//		if (m_pPlaneSprite->getTransform()->position.x - m_pPlayer->getTransform()->position.x <= RampWidth)
//		{
//			xStormPos += m_pPlaneSprite->getTransform()->position.x - m_pPlayer->getTransform()->position.x;
//		}
//		else
//			xStormPos -= RampWidth - (m_pPlaneSprite->getTransform()->position.x - m_pPlayer->getTransform()->position.x);
//
//	}*/
//	 
//	 std::cout << glm::degrees(initialAngle) << std::endl;
//	if (ImGui::SliderFloat("RampHeight", &RampHeight, 0, 850)) {
//	
//		  initialAngle = atan(RampHeight / RampWidth);
//		 RampWidth = xStormPos - xPlayerPos;
//		 m_pBall->throwPosition = glm::vec2(xPlayerPos, (400 - RampHeight));
//		  m_pBall->RampAngle = glm::degrees(initialAngle);
//	}
//	//ImGui::Slider("PlayerPosition x", &m_pPlayer->getTransform()->position.x, 0, 800);
//	//m_pBall->getTransform->rotation.x = initialAngle;
//	//std::cout << initialAngle << std::endl;
//	static float MewOfFric;
//	if (ImGui::SliderFloat("Fric Mew", &MewOfFric, 0, 2)) {
//
//
//	}
//	
//	static float CrateMass = 95;
//
//	if (ImGui::SliderFloat("Crate Mass", &CrateMass, 0, 200)) {
//	
//	
//	}
//	/*if (ImGui::SliderFloat("Throw angle", &initialAngle, 0, 90)) {
//
//	
//	}*/
//	/*float testvar = 60;
//	std::cout << sin(glm::radians(testvar)) << std::endl;
//	*/
//	m_pBall->SpeedOnRamp = glm::vec2(CrateMass * grav * cos((initialAngle)), CrateMass * grav * sin(initialAngle));
//	m_pBall->getRigidBody()->acceleration = glm::vec2(CrateMass * grav * cos((initialAngle)), CrateMass * grav * sin(initialAngle));
//	m_pBall->SpeedOffRamp = glm::vec2(grav * MewOfFric * CrateMass, 0);
//	//std::cout << "initial velocity X is: " << m_pBall->throwSpeed[0] << std::endl;
//	//std::cout << "initial velocity  Y is: " << m_pBall->throwSpeed[1] << std::endl;
//
//
//	// THESE BOTH ASSUME GRAVITY IS ON FOR THE SIMULATION
//	//const float MaxDistance = (initialVelocity * initialVelocity ) / (9.8);
//	//ImGui::Text("The Max throw distance (delta D x) is %f" , MaxDistance);
//
//	//if (ImGui::Button("Throw")) {
//	//	ImGui::LabelText("The Maximum horizontal distance for this throw is", )  //maybe use this for max throw. 
//	//}
//	/*Util::DrawLine(m_pPlayer->getTransform()->position, m_pPlaneSprite->getTransform()->position, glm::vec4(1, 0, 0, 1));
//	Util::DrawLine(m_pPlayer->getTransform()->position, (m_pPlayer->getTransform()->position - glm::vec2(0, RampHeight)), glm::vec4(1, 0, 0, 1));
//	Util::DrawLine((m_pPlayer->getTransform()->position - glm::vec2(0, RampHeight)), m_pPlaneSprite->getTransform()->position, glm::vec4(1, 0, 0, 1));
//	Util::DrawLine(m_pPlaneSprite->getTransform()->position, m_pPlaneSprite->getTransform()->position - glm::vec2(-400, 0), glm::vec4(1, 0, 0, 1));*/
//	ImGui::End();
//	// Don't Remove this
//	ImGui::Render();
//	ImGuiSDL::Render(ImGui::GetDrawData());
//	ImGui::StyleColorsDark();
//}
void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Physics Assigment 3 Sene 2", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	////Testing the Img::Button function
	

	if (ImGui::Button("Throw")) {
		m_pBall->doThrow();
		m_pBall->throwPosition = glm::vec2(200, 200);
	}
	if (ImGui::Button("Rotate Paddle")) {
		auto size = TextureManager::Instance()->getTextureSize("circle");
		m_pPlayer->RotAmount += 90;
		m_pPlayer->setWidth(size.y);
		m_pPlayer -> setHeight(size.x);

	}
	
	//if (buttonPressed) {
	//	std::cout << "ThrowPressed" << std::endl;
	//}


	/*if(ImGui::Button("Throw"))
	{
		std::cout << "Throw Pressed" << std::endl;
	}*/

	ImGui::Separator();

	static bool GravityBool = false;
	if ((ImGui::Checkbox("Gravity", &GravityBool)))
	{
		m_pBall->hasGravity = GravityBool;

	}

	//std::string grav = GravityBool ? "Gravity is turned ON" : "Gravity is turned OFF";
	//std::cout << grav << std::endl;
	/*static int xPlayerPos = 100;
	if (ImGui::SliderInt("PlayerPosition x", &xPlayerPos, 0, 800)) {
		m_pPlayer->getTransform()->position.x = xPlayerPos;
		m_pBall->throwPosition = glm::vec2(xPlayerPos, 200);
		m_pBall->getTransform()->position = m_pPlayer->getTransform()->position;
		m_pBall->getTransform()->position.x += m_pBall->getWidth();

	}*/


	//ImGui::Slider("PlayerPosition x", &m_pPlayer->getTransform()->position.x, 0, 800);
	static float initialVelocity = 16;
	static float ObjectMass = 50;
	static float PaddleMass = 50;
	static int ObjectType = 0;
	static float PaddleScaler = 5;
	static float PPM = 1;
	if (ImGui::SliderFloat("Throw Speed (Vi)", &initialVelocity, 0, 100)) {

		m_pBall->throwSpeed = glm::vec2(initialVelocity, initialVelocity);
	}

	if (ImGui::SliderFloat("PPM", &PPM, 0, 2)) {

		m_pBall->PPM = PPM;
	}
	if (ImGui::SliderFloat("Mass of Paddle", &PaddleMass, 0, 90)) {

		m_pPlayer->PlayerMass = PaddleMass;
	}
	if (ImGui::SliderFloat("Mass Of Object", &ObjectMass, 0, 90)) {
		m_pBall->TargetMass = ObjectMass;

	}
	if (ImGui::SliderFloat("Paddle Hit Force", &PaddleScaler, 0, 10)) {
		m_pPlayer->PaddleScaler = PaddleScaler;

	}
	if (ImGui::SliderInt("Object Type", &ObjectType, 0, 1)) {
		if (ObjectType == 1) {
			m_pBall->ObjectType = ObjectType;

		}
		else if (ObjectType == 0) {
			m_pBall->ObjectType = ObjectType;
		}
		m_pBall->throwSpeed = glm::vec2(initialVelocity, initialVelocity);
		//float testvar = 60;
		//std::cout << sin(glm::radians(testvar)) << std::endl;

		//m_pBall->throwSpeed = glm::vec2(initialVelocity,initialVelocity);



		// THESE BOTH ASSUME GRAVITY IS ON FOR THE SIMULATION


		//if (ImGui::Button("Throw")) {
		//	ImGui::LabelText("The Maximum horizontal distance for this throw is", )  //maybe use this for max throw. 
		//}
	}
		ImGui::End();

		// Don't Remove this
		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());
		ImGui::StyleColorsDark();
	}
