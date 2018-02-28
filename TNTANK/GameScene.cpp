#ifndef GameScene_CPP
#define GameScene_CPP

#include "ArduEngine/ArduEngine.h"

#include "Images.h"
#include "SceneID.h"

#include "Tank.cpp"

const int X4[4] = {0, 1, 0, -1};
const int Y4[4] = {1, 0, -1, 0};

class GameScene : public ArduScene {
  
public:
  GameScene(ArduEngine &engine, uint8_t sceneID) : ArduScene(sceneID, engine) {
    tank = new Tank(engine);
    tank->SetEnabled(false);
    
    flag = new ArduSprite(80, 48, 16, 16, WHITE, flag_image, engine);
    flag->isEnabled = false;

    countdown = new ArduText(3, 1, "", engine);
    countdown->SetSize(2);

    frameCountdown = 375;

    isWin = false;
    isLose = false;
  }
  
  void Load(ArduEngine &engine) {
    countdown->isEnabled = false;
    isWin = false;
    isLose = false;
    
    InitializeMap();
    TraverseMap(0, 0);
    GetStartPoint();
    PositioningTank();
    GetFinishPoint();
    
    frameCountdown = 375;
  }
  
  void Run(ArduEngine &engine) {
    drawBorder(engine);

    if (frameCountdown > 0) {
      drawTNT(engine);
      frameCountdown--;
      DrawCountdown(engine);
      return;
    } else if (frameCountdown == 0) {
      tank->SetEnabled(true);
      countdown->isEnabled = false;
      flag->isEnabled = true;
      frameCountdown = -1;
    }

    checkWin(engine);
    checkLose(engine);
    if (isWin || isLose)
      return;
      
    handleInput(engine);
  }
  
  void Destroy(ArduEngine &engine) {
    tank->SetEnabled(false);
    flag->isEnabled = false;
    countdown->isEnabled = false;
  }

private:
  Tank *tank;
  ArduSprite *flag;
  int8_t playMap[4][8];
  int8_t startX, startY;
  int8_t finishX, finishY;
  int16_t frameCountdown;
  ArduText *countdown;
  bool isWin, isLose;

  void DrawCountdown(ArduEngine &engine) {
    countdown->isEnabled = true;
    countdown->SetPosition(3 + (startY * 16), 1 + (startX * 16));
    countdown->SetText((int16_t)(frameCountdown / 75) + 1);
  }

  void PositioningTank() {
    tank->SetDirectPosition(1 + (startY * 16), 1 + (startX * 16));
  }

  void InitializeMap() {
    for (int8_t i = 0; i < 4; i++) {
      for (int8_t j = 0; j < 8; j++) {
        playMap[i][j] = -1;
      }
    }
  }

  bool isValidPath(int8_t x, int8_t y) {
    int8_t count = 0;
    for (int8_t i = 0; i < 4; i++) {
      int8_t X = x + X4[i];
      int8_t Y = y + Y4[i];

      if (X >= 0 && X < 4 && Y >= 0 && Y < 8) {
        if (playMap[X][Y] == 0)
          count++;
      }
    }

    return count == 1;
  }

  void TraverseMap(int8_t x, int8_t y) {
    if (x < 0 || x >= 4 || y < 0 || y >= 8)
      return;
    
    playMap[x][y] = 0;
    
    int8_t dir[4] = {0, 1, 2, 3};
    for (int8_t i = 0; i < 4; i++) {
      int8_t A = random(0, 4);
      int8_t B = random(0, 4);
      
      int8_t temp = dir[A];
      dir[A] = dir[B];
      dir[B] = temp;
    }
    
    for (int8_t i = 0; i < 4; i++) {
      if (isValidPath(x + X4[dir[i]], y + Y4[dir[i]])) {
        TraverseMap(x + X4[dir[i]], y + Y4[dir[i]]);
      }
    }
  }

  void GetStartPoint() {
    uint8_t road = 0;
    for (int8_t i = 0; i < 4; i++) {
      for (int8_t j = 0; j < 8; j++) {
        road += (playMap[i][j] == 0);
      }
    }

    uint8_t selectedIndex = random(1, road + 1);

    road = 0;
    for (int8_t i = 0; i < 4; i++) {
      for (int8_t j = 0; j < 8; j++) {
        road += (playMap[i][j] == 0);
        if (road == selectedIndex) {
          startX = i;
          startY = j;
          playMap[i][j] = 1;
          return;
        }
      }
    }
  }

  void GetFinishPoint() {
    uint8_t road = 0;
    for (int8_t i = 0; i < 4; i++) {
      for (int8_t j = 0; j < 8; j++) {
        road += (playMap[i][j] == 0);
      }
    }

    uint8_t selectedIndex = random(1, road + 1);

    road = 0;
    for (int8_t i = 0; i < 4; i++) {
      for (int8_t j = 0; j < 8; j++) {
        road += (playMap[i][j] == 0);
        if (road == selectedIndex) {
          finishX = i;
          finishY = j;
          
          flag->x = finishY * 16;
          flag->y = finishX * 16;
          
          playMap[i][j] = 2;
          return;
        }
      }
    }
  }

  void drawBorder(ArduEngine &engine) {
    for (int16_t i = -1; i < 128; i += 16) {
      engine.arduboy->drawBitmap(i, 0, vertical_border, 2, 64, WHITE);
    }
    for (int16_t i = -1; i < 64; i += 16) {
      engine.arduboy->drawBitmap(0, i, horizontal_border, 128, 2, WHITE);
    }
  }

  void handleInput(ArduEngine &engine) {
    if (engine.arduboy->justPressed(UP_BUTTON))
      tank->Up();
    if (engine.arduboy->justPressed(RIGHT_BUTTON))
      tank->Right();
    if (engine.arduboy->justPressed(DOWN_BUTTON))
      tank->Down();
    if (engine.arduboy->justPressed(LEFT_BUTTON))
      tank->Left();

    // if (engine.arduboy->justPressed(A_BUTTON))
    //   engine.SetScene(GAME_SCENE_ID);
  }

  void drawTNT(ArduEngine &engine) {
    for (int8_t i = 0; i < 4; i++) {
      for (int8_t j = 0; j < 8; j++) {
        if (playMap[i][j] == -1) {
          engine.arduboy->drawBitmap(1 + j * 16, 1 + i * 16, tnt_image, 14, 14, WHITE);
        }
      }
    }
  }

  void checkWin(ArduEngine &engine) {
    
    if (1 + (finishX * 16) == tank->nextY && 1 + (finishY * 16) == tank->nextX) {
      isWin = true;
      if (1 + (finishX * 16) == tank->currY && 1 + (finishY * 16) == tank->currX) {
        engine.SetScene(WIN_SCENE_ID);
      }
    }
  }

  void checkLose(ArduEngine &engine) {
    int16_t decodeNextX = (tank->nextY - 1) / 16;
    int16_t decodeNextY = (tank->nextX - 1) / 16;

    if (playMap[decodeNextX][decodeNextY] == -1) {
      isLose = true;
      if (1 + (decodeNextX * 16) == tank->currY && 1 + (decodeNextY * 16) == tank->currX) {
        engine.SetScene(GAME_OVER_SCENE_ID);
      }
    }
  }
};


#endif
