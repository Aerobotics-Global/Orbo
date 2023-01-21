/* 
    Orbo.h - Library for controlling the Aerobotics Global product Orbo.
    Created by Lokesh Kode and Filippos Batistatos, January 21, 2023.
    Released into the public domain. 
*/

#include "Arduino.h"
#include "Orbo.h"
#include "Servo.h"

Orbo::Orbo(int leftLegPin, int leftFootPin, int rightLegPin, int rightFootPin)
{
    ll.attach(leftLegPin, 120, 2400);
    lf.attach(leftFootPin);
    rl.attach(rightLegPin, 120, 2400);
    rf.attach(rightFootPin);

    ll.write(90);
    lf.write(90);
    rl.write(90);
    rf.write(90);

    //Defining private variables
    setIsWalkMode(true);
    setLeftLegPos(90);
    setRightLegPos(90);
    setRotSpeed(25);
    setReturnHomeDelay(3); //Milliseconds
}



/*   
    Balance Orbo on its left leg in degrees.
    args: {int}
    The right leg needs to first push Orbo over to the left
    then the left leg can bend and take the full weight of the robot.
    This approach works the most consistantly accross the most surfaces. 
*/
void Orbo::balanceLeft(int degree) {
  setLeftLegPos(90 + degree);
  setLeftLegPos(90 + 2 * degree / 3);
  modeChange(true);             //Check that Orbo is in the appropriate mode for this command 
  rl.write(90 + 2 * degree / 3);
  delay(25);
  ll.write(90 + degree);
}


/*   
    Balance Orbo on its right leg in degrees.
    args: {int}
    The left leg needs to first push Orbo over to the right
    then the right leg can bend and take the full weight of the robot.
    This approach works the most consistantly accross the most surfaces. 
*/
void Orbo::balanceRight(int degree) {
  setLeftLegPos(90 - 2 * degree / 3);
  setRightLegPos(90 - degree);
  modeChange(true);             //Check that Orbo is in the appropriate mode for this command 
  ll.write(90 - 2 * degree / 3);
  delay(25);
  rl.write(90 - degree);
}

/* 
    Returns Orbo to the home position after a step
    This function is intended to be used after using [balanceRight] or [balanceLeft].
    This function is **NOT** to used used after [modeChange]!
*/
void Orbo::returnHome() { 
  if (getLeftLegPos() > 90) {
    for (int i = 0; i < abs(getLeftLegPos() - 90); i++) {
      rl.write(getRightLegPos() - (i * 2 / 3));
      ll.write(getLeftLegPos() - i);
      delay(_returnHomeDelay);
    }
  } else {
    for (int i = 0; i < abs(getRightLegPos() - 90); i++) {
      rl.write(getRightLegPos() + i);
      ll.write(getLeftLegPos() + (i * 2 / 3));
      delay(_returnHomeDelay);
    }
  }
  setLeftLegPos(90);
  setRightLegPos(90);
}

/* @Overloaded
   Rotate target foot in appropriate direction.
   args: {servo, bool}
   True rotates clockwise, false rotates anti-clockwise,
   the CLOCKWISE and ANTICLOCKWISE definitions can be used for clarity
*/
void Orbo::rotateFoot(Servo & foot, bool clockwise) {
  clockwise ? foot.write(90 - getRotSpeed()) : foot.write(90 + getRotSpeed());
}

/* @Overloaded
   Rotate target foot in appropriate direction.
   args: {Servo, char}
   True rotates clockwise, false rotates anti-clockwise,
   the CLOCKWISE and ANTICLOCKWISE definitions can be used for clarity
*/
void Orbo::rotateFoot(Servo & foot, char dir) {
  switch (dir) {
    case 'C':
      foot.write(90 - getRotSpeed());
      break;
    case 'A':
      foot.write(90 + getRotSpeed());
      break;
    default:
      foot.write(90);
  }
}

/* @Overloaded
   Stop target servo from rotating.
   args: {Servo}
   Intended to be after [rotateFoot]
*/
void Orbo::stopFoot(Servo & foot) {
  foot.write(90);
}

/* @Overloaded
   Stop both servos from rotating
   Intended to be after [rotateFoot]
*/
void Orbo::stopFoot() {
  lf.write(90);
  rf.write(90);
}

/*  Check the current state of Orbo against desired and change accordingly
    args: {bool}
    True will set orbo into walk mode and false will set orbo into drive mode
    the WALK and DRIVE definitions can be used for clarity
*/
void Orbo::modeChange(bool desiredMode) {
  if (desiredMode) {
    setIsWalkMode(true);
    ll.write(90);
    rl.write(90);
  } else {
    setIsWalkMode(false);
    ll.write(170);
    rl.write(10);
  }
  delay(200);
}

/* 
    Drive in the appropriate direction
    args: {char}
    Ensure characters are wrapped in ' ' **NOT** " ".
    The direction is defined by the first character of the direction
    e.g. "Forward" --> 'F'
*/
void Orbo::drive(char dir) {
  modeChange(false);
  switch (dir) {
    case 'F':
      lf.write(90 + getRotSpeed());
      rf.write(90 - getRotSpeed());
      break;
    case 'B':
      lf.write(90 - getRotSpeed());
      rf.write(90 + getRotSpeed());
      break;
    case 'L':
      lf.write(90);
      rf.write(90 - getRotSpeed());
      break;
    case 'R':
      lf.write(90 + getRotSpeed());
      rf.write(90);
      break;
    default:
      lf.write(90);
      rf.write(90);
  }
}

// ======================================== Getters and Setters =========================================

// _isWalkMode setter
void Orbo::setIsWalkMode(bool isWalkMode)
{
    _isWalkMode = isWalkMode;
}

//_isWalkMode getter
bool Orbo::getIsWalkMode()
{
    return _isWalkMode;
}

// _rotSpeed setter
void Orbo::setRotSpeed(int rotSpeed)
{
    _rotSpeed = rotSpeed;
}

// _rotSpeed getter
int Orbo::getRotSpeed()
{
    return _rotSpeed;
}

// _leftLegPos setter
void Orbo::setLeftLegPos(int leftLegPos)
{
    _leftLegPos = leftLegPos;
}

// _leftLegPos getter
int Orbo::getLeftLegPos()
{
    return _leftLegPos;
}

// _rightLegPos setter
void Orbo::setRightLegPos(int rightLegPos)
{
    _rightLegPos = rightLegPos;
}

// _rightLegPos getter
int Orbo::getRightLegPos()
{
    return _rightLegPos;
}

// _returnHomeDelay setter
void Orbo::setReturnHomeDelay(int returnHomeDelay)
{
    _returnHomeDelay = returnHomeDelay;
}

// _returnHomeDelay getter
int Orbo::getReturnHomeDelay()
{
    return _returnHomeDelay;
}
// ==================================== End of Getters and Setters ======================================