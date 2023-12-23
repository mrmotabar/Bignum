/*mohammadreza motabar*/
#include <bits/stdc++.h>
using namespace std;
class Bignum
{
public:
	static const int MAX_Length = 1e3;
	static const int Base = 10;
	long Digit[MAX_Length], Length = 0;

	// Initializing the value of the variable
	Bignum(long Value = 0)
	{
		memset(this->Digit, 0, sizeof this->Digit);
		Length = 0;
		this->Digit[Length] = Value;
		relax();
	}
	Bignum(const Bignum &Value)
	{
		memset(this->Digit, 0, sizeof this->Digit);
		Length = Value.Length;
		for (int i = 0; i <= Length; i++)
		{
			Digit[i] = Value.Digit[i];
		}
	}

	// Normalizing the input bignum to the assigned Base
	void relax()
	{
		for (int i = 0; i <= Length; i++)
		{
			Digit[i + 1] += Digit[i] / Base;
			Digit[i] %= Base;
			if (Digit[Length + 1] > 0)
			{
				Length++;
			}
		}
		while (Length && !Digit[Length])
		{
			Length--;
		}
	}
	// Overloading + 
	inline Bignum operator+(const Bignum &Addend) const
	{
		Bignum ret = 0;
		int Carry = 0;
		for (int i = 0; i <= max(Addend.Length, Length); i++)
		{
			ret.Digit[i] = Digit[i] + Addend.Digit[i] + Carry;
			Carry = ret.Digit[i] / Base;
			ret.Digit[i] = ret.Digit[i] % Base;
		}
		ret.Length = max(Length, Addend.Length);
		if (Carry > 0)
		{
			ret.Length++;
			ret.Digit[ret.Length] = Carry;
		}
		return ret;
	}
	// Overloading +=
	inline Bignum operator+=(const Bignum &Addend)
	{
		return *this = *this + Addend;
	}
	// Overloading + for semmation of a Bignum with an Integer
	inline Bignum operator+(const int &Addend) const
	{
		Bignum ret = *this;
		ret.Digit[0] += Addend;
		ret.relax();
		return ret;
	}
	// Overloading += for semmation of a Bignum with an Integer
	inline Bignum operator+=(const int &Addend)
	{
		return *this = *this + Addend;
	}
	// Overloading *
	inline Bignum operator*(const Bignum &Multiplicand) const
	{
		Bignum ret = 0;
		ret.Length = Length + Multiplicand.Length;
		for (int i = 0; i <= Length; i++)
		{
			for (int j = 0; j <= Multiplicand.Length; j++)
			{
				ret.Digit[i + j] += Digit[i] * Multiplicand.Digit[j];
			}
		}
		ret.relax();
		return ret;
	}
	// Overloading *=
	inline Bignum operator*=(const Bignum &Multiplicand)
	{
		return *this = *this * Multiplicand;
	}
	// Overloading * for multiplication of a Bignum with an Integer
	inline Bignum operator*(const int &Multiplicand) const
	{
		Bignum ret = 0, temp = Multiplicand;
		ret.Length = Length + temp.Length;
		for (int i = 0; i <= Length; i++)
		{
			for (int j = 0; j <= temp.Length; j++)
			{
				ret.Digit[i + j] += Digit[i] * temp.Digit[j];
			}
		}
		ret.relax();
		return ret;
	}
	// Overloading *= for multiplication of a Bignum with an Integer
	inline Bignum operator*=(const int &Multiplicand)
	{
		return *this = *this * Multiplicand;
	}
	// Overloading -
	inline Bignum operator-(const Bignum &Subtrahend)
	{
		Bignum ret = 0;
		for (int i = 0; i <= max(Subtrahend.Length, Length); i++)
		{
			if (Digit[i] >= Subtrahend.Digit[i])
			{
				ret.Digit[i] = Digit[i] - Subtrahend.Digit[i];
			}
			else
			{
				Digit[i] += Base;
				Digit[i + 1]--;
				ret.Digit[i] = Digit[i] - Subtrahend.Digit[i];
			}
		}
		ret.Length = max(Length, Subtrahend.Length);
		ret.relax();
		return ret;
	}
	// Overloading -=
	inline Bignum operator-=(const Bignum &Subtrahend)
	{
		return *this = *this - Subtrahend;
	}
	// Overloading ++
	inline Bignum &operator++()
	{
		(*this).Digit[0] += 1;
		(*this).relax();
		return *this;
	}
	// Overloading --
	inline Bignum operator--()
	{
		int i = 0;
		while (Digit[i] == 0)
		{
			i++;
			if (Digit[i] > 0)
			{
				Digit[i]--;
				for (int j = i - 1; j >= 1; j--)
				{
					Digit[j] = Base - 1;
				}
				Digit[0] = Base;
				Digit[0]--;
			}
		}
		return *this;
	}
	// Overloading ^
	inline Bignum operator^(const int Exponent)
	{
		int temp = Exponent;
		Bignum r = *this;
		Bignum ret = 1;
		while (temp > 0)
		{
			if (temp % 2 == 1)
			{
				ret *= r;
			}
			r *= r;
			temp /= 2;
		}
		return ret;
	}
	// Overloading /
	inline Bignum operator/(Bignum &Divisor)
	{
		Bignum ret = 0;
		string temp = " ";
		for (int i = Length; i >= 0; i--)
		{
			for (int j = ret.Length + 1; j >= 1; j--)
			{
				ret.Digit[j] = ret.Digit[j - 1];
			}
			ret.Digit[0] = Digit[i];
			if (i < Length)
			{
				ret.Length++;
			}
			ret.relax();
			for (int j = 1; j <= Base; j++)
			{
				Bignum h = j;
				if (ret < h * Divisor)
				{
					ret -= ((h - 1) * Divisor);
					ret.relax();
					temp += char(j - 1 + int('0'));
					break;
				}
			}
		}
		Bignum result = 0;
		for (int i = temp.size() - 1; i >= 1; i--)
		{
			result.Digit[temp.size() - 1 - i] = int(temp[i]) - int('0');
		}
		result.Length = temp.size();
		result.relax();
		return result;
	}
	// Overloading /=
	inline Bignum operator/=(Bignum &Divisor)
	{
		return *this = *this / Divisor;
	}
	// Overloading %
	inline Bignum operator%(Bignum &Modulo)
	{
		Bignum ret = 0;
		for (int i = Length; i >= 0; i--)
		{
			for (int j = ret.Length + 1; j >= 1; j--)
			{
				ret.Digit[j] = ret.Digit[j - 1];
			}
			ret.Digit[0] = Digit[i];
			if (i < Length)
			{
				ret.Length++;
			}
			ret.relax();
			for (int j = 1; j <= Base; j++)
			{
				Bignum h = j;
				if (ret < h * Modulo)
				{
					ret -= ((h - 1) * Modulo);
					ret.relax();
					break;
				}
			}
		}
		return ret;
	}
	// Defining square root function for Bignum
	inline Bignum sqr()
	{
		Bignum ret = 0;
		Bignum temp = 0;
		int t = 0;
		for (int i = Length; i >= 0; i--)
		{
			if ((Length + 1) % 2 == 1 && i == Length)
			{
				temp = Digit[Length];
			}
			else if ((Length + 1) % 2 == 0 && i == Length)
			{
				temp = Digit[Length] * Base + Digit[Length - 1];
				i--;
			}
			else
			{
				for (int j = temp.Length + 2; j >= 2; j--)
				{
					temp.Digit[j] = temp.Digit[j - 2];
				}
				temp.Digit[0] = Digit[i - 1];
				temp.Digit[1] = Digit[i];
				temp.Length += 2;
				i--;
			}
			if (t > 0)
			{
				for (int j = 1; j <= Base; j++)
				{

					if (((ret * 20) + j) * j > temp)
					{
						temp -= ((ret * 20) + (j - 1)) * (j - 1);
						temp.relax();
						for (int k = ret.Length + 1; k >= 1; k--)
						{
							ret.Digit[k] = ret.Digit[k - 1];
						}
						ret.Digit[0] = j - 1;
						ret.Length++;
						break;
					}
				}
			}
			else
			{
				for (int j = 1; j <= Base; j++)
				{
					Bignum jSquare = j * j;
					if (jSquare > temp)
					{
						ret = (j - 1);
						temp -= (j - 1) * (j - 1);
						break;
					}
				}
				t++;
			}
		}
		return ret;
	}
	// Overloading >
	inline bool operator>(const Bignum &Value) const
	{
		if (Length > Value.Length)
		{
			return 1;
		}
		else if (Length < Value.Length)
		{
			return 0;
		}
		else
		{
			for (int i = Value.Length; i >= 0; i--)
			{
				if (Digit[i] > Value.Digit[i])
				{
					return 1;
				}
				if (Digit[i] < Value.Digit[i])
				{
					return 0;
				}
			}
			return 0;
		}
	}
	// Overloading >=
	inline bool operator>=(const Bignum &Value) const
	{
		if (Length > Value.Length)
		{
			return 1;
		}
		else if (Length < Value.Length)
		{
			return 0;
		}
		else
		{
			for (int i = Length; i >= 0; i--)
			{
				if (Digit[i] > Value.Digit[i])
				{
					return 1;
				}
				if (Digit[i] < Value.Digit[i])
				{
					return 0;
				}
			}
			return 1;
		}
	}
	// Overloading <=
	inline bool operator<=(const Bignum &Value) const
	{
		if (Value >= *this)
		{
			return 1;
		}
		return 0;
	}
	// Overloading <
	inline bool operator<(const Bignum &Value) const
	{
		if (Value > *this)
		{
			return 1;
		}
		return 0;
	}
	// Overloading ==
	inline bool operator==(const Bignum &Value) const
	{
		if (Length != Value.Length)
		{
			return 0;
		}
		else
		{
			for (int i = Value.Length; i >= 0; i--)
			{
				if (Digit[i] != Value.Digit[i])
				{
					return 0;
				}
			}
			return 1;
		}
	}
	// Printing a Bignum
	void show()
	{
		for (int i = Length; i >= 0; i--)
		{
			cout << Digit[i];
		}
	}
};
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	Bignum a;
	long b;
	cin >> b;
	a = b;
	a = a.sqr();
	a.show();
}
