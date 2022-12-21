#include "lcs.h"
#include <string>
#include <vector>
#include <chrono>
#include <iostream>
using namespace std;

//naive 

string lcs(const string& s, const string& t){
  string sSub = "";
  string tSub = "";
  if(!s.empty())
    sSub = s.substr(1);
  if(!t.empty())
    tSub = t.substr(1);

  if(s.empty() || t.empty())
    return "";

  if(s[0] == t[0]){
    string firstOfS = "";
    firstOfS += s[0];
    firstOfS += lcs(sSub, tSub);
    return s[0] + lcs(sSub, tSub);
  }

  else
  {
    string a = lcs(sSub, t);
    string b = lcs(s, tSub);
    if(a.length() > b.length())
      return a;
    else
      return b;
  }
}

/*
//effective
string backtrack(int ** C, string first, string second, int i, int j)
{
    if (i == 0 || j == 0)
        return "";
    if (first[i-1] == second[j-1])
        return backtrack(C, first, second, i-1, j-1) + first[i - 1];
    if (C[i][j-1] > C[i-1][j])
        return backtrack(C, first, second, i, j-1);
    return backtrack(C, first, second, i-1, j);
}

string lcs(const string &first, const string &second) 
{
    int m = first.length();
    int n = second.length();

    int ** C;
    C = new int* [m+1];
    for (int i = 0; i < m + 1; i++)
        C[i] = new int[n+1];

    for (int i = 0; i < m + 1; i++)
        C[i][0] = 0;
    for (int j = 0; j < n + 1; j++)
        C[0][j] = 0;
    for (int i = 1; i < m + 1; i++)
        for (int j = 1; j < n + 1; j++)
            if (first[i-1] == second[j-1])
                C[i][j] = C[i-1][j-1] + 1;
            else
                C[i][j] = max(C[i][j-1], C[i-1][j]);
    return backtrack(C, first, second, m, n);
}
*/