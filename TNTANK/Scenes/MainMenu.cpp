#ifndef MainMenu_CPP
#define MainMenu_CPP

#include "../ArduEngine/ArduEngine.h"

#include "../Images.h"
#include "../SceneManager.cpp"

#define TIME_BLINK 40;

class MainMenu : public ArduScene {
public:
    MainMenu(ArduEngine &engine, uint8_t sceneID) : ArduScene(sceneID, engine) {
        background = new ArduSprite(0, 0, 128, 64, WHITE, main_menu, engine);
        background->isEnabled = false;

        frame = TIME_BLINK;
        showText = true;
    }

    void Load(ArduEngine &engine) {
        background->isEnabled = true;
        frame = TIME_BLINK;
        showText = true;
    }

    void Run(ArduEngine &engine) {
        handleInput(engine);
        addText(engine);

        frame--;
        if (frame == 0) {
            showText ^= true;
            frame = TIME_BLINK;
        }
    }

    void Destroy(ArduEngine &engine) {
        background->isEnabled = false;
    }


private:
    ArduSprite *background;
    uint8_t frame;
    bool showText;

    void handleInput(ArduEngine &engine) {
        if (engine.arduboy->justPressed(A_BUTTON))
            engine.SetScene(GAME_SCENE_ID);
    }

    void addText(ArduEngine &engine) {
        engine.arduboy->fillRect(18, 38, 46, 12, WHITE);
        engine.arduboy->fillRect(19, 39, 44, 10, BLACK);

        if (showText) {
            engine.arduboy->setCursor(20, 40);
            engine.arduboy->setTextSize(1);
            engine.arduboy->print("Press A");
        }
    }
};

#endif
