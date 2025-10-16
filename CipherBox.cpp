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
          return neg? -result: result;            
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
  for (unsigned char c: in)
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
string r = "";
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
  for (char c: message)
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


class XORCipher: public Cipher {
char key;
Helper helper;
public:
XORCipher(char k=0){
  key = k;
if (k==0)
{
try{
cout << "Enter a single alphabet key XOR Cipher:";
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
for (unsigned char c: decoded)
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


class ReverseCipher: public Cipher {
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
char b = helper.isUpper(c) ? 'A': 'a';
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


class RailFenceCipher: public Cipher
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
      mat[i] = new char[len];
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
       mark[rows][i] = true;
            if (rows == 0)
                dir = 1;
            else if (rows == rails - 1)
                dir = -1;
            rows += dir;
    }
  int idx = 0;
  for(int i = 0; i  < rails; i++)
    for(int j = 0; j < len; j++)
      if(mark[i][j] && idx < len)
        mat[i][j] = message[idx++];
  string r ="";
  rows = 0;
  dir = 1;
  for(int i = 0; i < len; i++)
    {
       r += mat[rows][i];
            if (rows == 0)
                dir = 1;
            else if (rows == rails - 1)
                dir = -1;
            rows += dir;
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


class Base64Cipher : public Cipher{
string base64_chars;

public:
Base64Cipher(){
base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
}
string encrypt(){
string r = "";
int val = 0, valb = -6;
for(unsigned char c : message){
val = (val << 8) + c;
valb +=8;
while(valb >= 0){
r += base64_chars[(val >> valb) & 63];
valb -= 6;
}
}
if(valb > -6)
  r += base64_chars[((val << 8) >> (valb + 8)) &63];
while(r.length() % 4)
  r += '=';
return r;
}
string decrypt(){
int T[256];
  for (int i = 0; i<256; i++)
    T[i] = -1;
  for(int i = 0; i<64; i++)
    T[(unsigned char)base64_chars[i]] = i;
  string r = "";
  int val = 0, valb = -8;
  for(char c : message){
    if(c == '=')
      break;
    if(T[(unsigned char)c] == -1)
      continue;
    val = (val << 6) + T[(unsigned char)c];
    valb +=6;
    if(valb >= 0){
      r += char((val >> valb) & 255);
      valb -= 8;
    }
  }
  return r;
}
string getKeyInfo(){
  return "Base64";
}
};


class VigenereCipher: public Cipher {
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
for (char c: message)
{
if (helper.isAlpha(c))
{
char b = helper.isUpper(c) ? 'A': 'a';
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
for (char c: message)
{
if (helper.isAlpha(c))
{
char b = helper.isUpper(c) ? 'A': 'a';
char k = helper.toUpper(key[j % key.length()]) - 'A';
r += ((c - b - k + 26) % 26 + b);
j++;
}
else
r += c;
}
return r;
}
string getKeyInfo()
{
return "KEY=" + key;
}
};


class AffineCipher: public Cipher
{
int a, b;
Helper helper;
public : 
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
for (char c: message)
{
if (helper.isAlpha(c))
{
char base = helper.isUpper(c) ? 'A': 'a';
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
for (char c: message)
{
if (helper.isAlpha(c))
{
char base = helper.isUpper(c) ? 'A': 'a';
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


int main()
{
    Helper helper;
    int choiceCipher;
    string msg;

    cout << "-----CipherBox-----\n";

    cout << "Available Ciphers:\n";
    cout << "1. Caesar Cipher\n2. Substitution Cipher\n3. XOR Cipher\n4. Reverse Cipher\n5. Atbash Cipher\n6. ROT13 Cipher\n7. Rail Fence Cipher\n8. Vigenere Cipher\n9. Affine Cipher\n10. Base64 Cipher\n";
   
    choiceCipher = helper.getInput("Select a cipher (1-10): ", 1, 10);

    Cipher* cipher = nullptr;
    switch (choiceCipher)
    {
        case 1: cipher = new CaesarCipher(); 
          break;
        case 2: cipher = new SubstitutionCipher(); 
          break;
        case 3: cipher = new XORCipher(); 
          break;
        case 4: cipher = new ReverseCipher(); 
          break;
        case 5: cipher = new AtbashCipher(); 
          break;
        case 6: cipher = new ROT13Cipher(); 
          break;
        case 7: cipher = new RailFenceCipher(); 
          break;
        case 8: cipher = new VigenereCipher(); 
          break;
        case 9: cipher = new AffineCipher(); 
          break;
        case 10: cipher = new Base64Cipher(); 
          break;
        default: cout << "Invalid choice!\n"; 
          return 0;
    }

    int option;
    do
    {
        cout << "\nChoose an option:\n1. Encrypt message\n2. Decrypt message\n3. Exit\n";
        option = helper.getInput("Your choice: ", 1, 3);

        switch (option)
        {
            case 1:
                cout << "Enter message to encrypt: ";
                getline(cin, msg);
                cipher->setMessage(msg);
                cout << "\nEncrypted Message: " << cipher->encrypt() << "\n";
                cout << "Key Info: " << cipher->getKeyInfo() << "\n";
                break;
            case 2:
                cout << "Enter message to decrypt: ";
                getline(cin, msg);
                cipher->setMessage(msg);
                cout << "\nDecrypted Message: " << cipher->decrypt() << "\n";
                cout << "Key Info: " << cipher->getKeyInfo() << "\n";
                break;
            case 3:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid option!\n";
        }

    } while (option != 3);

    delete cipher;
    cout << "\n------Exiting------\n";

    return 0;
}
