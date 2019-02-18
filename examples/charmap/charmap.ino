#include <HID_Charmap.h>
// Made by gloglas
// https://github.com/gloglas/HID_Charmap

// Read source code to make better performance improvments
// I included first 5 rows of charmap.
HID_Charmap charmap;
String payload = "1a&2b3&z^#";

void setup()
{
  Keyboard.begin();
  delay(5000);
  
  // Open charmap.exe and TAB to character field.
  // Set font, wait for charmap window, wait for run window
  charmap.open("Arial",700,300);
  
  // It will find special characters in string
  // and find them in charmap field.
  // If you specify only needed characters it will be faster
  charmap.findChars(payload,0);
  
  // Copy characters and close charmap
  //    int delay, bool useCtrl+A? (to select a text)
  charmap.close(0);
  
  // Do something shady
  charmap.GUI('r');
  delay(150);
  // Like open a notepad
  Keyboard.print("notepad");
  
  charmap.typeKey(KEY_RETURN);
  delay(300);
  charmap.print(payload);
  charmap.clearClipboard();
}

void loop(){}
