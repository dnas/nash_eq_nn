#include<bits/stdc++.h>
using namespace std;
typedef long long int lld;
typedef long double lf;
#define INF 1000000000000000000LL
#define MOD 1000000007
#define EPS (0.00000000001L)
#define PI (3.141592653589793L)
#define ff first
#define ss second
const lf eps = numeric_limits<lf>::epsilon();
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng(623878634);
uniform_real_distribution<> runif((lf)0.0, (lf)1.0);

lf randGauss(){
	lf u1 = 0.0L, u2 = runif(rng);
	while(u1<=eps) u1 = runif(rng);
	return sqrt(-2.0L*log(u1))*sin(2.0L*PI*u2);
}

lf activ_func(lf x){
	//return 1.0L/(1.0L+exp(-x));
	return 2.0L/(1.0L+exp(-2.0L*x))-1.0L;
}

lf activ_der(lf x){
	//return activ_func(x)*(1-activ_func(x));
	return 4.0L*exp(-2.0L*x)/((1.0L+exp(-2.0L*x))*(1.0L+exp(-2.0L*x)));
}

lf cost_der(lf y, lf a){
	return a-y;
}

lf softmax(lf x, lf s){
	return exp(x)/s;
}

lf softmax_der_id(lf x, lf s){
	return ((s-exp(x))*exp(x))/(s*s);
}

lf softmax_der_diff(lf x, lf y, lf s){
	return -exp(x+y)/(s*s);
}

struct NeuralNetwork{
	int numLayers;
	vector<int> numNodes;
	vector<vector<lf>> bias;
	vector<vector<pair<lf,lf>>> node; //par (a=f(z), z)
	vector<vector<vector<lf>>> weight;

	NeuralNetwork(vector<int> numN = {1}){
		numLayers = (int) numN.size();
		numNodes = numN;
	}

	void init_rand(){
		node.resize(numLayers);
		bias.resize(numLayers);
		weight.resize(numLayers-1);
		for(int i=0;i<numLayers;i++){
			node[i].resize(numNodes[i], {0.0L, 0.0L});
			bias[i].resize(numNodes[i], 0.0L);
			for(int j=0;j<numNodes[i];j++) bias[i][j] = randGauss();
			if(i>0){
				weight[i-1].resize(numNodes[i]);
				for(int j=0;j<numNodes[i];j++){
					weight[i-1][j].resize(numNodes[i-1]);
					for(int k=0;k<numNodes[i-1];k++) weight[i-1][j][k] = randGauss();
				}
			}
		}
	}

	void init_file(){
		init_rand();
		for(int i=0;i<numLayers;i++){
			for(int j=0;j<numNodes[i];j++) cin >> bias[i][j];
		}
		for(int i=1;i<numLayers;i++){
			for(int j=0;j<numNodes[i];j++){
				for(int k=0;k<numNodes[i-1];k++) cin >> weight[i-1][j][k];
			}
		}
	}

	vector<lf> predict(vector<lf> in){
		if((int)in.size()!=numNodes[0]){
			cout << "Input size does not match first layer size.\n";
			exit(1);
			return {};
		}
		for(int i=0;i<numNodes[0];i++) node[0][i] = {in[i], 0.0L};
		lf s = 0.0L;
		for(int i=1;i<numLayers;i++){
			for(int j=0;j<numNodes[i];j++){
				node[i][j].ss = bias[i][j];
				for(int k=0;k<numNodes[i-1];k++) node[i][j].ss += node[i-1][k].ff*weight[i-1][j][k];
				node[i][j].ff = activ_func(node[i][j].ss);
				if(i==numLayers-1) s+=exp(node[i][j].ss);
			}
		}
		vector<lf> rt(numNodes[numLayers-1]);
		for(int i=0;i<numNodes[numLayers-1];i++){
			rt[i] = softmax(node[numLayers-1][i].ss, s);
			node[numLayers-1][i].ff = rt[i];
		}
		return rt;
	}

	pair<vector<vector<lf>>, vector<vector<vector<lf>>>> calc_der(vector<lf> y){
		vector<vector<lf>> delta(numLayers);
		vector<vector<vector<lf>>> wd(numLayers-1);
		for(int i=0;i<numLayers;i++) delta[i].resize(numNodes[i], 0.0L);
		lf s = 0.0L;
		for(int j=0;j<numNodes[numLayers-1];j++) s+=exp(node[numLayers-1][j].ss);
		for(int j=0;j<numNodes[numLayers-1];j++){
			delta[numLayers-1][j] += softmax_der_id(node[numLayers-1][j].ss, s)*cost_der(y[j], node[numLayers-1][j].ff);
			for(int k=0;k<numNodes[numLayers-1];k++)
				if(k!=j)
					delta[numLayers-1][j] += softmax_der_diff(node[numLayers-1][j].ss, node[numLayers-1][k].ss, s)*cost_der(y[k], node[numLayers-1][k].ff);
		}
		for(int i=numLayers-2;i>=0;i--){
			for(int j=0;j<numNodes[i];j++){
				for(int k=0;k<numNodes[i+1];k++){
					delta[i][j]+= weight[i][k][j]*delta[i+1][k];
				}
				delta[i][j]*=activ_der(node[i][j].ss);
			}
		}
		for(int i=0;i<numLayers-1;i++){
			wd[i].resize(numNodes[i+1]);
			for(int j=0;j<numNodes[i+1];j++){
				wd[i][j].resize(numNodes[i]);
				for(int k=0;k<numNodes[i];k++) wd[i][j][k] = node[i][k].ff*delta[i+1][j];
			}
		}
		return {delta, wd};
	}

