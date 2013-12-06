//Getting EMF Readings with LilyPad
// original code/project by Aaron ALAI - aaronalai1@gmail.com
// modified for use w/ LilyPad vibration Board by Andrew Cotter - cotter.andrew.p@gmail.com


#define NUMREADINGS 15 // raise this number to increase data smoothing

int haptic = 3;
int sensor = A5;

int senseLimit = 75; // raise this number to decrease sensitivity (up to 1023 max)
int val = 0; // reading from probePi


// variables for smoothing

int readings[NUMREADINGS];                // the readings from the analog input
int index = 0;                            // the index of the current reading
int total = 0;                            // the running total
int average = 0;                          // final average of the probe reading


void setup(){
  pinMode(haptic, OUTPUT);
  pinMode(sensor, INPUT);
  
  Serial.begin(9600);  // initiate serial connection for debugging/etc

  for (int i = 0; i < NUMREADINGS; i++)
    readings[i] = 0;                      // initialize all the readings to 0
}

void loop(){
  
  val = analogRead(sensor); //take a reading of the sensor
  
  if(val >= 1){
    
    val = constrain(val, 1, senselimit); // turn any reading higher than the senseLimit value into the senseLimit value
    val = map(val, 1, senseLimit, 1, 1023); // remap the constrained value within a 1 to 1023 range
    
    total -= readings[index];               // subtract the last reading
    readings[index] = val;         // read from the sensor
    total += readings[index];               // add the reading to the total
    index = (index + 1);                    // advance to the next index
    
    
    if (index >= NUMREADINGS)               // if we're at the end of the array...
      index = 0;                            // ...wrap around to the beginning

    average = total / NUMREADINGS;          // calculate the average
    
    
    if(average > 400){
      digitalWrite(haptic = HIGH);
    }
    else{
      digitalWrite(haptic = LOW);
    }
    
    Serial.println(val); // use output to aid in calibrating
    
  }
}
