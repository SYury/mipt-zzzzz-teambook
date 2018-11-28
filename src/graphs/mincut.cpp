typedef long long ll;

const ll inf = (ll)1e18 + 18;
const int N = 505;

ll gr[N][N];
ll w[N];
bool alive[N];
int n;

ll mincut(){
	if(n == 1)return 0;
	fill(alive, alive + n, true);
	ll ans = inf;
	for(int phase = 0; phase < n - 1; phase++){
		int pold = -1;
		int old;
		ll wold;
		int start = -1;
		for(int i = 0; i < n; i++)
			if(alive[i])start = i;
		for(int i = 0; i < n; i++)
			if(alive[i])w[i] = gr[i][start];
		old = start;
		for(;;){
			int what = -1;
			for(int i = 0; i < n; i++)
            if(alive[i] && i != start && (what == -1 || w[i] > w[what]))
            	what = i;
			if(what < 0 || w[what] < 0)break;
			pold = old;
			old = what;
			wold = w[what];
			for(int i = 0; i < n; i++){
				w[i] += gr[i][what];
			}
			w[what] = -inf;
		}
		alive[old] = 0;
		ans = min(ans, wold);
		for(int i = 0; i < n; i++){
			gr[i][pold] += gr[i][old];
			gr[pold][i] += gr[old][i];
		}
	}
	return ans;
}
