#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Helper
{ 
public:
inline bool isAlpha(char c) 
{
  return (c>='A' && c<='Z') || (c>='a' && c<='z');
}
inline bool isUpper(char c) 
{
  return (c>='A' && c<='Z');
}
inline char toUpper (char c)
{
  return (c >= 'a' && c <= 'z') ? c - 'a' + 'A' : c;
}
inline char toLower(char c)
{
  return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
}
void reverseString(string &s)
    {
        int n = s.length();
        for (int i = 0; i < n / 2; i++)
        {
            char temp = s[i];
            s[i] = s[n - i - 1];
            s[n - i - 1] = temp;
        }
    }
void reverseString(string &s, int start, int end)
    {
        if (start < 0)
            start = 0;
        if (end > (int)s.size())
            end = s.size();

        while (start < end)
        {
            char temp = s[start];
            s[start] = s[end - 1];
            s[end - 1] = temp;
            start++;
            end--;
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
int getInput (string prompt)
{
        int value;
        cout << prompt;
        while (!(cin >> value))
        {
            cout << "Invalid input! Enter a number again: ";
            cin.clear();
            cin.ignore(100, '\n');
        }
        cin.ignore();
        return value;
    }
float getInput(string prompt, float minVal, float maxVal)
    {
        float choice;
        while (true)
        {
            cout << prompt;
            if (cin >> choice && choice >= minVal && choice <= maxVal)
            {
                cin.ignore();
                return choice;
            }
            else
            {
                cout << "Invalid input! Enter a value between " << minVal << " and " << maxVal << ".\n";
                cin.clear();
                cin.ignore(100, '\n');
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
  string r = " ";
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

class ReverseCipher : public Cipher {
Helper helper;
public:
inline string encrypt() {
  string r = message;
helper.reverseString(r);
return r;
}
inline string decrypt() {
  return encrypt();
}
string operator~() {
    string r = message;
    helper.reverseString(r);
    return r;
}
};

class AtbashCipher: public Cipher{
Helper helper;
public:
string encrypt(){
  string r = "";
for(char c : message){
  if(helper.isUpper(c)){
    r += 'Z' - (c - 'A');
  }
  else if(helper.isAlpha(c)){
    r += 'z' - (c - 'a');
  }
  else{
    r += c;
  }
return r;
}
string decrypt(){
  return encrypt();
}
};
class ROT13Cipher : public Cipher
{
Helper helper;
public: 
string encrypt()
{
  string r = "";
  for (char c: message)
{
if (helper.isAlpha(c))
{
char b = helper.isUpper(c) ? 'A' : 'a';
r += ((c-b + 13) % 26 +b);
}
  else 
{
  r += c;
} 
}
return r;
}
string decrypt () 
{
    return encrypt();
}
};
  
class RailFenceCipher : public Cipher
{
  int rails;
  Helper helper;

public:
  RailFenceCipher(int r = 0) : rails(r)
{
  if(r == 0)
  {
    try{
      rails = helper.getInput("Enter number of rails of Rail Fence Cipher(2-10) : ",2,10);
    }
      catch(const string &e)
      {
        cout << "Error setting rails :" << e << ". Using default 2\n";
        rails = 2;
      }
  }
}

string encrypt()
{
  if (rails <= 1)
    return message;
  int len = message.length();
  char **mat = new char *[rails];

  for(int i = 0; i < rails; i++)
    {
       mat[i] = new char[len];
           for (int j = 0; j < len; j++)
               mat[i][j] = 0; 
    }
  int row = 0,dir = 1;
  for(int i = 0; i < len; i++)
    {
      mat[row][i] = message[i];
            if (row == 0)
                dir = 1;
            else if (row == rails - 1)
                dir = -1;
            row += dir;
    }
  string r = " ";
  for(int i = 0; i < rails;i++)
    for(int j = 0;j < len;j++)
      if(mat[i][j] != 0)
        r += mat[i][j];

  for(int i = 0; i < rails; i++)
    delete[] mat[i];
  delete[] mat;
  return  r;
}

string decrypt()
{
  if (rails <= 1)
    return message;
  int len = message.length();
  char **mat = new char *[rails];
  bool **mark = new bool *[rails];

  for(int i = 0; i < rails; i++)
    {
      mat[i] new char[len];
      mark[i] = new bool[len];
      for(int j = 0;j < len;j++)
        {
          mat[i][j] = 0;
          mark[i][j] = false;
        }
        
    }
  int rows = 0,dir = 1;
  for(int i = 0; i < len; i++)
    {
       mark[row][i] = true;
            if (row == 0)
                dir = 1;
            else if (row == rails - 1)
                dir = -1;
            row += dir;
    }
  int idx = 0;
  for(int i = 0; i  < raild; i++)
    for(int j = 0; j < len; j++)
      if(mark[i][j] && idx < len)
        mat[i][j] = message[idx++];
  string r ="";
  row = 0;
  dir = 1;
  for(int i = 0; i < len; i++)
    {
       r += mat[row][i];
            if (row == 0)
                dir = 1;
            else if (row == rails - 1)
                dir = -1;
            row += dir;
    }

  for (int i = 0; i <rails; i++)
    {
      delete[] mat[i];
      delete[] mark[i];
    }
  delete[] mat;
        delete[] mark;
        return r;
}

string getKeyInfo()
{
  return "Rails = "+ to_string(rails);
}
};

class VigenereCipher : public Cipher {
string key;
Helper helper;

public:
VigenereCipher(string k = "") : key(k) 
{
if (k.empty())
{
try
{
cout << "Enter key for Vigenere Cipher:";
getline(cin, key);
if (key.empty())
  throw string ("Empty key not allowed");
}
  catch (const string &e)
{
cout << "Error:" << e << ". Using default key 'KEY'\n";
key = "KEY";
}
}
}
string encrypt()
{
string r = "";
int j = 0;
for (char c : message)
{
if (helper.isAlpha(c))
{
char b = helper.isUpper(c) ? 'A' : 'a';
char k = helper.toUpper(key[j % key.length()]) - 'A';
r += ((c - b + k) % 26 + b);
j++;
}
else
r += c;
}
return r;
}
string decrypt()
{
string r = "";
int j = 0;
for (char c : message)
{
if (helper.isAlpha(c))
{
char b = helper.isUpper(c) ? 'A' : 'a';
char k = helper.toUpper(key[j % key.length()]) - 'A';
r += ((c - b - k + 26) % 26 + b);
j++;
}
else
r += c;
}
return r;
}
string getkeyinfo()
{
return "KEY=" + key;
}
};

class AffineCipher : public Cipher
{
int a, b;
Helper helper;
public
AffineCipher(int x = 0, int y = 0): a(x), b(y)
{
if (x==0)
{
try 
{
cout << "Enter key 'a' (coprime with 26) for Affine Cipher: ";
if (!(cin >> a))
{
throw string("Invalid input for 'a'");
}
int x=a, y2=26;
while (y2 != 0)
{
int t=x%y2;
x=y2;
y2=t;
}
if (x!=1)
{
throw string("Key 'a' must be coprime with 26");
}
cout << "Enter key 'b'(0-25) for Affine Cipher:";
if(!(cin >> b) || b<0 || b> 25)
{
throw string("Invalid 'b'. Must be between 0 and 25");
}
cin.ignore();
}
catch (const string &e)
{
cout << "Error: " << e << ". Using default a=5, b=8\n";
a = 5;
b = 8;
}
}
}
int modInverse(int x)
{
for (int i = 1; i < 26; i++)
if ((x * i) % 26 == 1)
{
return i;
}
return -1;
}
string encrypt()
{
string r = "";
for (char c : message)
{
if (helper.isAlpha(c))
{
char base = helper.isUpper(c) ? 'A' : 'a';
r += ((a * (c - base) + b) % 26 + base);
}
else
{
r += c;
}
}
return r;
}
string decrypt()
{
string r = "";
int inv = modInverse(a);
if (inv == -1)
{
return "[Affine: no modular inverse for a=" + to_string(a) + "]";
}
for (char c : message)
{
if (helper.isAlpha(c))
{
char base = helper.isUpper(c) ? 'A' : 'a';
r += ((inv * ((c - base - b + 26) % 26)) % 26 + base);
}
else
{
r += c;
}
}
return r;
}
string getKeyInfo()
{
return "a=" + to_string(a) + ", b=" + to_string(b);
}
};


int main() {
Helper helper;
cout << "Cipher Program\n";
string msg;
cout << " Enter the message:";
getline(cin,msg);
cout << "\n Choose a cipher:\n" << "1. Caesar Cipher\n" << "2.XOR Cipher\n" << "3.Substitution Cipher\n" << "4. Reverse Cipher\n" << "5. Atbash Cipher\n" << "6.ROT13 Cipher\n";
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
  case 4:
    {
   cipher = new ReverseCipher();
      break;
    }
  case 5:
    { cipher = new AtbashCipher();
     break;
    }
  case 6: 
    { cipher = new ROT13Cipher();
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
