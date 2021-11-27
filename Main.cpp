#include <bits/stdc++.h>
using namespace std;

int sheesh(int a[], int n);
void unsheesh(int a[], int i, int n);
void printPerm(int a[], int n);
void mult(int a[], int b[], int c[], int n);
int multSheesh(int sheesha, int sheeshb, int n);

const int MAX_N = 8;
const int MAX_LEN = 8*7*6*5*4*3*2;

int main() {
  bool a[MAX_LEN];
  int n;
  cout << "n = ";
  cin >> n;
  int len = 1;
  for(int i=1; i<=n; i++)
    len *= i;
  memset(a, false, MAX_LEN);
  int m;
  cout << "Сколько порождающих элементов дано? ";
  cin >> m;
  cout << "Введите их: \n";
  for(int i=0; i<m; i++) {
    cout << "Введите очередной элемент: \n";
    int tmpel[MAX_N];
    for(int j=0; j<n; j++) {
      cin >> tmpel[j];
      tmpel[j]--;
    }
    cout << "Его представление в виде независимых циклов: \n";
    int tmph1 = sheesh(tmpel, n);
    printPerm(tmpel, n);
    cout << "\n";
    a[tmph1] = true;
  }
  int t = 0;
  do {
    t = 0;
    for(int i=0; i<len; i++) {
      if(not a[i])
        continue;
      int m1[MAX_N];
      unsheesh(m1, i, n);
      for(int j=0; j<len; j++) {
        if(not a[j])
          continue;
        int m2[MAX_N];
        unsheesh(m2, j, n);
        int c[MAX_N];
        mult(m1, m2, c, n);
        int k = sheesh(c, n);
        if(not a[k]) {
          t++;
          a[k] = true;
          printPerm(m1, n);
          cout << " * ";
          printPerm(m2, n);
          cout << " = ";
          printPerm(c, n);
          cout << "\n";
        }
      }
    }
  } while(t != 0);

  cout << "\n Our group is: \n";
  int tmp[MAX_N];
  for(int i=0; i<len; i++)
    if(a[i]) {
      unsheesh(tmp, i, n);
      printPerm(tmp, n);
      cout << ", ";
    }
  cout << "\n";

  ///*
  cout << "Center of group: ";
  int m1[MAX_N];
  int m2[MAX_N];
  int c1[MAX_N];
  int c2[MAX_N];
  for(int i=0; i<len; i++) {
    if(not a[i])
      continue;
    unsheesh(m1, i, n);
    bool yes = true;
    for(int j=0; j<len; j++) {
      if(not a[j])
        continue;
      unsheesh(m2, j, n);
      mult(m1, m2, c1, n);
      mult(m2, m1, c2, n);
      for(int k=0; k<n; k++)
        if(c1[k] != c2[k]) {
          yes = false;
          break;
        }
      if(not yes)
        break;
    }
    if(yes) {
      printPerm(m1, n);
      cout << ", ";
    }
  }
  cout << "\n";
  //*/
} // */


int sheesh(int a[], int n) {
  bool b[MAX_N];
  int a0[MAX_LEN];
  memset(b, false, n);
  for(int i=0; i<n; i++) {
    int c = 0;
    for(int j=0; j<a[i]; j++) 
      if(not b[j])
        c++;
    b[a[i]] = true;
    a0[i] = c;
  }
  int h1 = 0;
  int fac = 1; int j = 1;
  for(int i=n-2; i>=0; i--) {
    h1 += fac*a0[i];
    j++;
    fac *= j;
  }
  return h1;
}
void unsheesh(int a1[], int h, int n) {
  int a0[MAX_N];
  a0[n-1] = 0;
  int h1 = h; 
  for(int i=1; i<n; i++) {
    a0[n-1-i] = (h1 % (i+1));
    h1 /= (i+1);
  }

  bool b[MAX_N];
  memset(b, false, n);
  for(int i=0; i<n; i++) {
    int c = 0;
    int j;
    for(j=0; j<n; j++) {
      if(not b[j] and c == a0[i])
        break;
      if(not b[j])
        c++;
    }
    b[j] = true;
    a1[i] = j;
  }
}


void printPerm(int a1[], int n) {
  // cheching if it is e:
  bool isE = true;
  for(int i=0; i<n; i++)
    if(a1[i] != i) {
      isE = false;
      break;
    }
  if(isE) {
    cout << "e";
    return;
  }
  bool checked[MAX_N];
  memset(checked, false, n);
  int tmp = -1;
  for(int i=0; i<n; i++)
    if(tmp == -1 and a1[i] != i and not checked[i]) {
      cout << "(" << i+1;
      checked[i] = true;
      tmp = i;
      int start = i;
      do {
        tmp = a1[tmp];
        checked[tmp] = true;
        cout << " " << (tmp+1);
      } while (a1[tmp] != start);
      cout << ")";
      tmp = -1;
    }
}

void mult(int a[], int b[], int c[], int n) {
  for(int i=0; i<n; i++)
    c[i] = a[b[i]];
}

int multSheesh(int sheesha, int sheeshb, int n) {
  int a[MAX_N];
  int b[MAX_N];
  int c[MAX_N];
  unsheesh(a, sheesha, n);
  unsheesh(b, sheeshb, n);
  mult(a, b, c, n);
  return sheesh(c, n);
}

/*int testSheesh() {
  int n = 6;
  cout << "n = " << n << "\n";
  bool b[MAX_LEN];
  for(int i=0; i<6*5*4*3*2; i++) {
    int a1[MAX_N];
    cout << i << ": ";    
    unsheesh(a1, i, n);
    
    printPerm(a1, n);
    cout << "\n";
    int i1 = sheesh(a1, n);
    if(i1 != i)
      cout << "MAY I HAVE UR ATTENTION PLEASE!!! " << i << " " << i1 << "\n\n";
  }
}*/
