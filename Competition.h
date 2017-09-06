
// True while autonomous is still running.
bool autonomous_on = false;

// Continuously updates the state of the robot.
task updateDisplay() {
	bool autonomous_competition = false;

	while (true) {
		if ((vexRT[Btn7U] && vexRT[Btn8U]) || bIfiAutonomousMode) {
			if (!autonomous_on) {
			  autonomous_on = true;
			  startTask(autonomous_task);
			  autonomous_competition = bIfiAutonomousMode;
		  }
		}
		// Forcefully terminate autonomous if the competition mode says so.
		if(autonomous_on && autonomous_competition && !bIfiAutonomousMode) {
			autonomous_on = false;
			stopTask(autonomous_task);
		}

		clearLCDLine(0);
    if (bIfiRobotDisabled) {
    	displayLCDCenteredString(0, "Disabled");
    } else {
    	displayLCDCenteredString(0, autonomous_on ? "Autonomous" : "Driver");
    }
		wait1Msec(100);
	}
}

// Starts the display and enters optimistic user controlled.
task main()
{
	startTask(updateDisplay);

	// For competition, don't start too early.
	while (bIfiRobotDisabled) {
		wait1Msec(25);
	}

	while (true) {
		if (autonomous_on) {
			wait1Msec(25);
			continue;
		}
		joystick();
  }
}
