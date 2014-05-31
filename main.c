#include "C:\Users\xb\Desktop\Hole_Test_P'T\main.h"

#define buttonBlue input(PIN_D0)
#define buttonWhite input(PIN_D1)
#define buttonBlack input(PIN_D2)
#define buttonGreen input(PIN_D3)

//sensor for catch dish
#define senLeftUP input(PIN_E2)
#define senLeftDown input(PIN_E3)
#define senRightUp input(PIN_E4)
#define senRightDown input(PIN_E5)

//keeper for catch dish (pneumatic)
#define keeperRight PIN_E0
#define keeperLeft PIN_E1

///48 mil sensors form outside

int cntStep = 0;
int toggle_feed = 0;
int state = 0;
int state1 = 0;
int state2 = 0;
int state3 = 0;
int stateL = 0;
int stateR = 0;
int angleLeft = 512;
int angleRight = 512;
unsigned int err = 0;
/*void servoTest(int16 pos,int16 speedServo){ //ID 2 //more cw , less ccw   

   unsigned char chksum;
   chksum=0x2c; 
   chksum+=pos; 
   chksum+=pos>>8;
   chksum+=speedServo;
   chksum+=speedServo>>8;
   chksum=~chksum; 
   fprintf(servo,"%c%c%c%c%c%c%c%c%c%c%c\r\n",0xff,0xff,0x04,0x07,0x03,0x1e,pos,pos>>8, 
      speedServo,speedServo>>8,chksum); 
   //fprintf(servo,"%c%c%c%c%c%c%c%c%c%c%c\r\n",0xff,0xff,0x02,0x07,0x03,0x1e,pos,pos>>8, 
     // 0x00,0x02,chksum); 
   
   //delay_ms(10);
} */

int indexRD2=0;
char buff[100];
int isRespond=0;
char cRespond[100];
int iRespond;
int ii=0;
void autokeep();
#INT_RDA2
void _rda2_isr(){
   buff[indexRD2]=fgetc(servo);
   if(indexRD2>2){
      if((buff[indexRD2-1]==0xff)&&(buff[indexRD2]==0xff)){
        
         for(ii=0;ii<=indexRD2;ii++){
            cRespond[ii]=buff[ii];
         }
         output_toggle(PIN_H0);
         iRespond=indexRD2;
         if(isRespond==0){
            indexRD2=0;
         }
         isRespond=1;
         
      }
      else if(indexRD2>90){
         indexRD2=0;
      }
      else{
         indexRD2++;
      }
   }
   else{
      indexRD2++;
   }
}
#INT_TIMER1
void timer(){
 //  autokeep();
}
void autokeep(){
   if(senLeftDown&&stateL==0){
      output_high(keeperLeft);
      stateL=1;
   }
   if(senRightUp&&stateR==0){
      output_high(keeperRight);
      stateR=1;
   }
   if(senLeftUp&&stateL==1){
      output_high(keeperLeft);
      stateL=0;
   }
   if(senRightDown&&stateR==1){
      output_high(keeperRight);
      stateR=0;
   }
  
   
}
void servoRight(int16 pos,int16 speedServo){ //ID 2 //more cw , less ccw   

   unsigned char chksum;
   chksum=0x2a; 
   chksum+=pos; 
   chksum+=pos>>8;
   chksum+=speedServo;
   chksum+=speedServo>>8;
   chksum=~chksum; 
   fprintf(servo,"%c%c%c%c%c%c%c%c%c%c%c\r\n",0xff,0xff,0x02,0x07,0x03,0x1e,pos,pos>>8, 
      speedServo,speedServo>>8,chksum); 
   delay_ms(20);
} 
void servoLeft(int16 pos,int16 speedServo){ //ID 4 //more cw ,less ,ccw 
   unsigned char chksum;
   chksum=0x2c; 
   chksum+=pos; 
   chksum+=pos>>8;
   chksum+=speedServo;
   chksum+=speedServo>>8;
   chksum=~chksum; 
   fprintf(servo,"%c%c%c%c%c%c%c%c%c%c%c\r\n",0xff,0xff,0x04,0x07,0x03,0x1e,pos,pos>>8, 
      speedServo,speedServo>>8,chksum); 
   delay_ms(20); 
} 
void testSwitch_Sen()
{
   fprintf(servo,"%d,%d,%d,%d\n\r",buttonBlue,buttonWhite,buttonBlack,buttonGreen);
   fprintf(servo,"%d,%d,%d,%d\n\r",senLeftUp,senLeftDown,senRightUp,senRightDown);
}

void testAngle()
{
   if(buttonBlue==0){
      angleLeft++;
   }
   else if(buttonWhite==0){
      angleLeft--;
   }
   
   if(buttonBlack==0)
   {
      angleRight++;
   }
   else if(buttonGreen==0)
   {
      angleRight--;
   }
   
   if(angleRight<=0){ angleRight = 0;}
   else if(angleRight>=1023){angleLeft = 1023;}
   
   if(angleLeft<=0){ angleRight = 0;}
   else if(angleLeft>=1023){angleLeft = 1023;}

  
}

