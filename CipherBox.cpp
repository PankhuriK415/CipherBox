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
int getInput(string prompt, int minVal, int maxVal)
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

int stringToInt(const string &s)
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
      for (idx = 1; idx < (int)s.length(); idx++)
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
      unsigned char lo = c & 0xF;
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
  return out;
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
void setMessage(string msg){
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
  return "Shift=" + to_string(shift);
}
};

class SubstitutionCipher: public Cipher
{
  string key;
  Helper helper;

public:
  SubstitutionCipher(string k = ""):
key(k)
{
  if(k.empty())
    key = "QWERTYUIOPASDFGHJKLZXCVBNM";
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

class XORCipher : public Cipher {
char key;
Helper helper;
public:
XORCipher(char k=0){
  key = k;
if (k==0)
{
try{
cout << "Enter a single character key XOR Cipher:";
if (!(cin>>key)) {
throw string("Invalid character input for XOR key");
}
cin.ignore();
}
  catch (const string &e) {
cout<< "Error:" << e <<".Using default key 'K' \n";
key='K';
  }
}
}
string encrypt () {
  string tmp = "";
for (unsigned char c : message) {
  tmp.push_back((char)(c^key));
}
return helper.hexEncode(tmp);
}
string decrypt () {
  string decoded = helper.hexDecode(message);
if (decoded.empty() && !message.empty()) {
  return "[XOR:Invalid hex data]";
    }
string out ="";
for (unsigned char c : decoded)
  out.push_back((char)(c^key));
return out;
}
string getKeyInfo()
{
  string s= "";
s += key;
return "Key=" + s;
}
};
int main()
{
  Helper helper;
cout << "Cipher Program\n";
string msg;
cout << " Enter the message:";
getline(cin,msg);
cout << "\n Choose a cipher:\n" << "1. Caesar Cipher\n" << "2.XOR Cipher\n" << "3.Substitution Cipher\n";
int choice = helper.getInput("Enter choice:", 1, 3);

Cipher *cipher = nullptr;
switch (choice) {
    case 1:
{
int shift = helper.getInput("Enter shift for Caesar Cipher (1-25, 0 for prompt): ", 0, 25);
cipher = new CaesarCipher(shift);
break;
}
    case 2:
{
char key;
cout << "Enter single character key for XOR Cipher";
if (!(cin>>key)) {
key=0;
cin.clear();
}
cin.ignore();
cipher = new XORCipher(key);
break;
}
  case 3:
    {
      string key;
      cout <<"Enter 26-letter key for Substitution Cipher (leave empty for default): ";
      getline(cin,key);
      cipher = new SubstitutionCipher(key);
      break;
    }
    }
cipher -> setMessage(msg);

string encrypted = cipher -> encrypt();
string decrypted = cipher -> decrypt();
cout << "\nOriginal Message:" << msg <<"\n" << "Encrypted Message:" << encrypted << "\n" << "Decrypted Message:" << decrypted << "\n" << "Cipher Key Info:" << cipher -> getKeyInfo() << "\n";
delete cipher;
return 0;
}
class ReserveCipher : public Cipher {
Helper helper;
public:
string encrypt() {
  string r = message;
helper.reverseString(r);
return r;
}
string decrypt() {
  return encrypt();
}
};

