#include<bits/stdc++.h>
using namespace std;

void findMat(char keysquare[][5] , int *x, int *y, char val){
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(keysquare[i][j] == val){
                *x = i;
                *y = j;
                return;
            }
        }
    }
}

string encrypt(char keysquare[][5], string plaintext){
    string cipher;
    int cur = 0;
    int pos = 0;
    while(true){
        char a, b;
        if(cur == plaintext.length()) break;
        if(cur == plaintext.length()-1)
        plaintext.push_back('x');
        if(plaintext[cur]!=plaintext[cur+1]){
            a = plaintext[cur];
            b = plaintext[cur+1];
            if(a=='j') a--;
            if(b=='j') b--;
            cur+=2;
        }
        else{
            a = plaintext[cur];
            b = 'x';
            if(a=='j') a--;
            cur++;
            //cur+=2;
        }
        int x1, y1, x2, y2;
        findMat(keysquare, &x1, &y1, a);
        findMat(keysquare, &x2, &y2, b);
        if(x1 == x2){
            if(y1==4) y1=0;
            else y1++;
            if(y2==4) y2=0;
            else y2++;
            cipher.push_back(keysquare[x1][y1]);
            cipher.push_back(keysquare[x2][y2]);
        }
        else if(y1 == y2){
            if(x1==4) x1=0;
            else x1++;
            if(x2==4) x2=0;
            else x2++;
            cipher.push_back(keysquare[x1][y1]);
            cipher.push_back(keysquare[x2][y2]);
        }
        else{
            cipher.push_back(keysquare[x1][y2]);
            cipher.push_back(keysquare[x2][y1]);
        }
    }
    return cipher;
}

string decrypt(char keysquare[][5], string plaintext){
    string cipher;
    int cur = 0;
    int pos = 0;
    while(true){
        char a, b;
        if(cur == plaintext.length()) break;
        if(cur == plaintext.length()-1)
        plaintext.push_back('x');
        if(plaintext[cur]!=plaintext[cur+1]){
            a = plaintext[cur];
            b = plaintext[cur+1];
            if(a=='j') a--;
            if(b=='j') b--;
            cur+=2;
        }
        else{
            a = plaintext[cur];
            b = 'x';
            if(a=='j') a--;
            cur++;
            //cur+=2;
        }
        int x1, y1, x2, y2;
        findMat(keysquare, &x1, &y1, a);
        findMat(keysquare, &x2, &y2, b);
        if(x1 == x2){
            if(y1==0) y1=4;
            else y1--;
            if(y2==0) y2=4;
            else y2--;
            cipher.push_back(keysquare[x1][y1]);
            cipher.push_back(keysquare[x2][y2]);
        }
        else if(y1 == y2){
            if(x1==0) x1=4;
            else x1--;
            if(x2==0) x2=4;
            else x2--;
            cipher.push_back(keysquare[x1][y1]);
            cipher.push_back(keysquare[x2][y2]);
        }
        else{
            cipher.push_back(keysquare[x1][y2]);
            cipher.push_back(keysquare[x2][y1]);
        }
    }
    return cipher;
}

int main(){
    string key, plaintext;
    cout<<"Enter Key :";
    cin>>key;
    cout<<"Enter Plain text :";
    cin>>plaintext;
    int pos = 0;
    bool b =false;
    char keysquare[5][5];
    int visit[26];
    for(int i=0; i<26; i++){
        visit[i]=-1;
    }
    int i, j;
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            keysquare[i][j] = key[pos++];
            visit[key[pos-1]-'a'] = 1;
            if(pos == key.length()){
                b = true;
                break;
            }
        }
        if(b){
            break;
        }
    }
    if(j==4){
        i++;j=0;
    }
    else
    j++;
    int cur = 0;
    while(i<5){
        while(j<5){
            while(true){
                if(visit[cur]==1)
                cur++;
                else break;
                if(cur == 'j'-'a') cur++;
            }
            keysquare[i][j] = cur+'a';
            visit[cur] =1;
            j++;
        }
        i++;
        j=0;
    }
    cout<<"Key Square :\n";
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cout<<keysquare[i][j]<<" ";
        }
        cout<<endl;
    }
    string cipher = encrypt(keysquare, plaintext);
    cout<<"Encrypted text is :";
    cout<<cipher<<endl;
    cipher = decrypt(keysquare, cipher);
    plaintext = "";
    for(int i=0; i<cipher.length(); i++){
        if(cipher[i]!='x') plaintext.push_back(cipher[i]);
        else{
            if(i!=0 && i!=plaintext.length()-1 && cipher[i-1]!=cipher[i+1])
            plaintext.push_back('x');
        }
    }
    cout<<"Decrypted text is :";
    cout<<plaintext<<endl;
}
