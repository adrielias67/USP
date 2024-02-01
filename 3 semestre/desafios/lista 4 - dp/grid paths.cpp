#include<bits/stdc++.h>

using namespace std;

using ll = long long;



char mapa[1001][1001];
ll nPaths[1000][1000];
int n;
int mod = 1000000007;



ll dp(int l, int c){
	if(nPaths[l][c] != -1) return nPaths[l][c];
	else{
		if((l+1 == n-1 && c+1 == n)  ||  (l+1 == n && c+1 == n-1)) nPaths[l][c] = 1;
		else if(mapa[l+1][c] == '*' && mapa[l][c+1] == '*') nPaths[l][c] = 0;
		else if(mapa[l+1][c] == '.' && mapa[l][c+1] == '.') nPaths[l][c] = (dp(l+1, c) + dp(l, c+1)) % mod;
		else if(mapa[l+1][c] == '*') nPaths[l][c] = dp(l, c+1) % mod;
		else nPaths[l][c] = dp(l+1, c) % mod;	
	}
	return nPaths[l][c];
}



int main(){
	int i, j;
	
	cin >> n;

	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			cin >> mapa[i][j];
			nPaths[i][j] = -1;
		}
	}
	for(i=0; i<n+1; i++){
		mapa[n][i] = '*';
		mapa[i][n] = '*';
	}

	if(n==1 && mapa[0][0]=='.'){
		cout << 1 << endl;
		return 0;
	}

	if(mapa[n-1][n-1]=='*'){
		cout << 0 << endl;
		return 0;
	}

	if(mapa[0][0]=='*'){
		cout << 0 << endl;
		return 0;
	}


	cout << dp(0, 0) << endl;
}