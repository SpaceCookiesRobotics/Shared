# Shared code

This repository contains code that can be shared between all the teams.

The main one is the _Competition code_. Use is like so:

```c
#include "../Shared/Competition.h"

// Instead of task main(), define the following two functions:

void joystick() {
  while (true) {
    // Usual joystick logic.
  }
}

void autonomous() {
  // Write your autonomous here.
  ...
}
```

When you turn the robot on, it will directly start the joystick code. You can trigger
autonomous mode by pressing _7U_ and _8U_ simultaneously. You can then cancel the running
autonomous by pressing _7D_ and _8D_.

If an LCD display is connected, the robot will indicate in which mode it. 