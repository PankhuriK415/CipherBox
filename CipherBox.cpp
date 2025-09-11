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
  return (c>='A' && c<='z');
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
  


