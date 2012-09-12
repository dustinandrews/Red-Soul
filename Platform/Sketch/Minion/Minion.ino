/*
Robotic Minion Starter Kit sample program
Copyright Dustin Andrews 2012

Licensed under the follwing license:

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
in the documentation and/or other materials provided with the distribution.
The name of the author may not be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


/* Libs Required:
LiquidCrystal should be built in.

Other Libs as follows:

https://github.com/DavidAndrews/Arduino_LCD_Menu
http://www.arduino.cc/playground/Code/Bounce
http://www.pjrc.com/teensy/td_libs_Encoder.html
*/


#include <arduino.h>
#include <LiquidCrystal.h>
#include <MenuEntry.h>
#include <MenuIntHelper.h>
#include <MenuLCD.h>
#include <MenuManager.h>
#include <Encoder.h>
#include <Bounce.h>

//Edit your particular harware setup here - See LiquidCrystal documentation for details
const int LCDD7 = 4;
const int LCDD6 = 6;
const int LCDD5 = 7;
const int LCDD4 = 8;
const int LCDE  = 9;
const int LCDRS = 10;

//Now create the MenuLCD and MenuManager classes.
MenuLCD g_menuLCD( LCDRS, LCDE, LCDD4, LCDD5, LCDD6, LCDD7, 16, 2);
MenuManager g_menuManager( &g_menuLCD);
const int ROTARY1 = A0;
const int ROTARY0 = 2;
const int SPEAKER = 5;
const int CLICK = 12;
const int LEDPIN = 13;

LiquidCrystal *pLCD = NULL;
/* setup hardware devices */
Encoder rotary(ROTARY0, ROTARY1);
Bounce clicker(CLICK, 5);
long rotaryPos = 0;
long rotaryOld = 0;
/**************************/

byte g_note[8] = {
  B00011,
  B00010,
  B00010,
  B00010,
  B01110,
  B01010,
  B01110,
};

byte g_note2[8] = {
  B01100,
  B01011,
  B11001,
  B11001,
  B00011,
  B00011,
  B00000,
};


void setupMenus()
{  
  g_menuLCD.MenuLCDSetup();  
}

void doit( char * s1, char * s2, int d )
{
  g_menuLCD.ClearLCD();
  g_menuLCD.PrintLine( s1 , 0 );
  g_menuLCD.PrintLine( s2 , 1 );
  delay(d);
}

void setup() 
{
  Serial.begin(115200);
  Serial.print("Ready.");
  pinMode( 13, OUTPUT );
  //set up click input
  pinMode(CLICK, INPUT );
  //Turn on pullup resistor for click button
  digitalWrite( CLICK, HIGH );
  setupMenus();
  g_menuLCD.getLCD()->createChar( 0, g_note );
  g_menuLCD.getLCD()->createChar( 1, g_note2 );

  MenuEntry * p_menuEntryRoot;
  //Add root node
  p_menuEntryRoot = new MenuEntry("Robotic Minion", NULL, NULL);
  g_menuManager.addMenuRoot( p_menuEntryRoot );

  g_menuManager.addChild( new MenuEntry("Run Tests", NULL, TestCallback) );
  g_menuManager.addChild( new MenuEntry("Say Hello", NULL, HelloCallback) );
  
  g_menuManager.addChild( new MenuEntry("Tell us more", NULL, MoreCallback) );
  g_menuManager.addChild( new MenuEntry("Show Examples", NULL, MoreCallback) );
  g_menuManager.MenuSelect();
  g_menuManager.MenuDown();
  g_menuManager.MenuDown();
  g_menuManager.addChild( new MenuEntry("Take Input", NULL, InputCallback) );
  g_menuManager.addChild( new MenuEntry("Take Picture", NULL, PictureCallback ) );
  g_menuManager.addChild( new MenuEntry("Play Music", NULL, MusicCallback) );
  g_menuManager.addChild( new MenuEntry("Back", (void *) &g_menuManager, MenuEntry_BackCallbackFunc) );
  g_menuManager.SelectRoot();

  g_menuManager.addChild( new MenuEntry("Ask the Question", NULL, QuestionCallback) );
  g_menuManager.addChild( new MenuEntry("Back", (void *) &g_menuManager, MenuEntry_BackCallbackFunc) );
  g_menuManager.DrawMenu();
}

int d = 2200;
int dl = 3000;

