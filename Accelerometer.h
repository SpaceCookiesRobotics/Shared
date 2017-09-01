// AnalogToMilliGees converts the raw input of
// a v0.5 Accelerometer (single jumper accelerometer)
// with the jumper _removed_, into an acceleration in mG.
// TODO: calibrate the sensor at startup.
int AnalogToMilliGees(int analog) {
	// Accelerometer v1.0
	// https://www.vexrobotics.com/276-2332.html
  // With no jumper: 1.6v to 3.4v from -2g to +2g
  // Analog to digital converter: 0 to 4095
  //   1000 * ((5.0 * analog / 4096) - 2.5)
  return 5000 * analog / 4096 - 2500;
}
