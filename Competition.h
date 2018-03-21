// Forward definition of the functions that need to be defined for each
// robot. Doing this avoid warnings from the compiler.
void autonomous();
void joystick();

// True while autonomous is still running.
bool COMP_autonomous_on = false;

// This just wraps around the "autonomous" function written for each robot.
task COMP_autonomousTask() {
	// The competition task also changes the running state explicitly.
  // Doing so ensures that whether we complete before the time elapses
  // or after it does, the state is accurate.
	COMP_autonomous_on = true;
	autonomous();
	COMP_autonomous_on = false;
}

// This just wraps around the "joystick" function written for each robot.
task COMP_driverControlled() {
  joystick();
}

// Stop all possible tasks but the main one.
void allTasksStop();

// main decides whether we are in autonomous or joystick mode and sets up
// the tasks accordingly.
task main() {
	enum State {
		STARTING = 0,
		AUTONOMOUS_RUNNING = 1,
		JOYSTICK_RUNNING = 2,
	};

	State current = STARTING;
  bool autonomous_competition = false;

	while (true) {
		State expected;
		if (bIfiRobotDisabled) {
			expected = STARTING;
		} else if ((vexRT[Btn7U] && vexRT[Btn8U]) || bIfiAutonomousMode) {
		  // Button 7 Up + Button 8 Up cause autonomous to fire.
			expected = AUTONOMOUS_RUNNING;
			autonomous_competition = bIfiAutonomousMode;
		} else if (COMP_autonomous_on && vexRT[Btn7D] && vexRT[Btn8D]) {
      // Button 7 Down + Button 8 Down forcefully terminate autonomous.
			expected = JOYSTICK_RUNNING;
		} else if (COMP_autonomous_on && autonomous_competition && !bIfiAutonomousMode) {
      // Forcefully terminate autonomous if the competition mode says so.
			expected = JOYSTICK_RUNNING;
	  } else if (!COMP_autonomous_on) {
	    // Notice when autonomous finishes on its own.
	    expected = JOYSTICK_RUNNING;
	  }

	  if (current != expected) {
  		clearLCDLine(0);
	  	switch (expected) {
       	case STARTING:
        	displayLCDCenteredString(0, "Disabled");
       	  break;
	  	  case AUTONOMOUS_RUNNING:
      	  displayLCDCenteredString(0, "Autonomous");
      	  allTasksStop();
	  	    startTask(COMP_autonomousTask);
	  	    break;
	  	  case JOYSTICK_RUNNING:
    	    displayLCDCenteredString(0, "Joystick");
      	  allTasksStop();
	  	    startTask(COMP_driverControlled);
	  	    break;
	    }
	    current = expected;
	  }

		wait1Msec(25);
	}
}

void allTasksStop() {
  stopTask(1);
  stopTask(2);
  stopTask(3);
  stopTask(4);
#if defined(VEX2)
  stopTask(5);
  stopTask(6);
  stopTask(7);
  stopTask(8);
  stopTask(9);
  stopTask(10);
  stopTask(11);
  stopTask(12);
  stopTask(13);
  stopTask(14);
  stopTask(15);
  stopTask(16);
  stopTask(17);
  stopTask(18);
  stopTask(19);
#endif
}
