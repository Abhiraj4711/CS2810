#include "bits/stdc++.h"
using namespace std;
typedef long long int ll;
typedef long double ld;

class Complex
{
private:
    ll real;
    ll imag;

public:
    Complex()
    {
        real = 0;
        imag = 0;
    }
    Complex(ll realPart, ll imagPart)
    {
        real = realPart;
        imag = imagPart;
    }
    ll getReal()
    {
        return real;
    }
    ll getImag()
    {
        return imag;
    }
    Complex operator*(const Complex &other) const
    {
        Complex ans(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
        return ans;
    }
    Complex operator+(const Complex &other) const
    {
        Complex ans(real + other.real, imag + other.imag);
        return ans;
    }
    Complex operator-(const Complex &other) const
    {
        Complex ans(real - other.real, imag - other.imag);
        return ans;
    }
};

template <typename T>
class Multiply
{
private:
    vector<T> divideAndConquer(vector<T> a, vector<T> b)
    {
        int n = a.size();
        int m = n / 2;

        if (n == 1)
            return {a[0] * b[0], T()};

        vector<T> A(a.begin(), a.begin() + m);
        vector<T> B(a.begin() + m, a.end());
        vector<T> C(b.begin(), b.begin() + m);
        vector<T> D(b.begin() + m, b.end());

        vector<T> E(m), F(m);
        for (int i = 0; i < m; i++)
        {
            E[i] = A[i] + B[i];
            F[i] = C[i] + D[i];
        }

        vector<T> z0 = divideAndConquer(A, C);
        vector<T> z2 = divideAndConquer(B, D);
        vector<T> z1 = divideAndConquer(E, F);

        for (int i = 0; i < m * 2; i++)
        {
            z1[i] = z1[i] - z0[i];
            z1[i] = z1[i] - z2[i];
        }

        vector<T> ans(2 * n, T());
        for (int i = 0; i < (ll)z0.size(); i++)
            ans[i] = z0[i] + ans[i];
        for (int i = 0; i < (ll)z1.size(); i++)
            ans[i + m] = z1[i] + ans[i + m];
        for (int i = 0; i < (ll)z2.size(); i++)
            ans[i + 2 * m] = z2[i] + ans[i + 2 * m];

        return ans;
    }

public:
    vector<T> MultiplyPolynomials(vector<T> a, vector<T> b)
    {
        vector<T> ans = divideAndConquer(a, b);
        return ans;
    }
};

template <typename T>
class Evaluate
{
public:
    T evaluatePolynomial(vector<ll> &coeff, ll x)
    {
        ll temp = 1;
        ll ans = 0;
        for (ll i : coeff)
        {
            ans += temp * i;
            temp *= x;
        }
        return ans;
    }

    T evaluatePolynomial(vector<ld> &coeff, ll x)
    {
        ld temp = 1;
        ld ans = 0;
        for (ld i : coeff)
        {
            ans += temp * i;
            temp *= x;
        }
        return ans;
    }

