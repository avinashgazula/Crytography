#include <bits/stdc++.h>
using namespace std;

void clear_zeros(vector<int> &v)
{
	while(v.size()>0 && v[0] == 0)
	{
		v.erase(v.begin());
	}
}

bool is_greater(vector<int> &A, vector<int> &B)
{
	int len1,len2;
	len1 = A.size();
	len2 = B.size();

	if(len1 > len2) return true;
	if(len1 < len2) return false;

	for(int i=0;i<len1;i++)
	{
		if(A[i] > B[i]) return true;
		if(A[i] < B[i]) return false;
	}
	return true;
}
vector<int> Add(vector<int> A, vector<int> B)
{
	if(is_greater(B,A))
	{
		swap(A,B);
	}
	int len1,len2;
	len1 = A.size();
	len2 = B.size();

	int ind = len1-1;
	int jnd = len2-1;

	int carry = 0;
	while(ind >=0 && jnd>=0)
	{
		int k = A[ind]+B[jnd]+carry;

		if(k >= 10)
		{
			A[ind] = k%10;
			carry = k/10;
		}
		else
		{
			A[ind] = k;
			carry = 0;
		}
		ind--;
		jnd--;

	}
	while(ind>=0 && carry > 0)
	{
		int k = A[ind]+carry;

		if(k >= 10)
		{
			A[ind] = k%10;
			carry = k/10;
		}
		else
		{
			A[ind] = k;
			carry = 0;
		}
		ind--;
	}
	if(carry > 0)
	{
		reverse(A.begin(),A.end());
		A.push_back(carry);
		reverse(A.begin(),A.end());
	}
	return A;
}
vector<int> subtract(vector<int> A, vector<int> B)
{
	int len1,len2;
	len1 = A.size();
	len2 = B.size();

	int ind = len1-1;
	int jnd = len2-1;

	int borrow = 0;
	while(ind >=0 && jnd>=0)
	{
		if(A[ind] >= B[jnd])
		{
			A[ind] -= B[jnd];
			ind--;
			jnd--;
		}
		else
		{
			int k = ind-1;
			while(A[k] == 0)
			{
				k--;
			}
			A[k]--;
			k++;
			while(k!=ind)
			{
				A[k] = 9;
				k++;
			}
			A[ind] = A[ind]+10-B[jnd];
			ind--;
			jnd--;
		}
	}
	clear_zeros(A);
	return A;
}

vector<int> modulo(vector<int> num1, vector<int> num2)
{
	clear_zeros(num1);
	clear_zeros(num2);

	while(is_greater(num1,num2))
	{
		num1 = subtract(num1,num2);
		clear_zeros(num1);	
	}

	return num1;
}

void print_num(vector<int> a)
{
	if(a.size() == 0)
	{
		cout<<"0\n";
		return;
	}
	for(int i=0;i<a.size();i++)
	{
		cout<<a[i];
	}
	cout<<endl;
}
void swap(vector<int> &A,vector<int> &B)
{
	vector<int> v;
	v = A;
	A = B;
	B = v;
}
vector<int> multiply_digit(vector<int> v,int d)
{
	vector<int> res;
	int carry = 0;

	int ind = v.size()-1;

	while(ind >= 0)
	{
		int k = v[ind]*d+carry;
		if(k >= 10)
		{
			res.push_back(k%10);
			carry = k/10;
		}
		else
		{
			res.push_back(k);
			carry = 0;
		}
		ind--;
	}
	if(carry > 0)
	{
		res.push_back(carry);
	}
	reverse(res.begin(),res.end());
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i];
	}
	cout<<endl;
	return res;

}
vector<int> multiply(vector<int> num1,vector<int> num2)
{
	if(is_greater(num2,num1))
	{
		swap(num1,num2);
	}
	vector<int> res;
	res.push_back(0);

	int count = 0;

	for(int i=num2.size()-1;i>=0;i--)
	{
		vector<int> x;
		x = multiply_digit(num1,num2[i]);

		int k = count;
		while(k)
		{
			x.push_back(0);
			k--;
		}
		res = Add(res,x);
		count++;
	}
	return res;
}

int main()
{
	vector<int> num1;
	vector<int> num2;
	vector<int> D;

	int inp;

	cout<<"Enter Num1 : ";
	cin>>inp;
	while(inp!=-1 && inp/10 == 0)
	{
		num1.push_back(inp);
		cin>>inp;
	}
	cout<<"Num1 = ";
	print_num(num1);

	cout<<"Enter Num2 : ";
	cin>>inp;
	while(inp!=-1 && inp/10 == 0)
	{
		num2.push_back(inp);
		cin>>inp;
	}
	cout<<"Num2 = ";
	print_num(num2);

	if(is_greater(num2,num1))
	{
		swap(num2,num1);
	}

	cout<<"Enter D : ";
	cin>>inp;
	while(inp!=-1 && inp/10 == 0)
	{
		D.push_back(inp);
		cin>>inp;
	}
	cout<<"D = ";
	print_num(D);

	vector<int> res;
	res = Add(num1,num2);
	cout<<"(num1+num2) is :  ";
	print_num(res);
	cout<<"(num1+num2) mod D is :  ";
	print_num(modulo(res,D));

	res = subtract(num1,num2);
	cout<<"(num1-num2) is :  ";
	print_num(res);
	cout<<"(num1-num2) mod D is :  ";
	print_num(modulo(res,D));

	res = multiply(num1,num2);
	cout<<"(num1*num2) is :  ";
	print_num(res);
	cout<<"(num1*num2) mod D is :  ";
	print_num(modulo(res,D));

	return 0;
}