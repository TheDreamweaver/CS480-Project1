#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> suffixRank(vector<int> perm) {
// take a perm as input and outputs suffixRank vector
// Example: < 5 1 4 2 3 > output = < 5 1 3 1 1 >, e.g., rank of 4 in suffix <4 2 3> is 3 etc.
    vector<int> srank; 
    for (int j = 0; j < perm.size(); j++) {
       int max = perm[j]; int count = 1;
       for (int k = j+1; k < perm.size(); k++)
         if (perm[j] > perm[k])
             count++;
       srank.push_back(count);
       // cout << srank[j] << endl;
   }
  return srank;
}

int fact(int j) {
  // computes j!
  int out = 1;
  if ((j == 0) || (j == 1))
   return out;
  for (int k = 2; k <= j; k++)
    out *= k;
  return out;
}

int permToInt( vector<int> perm) {
  // maps a given perm to its index in lexicographic order
   vector<int> srank = suffixRank(perm);
   int out = 0; int n = perm.size();
   for (int j = 0; j < n; j++)
     out += (srank[j]-1)*fact(n-j-1);
   return out;
}

vector<int> update(vector<int> perm, int j) {
 // updates a vector by incrementing all entries that are >= j
 // e.g. update( < 5 1 2 4 3 >, 3) will return < 6 1 2 5 4 > 
 int n = perm.size(); vector<int> temp;
 for (int i = 0; i < n; i++)
   if (perm[i] < j)
     temp.push_back(perm[i]);
   else
     temp.push_back(perm[i]+1);
 return temp;
}

vector<int> intToPerm(int n, int m) {
  // inverse of permToInt function. This function takes the lexical index n as well as the size of the permutation m
  vector<int> temp;
  if (m == 1) {
      vector<int> one{1};
      return one;
   };
  int fst = n / fact(m-1);
  temp = intToPerm(n - fst*fact(m-1), m-1);
  vector<int> temp1;
  temp1.push_back(fst+1);
  temp = update(temp, fst+1);
  for (int k = 0; k < temp.size(); k++)
   temp1.push_back(temp[k]);
  return temp1;
}

bool goalState(vector<int> perm){
    int temp = perm[0];
    for(int i = 1; i < perm.size(); i++){
        if(perm[i] < temp)
            return false;
        temp = perm[i];
    }
    return true;
}

vector<vector<int>> getNeighbors(vector<int> node, vector<int> &parent){
    vector<vector<int>> neighbors;
    size = node.size();
    while(size > 2){
        for(int i = 0; (i + size-1) < node.size(); i++){
            vector<int> temp(node);
            for(int j = 0, int k = j + size-1; j < k; j++, k--)
                swap(temp[i+j], temp[i+k]);
            if(permToint(temp) != parent[permToint(node)])
                neighbors.push_back(temp);
        }
        size--;
    }
    return neighbors;
}