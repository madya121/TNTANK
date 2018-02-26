#include <Arduboy2.h>
#include <ArduboyTones.h>

#include "ArduEngine/ArduRect.cpp"
#include "ArduEngine/ArduSprite.cpp"
#include "ArduEngine/ArduText.cpp"
#include "ArduEngine/ArduEngine.cpp"

#include "Images.h"
#include "SceneID.h"

// Scene
#include "MainMenu.cpp"
#include "GameScene.cpp"

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
ArduEngine *arduEngine = new ArduEngine(arduboy);

// Scene Declaration
MainMenu *mainMenu;
GameScene *gameScene;

void InitializeScenes()
{
	// Initialize Scene
	mainMenu = new MainMenu(*arduEngine, MAIN_MENU_SCENE_ID);
  gameScene = new GameScene(*arduEngine, GAME_SCENE_ID);

	arduEngine->SetScene(GAME_SCENE_ID);
}

void setup()
{
	arduboy.begin();
	arduboy.setFrameRate(60);
	arduboy.initRandomSeed();

	InitializeScenes();
}

void loop()
{
	if (!(arduboy.nextFrame())) return;
	arduboy.pollButtons();
	arduboy.clear();

	arduEngine->Update(arduboy);

	arduboy.display();
}
