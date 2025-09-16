#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Helper
{ 
public:
bool isAlpha(char c) 
{
  return (c>='A' && c<='Z') || (c>='a' && c<='z');
}
bool isUpper(char c) 
{
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
int getInput(string prompt, int minval, int maxval)
{
  int choice;
  while (true)
    {
      try
        {
          if (!prompt.empty())
          {
            cout << prompt;
          }
          if (cin >> choice && choice >= minVal && choice <= maxVal)
          {
            cin.ignore();
            return choice;
          }
          else
          {
            throw string("Invalid Input! Enter a number between " + to_string(minVal) +"and" + to_string(maxVal) + "\n");
          }
        }
        catch (const string &e)
        {
          cout << e;
          cin.clear();
          string bad;
          getline(cin, bad);
        }
    }
}

int stringToInt(cont string &s)
{
  try
    {
      if (s.empty())
      {
        throw string("Empty string");
      }
      int result = 0;
      int idx = 0;
      bool neg = false;
      if (s[0] == '-')
      {
        neg = true;
        idx = 1;
      }
      for (; idx < (int)s.length(); idx++)
        {
          char c = s[idx];
          if (c >= '0' && c <= '9')
          {
            result = result * 10 + (c - '0');
          }
          else
          {
            throw string("Invalid character in number");
          }
          return neg ? -result : result;            
        }
    }
      catch (const string &e)
        {
        return -1;
        }
}

string hexEncode (const string &in)
{
  const char hexDigits[] = "0123456789ABCDEF";
  string out;
  for (unsigned char c : in)
    {
      unsigned char hi = (c >> 4) & 0xF;
      out.push_back(hexDigits[hi]);
      out.push_back(hexDigits[lo]);
    }
  return out;
}

string hexDecode(const string &in)
{
  int n = in.length();
  if (n % 2 != 0)
  {
    return "";
  }
  string out;
  out.reserve(n / 2);
  for (int i = 0; i < n; i += 2)
    {
      char a = in[i];
      char b = in[i+1];
      int hi = hexCharToInt(a);
      int lo = hexCharToInt(b);
      if (hi == -1 || lo == -1)
      {
        return "";
      }
      char val = (char)((hi << 4) | lo);
      out.push_back(val);
    }
}
private:
int hexCharToInt(char c)
{
  if (c >= '0' && c<= '9')
  {
    return c- '0';
  }
  if (c >= 'A' && c <= 'F')
  {
    return 10 + (c - 'A');
  }
  if (c >= 'a' && c <= 'f')
  {
    return 10 + (c - 'a');
  }
  return -1;
}
friend class XORCipher;
};

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
string encrypt(){
return " ";
}
string decrypt(){
  return " ";
}
};

class  CaesarCipher: public Cipher{
int shift;
public:
CaesarCipher(int s = 3){
shift = s;
}
string encrypt(){
  Helper u;
  string r = "" "";
for(int i = 0; i < message.length(); i++){
char c = message{i};
if(u.isAlpha(c)){
char b = u.isUpper(c)? 'A': 'a';
r += char(((c-b+shift)%26)+b);
}
else r += c;
}
return r;
}
string decrypt(){
  Helper u;
string r = "" "";
for(int i = 0; i < message.length(); i++){
char c = message{i};
if(u.isAlpha(c)){
char b = u.isUpper(c)?'A': 'a';
r += char(((c - b - shift + 26) % 26) + b);
}
else r +=c;
}
return r;
}
};
