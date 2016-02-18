/*  stoplight_sandbox
 *
 *  The Arduino should be wired with an rgb LED and two 'stoplights'
 *  The 'stoplights' should each be a row of three LEDS, a green, a yellow, and then a red.
 *  You can think of each 'stoplight' as controlling an intersection, either NS (North/South) or EW (East/West).
 *  I arbitrarily chose the 'stoplight' closer to the rgb LED to be NS and the one farther away to be EW.
 *  
 */
 
const int rgbPinR = 11;     //rgb LED used for the walk light
const int rgbPinG = 9;
const int rgbPinB = 10;
const int NSgreenPin = 5;
const int NSyellowPin = 4;
const int NSredPin = 3;
const int EWgreenPin = 2;
const int EWyellowPin = 6;
const int EWredPin = 7;
const int redR = 255;       //defines the colors used by the rgb LED
const int redG = 0;
const int redB = 0;
const int whiteR = 255;
const int whiteG = 255;
const int whiteB = 255;
const int NSGTime = 4000;   //defines the time that each state will be on for
const int NSYTime = 2000;
const int EWGTime = 4000;
const int EWYTime = 2000;
const int PedTime = 6000;
const int deltaTWalk = 233; //sets the half-period of the blinking walk signal
int deltaT = 0;             //this is the variable we change when changing the timing of each state
long int accumulator = 0;
long int walkAccumulator = 0;
enum Direction {EWG, EWY, NSG, NSY, Ped}; //stoplight can be one of these 5 states: NS-Green, NS-Yellow, EW-Green, EW-Yellow, walk signal
Direction traffic = NSG;    //Starts at NSG
boolean walkOn = false;     //Used to blink the walk light at a set interval, true when on, false when off
boolean runPed = false;			//Because Ped state changes the traffic variable to NSG when run, I need a separate variable to tell me when I am in the Ped state
void setup() {
  	pinMode(rgbPinR, OUTPUT);
  	pinMode(rgbPinG, OUTPUT);
  	pinMode(rgbPinB, OUTPUT);
  	pinMode(NSgreenPin, OUTPUT);
  	pinMode(NSyellowPin, OUTPUT);
  	pinMode(NSredPin, OUTPUT);
    pinMode(EWgreenPin, OUTPUT);
    pinMode(EWyellowPin, OUTPUT);
    pinMode(EWredPin, OUTPUT);
    digitalWrite(EWredPin, HIGH);     //Because NSG is part of a loop, it will only digitalWrite() to pins being changed. However, since
}                                     //EWredPin is supposed to be on at NSG but is not changed by it, I set it on here so that it wil be on in
                                      //the initial loop.
void loop() {
	if (millis() - accumulator > deltaT) {
    accumulator += deltaT;
		switch(traffic) {     //defines what each state of traffic does
			case NSG:   deltaT = NSGTime;
				          digitalWrite(rgbPinR, redR);
      	          digitalWrite(rgbPinG, redG);
      	          digitalWrite(rgbPinB, redB);
      	          digitalWrite(NSgreenPin, HIGH);
    	            digitalWrite(NSredPin, LOW);
    		          runPed = false;
                  walkOn = false;
    		          traffic = NSY;
    		          break;
    	case NSY:   deltaT = NSYTime;
                  digitalWrite(NSgreenPin, LOW);
                  digitalWrite(NSyellowPin, HIGH);
      	          traffic = EWG;
      	          break;
      case EWG:   deltaT = EWGTime;
                  digitalWrite(EWgreenPin, HIGH);
                  digitalWrite(EWredPin, LOW);
                  digitalWrite(NSyellowPin, LOW);
                  digitalWrite(NSredPin, HIGH);
      	          traffic = EWY;
      	          break;
      case EWY:   deltaT = EWYTime;
                  digitalWrite(EWyellowPin, HIGH);
                  digitalWrite(EWgreenPin, LOW);
    		          traffic = Ped;
    		          break;
    	case Ped:   deltaT = PedTime;
                  digitalWrite(EWredPin, HIGH);
    		          digitalWrite(EWyellowPin, LOW);
    		          traffic = NSG;
    		          runPed = true;
    		          break;
		}
	}
	if(millis()-walkAccumulator > deltaTWalk) {      //when the Ped state is active, this statement will control the blinking walk signal
  	walkAccumulator += deltaTWalk;
    if (runPed) {
    	if (!walkOn) {
      	digitalWrite(rgbPinR, whiteR);
        digitalWrite(rgbPinG, whiteG);
        digitalWrite(rgbPinB, whiteB);
    		walkOn = true;
  		} else if(walkOn) {
    		digitalWrite(rgbPinR, LOW);
        digitalWrite(rgbPinG, LOW);
        digitalWrite(rgbPinB, LOW);
        walkOn = false;
  		}
  	}
	}
}
