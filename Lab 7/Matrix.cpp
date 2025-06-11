#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Comparator
{
private:
    bool bit = 0;

public:
    void operator()(string str)
    {
        if (str == "ascending")
        {
            bit = 0;
        }
        else
        {
            bit = 1;
        }
    }
    bool operator()(ll a, ll b)
    {
        return bit ^ (a < b);
    }
};

class Matrix
{
private:
    vector<vector<ll>> v;
    vector<ll> vectorForInversions;
    vector<ll> mergeSort(int a, int b, Comparator &comp, int i)
    {
        if (a == b)
        {
            vector<ll> vec = {v[i][a]};
            return vec;
        }
        int mid = (a + b) / 2;
        vector<ll> left = mergeSort(a, mid, comp, i);
        vector<ll> right = mergeSort(mid + 1, b, comp, i);
        int f = 0, s = 0;
        vector<ll> vec;
        while (f < (int)left.size() && s < (int)right.size())
        {
            if (comp(left[f], right[s]))
            {
                vec.push_back(left[f++]);
            }
            else
            {
                vec.push_back(right[s++]);
            }
        }
        while (f < (int)left.size())
        {
            vec.push_back(left[f++]);
        }
        while (s < (int)right.size())
        {
            vec.push_back(right[s++]);
        }
        return vec;
    }
    ll countInv(int a, int b)
    {
        if (b - a <= 0)
        {
            return 0;
        }
        ll mid = (a + b) / 2;
        ll invleft = countInv(a, mid);
        ll invRight = countInv(mid + 1, b);
        ll inv = 0;
        int p1 = a, p2 = mid + 1;
        vector<int> temp;
        while (p1 <= mid && p2 <= b)
        {
            if (vectorForInversions[p1] <= vectorForInversions[p2])
            {
                temp.push_back(vectorForInversions[p1++]);
            }
            else
            {
                temp.push_back(vectorForInversions[p2++]);
                inv += mid - p1 + 1;
            }
        }
        while (p1 <= mid)
        {
            temp.push_back(vectorForInversions[p1++]);
        }
        while (p2 <= b)
        {
            temp.push_back(vectorForInversions[p2++]);
        }
        for (int i = 0; i <= b - a; i++)
        {
            vectorForInversions[a + i] = temp[i];
        }
        return invleft + invRight + inv;
    }

public:
    Matrix() {}
    Matrix(int n) : v(n, vector<long long>(n, 0)) {}
    void createMat()
    {
        for (auto &i : v)
        {
            for (auto &j : i)
            {
                cin >> j;
            }
        }
    }
    void sortRows(Comparator comp)
    {
        for (int i = 0; i < (int)v.size(); i++)
        {
            v[i] = mergeSort(0, (int)v[i].size() - 1, comp, i);
        }
    }
    ll countInversions()
    {
        vectorForInversions.clear();
        vectorForInversions.resize(0);
        for (int i = 0; i < (int)v.size(); i++)
        {
            for (int j = 0; j < (int)v.size(); j++)
            {
                vectorForInversions.push_back(v[i][j]);
            }
        }

        return countInv(0, (int)vectorForInversions.size() - 1);
    }
    void display()
    {
        for (auto &i : v)
        {
            for (auto &j : i)
            {
                cout << j << " ";
            }
            cout << "\n";
        }
    }
};

#include <bits/stdc++.h>
using namespace std;

class PlayerPos
{
private:
    vector<pair<int, int>> pos;
    vector<pair<int, int>> poss;

    double closestDist(pair<int, int> p1, pair<int, int> p2)
    {
        double dx = p1.first - p2.first;
        double dy = p1.second - p2.second;
        return sqrt(dx * dx + dy * dy);
    }

    pair<double, pair<int, int>> findStrip(vector<tuple<int, int, int>> &strip, double distance)
    {
        pair<int, int> closestPair = {0, 1};
        double minDist = distance;

        sort(strip.begin(), strip.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b)
             { return get<1>(a) < get<1>(b); });

