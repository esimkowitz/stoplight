/*  stoplight_sandbox
 *  
 *  CSE 132 - Studio 3
 *  
 *  Fill this out so we know whose studio this is.
 *  
 *  Name: Evan Simkowitz
 *  WUSTL Key: esimkowitz
 *  
 *  Name: Brandon Staffeil 
 *  WUSTL Key:bjstaffeil
 *  
 *  Name:
 *  WUSTL Key:
 *  
 *  Name:
 *  WUSTL Key:
 */
 
const int rgbPinR = 11;
const int rgbPinG = 9;
const int rgbPinB = 10;
const int NSgreenPin = 5;
const int NSyellowPin = 4;
const int NSredPin = 3;
const int EWgreenPin = 2;
const int EWyellowPin = 6;
const int EWredPin = 7;
const int redR = 255;
const int redG = 0;
const int redB = 0;
const int whiteR = 255;
const int whiteG = 255;
const int whiteB = 255;
const int NSGTime = 4000;
const int NSYTime = 2000;
const int EWGTime = 4000;
const int EWYTime = 2000;
const int PedTime = 6000;
const int deltaTWalk = 233;
int deltaT = 0;
long int accumulator = 0;
long int walkAccumulator = 0;
enum Direction {EWG, EWY, NSG, NSY, Ped};
Direction traffic = NSG;
boolean walkOn = false;
boolean runPed = false;			//So that I can run the Switch and still run the Ped program
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
    digitalWrite(EWredPin, HIGH);
}

void loop() {
	if (millis() - accumulator > deltaT) {
    accumulator += deltaT;
		switch(traffic) {
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
	if(millis()-walkAccumulator > deltaTWalk) {
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
