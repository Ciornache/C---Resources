#include <bits/stdc++.h>

#define MAX 1000
#define FILES                       \
    freopen("nano.in", "r", stdin); \
    freopen("nano.out", "w", stdout);
#define CMAX 100000

using namespace std;

class BigNumber
{

private:
    int number[MAX + 5];
    int size;

public:
    BigNumber()
    {
        size = 0;
        memset(number, false, sizeof(number));
    }
    BigNumber(string &&nr)
    {
        memset(number, false, sizeof(number));
        size = nr.size();
        for (int i = size - 1; i >= 0; --i)
            number[size - i] = nr[i] - '0';
    }
    BigNumber(string &nr)
    {
        memset(number, false, sizeof(number));
        size = nr.size();
        for (int i = size - 1; i >= 0; --i)
            number[size - i] = nr[i] - '0';
    }
    void operator+=(const BigNumber B)
    {
        int t = 0;
        size = max(size, B.size);

        for (int i = 1; i <= size; ++i)
        {
            int cif = number[i] + B.number[i] + t;
            number[i] = cif % 10;
            t = cif / 10;
        }
        while (t)
        {
            number[++size] = t % 10;
            t /= 10;
        }
    }

    BigNumber operator+(const BigNumber &big)
    {
        BigNumber newNumber;
        newNumber.size = max(size, big.size);
        int t = 0;

        for (int i = 1; i <= newNumber.size; ++i)
        {
            int cif = number[i] + big.number[i] + t;
            newNumber.number[i] = cif % 10;
            t = cif / 10;
        }
        while (t)
        {
            newNumber.number[++newNumber.size] = t % 10;
            t /= 10;
        }
        return newNumber;
    }

    BigNumber operator-(BigNumber &big)
    {
        BigNumber newNumber;
        newNumber.size = size;
        bool t = 0;

        for (int i = 1; i <= size; ++i)
        {
            int cif = number[i] - big.number[i] - t;
            if (cif < 0)
                t = 1, cif += 10;
            else
                t = 0;

            newNumber.number[i] = cif % 10;
        }
        while (newNumber.size > 1 && newNumber.number[newNumber.size] == 0)
            newNumber.size--;
        return newNumber;
    }

    void operator-=(BigNumber &big)
    {
        bool t = 0;

        for (int i = 1; i <= size; ++i)
        {
            int cif = number[i] - big.number[i] - t;
            if (cif < 0)
                t = 1, cif += 10;
            else
                t = 0;
            number[i] = cif % 10;
        }
        while (size > 1 && number[size] == 0)
            size--;
    }

    void operator*=(long long x)
    {
        long long t = 0;
        for (int i = 1; i <= size; ++i)
        {
            long long cif = number[i] * x + t;
            number[i] = cif % 10;
            t = cif / 10;
        }
        while (t)
        {
            number[++size] = t % 10;
            t /= 10;
        }
    }

    void operator/=(int x)
    {
        int t = 0, cnt = 0;
        BigNumber nr;
        for (int i = size; i >= 1; --i)
        {
            t = t * 10 + number[i];
            nr.number[++cnt] = t / x;
            t %= x;
        }
        reverse(nr.number + 1, nr.number + cnt + 1);
        while (nr.number[cnt] == 0 && cnt > 1)
            cnt--;
        size = cnt;
        for (int i = 1; i <= size; ++i)
            number[i] = nr.number[i];
    }

    int rest(int x)
    {
        int t = 0;
        for (int i = size; i >= 1; --i)
        {
            while (i >= 1 && t <= x)
                t = t * 10 + number[i--];
            i++;
            t %= x;
        }
        return t;
    }

    void operator*=(BigNumber &big)
    {
        long long prod[2 * MAX + 5] = {0};
        for (int i = 1; i <= size; ++i)
        {
            for (int j = 1; j <= big.size; ++j)
                prod[i + j - 1] += number[i] * big.number[j];
        }
        int fSize = size + big.size - 1, t = 0;
        size = fSize;
        for (int i = 1; i <= fSize; ++i)
        {
            int cif = prod[i] + t;
            number[i] = cif % 10;
            t = cif / 10;
        }
        while (t)
        {
            number[++size] = t % 10;
            t /= 10;
        }
    }

    friend ostream &operator<<(ostream &os, BigNumber &big)
    {
        for (int i = big.size; i >= 1; --i)
            os << big.number[i];
        return os;
    }

    bool operator<=(const BigNumber &big)
    {
        if (size > big.size)
            return false;
        else if (big.size > size)
            return true;
        for (int i = size; i >= 1; --i)
        {
            if (number[i] > big.number[i])
                return false;
            else if (big.number[i] > number[i])
                return true;
        }
        return true;
    }

    bool operator<(const BigNumber &big)
    {
        if (size > big.size)
            return false;
        else if (big.size > size)
            return true;
        for (int i = size; i >= 1; --i)
        {
            if (number[i] > big.number[i])
                return false;
            else if (big.number[i] > number[i])
                return true;
        }
        return false;
    }

    bool operator>(const BigNumber &big)
    {
        if (size > big.size)
            return true;
        else if (big.size > size)
            return false;
        for (int i = size; i >= 1; --i)
        {
            if (number[i] > big.number[i])
                return true;
            else if (big.number[i] > number[i])
                return false;
        }
        return true;
    }

    bool operator==(const BigNumber &big)
    {
        if (size != big.size)
            return false;
        for (int i = 1; i <= size; ++i)
            if (number[i] != big.number[i])
                return false;
        return true;
    }
};
int n;
string x;
bool ciur[CMAX + 5];
vector<int> primes;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    FILES
    int t;
    std::cin >> t;
    BigNumber one("1");
    while (t--)
    {
        std::cin >> n >> x;

        if (x.back() == '2' || x.back() == '3' || x.back() == '7' || x.back() == '8')
            continue;
        BigNumber st("0");
        BigNumber dr(x), rez(x);
        while (st <= dr)
        {
            BigNumber mid = st + dr;
            mid /= 2;
            BigNumber prod = mid;
            prod *= mid;
            if (prod == rez)
            {
                std::cout << rez << '\n';
                break;
            }
            else if (prod < rez)
                st = mid + one;
            else
                dr = mid - one;
        }
    }
}