        for (int i = 0; i < (int)strip.size(); i++)
        {
            for (int j = i + 1; j < (int)strip.size() && (get<1>(strip[j]) - get<1>(strip[i])) < minDist; j++)
            {
                double dist = closestDist({get<0>(strip[i]), get<1>(strip[i])}, {get<0>(strip[j]), get<1>(strip[j])});
                if (dist < minDist)
                {
                    closestPair = {i, j};
                    minDist = dist;
                }
            }
        }
        return {minDist, closestPair};
    }

    pair<int, int> findClosest(int a, int b)
    {
        if (b - a == 1)
        {
            return {a, b};
        }
        if (b - a < 1)
        {
            return {1, (int)pos.size() - 1};
        }

        int mid = (a + b) / 2;
        pair<int, int> left = findClosest(a, mid);
        pair<int, int> right = findClosest(mid + 1, b);

        double distLeft = closestDist(poss[left.first], poss[left.second]);
        double distRight = closestDist(poss[right.first], poss[right.second]);

        double minDist;
        pair<int, int> closestPair;
        if (distLeft <= distRight)
        {
            minDist = distLeft;
            closestPair = left;
        }
        else
        {
            minDist = distRight;
            closestPair = right;
        }

        vector<tuple<int, int, int>> strip;
        for (int i = a; i <= b; i++)
        {
            if (abs(poss[i].first - poss[mid].first) <= minDist)
            {
                strip.emplace_back(poss[i].first, poss[i].second, i);
            }
        }

        pair<double, pair<int, int>> stripResult = findStrip(strip, minDist);
        if (stripResult.first < minDist)
        {
            pair<int, int> stripPair = stripResult.second;
            return {get<2>(strip[stripPair.first]), get<2>(strip[stripPair.second])};
        }

        return closestPair;
    }

public:
    PlayerPos() {}

    PlayerPos(int n)
    {
        pos.resize(n);
        poss.resize(n);
    }

    void inputPos()
    {
        for (auto &i : pos)
        {
            cin >> i.first >> i.second;
        }
        for (int i = 0; i < (int)pos.size(); i++)
        {
            poss[i].first = pos[i].first;
            poss[i].second = pos[i].second;
        }

        sort(poss.begin(), poss.end(), [](const pair<int, int> &a, const pair<int, int> &b)
             {
            if (a.first != b.first) 
                return a.first < b.first;
            return a.second < b.second; });
    }

    void closestPair()
    {
        pair<int, int> p = findClosest(0, (int)poss.size() - 1);
        pair<int, int> p1 = {-1, -1};
        bool found = false;
        for (int i = 0; i < (int)pos.size(); i++)
        {
            if (pos[i] == poss[p.first])
            {
                if (found)
                {
                    p1.second = i;
                }
                else
                {
                    p1.first = i;
                    found = true;
                }
            }
            if (pos[i] == poss[p.second])
            {
                if (found)
                {
                    p1.second = i;
                }
                else
                {
                    p1.first = i;
                    found = true;
                }
            }
        }

        cout << pos[p1.first].first << " " << pos[p1.first].second << " "
             << pos[p1.second].first << " " << pos[p1.second].second << "\n";
    }
};

int main()
{
    string str;
    Matrix mat;
    PlayerPos pp;
    Comparator comp;
    while (cin >> str)
    {
        if (str == "CREATE_2D")
        {
            int n;
            cin >> n;
            mat = Matrix(n);
            mat.createMat(); // done
        }
        else if (str == "SORT_2D")
        {
            cin >> str;
            comp(str);
            mat.sortRows(comp); // Done
        }
        else if (str == "INVERSION_2D")
        {
            cout << mat.countInversions() << "\n";
        }
        else if (str == "DISPLAY_2D")
        {
            mat.display(); // done
        }
        else if (str == "CLOSEST_2D")
        {
            int n;
            cin >> n;
            pp = PlayerPos(n);
            pp.inputPos();    // done
            pp.closestPair(); // done
        }
        else
        {
            break;
        }
    }
}