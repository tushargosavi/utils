#include <iostream>
#include <map>
#include <algorithm>
#include <sequtils.h>

using namespace std;

typedef map<string, float> StringFloatMap;


void print_stocks(StringFloatMap &stocks)
{
  StringFloatMap::iterator pos;
  for (pos = stocks.begin(); pos != stocks.end(); ++pos)
    cout << "stock : " << pos->first << "\t\t"
	 << "price : " << pos->second << endl;
  cout << endl;  
}

int main(int argc, char *argv[])
{
  StringFloatMap stocks;
  
  stocks["BASF"] = 369.0;
  stocks["VW"] = 413.50;
  stocks["Daimeler"] = 819.00;
  stocks["BMW"] = 834.00;
  stocks["Siemense"] = 842.20;
  print_stocks(stocks);

  StringFloatMap::iterator pos;
  for (pos = stocks.begin(); pos != stocks.end(); ++pos)
    pos->second *= 2;
  print_stocks(stocks);

  stocks["Volkswagan"] = stocks["VW"];
  stocks.erase("VW");
  print_stocks(stocks);

  return 0;
}
