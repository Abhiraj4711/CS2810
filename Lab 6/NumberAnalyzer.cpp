#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class CurrencySorter
{
private:
    ll MOM(vector<ll> &v, int start, int end)
    {
        int mid = start + (end - start) / 2;
        if (v[start] > v[mid])
            swap(v[start], v[mid]);
        if (v[start] > v[end])
            swap(v[start], v[end]);
        if (v[mid] > v[end])
            swap(v[mid], v[end]);
        return mid;
    }
    void quicksort(vector<ll> &v, int start, int end)
    {
        if (start >= end)
        {
            return;
        }
        ll index = MOM(v, start, end);

        swap(v[start], v[index]);
        index = start;
        int tempEnd = end;
        int i = start + 1;
        while (i <= tempEnd)
        {
            if (v[index] >= v[i])
            {
                swap(v[index], v[i]);
                index++;
                i++;
            }
            else
            {
                swap(v[i], v[tempEnd]);
                tempEnd--;
            }
        }
        quicksort(v, start, index - 1);
        quicksort(v, index + 1, end);
    }

public:
    void operator()(vector<ll> &v)
    {
        quicksort(v, 0, (ll)v.size() - 1);
    }
};

class FibonacciGenerator
{
private:
    const ll MOD = 1e9 + 7;

public:
    void matMult(ll a[2][2], ll b[2][2], ll ans[2][2])
    {
        ll c[2][2];
        c[0][0] = (a[0][0] * b[0][0] % MOD + a[0][1] * b[1][0] % MOD) % MOD;
        c[0][1] = (a[0][0] * b[0][1] % MOD + a[0][1] * b[1][1] % MOD) % MOD;
        c[1][0] = (a[1][0] * b[0][0] % MOD + a[1][1] * b[1][0] % MOD) % MOD;
        c[1][1] = (a[1][0] * b[0][1] % MOD + a[1][1] * b[1][1] % MOD) % MOD;

        ans[0][0] = c[0][0];
        ans[0][1] = c[0][1];
        ans[1][0] = c[1][0];
        ans[1][1] = c[1][1];
    }

    void binpowMat(ll mat[2][2], ll n, ll res[2][2])
    {
        while (n > 0)
        {
            if (n % 2)
                matMult(res, mat, res);
            matMult(mat, mat, mat);
            n /= 2;
        }
    }

    ll operator()(ll n)
    {
        if (n == 0)
            return 0;
        ll res[2][2] = {{1, 0}, {0, 1}};
        ll mat[2][2] = {{1, 1}, {1, 0}};
        binpowMat(mat, n - 1, res);
        return res[0][0];
    }
};

class PrimeCalculator
{
private:
    vector<bool> prime;
    void precomputePrimes()
    {
        prime[0] = 0;
        prime[1] = 0;
        for (int i = 2; i * i < 1e6 + 1; i++)
        {
            if (prime[i])
            {
                for (int j = i * i; j < 1e6 + 1; j += i)
                {
                    prime[j] = 0;
                }
            }
        }
    }

public:
    PrimeCalculator()
    {
        prime = vector<bool>(1000001, 1);
        precomputePrimes();
    }
    vector<ll> FindPrimes(ll L, ll R)
    {
        if (L > R)
            return {};

        vector<bool> isPrime(R - L + 1, true);
        if (L == 1)
            isPrime[0] = false;
        if (L == 0)
            isPrime[0] = isPrime[1] = false;

        for (ll i = 2; i * i <= R; i++)
        {
            if (prime[i])
            {
                ll start = max(i * i, ((L + i - 1) / i) * i);
                for (ll j = start; j <= R; j += i)
                {
                    isPrime[j - L] = false;
                }
            }
        }
        vector<ll> primeList;
        for (ll i = 0; i < (ll)isPrime.size(); i++)
        {
            if (isPrime[i])
            {
                primeList.push_back(L + i);
            }
        }
        return primeList;
    }
    void PrintPrimes(ll L, ll R)
    {
        for (auto i : FindPrimes(L, R))
        {
            cout << i << " ";
        }
        cout << "\n";
    }
    void PrintPrimeSum(ll L, ll R)
    {
        ll sum = 0;
        for (auto i : FindPrimes(L, R))
        {
            sum += i;
        }
        cout << sum << "\n";
    }
};

class NumberAnalyzer
{
public:
    bool isSquareFree(int X)
    {
        if (X % (4) == 0)
        {
            return false;
        }
        for (int i = 3; i * i <= X; i += 2)
        {
            if (X % (i * i) == 0)
            {
                return false;
            }
        }
        return true;
    }

    int countDivisors(int X)
    {
        int num = 0;
        for (int i = 1; i * i <= X; i++)
        {
            if (X % i == 0)
            {
                num++;
                if (i != X / i)
                {
                    num++;
                }
            }
        }
        return num;
    }

    int sumOfDivisors(int X)
    {
        int sum = 0;
        for (int i = 1; i * i <= X; i++)
        {
            if (X % i == 0)
            {
                sum += i;
                if (i != X / i)
                {
                    sum += X / i;
                }
            }
        }
        return sum;
    }
};

int main()
{
    int t;
    cin >> t;
    if (t == 1)
    {
        CurrencySorter cs;
        int tt;
        cin >> tt;
        while (tt--)
        {
            ll n;
            cin >> n;
            vector<ll> v(n);
            for (auto &i : v)
            {
                cin >> i;
            }
            cs(v);
            for (int i = 0; i < n; i++)
            {
                cout << v[i] << " ";
            }
            cout << "\n";
        }
    }
    else if (t == 2)
    {
        FibonacciGenerator fg;
        int tt;
        cin >> tt;
        while (tt--)
        {
            ll n;
            cin >> n;
            cout << fg(n) << "\n";
        }
    }
    else if (t == 3)
    {
        PrimeCalculator pc;
        int tt;
        cin >> tt;
        while (tt--)
        {
            string str;
            cin >> str;
            if (str == "printPrimes")
            {
                ll L, R;
                cin >> L >> R;
                pc.PrintPrimes(L, R);
            }
            else
            {
                ll L, R;
                cin >> L >> R;
                pc.PrintPrimeSum(L, R);
            }
        }
    }
    else
    {
        int tt;
        cin >> tt;
        while (tt--)
        {
            NumberAnalyzer na;
            string str;
            cin >> str;
            if (str == "isSquareFree")
            {
                ll n;
                cin >> n;
                if (na.isSquareFree(n))
                {
                    cout << "yes" << "\n";
                }
                else
                {
                    cout << "no" << "\n";
                }
            }
            else if (str == "countDivisors")
            {
                ll n;
                cin >> n;
                cout << na.countDivisors(n) << "\n";
            }
            else
            {
                int n;
                cin >> n;
                cout << na.sumOfDivisors(n) << "\n";
            }
        }
    }
}