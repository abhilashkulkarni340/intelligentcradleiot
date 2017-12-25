#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial cell(9,10);
Servo myservo; 
int pos = 0;
int pirPin1=6;
int pirPin2=5;
int noisePin1=7;
int noisePin2=8;
int pir1_flag=0;
int pir2_flag=0;
int noise1_flag=0;
int noise2_flag=0;
int flag_noise=0;
int calibrationTime = 30;       
void setup() {
  cell.begin(9600);
  delay(500);
  Serial.begin(9600);
  pinMode(pirPin1, INPUT);
  pinMode(pirPin2, INPUT);
  pinMode(noisePin1, INPUT);
  pinMode(noisePin1, INPUT);
  myservo.attach(11);
  Serial.print("calibrating sensor ");
  for(int i = 0; i<calibrationTime; i++){
        Serial.print(".");
        delay(1000);
     }
   Serial.println(" done");
   Serial.println("SENSOR ACTIVE");
   delay(50);

}
void loop(){
  pir1();
  pir2();
  noise1();
  noise2();
  if(noise1_flag==1 || noise2_flag==1)
  {
    flag_noise=1;
  }
  else
  {
    flag_noise=0;
  }
  if(pir1_flag==1 && pir2_flag==1 && flag_noise==1 )
  {
    gsm();
    servo();
  }
  else if(pir1_flag==1 && pir2_flag==1)
  {
   gsm();
   servo();
  }
  delay(2500);
  pir1_flag=0;
  pir2_flag=0;
  noise1_flag=0;
  noise2_flag=0;
  flag_noise=0; 
}
void pir1() {
 if(digitalRead(pirPin1) == HIGH){
    Serial.println("Motion detected PIR-1");
    pir1_flag=1;
}
else{
  Serial.println("Motion not detected PIR-1");
  pir1_flag=0;
} 
 }
 void pir2() {
 if(digitalRead(pirPin2) == HIGH){
    Serial.println("Motion detected PIR-2");
    pir2_flag=1;
}
else{
  Serial.println("Motion not detected PIR-2");
  pir2_flag=0;
} 
}
 
 void noise1(){
 if(digitalRead(noisePin1) == LOW){
    Serial.println("Noise detected sensor-1");
    noise1_flag=1;
}
else{
  Serial.println("Noise not detected sensor-1");
  noise1_flag=0;
} 
}
void noise2(){
 if(digitalRead(noisePin2) == LOW){
    Serial.println("Noise detected sensor-2");
    noise2_flag=1;
}
else{
  Serial.println("Noise not detected sensor-2");
  noise2_flag=0;
} 
}
void servo() { 
  int i=0;
  while(i<4)
  {
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos); 
    delay(15);                                
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);
    delay(15);               
   }
  i++;
}
}
void gsm()
{ cell.println("AT;");
  if(cell.available()>0)
  {
    cell.println("At+CREG=1;");
    
  cell.println( "AT+CLIP = 1;" );
   
    Serial.println("CALLING..........");
    cell.println("ATD+7045347637;");   
    Serial.println("Contacting caretaker");
  }
  delay(20000);
  Serial.println("CALL ENDED");
}
