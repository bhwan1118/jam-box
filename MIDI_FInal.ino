/* MIDI Input Test - for use with Teensy or boards where Serial is separate from MIDI
   As MIDI messages arrive, they are printed to the Arduino Serial Monitor.

   Where MIDI is on "Serial", eg Arduino Duemilanove or Arduino Uno, this does not work!

   This example code is released into the public domain.
*/

#include <MIDI.h>
#include <SoftwareSerial.h>
#include "pitches.h"

#include <LiquidCrystal.h>
#include <LiquidMenu.h>
#include "button.h"

// We will use the SoftwareSerial library instead of the Serial library, as this will let us control which pins our MIDI interface is connected to.
SoftwareSerial midiSerial(0, 3); // RX, TX

MIDI_CREATE_INSTANCE(SoftwareSerial, midiSerial, MIDI);

//Define pin for speaker
int speakerpin = 13;


//int DMAJ[] = {0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  NOTE_FS2,   NOTE_G2,  0,  NOTE_A2,  0,  NOTE_B2,  0,  NOTE_CS3,   NOTE_D3,  0,  NOTE_E3,  0,  NOTE_FS3,   NOTE_G3,  0,  NOTE_A3,  0,  NOTE_B3,  0,  NOTE_CS4,   NOTE_D4,  0,  NOTE_E4,  0,  NOTE_FS4,   NOTE_G4,  0,  NOTE_A4,  0,  NOTE_B4,  0,  NOTE_CS5,   NOTE_D5,  0,  NOTE_E5,  0,  NOTE_FS5,   NOTE_G5,  0,  NOTE_A5,  0,  NOTE_B5,  0,  NOTE_CS6,   NOTE_D6,  0,  NOTE_E6,  0,  NOTE_FS6,   NOTE_G6,  0,  NOTE_A6,  0,  NOTE_B6,  0,  NOTE_CS7,   NOTE_D7,  0,  NOTE_E7,  0,  NOTE_FS7,   NOTE_G7,  0,  NOTE_A7,  0,  NOTE_B7,  0,  NOTE_CS8,   NOTE_D8,  0,  NOTE_E8,  0,  NOTE_FS8};
//int EMAJ[] = {0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  NOTE_GS2,   NOTE_A2,  0,  NOTE_B2,  0,  NOTE_CS3,   0,  NOTE_DS3,   NOTE_E3,  0,  NOTE_FS3,   0,  NOTE_GS3,   NOTE_A3,  0,  NOTE_B3,  0,  NOTE_CS4,   0,  NOTE_DS4,   NOTE_E4,  0,  NOTE_FS4,   0,  NOTE_GS4,   NOTE_A4,  0,  NOTE_B4,  0,  NOTE_CS5,   0,  NOTE_DS5,   NOTE_E5,  0,  NOTE_FS5,   0,  NOTE_GS5,   NOTE_A5,  0,  NOTE_B5,  0,  NOTE_CS6,   0,  NOTE_DS6,   NOTE_E6,  0,  NOTE_FS6,   0,  NOTE_GS6,   NOTE_A6,  0,  NOTE_B6,  0,  NOTE_CS7,   0,  NOTE_DS7,   NOTE_E7,  0,  NOTE_FS7,   0,  NOTE_GS7,   NOTE_A7,  0,  NOTE_B7,  0,  NOTE_CS8,   0,  NOTE_DS8,   NOTE_E8,  0,  NOTE_FS8,   0,  NOTE_GS8};

