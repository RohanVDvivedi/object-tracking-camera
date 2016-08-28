#include <Servo.h>
Servo horizontal;
Servo vertical;
void setup()
{
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  horizontal.attach(10); // for me the horizontal servo has been attched to pin 10
  vertical.attach(9); // the servo for vertical motion is attched to pin 9
}

void send_serial_long(unsigned long i) // function for unsigned integral communication for uC  
{
       
        unsigned char uc[4];
        uc[3]=i;
        i=i>>8;
        uc[2]=i;
        i=i>>8;
        uc[1]=i;
        i=i>>8;
        uc[0]=i;
        Serial.write(uc,4);
  }
        
        


unsigned long recieve_serial_long() // function for unsigned integral receeving 
{
  unsigned long i=0;
  unsigned char uc;
  while(1)
  {
    if(Serial.available()==4)
    {
      uc=Serial.read();
      i=i+((unsigned long)uc)<<24;
      uc=Serial.read();
      i=i+(((unsigned long)uc)<<16);
      uc=Serial.read();
      i=i+(((unsigned long)uc)<<8);
      uc=Serial.read();
      i=i+(unsigned long)uc;
     
      
      break;
    }
  }
  return i;
}

int h=90;
int v=90; // this are the setup angles when the camera is made to 
          //look staright and the servos are set initial to 90 degrees 
          //with mechanical adjustments

unsigned long go; // global variable to store the received command

void loop()
{
  go=recieve_serial_long(); // getting data from the computer
  
  /*
    go command will move the camera 
    go is going to be
    120,130 - left or right
    ,140,150 - top or bottom
    comaparing this values or more correctly now will give you responses
    here the least resolution the camrera cam move is 1 degree you may incease or decrease by
    improving the communication protocol in Serial interface
    
    servos i used faced strong colissions on reaching 0 and 180 degrees 
    so i have used the deviation fron 5 to 175 degrees
  */
  
  
  if(go==120 && h<175) 
  {
    h=h+1;
    horizontal.write(h);
    send_serial_long(125);
    
    digitalWrite(13,HIGH);
  }
  else if(go==130 && h>5)
  {
    h=h-1;
    horizontal.write(h);
    delay(7);
    send_serial_long(135);
    
    digitalWrite(13,HIGH);
  }
  else if(go==140 && v<175)
  {
    v=v+1;
    vertical.write(v);
    delay(7);
    send_serial_long(145);
    
    digitalWrite(13,LOW);
  }
  else if(go==150 && v>5)
  {
    v=v-1;
    vertical.write(v);
    delay(7);
    send_serial_long(155);
    
    digitalWrite(13,LOW);
  }
  delay(5);
  
  // this delay will ensure the proper movement of servos
  
}



