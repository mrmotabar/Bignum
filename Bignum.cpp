/*mohammadreza motabar*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;
class Bignum
{
public:
	static const int MAX_N = 1e3;
	static const int MOD = 10;
	ll d[MAX_N], sizd = 0;
	Bignum(ll x = 0)
	{
		memset(d, 0, sizeof d);
		sizd = 0;
		d[sizd] = x;
		relax();
	}
	Bignum(const Bignum &b)
	{
		memset(d, 0, sizeof d);
		sizd = b.sizd;
		for (int i = 0; i <= sizd; i++)
		{
			d[i] = b.d[i];
		}
	}
	void relax()
	{
		for (int i = 0; i <= sizd; i++)
		{
			d[i + 1] += d[i] / MOD;
			d[i] %= MOD;
			if (d[sizd + 1] > 0)
			{
				sizd++;
			}
		}
		while (sizd && !d[sizd])
		{
			sizd--;
		}
	}
	inline Bignum operator+(const Bignum &b) const
	{
		Bignum ret = 0;
		int dah_bar_yek = 0;
		for (int i = 0; i <= max(b.sizd, sizd); i++)
		{
			ret.d[i] = d[i] + b.d[i] + dah_bar_yek;
			dah_bar_yek = ret.d[i] / MOD;
			ret.d[i] = ret.d[i] % MOD;
		}
		ret.sizd = max(sizd, b.sizd);
		if (dah_bar_yek > 0)
		{
			ret.sizd++;
			ret.d[ret.sizd] = dah_bar_yek;
		}
		return ret;
	}
	inline Bignum operator+=(const Bignum &b)
	{
		return *this = *this + b;
	}
	inline Bignum operator+(const int &b) const
	{
		Bignum ret = *this;
		ret.d[0] += b;
		ret.relax();
		return ret;
	}
	inline Bignum operator+=(const int &b)
	{
		return *this = *this + b;
	}
	inline Bignum operator*(const Bignum &b) const
	{
		Bignum ret = 0;
		ret.sizd = sizd + b.sizd;
		for (int i = 0; i <= sizd; i++)
		{
			for (int j = 0; j <= b.sizd; j++)
			{
				ret.d[i + j] += d[i] * b.d[j];
			}
		}
		ret.relax();
		return ret;
	}
	inline Bignum operator*=(const Bignum &b)
	{
		return *this = *this * b;
	}
	inline Bignum operator*(const int &b) const
	{
		Bignum ret = 0, g = b;
		ret.sizd = sizd + g.sizd;
		for (int i = 0; i <= sizd; i++)
		{
			for (int j = 0; j <= g.sizd; j++)
			{
				ret.d[i + j] += d[i] * g.d[j];
			}
		}
		ret.relax();
		return ret;
	}
	inline Bignum operator*=(const int &b)
	{
		return *this = *this * b;
	}
	inline Bignum operator-(const Bignum &b)
	{
		Bignum ret = 0;
		for (int i = 0; i <= max(b.sizd, sizd); i++)
		{
			if (d[i] >= b.d[i])
			{
				ret.d[i] = d[i] - b.d[i];
			}
			else
			{
				d[i] += 10;
				d[i + 1]--;
				ret.d[i] = d[i] - b.d[i];
			}
		}
		ret.sizd = max(sizd, b.sizd);
		ret.relax();
		return ret;
	}
	inline Bignum operator-=(const Bignum &b)
	{
		return *this = *this - b;
	}
	inline Bignum &operator++()
	{
		(*this).d[0] += 1;
		(*this).relax();
		return *this;
	}
	inline Bignum operator--()
	{
		int i = 0;
		while (d[i] == 0)
		{
			i++;
			if (d[i] > 0)
			{
				d[i]--;
				for (int j = i - 1; j >= 1; j--)
				{
					d[j] = 9;
				}
				d[0] = 10;
				d[0]--;
			}
		}
		return *this;
	}
	inline Bignum operator^(const int x)
	{
		int y = x;
		Bignum r = *this;
		Bignum ret = 1;
		while (y > 0)
		{
			if (y % 2 == 1)
			{
				ret *= r;
			}
			r *= r;
			y /= 2;
		}
		return ret;
	}
	inline Bignum operator/(Bignum &b)
	{
		Bignum ret = 0;
		string s = " ";
		for (int i = sizd; i >= 0; i--)
		{
			for (int j = ret.sizd + 1; j >= 1; j--)
			{
				ret.d[j] = ret.d[j - 1];
			}
			ret.d[0] = d[i];
			if (i < sizd)
			{
				ret.sizd++;
			}
			ret.relax();
			for (int j = 1; j <= 10; j++)
			{
				Bignum h = j;
				if (ret < h * b)
				{
					ret -= ((h - 1) * b);
					ret.relax();
					s += char(j - 1 + int('0'));
					break;
				}
			}
		}
		Bignum jav = 0;
		for (int i = s.size() - 1; i >= 1; i--)
		{
			jav.d[s.size() - 1 - i] = int(s[i]) - int('0');
		}
		jav.sizd = s.size();
		jav.relax();
		return jav;
	}
	inline Bignum operator/=(Bignum &b)
	{
		return *this = *this / b;
	}
	inline Bignum operator%(Bignum &b)
	{
		Bignum ret = 0;
		for (int i = sizd; i >= 0; i--)
		{
			for (int j = ret.sizd + 1; j >= 1; j--)
			{
				ret.d[j] = ret.d[j - 1];
			}
			ret.d[0] = d[i];
			if (i < sizd)
			{
				ret.sizd++;
			}
			ret.relax();
			for (int j = 1; j <= 10; j++)
			{
				Bignum h = j;
				if (ret < h * b)
				{
					ret -= ((h - 1) * b);
					ret.relax();
					break;
				}
			}
		}
		return ret;
	}
	inline Bignum sqr()
	{
		Bignum ret = 0;
		Bignum kh = 0;
		int t = 0;
		for (int i = sizd; i >= 0; i--)
		{
			if ((sizd + 1) % 2 == 1 && i == sizd)
			{
				ret = d[sizd];
			}
			else if ((sizd + 1) % 2 == 0 && i == sizd)
			{
				ret = d[sizd] * 10 + d[sizd - 1];
				i--;
			}
			else
			{
				for (int j = ret.sizd + 2; j >= 2; j--)
				{
					ret.d[j] = ret.d[j - 2];
				}
				ret.d[0] = d[i - 1];
				ret.d[1] = d[i];
				ret.sizd += 2;
				i--;
			}
			if (t > 0)
			{
				for (int h = 1; h <= 10; h++)
				{
					Bignum g = (kh * 20);
					g += h;
					g *= h;
					if (g > ret)
					{
						Bignum z = (kh * 20);
						z += (h - 1);
						z *= (h - 1);
						ret -= z;
						ret.relax();
						for (int j = kh.sizd + 1; j >= 1; j--)
						{
							kh.d[j] = kh.d[j - 1];
						}
						kh.d[0] = h - 1;
						kh.sizd++;
						break;
					}
				}
			}
			else
			{
				for (int h = 1; h <= 10; h++)
				{
					Bignum l = h;
					if (l * l > ret)
					{
						kh = (h - 1);
						ret -= (h - 1) * (h - 1);
						break;
					}
				}
				t++;
			}
		}
		return kh;
	}
	inline bool operator>(const Bignum &b) const
	{
		if (sizd > b.sizd)
		{
			return 1;
		}
		else if (sizd < b.sizd)
		{
			return 0;
		}
		else
		{
			for (int i = b.sizd; i >= 0; i--)
			{
				if (d[i] > b.d[i])
				{
					return 1;
				}
				if (d[i] < b.d[i])
				{
					return 0;
				}
			}
			return 0;
		}
	}
	inline bool operator>=(const Bignum &b) const
	{
		if (sizd > b.sizd)
		{
			return 1;
		}
		else if (sizd < b.sizd)
		{
			return 0;
		}
		else
		{
			for (int i = sizd; i >= 0; i--)
			{
				if (d[i] > b.d[i])
				{
					return 1;
				}
				if (d[i] < b.d[i])
				{
					return 0;
				}
			}
			return 1;
		}
	}
	inline bool operator<=(const Bignum &b) const
	{
		if (b >= *this)
		{
			return 1;
		}
		return 0;
	}
	inline bool operator<(const Bignum &b) const
	{
		if (b > *this)
		{
			return 1;
		}
		return 0;
	}
	inline bool operator==(const Bignum &b) const
	{
		if (sizd != b.sizd)
		{
			return 0;
		}
		else
		{
			for (int i = b.sizd; i >= 0; i--)
			{
				if (d[i] != b.d[i])
				{
					return 0;
				}
			}
			return 1;
		}
	}
	void show()
	{
		for (int i = sizd; i >= 0; i--)
		{
			cout << d[i];
		}
	}
};
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	Bignum a;
	ll b;
	cin >> b;
	a = b;
	a = a.sqr();
	a.show();
}