	void grad_descent(pair<vector<vector<lf>>, vector<vector<vector<lf>>>> der, lf learnRate){
		auto d = der.ff;
		auto wd = der.ss;
		for(int i=1;i<numLayers;i++){
			for(int j=0;j<numNodes[i];j++){
				bias[i][j]-= learnRate*d[i][j];
				for(int k=0;k<numNodes[i-1];k++) weight[i-1][j][k] -= learnRate*wd[i-1][j][k];
			}
		}
	}

	void batch_learn(vector<vector<lf>> in, vector<vector<lf>> y, lf learnRate){
		if(in.size()!=y.size()){
			exit(2);
			cout << "Batch size inconsistent\n";
			return;
		}
		int numBatches = (int)in.size();
		vector<vector<lf>> d(numLayers);
		vector<vector<vector<lf>>> wd(numLayers-1);
		for(int i=0;i<numLayers;i++){
			d[i].resize(numNodes[i], 0.0L);
			if(i>0){
				wd[i-1].resize(numNodes[i]);
				for(int j=0;j<numNodes[i];j++){
					wd[i-1][j].resize(numNodes[i-1], 0.0L);
				}
			}
		}
		for(int batch=0;batch<numBatches;batch++){
			if((int)in[batch].size()!=numNodes[0]){
				cout << "Input size inconsistent\n";
				exit(3);
				return;
			}
			if((int)y[batch].size()!=numNodes[numLayers-1]){
				cout << "Output size inconsistent\n";
				exit(4);
				return;
			}
			predict(in[batch]);
			auto der = calc_der(y[batch]);
			for(int i=0;i<numLayers;i++){
				for(int j=0;j<numNodes[i];j++){
					d[i][j]+=der.ff[i][j]/((lf) numBatches);
					if(i>0){
						for(int k=0;k<numNodes[i-1];k++) wd[i-1][j][k]+=der.ss[i-1][j][k]/((lf) numBatches);
					}
				}
			}
		}
		grad_descent({d,wd}, learnRate);
	}

	void print_info(){
		for(int i=0;i<numLayers;i++){
			for(int j=0;j<numNodes[i];j++) cout << bias[i][j] << " \n"[j==numNodes[i]-1];
		}
		for(int i=1;i<numLayers;i++){
			for(int j=0;j<numNodes[i];j++){
				for(int k=0;k<numNodes[i-1];k++) cout << weight[i-1][j][k] << " \n"[k==numNodes[i-1]-1];
			}
		}
	}

};

NeuralNetwork NN;
vector<lf> rps = {0,-1,1,1,0,-1,-1,1,0};

void print_vector(vector<lf> prnt){
	for(lf xxx:prnt) cout << xxx << " ";
	cout << "\n";
}

void learn_data(){
	freopen("games.txt", "r", stdin);
	freopen("nn.txt", "w", stdout);
	NN.init_rand();
	int valid = 0;
	for(int i=0;i<10000;i++){
		vector<vector<lf>> in, y;
		for(int j=0;j<10;j++){
			vector<lf> in_tmp(9);
			vector<lf> y_tmp(3);
			for(int k=0;k<9;k++) cin >> in_tmp[k];
			bool pure = false;
			for(int k=0;k<3;k++){
				cin >> y_tmp[k];
				//if(y_tmp[k]<EPS) pure = true;
			}
			if(pure) continue;
			valid++;
			in.push_back(in_tmp);
			y.push_back(y_tmp);
		}
		NN.batch_learn(in, y, 0.03L);
	}
	NN.print_info();
	//cout << valid << "\n";
}

void learn_debug(){
	freopen("nn.txt", "w", stdout);
	NN.init_rand();
	int batch_size = 1;
	for(int i=0;i<50000/batch_size;i++){
		vector<vector<lf>> in, y;
		for(int j=0;j<batch_size;j++){
			vector<lf> in_tmp(2);
			vector<lf> y_tmp(2);
			for(int k=0;k<2;k++) in_tmp[k] = runif(rng);
			y_tmp[0] = (in_tmp[0]+in_tmp[1])/2.0L;
			y_tmp[1] = 1-y_tmp[0];
			in.push_back(in_tmp);
			y.push_back(y_tmp);
		}
		NN.batch_learn(in, y, 0.03L);
	}
	NN.print_info(); 
}

void learn_file(){
	freopen("nn.txt", "r", stdin);
	NN.init_file();
	print_vector(NN.predict(rps));
}

int main(){	
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout.precision(20); cout << fixed;
	vector<int> layers = {1,2};
	NN = NeuralNetwork(layers);
	NN.init_rand();
	for(int i=0;i<5000000;i++){
		vector<lf> in(1);
		in[0] = runif(rng);
		vector<lf> y = {in[0], 1.0L-in[0]};
		NN.batch_learn({in}, {y}, 0.03L);
	}
	cout << NN.weight[0][0][0] << " " << NN.bias[1][0] << "\n";
	cout << NN.weight[0][1][0] << " " << NN.bias[1][1] << "\n";
	return 0;
}