/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Lauren Abbott                                             */
/*    Created:      Dec 12, 2019                                              */
/*    Description:  Competition template with auton selection                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Lauren's Functions                               */
/*                                                                           */
/*  setButton sets the description (desc) and color (c) to be used for a     */
/*  button on the brain screen. The position (pos) of the botton is given.   */
/*  Buttons 1-3 appear on the first row and buttons 4-6 appear on the        */
/*  second row. The description is also printed to the controller screen.    */
/*  Make sure to specify what controller button is used in the description.  */
/*                                                                           */
/*  clearScreens clears the brain and controller screens.                    */
/*                                                                           */
/*  pointInRectangle checks if the point (x,y) falls within the rectangle    */
/*  with corners (x1,y1) and (x2,y2), where x1 < x2 and y1 < y2. It returns  */
/*  a boolean (true or false). It is useful for checking to see if a point   */
/*  pressed on the screen corresponds to a button.                           */
/*                                                                           */
/*  whichButtonPressed determines out what button on the screen was pressed  */
/*  by the (x,y) point. It returns an integer corresponding to the button,   */
/*  between 1 and 6. It return 0 if the point is not on any button.          */
/*---------------------------------------------------------------------------*/

void setButton(int pos, const char* desc) { // , color c = black
  // These should be the same as in whichButtonPressed
  int size = 80;
  int xs[8] = {10, 120, 230, 10, 120, 230};
  int ys[8] = {25, 25, 25, 145, 145, 145};
  int brows[8] = {1, 1, 1, 7, 7, 7};
  int bcols[8] = {2, 13, 24, 2, 13, 24};
  int crows[8] = {1, 2, 3, 1, 2, 3};
  int ccols[8] = {1, 1, 1, 12, 12, 12};

  // Draw the button on brain screen
  Brain.Screen.drawRectangle(xs[pos-1], ys[pos-1], size, size);
  Brain.Screen.setCursor(brows[pos-1], bcols[pos-1]);
  Brain.Screen.print(desc);

  // Print options to controller screen
  Controller1.Screen.setCursor(crows[pos-1], ccols[pos-1]);
  Controller1.Screen.print(desc);
}

void clearScreens() {
  Brain.Screen.clearScreen();
  Controller1.Screen.clearScreen();
  task::sleep(500);
}

bool pointInRectangle(int x, int y, int x1, int y1, int x2, int y2) {
  if ((x >= x1 && x <= x2) && (y >= y1 && y <= y2)) {
    return true;
  } else {
    return false;
  }
}

int whichButtonPressed(int x, int y) {
  // These should be the same as in setButton
  int size = 100;
  int xs[8] = {10, 120, 230, 10, 120, 230};
  int ys[8] = {25, 25, 25, 145, 145, 145};

  // Return which button if point is in defined regions
  for (int i=1; i <= 8; i++) {
    if (pointInRectangle(x, y, xs[i-1], ys[i-1], xs[i-1]+size, ys[i-1]+size)) {
      return i;
    }
  }

  // Return 0 if not in defined button regions
  return 0;
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*                                                                           */
/*  Note from Lauren:                                                        */
/*  Autonomous selection can be done here. An example is provided to         */
/*  demonstrate how it works. Please modify to suit your needs.              */
/*---------------------------------------------------------------------------*/

void preAuton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  // Selection of autonomous tasks using brain screen or controller
  // First task: Define buttons
  clearScreens();
  setButton(1, "Y:");
  setButton(2, "X:");
  setButton(3, "A:");
  setButton(4, "Left:");
  setButton(5, "Up:");
  setButton(6, "Right:");

  // Second task: Save button selection
  int x, y;
  int button = 0;
  while(button == 0) {
    // If brain screen is touched
    if (Brain.Screen.pressing()) {
      x = Brain.Screen.xPosition();
      y = Brain.Screen.yPosition();

      button = whichButtonPressed(x, y);
    }

    // If controller button is pressed
    else if (Controller1.ButtonY.pressing()) {
      button = 1;
    } else if (Controller1.ButtonX.pressing()) {
      button = 2;
    } else if (Controller1.ButtonA.pressing()) {
      button = 3;
    } else if (Controller1.ButtonLeft.pressing()) {
      button = 4;
    } else if (Controller1.ButtonUp.pressing()) {
      button = 5;
    } else if (Controller1.ButtonRight.pressing()) {
      button = 6;
    }
  }

  clearScreens();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("You selected button %d", button);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Driver Control Task                          */
/*                                                                           */
/*  This task is used to control your robot during the driver control phase  */
/*  of a VEX Competition.                                                    */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void driverControl(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(driverControl);

  // Run the pre-autonomous function.
  preAuton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}