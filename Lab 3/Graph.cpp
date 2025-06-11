#include <bits/stdc++.h>

using namespace std;

class Graph
{
private:
    int n;
    vector<vector<int>> am;
    vector<set<int>> al;

public:
    Graph()
    {
        n = 0;
    }
    void operator+(Graph *g2)
    {
        if (g2->n > n)
        {
            for (auto i : am)
            {
                while ((int)i.size() < g2->n)
                {
                    i.push_back(0);
                }
            }
            while ((int)am.size() < g2->n)
            {
                vector<int> v(g2->n, 0);
                set<int> s;
                am.push_back(v);
                al.push_back(s);
            }
            n = g2->n;
            for (int i = 0; i < n; i++)
            {
                for (auto j : g2->al[i])
                {
                    al[i].insert(j);
                    al[j].insert(i);
                    am[i][j] = 1;
                    am[j][i] = 1;
                }
            }
        }
        else
        {
            for (int i = 0; i < g2->n; i++)
            {
                for (auto j : g2->al[i])
                {
                    al[i].insert(j);
                    al[j].insert(i);
                    am[i][j] = 1;
                    am[j][i] = 1;
                }
            }
        }
    }
    void operator-(Graph *g2)
    {
        if (g2->n > n)
        {
            vector<vector<int>> AM(g2->n, vector<int>(g2->n, 0));
            vector<set<int>> AL(g2->n);
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (am[i][j] == 1 && g2->am[i][j] == 1)
                    {
                        AM[i][j] = 1;
                        AM[j][i] = 1;
                        AL[i].insert(j);
                        AL[j].insert(i);
                    }
                }
            }
            am = AM;
            al = AL;
            n = g2->n;
        }
        else
        {
            vector<vector<int>> AM(n, vector<int>(n, 0));
            vector<set<int>> AL(n);
            for (int i = 0; i < g2->n; i++)
            {
                for (int j = 0; j < g2->n; j++)
                {
                    if (am[i][j] == 1 && g2->am[i][j] == 1)
                    {
                        AM[i][j] = 1;
                        AM[j][i] = 1;
                        AL[i].insert(j);
                        AL[j].insert(i);
                    }
                }
            }
            am = AM;
            al = AL;
        }
    }
    void operator!()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                    am[i][j] ^= 1;
            }
        }
        for (int i = 0; i < n; i++)
        {
            al[i].clear();
            for (int j = 0; j < n; j++)
            {
                if (am[i][j] == 1)
                {
                    al[i].insert(j);
                }
            }
        }
    }
    bool isReachable(int a, int b)
    {
        stack<int> dfs;
        vector<bool> visited(n, 0);
        visited[a] = 1;
        dfs.push(a);
        while (!dfs.empty())
        {
            int curr = dfs.top();
            dfs.pop();
            if (curr == b)
            {
                return true;
            }
            visited[curr] = true;
            for (auto i : al[curr])
            {
                if (!visited[i])
                {
                    dfs.push(i);
                }
            }
        }
        return false;
    }
    void addEdge(int a, int b)
    {
        am[a][b] = 1;
        am[b][a] = 1;
        al[a].insert(b);
        al[b].insert(a);
    }
    void removeEdge(int a, int b)
    {
        am[a][b] = 0;
        am[b][a] = 0;
        al[a].erase(b);
        al[b].erase(a);
    }

    friend void operator>>(std::istream &stream, Graph *g1);
    friend void operator<<(std::ostream &stream, Graph *g1);
};

void operator>>(std::istream &stream, Graph *g1)
{
    int N, M;
    stream >> N >> M;
    g1->n = N;
    g1->al = vector<set<int>>(N);
    g1->am = vector<vector<int>>(N, vector<int>(N, 0));
    for (int i = 0; i < M; i++)
    {
        int a, b;
        stream >> a >> b;
        g1->addEdge(a, b);
    }
}
void operator<<(std::ostream &stream, Graph *g1)
{
    for (int i = 0; i < g1->n; i++)
    {
        stream << "Vertex " << i << ": ";
        for (auto j : g1->al[i])
        {
            stream << j << " ";
        }
        stream << "\n";
    }
}

int main()
{
    string str;
    cin >> str;
    Graph *g1 = new Graph();
    cin >> g1;
    cin >> str;
    while (str != "end")
    {
        if (str == "printGraph")
        {
            cout << g1;
        }
        else if (str == "isReachable")
        {
            int a, b;
            cin >> a >> b;
            if (g1->isReachable(a, b))
            {
                cout << "Yes\n";
            }
            else
            {
                cout << "No\n";
            }
        }
        else if (str == "complement")
        {
            !*g1;
        }
        else if (str == "union")
        {
            cin >> str;
            Graph *g2 = new Graph();
            cin >> g2;
            *g1 + g2;
        }
        else if (str == "intersection")
        {
            cin >> str;
            Graph *g2 = new Graph();
            cin >> g2;
            *g1 - g2;
        }
        else if (str == "add_edge")
        {
            int a, b;
            cin >> a >> b;
            g1->addEdge(a, b);
        }
        else if (str == "remove_edge")
        {
            int a, b;
            cin >> a >> b;
            g1->removeEdge(a, b);
        }
        cin >> str;
    }
}