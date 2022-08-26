#include<bits/stdc++.h>
using namespace std;
typedef long long int lld;
typedef long double lf;
#define INF 1000000000000000000LL
#define MOD 1000000007
#define EPS (0.00000000001L)
#define PI (3.141592653589793L)


int main(){
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout.precision(6); cout << fixed;
	int num = 1;
	while(num--){
		lf ans = 0;
		lf sq = 0;
		for(int i=0;i<50000;i++){
			lf a, exp_a; cin >> a >> exp_a;
			ans += abs(a-exp_a)/exp_a;
			sq += 0.5L*(a-exp_a)*(a-exp_a);
		}
		cout << ans/50000.0L << "\n";
		cout << sq/50000.0L << "\n";
		cout << "-\n";
	}
	return 0;
}