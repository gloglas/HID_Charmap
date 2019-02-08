
#include "Arduino.h"
#include "Keyboard.h"
#include "HID_Charmap.h"

HID_Charmap::HID_Charmap()
{
    String _clipboard = "";
}
void HID_Charmap::typeKey(int key, int _delay=5)
{
  Keyboard.press(key);
  delay(_delay);
  Keyboard.release(key);
}
void HID_Charmap::GUI(char _key)
{
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(_key);
  Keyboard.releaseAll();
}
void HID_Charmap::CTRL(char _key)
{
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(_key);
  Keyboard.releaseAll();
}
void HID_Charmap::findChars(String str, int _delay=5){
  // Actual position
  int _x = 0;
  int _y = 0;
  
  // Destination
  int _goX = 0;
  int _goY = 0;
  
  const char charMap[5][20] = {  
    {'!','"','#','$','%','&','\'','(',')','*','+',',','-','.','/','0','1','2','3','4'},
    {'5','6','7','8','9',':',';','<','=','>','?','@','A','B','C','D','E','F','G','H'},
    {'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','[','\\'},
    {']','^','_','`','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'},
    // UTF-8 characters are deleted. If you know how to write them via arduino, feel free to improve this.
    {'q','r','s','t','u','v','w','x','y','z','{','|','}','~','\0','\0','\0','\0','\0','\0'}//static_cast<char>(' '),static_cast<char>('¡'),static_cast<char>('¢'),static_cast<char>('£'),static_cast<char>('¤'),static_cast<char>('¥')}
  };
  
  //Let's go character by character
  for(unsigned int i=0; i < str.length(); i++){
    //Search only for chars that you can't type (Numbers,z,y) and don't add already pasted ones
    if(_clipboard.indexOf(str[i]) < 0){
      if( !isalpha(str[i]) || tolower(str[i]) == 'y' || tolower(str[i]) == 'z' ){
        //Find position of char by 2D array
        for(int jj = 0; jj < 5; jj++){
          for(int kk = 0; kk < 20; kk++){
            if(charMap[jj][kk] == str[i]){
              _goX = jj;
              _goY = kk;
            }
          }
        }
        //Calculate steps
        int _timesX = (_x - _goX);
        int _timesY = (_y - _goY);
      
        //Get directions and move
        if( _timesX > 0) {
          for(int iii=0; iii < _timesX;iii++)
          {
            typeKey(KEY_UP_ARROW);
            delay(_delay);
          }
        }
        else if( _timesX < 0) {
          for(int iii=0; iii < -1*_timesX;iii++)
          {
            typeKey(KEY_DOWN_ARROW);
            delay(_delay);
          }
        }
          
        if( _timesY < 0) {
          for(int iii=0; iii < -1*_timesY;iii++)
          {
            typeKey(KEY_RIGHT_ARROW);
            delay(_delay);
          }
        }
        else if( _timesY > 0){
          for(int iii=0; iii < _timesY;iii++)
          {
            typeKey(KEY_LEFT_ARROW);
            delay(_delay);
          }
        }
     
        // Set a new position
        _x = _goX;
        _y = _goY;

        // Select a character
        typeKey(KEY_RETURN);

        // Add character to overview
        _clipboard += str[i];
      }
    }
  }
}
void HID_Charmap::print(String str, int _delay=0){
  for(unsigned int i=0; i < str.length(); i++){
    
    //If character is not present in clipboard write it otherwise do clippy thing.
    if( _clipboard.indexOf(str[i]) < 0)
      Keyboard.write(str[i]);
    else
    {
      //Paste clipboard
      CTRL('v');
      delay(_delay);

      // Delete after the character
      for(unsigned int j=0; j < _clipboard.length()-_clipboard.indexOf(str[i])-1; j++)
        typeKey(KEY_BACKSPACE);

      // Get before the character
      typeKey(KEY_LEFT_ARROW);

      // Clear mess
      for(signed int j=0; j < _clipboard.indexOf(str[i]); j++)
        typeKey(KEY_BACKSPACE);

      // Continue typing after character
      typeKey(KEY_RIGHT_ARROW); 
    }
    
  }
}
void HID_Charmap::open(String _font="aaa",int _windowDelay=700,int _guiDelay=300)
{
    GUI('r');
    delay(_guiDelay);
    
    // remove .exe to be even faster!
    Keyboard.print("charmap.exe");
    typeKey(KEY_RETURN);
    delay(_windowDelay);
    // Set font to Arial (or 6x 's' to Segoe UI)
    Keyboard.print(_font);

    // Navigate to the list
    typeKey(KEY_TAB);
    typeKey(KEY_TAB);
}
void HID_Charmap::close(int _delay=5,bool _ctrlA=false)
{
    // Copy characters first
    typeKey(KEY_TAB);
    delay(_delay);
    // remove CTRL+A to go even faster!
    if(_ctrlA){
      CTRL('a');
      delay(_delay);
    }
    
    CTRL('c');
    delay(_delay);
    
    // Then close charmap
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F4);
    Keyboard.releaseAll();
}
void HID_Charmap::clearClipboard()
{
  typeKey(' ');
  
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ARROW);
  Keyboard.releaseAll();

  CTRL('x');
}