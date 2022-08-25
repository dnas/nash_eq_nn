#include<bits/stdc++.h>
using namespace std;
typedef long long int lld;
typedef long double lf;
#define INF 1000000000000000000LL
#define MOD 1000000007
#define EPS (0.00000000001L)
#define PI (3.141592653589793L)

int a[5010][5010], b[5010][5010];
int max_row[5010];

int main(){
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout.precision(4); cout << fixed;
	int n = 3;
	int range = 100;
	for(int i=0;i<n;i++){
		max_row[i] = -1;
		for(int j=0;j<n;j++){
			cin >> a[i][j];
			max_row[i] = max(max_row[i], abs(a[i][j]));
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout << ((lf)a[i][j])/((lf) range) << " \n"[i==n-1&&j==n-1];
		}
	}
	return 0;
}