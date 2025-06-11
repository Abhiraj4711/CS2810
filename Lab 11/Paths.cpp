#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

class Node
{
private:
    string ID;
    ll evenDist;
    ll oddDist;

public:
    // Constructors
    Node()
    {
        ID = "";
        evenDist = oddDist = INT_MAX;
    }
    Node(string id)
    {
        ID = id;
        evenDist = oddDist = INT_MAX;
    }

    // Getters
    string getID()
    {
        return ID;
    }
    ll getEvenDist()
    {
        return evenDist;
    }
    ll getOddDist()
    {
        return oddDist;
    }

    // Setters
    void setID(string id)
    {
        ID = id;
    }
    void setEvenDist(ll ed)
    {
        evenDist = ed;
    }
    void setOddDist(ll od)
    {
        oddDist = od;
    }

    // overloading
    bool operator>(const Node &other) const
    {
        return min(evenDist, oddDist) > min(other.evenDist, other.oddDist);
    }

    bool operator<(const Node &other) const
    {
        return min(evenDist, oddDist) < min(other.evenDist, other.oddDist);
    }
};

template <typename T>
class PriorityQueue
{
private:
    vector<T> arr;

    void percolateUp(int hole)
    {
        T e = arr[hole];
        while (hole > 0 && arr[(hole - 1) / 2] > e)
        {
            arr[hole] = arr[(hole - 1) / 2];
            hole = (hole - 1) / 2;
        }
        arr[hole] = e;
    }

    void percolateDown(int hole)
    {
        int size = arr.size();
        T e = arr[hole];
        while (2 * hole + 1 < size)
        {
            int child = 2 * hole + 1;
            if (child + 1 < size && arr[child + 1] < arr[child])
            {
                child++;
            }
            if (arr[child] > e)
            {
                break;
            }
            arr[hole] = arr[child];
            hole = child;
        }
        arr[hole] = e;
    }

public:
    PriorityQueue() {}

    size_t size()
    {
        return arr.size();
    }

    void push(const T &e)
    {
        arr.push_back(e);
        percolateUp(arr.size() - 1);
    }

    void pop()
    {
        if (empty())
            return;

        arr[0] = arr.back();
        arr.pop_back();
        if (!empty())
            percolateDown(0);
    }

    const T &top()
    {
        assert(!empty());
        return arr[0];
    }

    bool empty()
    {
        return arr.size() == 0;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<Node> v(n);
    map<string, int> idMap;
    vector<vector<pair<int, int>>> al(n);

    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        v[i] = Node(str);
        idMap[str] = i;
    }

    for (int i = 0; i < m; i++)
    {
        string a, b;
        int w;
        cin >> a >> b >> w;
        al[idMap[a]].push_back({idMap[b], w});
        al[idMap[b]].push_back({idMap[a], w});
    }

    string src, dst;
    cin >> src >> dst;
    int sourceIndex = idMap[src], destIndex = idMap[dst];

    v[sourceIndex].setEvenDist(0);
    v[sourceIndex].setOddDist(INT_MAX);

    PriorityQueue<Node> pq;
    pq.push(v[sourceIndex]);

    vector<bool> visited(n, false);
    vector<vector<ll>> distances(n, vector<ll>(2, INT_MAX));
    distances[sourceIndex][0] = 0;

    while (!pq.empty())
    {
        Node curr = pq.top();
        pq.pop();

        int u = idMap[curr.getID()];

        for (auto &edge : al[u])
        {
            int neighbor = edge.first;
            int weight = edge.second;

            if (curr.getOddDist() + weight < distances[neighbor][0])
            {
                distances[neighbor][0] = curr.getOddDist() + weight;
                v[neighbor].setEvenDist(curr.getOddDist() + weight);
                pq.push(v[neighbor]);
            }

            if (curr.getEvenDist() + weight < distances[neighbor][1])
            {
                distances[neighbor][1] = curr.getEvenDist() + weight;
                v[neighbor].setOddDist(curr.getEvenDist() + weight);
                pq.push(v[neighbor]);
            }
        }
    }

    if (distances[destIndex][0] >= INT_MAX)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << distances[destIndex][0] << endl;
    }

    return 0;
}