#ifndef SCENE_MANAGER_CPP
#define SCENE_MANAGER_CPP

const int GAME_SCENE_ID = 0;
const int GAME_OVER_SCENE_ID = 1;
const int MAIN_MENU_SCENE_ID = 2;
const int SPLASH_SCREEN_SCENE_ID = 3;
const int WIN_SCENE_ID = 4;

#include "Scenes/Game.cpp"
#include "Scenes/GameOver.cpp"
#include "Scenes/MainMenu.cpp"
#include "Scenes/SplashScreen.cpp"
#include "Scenes/Win.cpp"

class SceneManager {
public:
    Game *game;
    GameOver *gameOver;
    MainMenu *mainMenu;
    SplashScreen *splashScreen;
    Win *win;

    SceneManager(ArduEngine &engine) {
        game = new Game(engine, GAME_SCENE_ID);
        gameOver = new GameOver(engine, GAME_OVER_SCENE_ID);
        mainMenu = new MainMenu(engine, MAIN_MENU_SCENE_ID);
        splashScreen = new SplashScreen(engine, SPLASH_SCREEN_SCENE_ID);
        win = new Win(engine, WIN_SCENE_ID);
    }
};

#endif
