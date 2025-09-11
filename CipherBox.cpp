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
    