//int DMAJ[] = {NOTE_FS2,   NOTE_G2,  0,  NOTE_A2,  0,  NOTE_B2,  0,  NOTE_CS3,   NOTE_D3,  0,  NOTE_E3,  0,  NOTE_FS3,   NOTE_G3,  0,  NOTE_A3,  0,  NOTE_B3,  0,  NOTE_CS4,   NOTE_D4,  0,  NOTE_E4,  0,  NOTE_FS4,   NOTE_G4,  0,  NOTE_A4,  0,  NOTE_B4,  0,  NOTE_CS5,   NOTE_D5,  0,  NOTE_E5,  0,  NOTE_FS5,   NOTE_G5,  0,  NOTE_A5,  0,  NOTE_B5,  0,  NOTE_CS6,   NOTE_D6,  0,  NOTE_E6,  0,  NOTE_FS6,   NOTE_G6,  0,  NOTE_A6,  0,  NOTE_B6,  0,  NOTE_CS7,   NOTE_D7,  0,  NOTE_E7,  0,  NOTE_FS7,   NOTE_G7,  0,  NOTE_A7,  0,  NOTE_B7,  0,  NOTE_CS8,   NOTE_D8,  0,  NOTE_E8,  0,  NOTE_FS8};
int EMAJ[] = {NOTE_GS2,   NOTE_A2,  0,  NOTE_B2,  0,  NOTE_CS3,   0,  NOTE_DS3,   NOTE_E3,  0,  NOTE_FS3,   0,  NOTE_GS3,   NOTE_A3,  0,  NOTE_B3,  0,  NOTE_CS4,   0,  NOTE_DS4,   NOTE_E4,  0,  NOTE_FS4,   0,  NOTE_GS4,   NOTE_A4,  0,  NOTE_B4,  0,  NOTE_CS5,   0,  NOTE_DS5,   NOTE_E5,  0,  NOTE_FS5,   0,  NOTE_GS5,   NOTE_A5,  0,  NOTE_B5,  0,  NOTE_CS6,   0,  NOTE_DS6,   NOTE_E6,  0,  NOTE_FS6,   0,  NOTE_GS6,   NOTE_A6,  0,  NOTE_B6,  0,  NOTE_CS7,   0,  NOTE_DS7,   NOTE_E7,  0,  NOTE_FS7,   0,  NOTE_GS7,   NOTE_A7,  0,  NOTE_B7,  0,  NOTE_CS8,   0,  NOTE_DS8,   NOTE_E8,  0,  NOTE_FS8,   0,  NOTE_GS8};
int EMIN[] = {NOTE_A2,  NOTE_B2,  0,  NOTE_C3,  0,  NOTE_D3,  0,  NOTE_E3,  NOTE_FS3,   0,  NOTE_G3,  0,  NOTE_A3,  NOTE_B3,  0,  NOTE_C4,  0,  NOTE_D4,  0,  NOTE_E4,  NOTE_FS4,   0,  NOTE_G4,  0,  NOTE_A4,  NOTE_B4,  0,  NOTE_C5,  0,  NOTE_D5,  0,  NOTE_E5,  NOTE_FS5,   0,  NOTE_G5,  0,  NOTE_A5,  NOTE_B5,  0,  NOTE_C6,  0,  NOTE_D6,  0,  NOTE_E6,  NOTE_FS6,   0,  NOTE_G6,  0,  NOTE_A6,  NOTE_B6,  0,  NOTE_C7,  0,  NOTE_D7,  0,  NOTE_E7,  NOTE_FS7,   0,  NOTE_G7,  0,  NOTE_A7,  NOTE_B7,  0,  NOTE_C8,  0,  NOTE_D8,  0,  NOTE_E8,  NOTE_FS8,   0,  NOTE_G8,  0,  NOTE_A2};
int CMINPENT[] = {NOTE_F2,  NOTE_FS2,   0,  NOTE_G2,  0,  NOTE_AS2,   0,  NOTE_C3,  NOTE_DS3,   0,  NOTE_F3,  0,  NOTE_FS3,   NOTE_G3,  0,  NOTE_AS3,   0,  NOTE_C4,  0,  NOTE_DS4,   NOTE_F4,  0,  NOTE_FS4,   0,  NOTE_G4,  NOTE_AS4,   0,  NOTE_C5,  0,  NOTE_DS5,   0,  NOTE_F5,  NOTE_FS5,   0,  NOTE_G5,  0,  NOTE_AS5,   NOTE_C6,  0,  NOTE_DS6,   0,  NOTE_F6,  0,  NOTE_FS6,   NOTE_G6,  0,  NOTE_AS6,   0,  NOTE_C7,  NOTE_DS7,   0,  NOTE_F7,  0,  NOTE_FS7,   0,  NOTE_G7,  NOTE_AS7,   0,  NOTE_C8,  0,  NOTE_DS8,   NOTE_B7,  0,  NOTE_C8,  0,  NOTE_D8,  0,  NOTE_E8,  NOTE_FS8,   0,  NOTE_G8,  0,  NOTE_A2};
//int FMAJPENT[] = {0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  NOTE_A2,  NOTE_C3,  0,  NOTE_D3,  0,  NOTE_F3,  0,  NOTE_G3,  NOTE_GS3,   0,  NOTE_A3,  0,  NOTE_C4,  NOTE_D4,  0,  NOTE_F4,  0,  NOTE_G4,  0,  NOTE_GS4,   NOTE_A4,  0,  NOTE_C5,  0,  NOTE_D5,  NOTE_F5,  0,  NOTE_G5,  0,  NOTE_GS5,   0,  NOTE_A5,  NOTE_C6,  0,  NOTE_D6,  0,  NOTE_F6,  NOTE_G6,  0,  NOTE_GS6,   0,  NOTE_A6,  0,  NOTE_C7,  NOTE_D7,  0,  NOTE_F7,  0,  NOTE_G7,  NOTE_GS7,   0,  NOTE_A7,  0,  NOTE_C8,  0,  NOTE_D8,  NOTE_F8,  0,  NOTE_G8,  0,  NOTE_GS8,   NOTE_B7,  0,  NOTE_C8,  0,  NOTE_D8,  0,  NOTE_E8,  NOTE_FS8,   0,  NOTE_G8,  0,  NOTE_A2};
//int white_keys[] = {28,  29,   31,   33,   35,   36,   38,   40,   41,   43,   45,   47,   48,   50,   52,   53,   55,   57,   59,   60,   62,   64,   65,   67,   69,   71,   72,   74,   76,   77,   79,   81,   83,   84,   86,   88,   89,   91,   93,   95,   96,   98,   100};

