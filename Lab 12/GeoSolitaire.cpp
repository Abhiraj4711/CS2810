#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

class Card
{
public:
    ~Card();
    virtual bool operator<(Card &other) const = 0;
    virtual ll getArea() const = 0;
    virtual pair<string, vector<ll>> getInfo() const = 0;
    friend void operator>>(std::istream &stream, Card *&c);
    friend void operator<<(std::ostream &stream, Card *c);
};
Card::~Card() {}

class rectangle : public Card
{
private:
    ll length;
    ll breadth;
    ll area;

public:
    rectangle()
    {
        length = breadth = area = 0;
    }
    rectangle(ll l, ll b)
    {
        length = l;
        breadth = b;
        area = l * b;
    }
    bool operator<(Card &other) const override
    {
        return area < other.getArea();
    }
    ll getArea() const override
    {
        return area;
    }
    pair<string, vector<ll>> getInfo() const override
    {
        return {"RECTANGLE", {length, breadth}};
    }
    friend void operator>>(std::istream &stream, Card *&c);
    friend void operator<<(std::ostream &stream, Card *c);
};

class square : public Card
{
private:
    ll edge;
    ll area;

public:
    square()
    {
        edge = area = 0;
    }
    square(ll e)
    {
        edge = e;
        area = e * e;
    }
    bool operator<(Card &other) const override
    {
        return area < other.getArea();
    }
    ll getArea() const override
    {
        return area;
    }
    pair<string, vector<ll>> getInfo() const override
    {
        return {"SQUARE", {edge}};
    }
    friend void operator>>(std::istream &stream, Card *&c);
    friend void operator<<(std::ostream &stream, Card *c);
};

class triangle : public Card
{
private:
    ll height;
    ll base;
    ll area;

public:
    triangle()
    {
        height = base = area = 0;
    }
    triangle(ll b, ll h)
    {
        height = h;
        base = b;
        area = (h * b) / 2;
    }
    bool operator<(Card &other) const override
    {
        return area < other.getArea();
    }
    ll getArea() const override
    {
        return area;
    }
    pair<string, vector<ll>> getInfo() const override
    {
        return {"TRIANGLE", {base, height}};
    }
    friend void operator>>(std::istream &stream, Card *&c);
    friend void operator<<(std::ostream &stream, Card *c);
};

void operator>>(std::istream &stream, Card *&c)
{
    string a;
    stream >> a;
    if (a == "SQUARE")
    {
        ll e;
        stream >> e;
        c = new square(e);
    }
    else if (a == "RECTANGLE")
    {
        ll l, b;
        stream >> l >> b;
        c = new rectangle(l, b);
    }
    else
    {
        ll h, b;
        stream >> h >> b;
        c = new triangle(h, b);
    }
}
void operator<<(std::ostream &stream, Card *c)
{
    pair<string, vector<ll>> p = c->getInfo();
    stream << p.first << " ";
    for (auto i : p.second)
    {
        stream << i << " ";
    }
    stream << "\n";
}

class CardOrganizer
{
private:
    vector<vector<Card *>> piles;
    vector<vector<Card *>> LIS;
    void adjustLIS(Card *c)
    {
        int pos = -1;
        int n = LIS.size();

        for (int i = n - 1; i >= 0; i--)
        {
            if (*(LIS[i].back()) < *c)
            {
                pos = i;
                break;
            }
        }

        vector<Card *> newSeq;
        if (pos != -1)
            newSeq = LIS[pos];

        newSeq.push_back(c);

        if (pos + 1 < n)
            LIS[pos + 1] = newSeq;
        else
            LIS.push_back(newSeq);
    }

public:
    CardOrganizer()
    {
        piles.resize(0);
    }
    void addCard(Card *c)
    {
        adjustLIS(c);
        auto it = std::lower_bound(piles.begin(), piles.end(), c, [](const vector<Card *> &v, Card *c)
                                   { return *(v.back()) < *c; });

        if (it == piles.end())
        {
            piles.push_back({c});
        }
        else
        {
            it->push_back(c);
        }
    }
    size_t getPileCount() const
    {
        return piles.size();
    }
    vector<Card *> getLIS() const
    {
        return LIS.back();
    }
};

int main()
{
    int q;
    cin >> q;
    CardOrganizer CO;
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            Card *c;
            cin >> c;
            CO.addCard(c);
        }
        else if (type == 2)
        {
            cout << CO.getPileCount() << "\n";
        }
        else
        {
            vector<Card *> LIS = CO.getLIS();
            cout << LIS.size() << "\n";
            for (auto c : LIS)
            {
                cout << c;
            }
        }
    }
}