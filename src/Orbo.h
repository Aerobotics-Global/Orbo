#ifndef Orbo_h
#define Orbo_h

#include "Arduino.h"
#include "Servo.h"

//Define class constants
#define CLOCKWISE true
#define ANTICLOCKWISE false
#define DRIVE false
#define WALK true

class Orbo
{
    public:
        Servo ll;   //Left leg ---- 180 degree
        Servo lf;   //Left foot --- 360 degree, continuous
        Servo rl;   //right leg --- 180 degree
        Servo rf;   //right foot -- 360 degree, continuous
        Orbo(int leftLegPin, int leftFootPin, int rightLegPin, int rightFootPin);
        void balanceLeft(int degree);
        void balanceRight(int degree);
        void returnHome();
        void rotateFoot(Servo &foot, bool clockwise);
        void rotateFoot(Servo &foot, char dir);
        void stopFoot(Servo &foot);
        void stopFoot();
        void modeChange(bool desiredMode);
        void drive(char dir);
        void setIsWalkMode(bool isWalkMode);
        bool getIsWalkMode();
        void setRotSpeed(int rotSpeed);
        int getRotSpeed();
        void setLeftLegPos(int leftLegPos);
        int getLeftLegPos();
        void setRightLegPos(int rightLegPos);
        int getRightLegPos();
        void setReturnHomeDelay(int returnHomeDelay);
        int getReturnHomeDelay();
    private:
        bool _isWalkMode;       // Controls robot state
        int _rotSpeed;          // Speed of foot rotation
        int _leftLegPos;        // Position of left leg in degrees
        int _rightLegPos;       // Position of right leg in degrees
        int _returnHomeDelay;   // Delay amount for return home function in milliseconds
};

#endif