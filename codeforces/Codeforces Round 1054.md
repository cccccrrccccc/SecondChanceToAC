## [Codeforces Round 1054（Div3）](https://codeforces.com/contest/2149)

### C

**题意**

给定一个序列，值域为 $[0,n]$ ，可以将其中的值修改为 $[0,n]$ 中的一个整数， 求将序列的 `mex` 值变为 $k$ 需要的最小操作数

**思路**

需要将小于 $k$ 的数至少出现一次，记缺少的 $[0,k)$ 缺少的数的个数为 $cnt1$ ，等于 $k$ 的数也要改掉，记其个数为 $cnt2$ 。注意到可以将等于 $k$ 的数修改为 $[0,k)$ 中的数，因此答案为
$$
max(cnt1,cnt2)
$$

~~~c++
void solve() {
	int n, k;
	cin >> n >> k;
	vector<int>a(n);
	vector<bool>vis(n + 1);
	int ans = 0;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		vis[a[i]] = 1;
		if (a[i] == k) {
			cnt++;
		}
	}
	for (int i = 0; i < k; i++) {
		if (!vis[i])ans++;
	}
	cout << max(ans,cnt) << "\n";
}
~~~

### D

**题意**

给定一个字符串，仅含 $a、b$ ，求将至少一种字符全部放在一块所需要的最小操作数

**思路**

考虑将某一个字符全部往中间靠，一定是操作数最小的，分别取最中间位置，把其余字符往中间靠，计算出操作数，两种字符取最小值即可

~~~c++
void solve() {
    int n;
    string s;
    cin >> n >> s;
    if (n == 1) {
        cout << "0\n";
        return;
    }
    ll ans = 1e18;
    vector<int> pa;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') {
            pa.push_back(i);
        }
    }
    if (!pa.empty()) {
        int k = pa.size();
        int mid = k / 2;
        ll cost = 0;
        int t = pa[mid] - mid;
        for (int i = 0; i < k; i++) {
            int tp = t + i;
            cost += abs(pa[i] - tp);
        }
        ans = min(ans, cost);
    }
    vector<int> pb;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'b') {
            pb.push_back(i);
        }
    }

    if (!pb.empty()) {
        int k = pb.size();
        int mid = k / 2;
        ll cost = 0;
        int t = pb[mid] - mid;

        for (int i = 0; i < k; i++) {
            int tp = t + i;
            cost += abs(pb[i] - tp);
        }
        ans = min(ans, cost);
    }
    if (pa.empty() || pb.empty()) {
        ans = 0;
    }
    cout << ans << "\n";
}
~~~

### E

**题意**

给定一个长为 $n$ 的数组，求出长度在 $[l,r]$ 中恰好有 $k$ 种不同的数字的子数组个数

**思路**

想到可以用双指针计算出符合长度要求，小于等于 $k$ 种不同的数字的子数组个数。于是要计算 $k$ ，那么就只需要用 $k$ 的答案减去 $k-1$ 的答案即可

~~~c++
ll cal(vector<int>& a, int k, int l, int r) {
    int n = a.size();
    map<int, int>freq;
    ll cnt = 0;
    int le = 0,d=0;
    for (int ri = 0; ri < n; ri++) {
        if (freq[a[ri]] == 0)d++;
        freq[a[ri]]++;
        while (d > k) {
            freq[a[le]]--;
            if (freq[a[le]] == 0)
                d--;
            le++;
        }
        int mn = max(le, ri - r + 1);//左端点起始位置
        int mx = ri - l + 1;//右端点位置
        if (mx >= mn && mx >= 0) {
            cnt += max(0, mx - mn + 1);
        }
    }
    return cnt;
}
void solve() {
    int n,k,l,r;
    cin >> n>>k>>l>>r;
    vector<int>a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = cal(a, k, l, r) - cal(a, k - 1, l, r);
    cout << ans << "\n";
}
~~~



