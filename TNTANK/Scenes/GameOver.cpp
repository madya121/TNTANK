#ifndef GameOver_CPP
#define GameOver_CPP

#include "../ArduEngine/ArduEngine.h"

#include "../Images.h"
#include "../SceneManager.cpp"

class GameOver : public ArduScene {
public:
    GameOver(ArduEngine &engine, uint8_t sceneID) : ArduScene(sceneID, engine) {
        frame = 0;
    }

    void Load(ArduEngine &engine) {
        frame = 0;
    }

    void Run(ArduEngine &engine) {
        engine.arduboy->drawBitmap(0, 0, game_over, 128, 64, WHITE);

        frame += 1;

        engine.arduboy->fillRect(0, 56, frame, 8, WHITE);
        if (frame == 128) {
            engine.SetScene(MAIN_MENU_SCENE_ID);
        }
    }

    void Destroy(ArduEngine &engine) {

    }


private:
    uint16_t frame;
};


#endif
