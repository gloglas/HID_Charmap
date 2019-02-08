# HID_Charmap arduino library
Less problems with layouts!
<!-- WIP don't judge. English is my foreign language -->
## Why I did it?
If you have ever written a script you have experienced problems with different keyboard layouts.
It's pain especially on windows where they can be switched (with ALT-SHIFT), but you never know what windows decides to do or how many layouts are there. So I was like hmm... let's use this in powershell
```powershell
Set-WinUserLanguageList -LanguageList en-US -Force
```  
But it has a few problems...
1. It doesn't work on Windows 7.
2. You can't write it 'cause of layout problem.
3. You will mess up user settings.

Charmap's layout is still same... so we can use that to get special characters that we need to the clipboard and when it's time to use them you just paste the whole clipboard and delete characters that you don't need.
1. Longer execution time (tweak delays for yourself)
2. You will use/clear clipboard
3. But special characters will work! 
## Usage
### Open charmap
```c++
void open(String _font="aaa", int _windowDelay=700, int _guiDelay=300);
```
First you need to open a charmap. Simply by pressing **GUI+r** (third argument is delay for Run to show) and typing **charmap.exe**.  
Then second argument specifies how long will program wait for charmap to show up.  
After that it will press 'a' 3 times to set usable font and 2x **TAB** to character field.
### Find characters
```c++
void findChars(String str, int _delay=5);
```
When you are in character field and you are able to move with arrows, you need to find characters that you will need. 
I made 2D array with first 5 most important rows of characters from charmap.exe. Function will go through string char by char.  
If character is not a letter it will try to find it in array. After that it will use array indexes to navigate in charmap.exe itself.  
Delay is in this case for arrows.  
### Obtain characters and close charmap
```c++
void close(int _delay=5,bool _ctrlA=false);
```
TAB in to character field. If _ctrlA is true it will press that combination to select characters but it is unnecessary.  
Then it will copy and close charmap (CTRL+c, ALT+F4)  
Delay is after every shortcut.  
### Print using clipboard
```c++
void print(String str, int _delay=0);
```
Print function will go character by character, if the character is in clipboard it will paste whole clipboard and with help of indexes it will delete useless characters.
### Extra functions
```c++
//Type key, hold delay.
   void typeKey(int key, int _delay=5);

//Self explanatory
   void clearClipboard();

//Press GUI + key
   void GUI(char _key);

//Press GUI + key
   void CTRL(char _key);
```
