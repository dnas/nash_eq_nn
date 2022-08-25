#include<bits/stdc++.h>
using namespace std;
typedef long long int lld;
typedef long double lf;
#define INF 1000000000000000000LL
#define MOD 1000000007
#define EPS (0.00000000001L)
#define PI (3.141592653589793L)
mt19937 rng(623878634);
uniform_real_distribution<> runif((lf)0.0, (lf)1.0);


int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout.precision(20); cout << fixed;
	for(int i=0;i<50000;i++){
		vector<lf> in(9);
		lf exp_ans;
		for(int j=0;j<9;j++) cin >> in[j];
		cin >> exp_ans;
		cout << runif(rng) << " " << exp_ans << "\n";
	}
	return 0;
}