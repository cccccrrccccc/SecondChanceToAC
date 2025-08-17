## [Codeforces Round 944 (Div. 4)](https://codeforces.com/contest/1971)

### C.

判断时钟上的两条线段是否相交，两条线段由四个点 $a,b,c,d$ 确定

那么相交的充要条件即为线段二的每一个点的数值在线段一两点数值之间，不同时成立（有且仅有1个点成立）

有0/2个成立，线段二便在线段一上方/下方

```c++
void solve() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	if (a > b)swap(a, b);
	if (c > d)swap(c, d);
	if ((a<c&&c<b)^(a<d&&d<b)==1)cout << "Yes\n";
	else cout << "no\n";
}
```

### E.

#### 题目大意 

出租车（~~确信~~）$b[i]$ 时到达位置 $a[i]$ 点，在两点之间时速度为 $(a[i]-a[i-1])/(b[i]-b[i-1])$ ，给定 $q$ 个查询，对于每个查询位置 $d$ ，给出到达所需要的时间，向下取整（round down）

#### 思路

二分查找位置 $d$ 在 $a$ 中的下界，对于中间部分距离，利用速度、差值处理出时间。注意特殊点和边界处理

> [!Tip]
>
> 这里采用整形运算，可以避免浮点数造成的精度差异，可以满足向下取整的需求

~~~c++
void solve() {
    int n, k, q;
    cin >> n >> k >> q;
    vector<ll> a(k + 1), b(k + 1);
    a[0] = 0;
    for (int i = 1; i <= k; ++i) {
        cin >> a[i];
    }
    b[0] = 0;
    for (int i = 1; i <= k; ++i) {
        cin >> b[i];
    }
    vector<ll> res;
    while (q--) {
        ll d;
        cin >> d;
        auto it = lower_bound(a.begin(), a.end(), d);
        int p = it - a.begin();
        //该位置正好在点上
        if (p <= k && a[p] == d) {
            res.push_back(b[p]);
        }
        else {
            //注意边界处理
            if (p == 0) {
                res.push_back(0);
            }
            else {
                int i = p - 1;
                ll t = (d-a[i]) * (b[i + 1] - b[i]) / (a[i + 1] - a[i]);
                //时间=位移/速度
                ll total = b[i] + t;
                res.push_back(total);
            }
        }
    }
    for (int j = 0; j < res.size(); ++j) {
        cout << res[j]<<" \n"[j==res.size()-1];
    }
}
~~~

### F.

#### 题目大意

二维直角坐标系中在半径为 $r+1$ 和 $r$ 的圆之间的整点个数为多少，大圆不能取边界，小圆可取

#### 思路

很简单，大圆整点数减去小圆整点数，勾股定理处理每一个点即可，注意细节，详见代码注释 

- [ ] 或许还有更直观的做法

~~~c++
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<cmath>
typedef unsigned long long ull;
typedef long long ll;
double M = 1e-2;//处理浮点数精度问题，具体原理还没弄懂
using namespace std;
void solve() {
	ll r;
	cin >> r;
	ll ans1 = 0;
	ll ans2 = 0;
	for (ll i = 1; i < r; i++) {
        //循环变量一定开long long，不然下面根式中i*i要爆int
		ans1 += 2 * (int)sqrt(r * r - i * i - M) + 1;
	}
	ans1 *= 2;
	ans1 += 2 * r - 1;
	for (ll i = 1; i < r + 1; i++) {
		ans2 += 2 * (int)sqrt((r + 1) * (r + 1) - i * i - M) + 1;
	}
	ans2 *= 2;
	ans2 += 2 * r + 1;
	cout << ans2 - ans1 << "\n";
}

int main() {
	int t;
	cin >> t;
	while (t--)solve();
}
~~~



### G.

#### 题目大意

给定数组 $a$ ，若其中两个元素异或值小于 $4$ ，那么这两个元素可以交换，求所有交换下，字典序最小的序列

#### 思路

异或值小于四，那么只能最右边两位不同，其他位置上一定相同，那么我们可以通过将每个元素右移两位，那么就能通过是否相等判断能否交换，将数值最小放在前面即可，用 `map` 和 `priority_queue` 可以在 $O(n\log n)$ 的时间高效完成

~~~c++
void solve() {
    int n;
    cin >> n;
    vector<int>a(n);
    map<int, priority_queue<int, vector<int>, greater<int>>>mp;//a[i]>>2作为键对应一个小根堆
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i] >> 2].push(a[i]);

    }
    for (int i = 0; i < n; i++) {
        cout << mp[a[i] >> 2].top()<<" \n"[i==n-1] ;
        mp[a[i] >> 2].pop();
    }
}
~~~



