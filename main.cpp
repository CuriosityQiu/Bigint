#include<iostream>
#define Length 1000
using namespace std;

class Bigint
{
public:
	Bigint(string s);
	Bigint();
	void op();
	Bigint operator+(Bigint b);
	Bigint operator-(Bigint b);
	Bigint operator*(Bigint b);
	Bigint operator/(Bigint b);
	Bigint sqr(Bigint a, Bigint b);//算a的b次方
private:
	char arr[Length];
	bool sym;
};
//默认构造函数
Bigint::Bigint()
{
	for (int i = 0; i < Length; i++)
		arr[i] = 0;
	sym = 1;
}

//构造函数
Bigint::Bigint(string s)
{
	for (int i = 0; i < Length; i++)
		arr[i] = 0;
	int n = s.length();
	for (int i = Length - n; i < Length; i++)
		arr[i] = s[i - Length + n]-'0';
	sym = 1;
}

//输出大数
void Bigint::op()
{
	bool flag = 0;
	if (sym == 0)
		cout << '-';
	for (int i = 0; i < Length-1; i++)
	{
		if (arr[i] != 0)
			flag = 1;
		if (flag==1)
			cout << (int)arr[i];
	}
	cout << (int)arr[Length-1]<<endl;
}

//加法运算
Bigint Bigint::operator+(Bigint b)
{
	Bigint a;
	char temp = 0;
	for (int i = Length-1; i >=0; i--)
	{
		a.arr[i] = (arr[i] + b.arr[i] + temp)%10;
		temp = (arr[i] + b.arr[i] + temp) / 10;
	}
	return a;
}

//减法运算
Bigint Bigint::operator-(Bigint b)
{
	Bigint a;
	Bigint r;
	for (int i = 0; i < Length; i++)
		r.arr[i] = arr[i];
	for (int i = Length - 1; i >= 0; i--)
	{
		if (r.arr[i] >= b.arr[i])
			a.arr[i] = r.arr[i] - b.arr[i];
		else
		{
			int j;
			for (j = i - 1; j >= 0; j--)
			{
				if (r.arr[j] > 0)
					break;
			}
			if (j < 0)
			{
				a=b - *this;
				a.sym = 0;
				return a;
			}
			r.arr[j]--;
			for (int k = j + 1; k < i; k++)
			{
				r.arr[k] = 9;
			}
			a.arr[i] = r.arr[i] + 10 - b.arr[i];
		}
	}
	return a;
}

//乘法运算
Bigint Bigint::operator*(Bigint b)
{
	Bigint r;
	for (int i = 0; i < Length; i++)
		r.arr[i] = 0;
	for (int i = Length - 1; i >= 0; i--)
	{
		char temp = 0;
		for (int j = Length - 1; j >= 0; j--)
		{
			if (i + j - Length + 1 >= 0)
			{
				r.arr[i + j - Length + 1] = r.arr[i + j - Length + 1] + b.arr[j] * arr[i] + temp;
				temp = r.arr[i + j - Length + 1] / 10;
				r.arr[i + j - Length + 1] %= 10;
			}
		}
	}
	return r;
}

//整除运算
Bigint Bigint::operator/(Bigint b)
{
	Bigint r,a=*this;
	if ((a - b).sym == 0)
		return r;
	for (int i = 0; (a - b).sym == 1; i++)
	{
		a = a - b;
		r.arr[Length - 1]++;
		if (r.arr[i] >= 10)
		{
			char temp = 0;
			for (int j = Length - 1; j >= 0; j--)
			{
				arr[j] = arr[j] + temp;
				temp = arr[j] / 10;
				arr[j] %= 10;
			}
		}
	}
	return r;
}

//幂运算
Bigint Bigint::sqr(Bigint a, Bigint b)
{
	Bigint r;
	r.arr[Length - 1] = 1;
	Bigint e = r;
	b = b - e;
	while (b.sym == 1)
	{
		r = r * a;
		b = b - e;
	}
	return r;
}


int main()
{
	//输入区
	string n;
	cout << "请输入前项：";
	cin >> n;
	string m;
	cout << "请输入后项：";
	cin >> m;
	//创建三个大数对象
	Bigint a(n);
	Bigint b(m);
	Bigint c;
	cout << "进行两数间的加法运算" << endl;
	c = a + b;
	c.op();

	cout << "进行两数间的减法运算" << endl;
	c = a - b;
	c.op();

	cout << "进行两数间乘法运算" << endl;
	c = a * b;
	c.op();	

	cout << "进行两数间的整除运算" << endl;
	c = a / b;
	c.op();

	cout << "进行两数间幂运算" << endl;
	c=c.sqr(a, b);
	c.op();
	return 0;
}
