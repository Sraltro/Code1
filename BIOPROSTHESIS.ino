int num_Measure = 128 ; // Set the number of measurements   
int pinSignal = A0; // pin connected to pin O module sound sensor  
long Sound_signal;    // Store the value read Sound Sensor   
long sum = 0 ; // Store the total value of n measurements   
long level = 0 ; // Store the average value   
int motor = 2;
int count = 0;
unsigned long previousMillis = 0;
int previousValue = 0;
bool check = false;
int threeMinutes = 180000;
 
void setup ()  
{   
  pinMode (pinSignal, INPUT); // Set the signal pin as input  
  pinMode (motor, OUTPUT); 
  Serial.begin (9600); 
  digitalWrite (motor, LOW);
}  
   
void loop ()  
{  
  // Performs 128 signal readings   
  for ( int i = 0 ; i <num_Measure; i ++)  
  {  
   Sound_signal = analogRead (pinSignal);  
    sum =sum + Sound_signal;  
  }  
 
  level = sum / num_Measure - 150; // Calculate the average value   
  Serial.print("Sound Level: ");
  Serial.print (level); 
  Serial.println(" dB");
  sum = 0 ;

    if(level > 70 && level < 85){
      check = wait(threeMinutes, 70, level);
      if(check == true)
        mediumWarning();
      check = false;
    }
    else if(level > 85 && level < 350){
      check = wait(threeMinutes, 70, level);
      if(check == true)
        highWarning();
      check = false;
  }
  count++;
  delay(200);
}

bool wait(int waitTime, int threshold, long value) {
  static unsigned long startTime = 0; // Static variable to store the start time when the threshold is first exceeded

  if (value >= threshold) { // If current value exceeds threshold
    if (startTime == 0) { // If this is the first time the threshold is exceeded
      startTime = millis(); // Record  start time
    } else {
      if (millis() - startTime >= waitTime) { // If enough time has passed since the start time
        startTime = 0; // Reset start time for next iteration
        return true;
      }
    }
  } else {
    startTime = 0; // Reset start time if the value drops below the threshold
  }

  return false; 
}

void mediumWarning(){
  digitalWrite(motor, HIGH);
  delay(300);
  digitalWrite(motor, LOW);
}

void highWarning(){
  for(int i = 0; i < 3; i++){
    digitalWrite(motor, HIGH);
    delay(800);
    digitalWrite(motor, LOW);
    delay(400);
  }
}