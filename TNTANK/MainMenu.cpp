#ifndef MainMenu_CPP
#define MainMenu_CPP

#include "ArduEngine/ArduEngine.h"

#include "Images.h"
#include "SceneID.h"

class MainMenu : public ArduScene
{
public:
  MainMenu(ArduEngine &engine, uint8_t sceneID) : ArduScene(sceneID, engine)
  {
    // This will be called once when the game start
  }
  void Load(ArduEngine &engine)
  {
    // This will be called once everytime we enter this scene
  }
  void Run(ArduEngine &engine)
  {
    // This will be called every frame when we're in this scene
  }
  void Destroy(ArduEngine &engine)
  {
    // This will be called once everytime we leave this scene
  }

private:
  
};


#endif
