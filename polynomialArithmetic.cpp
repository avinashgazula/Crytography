#include<bits/stdc++.h>
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

void swap(vector<int> &A,vector<int> &B)
{
	vector<int> v;
	v = A;
	A = B;
	B = v;
}

vector<int> XOR(vector<int> A, vector<int> B){
    int n = A.size();
    vector<int> res;
    for(int i=0; i<n; i++){
        if(A[i]==B[i]) res.push_back(0);
        else res.push_back(1);
    }
    return res;
}

void print_poly(vector<int> a)
{
    int deg = a.size();
	if(a.size() == 0)
	{
		cout<<"0\n";
		return;
	}
	for(int i=0;i<a.size();i++)
	{
        if(i!=0&&a[i]!=0) cout<<" + "; 
        if(a[i]!=0) 
		cout<<a[i]<<"x^"<<deg-i-1;
        
	}
	cout<<endl;
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
	//clear_zeros(A);
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
    for(int i=0; i<num1.size(); i++){
        num1[i]%=2;
    }

	return num1;
}

void lshift(vector<int> &A){
    reverse(A.begin(), A.end());
    A.pop_back();
    reverse(A.begin(), A.end());
    A.push_back(0);
}

int main(){
    vector<int> num1;
	vector<int> num2;
    int deg1, deg2;
	vector<int> D;

	int inp; 

	cout<<"Enter Polynomial 1 : ";
	cin>>inp;
	while(inp!=-1 && inp/10 == 0)
	{
		num1.push_back(inp);
		cin>>inp;
	}
	cout<<"Polynomial1 = ";
	print_num(num1);
    

	cout<<"Enter Polynomial 2 : ";
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

    deg1 = num1.size();
    deg2 = num2.size();



	cout<<"Enter D : ";
	cin>>inp;
	while(inp!=-1 && inp/10 == 0)
	{
		D.push_back(inp);
		cin>>inp;
	}
	cout<<"D = ";
	print_num(D);

    vector<int> nextDeg;
    nextDeg.push_back(1);
    for(int i=0; i<deg1; i++){
        nextDeg.push_back(0);
    }
    cout<<"deg1 "<<deg1<<" deg2 "<<deg2<<endl;
    vector<int> modVal = modulo(nextDeg, D);
    cout<<"Modval = ";
    print_num(modVal);
    int gdeg = 0;
    for(int i=0; i<deg2; i++){
        if(num2[i]==1){
            gdeg = i; break;
        }
    }
    gdeg = deg2-gdeg-1;
    vector<vector<int> > res;
    res.push_back(num1);
    int cur = 0;

    while(cur!=gdeg){
        if(res[cur][0]==0){
            vector<int> temp = res[cur];
            lshift(temp);
            res.push_back(temp);
        }
        else{
            vector<int> temp = res[cur];
            lshift(temp);
            temp = XOR(modVal, temp);
            res.push_back(temp);
        }

        cur++;
    }
    cout<<"values\n";
    for(int i=0;i<res.size();i++){
        vector<int> temp = res[i];
        for(int j=0; j<temp.size(); j++)
        cout<<temp[j];
        cout<<endl;
    }


}
// 0 1 0 1 0 1 1 1 -1 1 0 0 0 0 0 1 1 -1 0 0 0 1 1 0 1 1 -1