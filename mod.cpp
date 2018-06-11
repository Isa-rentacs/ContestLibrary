#include <iostream>
using namespace std;

/*
   nCk mod p 
   nCk =  n! / ((n-k)! * k!)
   nCk mod p = ((n! mod p) * (((n-k)!)^-1 mod p) * ((k!)^-1 mod p)) mod p
*/

/*
    init : O(n)
    query : O(1)
    constraint : 1 < k <= n < (about 10^7), mod is a prime, k,n < mod

    inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;

    p = (p / a) * a + (p % a)
    ( mod p * a^-1 for both ) <=> 0 = (p / a) + (p % a) * a^-1
    <=> - (p/a) = (p % a) * a^-1
    <=> a^-1 = - (p/a)^-1 * (p/a)
    <=> a^-1 = MOD - (p/a)^-1 * (p/a) % MOD

*/
const int MAX_K = 300000;
bool fact_initialized = false;
long long fact[MAX_K], fact_inv[MAX_K], inv[MAX_K];

void combination_init(int mod)
{
    fact[0] = fact[1] = 1;
    fact_inv[0] = fact_inv[1] = 1;
    inv[1] = 1;

    for(int i = 2; i < MAX_K; ++i)
    {
        fact[i] = fact[i-1] * i % mod;
        inv[i] = mod - inv[mod % i] * (mod / i) % mod;
        fact_inv[i] = fact_inv[i-1] * inv[i] % mod;
    }
}

long long combination_mod(int n, int k, int mod)
{
    if (n < k || n < 0 || k < 0) return 0;
    if(!fact_initialized)
    {
        combination_init(mod);
        fact_initialized = true;
    } 
    cout << fact[n] << endl;
    cout << fact_inv[k] << endl;
    cout << fact_inv[n-k] << endl;
    return fact[n] * (fact_inv[k] * fact_inv[n-k] % mod) % mod;
}

/*
    extGCD
    calculate (x, y) where ax + by = gcd(a,b)
*/
long long extGCD(long long a, long long b, long long &x, long long &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    long long d = extGCD(b, a%b, y, x);
    y -= a / b  *x;
    return d;
}

/*
    mod (a can be negative)
*/
long long modulo(long long a, long long mod)
{
    return (a % mod + mod) % mod;
}

/*
    mod inverse
    return x where ax mod p === 1

    constraint : gcd(a, m) = 1
*/
long long mod_inverse(long long a, long long mod)
{
    long long x, y;
    extGCD(a, mod, x, y);
    return modulo(x, mod);
}

/*
    init : O(k)
    runtime : O(k)
    constraint : mod is a prime, n,k < mod
    nCk = (n/1) * ((n-1)/2) * ((n-2)/3) ... * (n-k+1)/k
*/

long long combination_mod2(int n, int k, int mod)
{
    if (n < k || n < 0 || k < 0) return 0;

    long long ret = 1;
    while(true)
    {
        if(k == 0) break;
        int tmp_n = n % mod;
        int tmp_k = k % mod;
        if (tmp_n < tmp_k) return 0;

        for(int i=0; i < tmp_k; i++)
        {
            ret = ret * (tmp_n - i) % mod;
        }
        
        long long div = 1;
        for(int i=0; i < tmp_k; ++i)
        {
            div = div * (i+1) % mod;
        }

        ret = ret * mod_inverse(div, mod) % mod;
        n /= mod;
        k /= mod;
    }

    return ret;
}

int main()
{
    int n = 10;
    int k = 2;
    int mod = 1000000007;

    cout << "nCk : n = " << n << ", k = " << k << ", mod = " << mod << endl;
    cout << combination_mod(n, k, mod) << endl;
    cout << combination_mod2(n, k, mod) << endl;
}