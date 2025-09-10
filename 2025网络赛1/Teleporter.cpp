#include <bits/stdc++.h>
using namespace std;

const int N = 5500;
using ll = long long;
#define up(a,b,c) for(int a=b; a<=c; ++a)

int n, m;          // n = 城市数, m = 传送路径数
ll sum;            // 所有树边权值之和（用来初始化时的“大数”）
ll a[N], b[N], f[N]; // a = 上一轮的初始代价, b = 本轮最优结果, f = dfs中的中间状态

// 树的边
struct edge {
    int v;   // 邻接点
    int w;   // 边权
};
vector<edge> to[N];

// 传送器的边（无权值，0 代价）
struct trans {
    int u, v;
} e[N*2];


// ---------- 第一次 DFS（自底向上） ----------
// 计算每个点 u 的最小代价 f[u]，只考虑往子树方向走
void dfs1(int u, int la) {
    f[u] = a[u]; // 先取当前点的代价（从上一轮传下来的）
    for (edge z : to[u]) {
        if (z.v != la) { // 不走回父亲
            dfs1(z.v, u);
            // 如果走子节点再加边权更优，则更新
            f[u] = min(f[u], f[z.v] + z.w);
        }
    }
}


// ---------- 第二次 DFS（自顶向下） ----------
// 在 dfs1 的结果基础上，再结合父亲传递下来的信息
void dfs2(int u, int la, ll W) {
    // 当前点的代价 = min(子树内算出的代价, 父亲方向传来的代价)
    b[u] = f[u] = min(f[u], W);

    // 把结果传递给子节点
    for (edge z : to[u]) {
        if (z.v != la) {
            dfs2(z.v, u, f[u] + z.w);
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    sum = 0;
    // 输入 n-1 条树边
    up(i,2,n) {
        int u, v, w;
        cin >> u >> v >> w;
        to[u].push_back({v, w});
        to[v].push_back({u, w});
        sum += w;
    }

    // 输入 m 条传送边
    up(i,1,m) cin >> e[i].u >> e[i].v;

    // 初始化：所有点代价设为 sum（大数），首都 city 1 代价设为 0
    fill(a+1, a+n+1, sum);
    a[1] = 0;

    // 总共要算 n+1 轮 (k = 0..n)
    up(k,0,n) {
        // 在树上做两次 DFS，求出本轮最优结果 b[u]
        dfs1(1, 0);
        dfs2(1, 0, sum);

        // 计算并输出答案：∑ b[i] = 所有点在最多 k 次传送下的最短路之和
        ll sm = 0;
        up(i,1,n) sm += b[i];
        cout << sm << '\n';

        // 为下一轮准备：把 b 拷贝回 a
        copy(b+1, b+n+1, a+1);

        // 用传送边做一次“松弛”（Bellman-Ford 的核心）
        up(i,1,m) {
            a[e[i].u] = min(a[e[i].u], b[e[i].v]);
            a[e[i].v] = min(a[e[i].v], b[e[i].u]);
        }
    }
    return 0;
}
