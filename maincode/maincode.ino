#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <DS1302.h>
#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#define mt1 12
#define mt2 13
#define mt3 2
#define mt4 3

const int buzzer = 4;
int menuitem=1;
int submenuitem1=1;
int submenuitem2=1;
int submenuitem3=1;
int submenuitem4=1;
int page=1;
int num1=1;
int num2=1;
int num3=1;
int num4=1;
int stime1=1;
int stime2=1;
int stime3=1; 
int stime4=1;
int h1=10; int m1=30; int hk1; int mk1;
int h2=10; int m2=30; int hk2; int mk2;
int h3=10; int m3=30; int hk3; int mk3;
int h4=10; int m4=30; int hk4; int mk4;
int nowhour; int nowmin;

volatile boolean down = false;
volatile boolean up = false;
volatile boolean middle = false;

int downButtonState = 0;
int upButtonState = 0;  
int selectButtonState = 0;          
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;

void setTime();
void printTime();
void drawMenu();
void checkIfDownButtonIsPressed();
void checkIfUpButtonIsPressed();
void checkIfSelectButtonIsPressed();
void alarm();


LiquidCrystal_I2C lcd(0x3F,20,4);

const int kCePin   = 5;  //RST
const int kIoPin   = 6;  //DAT
const int kSclkPin = 7;  //CLK

// Create a DS1302 object.
DS1302 rtc(kCePin, kIoPin, kSclkPin);

