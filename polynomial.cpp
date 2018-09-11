#include <bits/stdc++.h>
using namespace std;

vector<int> input_pol(int deg)
{
	vector<int> arr;
	int inp;
	for(int i=0;i<=deg;i++)
	{
		cin>>inp;
		arr.push_back(inp);
	}
	return arr;
}
vector<int> get_xor(vector<int> A,vector<int> B)
{
	vector<int> res(A.size());
	for(int i=0;i<A.size();i++)
	{
		if(A[i] == B[i])
			res[i]=0;
		else
			res[i]=1;
	}
	return res;
}
vector<int> product(vector<int> A,vector<int> m_x)
{
	int t = A[0];
	A.erase(A.begin());
	A.push_back(0);

	if(t == 1)
	{
		A = get_xor(A,m_x);
	}
	return A;
}
int main()
{
	int p,n;
	cout<<"Enter P : ";
	cin>>p;

	cout<<"Enter n : ";
	cin>>n;

	vector<int> m_x;
	cout<<"Enter a Irreducible polynomial of degree "<<n<<" : ";
	m_x = input_pol(n);
	m_x.erase(m_x.begin());

	vector<int> f_x;
	cout<<"Enter a polynomial f(x) ";
	f_x = input_pol(n-1);
	
	vector<int> g_x;
	cout<<"Enter a polynomial g(x) degree :  ";
	g_x = input_pol(n-1);

	vector<int> res;
	for(int i=0;i<n;i++)
		res.push_back(0);

	int ind,jnd;
	jnd = g_x.size()-1;

	for(int i=0;i<n;i++)
	{
		if(i == 0)
		{
			if(g_x[jnd] == 1)
				res = get_xor(res,f_x);
		}
		else
		{
			f_x = product(f_x,m_x);
			if(g_x[jnd] == 1)
				res = get_xor(res,f_x);
		}
		jnd--;
	}
	for(int i=0;i<res.size();i++)
		cout<<res[i];
	cout<<endl;
	return 0;
}