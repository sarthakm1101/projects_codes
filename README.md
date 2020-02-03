#include<Ultrasonic.h>

Ultrasonic ultrasonic(5,6);

Ultrasonic ultrasonic2(11,10);


unsigned long currentMillis =0,t1,t2;

int d1,d2,c;

boolean ex=0,en=0,in;

void setup() 
{
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  Serial.begin(9600);
  delay(5000);
  Serial.println("entered in room");
  Serial.println(ultrasonic.distanceRead());
  Serial.println(ultrasonic2.distanceRead());
}

void loop() 
{
  currentMillis=(millis())%100;
  d1=ultrasonic.distanceRead();
  d2=ultrasonic2.distanceRead();

  if(currentMillis==0)
  {
    Serial.print("Count is :");
    Serial.println(c);
    Serial.println(d1);
    Serial.println(d2);
  }


  if(d1<=15 && d2<=15)
  {
    c=c;
  }
  else if(d1<=15)
  {
    if(en==1)
    {
      c++;
      en=0;
    }
    else ex=1;
  }

  else if(d2<=15)
  {
    if(ex==1)
    {
      c--;
      ex=0;
    }
    else en=0;
  }

}