void setup()
{
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(mt1,OUTPUT);
  pinMode(mt2,OUTPUT);
  pinMode(mt3,OUTPUT);
  pinMode(mt4,OUTPUT);
  
  Serial.begin(9600);
  
  setTime(); 
  lcd.begin();
  lcd.clear();
  lcd.display();
}
void loop()
{
  drawMenu();
  
  downButtonState = digitalRead(8);
  selectButtonState = digitalRead(9);
  upButtonState =   digitalRead(10);
 
  checkIfDownButtonIsPressed();
  checkIfUpButtonIsPressed();
  checkIfSelectButtonIsPressed();

 if(hk1==nowhour && mk1==nowmin)
  {
    alarm();
    digitalWrite(mt1,HIGH);
    delay(570*num1);
  }
  if(hk2==nowhour && mk2==nowmin)
  {
    alarm();
    digitalWrite(mt2,HIGH);
    delay(570*num2);
  }
  if(hk3==nowhour && mk3==nowmin)
  {
    alarm();
    digitalWrite(mt3,HIGH);
    delay(570*num3);
  }
  if(hk4==nowhour && mk4==nowmin)
  {
    alarm();
    digitalWrite(mt4,HIGH);
    delay(570*num4);
  }

  if (up && (page == 1) ) {
    up = false;
    menuitem--;
    if (menuitem==0)
    {
      menuitem=4;
    }      
    lcd.clear();
  }


  if (down && (page == 1)) {
    down = false;
    menuitem++;
    if (menuitem==5) 
    {
      menuitem=1;
    }   
    lcd.clear();  
  }

  if (up && (page == 2) ) {
    up = false;
    submenuitem1--;
    if (submenuitem1==0)
    {
      submenuitem1=3;
    }      
    lcd.clear();
  }


  if (down && (page == 2)) {
    down = false;
    submenuitem1++;
    if (submenuitem1==4) 
    {
      submenuitem1=1;
    }   
    lcd.clear();  
  }

  if (up && (page == 3) ) {
    up = false;
    submenuitem2--;
    if (submenuitem2==0)
    {
      submenuitem2=3;
    }      
    lcd.clear();
  }


  if (down && (page == 3)) {
    down = false;
    submenuitem2++;
    if (submenuitem2==4) 
    {
      submenuitem2=1;
    }   
    lcd.clear();  
  }

if (up && (page == 4) ) {
    up = false;
    submenuitem3--;
    if (submenuitem3==0)
    {
      submenuitem3=3;
    }      
    lcd.clear();
  }


  if (down && (page == 4)) {
    down = false;
    submenuitem3++;
    if (submenuitem3==4) 
    {
      submenuitem3=1;
    }   
    lcd.clear();  
  }

if (up && (page == 5) ) {
    up = false;
    submenuitem4--;
    if (submenuitem4==0)
    {
      submenuitem4=3;
    }      
    lcd.clear();
  }


 if (down && (page == 5)) {
    down = false;
    submenuitem4++;
    if (submenuitem4==4) 
    {
      submenuitem4=1;
    }   
    lcd.clear();  
  }

if (up && (page == 22) ) {
    up = false;
    stime1--;
    if (stime1==0)
    {
      stime1=3;
    }      
    lcd.clear();
  }


  if (down && (page == 22)) {
    down = false;
    stime1++;
    if (stime1==4) 
    {
      stime1=1;
    }   
    lcd.clear();  
  }

  if (up && (page == 32) ) {
    up = false;
    stime2--;
    if (stime2==0)
    {
      stime2=3;
    }      
    lcd.clear();
  }


  if (down && (page == 32)) {
    down = false;
    stime2++;
    if (stime2==4) 
    {
      stime2=1;
    }   
    lcd.clear();  
  }

  if (up && (page == 42) ) {
    up = false;
    stime3--;
    if (stime3==0)
    {
      stime3=3;
    }      
    lcd.clear();
  }


  if (down && (page == 42)) {
    down = false;
    stime3++;
    if (stime3==4) 
    {
      stime3=1;
    }   
    lcd.clear();  
  }

  if (up && (page == 52) ) {
    up = false;
    stime4--;
    if (stime4==0)
    {
      stime4=3;
    }      
    lcd.clear();
  }


  if (down && (page == 52)) {
    down = false;
    stime4++;
    if (stime4==4) 
    {
      stime4=1;
    }   
    lcd.clear();  
  }
 
  //first
  if (up && (page==21)) {
    up = false;
    lcd.clear();
    num1-=1;
    if(num1==-1)
    {
      num1=6;
    } 
    }
    if (down && (page==21)) {
    down = false;
    lcd.clear();
    num1+=1;
    if(num1==7)
    {
      num1=0;
    }
    }
  //second
      if (up && (page==31)) {
    up = false;
    lcd.clear();
    num2-=1;
    if(num2==-1)
    {
      num2=6;
    } 
    }
   if (down && (page==31)) {
    down = false;
    lcd.clear();
    num2+=1;
    if(num2==7)
    {
      num2=0;
    }
   }
   //third
     if (up && (page==41)) {
    up = false;
    lcd.clear();
    num3-=1;
    if(num3==-1)
    {
      num3=6;
    } 
    }
    if (down && (page==41)) {
    down = false;
    lcd.clear();
    num3+=1;
    if(num3==7)
    {
      num3=0;
    }
    }
  //forth
    if (up && (page==51)) {
    up = false;
    lcd.clear();
    num4-=1;
    if(num4==-1)
    {
      num4=6;
    } 
    }
    if (down && (page==51)) {
    down = false;
    lcd.clear();
    num4+=1;
    if(num4==7)
    {
      num4=0;
    }
    }

    if (up && (page==221)) {
    up = false;
    lcd.clear();
    h1-=1;
    if(h1==-1)
    {
      h1=23;
    } 
    }
    if (down && (page==221)) {
    down = false;
    lcd.clear();
    h1+=1;
    if(h1==24)
    {
      h1=0;
    }
    }

    if (up && (page==222)) {
    up = false;
    lcd.clear();
    m1-=1;
    if(m1==-1)
    {
      m1=59;
    } 
    }
    if (down && (page==222)) {
    down = false;
    lcd.clear();
    m1+=1;
    if(m1==60)
    {
      m1=0;
    }
    }


    if (up && (page==321)) {
    up = false;
    lcd.clear();
    h2-=1;
    if(h2==-1)
    {
      h2=23;
    } 
    }
    if (down && (page==321)) {
    down = false;
    lcd.clear();
    h2+=1;
    if(h2==24)
    {
      h2=0;
    }
    }

    if (up && (page==322)) {
    up = false;
    lcd.clear();
    m2-=1;
    if(m2==-1)
    {
      m2=59;
    } 
    }
    if (down && (page==322)) {
    down = false;
    lcd.clear();
    m2+=1;
    if(m2==60)
    {
      m2=0;
    }
    }

 if (up && (page==421)) {
    up = false;
    lcd.clear();
    h3-=1;
    if(h3==-1)
    {
      h3=23;
    } 
    }
    if (down && (page==421)) {
    down = false;
    lcd.clear();
    h3+=1;
    if(h3==24)
    {
      h3=0;
    }
    }

    if (up && (page==422)) {
    up = false;
    lcd.clear();
    m3-=1;
    if(m3==-1)
    {
      m3=59;
    } 
    }
    if (down && (page==422)) {
    down = false;
    lcd.clear();
    m3+=1;
    if(m3==60)
    {
      m3=0;
    }
    }

    if (up && (page==521)) {
    up = false;
    lcd.clear();
    h4-=1;
    if(h4==-1)
    {
      h4=23;
    } 
    }
    if (down && (page==521)) {
    down = false;
    lcd.clear();
    h4+=1;
    if(h4==24)
    {
      h4=0;
    }
    }

    if (up && (page==522)) {
    up = false;
    lcd.clear();
    m4-=1;
    if(m4==-1)
    {
      m4=59;
    } 
    }
    if (down && (page==522)) {
    down = false;
    lcd.clear();
    m4+=1;
    if(m4==60)
    {
      m4=0;
    }
    }
  
  if (middle) {
    middle = false;
    
    if (page == 1 && menuitem==2) 
    {
      lcd.clear();
      page=3;
    }

    else if(page == 1 && menuitem ==3)
    {
      lcd.clear();
      page=4;
    }
    else if(page == 1 && menuitem ==4)
    {
      lcd.clear();
      page=5;
    }

     else if (page == 1 && menuitem==1) {
     lcd.clear();
      page=2;
     }
     else if (page == 2 && submenuitem1 == 1) {
      lcd.clear();
      page=1;
     }
     else if (page == 3 && submenuitem2 == 1) {
      lcd.clear();
      page=1;
     }
     else if (page == 4 && submenuitem3 == 1) {
      lcd.clear();
      page=1;
     }
     else if (page == 5 && submenuitem4 == 1) {
      lcd.clear();
      page=1;
     }
     else if(page ==2 && submenuitem1==2)
     {
      lcd.clear();
      page=21;
     }
     else if(page==21)
     {
      lcd.clear();
      page=2;
   }

   else if(page ==3 && submenuitem2==2)
     {
      lcd.clear();
      page=31;
     }
     else if(page==31)
     {
      lcd.clear();
      page=3;
   }
   else if(page ==4 && submenuitem3==2)
     {
      lcd.clear();
      page=41;
     }
     else if(page==41)
     {
      lcd.clear();
      page=4;
   }
   else if(page ==5 && submenuitem4==2)
     {
      lcd.clear();
      page=51;
     }
     else if(page==51)
     {
      lcd.clear();
      page=5;
   }
   else if(page==2&&submenuitem1==3)
   {
    lcd.clear();
    page=22;
   }
   else if(page==22&&stime1==1)
   {
    lcd.clear();
    page=2;
   }
   else if(page==22&&stime1==2)
   {
    lcd.clear();
    page=221;
   }
   else if(page==22&&stime1==3)
   {
    lcd.clear();
    page=222;
   }
   else if(page==221)
   {
    lcd.clear();
    page=22;
   }
   else if(page==222)
   {
    lcd.clear();
    hk1=h1;
    mk1=m1;
    page=22;
   }

   else if(page==3&&submenuitem2==3)
   {
    lcd.clear();
    page=32;
   }
   else if(page==32&&stime2==1)
   {
    lcd.clear();
    page=3;
   }
   else if(page==32&&stime2==2)
   {
    lcd.clear();
    page=321;
   }
   else if(page==32&&stime2==3)
   {
    lcd.clear();
    page=322;
   }
   else if(page==321)
   {
    lcd.clear();
    page=32;
   }
   else if(page==322)
   {
    lcd.clear();
    hk2=h2;
    mk2=m2;
    page=32;
   }

   else if(page==4&&submenuitem3==3)
   {
    lcd.clear();
    page=42;
   }
   else if(page==42&&stime3==1)
   {
    lcd.clear();
    page=4;
   }
   else if(page==42&&stime3==2)
   {
    lcd.clear();
    page=421;
   }
   else if(page==42&&stime3==3)
   {
    lcd.clear();
    page=422;
   }
   else if(page==421)
   {
    lcd.clear();
    hk3=h3;
    mk3=m3;
    page=42;
   }
   else if(page==422)
   {
    lcd.clear();
    page=42;
   }

   else if(page==5&&submenuitem4==3)
   {
    lcd.clear();
    page=52;
   }
   else if(page==52&&stime4==1)
   {
    lcd.clear();
    page=5;
   }
   else if(page==52&&stime4==2)
   {
    lcd.clear();
    page=521;
   }
   else if(page==52&&stime4==3)
   {
    lcd.clear();
    page=522;
   }
   else if(page==521)
   {
    lcd.clear();
    page=52;
   }
   else if(page==522)
   {
    lcd.clear();
    hk4=h4;
    mk4=m4;
    page=52;
   }
  }
}
void drawMenu()
{ 
  if (page==1)
 {
  lcd.setCursor(8,0);
  lcd.print("Menu");
  lcd.setCursor(0,1);
  lcd.print("Number");
  printTime();

  if(menuitem==1)
  {
    lcd.setCursor(7,1);
    lcd.print(">");
    lcd.setCursor(8,1);
    lcd.print("1");
  }
  else
  {
    lcd.setCursor(8,1);
    lcd.print("1");
  }
  
  if(menuitem==2)
  {
    lcd.setCursor(12,1);
    lcd.print(">");
    lcd.setCursor(13,1);
    lcd.print("2");
  }
  else
  {
    lcd.setCursor(13,1);
    lcd.print("2");
  }

  if(menuitem==3)
  {
    lcd.setCursor(7,2);
    lcd.print(">");
    lcd.setCursor(8,2);
    lcd.print("3");
  }
  else
  {
    lcd.setCursor(8,2);
    lcd.print("3");
  }

  if(menuitem==4)
  {
    lcd.setCursor(12,2);
    lcd.print(">");
    lcd.setCursor(13,2);
    lcd.print("4");
  }
  else
  {
    lcd.setCursor(13,2);
    lcd.print("4");
  }
  printTime();
 }
 else if(page==2)
 {
  if(submenuitem1==1)
  {
    lcd.setCursor(15,3);
    lcd.print(">Exit");
  }
  else
  {
    lcd.setCursor(16,3);
    lcd.print("Exit");
  }
  
  if(submenuitem1==2)
  {
  lcd.setCursor(0,0);
  lcd.print(">Amount : ");
  lcd.setCursor(10,0);
  lcd.print(num1);
  }
  else{
  lcd.setCursor(0,0);
  lcd.print("Amount : ");
  lcd.setCursor(9,0);
  lcd.print(num1);
  }

  if(submenuitem1==3)
  {
  lcd.setCursor(0,1);
  lcd.print(">TimeEat : ");
  String hh1;
  String mm1;
  hh1=String(h1);
  if(h1<10)
  {
    hh1="0"+hh1;
    lcd.setCursor(12,1);
    lcd.print(hh1);
  }
  else
  {
    lcd.setCursor(12,1);
    lcd.print(hh1);
  }
  lcd.setCursor(14,1);
  lcd.print(":");
  mm1=String(m1);
  if(m1<10)
  {
    mm1="0"+mm1;
    lcd.setCursor(15,1);
    lcd.print(mm1);
  }else
  {
    lcd.setCursor(15,1);
    lcd.print(mm1);
  }
  }
  else{
    lcd.setCursor(0,1);
    lcd.print("TimeEat : ");
    String hh1;
  String mm1;
  hh1=String(h1);
  if(h1<10)
  {
    hh1="0"+hh1;
    lcd.setCursor(10,1);
    lcd.print(hh1);
  }
  else
  {
    lcd.setCursor(10,1);
    lcd.print(hh1);
  }
  lcd.setCursor(12,1);
  lcd.print(":");
  mm1=String(m1);
  if(m1<10)
  {
    mm1="0"+mm1;
    lcd.setCursor(13,1);
    lcd.print(mm1);
  }else
  {
    lcd.setCursor(13,1);
    lcd.print(mm1);
  }
  }
  printTime();
 }
 else if(page==3)
 {
if(submenuitem2==1)
  {
    lcd.setCursor(15,3);
    lcd.print(">Exit");
  }
  else
  {
    lcd.setCursor(16,3);
    lcd.print("Exit");
  }
  
  if(submenuitem2==2)
  {
  lcd.setCursor(0,0);
  lcd.print(">Amount : ");
  lcd.setCursor(10,0);
  lcd.print(num2);
  }
  else{
  lcd.setCursor(0,0);
  lcd.print("Amount : ");
  lcd.setCursor(9,0);
  lcd.print(num2);
  }

  if(submenuitem2==3)
  {
  lcd.setCursor(0,1);
  lcd.print(">TimeEat : ");
  String hh2;
  String mm2;
  hh2=String(h2);
  if(h2<10)
  {
    hh2="0"+hh2;
    lcd.setCursor(11,1);
    lcd.print(hh2);
  }
  else
  {
    lcd.setCursor(11,1);
    lcd.print(hh2);
  }
  lcd.setCursor(13,1);
  lcd.print(":");
  mm2=String(m2);
  if(m2<10)
  {
    mm2="0"+mm2;
    lcd.setCursor(14,1);
    lcd.print(mm2);
  }else
  {
    lcd.setCursor(14,1);
    lcd.print(mm2);
  }
  }
  else{
    lcd.setCursor(0,1);
    lcd.print("TimeEat : ");
    String hh2;
  String mm2;
  hh2=String(h2);
  if(h2<10)
  {
    hh2="0"+hh2;
    lcd.setCursor(10,1);
    lcd.print(hh2);
  }
  else
  {
    lcd.setCursor(10,1);
    lcd.print(hh2);
  }
  lcd.setCursor(12,1);
  lcd.print(":");
  mm2=String(m2);
  if(m2<10)
  {
    mm2="0"+mm2;
    lcd.setCursor(13,1);
    lcd.print(mm2);
  }else
   {
    lcd.setCursor(13,1);
    lcd.print(mm2);
   }
  }
  printTime();
 }
 
 else if(page==4)
 {
  if(submenuitem3==1)
  {
    lcd.setCursor(15,3);
    lcd.print(">Exit");
  }
  else
  {
    lcd.setCursor(16,3);
    lcd.print("Exit");
  }
  
  if(submenuitem3==2)
  {
  lcd.setCursor(0,0);
  lcd.print(">Amount : ");
  lcd.setCursor(10,0);
  lcd.print(num3);
  }
  else{
  lcd.setCursor(0,0);
  lcd.print("Amount : ");
  lcd.setCursor(9,0);
  lcd.print(num3);
  }

  if(submenuitem3==3)
  {
  lcd.setCursor(0,1);
  lcd.print(">TimeEat : ");
  String hh3;
  String mm3;
  hh3=String(h3);
  if(h3<10)
  {
    hh3="0"+hh3;
    lcd.setCursor(12,1);
    lcd.print(hh3);
  }
  else
  {
    lcd.setCursor(12,1);
    lcd.print(hh3);
  }
  lcd.setCursor(14,1);
  lcd.print(":");
  mm3=String(m3);
  if(m3<10)
  {
    mm3="0"+mm3;
    lcd.setCursor(15,1);
    lcd.print(mm3);
  }else
  {
    lcd.setCursor(15,1);
    lcd.print(mm3);
  }
  }
  else{
    lcd.setCursor(0,1);
    lcd.print("TimeEat : ");
    String hh3;
  String mm3;
  hh3=String(h1);
  if(h3<10)
  {
    hh3="0"+hh3;
    lcd.setCursor(10,1);
    lcd.print(hh3);
  }
  else
  {
    lcd.setCursor(10,1);
    lcd.print(hh3);
  }
  lcd.setCursor(12,1);
  lcd.print(":");
  mm3=String(m3);
  if(m3<10)
  {
    mm3="0"+mm3;
    lcd.setCursor(13,1);
    lcd.print(mm3);
  }else
  {
    lcd.setCursor(13,1);
    lcd.print(mm3);
    }
   }
   printTime();
  }
 else if(page==5)
 {
if(submenuitem4==1)
  {
    lcd.setCursor(15,3);
    lcd.print(">Exit");
  }
  else
  {
    lcd.setCursor(16,3);
    lcd.print("Exit");
  }
  
  if(submenuitem4==2)
  {
  lcd.setCursor(0,0);
  lcd.print(">Amount : ");
  lcd.setCursor(10,0);
  lcd.print(num4);
  }
  else{
  lcd.setCursor(0,0);
  lcd.print("Amount : ");
  lcd.setCursor(9,0);
  lcd.print(num4);
  }
  if(submenuitem4==3)
  {
  lcd.setCursor(0,1);
  lcd.print(">TimeEat : ");
  String hh4;
  String mm4;
  hh4=String(h4);
  if(h4<10)
  {
    hh4="0"+hh4;
    lcd.setCursor(12,1);
    lcd.print(hh4);
  }
  else
  {
    lcd.setCursor(12,1);
    lcd.print(hh4);
  }
  lcd.setCursor(14,1);
  lcd.print(":");
  mm4=String(m4);
  if(m4<10)
  {
    mm4="0"+mm4;
    lcd.setCursor(15,1);
    lcd.print(mm4);
  }else
  {
    lcd.setCursor(15,1);
    lcd.print(mm4);
  }
  }
  else{
    lcd.setCursor(0,1);
    lcd.print("TimeEat : ");
    String hh4;
  String mm4;
  hh4=String(h4);
  if(h4<10)
  {
    hh4="0"+hh4;
    lcd.setCursor(10,1);
    lcd.print(hh4);
  }
  else
  {
    lcd.setCursor(10,1);
    lcd.print(hh4);
  }
  lcd.setCursor(12,1);
  lcd.print(":");
  mm4=String(m4);
  if(m4<10)
  {
    mm4="0"+mm4;
    lcd.setCursor(13,1);
    lcd.print(mm4);
  }else
  {
    lcd.setCursor(13,1);
    lcd.print(mm4);
  }
  }
    printTime();
  }

 if(page==21)
 {
  lcd.setCursor(5,1);
  lcd.print("Amount : ");
  lcd.setCursor(14,1);
  lcd.print(num1);
 }
 if(page==31)
 {
  lcd.setCursor(5,1);
  lcd.print("Amount : ");
  lcd.setCursor(14,1);
  lcd.print(num2);
 }
 if(page==41)
 {
  lcd.setCursor(5,1);
  lcd.print("Amount : ");
  lcd.setCursor(14,1);
  lcd.print(num3);
 }
 if(page==51)
 {
  lcd.setCursor(5,1);
  lcd.print("Amount : ");
  lcd.setCursor(14,1);
  lcd.print(num4);
 }
 if(page==22)
 {
  String hh1;
  String mm1;
  lcd.setCursor(7,0);
  lcd.print("SetTime");
  hh1=String(h1);
  if(h1<10)
  {
    hh1="0"+hh1;
    lcd.setCursor(8,1);
    lcd.print(hh1);
  }
  else
  {
    lcd.setCursor(8,1);
    lcd.print(hh1);
  }
  lcd.setCursor(10,1);
  lcd.print(":");
  mm1=String(m1);
  if(m1<10)
  {
    mm1="0"+mm1;
    lcd.setCursor(11,1);
    lcd.print(mm1);
  }else
  {
    lcd.setCursor(11,1);
    lcd.print(mm1);
  }
  if(stime1==1)
  {
    lcd.setCursor(15,3);
    lcd.print(">Exit");
  }
  else{
    lcd.setCursor(16,3);
    lcd.print("Exit");
  }
  if(stime1==2)
  {
    lcd.setCursor(0,2);
    lcd.print(">hours");
  }
  else{
    lcd.setCursor(0,2);
    lcd.print("hours");
  }
  if(stime1==3)
  {
    lcd.setCursor(0,3);
    lcd.print(">minutes");
  }
  else{
    lcd.setCursor(0,3);
    lcd.print("minutes");
  }
 }
 if(page==221)
 {
  lcd.setCursor(5,1);
  lcd.print("Hours");
  String hh1;
  hh1=String(h1);
  if(h1<10)
  {
    hh1="0"+hh1;
    lcd.setCursor(13,1);
    lcd.print(hh1);
  }
  else
  {
    lcd.setCursor(13,1);
    lcd.print(hh1);
  }
 }
 if(page==222)
 {
  lcd.setCursor(5,1);
  lcd.print("Mins");
  String mm1;
  mm1=String(m1);
  if(m1<10)
  {
    mm1="0"+mm1;
    lcd.setCursor(12,1);
    lcd.print(mm1);
  }
  else
  {
    lcd.setCursor(12,1);
    lcd.print(mm1);
  }
 }

 if(page==32)
 {
  String hh2;
  String mm2;
  lcd.setCursor(7,0);
  lcd.print("SetTime");
  hh2=String(h2);
  if(h2<10)
  {
    hh2="0"+hh2;
    lcd.setCursor(8,1);
    lcd.print(hh2);
  }
  else
  {
    lcd.setCursor(8,1);
    lcd.print(hh2);
  }
  lcd.setCursor(10,1);
  lcd.print(":");
  mm2=String(m2);
  if(m2<10)
  {
    mm2="0"+mm2;
    lcd.setCursor(11,1);
    lcd.print(mm2);
  }else
  {
    lcd.setCursor(11,1);
    lcd.print(mm2);
  }
  if(stime2==1)
  {
    lcd.setCursor(15,3);
    lcd.print(">Exit");
  }
  else{
    lcd.setCursor(16,3);
    lcd.print("Exit");
  }
  if(stime2==2)
  {
    lcd.setCursor(0,2);
    lcd.print(">hours");
  }
  else{
    lcd.setCursor(0,2);
    lcd.print("hours");
  }
  if(stime2==3)
  {
    lcd.setCursor(0,3);
    lcd.print(">minutes");
  }
  else{
    lcd.setCursor(0,3);
    lcd.print("minutes");
  }
 }
 if(page==321)
 {
  lcd.setCursor(5,1);
  lcd.print("Hours");
  String hh2;
  hh2=String(h2);
  if(h2<10)
  {
    hh2="0"+hh2;
    lcd.setCursor(13,1);
    lcd.print(hh2);
  }
  else
  {
    lcd.setCursor(13,1);
    lcd.print(hh2);
  }
 }
 if(page==322)
 {
  lcd.setCursor(5,1);
  lcd.print("Mins");
  String mm2;
  mm2=String(m2);
  if(m2<10)
  {     
    mm2="0"+mm2;
    lcd.setCursor(12,1);
    lcd.print(mm2);
  }
  else
  {
    lcd.setCursor(12,1);
    lcd.print(mm2);
  }
 }

 if(page==42)
 {
  String hh3;
  String mm3;
  lcd.setCursor(7,0);
  lcd.print("SetTime");
  hh3=String(h3);
  if(h3<10)
  {
    hh3="0"+hh3;
    lcd.setCursor(8,1);
    lcd.print(hh3);
  }
  else
  {
    lcd.setCursor(8,1);
    lcd.print(hh3);
  }
  lcd.setCursor(10,1);
  lcd.print(":");
  mm3=String(m3);
  if(m3<10)
  {
    mm3="0"+mm3;
    lcd.setCursor(11,1);
    lcd.print(mm3);
  }else
  {
    lcd.setCursor(11,1);
    lcd.print(mm3);
  }
  if(stime3==1)
  {
    lcd.setCursor(15,3);
    lcd.print(">Exit");
  }
  else{
    lcd.setCursor(16,3);
    lcd.print("Exit");
  }
  if(stime3==2)
  {
    lcd.setCursor(0,2);
    lcd.print(">hours");
  }
  else{
    lcd.setCursor(0,2);
    lcd.print("hours");
  }
  if(stime3==3)
  {
    lcd.setCursor(0,3);
    lcd.print(">minutes");
  }
  else{
    lcd.setCursor(0,3);
    lcd.print("minutes");
  }
 }
 if(page==421)
 {
  lcd.setCursor(5,1);
  lcd.print("Hours");
  String hh3;
  hh3=String(h3);
  if(h3<10)
  {
    hh3="0"+hh3;
    lcd.setCursor(13,1);
    lcd.print(hh3);
  }
  else
  {
    lcd.setCursor(13,1);
    lcd.print(hh3);
  }
 }
 if(page==422)
 {
  lcd.setCursor(5,1);
  lcd.print("Mins");
  String mm3;
  mm3=String(m3);
  if(m3<10)
  {
    mm3="0"+mm3;
    lcd.setCursor(12,1);
    lcd.print(mm3);
  }
  else
  {
    lcd.setCursor(12,1);
    lcd.print(mm3);
  }
 }

if(page==52)
 {
  String hh4;
  String mm4;
  lcd.setCursor(7,0);
  lcd.print("SetTime");
  hh4=String(h4);
  if(h4<10)
  {
    hh4="0"+hh4;
    lcd.setCursor(8,1);
    lcd.print(hh4);
  }
  else
  {
    lcd.setCursor(8,1);
    lcd.print(hh4);
  }
  lcd.setCursor(10,1);
  lcd.print(":");
  mm4=String(m4);
  if(m4<10)
  {
    mm4="0"+mm4;
    lcd.setCursor(11,1);
    lcd.print(mm4);
  }else
  {
    lcd.setCursor(11,1);
    lcd.print(mm4);
  }
  if(stime4==1)
  {
    lcd.setCursor(15,3);
    lcd.print(">Exit");
  }
  else{
    lcd.setCursor(16,3);
    lcd.print("Exit");
  }
  if(stime4==2)
  {
    lcd.setCursor(0,2);
    lcd.print(">hours");
  }
  else{
    lcd.setCursor(0,2);
    lcd.print("hours");
  }
  if(stime4==3)
  {
    lcd.setCursor(0,3);
    lcd.print(">minutes");
  }
  else{
    lcd.setCursor(0,3);
    lcd.print("minutes");
  }
 }
 if(page==521)
 {
  lcd.setCursor(5,1);
  lcd.print("Hours");
  String hh4;
  hh4=String(h4);
  if(h4<10)
  {
    hh4="0"+hh4;
    lcd.setCursor(13,1);
    lcd.print(hh4);
  }
  else
  {
    lcd.setCursor(13,1);
    lcd.print(hh4);
  }
 }
 if(page==522)
 {
  lcd.setCursor(5,1);
  lcd.print("Mins");
  String mm4;
  mm4=String(m4);
  if(m4<10)
  {
    mm4="0"+mm4;
    lcd.setCursor(12,1);
    lcd.print(mm4);
  }
  else
  {
    lcd.setCursor(12,1);
    lcd.print(mm4);
  }
 }
}
void checkIfDownButtonIsPressed()
  {
    if (downButtonState != lastDownButtonState) 
  {
    if (downButtonState == 0) 
    {
      down=true;
    }
    delay(50);
  }
   lastDownButtonState = downButtonState;
  }

