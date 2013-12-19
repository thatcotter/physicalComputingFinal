// EMF LilyPad Haptic Feedback
// original code/project by Aaron ALAI - aaronalai1@gmail.com
// modified for use w/ LED bargraph by Collin Cunningham - collin@makezine.com
//modified for LilyPad with Haptic Feedback by Andrew Cotter

int curve = 0;

#define NUMREADINGS 15 // raise this number to increase data smoothing

int senseLimit = 350; // raise this number to decrease sensitivity (up to 1023 max)
int probePin = A2; // analog 5
int val = 0; // reading from probePin

int LED1 = 11;  // connections
int LED2 = 10;  // to
int LED3 = 9;   // LED

int LED4 = 6;   

int haptic = A5;


// variables for smoothing

int readings[NUMREADINGS];                // the readings from the analog input
int index = 0;                            // the index of the current reading
int total = 0;                            // the running total
int average = 0;                          // final average of the probe reading


void setup() {

  pinMode(2, OUTPUT);  // specify LED bargraph outputs
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT);
  pinMode(A5, OUTPUT); 

  Serial.begin(9600);  // initiate serial connection for debugging/etc

  for (int i = 0; i < NUMREADINGS; i++)
    readings[i] = 0;                      // initialize all the readings to 0
}

void loop() {

  val = analogRead(probePin);  // take a reading from the probe

  if(val >= 1){                // if the reading isn't zero, proceed

    val = constrain(val, 1, senseLimit);  // turn any reading higher than the senseLimit value into the senseLimit value
    val = map(val, 1, senseLimit, 1, 1023);  // remap the constrained value within a 1 to 1023 range

    total -= readings[index];               // subtract the last reading
    readings[index] = val; // read from the sensor
    total += readings[index];               // add the reading to the total
    index = (index + 1);                    // advance to the next index

    if (index >= NUMREADINGS)               // if we're at the end of the array...
      index = 0;                            // ...wrap around to the beginning

    average = total / NUMREADINGS;          // calculate the average


    if (average > 50 + curve){                // if the average is over 50 ...
      digitalWrite(LED1, HIGH);   // light the first LED
    }
    else{                         // and if it's not ...
      digitalWrite(LED1, LOW);    // turn that LED off
    }


    if (average > 150 + curve){               // and so on ...
      digitalWrite(LED2, HIGH);
    }
    else{
      digitalWrite(LED2, LOW);
    }

    if (average > 250 + curve){
      digitalWrite(LED3, HIGH);
      digitalWrite(haptic, HIGH);
    }
    else{
      digitalWrite(LED3, LOW);
      digitalWrite(haptic, LOW);
    }


    if (average > 350 + curve){
      digitalWrite(LED4, HIGH);
    }
    else{
      digitalWrite(LED4, LOW);
    }


    Serial.println(val); // use output to aid in calibrating
  }
}
