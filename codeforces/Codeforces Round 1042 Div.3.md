# [Codeforces Round 1042 Div.3](https://codeforces.com/contest/2131)

## C

**题目大意**

给定两个大小均为 $n$ 的多集 $S$ 和 $T$ ，元素均为正整数，给定一个正整数 $k$ ，对集合 $S$ 中的元素 $x$ ，可以将其转化为 $x+k$ 或者 $|x-k|$ ，判断若干次操作后，能否让 $S、T$ 相同

**思路**

采用 $x+k$ 操作，结果必然对 $k$ 同余，采用 $|x-k|$ 操作，可以改变余数，余数最多出现两种情况。其实就是判断 $T$ 中出现的余数 $S$ 能否全覆盖掉，对于余数 $m$ 和 $k-m$ ，可以由同一个数得到，于是将 $S$ 和 $T$ 中的每个对 $k$ 的余数 $m$ 取 $min(m,k-m)$ 记录下来，判断是否相等

**代码**

~~~c++
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int>a, b;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x %= k;
        x = min(x, k-x);
        a.push_back(x);
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x %= k;
        x = min(x, k - x);
        b.push_back(x);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a == b)cout << "YES\n";
    else cout << "NO\n";
}
~~~

## D

**题目大意**

给定一颗树，给定操作

- 选择两个结点 $s$ 和 $t$ ，移除两点间简单路径上的所有边
- 将除 $s$ 以外其余所有点直接连接到 $s$ 上

确定使树直径最小所需要的最少操作次数

**思路**

- 考虑如何选择 $s$ ，如果选择多个结点作为 $s$ 进行操作，不会比仅选择一个结点作为 $s$ 进行操作更优
- 非叶子结点可以通过对某一个叶子结点进行操作从而连接到 $s$ ，也就是说，终点 $t$ 一定是在叶子结点处
- 如果叶子结点之间连接到了 $s$ 就不用进行操作

于是，最小操作次数可以这样得到：

获取叶子结点总数 $tot$ ，遍历每个结点，考虑其作为 $s$ 的情况，$leaf[s]$ 表示与 $s$ 直接相连的叶子结点个数，那么对应的答案就是 $tot-leaf[s]$ ，也就是除了和 $s$ 直接相连的叶子结点，所有的叶子结点总数，取最小值即可

> [!Warning]
>
> 注意 $s$ 本身也可能是叶子结点，那么其自身也不用操作，要把这种情况也算在 $leaf[s]$ 中

**代码**

~~~c++
void solve() {
    int n;
    cin >> n;
    vector<vector<int>>adj(n);
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int tot = 0;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1) {
            tot++;
        }
    }
    int ans = INF;
    for (int s = 0; s < n; s++) {
        int leaf = 0;
        if (adj[s].size() == 1)leaf++;//s本身作为叶子结点的情况
        for (auto v : adj[s]) {
            if (adj[v].size() == 1) {
                leaf++;
            }
        }
        ans = min(ans, tot - leaf);
    }
    cout << ans << "\n";
}
~~~

## E

**题目大意**

给定两个数组 $a、b$，对于每个 $i$ ，至多进行一次操作，使 $a_i=a_i \oplus a_{i+1}$ ，问能否将 $a$ 变为 $b$

**思路**

由于每个位置 $i$ 操作只能最多一次，那么对每一个位置进行判断

- 如果相等，显然满足
- 如果不相等，那么如果异或 $a_{i+1}$ 能得到，那么也能满足
- 如果都不行，那么如果异或 $b_{i+1}$ 能得到，也满足，因为可以让 $a_{i+1}$ 先变为 $b_{i+1}$ 

遍历即可。不过怎么严格证明条件满足时，一定存在合法操作序列，我还不清楚

**代码**

