int num_Measure = 128 ; //number of measurements   
int pinSignal = A0; //sound sensor module  
long Sound_signal;  //value of Sound Sensor   
long sum = 0 ;  //total value of n measurements   
long level = 0 ; //average value
int motor = 2; //vibration motor

//To prevent motor from vibrating constantly (Cause it's annoying)
int count = 0; 
unsigned long startMillis;
const unsigned long period1 = 10000; //10 seconds
const unsigned long period2 = 5000; //5 seconds
int nestCount;

void setup ()  
{   
  pinMode (pinSignal, INPUT); //Sound Sensor to input
  pinMode (motor, OUTPUT);  //Motor to output
  Serial.begin (9600);
  startMillis = millis();
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
  Serial.println(level); 
  sum = 0 ;

  /*
    This if statement is just to make sure the motor doesn't vibrate when first turning on
    Since the level value starts at like 150+
    p.s. using delay is pointless, I tried :(
  */
  if(count > 10){
    if(level > 70 && level < 85) //check if noise level is within range
      mediumWarning();
    else if(level > 85 && level < 350)  //check if noise level is within range
      highWarning();
  }
  count++;
  delay(200);
}

void mediumWarning(){
  unsigned long currentMillis = millis();
  if(nestCount >= 10){
    if(currentMillis - startMillis >= period1){
      nestCount = 0;
    }
  }
  if(nestCount <= 10){
    digitalWrite(motor, HIGH);
    delay(300);
    digitalWrite(motor, LOW);
    nestCount++;
  }
}

void highWarning(){
  unsigned long currentMillis = millis();
  if(nestCount >= 10){
    if(currentMillis - startMillis >= period2){
      nestCount = 0;
    }
  }
  if(nestCount <= 10){
    for(int i = 0; i < 3; i++){
    digitalWrite(motor, HIGH);
    delay(800);
    digitalWrite(motor, LOW);
    delay(400);
  }
    nestCount++;
  }
}