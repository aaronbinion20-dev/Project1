Aaron Binion, Duy Hung Dang 
Professor Traver
ECE 218-01
February 2026 


Project 3: Car Alarm & Windshield Wiper Subsystem


System Descriptions:

We designed a windshield wiper subsystem to be incorporated with the project 1 car alarm subsystem. The behavior of both subsystems are as follows. Firstly, when the driver seat switch is activated, the message, 
“Welcome to enhanced alarm system model 218-W26” is displayed. Then, when all four switches are activated (driver seat, passenger seat, driver seatbelt, passenger seatbelt), a green LED will ignite to indicate that ignition is enabled. 
Then, when this LED is on and the ignition button is pushed, the red engine LED is turned off and the green LED turns off. We are using a red LED instead of a blue one because there were none available. 
If the ignition button is pushed and the green LED is not on, a buzzer will sound for a time, “Ignition Inhibited” will be displayed, and error messages corresponding to unactivated switches (ex. “Passenger seat not occupied” ) 
will be displayed. Once the error messages are displayed and the buzzer is no longer sounding, additional attempts can be made. The engine should stay running even if any or all of the driver and passenger switches are unactivated, 
and when it is running simply pressing the ignition button should stop the engine. 

The wiper subsystem behavior is as follows. While the engine is running, the user can select the following wiper (PWM motor) modes with a dial (potentiometer): HI, LO, INT, or OFF.
In each mode, the wipers should start at 0 degrees, make their way up to 90 degrees, and then back down to 0 degrees. For context, a full swipe will be referred to when the wipers go from 0 degrees up to 90 degrees, 
and then back down to 0 degrees.In HI mode, the wipers should be moving at a speed of 25 rpm (revolutions per minute) with no delay between full swipes. 
In LO mode, the wipers should be moving at a speed of 10 rpm with no delay between full swipes. In INT mode, the wipers should be moving at 10 rpm, with a user set delay controlled by another dial between full swipes. 
This delay can be set to either SHORT, MEDIUM, or LONG (1, 3, or 5 seconds). In OFF mode, if the wiper is moving, the current cycle is completed and the wipers are returned to 0 degrees. 
As well, if the wiper is hesitating in INT mode, it should remain stationary, and if the system is turned on after this the motor first returns to 0 degrees then executes the current set mode. 
This also applies to when the engine is turned off and the wipers are moving. For each of these modes, a message is displayed on a 2x20 LCD display corresponding to the present wiper mode, 
including the chosen delay for INT mode if it is the present mode. 

Design Alternatives:
	
For this project, we had the opportunity to decide between using a continuous or a position servo motor. A continuous servo motor has a range of 0 degrees - 180 degrees, and a continuous servo motor does not have a range limit. 
Changing the duty cycle for the position servo motor changes its degree value, while changing the duty cycle of a continuous servo motor changes the speed of the motor. 
For this project, we decided to use a continuous servo motor as it was easier to design around, since using a continuous servo motor provided little added benefit to the system while also being more complicated to work with.
It was easier because one of the project requirements was to have the wipers go from 0 degrees to 90 degrees. With a positional servo motor this is easy, as the duty cycle for 90 degrees is a fixed value.
Meanwhile, for a continuous servo motor one would have to adjust the rate at which the duty cycle is changing and know where it is in space to achieve the same outcome, hence more difficult. 


Summary of Testing Results: 

Ignition Subsystem:

SPECIFICATION - 

When the driver seat (DS) is occupied for the first time, display a welcome message. While both seats are occupied and seatbelts are fastened / all switches on (DS, PS, DSB, PSB), engine start should be enabled / the lone green LED lit.
If ever the four switches are not on, the green LED is off. 

TEST PROCESS - 

4 switches: DS, PS, DSB, PSB
1. Display welcome message 
2. All switches on
3. All switches not on

RESULTS - 

All tests passed.

1. Welcome message displayed
   
1.Green LED on

2.Green LED off

SPECIFICATION - 

If the ignition button is pressed and the green LED is on, displaying an engine start message, turn off the green LED, and turn on the red LED. Otherwise, turn on the buzzer for three seconds and display ignition inhibited and
corresponding error messages. Allow for reattempts after error messages are printed.
If the engine is on (red LED is lit) and the ignition button is pressed, the engine is turned off (red LED is turned off).

TEST PROCESS - 

