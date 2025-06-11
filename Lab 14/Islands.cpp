#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef long double ld;

class Island
{
private:
    virtual ld findAppRadius(const pair<ll, ll> centre, const pair<ll, ll> vertex) const = 0;
    virtual pair<ll, ll> findCentre() const = 0;

public:
    virtual ~Island();
    virtual string getID() const = 0;
    virtual ld getRadius() const = 0;
    virtual pair<ll, ll> getCentre() const = 0;
    friend void operator>>(std::istream &stream, Island *&I);
    friend void operator<<(std::ostream &stream, Island *I);
};
Island::~Island() {}

class rectangle : public Island
{
private:
    string recID;
    pair<ll, ll> centre;
    pair<ll, ll> p1;
    pair<ll, ll> p2;
    pair<ll, ll> p3;
    pair<ll, ll> p4;
    ld appRadius;

    ld findAppRadius(const pair<ll, ll> centre, const pair<ll, ll> vertex) const override
    {
        ld xSquared = (centre.first - vertex.first) * (centre.first - vertex.first);
        ld ySquared = (centre.second - vertex.second) * (centre.second - vertex.second);
        return sqrtl(xSquared + ySquared);
    }
    pair<ll, ll> findCentre() const override
    {
        ll sumOfX = p1.first + p2.first + p3.first + p4.first;
        ll sumOfY = p1.second + p2.second + p3.second + p4.second;
        return {sumOfX / 4, sumOfY / 4};
    }

public:
    rectangle(string ID, ll x1, ll y1, ll x2, ll y2, ll x3, ll y3, ll x4, ll y4)
    {
        recID = ID;
        p1 = {x1, y1};
        p2 = {x2, y2};
        p3 = {x3, y3};
        p4 = {x4, y4};
        centre = findCentre();
        appRadius = findAppRadius(centre, p4);
    }
    string getID() const override
    {
        return recID;
    }
    ld getRadius() const override
    {
        return appRadius;
    }
    pair<ll, ll> getCentre() const override
    {
        return centre;
    }
};

class circle : public Island
{
private:
    string cirID;
    pair<ll, ll> centre;
    ld radius;

    ld findAppRadius(const pair<ll, ll> centre, const pair<ll, ll> vertex) const override
    {
        return radius;
    }

    pair<ll, ll> findCentre() const override
    {
        return centre;
    }

public:
    circle(string ID, ll x, ll y, ll r)
    {
        cirID = ID;
        centre = {x, y};
        radius = r;
    }
    string getID() const override
    {
        return cirID;
    }
    ld getRadius() const override
    {
        return radius;
    }
    pair<ll, ll> getCentre() const override
    {
        return centre;
    }
};

class triangle : public Island
{
private:
    string triID;
    pair<ll, ll> centre;
    pair<ll, ll> p1;
    pair<ll, ll> p2;
    pair<ll, ll> p3;
    ld appRadius;

    ld findAppRadius(const pair<ll, ll> centre, const pair<ll, ll> vertex) const override
    {
        ld xSquared = (centre.first - vertex.first) * (centre.first - vertex.first);
        ld ySquared = (centre.second - vertex.second) * (centre.second - vertex.second);
        return sqrtl(xSquared + ySquared);
    }

    pair<ll, ll> findCentre() const override
    {
        ll sumOfX = p1.first + p2.first + p3.first;
        ll sumOfY = p1.second + p2.second + p3.second;
        return {sumOfX / 3, sumOfY / 3};
    }

public:
    triangle(string ID, ll x1, ll y1, ll x2, ll y2, ll x3, ll y3)
    {
        triID = ID;
        p1 = {x1, y1};
        p2 = {x2, y2};
        p3 = {x3, y3};
        centre = findCentre();
        appRadius = max(findAppRadius(centre, p1), max(findAppRadius(centre, p2), findAppRadius(centre, p3)));
    }
    string getID() const override
    {
        return triID;
    }
    ld getRadius() const override
    {
        return appRadius;
    }
    pair<ll, ll> getCentre() const override
    {
        return centre;
    }
};

void operator>>(std::istream &stream, Island *&I)
{
    string a;
    stream >> a;
    if (a == "TRIANGLE")
    {
        string ID;
        ll x1, x2, x3, y1, y2, y3;
        stream >> ID >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        I = new triangle(ID, x1, y1, x2, y2, x3, y3);
    }
    else if (a == "RECTANGLE")
    {
        string ID;
        ll x1, x2, x3, y1, y2, y3, x4, y4;
        stream >> ID >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        I = new rectangle(ID, x1, y1, x2, y2, x3, y3, x4, y4);
    }
    else
    {
        string ID;
        ll x, y, r;
        stream >> ID >> x >> y >> r;
        I = new circle(ID, x, y, r);
    }
}
void operator<<(std::ostream &stream, Island *I)
{
    stream << I->getID() << " ";
}

ld getDist(pair<ll, ll> a, pair<ll, ll> b)
{
    return sqrtl((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

vector<Island *> findLongestPath(vector<vector<bool>> &adj, int n, vector<Island *> &islands)
{
    int full = 1 << n;
    vector<vector<vector<Island *>>> dp(n, vector<vector<Island *>>(full));

    for (int i = 0; i < n; ++i)
    {
        dp[i][1 << i] = {islands[i]};
    }

    for (int mask = 0; mask < full; ++mask)
    {
        for (int j = 0; j < n; ++j)
        {
            if (mask & (1 << j))
            {
                for (int k = 0; k < n; ++k)
                {
                    if ((mask & (1 << k)) && adj[k][j] && j != k && !dp[k][mask ^ (1 << j)].empty())
                    {
                        auto candidate = dp[k][mask ^ (1 << j)];
                        candidate.push_back(islands[j]);
                        if (candidate.size() > dp[j][mask].size())
                        {
                            dp[j][mask] = candidate;
                        }
                    }
                }
            }
        }
    }

    vector<Island *> result;
    for (int i = 0; i < n; ++i)
    {
        for (int mask = 0; mask < full; ++mask)
        {
            if (dp[i][mask].size() > result.size())
            {
                result = dp[i][mask];
            }
        }
    }

    return result;
}

int main()
{
    int n;
    cin >> n;
    vector<Island *> islands(n);
    for (int i = 0; i < n; i++)
    {
        Island *I;
        cin >> I;
        islands[i] = I;
    }
    vector<vector<bool>> graphAdjList(n, vector<bool>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j && getDist(islands[i]->getCentre(), islands[j]->getCentre()) <= islands[i]->getRadius() + islands[j]->getRadius() + 1e-6)
            {
                graphAdjList[i][j] = 1;
                graphAdjList[j][i] = 1;
            }
        }
    }
    vector<Island *> path = findLongestPath(graphAdjList, n, islands);
    if (path.size() == n)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n"
             << path.size() << "\n";
    }
    for (auto i : path)
    {
        cout << i;
    }
}