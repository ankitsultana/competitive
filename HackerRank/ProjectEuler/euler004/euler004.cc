#include <iostream>
#include <algorithm>
#define LIMIT 1000004

using namespace std;
bool if_poss[LIMIT] = {false};
int arr[LIMIT] = {0};

bool if_palin(int x)
{
	int y = 0, temp = x;
	while(temp){
		y = y*10+temp%10;
		temp /= 10;
	}
	return x==y;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int t, n;
	for(int lower = 100; lower < 1000; lower++){
		for(int upper = lower; upper < 1000; upper++){
			if(if_palin(upper*lower)){
				if_poss[upper*lower] = true;
			}
		}
	}
	int temp = 101101;
	for(int i = 101101; i < 1000000; i++){
		arr[i] = temp;
		if(if_poss[i])
			temp = i;
	}
	cin>>t;
	while(t--){
		cin>>n;
		cout<<arr[n]<<'\n';
	}
	return 0;
}