~~~c++
#include <iostream>
#include<vector>
#include<algorithm>
const int INF = 1 << 30;
using namespace std;
void solve() {
    int n;
    cin >> n;
    vector<int>a(n);
    vector<int>b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    if (a[n - 1] != b[n - 1]) {
        cout << "No\n";
        return;
    }
    for (int i = 0; i <n-1; i++) {
        int c = a[i] ^ b[i];
        if (c == 0 || c == a[i + 1] || c == b[i + 1]) {
            continue;
        }
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
~~~

## F

**题目大意**

给定两个长为 $n$ 的 $01$ 序列 $a、b$ ，一个 $n\times n$ 网格由 $a,b$ 决定，其中 $(i,j)$ 的值为 $a_i\oplus b_j$ ，可以操作使 $a$ 或 $b$ 中的某一位反转，代价为 $1$

定义 $f(x,y)$ 表示从点 $(1,1)$ 通过值全为 $0$ 的路径到点 $(x,y)$ 所需要的最小代价 (通过操作构造一条从 $(1,1)$ 到 $(x,y)$的全 $0 $ 路径的最小代价)

求 
$$
\sum_{x=1}^{n}\sum_{y=1}^{n}f(x,y)
$$


**思路**

- 1 考虑任意一条从 $(1,1)$ 到 $(x,y)$ 的合法路径，需要满足条件 $a_1=b_1$ ，$a_x=b_y$ ，并且对于路径上所有的点 $(i,j)$ $a_i=b_j$ 。而路径上相邻点之间横坐标或纵坐标其中一个相等，其中一个差值为1，手玩一下不难推证出 $a[1,x]$ 和 $b[1,y]$ 这 $x+y$ 个元素全部相同，要么全为 $0$ 要么全为 $1$ 。
- 2 那么要使这些元素全部相同，最小代价两者前缀 $1$ 的和与前缀 $0$ 的和的最小值，即 

$$
f(x,y)=min(prea1[x]+preb1[y],prea0[x]+preb0[y])
$$

有如下公式
$$
min(a,b)=\frac{a+b-|a-b|}{2}\\
\\max(a,b)=\frac{a+b+|a-b|}{2}
$$
于是可化为
$$
f(x,y)=\frac{prea1[x]+prea0[x]+preb1[y]+preb0[y]-|prea1[x]-prea0[x]+preb1[y]-preb0[y]|}{2}
$$
而前缀 $0$ 和前缀 $1$ 的的和就是前缀长度呗。再令 $t1[x]=prea1[x]-prea0[x]$ $t2[x]=preb1[x]-preb0[x]$

所以
$$
f(x,y)=\frac{x+y-|t1[x]+t2[y]|}{2}
$$
那么所求式子可化为
$$
\sum_{x=1}^{n}\sum_{y=1}^{n}f(x,y)=\frac{n^3+n^2}{2}-\sum_{x=1}^{n}\sum_{y=1}^{n}\frac{t1[x]+t2[y]}{2}
$$
接下来就是绝对值的处理了，对 $t1$ 排序

对于每个 $t2[i]$，找到 $t1$ 中第一个满足 $t1[j] \geq -t2[i]$ 的位置 $p$。

这样，对于 $x < p$，$t1[x] + t2[i] < 0$，所以绝对值为 $-(t1[x] + t2[i])$。

对于 $x \geq p$，$t1[x] + t2[i] \geq 0$，所以绝对值为 $t1[x] + t2[i]$。

总和可以拆分为：
$$
\sum_{x=1}^n |t1[x] + t2[i]| = -\sum_{x < p} t1[x] - t2[i] \cdot (p-1) + \sum_{x \geq p} t1[x] + t2[i] \cdot (n - p + 1)
$$


进一步整理为：

$$
\sum_{x \geq p} t1[x] - \sum_{x < p} t1[x]) + t2[i] \cdot (n - 2p + 2)
$$
其中 $\sum_{x \geq p} t1[x] - \sum_{x < p} t1[x] = pt1[n] - 2 \cdot pt1[p-1]$。 $pt1$ 是 $t1$ 的前缀数组

这一部分代码如下

~~~c++
	sort(t1.begin() + 1, t1.end());
	vector<ll>pt1(n + 1);
	for (int i = 1; i <= n; i++) {
		pt1[i] = pt1[i - 1] + t1[i];
	}
	for (int i = 1; i <= n; i++) {
		auto p = lower_bound(t1.begin() + 1, t1.end(), -t2[i]) - t1.begin();//找到 t1 中第一个满足t1[j]>=-t2[i]
        //即第一个满足t1[j]+t2[i]>=0的位置p
		ll sum = (pt1[n] - 2 * pt1[p - 1]) + t2[i] * (n - 2 * p + 2);//累计贡献
		ans -= sum;
	}
~~~

**完整代码**

~~~c++
void solve() {
	int n;
	cin >> n;
	string a, b;
	cin >> a >> b;
	a = "#" + a;
	b = "#" + b;
	vector<int>pa1(n+1), pb1(n+1);
	for (int i = 1; i <= n; i++) {
		pa1[i] = pa1[i - 1] + (a[i] == '1');
		pb1[i] = pb1[i - 1] + (b[i] == '1');
	}
	ll ans = (ll)n * n * n + (ll)n * n;
	ans;
	vector<int>t1(n + 1), t2(n + 1);
	for (int i = 1; i <= n; i++) {
		t1[i] = 2 * pa1[i] - i;
		t2[i] = 2 * pb1[i] - i;
	}
	sort(t1.begin() + 1, t1.end());
	vector<ll>pt1(n + 1);
	for (int i = 1; i <= n; i++) {
		pt1[i] = pt1[i - 1] + t1[i];
	}
	for (int i = 1; i <= n; i++) {
		auto p = lower_bound(t1.begin() + 1, t1.end(), -t2[i]) - t1.begin();
		ll sum = (pt1[n] - 2 * pt1[p - 1]) + t2[i] * (n - 2 * p + 2);
		ans -= sum;
	}
	cout << ans /2<< "\n";
}
~~~



