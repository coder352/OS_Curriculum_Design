#include <iostream>
#include <cstdio>
using namespace std;
typedef struct {
    int dirx;
    int diry;
}DIRECTION;
DIRECTION dir_4[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int res[100][100];
int main(){
    int k = 0, max, dir = 0; //方向
    int x = 0, y = 0; //当前的位置
    cout << "请输入 长 和 宽:" << endl;
    int n, m; cin >> n >> m; max = m * n;
    for(res[x][y] = 65 + k++; k < max; res[x][y] = 65 + k++){
        int tmpx = x + dir_4[dir].dirx, tmpy = y + dir_4[dir].diry;
        if(tmpx < 0 || tmpx == n || tmpy < 0 || tmpy == m || res[tmpx][tmpy] != 0){
            dir += 1, dir %= 4, x += dir_4[dir].dirx; y += dir_4[dir].diry;
        }
        else x = tmpx, y = tmpy;
    }
    for(int i = 0; i < n; i++, cout << endl)
        for(int j = 0; j < m; j++)
            cout << (char)res[i][j] << " ";
}
