/* sample program for how to do menus using the LCD display */

/* choices are:
  go left / go right
  go short / go long
  do all cones / first cone only / second cone only

  Arrange these left to right on the top line of the display

  Left  Short  ALL

  with the first 3 buttons toggling thru the options
*/
string leftRightMenuText[2]={"left", "right" };
//enum DirType { GO_LEFT, GO_RIGHT};
//DirType direction=GO_LEFT;
int direction=0;// can be 0,1

string shortLongMenuText[2]={"short", "long" };
//enum DistType { GO_SHORT, GO_LONG};
//DistType distance=GO_SHORT;
int distance=0; // can be 0,1
string numConesText[3]={"ALL", "1  ", "2  " };
//enum ConesType { DO_ALL_CONES, DO_FIRST_CONE_ONLY, DO_SECOND_CONE_ONLY};
//ConesType cones=DO_ALL_CONES;
int cones=0; // can be 0,1,2

// look at the 3 variables direction, distance, cones
// and update the display to match
void UpdateDisplay(void){
	clearLCDLine(0);
	displayLCDString(0,0, 	leftRightMenuText[direction]); // left/right
	displayLCDString(0,7, 	shortLongMenuText[distance]); // short/long
	displayLCDString(0,13, 	numConesText[cones]); // how many cones
}// UpdateDisplay

/* LCD buttons
0:  No buttons pressed
1:  Left button is pressed
2:  Center button is pressed
3:  Left and Center buttons are pressed
4:  Right button is pressed
5:  Left and Right buttons are pressed
6:  Center and Right buttons are pressed
7:  Left, Center, and Right buttons are pressed
So this is actually assigning bits to the buttons.
Bit0: left button pressed
Bit1: center button pressed
Bit2: right button pressed
*/
bool leftWasPressed=false, // was left pressed last time we looked at it
      centerWasPressed=false,
      rightWasPressed=false;

void ReadLCDbuttons(void){
	bool leftPressed=((int)nLCDButtons & 1) !=0; // &1 masks off bit 0
	bool centerPressed=((int)nLCDButtons & 2) !=0; // &2 masks off bit 1
	bool rightPressed=((int)nLCDButtons & 4) !=0; // &4 masks off bit 2

	// we only register a button press if it previously wasn't pressed, and is pressed now
	// so holding down a button doesn't make the menu cycle thru at warp speed
	if(!leftWasPressed && leftPressed){
		// increment the counter
	   direction=(direction+1)%2; // %2 is read "mod two" and means remainder after dividing by two
  }
  	if(!centerWasPressed && centerPressed){
		// increment the counter
	   distance=(distance+1)%2; // %2 is read "mod two" and means remainder after dividing by two
  }
 	if(!rightWasPressed && rightPressed){
		// increment the counter
	   cones=(cones+1)%3; // %3 is read "mod three" and means remainder after dividing by three
  }

  // update for next time we look
  leftWasPressed=leftPressed;
  centerWasPressed=centerPressed;
  rightWasPressed=rightPressed;

}// ReadLCDbuttons

task main()
{

while(true){
	ReadLCDbuttons();
UpdateDisplay();
}// while


}// main
