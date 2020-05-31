//#include <Servo.h> 
#include <LiquidCrystal.h> //1602
//1602Arduino84
//LiquidCrystal lcd(12,11,10,9,8,7,6,5,4,3,2);   //8
LiquidCrystal lcd(13,12,7,6,5,4,3); //4 P13--LCD 4  P12--LCD 5  
              //P7--LCD 6   P6--LCD 11  P5--LCD 12  P4--LCD 13  P3--LCD 14  

int Echo = A1;  // Echo(P2.0)
int Trig =A0;  //  Trig (P2.1)

int Front_Distance = 0;//
int Left_Distance = 0;
int Right_Distance = 0;

int Left_motor_go=8;     //(IN1)
int Left_motor_back=9;     //(IN2)

int Right_motor_go=10;    // (IN3)
int Right_motor_back=11;    // (IN4)

int key=A2;// A2 
int beep=A3;// A3 

//const int SensorRight = 3;     //(P3.2 OUT1)
//const int SensorLeft = 4;       //(P3.3 OUT2)

//const int SensorRight_2 = 6;    //(P3.5 OUT4)
//const int SensorLeft_2 = 5;     //(P3.4 OUT3)

//int SL;    //
//int SR;    //
//int SL_2;    //
//int SR_2;    //

int servopin=2;//2
int myangle;//
int pulsewidth;//
int val;

void setup()
{
  Serial.begin(9600);     // 
  //IO
  pinMode(Left_motor_go,OUTPUT); // PIN 8 (PWM)
  pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 10 (PWM) 
  pinMode(Right_motor_back,OUTPUT);// PIN 11 (PWM)
  pinMode(key,INPUT);//
  pinMode(beep,OUTPUT);
  // pinMode(SensorRight, INPUT); //
  // pinMode(SensorLeft, INPUT); //
  //pinMode(SensorRight_2, INPUT); //
  //pinMode(SensorLeft_2, INPUT); //
  //
  pinMode(Echo, INPUT);    // 
  pinMode(Trig, OUTPUT);   // 
  lcd.begin(16,2);      //1602                       
  //1602216  
  pinMode(servopin,OUTPUT);//
}
//================================================
//void run(int time)     // 
void run()     // 
{
  digitalWrite(Right_motor_go,HIGH);  // 
  digitalWrite(Right_motor_back,LOW);     
  analogWrite(Right_motor_go,165);//PWM0~255
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,LOW);  // 
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0);//PWM0~255
  analogWrite(Left_motor_back,160);
  //delay(time * 100);   //  
}

void brake(int time)  //
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
  delay(time * 100);//  
}

void left(int time)         //()
//void left()         //()
{
  digitalWrite(Right_motor_go,HIGH);  // 
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,180); 
  analogWrite(Right_motor_back,0);//PWM0~255
  digitalWrite(Left_motor_go,LOW);   //
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,0);//PWM0~255
  delay(time * 100);  //  
}

void spin_left(int time)         //()
{
  digitalWrite(Right_motor_go,HIGH);  // 
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,200); 
  analogWrite(Right_motor_back,0);//PWM0~255
  digitalWrite(Left_motor_go,HIGH);   //
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,200); 
  analogWrite(Left_motor_back,0);//PWM0~255
  delay(time * 100);  //   
}

void right(int time)
//void right()        //()
{
  digitalWrite(Right_motor_go,LOW);   //
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,0);//PWM0~255
  digitalWrite(Left_motor_go,LOW);//
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,200);//PWM0~255
  delay(time * 100);  //  
}

void spin_right(int time)        //()
{
   digitalWrite(Right_motor_go,LOW);   //
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,150);//PWM0~255
  digitalWrite(Left_motor_go,LOW);//
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,150);//PWM0~255
  delay(time * 100);  //   
}

void back(int time)          //
{
   digitalWrite(Right_motor_go,LOW);  //
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,150);//PWM0~255
  digitalWrite(Left_motor_go,HIGH);  //
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,150);
  analogWrite(Left_motor_back,0);//PWM0~255
  delay(time * 100);     //  
}
//==========================================================

void keysacn()//
{
  int val;
  val=digitalRead(key);//7 val
  while(!digitalRead(key))//
  {
    val=digitalRead(key);//
  }
  while(digitalRead(key))//
  {
    delay(10);  //10ms
    val=digitalRead(key);//7 val
    if(val==HIGH)  //
    {
      digitalWrite(beep,HIGH);    //
      while(!digitalRead(key))  //
        digitalWrite(beep,LOW);   //
    }
    else
      digitalWrite(beep,LOW);          //
  }
}

float Distance_test()   //  
{
  digitalWrite(Trig, LOW);   // 2s
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  // 10s10s
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    // 
  float Fdistance = pulseIn(Echo, HIGH);  // ()
  Fdistance= Fdistance/58;       //58  Y=X*344/2
  // X= 2*Y/344 ==X=0.0058*Y ===/58
  //Serial.print("Distance:");      //
  //Serial.println(Fdistance);         //
  //Distance = Fdistance;
  return Fdistance;
}  

void Distance_display(int Distance)//
{
  if((2<Distance)&(Distance<400))
  {
    lcd.home();        //   
    lcd.print("    Distance: ");       //
    lcd.setCursor(6,2);   //26
    lcd.print(Distance);       //
    lcd.print("cm");          //
  }
  else
  {
    lcd.home();        //  
    lcd.print("!!! Out of range");       //
  }
  delay(250);
  lcd.clear();
}

void servopulse(int servopin,int myangle)/*PWM0.5MS2.5MS 1.5MS 20MS*/ 
{
  pulsewidth=(myangle*11)+500;//500-2480  myangle0-180  180*11+50=2480  11901.5MS
  digitalWrite(servopin,HIGH);//                                      90*11+50=1490uS  1.5ms
  delayMicroseconds(pulsewidth);//  
  digitalWrite(servopin,LOW);//
 // delay(20-pulsewidth/1000);//  ms
  delay(20-(pulsewidth*0.001));//  ms
}

void front_detection()
{
  //
  for(int i=0;i<=5;i++) //PWM
  {
    servopulse(servopin,90);//PWM
  }
  Front_Distance = Distance_test();
  //Serial.print("Front_Distance:");      //
 // Serial.println(Front_Distance);         //
 //Distance_display(Front_Distance);
}

void left_detection()
{
  for(int i=0;i<=15;i++) //PWM
  {
    servopulse(servopin,175);//PWM
  }
  Left_Distance = Distance_test();
  //Serial.print("Left_Distance:");      //
  //Serial.println(Left_Distance);         //
}

void right_detection()
{
  for(int i=0;i<=15;i++) //PWM
  {
    servopulse(servopin,5);//PWM
  }
  Right_Distance = Distance_test();
  //Serial.print("Right_Distance:");      //
  //Serial.println(Right_Distance);         //
}
//===========================================================
void loop()
{
  keysacn();     //
  while(1)
  {
    front_detection();//
    if(Front_Distance < 30)//
    {
      brake(2);//
      back(2);//
      brake(2);//
      left_detection();//
      Distance_display(Left_Distance);//
      right_detection();//
      Distance_display(Right_Distance);//
      if((Left_Distance < 30 ) &&( Right_Distance < 30 ))//
        spin_left(0.7);//
      else if(Left_Distance > Right_Distance)//
      {      
        left(3);//
        brake(1);//
      }
      else//
      {
        right(3);//
        brake(1);//
      }
    }
    else
    {
      run(); //     
    }
  } 
}
