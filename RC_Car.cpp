   #include <NewPing.h>
     
    
    #define MAX_DISTANCE_1 20
    #define MAX_DISTANCE_2 30
    #define MAX_DISTANCE_3 21
    // Max distance in cm.
    #define PING_INTERVAL 30 // Milliseconds between pings.
     
 //   unsigned long pingTimer[SONAR_NUM]; // When each pings.
   // unsigned int cm[SONAR_NUM]; // Store ping distances.
    //uint8_t currentSensor = 0; // Which sensor is active.
     
    NewPing dist1(6,7, MAX_DISTANCE_1);
    NewPing dist2(15,14, MAX_DISTANCE_2);
    NewPing dist3(19,18, MAX_DISTANCE_3);






#define enbR 11
#define fwrR 12
#define rvrR 13
#define enbL 10
#define fwrL 9
#define rvrL 8
#define trigPin1 6
#define echoPin1 7
#define trigPin2 15
#define echoPin2 14
#define trigPin3 19
#define echoPin3 18
#define rightW 3
#define leftW 5
#define midW 4
char in_byte = 0;
char last_direction ;
bool flag;
int LW = 0;
int MW = 0;
int RW = 0;
long duration1;
int distance1;
long duration2;
int distance2;
bool b = 0;
bool t = 1;
void brake()
{
  analogWrite(enbR,LOW);
  analogWrite(enbL,LOW);
  digitalWrite(fwrL,LOW);
  digitalWrite(fwrR,LOW);
  digitalWrite(rvrR,LOW);
  digitalWrite(rvrL,LOW);
}
void forward (int spd)
{
  analogWrite(enbR,spd);
  analogWrite(enbL,spd);
  digitalWrite(fwrL,HIGH);
  digitalWrite(fwrR,HIGH);
  digitalWrite(rvrR,LOW);
  digitalWrite(rvrL,LOW);
}
void backward (int spd)
{
  analogWrite(enbR,spd);
  analogWrite(enbL,spd);
  digitalWrite(fwrL,LOW);
  digitalWrite(fwrR,LOW);
  digitalWrite(rvrR,HIGH);
  digitalWrite(rvrL,HIGH); 
}
void right (int spd1, int spd2)
{
  analogWrite(enbR,spd1);
  analogWrite(enbL,spd2);
  digitalWrite(fwrL,HIGH);
  digitalWrite(fwrR,HIGH);
  digitalWrite(rvrR,LOW);
  digitalWrite(rvrL,LOW);
}
void rightc (int spd1, int spd2)
{
  analogWrite(enbR,spd2);
  analogWrite(enbL,spd1);
  digitalWrite(fwrL,HIGH);
  digitalWrite(fwrR,LOW);
  digitalWrite(rvrR,HIGH);
  digitalWrite(rvrL,LOW);
}
void left (int spd1, int spd2)
{
  analogWrite(enbR,spd2);
  analogWrite(enbL,spd1);
  digitalWrite(fwrL,HIGH);
  digitalWrite(fwrR,HIGH);
  digitalWrite(rvrR,LOW);
  digitalWrite(rvrL,LOW);
}
void leftc (int spd1, int spd2)
{
  analogWrite(enbR,spd1);
  analogWrite(enbL,spd2);
  digitalWrite(fwrL,LOW);
  digitalWrite(fwrR,HIGH);
  digitalWrite(rvrR,LOW);
  digitalWrite(rvrL,HIGH);
}

bool track (bool right,bool mid,bool left,bool x,bool y,bool z)
{
  if((right == x) && (mid == y) && ( left == z)) return 1;
  else return 0;
  
}

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(enbR,OUTPUT);
 pinMode(fwrR,OUTPUT);
 pinMode(rvrR,OUTPUT);
 pinMode(enbL,OUTPUT);
 pinMode(fwrL,OUTPUT);
 pinMode(rvrL,OUTPUT);
 pinMode(trigPin1,OUTPUT);
 pinMode(echoPin1,INPUT);
 pinMode(echoPin2,INPUT);
 pinMode(trigPin2,OUTPUT);
 pinMode(echoPin3,INPUT);
 pinMode(trigPin3,OUTPUT);
 pinMode(midW,INPUT);
 pinMode(leftW,INPUT);
 pinMode(rightW,INPUT);
}

