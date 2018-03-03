#ifndef WinScene_CPP
#define WinScene_CPP

#include "ArduEngine/ArduEngine.h"

#include "Images.h"
#include "SceneID.h"

class WinScene : public ArduScene {
public:

  WinScene(ArduEngine &engine, uint8_t sceneID) : ArduScene(sceneID, engine) {
    frame = 0;
  }
  
  void Load(ArduEngine &engine) {
    frame = 0;
    engine.arduboy->digitalWriteRGB(RGB_OFF, RGB_ON, RGB_OFF);
  }
  
  void Run(ArduEngine &engine) {
    engine.arduboy->drawBitmap(0, 0, win_image, 128, 64, WHITE);
    
    frame += 2;

    engine.arduboy->fillRect(0, 56, frame, 8, WHITE);
    if (frame == 128) {
      engine.SetScene(GAME_SCENE_ID);
    }
  }
  
  void Destroy(ArduEngine &engine) {
    engine.arduboy->digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
  }

private:
  uint16_t frame;
};


#endif