void hole_move_blue()
{
   ////hole1 to hole2
   output_low(keeperLeft);
   output_low(keeperRight);
   servoRight(512,400);
   delay_ms(100);
   servoLeft(850,700);
   delay_ms(1000);
   output_high(keeperRight);
   //delay_ms(1500);
   servoRight(200,350);
   while(!senLeftUp);
   output_high(keeperLeft);
   ////hole2 to hole3
   delay_ms(200);
   output_low(keeperRight);
   delay_ms(200);
   servoRight(725,500);
   delay_ms(100);
   servoLeft(240,500);
   while(!senRightUp);
   output_high(keeperRight);
   ////hole3 to hole 4
   delay_ms(200);
   output_low(keeperLeft);
   delay_ms(200);
   servoLeft(650,500);
   delay_ms(200);
   servoRight(130,500);
   while(!senLeftDown);
   //delay_ms(1100);
   output_high(keeperLeft);
   delay_ms(200);
   /*
   //finish//
   output_low(keeperRight);
   delay_ms(300);
   servoRight(512,200);
   delay_ms(100);
   servoLeft(512,200);
*/   
}
/*
void hole_move_red()
{
   ////hole1 to hole2
   output_low(keeperLeft);
   output_low(keeperRight);
   servoLeft(512,300);
   delay_ms(100);
   servoRight(200,400);
   delay_ms(1000);
   output_high(keeperLeft);
   //delay_ms(1500);
   servoLeft(700,400);
   while(!senRightUp);
   output_high(keeperRight);
   ////hole2 to hole3
   delay_ms(200);
   output_low(keeperLeft);
   delay_ms(200);
   servoLeft(315,500);
   delay_ms(100);
   servoRight(690,500);
   while(!senLeftUp);
   output_high(keeperLeft);
   ////hole3 to hole 4
   delay_ms(200);
   output_low(keeperRight);
   delay_ms(200);
   servoRight(330,400);
   delay_ms(200);
   servoLeft(800,400);
   while(!senRightDown);
   //delay_ms(1100);
   output_high(keeperRight);
   delay_ms(200);
   //finish//
   //output_low(keeperLeft);
   //delay_ms(300);
   //servoLeft(512,500);
   //delay_ms(100);
   //servoRight(512,500);
   
}*/

void hole_move_red()
{
   ////hole1 to hole2
   output_low(keeperLeft);
   output_low(keeperRight);
   servoLeft(512,400);
   delay_ms(100);
   servoRight(200,500);
   delay_ms(1000);
   output_high(keeperLeft);
   //delay_ms(1500);
   servoLeft(700,450);
   while(!senRightUp);
   output_high(keeperRight);
   ////hole2 to hole3
   delay_ms(200);
   output_low(keeperLeft);
   delay_ms(200);
   servoLeft(315,700);
   delay_ms(100);
   servoRight(600,1000);
   delay_ms(500);
   servoRight(850,700);
   while(!senLeftUp);
   output_high(keeperLeft);
   ////hole3 to hole 4
   delay_ms(200);
   output_low(keeperRight);
   delay_ms(200);
   servoRight(390,700);
   delay_ms(200);
   servoLeft(600,1000);
   delay_ms(500);
   servoLeft(850,700);
   while(!senRightDown);
   //delay_ms(1100);
   output_high(keeperRight);
   delay_ms(200);
   //finish//
   output_low(keeperLeft);
   delay_ms(300);
   servoLeft(512,600);
   delay_ms(100);
   servoRight(512,600);
}
void home_test_seesaw()//L=69 for home - seesaw=940  , R=975 for home - seesaw=105
{
   output_low(keeperRight);
   output_low(keeperLeft);
   servoLeft(512,300);
   delay_ms(100);
   servoRight(512,300);
}
void enableTorque(int id){
   
   unsigned int chk=id+5+3+ 0x18 +1+1 ;
   chk=~chk;
   fputc(0xff,servo);
   fputc(0xff,servo);
   fputc(id,servo);
   fputc(0x05,servo);
   fputc(0x03,servo);
   fputc(0x18,servo);
   fputc(0x01,servo);
   fputc(0x01,servo);
   fputc(chk,servo);
   
   
}
void seesaw()
{
   while(1){
   servoLeft(940,300);
   delay_ms(200);
   servoRight(105,300);
   delay_ms(200);
   if(isRespond==1){
      int i;
      for(i=0;i<=iRespond*2;i++){
         fputc(cRespond[i],PIC);
         
      }
      if(cRespond[2]==0x20){
         fprintf(PIC,"OVERLOAD");
         enableTorque(4);
         enableTorque(2);
      }
      isRespond=0;
   }
   //fputc(0xfb,PIC);
   //fputc(0xfa,PIC);
   }
}
void home()
{
   servoLeft(69,300);
   delay_ms(50);
   servoRight(975,300);
}
void main() 
{
   init();
  // while(true){fprintf(PIC,"wwww");}
 /*
   while(true){
      servoLeft(512,100);      
      servoRight(512,100);
      delay_ms(1000);
      servoLeft(300,100);
      servoRight(700,100);
      delay_ms(1000);
   }
   */
   while(true){
   
  
   if(buttonBlue==0&&state==0)
   {
      state=1;
   }
   else if(buttonBlue==1&&state==1)
   {
      home_test_seesaw();
      state=0;
   }
   if(buttonWhite==0&&state1==0)
   {
      state1=1;
   }
   else if(buttonWhite==1&&state1==1)
   {
      hole_move_red();
      state1=0;
   }
   if(buttonBlack==0&&state2==0)
   {
      state2=1;
   }
   else if(buttonBlack==1&&state2==1)
   {
      //seesaw();
      hole_move_blue();
      state2=0;
   }
   if(buttonGreen==0&&state3==0)
   {
      state3=1;
   }
   else if(buttonGreen==1&&state3==1)
   {
      home();
      state3=0;
   }
   //firtTosecond_hole();
      //output_low(keeperLeft);
      //testSwitch();
    // fprintf(servo,"www");
     

   }
}
