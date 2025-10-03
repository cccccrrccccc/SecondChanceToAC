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
### G

**题意**

给定一个长为 $n$ 的数组和q次包含l,r的查询，对于每次查询求出 $[l,r]$ 中出现出现频次严格大于 $[r-l+1]/3$ 的所有数。

**思路**

随机化方法详见官方题解，这里给出一种主席树做法。考虑对每个数组a的前缀 $(a[1]到 a[i])$ 维护一个权值线段树,那么 $[l,r]$ 上某一个区间(是指数值区间，不是指原数组的下标区间)内的所有数的出现频次和就可以用 $r$ 处线段树在该区间的频次，减去 $l-1$ 处线段树在该区间的频次就可以了。我们在寻找出现频次大于某一特定值(本题为$[r-l+1]/3$)的某几个数时，只要在区间的总出现频次大于该值时向下寻找，小于等于该值时结束，递归到最底层，即可找到这些数。详情见代码(代码来自https://www.bilibili.com/video/BV1vwnJzLEPk/?buvid=XX551D05214F768AD5CD10390D51824A54821&from_spmid=search.search-result.0.0&is_story_h5=false&mid=HVPUs3%2BSIfVeYFz%2BetlC%2Bn8FTQ%2FSZMtL1rElX6M3iMo%3D&p=8&plat_id=116&share_from=ugc&share_medium=android&share_plat=android&share_session_id=21828b6e-4cbd-4184-9d31-235b8932d0a2&share_source=WEIXIN&share_tag=s_i&spmid=united.player-video-detail.0.0&timestamp=1759456417&unique_k=l5qhtSJ&up_id=40583595)。

~~~c++
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;  

// 主席树的节点结构
struct node
{
    ll lson;  // 左子节点索引
    ll rson;  // 右子节点索引
    ll fre;   // 当前节点代表的区间中元素的出现次数
};

// 主席树类，封装了构建、插入和查询等操作
struct pst
{
    vector<node> tr;       // 存储所有节点的数组
    vector<ll> b;          // 用于离散化的数组（存储去重排序后的元素）
    vector<ll> rt;         // 存储各版本根节点的索引
    vector<ll> ans;        // 存储查询结果
    ll tot;                // 节点计数器，用于分配新节点
    ll n;                  // 原始数据规模
    ll bn;                 // 离散化后的元素数量

    // 离散化：获取元素x在b数组中的位置（1-based索引）
    ll getid(ll x)
    {
        return lower_bound(b.begin(), b.end(), x) - b.begin() + 1;
    }

    // 构建初始版本的线段树（空树）
    // x：当前节点引用，l、r：当前节点负责的区间
    void build(ll &x, ll l, ll r)
    {
        x = ++tot;       // 分配新节点
        tr[x].fre = 0;   // 初始出现次数为0
        if (l == r) return;  // 叶子节点直接返回
        ll mid = (l + r) / 2;
        build(tr[x].lson, l, mid);    // 递归构建左子树
        build(tr[x].rson, mid + 1, r); // 递归构建右子树
    }

    // 插入操作：基于旧版本创建新版本
    // x：旧版本节点，y：新版本节点引用，l、r：当前区间，tar：要插入的元素（离散化后的值）
    void ins(ll x, ll &y, ll l, ll r, ll tar)
    {
        y = ++tot;       // 分配新节点
        tr[y] = tr[x];   // 复制旧节点信息
        tr[y].fre++;     // 更新出现次数
        if (l == r) return;  // 到达叶子节点，插入完成
        ll mid = (l + r) / 2;
        if (tar <= mid)  // 目标在左区间
            ins(tr[x].lson, tr[y].lson, l, mid, tar);
        else  // 目标在右区间
            ins(tr[x].rson, tr[y].rson, mid + 1, r, tar);
    }

    // 查询操作：找出区间内出现次数超过tar的元素
    // x：旧版本节点（l1-1对应的根），y：新版本节点（r1对应的根）
    // l、r：当前区间，tar：次数阈值
    void query(ll x, ll y, ll l, ll r, ll tar)
    {
        // 若当前区间总出现次数 <= tar，无需继续查询
        if (tr[y].fre - tr[x].fre <= tar) return;
        if (l == r)  // 叶子节点，说明找到符合条件的元素
        {
            ans.push_back(b[l - 1]);  // 存储原始值（b是0-based，l是1-based）
            return;
        }
        ll mid = (l + r) / 2;
        // 递归查询左右子树
        query(tr[x].lson, tr[y].lson, l, mid, tar);
        query(tr[x].rson, tr[y].rson, mid + 1, r, tar);
    }

    // 对外接口：查询[l1, r1]区间中出现次数超过tar的元素
    void qry(ll l1, ll r1, ll tar)
    {
        ans.clear();  // 清空上一次查询结果
        // 调用内部查询函数，rt[l1-1]是前缀l1-1的根，rt[r1]是前缀r1的根
        query(rt[l1 - 1], rt[r1], 1, bn, tar);
    }

    // 构造函数：初始化主席树
    // n1：数据规模，a：原始数组（1-based）
    pst(ll n1, vector<ll>& a)
    {
        tot = 0;  // 重置节点计数器
        n = n1;
        rt.resize(n + 10);  // 预留根节点数组空间
        tr.resize(32 * n);  // 预留节点空间（32*n是经验值）
        b.resize(n);
        // 复制原始数据到b数组（用于离散化）
        b.assign(a.begin() + 1, a.end());
        sort(b.begin(), b.end());  // 排序
        // 去重，保留唯一元素
        b.erase(unique(b.begin(), b.end()), b.end());
        bn = b.size();  // 离散化后的元素数量
        build(rt[0], 1, bn);  // 构建初始版本（空树）
        // 构建前缀版本：rt[i]是插入前i个元素后的根节点
        for (ll i = 1; i <= n; i++)
        {
            // 基于上一个版本rt[i-1]插入a[i]，生成新版本rt[i]
            ins(rt[i - 1], rt[i], 1, bn, getid(a[i]));
        }
    }
};

// 处理单组测试数据
void solve()
{
    ll n, q;
    cin >> n >> q;  // 输入数据规模n和查询次数q
    vector<ll> a(n + 1);  // 存储原始数据（1-based索引）
    for (ll i = 1; i <= n; i++) cin >> a[i];
    pst tree(n, a);  // 初始化主席树

    // 处理q次查询
    for (ll i = 0; i < q; i++)
    {
        ll l1, r1;
        cin >> l1 >> r1;  // 输入查询区间[l1, r1]
        // 计算阈值：区间长度的1/3（向下取整）
        ll tar = (r1 - l1 + 1) / 3;
        // 查询区间中出现次数超过tar的元素
        tree.qry(l1, r1, tar);
        
        if (tree.ans.size() == 0)  // 没有符合条件的元素
            cout << -1 << '\n';
        else
        {
            sort(tree.ans.begin(), tree.ans.end());  // 排序结果
            for (ll tt : tree.ans)
            {
                cout << tt << ' ';
            }
            cout << '\n';
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    cout << fixed << setprecision(20);  
    
    int t;
    cin >> t;  
    for (int i = 0; i < t; i++)
    {
        solve();  
    }
    return 0;
}
~~~



