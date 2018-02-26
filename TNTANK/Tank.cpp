#ifndef TANK_CPP
#define TANK_CPP

#include "ArduEngine/ArduEngine.h"

#include "Images.h"

class Tank : public ArduObject {
  public:
    Tank(ArduEngine &engine) {
      tankSprite = new ArduSprite(1, 1, 14, 14, WHITE, tank_image_up, engine);
      engine.RegisterObject(*this);
      
      enabled = true;
      
      currX = 1;
      currY = 1;

      nextX = 1;
      nextY = 1;
    }

    void Update(ArduEngine &engine) {
      if (!enabled)
        return;
      
      if (currX < nextX) currX++;
      if (currX > nextX) currX--;
      if (currY < nextY) currY++;
      if (currY > nextY) currY--;
      
      tankSprite->x = currX;
      tankSprite->y = currY;
    }

    void SetDirectPosition(int16_t _X, int16_t _Y) {
      currX = _X;
      currY = _Y;

      nextX = _X;
      nextY = _Y;

      tankSprite->x = currX;
      tankSprite->y = currY;
    }

    void SetEnabled(bool _enabled) {
      this->enabled = _enabled;
      tankSprite->isEnabled = _enabled;
    }

    void SetNextPosition(int16_t _nextX, int16_t _nextY) {
      currX = nextX;
      currY = nextY;

      nextX = _nextX;
      nextY = _nextY;
    }

    void Up() {
      if (nextY == 1)
        return;
      this->SetNextPosition(nextX, nextY - 16);
      tankSprite->image = tank_image_up;
    }

    void Right() {
      if (nextX == 128 - 15)
        return;
      this->SetNextPosition(nextX + 16, nextY);
      tankSprite->image = tank_image_right;
    }

    void Down() {
      if (nextY == 64 - 15)
        return;
      this->SetNextPosition(nextX, nextY + 16);
      tankSprite->image = tank_image_down;
    }

    void Left() {
      if (nextX == 1)
        return;
      this->SetNextPosition(nextX - 16, nextY);
      tankSprite->image = tank_image_left;
    }

    int16_t currX, currY;
    int16_t nextX, nextY;
    
  private:
    ArduSprite *tankSprite;
    bool enabled;
};

#endif
