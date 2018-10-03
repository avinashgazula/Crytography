#include<bits/stdc++.h>
using namespace std;

int n, e, d;

int gcd(int a, int h)
{
    int temp;
    while (1)
    {
        temp = a%h;
        if (temp == 0)
          return h;
        a = h;
        h = temp;
    }
}

int gcdExtended(int a, int b, int *x, int *y) 
{ 
    if (a == 0) 
    { 
        *x = 0, *y = 1; 
        return b; 
    } 
  
    int x1, y1; 
    int gcd = gcdExtended(b%a, a, &x1, &y1); 

    *x = y1 - (b/a) * x1; 
    *y = x1; 
  
    return gcd; 
} 

int modInverse(int a, int m) 
{ 
    int x, y; 
    int g = gcdExtended(a, m, &x, &y); 
    if (g != 1) 
        return -1;
    else
    { 
        // m is added to handle negative x 
        int res = (x%m + m) % m; 
        return res; 
    } 
} 
  


string encrypt(string plaintext){
  
    int len = plaintext.length();
    
    string res = "";
    for(int i=0; i<len; i++){
        int temp = plaintext[i];
        int val = temp;
        for(int i=1; i<e; i++){
            temp *= val;
            temp %= n;
        }
        cout<<temp<<" ";
        char ch = temp;
        res.push_back(ch);
    }
    return res;
}

string decrypt(string cipher){
    int len = cipher.length();
    string res = "";
    for(int i=0; i<len; i++){
        int temp = cipher[i];
        int val = temp;
        for(int i=1; i<d; i++){
            temp *= val;
            temp %= n;
        }
        cout<<temp<<" ";
        char ch = temp;
        
        res.push_back(ch);
    }
    return res;
}

int main(){
    int p = 7, q = 13;
    n = p*q;
    int phi = (p-1)*(q-1);
    e = 2;
    //cout<<"n "<<n<<endl;
    //cout<<"test "<<gcd(e, n)<<endl;
    for(e=2; e<phi; e++){
        if(gcd(e,phi) == 1) break;
    }

    d = modInverse(e, phi);
    cout<<"e "<<e<<" d "<<d<<" n "<<n<<" phi "<<phi<<endl;
    string input;
    cout<<"Enter input :";
    cin>>input;
    string cipher = encrypt(input);
    cout<<"Encrypted data : "<<cipher<<endl;
    input = "";
    cout<<endl;
    input = decrypt(cipher);
    cout<<"Decrypted data : "<<input<<endl;
}