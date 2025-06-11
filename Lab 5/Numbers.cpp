#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MOD 1000000007LL

vector<bool> prime(1e6 + 1, 1);
void precomputePrimes()
{
    prime[0] = 0;
    prime[1] = 0;
    for (int i = 2; i < 1e6 + 1; i++)
    {
        if (prime[i])
        {
            for (int j = i * 2; j < 1e6 + 1; j += i)
            {
                prime[j] = 0;
            }
        }
    }
}

class Numbers
{
public:
    double add(double a, double b)
    {
        return a + b;
    }
    double sub(double a, double b)
    {
        return a - b;
    }
    double mult(double a, double b)
    {
        return a * b;
    }
    ll gcdF(ll a, ll b)
    {
        if (b % a == 0)
        {
            return a;
        }
        return gcdF(b % a, a);
    }
    pair<ll, ll> reduce(ll a, ll b)
    {
        ll gcdNum = gcdF((ll)a, (ll)b);
        pair<ll, ll> p = make_pair((ll)(a / gcdNum), (ll)(b / gcdNum));
        return p;
    }
    ll powFunc(ll a, ll power)
    {
        if (power == 1)
        {
            return a;
        }
        else if (power == 0)
        {
            return 1;
        }
        if (power % 2)
        {
            return ((a * (powFunc((a * a) % MOD, (power - 1) / 2)) % MOD) % MOD);
        }
        else
        {
            return ((powFunc((a * a) % MOD, power / 2)) % MOD);
        }
    }
    ll modInv(ll a)
    {
        return powFunc(a, MOD - 2);
    }
};

class Complex : public Numbers
{
public:
    void addComplex()
    {
        double a1, a2, b1, b2;
        cin >> a1 >> a2 >> b1 >> b2;
        cout << setiosflags(ios::fixed) << setprecision(3) << add(a1, b1) << " " << add(a2, b2) << "\n";
    }
    void subComplex()
    {
        double a1, a2, b1, b2;
        cin >> a1 >> a2 >> b1 >> b2;
        cout << setiosflags(ios::fixed) << setprecision(3) << sub(a1, b1) << " " << sub(a2, b2) << "\n";
    }
    void mulComplex()
    {
        double a1, a2, b1, b2;
        cin >> a1 >> a2 >> b1 >> b2;
        cout << setiosflags(ios::fixed) << setprecision(3) << add(mult(a1, b1), -1.0 * mult(a2, b2)) << " " << add(mult(a1, b2), mult(a2, b1)) << "\n";
    }
};
class Rational : public Numbers
{
public:
    void addRat()
    {
        double a1, a2, b1, b2;
        cin >> a1 >> b1 >> a2 >> b2;
        double a = a1 / b1;
        double b = a2 / b2;
        cout << setiosflags(ios::fixed) << setprecision(3) << a + b << "\n";
    }
    void subRat()
    {
        double a1, a2, b1, b2;
        cin >> a1 >> b1 >> a2 >> b2;
        double a = a1 / b1;
        double b = a2 / b2;
        cout << setiosflags(ios::fixed) << setprecision(3) << a - b << "\n";
    }
    void multRat()
    {
        double a1, a2, b1, b2;
        cin >> a1 >> b1 >> a2 >> b2;
        double a = a1 / b1;
        double b = a2 / b2;
        cout << setiosflags(ios::fixed) << setprecision(3) << a * b << "\n";
    }
    void reduceRat()
    {
        ll a, b;
        cin >> a >> b;
        if (a == 0)
        {
            cout << 0 << " " << abs(b) << "\n";
            return;
        }
        pair<ll, ll> p = reduce(abs(a), abs(b));
        if (((b < 0) && (a > 0)) || (b > 0 && a < 0))
        {
            p.first *= -1;
        }
        cout << p.first << " " << p.second << "\n";
    }
};

class Natural : public Rational
{
public:
    void inverse()
    {
        ll a;
        cin >> a;
        cout << modInv(a) << "\n";
    }
    void checkPrime()
    {
        ll a;
        cin >> a;
        if (prime[a])
        {
            cout << "1\n";
        }
        else
        {
            cout << "0\n";
        }
    }
};

int main()
{
    precomputePrimes();
    int n;
    cin >> n;
    Natural nat;
    Rational rat;
    Complex com;
    while (n--)
    {
        string str1, str2;
        cin >> str1 >> str2;
        if (str1 == "complex")
        {
            if (str2 == "add")
            {
                com.addComplex();
            }
            else if (str2 == "sub")
            {
                com.subComplex();
            }
            else
            {
                com.mulComplex();
            }
        }
        else if (str1 == "rational")
        {
            if (str2 == "add")
            {
                rat.addRat();
            }
            else if (str2 == "sub")
            {
                rat.subRat();
            }
            else if (str2 == "mult")
            {
                rat.multRat();
            }
            else
            {
                rat.reduceRat();
            }
        }
        else
        {
            if (str2 == "isprime")
            {
                nat.checkPrime();
            }
            else
            {
                nat.inverse();
            }
        }
    }
}