// These cryptic lines prevent problems if someone
#ifndef HID_Charmap_h
// accidentally includes the library twice.
#define HID_Charmap_h

#include "Arduino.h" // Sketches automatically include this. Libraries do not.
#include "Keyboard.h"

class HID_Charmap
{
  public:
    HID_Charmap();
    
    // Example keypress: typeKey(KEY_LEFT_ARROW)
    void typeKey(int key, int _delay=5);
    
    // You must be tabbed in charmap.exe's char list
    void findChars(String str, int _delay=5);
    
    // Print string with using characters in clipboard
    //       print string, arrow delay
    void print(String str, int _delay=0);
    
    // Open charmap  
    //           Set font, Wait x millisecs after GUI+r, Delay after GUI+r
    void open(String _font="Arial", int _windowDelay=700, int _guiDelay=300);
    
    // Copy characters and close charmap
    //  use CTRL+A if characters are not selected (They are everytime but it can happen)
    void close(int _delay=5,bool _ctrlA=false);
    
    // Press GUI + key
    void GUI(char _key);
    // Press GUI + key
    void CTRL(char _key);
    
    void clearClipboard();
    
  private:
    // Keep track of a clipboard
    String _clipboard;
};


#endif