/* Author: Ankit Sultana
 * Problem id: 1258
 * * * * * * * * * */
#include <stdio.h>
#include <algorithm>
#define gc getchar_unlocked
#define INF 1<<28
#define MAXN 1000002
 
using namespace std;
 
int P[MAXN] = {0}, aux[MAXN] = {0};
 
void prefix(char p[], int size) {
    int k = 0;
    P[0] = 0;
	for(int i = 1; i < size; i++) {
        while(k > 0 && p[k] != p[i]){
            k = P[k-1];  
        }
        if(p[k] == p[i]){
            k++;
        }
        P[i] = k;
    }
}
int kmp(char main_string[], char pattern[], int size) {
    if(size == 1){
        return 1;  
    }
    int res = size;
    prefix(pattern, size);
    int k = 0;
    P[0] = 0, aux[0] = 0;
	for(int i = 0; i < size; i++) {
        while(k > 0 && main_string[i] != pattern[k]){
            k = P[k-1];
        }
        if(main_string[i] == pattern[k]){
            k++;  
        }
        aux[i] = k;
        if(k == size){
            k = P[k-1];  
        }
    }
    res += res - aux[size-1];
    return res;
}
 
void scan_string(char st[], int &size) {
    char temp = gc();
    size = 0;
    while(!(temp >= 'a' && temp <= 'z')) temp = gc();
    while(temp >= 'a' && temp <= 'z'){
        st[size++] = temp;
        temp = gc();  
    }
}
 
int main() {
    int t;
    scanf("%d", &t);
    char main_string[MAXN], pattern[MAXN];
	for(int tc = 1; tc <= t; tc++) {
        printf("Case %d: ", tc);
        int size = 0;
        scan_string(main_string, size);
		for(int i = 0; i < size; i++) {
            P[i] = 0;  
            pattern[i] = main_string[size-i-1];
        }
        printf("%d\n", kmp(main_string, pattern, size));
    }
    return 0;
}