void checkIfUpButtonIsPressed()
{
  if (upButtonState != lastUpButtonState) 
  {
    if (upButtonState == 0) {
      up=true;
    }
    delay(50);
  }
   lastUpButtonState = upButtonState;
}

void checkIfSelectButtonIsPressed()
{
   if (selectButtonState != lastSelectButtonState) 
  {
    if (selectButtonState == 0) {
      middle=true;
    }
    delay(50);
  }
   lastSelectButtonState = selectButtonState;
}
void printTime() 
{
  Time t = rtc.time();
  
  nowhour=t.hr;
  nowmin=t.min;
  
  String hour;
  String minutes;
  
  hour = String(t.hr);
  minutes = String(t.min);

  if(t.hr<10)
  {
    hour = "0"+hour;
    lcd.setCursor(0,3);
    lcd.print(hour);
  }else
  {
    lcd.setCursor(0,3);
    lcd.print(hour);
  }
  lcd.setCursor(2,3);
  lcd.print(":");
  
  if(t.min<10)
  {
    minutes = "0"+minutes;
    lcd.setCursor(3,3);
    lcd.print(minutes);
  }else
  {
      lcd.setCursor(3,3);
      lcd.print(minutes);
  }
}
void setTime()
{
  rtc.writeProtect(false);
  rtc.halt(false);
  Time t(2018, 1, 31, 16, 45, 00, Time::kWednesday);
  rtc.time(t);
}
void alarm(){
  tone(buzzer, 2500); 
  delay(250);        
  noTone(buzzer);    
  delay(250); 
}

