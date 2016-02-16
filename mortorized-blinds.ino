/**

 *  Particle Photon
 
 *

 *  Author: Justin Wurth

 *  Date: 2014-09-19

 */

// a maximum of eight servo objects can be created 

// Constants
#define SERVO_PIN       A4  
#define SWITCH_PIN      D0

Servo myservo;
int state;
int open=0; 
int closed=150; 

// Functions
int setState(String command);

void setup(){
  myservo.attach(A4);   
  myservo.attach(SERVO_PIN); // attaches the servo on analog pin A4 to the servo object
  Particle.function("setstate", setState);
  Particle.variable("getstate", &state, INT);
  state=myservo.read();
  pinMode(SWITCH_PIN,  INPUT_PULLUP);
}

void loop(){
  if(!digitalRead(SWITCH_PIN)){
    delay(50);
    myservo.attach(A4);
    myservo.attach(SERVO_PIN);
    state=(state)?open:closed; // Toggle between fully open and closed
    myservo.write(state);
    delay(500);
    analogWrite(A4,255);
    // TODO: Notify Smart things
  }
  while(!digitalRead(SWITCH_PIN));
}

int setState(String command){ 
    myservo.attach(A4);
    myservo.attach(SERVO_PIN);
    state = command.toInt(); 
    state = map (state, 0, 99, open, closed); 
    myservo.write(state); 
    delay(500);
    analogWrite(A4,255);
    return 1;
    }
