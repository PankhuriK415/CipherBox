#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Helper
{ 
public:
bool isAlpha(char c) {
  return (c>='A' && c<='Z') || (c>='a' && c<='z');
}
bool isUpper(char c) {
  return (c>='A' && c<='Z');
}
char toUpper (char c)
{
  if (c>='a' && c<='z')
    return c-'a'+'A';
return c;
}
char toLower(char c)
{
  if (c>='A' && c<='Z')
    return c-'A'+'a';
return c;
}
string cleanText(string yext,bool toUpperFlag = true)
{
  string result = "";
  for(int i = 0; i < text.length(); i++)
    {
      char c = text[i];
      if(isAlpha(c))
          result += toUpperFlag ?
    toUpper(c) : c;
    }
  return result;
}

bool isCoprimeWith26(int a)
{
  int x = a,y =26;
  while( y != 0)
    {
      int temp = x % y;
      x = y;
      y = temp;
    }
  return (x==1);
}
void reverseString (string &s)
{
  int n = s.length();
for (int i = 0; i < n/2; i++)
{
char temp = s[i];
s[i] = s[n-i-1];
s[n-i-1] =temp;
}
}
int getInput(string prompt, int minval. int maxval)
{
  int choice;
while (true)
{
cout << prompt;
if (cin >> choice && choice >= minval && choice <= maxval)
{
return choice;
}
else
{
cin.clear();
string badInput;
cin >> badInput;
cout << "Invalid Input!! Enter a number between " << minval << "and" << maxval << "\n";
}
}
}
class Cipher{
protected:
string message;

public:
void setmessage(string msg){
  message = msg;
}

string getmessage(){
  return message;
}
virtual string encrypt() = 0;
virtual string decrypt() = 0;
virtual string getKeyInfo(){
  return " ";
}
virtual ~Cipher(){}
};

class  CaesarCipher: public Cipher{
int shift;
Helper helper;
public:
CaesarCipher(int s = 0) : shift(s){
  if(s == 0){
    try{
      shift = helper.getInput("Enter shift value for Caesar Cipher (1-25) :", 1, 25);
    }
    catch (const string &e){
      cout << "Error setting shift: " << e << "\n";
      shift = 1;
    }
  }
}
string encrypt(){
  string r = "" "";
for(char c : message){
if(helper.isAlpha(c)){
char b = helper.isUpper(c)? 'A': 'a';
r += char(((c-b+shift)%26)+b);
}
else r += c;
}
return r;
}
string decrypt(){
string r = "" "";
for(char c : message){
if(helper.isAlpha(c)){
char b = helper.isUpper(c)?'A': 'a';
r += char(((c - b - shift + 26) % 26) + b);
}
else r +=c;
}
return r;
}
string getKeyInfo(){
  return "Shift=" + to -string(shift);
}
};

class SubstitutionCipher : public Cipher
{
  string key;
  Helper helper;

public:
  SubstitutionCipher(string k = ""):
key(k)
{
  if(k.empty())
    key = "QWERTYUIOPASDFGHJKLZXCVBNM"
}
string encrypt()
{
  string r = "";
  for(char  c : message)
    {
      if (helper.isUpper(c))
                r += key[c - 'A'];
      else if (helper.isAlpha(c))
                r += helper.toLower(key[c - 'a']);
       else
                r += c;

    }
    return r;
}
string decrypt()
{
  string r = "";
  for (char c : message)
    {
      if(helper.isUpper(c))
      {
         for (int j = 0; j < 26; j++)
                    if (key[j] == c)
                    {
                        r += 'A' + j;
                        break;
                    }

      }
   else if (helper.isAlpha(c))
   {
     for(int j = 0; j < 26;j++)
       {
          if(helper.toLower(key[j]) == c)
         {
         r+= 'a' + j;
         break;
         }
       }
      
   }
      else
      r+= c;
    }
  return r;
}
string getKeyInfo()
{
  return "Key= " + key;
}
};

