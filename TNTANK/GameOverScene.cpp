#ifndef GameOverScene_CPP
#define GameOverScene_CPP

#include "ArduEngine/ArduEngine.h"

#include "Images.h"
#include "SceneID.h"

class GameOverScene : public ArduScene {
public:

  GameOverScene(ArduEngine &engine, uint8_t sceneID) : ArduScene(sceneID, engine) {
    frame = 0;
  }
  
  void Load(ArduEngine &engine) {
    frame = 0;
    engine.arduboy->digitalWriteRGB(RGB_ON, RGB_OFF, RGB_OFF);
  }
  
  void Run(ArduEngine &engine) {
    engine.arduboy->drawBitmap(0, 0, game_over, 128, 64, WHITE);
    
    frame += 2;

    engine.arduboy->fillRect(0, 56, frame, 8, WHITE);
    if (frame == 128) {
      engine.SetScene(MAIN_MENU_SCENE_ID);
    }
  }
  
  void Destroy(ArduEngine &engine) {
    engine.arduboy->digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
  }

private:
  uint16_t frame;
};


#endif
