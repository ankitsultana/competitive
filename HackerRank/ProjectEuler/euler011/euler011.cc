#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#define WIDTH 20

int grid[30][30] = {0}, res = 0, temp;

int main() {
    ios_base::sync_with_stdio(false);
    for(int i = 1; i <= 20; i++){
        for(int j = 1; j <= 20; j++){
            cin>>grid[i][j];
        }
    }
    for(int i = 1; i <= WIDTH; i++){
        for(int j =1; j <= WIDTH; j++){
            temp = 1;
            bool check = true;
            // Diagonal
            for(int add = 0; add < 4; add++){
                if(add+i > 20 || add+j > 20){
                    check = false;
                    break;
                }
                temp *= grid[add+i][add+j];
            }
            if(check)
                res = max(res, temp);
            check = true;
            temp = 1;
            for(int add = 0; add > -4; add--){
                if(i-add > 20 || add+j < 0){
                    check = false;
                    break;
                }
                temp *= grid[i-add][add+j];
            }
            if(check)
                res = max(res, temp);
            check = true;
            temp = 1;
            for(int add= 0; add < 4; add++){
                if(add+j > 20){
                    check = false;
                    break;
                }
                temp *= grid[i][j+add];
            }
            if(check)
                res = max(res, temp);
            temp = 1;
            check = true;
            for(int add = 0; add < 4; add++){
                if(add+i > 20){
                    check = false;
                    break;
                }
                temp *= grid[i+add][j];
            }
            if(check){
                res = max(res, temp);
            }
        }
    }
    cout<<res<<'\n';
    return 0;
}
