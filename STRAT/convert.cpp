#include<bits/stdc++.h>
using namespace std;
typedef long long int lld;
typedef long double lf;
#define INF 1000000000000000000LL
#define MOD 1000000007
#define EPS (0.00000000001L)
#define PI (3.141592653589793L)

lf a[5010][5010];
lf x[5010], y[5010];

int main(){
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout.precision(6); cout << fixed;
	int num = 150000;
	int n = 3;
	int range = 100;
	while(num--){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cin >> a[i][j];
			}
		}
		for(int i=0;i<n;i++) cin >> x[i];
		for(int i=0;i<n;i++) cin >> y[i];
		lf ans = 0.0L;
		for(int i=0;i<n;i++){
			lf tmp = 0.0L;
			for(int j=0;j<n;j++) tmp += a[i][j]*y[j];
			ans += tmp*x[i];
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cout << a[i][j] << " \n"[i==n-1&&j==n-1];
			}
		}
		cout << ans << "\n";
	}
	return 0;
}