    T evaluatePolynomial(vector<string> &coeff, ll x)
    {
        string ans = "";
        for (int i = coeff.size() - 1; i >= 0; i--)
        {
            for (int j = 0; j < pow(x, i); j++)
            {
                ans += coeff[i];
            }
        }
        return ans;
    }
};

template <typename T>
class Differentiate
{
public:
    vector<T> differentiatePolynomial(vector<T> &coeff)
    {
        if ((ll)coeff.size() <= 1)
        {
            vector<T> ans = {0};
            return ans;
        }
        vector<T> ans((ll)coeff.size() - 1LL, 0);
        for (ll i = 1; i < (ll)coeff.size(); i++)
        {
            ans[i - 1] = coeff[i] * i;
        }
        return ans;
    }
};

template <typename T>
class Polynomial
{
private:
    vector<T> coeff;

public:
    Polynomial();
    Polynomial(const vector<T> coefficient)
    {
        for (auto i : coefficient)
        {
            coeff.push_back(i);
        }
    }
    Polynomial<T> operator*(Polynomial<T> &other)
    {
        Multiply<T> m;
        Polynomial<T> ans = m.MultiplyPolynomials(coeff, other.coeff);
        return ans;
    }
    T eval(ll x)
    {
        Evaluate<T> e;
        return e.evaluatePolynomial(coeff, x);
    }
    Polynomial<T> diff()
    {
        Differentiate<T> d;
        Polynomial<T> p(d.differentiatePolynomial(coeff));
        return p;
    }
    void printPolynomial(int n)
    {

        for (int i = 0; i < n; i++)
        {
            cout << fixed << setprecision(6) << coeff[i] << " ";
        }
        cout << "\n";
    }
    void printPolynomial(Complex c, int n)
    {

        for (int i = 0; i < n; i++)
        {
            cout << coeff[i].getReal() << " " << coeff[i].getImag() << " ";
        }
        cout << "\n";
    }
};

int main()
{
    ll q;
    cin >> q;
    while (q--)
    {
        ll op;
        cin >> op;
        if (op == 1)
        {
            string str;
            cin >> str;
            if (str == "integer")
            {
                int coeff1, coeff2;
                cin >> coeff1;
                vector<ll> av(coeff1);
                for (auto &i : av)
                {
                    cin >> i;
                }
                av.resize(16, 0);
                Polynomial<ll> a(av);
                cin >> coeff2;
                vector<ll> bv(coeff2);
                for (auto &i : bv)
                {
                    cin >> i;
                }
                bv.resize(16, 0);
                Polynomial<ll> b(bv);
                Polynomial<ll> c = a * b;
                c.printPolynomial(coeff1 + coeff2 - 1);
            }
            else if (str == "float")
            {
                int coeff1, coeff2;
                cin >> coeff1;
                vector<ld> av(coeff1);
                for (auto &i : av)
                {
                    cin >> i;
                }
                av.resize(16, 0.0);
                Polynomial<ld> a(av);
                cin >> coeff2;
                vector<ld> bv(coeff2);
                for (auto &i : bv)
                {
                    cin >> i;
                }
                bv.resize(16, 0.0);
                Polynomial<ld> b(bv);
                Polynomial<ld> c = a * b;
                c.printPolynomial(coeff1 + coeff2 - 1);
            }
            else if (str == "complex")
            {
                int coeff1, coeff2;
                cin >> coeff1;
                vector<Complex> av;
                for (int i = 0; i < coeff1; i++)
                {
                    ll a, b;
                    cin >> a >> b;
                    Complex c(a, b);
                    av.push_back(c);
                }
                av.resize(16, Complex());
                Polynomial<Complex> a(av);
                cin >> coeff2;
                vector<Complex> bv;
                for (int i = 0; i < coeff2; i++)
                {
                    ll a, b;
                    cin >> a >> b;
                    Complex c(a, b);
                    bv.push_back(c);
                }
                bv.resize(16, Complex());
                Polynomial<Complex> b(bv);
                Polynomial<Complex> c = a * b;
                Complex t(0, 0);
                c.printPolynomial(t, coeff1 + coeff2 - 1);
            }
        }
        else if (op == 2)
        {
            string str;
            cin >> str;
            if (str == "integer")
            {
                int coeff1;
                cin >> coeff1;
                vector<ll> av(coeff1);
                for (auto &i : av)
                {
                    cin >> i;
                }
                Polynomial<ll> a(av);
                ll x;
                cin >> x;
                cout << a.eval(x) << "\n";
            }
            else if (str == "float")
            {
                int coeff1;
                cin >> coeff1;
                vector<ld> av(coeff1);
                for (auto &i : av)
                {
                    cin >> i;
                }
                Polynomial<ld> a(av);
                ll x;
                cin >> x;
                cout << fixed << setprecision(6) << a.eval(x) << "\n";
            }
            else if (str == "string")
            {
                int coeff1;
                cin >> coeff1;
                vector<string> av(coeff1);
                for (auto &i : av)
                {
                    cin >> i;
                }
                Polynomial<string> a(av);
                ll x;
                cin >> x;
                cout << a.eval(x) << "\n";
            }
        }
        else if (op == 3)
        {
            string str;
            cin >> str;
            if (str == "integer")
            {
                int coeff1;
                cin >> coeff1;
                vector<ll> av(coeff1);
                for (auto &i : av)
                {
                    cin >> i;
                }
                Polynomial<ll> a(av);
                Polynomial<ll> b = a.diff();
                b.printPolynomial(coeff1 - 1);
            }
            else if (str == "float")
            {
                int coeff1;
                cin >> coeff1;
                vector<ld> av(coeff1);
                for (auto &i : av)
                {
                    cin >> i;
                }
                Polynomial<ld> a(av);
                Polynomial<ld> b = a.diff();
                b.printPolynomial(coeff1 - 1);
            }
        }
    }
}