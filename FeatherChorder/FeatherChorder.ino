

/*
 * Arduino code for a Bluetooth version of the Chorder.
 * @author: clc@clcworld.net
 * additional code by: priestdo@budgardr.org
 * This version tested on/with the Adafruit Feather 32u4 Bluefruit LE
 *
 * It is a new arduino based chorder inspired by the SpiffChorder 
 * which can be found at http://symlink.dk/projects/spiffchorder/ 
 */

#include <Arduino.h>
#include <HID-Settings.h>
#include <HID-Project.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_)
#include <SoftwareSerial.h>
#endif

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"
#include "KeyCodes.h"
#include "ChordMappings.h"
#include "Pins.h"

/*========================================================================
    APPLICATION SETTINGS

    FACTORYRESET_ENABLE       Perform a factory reset when running this sketch
   
                              Enabling this will put your Bluefruit LE module
                              in a 'known good' state and clear any config
                              data set in previous sketches or projects, so
                              running this at least once is a good idea.
   
                              When deploying your project, however, you will
                              want to disable factory reset by setting this
                              value to 0.  If you are making changes to your
                              Bluefruit LE device via AT commands, and those
                              changes aren't persisting across resets, this
                              is the reason why.  Factory reset will erase
                              the non-volatile memory where config data is
                              stored, setting it back to factory default
                              values.
       
                              Some sketches that require you to bond to a
                              central device (HID mouse, keyboard, etc.)
                              won't work at all with this feature enabled
                              since the factory reset will clear all of the
                              bonding data stored on the chip, meaning the
                              central device won't be able to reconnect.
    MINIMUM_FIRMWARE_VERSION  Minimum firmware version to have some new features
    -----------------------------------------------------------------------*/
    #define FACTORYRESET_ENABLE         0
    #define MINIMUM_FIRMWARE_VERSION    "0.6.6"
/*=========================================================================*/

// Create the bluefruit object, either software serial...uncomment these lines
/*
SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);

Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN,
                      BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);
*/

/* ...or hardware serial, which does not need the RTS/CTS pins. Uncomment this line */
// Adafruit_BluefruitLE_UART ble(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN);

/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

/* ...software SPI, using SCK/MOSI/MISO user-defined SPI pins and then user selected CS/IRQ/RST */
//Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_SCK, BLUEFRUIT_SPI_MISO,
//                             BLUEFRUIT_SPI_MOSI, BLUEFRUIT_SPI_CS,
//                             BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  int last = millis();
  while (1) {
    if (millis() - last > 2000) {
      last = millis();
      Serial.println(err);
    }
  }
}

// moved to KeyCodes.h

// moved to ChordMappings.h


class Button {
  byte _pin;  // The button's I/O pin, as an Arduino pin number.
  
public:
  Button(byte pin) : _pin(pin) {
    pinMode(pin, INPUT_PULLUP);      // Make pin an input and activate pullup.
  }
  
  bool isDown() const {
    // TODO: this assumes we're using analog pins!
    //return analogRead(_pin) < 0x100;
    return (digitalRead(_pin) == LOW);
  }
};

// power regulator enabale control pin
const int EnPin =  5;

// Pin numbers for the keyboard switches, using the Arduino numbering.
static const Button switch_pins[7] = {
  Button(PINKY),
  Button(RING),
  Button(MIDDLE),
  Button(INDEX),
  Button(NEAR_THUMB),
  Button(CENTER_THUMB),
  Button(FAR_THUMB)
};

