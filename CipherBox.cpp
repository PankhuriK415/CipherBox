#include <iostream>
#include <string>
#include <limits>

using namespace std;























void reversestrng (string &s)
{
  int n = s.length() ;
  for (int i = 0; i < n/2; i++)
  {
     char temp = s[i];
s[i] = s[n - i - 1];
s[n - i - 1] = temp;
  }
}

int getinput (string prompt, int minval, int maxval)
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
cin.clear ();
string badInput;
cin >> badInput;
cout<< " Invalid Input!! Enter a number between" << minval << " and" << maxval << "\n";
}
}
}

