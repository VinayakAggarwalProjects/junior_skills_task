/*
 * ---Notes for user---
 * Written by Vinayak Aggarwal
 * to shorten up the program High and Low can be written as 1 and 0 respectively 
 * the speed can be increased but to accomplish every task with accuracy the speed is kept low
 * don't worry if the speed is having variation , the robot is programed to variate the speed whenever necessary 
 * for accuracy.
 * at some places combinations recived from ir array is been used for better understanding  like - 11011,11111 and so on
 */
int inputpins[]={A0,A1,A2,A3,A4};// list of input pins
int outputpins[]={4,5,6,7,9,10};// list of output pins
int sen1;//stating the variables for ir array
int sen2;
int sen3;
int sen4;
int sen5;
void sen(){//function to get the ir array reading
  sen1=digitalRead(A0);//extreme left
  sen2=digitalRead(A1);//left
  sen3=digitalRead(A2);//center
  sen4=digitalRead(A3);//right
  sen5=digitalRead(A4);//extreme right
}
void runs(char movement){//function for directing the robot
 if(movement=='f'){//configuration to run it in forward direction
    digitalWrite(4,1);
    digitalWrite(5,0);
    digitalWrite(6,1);
    digitalWrite(7,0);
 }
 else if(movement=='b'){//config. to run it backward
    digitalWrite(4,0);
    digitalWrite(5,1);
    digitalWrite(6,0);
    digitalWrite(7,1);
 }
 else if(movement=='r'){// for right
    digitalWrite(4,1);
    digitalWrite(5,0);
    digitalWrite(6,0);
    digitalWrite(7,0);
    sen();//for updating the sensors as early as posible for accuracy
 }
 else if(movement=='l'){// for left
    digitalWrite(4,0);
    digitalWrite(5,0);
    digitalWrite(6,1);
    digitalWrite(7,0);
    sen();//for updating the sensors as early as posible
 }
}
void sp(int spa,int spb){// setting up the speed for thew two motors
  analogWrite(9,spa);
  analogWrite(10,spb);
}
void defsp(){//setting the default speed , redused when it senses some thing for accuracy
  sp(130,130);
}
void setup() {
  //Serial.begin(9600);// for debuging
  for(int x=0;x<(sizeof(inputpins)/sizeof(inputpins[1]));x++){//short code for setting up pins as input and output
    //technical details used(same for the output pins.
    //(sizeof gives the number of bytes stored that's why it needs to be divided by the bytes stored in the first
    //item , pin numbers are stored in two bytes .
    pinMode(inputpins[x],INPUT);
   // Serial.println(inputpins[x]);// for debuging
  }
  for(int y=0;y<(sizeof(outputpins)/sizeof(outputpins[1]));y++){
    pinMode(outputpins[y],OUTPUT);
   // Serial.println(outputpins[y]);//for debugind
  }
  delay(3000); // delay for recording purpose not necessary
  defsp();
  runs('f');//the speed makes it so accurate that it even detects the start box line so making it move fotward for a little time is stopping it to detect the start box line .
  delay(200);
}

void loop() {
  sen();// updating values ofd ir array
  defsp();// setting the default speed
  if(sen1==1&&sen2==1&&sen3==0&&sen4==1&&sen5==1){// move forward when the ir sensor is 11011
    runs('f');
  }
  else if(sen1==1&&sen2==0&&sen3==0&&sen4==1&&sen5==1||sen1==0&&sen2==0&&sen3==0&&sen4==1&&sen5==1||sen1==1&&sen2==0&&sen3==1&&sen4==1&&sen5==1){
    // if the ir gives 10011,00011,10111 
    //the robot moves towards left until the ir combination is 11011 ,00000
    while ((sen1==1&&sen2==1&&sen3==0&&sen4==1&&sen5==1||sen1==0&&sen2==0&&sen3==0&&sen4==0&&sen5==0)==false){
    sp(100,100);
    runs('l');
    sen();
  }}
  else if (sen1==1&&sen2==1&&sen3==0&&sen4==0&&sen5==1||sen1==1&&sen2==1&&sen3==0&&sen4==0&&sen5==0||sen1==1&&sen2==1&&sen3==1&&sen4==0&&sen5==1){
    // if the ir gives 11001,11000,11101
    //the robot moves towards right until the ir combination is 11011 ,00000
    while ((sen1==1&&sen2==1&&sen3==0&&sen4==1&&sen5==1||sen1==0&&sen2==0&&sen3==0&&sen4==0&&sen5==0)==false){
    sp(100,100);
    runs('r');
    sen();
  }}
  else if(sen1==0&&sen2==0&&sen3==0&&sen4==0&&sen5==0){ //when ir sensor is 00000 it runs forward for sometime then checks 
    //if any sensor detects white if yes it comes back and move towards left until ir reading is 11011 if no 
    //then it keeps moving forward and if it derails from that wide black patch it adjust itself to be on the black patch.
    runs('f');
    delay(100);
    sen();
    if(sen2==1||sen3==1||sen4==1){
     while((sen1==0&&sen2==0&&sen3==0&&sen4==0&&sen5==0)==false){
      runs('b');
      sp(100,100);
      sen();
     }
     while((sen1==1&&sen2==1&&sen3==0&&sen4==1&&sen5==1)==false){
      runs('l');
      sen();
     }
    }
    else{
      while((sen1==1||sen2==1||sen4==1||sen5==1)==false){
      sen();
      runs('f');
      if(sen1==1){
        runs('r');
      }
      else if(sen5==1){
        runs('l');
      }
    }  
    }
  }
  else if(sen1==1&&sen2==1&&sen3==1&&sen4==1&&sen5==1){// this is for the dotted path and the two black lines 
    //which are parellel and wide than the array  . so when all ir are 11111 then it runs forward when all are 11111 if 
    // the change is detect as 01111 then the robot turns right and if it is 11110 then it turns towards right 
    // the dotted line left and right system is defined before with the line following one only to increase efficency and to reduce the code.
    while(sen1==1&&sen2==1&&sen3==1&&sen4==1&&sen5==1){
      sp(70,70);
      runs('f');
      sen();
    }
    sen();
  }
  else if(sen1==0&&sen2==1&&sen3==1&&sen4==1&&sen5==1){
    while(sen1==0&&sen2==1&&sen3==1&&sen4==1&&sen5==1){
    sp(70,70);
    runs('r');
  }}
  else if(sen1==1&&sen2==1&&sen3==1&&sen4==1&&sen5==0){
    while(sen1==1&&sen2==1&&sen3==1&&sen4==1&&sen5==0){
    sp(70,70);
    runs('l');
  }}
else if(sen1==0 && sen5==0&&(sen3==1||sen4==1||sen2==1)){ // if the ir is 01100 or 00110 or 00100 it means robot reached at end and it stops.
  sp(0,0);
}
}
// code ends