1 button: IG
1. Ignition pressed (IG), green LED on (all buttons pressed)
2. Ignition pressed (IG), green LED off (all buttons but PS pressed)
3. Attempt to start engine after previous failure
4. Engine LED is on and ignition button pressed
   
RESULTS - 

All tests passed. 
1. Green LED is turned off, engine / red LED illuminates and stays on after the ignition button is pressed, message stating engine started is displayed.
2. Buzzer turns on for three seconds, ignition inhibited message displayed and “Passenger seatbelt not fastened” message displayed.
3. Reattempts to start the engine were possible after the error messages were displayed 
4. Engine turns off


Windshield Wiper Subsystem:

SPECIFICATION - 

Wiper mode cannot be selected before the red engine LED is on. While the red engine LED is on, allow the user to select between OFF, LO, HI, and INT modes with a potentiometer (dial). The PWM position motor should go precisely 
from 0 degrees to 90 degrees in every mode that moves the motor. When LO is selected, the motor goes from 0 degrees to 90 degrees at 10 rpm, and back down to 0 degrees at the same speed with no delay after returning to 0 degrees. 
When HI  is selected, the motor goes from 0 degrees to 90 degrees at 25 rpm, and back down to 0 degrees at the same speed with no delay after returning to 0 degrees. When INT is selected, the motor goes from 0 degrees to 90 degrees at 
10 rpm, and back down to 0 degrees at the same speed with a user set delay after a return to 0 degrees: 1, 3, or 5 seconds. Corresponding wiper modes and delays are displayed to the LCD display for the user.

TEST PROCESS - 

2 potentiometers: SM, SD
1. Red engine LED is not on
2. Select Mode (SM) 
OFF (SM dial turned all the way to the left) while red LED is on
3. Select Mode (SM) LO (SM dial turned 90 degrees clockwise from start, motor at 10 RPM)
while red LED is on
4. Select Mode (SM) HI (SM dial turned 180 degrees clockwise from start, motor at 25 RPM) 
while red LED is on
5. Select Mode (SM) INT (SM dial turned 270 degrees clockwise from start, motor at 10 rpm w/ user set delay SD) while red LED is on
6. Select Delay (SD) of 1, 3, and 5 seconds (SD dial turned all the way to left, 130 degrees clockwise from start, all the way to the right while in INT mode) while red LED is on
   
RESULTS - 

All tests passed.
1. Wiper mode cannot be set while red engine LED is off, and motor is not moving 
2. Wiper mode OFF is successfully selected while red engine LED is on, motor is not moving, mode OFF is displayed on the LCD display. 
3. Wiper mode LO is successfully selected while red engine LED is on, motor is moving precisely from 0 degrees to 90 degrees and back down to 0 degrees at 10 rpm with no delay after returning to 0 degrees, mode LO is displayed on the LCD display. 
4. Wiper mode HI is successfully selected while red engine LED is on, motor is moving precisely from 0 degrees to 90 degrees and back down to 0 degrees at 25 rpm with no delay after returning to 0 degrees, mode HI is displayed on the LCD display. 
5. Wiper mode INT is successfully selected while red engine LED is on, motor is moving precisely from 0 degrees to 90 degrees and back down to 0 degrees at 10 rpm with a user set delay after returning to 0 degrees, mode INT is displayed on the LCD display. 
6. Delay for INT mode is successfully selected as 1, 3, or 5 seconds while red engine LED is on, motor is moving precisely from 0 degrees to 90 degrees and back down to 0 degrees at 10 rpm with a delay after returning to 0 corresponding to the set delay,
current delay is shown on the LCD display

SPECIFICATION - 

If the IG button is pressed while the engine LED is on / mode is set to OFF and the motor is moving, return the motor to 0 degrees and stop.
If the IG button is pressed while engine LED is on / mode is set to OFF and the motor is hesitating in INT mode, remain stationary 

TEST PROCESS - 

2 potentiometers: SM, SD
1 button: IG
1. Select mode (SM) OFF / press ignition while engine is running while motor is moving in LO, HIGH, and INT mode 
2. Select mode (SM) OFF / press ignition (IG) while engine is running while motor is hesitating in  INT mode with delays of 1, 3, and 5 seconds
   
RESULTS - 

All tests passed. 
1. Motor returned to 0 degrees in LO, HIGH, and INT modes while the motor was moving after engine was turned off / SM turned to OFF
2. Motor remained stationary at 0 degrees with delays of 1, 3, and 5 seconds while hesitating in INT mode when the engine was turned off / SM set to OFF


