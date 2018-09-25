#include<bits/stdc++.h>
using namespace std;

string kl, kr;
int sbox[8][4][16];
int ip[64], fp[64], sp[32];

string binary(int num){
    string res;
    while(num){
        res.push_back(num%2 + '0');
        num/=2;
    }
    reverse(res.begin(), res.end());
    int diff = 4-res.length();
    string s = "";
    for(int i=0; i<diff; i++)
    s.push_back('0');
    s+=res;
    return s;
}

string XOR(string s1, string s2, int len){
    string res;
    for(int i=0; i<len; i++){
        if(s1[i]==s2[i]) res.push_back('0');
        else res.push_back('1');
    }
    //cout<<res<<endl;
    return res;
}

string compressKey(string key){
    //cout<<"    "<<key.substr(4,48);
    return key.substr(4,48);
}

string expandString(string right){
    string expand;
    expand.push_back(right[31]);
    int pos = 0;
    for(int i=0; i<8; i++){
        string temp = right.substr(pos, 4);
        //cout<<temp<<" ";
        pos +=4;
        pos%=32;
        expand +=temp;
        expand.push_back(right[pos]);
        expand.push_back(temp[3]);
    }
    expand[expand.length()-1] = '\0'; 
    return expand;
}

string compressSBox(string cipher){
    int pos = 0;
    string res = "";
    for(int i=0; i<8; i++){
        string temp = cipher.substr(pos, 6);
        pos+=6;

        int row = 2*(temp[0]-'0') + (temp[5]-'0');
        int column = 8*(temp[1]-'0') + 4*(temp[2]-'0') + 2*(temp[3]-'0') + (temp[4]-'0');
        int val = sbox[i][row][column];
        //cout<<val<<" ";
        res += binary(val);

    }
    return res;
}

string generateKey(int round){
    //cout<<kl<<" "<<kr<<endl;
    if(round == 1 || round == 2 || round == 9 || round == 16){
        kl.push_back(kl[0]);
        kl = kl.substr(1, 28);
        kr.push_back(kr[0]);
        kr = kr.substr(1, 28);
    }
    else{
        kl.push_back(kl[0]);
        kl.push_back(kl[1]);
        kl = kl.substr(2, 28);
        kr.push_back(kr[0]);
        kr.push_back(kr[1]);
        kr = kr.substr(2, 28);
    }
    //cout<<kl<<" "<<kr<<endl;
    string main = kl;
    main += kr;
    //cout<<main<<endl;
    return compressKey(main);
}

string encrypt(string plaintext, string key){
    string cipher(plaintext);

    //Initial Permutation
    for(int i=0; i<64; i++){
        cipher[i] = plaintext[ip[i]];
    }

    cout<<"cipher "<<cipher<<endl;

    //Rounds
    for(int round=1; round<=16; round++){
        string left = cipher.substr(0,32);
        string right = cipher.substr(32,32);
        string nextleft = right;
        //cout<<left<<" "<<right<<endl;
        string expand = expandString(right);
        int pos=0;
        string ki = generateKey(round);
        //cout<<"\n"<<ki<<" "<<ki.length()<<endl;
        cipher = XOR(expand, ki, 48);

        string res = compressSBox(cipher);
        //cout<<endl;
        cipher = res;
        for(int i=0; i<64; i++){
            cipher[i] = res[sp[i]];
        }
        //cout<<"res "<<res<<endl;
        //cout<<cipher<<" "<<cipher.length()<<endl;
        right = "";
        right = XOR(cipher, left, 32);
        cipher = nextleft;
        cipher+=right;
        //cout<<cipher<<" "<<cipher.length()<<endl;
    }

    //final permutation
    string temp = cipher;
    for(int i=0; i<64; i++){
        cipher[i] = temp[fp[i]];
    }
    return cipher;
}

int main(int argc, char const *argv[])
{
    string plaintext, key;
    
    //sbox generation
    for(int i=0; i<8; i++){
        for(int r=0; r<4; r++){
            for(int c=0; c<16; c++){
                sbox[i][r][c] = rand()%16;
            }
        }
    }
    cout<<endl;
    /*for(int i=0; i<8; i++){
        for(int r=0; r<4; r++){
            for(int c=0; c<16; c++){
                cout<<sbox[i][r][c]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<endl;
    }*/

    cout<<endl;

    //cin>>plaintext>>key;
    bool visit[64];
    srand(time(NULL));
    for(int i=0; i<64; i++)
    visit[i] = false;
    //Initial Permutation table generation
    for(int i=0; i<64; i++){
        int val = rand()%64;
        while(visit[val]){
            val = rand()%64;
        }
        visit[val] = true;
        ip[i] = val;
    }
    for(int i=0; i<64; i++)
    visit[i] = false;
    //Single Permutation table generation
    for(int i=0; i<32; i++){
        int val = rand()%32;
        while(visit[val]){
            val = rand()%32;
        }
        visit[val] = true;
        sp[i] = val;
    }

    //Plain Text generation
    for(int i=0; i<64; i++){
        int val = rand()%2;
        plaintext.push_back(val+'0');
    }
    //Key generation
    for(int i=0; i<64; i++){
        int val = rand()%2;
        key.push_back(val+'0');
    }
    kl = key.substr(0,28);
    kr = key.substr(28,28);

    //Final Permutation table generation
    for(int i=0; i<64; i++){
        fp[ip[i]] = i;
    }
    /*for(int i=0; i<64; i++){
        cout<<ip[i]<<", ";
    }
    cout<<endl;
    for(int i=0; i<64; i++){
        cout<<fp[i]<<", ";
    }*/
    cout<<endl;
    cout<<"plaintext "<<plaintext<<endl;
    cout<<"key "<<key<<endl;


    string cipher = encrypt(plaintext, key);
    cout<<"Encrypted Text is "<<cipher<<" "<<cipher.length()<<endl;
    return 0;
}
