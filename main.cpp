#include <stdio.h>
#include <queue>

const int sa = 4, sb = 5;

struct Position {
  int a, b;
  Position(int an, int bn) {
    a = an;
    b = bn;
  }
};

void FillAround(int a[][sb], int **B, int m, int n, int cura, int curb, std::queue<Position> &q) {
  if (cura + 1 < m)
    if ((a[cura + 1][curb] == 1) && (B[cura + 1][curb] == -1)) {
      B[cura + 1][curb] = B[cura][curb] + 1;
      q.push(Position(cura + 1, curb));
    }

  if (curb + 1 < n)
    if ((a[cura][curb + 1] == 1) && (B[cura][curb + 1] == -1)) {
      B[cura][curb + 1] = B[cura][curb] + 1;
      q.push(Position(cura, curb + 1));
    }

  if (cura > 0)
    if ((a[cura - 1][curb] == 1) && (B[cura - 1][curb] == -1)) {
      B[cura - 1][curb] = B[cura][curb] + 1;
      q.push(Position(cura - 1, curb));
    }

  if (curb > 0)
    if ((a[cura][curb - 1] == 1) && (B[cura][curb - 1] == -1)) {
      B[cura][curb - 1] = B[cura][curb] + 1;
      q.push(Position(cura, curb - 1));
    }
}

void MinAround(int **B, int &cura, int &curb, int m, int n) {
  int min = m*n, newa = cura, newb = curb;
  if (cura + 1 < m)
    if ((B[cura + 1][curb] < min) && (B[cura + 1][curb] != -1)) {
      min = B[cura + 1][curb];
      newa = cura + 1;
      newb = curb;
    }
  if (curb + 1 < n)
    if ((B[cura][curb + 1] < min) && (B[cura][curb + 1] != -1)) {
      min = B[cura][curb + 1];
      newa = cura;
      newb = curb + 1;
    }
  if (cura > 0)
    if ((B[cura - 1][curb] < min) && (B[cura - 1][curb] != -1)) {
      min = B[cura - 1][curb];
      newa = cura - 1;
      newb = curb;
    }
  if (curb > 0)
    if ((B[cura][curb - 1] < min) && (B[cura][curb - 1] != -1)) {
      min = B[cura][curb - 1];
      newa = cura;
      newb = curb - 1;
    }
  cura = newa;
  curb = newb;
}

int FindWay(const int m, const int n, int  a[][sb]) {
  std::queue<Position> q;

  int **B = new int*[m];
  for (int i = 0; i < m; i++) {
    B[i] = new int[n];
    for (int j = 0; j < n; j++)
      B[i][j] = -1;
  }

  B[0][n - 1] = 0;

  q.push(Position(0, n - 1));

  while (!q.empty()) {
    Position pt = q.front();
    FillAround(a, B, m, n, pt.a, pt.b, q);
    q.pop();
  }


  int cura = m - 1, curb = 0;

  MinAround(B, cura, curb, m, n);
  int count = B[cura][curb] + 1;

  while ((cura != 0) || (curb != n - 1)) {
    MinAround(B, cura, curb, m, n);

  }

  return count;
}


int main() {

  int a[sa][sb]={ {1, 0, 1, 1, 0},
                {1, 0, 1, 1, 1},
                {1, 1, 1, 1, 1},
                {0, 0, 0, 1, 1} };

  int w = FindWay(sa, sb, a);
  printf("%d\n", w);
  system("pause");
}