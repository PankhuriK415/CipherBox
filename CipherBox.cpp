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
            throw string("Invalid Input! Enter a number between " + to_string(minVal) + " and "  + to_string(maxVal) + "\n");
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
        }  
          return neg? -result: result;            
        
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

string getCipherName(int cipherChoice)
{
    switch (cipherChoice)
    {
    case 1:
        return "Caesar Cipher";
    case 2:
        return "XOR Cipher";
    case 3:
        return "Substitution Cipher";
    case 4:
        return "Reverse Cipher";
    case 5:
        return "Atbash Cipher";
    case 6:
        return "ROT13 Cipher";
    case 7:
        return "Rail Fence Cipher";
    case 8:
        return "Vigenere Cipher";
    case 9:
        return "Affine Cipher";
    case 10:
        return "Base64 Cipher";
    default:
        return "Unknown Cipher";
    }
}

Cipher *createCipher(int choice, string keyInfo = "")
{
  Helper helper;
  try
    {
      switch(choice)
        {
          case 1 :
            {
              int shift = 0;
              if (!keyInfo.empty() && keyInfo.find("Shift=") == 0)
              shift = helper.stringToInt(keyInfo.substr(6));
              return new CaesarCipher(shift);
            }
          case 2 :
            {
              char key = 0;
              if (!keyInfo.empty() && keyInfo.find("Key=") == 0 && keyInfo.length() > 4)
              key = keyInfo[4];
              return new XORCipher(key);
            }
          case 3:
            {
              string key = "";
              if (!keyInfo.empty() && keyInfo.find("Key=") == 0)
              key = keyInfo.substr(4);
              return new SubstitutionCipher(key);
            }
          case 4 :
            {
              return new ReverseCipher();
            }
          case 5:
          {
            return new AtbashCipher();
          }
          case 6:
          {
            return new ROT13Cipher();
          }
          case 7:
            {
              int rails = 0;
            if (!keyInfo.empty() && keyInfo.find("Rails=") == 0)
                rails = helper.stringToInt(keyInfo.substr(6));
            return new RailFenceCipher(rails);
            }
          case 8:
            {
              string key = "";
            if (!keyInfo.empty() && keyInfo.find("Key=") == 0)
                key = keyInfo.substr(4);
            return new VigenereCipher(key);
            }
          case 9 :
            {
              int a = 0,b = 0;
              if (!keyInfo.empty() && keyInfo.find("a=") == 0)
            {
                int p = keyInfo.find(", b=");
                if (p != string::npos)
                {
                    a = helper.stringToInt(keyInfo.substr(2, p - 2));
                    b = helper.stringToInt(keyInfo.substr(p + 4));
                }
            }
            return new AffineCipher(a, b);
            }
          case 10:
          {
            return new Base64Cipher();
          }
          default :
          {
            throw string("Invalid cipher choice : "+ to_string(choice));
          }
        }
    }
      catch(const string &e)
        {
          cout << "Error creating cipher: " << e << "\n";
          return nullptr;
        }
}
int main()
{
    Helper helper;
    string text, username;

    cout << "===== CipherBox: Encryption-Decryption Framework =====\n";

    while (true)
    {
        try
        {
            int mainChoice = helper.getInput("Select action:\n1. Encrypt & store password\n2. Decrypt password\n3. Exit\nEnter choice: ", 1, 3);

            if (mainChoice == 3)
            {
                cout << "Exiting CipherBox. Goodbye!\n";
                break;
            }

            if (mainChoice == 1)
            {
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter text/password to encrypt: ";
                getline(cin, text);

                int cipherChoice = helper.getInput("\nChoose Cipher Method:\n 1. Caesar Cipher\n 2. XOR Cipher\n 3. Substitution Cipher\n 4. Reverse Cipher\n 5. Atbash Cipher\n 6. ROT13 Cipher\n 7. Rail Fence Cipher\n 8. Vigenere Cipher\n 9. Affine Cipher\n 10. Base64 Cipher\n 11. Multi-Encryption Cipher\n Enter choice: ", 1, 11);

            int nextSession = 1;
                try
                {
                    ifstream fin("data.txt");
                    if (fin.is_open())
                    {
                        string line;
                        int maxSession = 0;
                        while (getline(fin, line))
                        {
                            int p1 = line.find(';');
                            if (p1 == string::npos)
                                continue;
                          
                            int p2 = line.find(';', p1 + 1);
                            if (p2 == string::npos)
                                continue;
                          
                            string sessionStr = line.substr(p1 + 1, p2 - p1 - 1);
                            int sess = helper.stringToInt(sessionStr);
                            if (sess > maxSession)
                                maxSession = sess;
                        }
                      
                        fin.close();
                        nextSession = maxSession + 1;
                    }
                }
                  
                catch (const string &e)
                {
                    cout << "Error reading session data: " << e << "\n";
                    continue;
                }
              
                if (cipherChoice >= 1 && cipherChoice <= 10)
                {
                    Cipher *cipher = createCipher(cipherChoice);
                  
                    if (!cipher)
                        throw string("Failed to create cipher");
                    cipher->setMessage(text);
                    string encrypted = cipher->encrypt();

                    cout << "Step 1: Layer one encrypted using " << getCipherName(cipherChoice) << " | Key Info: " << cipher->getKeyInfo() << "\n";

                    ofstream fout("data.txt", ios::app);
                    if (!fout.is_open())
                        throw string("Unable to open data.txt for writing");
                  
                    fout << username << ";" << nextSession << ";1;" << cipherChoice << ";" << cipher->getKeyInfo() << ";" << encrypted << "\n";
                    fout.close();

                    cout << "Password stored successfully (session " << nextSession << ")\n";
                    delete cipher;
                }
                
                else if (cipherChoice == 11)

  
    return 0;
}
