#include <iostream>
#include <string>

using namespace std;

inline int min(int a, int b) {
  return (a>b)? b : a;
}

int edit_dist(string &str1, string &str2) {
  int n1 = str1.size();
  int n2 = str2.size();

  int d[str1.size()][str2.size()];

  for(int i = 0; i <= n2; i++) d[0][i] = i;
  for(int i = 0; i <= n1; i++) d[i][0] = i;
  
  for(int i = 1; i <= n1; i++) {
    for(int j = 1; j <= n2; j++) {
      d[i][j] = min(d[i-1][j] + 1, d[i][j-1] + 1);
      d[i][j] = min(d[i][j], (d[i-1][j-1] + (str1[i-1] != str2[j-1])));
    }
  }

  return d[n1][n2];
}

int main(int argc, char **argv) {
  string str1;
  string str2;

  cin >> str1;
  cin >> str2;

  int dist = edit_dist(str1, str2);
  cout << dist << endl;
  return 0;
}

