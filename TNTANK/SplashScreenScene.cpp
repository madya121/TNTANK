#ifndef SplashScreenScene_CPP
#define SplashScreenScene_CPP

#include "ArduEngine/ArduEngine.h"

#include "Images.h"
#include "SceneID.h"

class SplashScreenScene : public ArduScene {
public:

  SplashScreenScene(ArduEngine &engine, uint8_t sceneID) : ArduScene(sceneID, engine) {
    frame = 0;
  }
  
  void Load(ArduEngine &engine) {
    frame = 0;
    
  }
  
  void Run(ArduEngine &engine) {
    frame += 1;

    if (frame <= 125) {
      engine.arduboy->drawBitmap(0, 0, ardunx_splash, 128, 64, WHITE);
    } else if (frame <= 150) {
      // DO Nothing
    } else if (frame <= 300) {
      engine.arduboy->drawBitmap(0, 0, grim_pros_splash, 128, 64, WHITE);
    } else {
      engine.SetScene(MAIN_MENU_SCENE_ID);
    }
  }
  
  void Destroy(ArduEngine &engine) {
    
  }

private:
  uint16_t frame;
};


#endif