void loop() {
Serial.print(dist1.ping_cm());Serial.print(" ");
Serial.print(dist2.ping_cm());Serial.print(" ");
Serial.println(dist3.ping_cm());
RW = digitalRead(rightW);  
MW = digitalRead(midW);
LW = digitalRead(leftW);
if (Serial.available()>0)
{
 in_byte = Serial.read(); 
}
if (in_byte == '5') {b = 1; t = 0;}
if (in_byte == '6') {b = 0; t = 1;}
if (t)
{
if (dist1.ping_cm()== 0 ) {
  Normal:
if(track(LW,MW,RW,0,1,0)) {forward(150); Serial.println("forward");}
else if((track(LW,MW,RW,0,0,1))) {rightc(170, 170);last_direction='R';Serial.println("right");}
else if((track(LW,MW,RW,1,0,0))) {leftc(180,180);last_direction='L';Serial.println("left");}
else if (track(LW,MW,RW,1,1,1)|| (track(LW,MW,RW,1,1,0)) ||(track(LW,MW,RW,0,1,1))) {
  if(dist2.ping_cm() != 0) {rightc(120, 120);Serial.println("rightblack");}
 else {forward(150); Serial.println("black");}
  }
}

else if (dist1.ping_cm()!= 0)                                    
{ 
    if (last_direction == 'R')
    {  //rightc(255,0);delay(150);
      while(1)
      {
    if (dist2.ping_cm() == 0) {right(255,0);Serial.print("ultraright");Serial.print(" ");Serial.print(dist1.ping_cm());Serial.print(" ");Serial.print(dist2.ping_cm());Serial.print(" ");Serial.println(dist3.ping_cm());}
    if (dist2.ping_cm() != 0)
      {
RW = digitalRead(rightW);
MW = digitalRead(midW);
LW = digitalRead(leftW);
    forward(130);Serial.print("ultraforward"); Serial.print(" ");Serial.print(dist1.ping_cm());Serial.print(" ");Serial.print(dist2.ping_cm());Serial.print(" ");Serial.println(dist3.ping_cm());if(!(track(LW,MW,RW,0,0,0))){rightc(150,150); break;}
    } 
    }    }

if (last_direction == 'L')
  {  
    while(1)
    {
         // NewPing dist1(6,7,24);
   if (dist3.ping_cm() == 0) {left(230,0);Serial.print("ultraleft");Serial.print(" ");Serial.print(dist1.ping_cm());Serial.print(" ");Serial.print(dist2.ping_cm());Serial.print(" ");Serial.println(dist3.ping_cm());}
      if (dist3.ping_cm() != 0)
      {
while(dist3.ping_cm() > 10 ){forward(130);Serial.println("ultraforward");Serial.println(dist3.ping_cm());}
      if (dist3.ping_cm() == 10)
      {
       while(1)
      {RW = digitalRead(rightW);
        MW = digitalRead(midW);
        LW = digitalRead(leftW);
        if(!(track(LW,MW,RW,0,0,0))){leftc(220,220); goto Normal ;}
        else{if (dist3.ping_cm() < 9) {left(220,0);Serial.print("cond leftt");Serial.println(dist3.ping_cm());}
       if ((dist3.ping_cm() >= 9) || (dist3.ping_cm() <= 12)) {forward (130);Serial.print("cond forward");Serial.println(dist3.ping_cm());}
        if (dist3.ping_cm() >12) {right(220,0);Serial.print("cond right");Serial.println(dist3.ping_cm());}
   
       }}
      }
      
RW = digitalRead(rightW);
MW = digitalRead(midW);
LW = digitalRead(leftW);
    
    } 
  }
    
  

}              
}              

       
}

if (b)
{
  if (dist1.ping_cm()!= 0)
{
  backward(150);
  Serial.println("bluetooth ultra");
  delay(200);
}
if (dist1.ping_cm()== 0)
{
if(in_byte == '3')
 {
    right(250,0); Serial.println("bluetooth right");

 }
else if(in_byte == '1')
{
  forward (250);Serial.println("bluetooth forward");
  }
 else if(in_byte == '2')
 {
    backward(250);Serial.println("bluetooth backwarrd");

 }
 else if(in_byte == '4')
 {
    left(250,0);Serial.println("bluetooth left");

 }
 else if(in_byte == '0')
 {
  brake();
 }
}
  }
  }