#include <iostream>

using namespace std;

long long part3(long long n, long long query)
{
	if(n < query)
		return 0;
	long long N = n/query;
	long long result = N*(( 2*query ) + (N - 1)*query) / 2;
	if(n % query == 0)
		result -= n;
	return result;
}

int main()

{
	std::ios_base::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t > 0){
		long long N;
		cin>> N;
		long long result = part3(N, 3) + part3(N, 5) - part3(N, 15); 
		cout<<result<<'\n';
		t--;
	}
	return 0;
}
