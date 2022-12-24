#include <iostream>
#include <vector>

using namespace std;
int policeThief(char arr[], int n, int k)
{
  int res = 0;
  vector<int> thi;
  vector<int> pol;
 
  // store indices in the vector
  for (int i = 0; i < n; i++) {
    if (arr[i] == 'P')
      pol.push_back(i);
    else if (arr[i] == 'T')
      thi.push_back(i);
  }
 
  // track lowest current indices of
  // thief: thi[l], police: pol[r]
  int l = 0, r = 0;
  while (l < thi.size() && r < pol.size()) {
    // can be caught
    if (abs(thi[l] - pol[r]) <= k){
      l++;
      r++;
      res++;
    }
    //can't be caught
    // thief is behind the police(look for next thief)
    else if (thi[l] < pol[r]){
      l++;
    }
    //thief is infront of police(look for next police)
    else{
      r++;
    }
  }
  return res;
}
 
int main()
{
  int k, n;
  char arr1[] = { 'P', 'T', 'T', 'P', 'T' };
  k = 1;
  n = sizeof(arr1) / sizeof(char);
  cout << "Maximum thieves caught: " << policeThief(arr1, n, k) << endl;
 
  char arr2[] = { 'T', 'T', 'P', 'P', 'T', 'P' };
  k = 2;
  n = sizeof(arr2) / sizeof(char);
  cout << "Maximum thieves caught: " << policeThief(arr2, n, k) << endl;
 
  return 0;
}