int state = 0;



// Pin mapping for the display
const byte LCD_RS = 12;
const byte LCD_E = 11;
const byte LCD_D4 = 5;
const byte LCD_D5 = 4;
const byte LCD_D6 = 3;
const byte LCD_D7 = 2;
#define ENC_A 8 //these need to be digital input pins
#define ENC_B 9
#define ENC_C 7
//LCD R/W pin to ground
//10K potentiometer to VO
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/*
   The Button class is not a part of the LiquidMenu library. The first
   parameter is the button's pin, the second enables or disables the
   internal pullup resistor (not required) and the third is the debounce
   time (not required).
*/
// Button objects instantiation
const bool pullup = true;
Button enter(7, pullup);

const float pi = 3.14159265f;

LiquidLine line1(0, 0, "C MIN PENT");
LiquidLine line2(0, 1, "E MAJ");
LiquidLine line3(0, 1, "E MIN");
//LiquidLine line4(0, 1, "C MIN PENT");
//LiquidLine line5(0, 1, "F MAJ PENT");


LiquidScreen screen;

LiquidMenu menu(lcd);

// Used for attaching something to the lines, to make them focusable.
void blankFunction() {
  return;
}


void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(250000);
  Serial.println("MIDI Input Test");
  //Serial.println(white_keys[1]);

  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);

  lcd.begin(16, 2);

  // Add more "lines" than the display has. The extra will be scrolled.
  screen.add_line(line1);
  screen.add_line(line2);
  screen.add_line(line3);
//  screen.add_line(line4);
//  screen.add_line(line5);

  // Attaching a function to the lines is required for scrolling to work.
  line1.attach_function(1, blankFunction);
  line2.attach_function(1, blankFunction);
  line3.attach_function(1, blankFunction);
//  line4.attach_function(1, blankFunction);
//  line5.attach_function(1, blankFunction);

  // Set the number of lines the display has.
  /*
     Setting this is a must when you want to add more "lines" than
     the display actually has (the extra lines will be scrolled).
     This must be set after adding the "lines" to the "screen".
  */
  screen.set_displayLineCount(2);

  menu.add_screen(screen);
  menu.update();


}


int currentLine = -10;
void loop() {
  int type, note, velocity, channel, d1, d2;

  static unsigned int counter4x = 0;      //the SparkFun encoders jump by 4 states from detent to detent
  static unsigned int counter = 0;
  static unsigned int prevCounter = 0;
  // Turn off the display:
  int tmpdata;
  tmpdata = read_encoder();
  if ( tmpdata) {
  
    counter4x += tmpdata;
    counter = counter4x / 4;

    if (prevCounter != counter) {
      tmpdata = tmpdata * -1;
      if (tmpdata == 1) {
        if (currentLine == -10) {
          currentLine = 3;
        }
        currentLine -= tmpdata;
        if (currentLine == -1) {
          menu.switch_focus(false);
          currentLine = 2;
        }

        Serial.println(currentLine);
        menu.switch_focus(false);
      } else if (tmpdata == -1) {
        if (currentLine == -10) {
          currentLine = -1;
        }
        currentLine -= tmpdata;

        if (currentLine == 3) {
          menu.switch_focus();
          currentLine = 0;
        }
        Serial.println(currentLine);
        menu.switch_focus();
      }





    }
    prevCounter = counter;
  }
  //
  //  if (enter.check() == LOW) {
  //    Serial.println(F("ENTER button pressed"));
  //    menu.switch_focus(false);
  //    menu.update();
  //  }


  if (MIDI.read()) {                    // Is there a MIDI message incoming ?
    byte type = MIDI.getType();
    switch (type) {
      case midi::NoteOn:
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        if (velocity > 0) {
          Serial.println(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + velocity);
          if (currentLine == 0) {
            tone(speakerpin, CMINPENT[note - 28], 40);
          } else if (currentLine == 1) {
            tone(speakerpin, EMAJ[note - 28], 40);
          } else if (currentLine == 2)  {
            tone(speakerpin, EMIN[note - 28], 40);
          } 
         
          break;
        case midi::NoteOff:
          note = MIDI.getData1();
          velocity = MIDI.getData2();
          channel = MIDI.getChannel();
          //Serial.println(String("Note Off: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
          break;
        default:
          d1 = MIDI.getData1();
          d2 = MIDI.getData2();
          //Serial.println(String("Message, type=") + type + ", data = " + d1 + " " + d2);
        }

    }

  }
}

int read_encoder()
{
  static int enc_states[] = {
    0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0
  };
  static byte ABab = 0;
  ABab *= 4;                   //shift the old values over 2 bits
  ABab = ABab % 16;    //keeps only bits 0-3
  ABab += 2 * digitalRead(ENC_A) + digitalRead(ENC_B); //adds enc_a and enc_b values to bits 1 and 0

  return ( enc_states[ABab]);


}