void TestCallback( char* pMenuText, void *pUserData)
{
  Test(); 
}
void Test()
{
  doit("Flash Pin 13 LED","", d - 1000);
  for(int i=0; i<5; i++)
  {
    digitalWrite(LEDPIN, HIGH);
    delay(125);
    digitalWrite(LEDPIN, LOW);
    delay(125);
  }
  
  doit("Play a tone", "on speaker", d - 1000);
  tone(SPEAKER, 349, 1000);
  
  doit("Ensure input","up/down", d - 1000);
  
  char *pLabel = "Input a number";
  int iNumLabelLines = 1;
  int iMin = 1;
  int iMax = 100;
  int iStart = 50;
  //Each user input action (such as a turn of rotary enocoder or push of button
  //will step this amount
  int iStep = 1;
  
  int i;
  g_menuManager.DoIntInput( iMin, iMax, iStart, iStep, &pLabel, iNumLabelLines, &i );
}

void More()
{
  doit( "I'm an Adruino", "compatible", d );
  doit( "board plus a ", "few extras:", d );
  doit( "16x2 LCD display", "Speaker", d+500 );
  doit( "USB Port", "Rotary Encoder", d );
  doit( "Power Regulator", " and Enclosure.", d );
  doit( "With me, you","can take your", d);
  doit( "Arduino project","beyond your desk", dl);
  doit( "because I am ","rugged and ", d);
  doit( "versatile."," ", d);
  doit( "I come with", "a menu library", dl);
  doit( "so you can write","apps controlled", dl);
  doit( "with my rotary", "encoder (knob).",dl);
  g_menuManager.DrawMenu();
}

void Hello()
{
  int d = 2200;
  int dl = 3000;
  g_menuLCD.ClearLCD();
  delay(1800);
  g_menuLCD.PrintLine( "Hello", 1 );
  delay(d);
  for( int i = 0; i < 5; ++i )
  {
    g_menuLCD.getLCD()->scrollDisplayRight();
    delay(d/4);
  }
  delay(d/4);
  g_menuLCD.ClearLCD();
  g_menuLCD.PrintLine( "     Hello", 0 );
  delay(d);
  doit( "My name is the", " ", d);
  doit("Robotic Minion", "Starter Kit.", d+d );
  doit( "I help you get", "your code", d );
  doit( "running and into", "the real world", d );
  doit( "faster!", " ", d );
  for( int i = 0; i < 17; ++i )
  {
    g_menuLCD.getLCD()->scrollDisplayRight();
    delay(d/((i+1)*4));
  }
  g_menuManager.DrawMenu();

}

void loop() 
{
 rotaryPos = rotary.read();
 clicker.update();

 if(clicker.fallingEdge())
 {
   Serial.println( "CLICK");
   g_menuManager.DoMenuAction( MENU_ACTION_SELECT );
 }
 ProcessRotaryEncoder();
}

void ProcessRotaryEncoder()
{
 if(abs(rotaryPos - rotaryOld)>3)
 {
    if( rotaryPos < rotaryOld )
    {
      g_menuManager.DoMenuAction( MENU_ACTION_UP );
    }
    else
    {
      g_menuManager.DoMenuAction( MENU_ACTION_DOWN );
    }
    rotaryOld = rotaryPos;
 }
}


void HelloCallback( char* pMenuText, void *pUserData)
{
  Hello();
}

void MoreCallback( char* pMenuText, void *pUserData)
{
  More();
}

void QuestionCallback( char* pMenuText, void *pUserData)
{
   doit( "Do you want to", "take me home? ", dl);
   doit( "Buy me at", "Rugged Circuits", dl);
   doit( "http://bit.ly/", "rminionl", dl);
   doit( "Wherever you", "need a minion,", dl);
   doit( "I'll be there to", "do your bidding.", dl);
}



void InputCallback( char* pMenuText, void *pUserData )
{
  char *pLabel = "Input a number";
  int iNumLabelLines = 1;
  int iMin = 1;
  int iMax = 100;
  int iStart = 50;
  //Each user input action (such as a turn of rotary enocoder or push of button
  //will step this amount
  int iStep = 1;
  
  int i;
  g_menuManager.DoIntInput( iMin, iMax, iStart, iStep, &pLabel, iNumLabelLines, &i );
}

void PictureCallback( char *, void *)
{
  doit( "AWWWW SNAP", " ", 0);
  digitalWrite( 13, HIGH );    
  delay(4200);
  digitalWrite( 13, LOW );
}

void MusicCallback( char *, void *)
{
  int row = 0;
  int col = 0;
  int ch = 0;

  g_menuLCD.ClearLCD();

  g_menuLCD.getLCD()->setCursor( col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 261, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 391, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 391, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 440, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 440, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 391, 1024);
  delay(1029);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 349, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 349, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 329, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 329, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 293, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 293, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 261, 1024);
  delay(1029);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 391, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 391, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 349, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 349, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 329, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 329, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 293, 1024);
  delay(1029);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 391, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 391, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 349, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 349, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 329, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 329, 512);
  delay(517);
  g_menuLCD.getLCD()->setCursor( ++col, row );
  g_menuLCD.getLCD()->print( (char)(++ch%2) );
  tone(SPEAKER, 293, 1024);
  delay(1029);
}
