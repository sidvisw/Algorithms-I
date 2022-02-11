#include <bits/stdc++.h>

#define endl '\n'
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define ff first
#define ss second
#define vi vector<int>
#define vl vector<ll>
#define vii vector<pii>
#define vll vector<pll>
#define F0R(i, N) for (i = 0; i < (N); ++i)
#define F0Re(i, N) for (i = 1; i <= (N); ++i)
#define F0Rr(i, a, b) for (i = (a); i < (b); ++i)
#define F0Rrev(i, N) for (i = (N); i >= 0; --i)
#define FOR(i, N) for (int i = 0; i < (N); ++i)
#define FORe(i, N) for (int i = 1; i <= (N); ++i)
#define FORr(i, a, b) for (ll i = (a); i < (b); ++i)
#define FORrev(i, N) for (int i = (N); i >= 0; --i)
#define all(v) (v).begin(), (v).end()
#define dbgLine cerr << " LINE : " << __LINE__ << '\n'
#define ldd long double

using namespace std;

const int Alp = 26;
const int __PRECISION = 9;
const int inf = 1e9 + 8;

const ldd PI = acos(-1);
const ldd EPS = 1e-7;

const ll MOD = 1e9 + 7;
const ll MAXN = 2e5 + 5;
const ll ROOTN = 320;
const ll LOGN = 18;
const ll INF = 1e18 + 1022;

/*Your functions here*/

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vi v;
        FOR(i, n)
        {
            int no;
            cin >> no;
            v.pb(no);
        }
        set<int> s;
        int c = 0;
        for (int i = 0; i < n;)
        {
            if (!s.count(v[i]))
            {
                int l = lower_bound(all(v), v[i]) - v.begin();
                int r = upper_bound(all(v), v[i]) - v.begin() - 1;
                c += r - l + 1;
                i = i + 1;
                s.insert(v[i]);
            }
            else
            {
                i++;
            }
        }
        cout << c << endl;
    }

    return 0;
}