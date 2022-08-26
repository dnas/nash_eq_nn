#include<bits/stdc++.h>
using namespace std;
typedef long long int lld;
typedef long double lf;
#define INF 1000000000000000000LL
#define MOD 1000000007
#define EPS (0.00000000001L)
#define PI (3.141592653589793L)

lf a[5010][5010];
lf strat[5010];
lf trash;

int main(){
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout.precision(6); cout << fixed;
	int n = 3;
	int num = 768594;
	while(num--){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++) cin >> a[i][j];
		}
		for(int i=0;i<n;i++) cin >> strat[i];
		for(int i=0;i<n;i++) cin >> trash;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++) cout << a[i][j] << " \n"[i==n-1&&j==n-1];
		}
		for(int i=0;i<n;i++) cout << strat[i] << " \n"[i==n-1];
	}
	return 0;
}