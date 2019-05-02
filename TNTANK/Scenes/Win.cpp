#ifndef Win_CPP
#define Win_CPP

#include "../ArduEngine/ArduEngine.h"

#include "../Images.h"
#include "../SceneManager.cpp"

class Win : public ArduScene
{
public:
	Win(ArduEngine &engine, uint8_t sceneID) : ArduScene(sceneID, engine)
	{
		frame = 0;
	}
	
	void Load(ArduEngine &engine)
	{
		frame = 0;
	}
	
	void Run(ArduEngine &engine)
	{
		engine.arduboy->drawBitmap(0, 0, win_image, 128, 64, WHITE);
    
    frame += 1;

    engine.arduboy->fillRect(0, 56, frame, 8, WHITE);
    if (frame == 128) {
      engine.SetScene(GAME_SCENE_ID);
    }
	}
	
	void Destroy(ArduEngine &engine)
	{
		// This will be called once everytime we leave this scene
	}
	

private:
	  uint16_t frame;
};


#endif
