#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

class Sentinal
{
private:
    int id;
    string name;
    string rank;

public:
    Sentinal() {}
    Sentinal(int ID, string RANK)
    {
        id = ID;
        rank = RANK;
    }
    virtual int countHigherRank(int senapati, int dandanayaka, int chaturangini) const = 0;
    int getId()
    {
        return id;
    }
    string getRank()
    {
        return rank;
    }
    ~Sentinal();
};
Sentinal::~Sentinal() {}

class Senapati : public Sentinal
{
private:
    string name;

public:
    Senapati() {}
    Senapati(int ID, string NAME) : Sentinal(ID, "SENAPATI")
    {
        name = NAME;
    }
    int countHigherRank(int senapati, int dandanayaka, int chaturangini) const override
    {
        return 0;
    }
};

class Dandanayaka : public Sentinal
{
private:
    string name;

public:
    Dandanayaka() {}
    Dandanayaka(int ID, string NAME) : Sentinal(ID, "DANDANAYAKA")
    {
        name = NAME;
    }
    int countHigherRank(int senapati, int dandanayaka, int chaturangini) const override
    {
        return senapati;
    }
};

class Chaturangini : public Sentinal
{
private:
    string name;

public:
    Chaturangini() {}
    Chaturangini(int ID, string NAME) : Sentinal(ID, "CHATURANGINI")
    {
        name = NAME;
    }
    int countHigherRank(int senapati, int dandanayaka, int chaturangini) const override
    {
        return senapati + dandanayaka;
    }
};

struct Comparator
{
    bool operator()(Sentinal *&a, Sentinal *&b)
    {
        if (a->getRank() == b->getRank())
        {
            return a->getId() < b->getId();
        }
        if (a->getRank() == "SENAPATI")
        {
            return true;
        }
        else if (a->getRank() == "DANDANAYAKA")
        {
            if (b->getRank() == "SENAPATI")
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
};

template <typename T>
class Kingdom
{
private:
    vector<vector<int>> adjList;
    pair<int, bool> dfs(int v, int p)
    {
        bool toBeCounted = false;
        int minVertexCover = 0;
        for (auto i : adjList[v])
        {
            if (i != p)
            {
                pair<int, bool> p = dfs(i, v);
                minVertexCover += p.first;
                if (!p.second)
                {
                    toBeCounted = true;
                }
            }
        }
        if (toBeCounted)
        {
            minVertexCover++;
        }
        return {minVertexCover, toBeCounted};
    }

public:
    Kingdom(int n)
    {
        adjList.resize(n);
    }
    void addRoad(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    int findVertexCover()
    {
        return dfs(0, 0).first;
    }
};

int main()
{
    int n;
    cin >> n;
    Kingdom<Sentinal *> kingdom(n);
    Comparator comp;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        kingdom.addRoad(u, v);
    }
    vector<Sentinal *> allSentinals;
    int countOfSenapati = 0, countOfDandanayaka = 0, countOfChaturangini = 0;
    for (int i = 0; i < n; i++)
    {
        string name, rank;
        cin >> name >> rank;
        if (rank == "SENAPATI")
        {
            countOfSenapati++;
            allSentinals.push_back(new Senapati(i, name));
        }
        else if (rank == "DANDANAYAKA")
        {
            countOfDandanayaka++;
            allSentinals.push_back(new Dandanayaka(i, name));
        }
        else
        {
            countOfChaturangini++;
            allSentinals.push_back(new Chaturangini(i, name));
        }
    }

    vector<Sentinal *> copyOfAllSentinals;
    for (int i = 0; i < n; i++)
    {
        copyOfAllSentinals.push_back(allSentinals[i]);
    }

    sort(allSentinals.begin(), allSentinals.end(), comp);
    int minSpan = kingdom.findVertexCover();
    int q;
    cin >> q;
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            cout << minSpan << "\n";
        }
        else if (type == 2)
        {
            for (int i = 0; i < n; i++)
            {
                cout << allSentinals[i]->getId() << " ";
            }
            cout << "\n";
        }
        else
        {
            int i;
            cin >> i;
            cout << copyOfAllSentinals[i]->countHigherRank(countOfSenapati, countOfDandanayaka, countOfChaturangini) << "\n";
        }
    }
}