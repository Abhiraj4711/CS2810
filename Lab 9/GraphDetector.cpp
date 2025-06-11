#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

struct Comparator
{
    bool operator()(const ll &a, const ll &b) const
    {
        return a > b;
    }
};

class GraphAlgorithm
{
    virtual void Query() {}
};

class cycleDetector : public GraphAlgorithm
{
private:
    vector<int> visited;
    bool dfs(vector<vector<ll>> &out, int x)
    {
        visited[x] = 1;
        for (ll i : out[x])
        {
            if (visited[i] == 1)
            {
                return false;
            }
            else if (visited[i] == 0)
            {
                if (!dfs(out, i))
                {
                    return false;
                }
            }
        }
        visited[x] = 2;
        return true;
    }

public:
    cycleDetector(int n)
    {
        visited.resize(n);
    }
    bool Query(vector<vector<ll>> &out)
    {
        bool ans = true;
        for (int i = 0; i < (int)visited.size() && ans; i++)
        {
            if (!visited[i])
            {
                ans &= dfs(out, i);
            }
        }
        return ans;
    }
};

class indepComponent : public GraphAlgorithm
{
private:
    void dfs1(int x, vector<ll> &v, vector<bool> &visited, vector<vector<ll>> &out)
    {
        for (auto i : out[x])
        {
            if (!visited[i])
            {
                visited[i] = 1;
                dfs1(i, v, visited, out);
                v.push_back(i);
            }
        }
    }
    void dfs2(int x, ll &size, vector<bool> &visited, vector<vector<ll>> &in, vector<vector<ll>> &scc)
    {
        for (auto i : in[x])
        {
            if (!visited[i])
            {
                visited[i] = 1;
                scc.back().push_back(i);
                size++;
                dfs2(i, size, visited, in, scc);
            }
        }
    }

public:
    pair<vector<vector<ll>>, ll> Query(vector<vector<ll>> &out, vector<vector<ll>> &in)
    {
        ll n = out.size();
        vector<ll> v;
        pair<vector<vector<ll>>, ll> ans = {{}, 0};
        vector<bool> visited(n, 0);
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                visited[i] = 1;
                dfs1(i, v, visited, out);
                v.push_back(i);
            }
        }
        for (int i = 0; i < n; i++)
        {
            visited[i] = 0;
        }
        vector<vector<ll>> scc;
        for (int i = n - 1; i >= 0; i--)
        {
            if (!visited[v[i]])
            {
                vector<ll> temp = {v[i]};
                scc.push_back(temp);
                visited[v[i]] = 1;
                ll size = 1;
                dfs2(v[i], size, visited, in, scc);
                ans.second = max(ans.second, size);
            }
        }
        ans.first = scc;
        return ans;
    }
};

class validOrder : public GraphAlgorithm
{
public:
    vector<ll> Query(vector<vector<ll>> &in, vector<vector<ll>> &out)
    {
        ll n = in.size();
        vector<ll> in_degree(n, 0);

        for (ll v = 0; v < n; v++)
        {
            in_degree[v] = in[v].size();
        }

        priority_queue<ll, vector<ll>, Comparator> pq;

        for (ll i = 0; i < n; i++)
        {
            if (in_degree[i] == 0)
            {
                pq.push(i);
            }
        }

        vector<ll> topo_order;

        while (!pq.empty())
        {
            ll u = pq.top();
            pq.pop();
            topo_order.push_back(u);

            for (ll v : out[u])
            {
                in_degree[v]--;
                if (in_degree[v] == 0)
                {
                    pq.push(v);
                }
            }
        }

        return topo_order;
    }
};

class maxHype : public GraphAlgorithm
{

public:
    ll Query(vector<vector<ll>> &out, vector<ll> &h, vector<vector<ll>> &scc)
    {
        vector<vector<ll>> out2(scc.size(), vector<ll>(0));
        vector<vector<ll>> in2(scc.size(), vector<ll>(0));
        vector<ll> hype(scc.size(), 0);
        vector<ll> m(out.size(), 0);
        for (int i = 0; i < (int)scc.size(); i++)
        {
            for (auto j : scc[i])
            {
                hype[i] += h[j];
                m[j] = i;
            }
        }
        for (int i = 0; i < (int)out.size(); i++)
        {
            for (auto j : out[i])
            {
                if (m[i] == m[j])
                {
                    continue;
                }
                out2[m[i]].push_back(m[j]);
                in2[m[j]].push_back(m[i]);
            }
        }
        validOrder vo;
        vector<ll> topo = vo.Query(in2, out2);
        reverse(topo.begin(), topo.end());
        ll n = out2.size();
        ll ans = 0;
        vector<ll> hype2(n, 0);
        for (auto i : topo)
        {
            if ((int)out2[i].size() == 0)
            {
                hype2[i] = hype[i];
            }
            else
            {

                for (auto j : out2[i])
                {
                    hype2[i] = max(hype2[i], hype2[j]);
                }
                hype2[i] += hype[i];
            }
        }
        for (auto i : hype2)
        {
            ans = max(ans, i);
        }
        return ans;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> in(n), out(n);
    vector<ll> h(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> h[i];
    }
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        out[a].push_back(b);
        in[b].push_back(a);
    }
    cycleDetector cd(n);         // done
    bool cycle = !cd.Query(out); // cycle is true if there is a cycle
    validOrder vo;               // done
    vector<ll> v;
    if (!cycle)
    {
        v = vo.Query(in, out);
    }
    indepComponent ic; // done
    pair<vector<vector<ll>>, ll> p = ic.Query(out, in);
    maxHype mh;
    ll maxHype = mh.Query(out, h, p.first);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            if (cycle)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
        else if (type == 2)
        {
            cout << p.first.size() << " " << p.second << "\n";
        }
        else if (type == 3)
        {
            if (cycle)
            {
                cout << "NO\n";
            }
            else
            {
                for (int i = 0; i < n; i++)
                {
                    cout << v[i] + 1 << " ";
                }
                cout << "\n";
            }
        }
        else
        {
            cout << maxHype << "\n";
        }
    }
}