void setup(void)
{
  // Ensure software power reset pin in high
   pinMode(EnPin, OUTPUT);      // Make pin an output,
   digitalWrite(EnPin, HIGH);  // and activate pullup.
  //while (!Serial);  // Required for Flora & Micro
  delay(500);

  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit HID Chorder"));
  Serial.println(F("---------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Factory reset failed!"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  // This demo only works with firmware 0.6.6 and higher!
  // Request the Bluefruit firmware rev and check if it is valid
  if ( !ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    error(F("This sketch requires firmware version " MINIMUM_FIRMWARE_VERSION " or higher!"));
  }

  /* Enable HID Service */
  Serial.println(F("Enable HID Services (including Control Key): "));
  if (! ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=On"  ))) {
    error(F("Failed to enable HID (firmware >=0.6.6?)"));
  }

  /* Adding or removing services requires a reset */
  Serial.println(F("Performing a SW reset (service changes require a reset): "));
  if (! ble.reset() ) {
    error(F("Couldn't reset??"));
  }


  String stringOne =  String(0x45, HEX);
  
  Serial.println(stringOne);

  Keyboard.begin();
}


enum State {
  PRESSING,
  RELEASING,
};

State state = RELEASING;
byte lastKeyState = 0;

enum Mode {
  ALPHA,
  NUMSYM,
  FUNCTION
};

bool isCapsLocked = false;
bool isNumsymLocked = false;
keymap_t modKeys = 0x00;
uint8_t usbModKeys = 0x00;


Mode mode = ALPHA;


void send(char* character) {
//  Uart.print(character);
}


void sendKey(byte keyState){
  keymap_t theKey;  
  // Determine the key based on the current mode's keymap
  if (mode == ALPHA) {
    theKey = keymap_default[keyState];
  } else if (mode == NUMSYM) {
    theKey = keymap_numsym[keyState];
  } else {
    theKey = keymap_function[keyState];
  }

  switch (theKey)  {
  // Handle mode switching - return immediately after the mode has changed
  // Handle basic mode switching
  case MODE_NUM:
    if (mode == NUMSYM) {
      mode = ALPHA;
    } else {
      mode = NUMSYM;
    }
    return;
  case MODE_FUNC:
    if (mode == FUNCTION) {
      mode = ALPHA;
    } else {
      mode = FUNCTION;
    }
    return;
  case MODE_RESET:
    mode = ALPHA;
    modKeys = 0x00;
    Keyboard.release(KEY_LEFT_CTRL);
    isCapsLocked = false;
    Keyboard.release(KEY_LEFT_SHIFT);
    isNumsymLocked = false;
    Keyboard.release(KEY_LEFT_ALT);
    Keyboard.release(KEY_LEFT_GUI);
    return;
  case MODE_MRESET:
    mode = ALPHA;
    modKeys = 0x00;
    isCapsLocked = false;
    isNumsymLocked = false;
    digitalWrite(EnPin, LOW);  // turn off 3.3v regulator enable.
    Keyboard.releaseAll();
    return;
  // Handle mode locks
  case ENUMKEY_cpslck:
    if (isCapsLocked) {
      isCapsLocked = false;
      modKeys = 0x00;
      Keyboard.release(KEY_LEFT_SHIFT);
    } else {
      isCapsLocked = true;
      modKeys = 0x02;
      Keyboard.press(KEY_LEFT_SHIFT);
    }
    return;
  case MODE_NUMLCK:
    if (isNumsymLocked) {
      isNumsymLocked = false;
      mode = ALPHA;
    } else {
      isNumsymLocked = true;
      mode = NUMSYM;
    }
    return;
  // Handle modifier keys toggling
  case MOD_LCTRL:
    modKeys = modKeys ^ 0x01;
    Keyboard.press(KEY_LEFT_CTRL);
    return;
  case MOD_LSHIFT:
    modKeys = modKeys ^ 0x02;
    Keyboard.press(KEY_LEFT_SHIFT);
    return;
  case MOD_LALT:
    modKeys = modKeys ^ 0x04;
    Keyboard.press(KEY_LEFT_ALT);
    return;
  case MOD_LGUI:
    modKeys = modKeys ^ 0x08;
    Keyboard.press(KEY_LEFT_GUI);
    return;
  case MOD_RCTRL:
    modKeys = modKeys ^ 0x10;
    Keyboard.press(KEY_RIGHT_CTRL);
    return;
  case MOD_RSHIFT:
    modKeys = modKeys ^ 0x20;
    Keyboard.press(KEY_RIGHT_SHIFT);
    return;
  case MOD_RALT:
    modKeys = modKeys ^ 0x40;
    Keyboard.press(KEY_RIGHT_ALT);
    return;
  case MOD_RGUI:
    modKeys = modKeys ^ 0x80;
    Keyboard.press(KEY_RIGHT_GUI);
    return;
  // Handle special keys
  case MULTI_NumShift:
    if (mode == NUMSYM) {
      mode = ALPHA;
    } else {
      mode = NUMSYM;
    }
    modKeys = modKeys ^ 0x02;
    Keyboard.press(KEY_LEFT_SHIFT);
    return;
  case MULTI_CtlAlt:
    modKeys = modKeys ^ 0x01;
    Keyboard.press(KEY_LEFT_CTRL);
    modKeys = modKeys ^ 0x04;
    Keyboard.press(KEY_LEFT_ALT);
    return;
  /* Everything after this sends actual keys to the system; break rather than
     return since we want to reset the modifiers after these keys are sent. */
  case MACRO_000:
    sendRawKey(0x00, 0x27);
    sendRawKey(0x00, 0x27);
    sendRawKey(0x00, 0x27);
    Keyboard.print("000");
    break;
  case MACRO_00:
    sendRawKey(0x00, 0x27);
    sendRawKey(0x00, 0x27);
    Keyboard.print("00");
    break;
  case MACRO_quotes:
    sendRawKey(0x02, 0x34);
    sendRawKey(0x02, 0x34);
    sendRawKey(0x00, 0x50);
    Keyboard.print("\"\"");
    Keyboard.write(KEY_LEFT_ARROW);
    break;
  case MACRO_parens:
    sendRawKey(0x02, 0x26);
    sendRawKey(0x02, 0x27);
    sendRawKey(0x00, 0x50);
    Keyboard.print("()");
    Keyboard.write(KEY_LEFT_ARROW);
    break;
  case MACRO_dollar:
    sendRawKey(0x02, 0x21);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('1');
    Keyboard.release(KEY_LEFT_SHIFT);
    break;
  case MACRO_percent:
    sendRawKey(0x02, 0x22);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('5');
    Keyboard.release(KEY_LEFT_SHIFT);
    break;
  case MACRO_ampersand:
    sendRawKey(0x02, 0x24);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('7');
    Keyboard.release(KEY_LEFT_SHIFT);
    break;
  case MACRO_asterisk:
    sendRawKey(0x02, 0x25);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('8');
    Keyboard.release(KEY_LEFT_SHIFT);
    break;
  case MACRO_question:
    sendRawKey(0x02, 0x38);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('/');
    Keyboard.release(KEY_LEFT_SHIFT);
    break;
  case MACRO_plus:
    sendRawKey(0x02, 0x2E);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('=');
    Keyboard.release(KEY_LEFT_SHIFT);
    break;
  case MACRO_openparen:
    sendRawKey(0x02, 0x26);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('9');
    Keyboard.release(KEY_LEFT_SHIFT);
    break;
  case MACRO_closeparen:
    sendRawKey(0x02, 0x27);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('0');
    Keyboard.release(KEY_LEFT_SHIFT);
    break;
  case MACRO_opencurly:
    sendRawKey(0x02, 0x2F);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('[');
    Keyboard.release(KEY_LEFT_SHIFT);
    break;
  case MACRO_closecurly:
    sendRawKey(0x02, 0x30);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write(']');
    Keyboard.release(KEY_LEFT_SHIFT);
    break;
  // Handle Android specific keys
  case ANDROID_search:
    sendRawKey(0x04, 0x2C);
    Keyboard.write(KeyboardKeycode(0x7e));
    break;
  case ANDROID_home:
    sendRawKey(0x04, 0x29);
    Keyboard.write(KeyboardKeycode(KEY_HOME));
    break;
  case ANDROID_menu:
    sendRawKey(0x10, 0x29);
    Keyboard.write(KeyboardKeycode(0x76));
    break;
  case ANDROID_back:
    sendRawKey(0x00, 0x29);
    Keyboard.write(KeyboardKeycode(0x7a));
    break;
  case ANDROID_dpadcenter:
    sendRawKey(0x00, 0x5D);
    Keyboard.write(KeyboardKeycode(0x77));
    break;
  case MEDIA_playpause:
    sendControlKey("PLAYPAUSE");
    Keyboard.write(KeyboardKeycode(0xe8));
    break;
  case MEDIA_stop:
    sendControlKey("MEDIASTOP");
    Keyboard.write(KeyboardKeycode(0xf3));
    break;
  case MEDIA_next:
    sendControlKey("MEDIANEXT");
    Keyboard.write(KeyboardKeycode(0xeb));
    break;
  case MEDIA_previous:
    sendControlKey("MEDIAPREVIOUS");
    Keyboard.write(KeyboardKeycode(0xea));
    break;
  case MEDIA_volup:
    sendControlKey("VOLUME+,500");
    Keyboard.write(HID_KEYBOARD_VOLUME_DOWN);
    break;
  case MEDIA_voldn:
    sendControlKey("VOLUME-,500");
    Keyboard.write(HID_KEYBOARD_VOLUME_UP);
    break;
  // Send the key
  default:
    Serial.println(String(theKey, HEX));
    sendRawKey(modKeys, theKey);
    Keyboard.write(KeyboardKeycode(theKey));
    break;
  }

  modKeys = 0x00;
  Keyboard.releaseAll();
  mode = ALPHA;
  // Reset the modKeys and mode based on locks
  if (isCapsLocked) {
    modKeys = 0x02;
    Keyboard.press(KEY_LEFT_SHIFT);
  }
  if (isNumsymLocked) {
    mode = NUMSYM;
  }
}

void sendRawKey(char modKey, char rawKey){
    // Format for Bluefruit Feather is MOD-00-KEY.
    String keys = String(modKey, HEX) + "-00-" + String(rawKey, HEX);
    
    ble.print("AT+BLEKEYBOARDCODE=");
    ble.println(keys);
    // Must send this to release the keys.
    ble.println("AT+BLEKEYBOARDCODE=00-00");
}

void sendControlKey(String cntrlName){
  // note: for Volume +/- and the few other keys that take a time to hold, simply add it into the string
  // for example:
  //    sendControlKey("VOLUME+,500")
  // will send Volume up and hold it for half a second
  ble.print("AT+BLEHIDCONTROLKEY=");
  ble.println(cntrlName);  
}  
byte previousStableReading = 0;
byte currentStableReading = 0;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 10;    // the debounce time; increase if the output flickers

void processReading(){
    switch (state) {
    case PRESSING:
      if (previousStableReading & ~currentStableReading) {
        state = RELEASING;
        sendKey(previousStableReading);
      } 
      break;

    case RELEASING:
      if (currentStableReading & ~previousStableReading) {
        state = PRESSING;
      }
      break;
    }
}

void loop() {
  // Build the current key state.
  byte keyState = 0, mask = 1;
  for (int i = 0; i < 7; i++) {
    if (switch_pins[i].isDown()) keyState |= mask;
    mask <<= 1;
  }

  if (lastKeyState != keyState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    currentStableReading = keyState;
  }

  if (previousStableReading != currentStableReading) {
    processReading();
    previousStableReading = currentStableReading;
  }

  lastKeyState = keyState;
}
