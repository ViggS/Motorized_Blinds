/**

 *  Spark Core

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
int open=0; //changed from 0 on 2/9
int closed=150; //changed from 150 on 2/9 at 2:54pm

// Functions
int setState(String command);

void setup(){
  myservo.attach(A4);   
  myservo.attach(SERVO_PIN); // attaches the servo on analog pin A4 to the servo object
  Spark.function("setstate", setState);
  Spark.variable("getstate", &state, INT);
  state=myservo.read();
  pinMode(SWITCH_PIN,  INPUT_PULLUP);
}

void loop(){
  if(!digitalRead(SWITCH_PIN)){
    delay(50);
    state=(state)?open:closed; // Toggle between fully open and closed
    myservo.write(state);
    // TODO: Notify Smart things
  }
  while(!digitalRead(SWITCH_PIN));
}

int setState(String command){ 
    state = command.toInt(); 
    state = map (state, 0, 80, open, closed); //second number was 99 on 2/9 at 2:48PM
    myservo.write(state); //changed from myservo.write(state)
    return 1;
    }


