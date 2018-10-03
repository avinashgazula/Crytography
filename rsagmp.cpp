#include<stdio.h>
#include<gmp.h>
#include<time.h>
#include<bits/stdc++.h>
using namespace std;
mpz_t n, phi, e, d;
bool coprime = false;
mpz_t atemp[100];


void gcd(mpz_t a, mpz_t b)
{

    mpz_t x0, y0, x_1, y_1, r_1, r0;
    mpz_init_set_ui(x0, 0);
    mpz_init_set_ui(y0, 1);
    mpz_init_set_ui(x_1, 1);
    mpz_init_set_ui(y_1, 0);
    mpz_init_set(r_1, a);
    mpz_init_set(r0, b);
    mpz_t x1, y1;
    mpz_init(x1);
    mpz_init(y1);

    while(1){
        mpz_t q1;
        mpz_init(q1);
        mpz_fdiv_q(q1, r_1, r0);
        mpz_mul(x1, q1, x0);
        mpz_mul_si(x1, x1, -1);
        mpz_add(x1, x1, x_1);

        mpz_mul(y1, q1, y0);
        mpz_mul_si(y1, y1, -1);
        mpz_add(y1, y1, y_1);

        //x1 = x_1 - (q1 * x0);
        //y1 = y_1 - (q1 * y0);

        mpz_t r1;
        mpz_init(r1);

        mpz_mul(r1, a, x1);
        mpz_addmul(r1, b, y1);
        
        //int r1 = a*x1 + b*y1;

        if(mpz_cmp_ui(r1, 0)==0) break;
        mpz_set(r_1, r0);
        mpz_set(x_1, x0);
        mpz_set(y_1, y0);
        mpz_set(r0, r1);
        mpz_set(x0, x1);
        mpz_set(y0, y1);
    }
    mpz_abs(r0, r0);
    //gmp_printf("GCD is %Zd = %Zd*%Zd + %Zd*%Zd\n", r0, a, x0, b, y0);
    if(mpz_cmp_ui(r0, 1) == 0) coprime = true;
    else coprime = false;
    
}

string encrypt(string plaintext){
    int len = plaintext.length();
    
    for(int i=0; i<len; i++)
    mpz_init(atemp[i]);
    string res = "";
    for(int i=0; i<len; i++){
        int temp = plaintext[i];
        cout<<"t"<<temp<<" ";
        mpz_t mtemp;
        mpz_init_set_ui(mtemp, temp);
        mpz_powm(mtemp, mtemp, e, n);
        gmp_printf("%Zd ", mtemp);
        mpz_set(atemp[i], mtemp);
        char ch = temp;
        res.push_back(ch);
    }
    return res;
}

string decrypt(string cipher){
    int len = cipher.length();
    string res = "";
    for(int i=0; i<len; i++){
        //int temp = cipher[i];
        mpz_t mtemp;
        mpz_init_set(mtemp, atemp[i]);
        //mpz_init_set_ui(mtemp, temp);
        mpz_powm(mtemp, mtemp, d, n);
        gmp_printf("%Zd ", mtemp);
        int temp = mpz_get_ui(mtemp);
        char ch = temp;
        res.push_back(ch);
    }
    return res;
}

int main(){
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    seed = time(NULL);
    gmp_randseed_ui(state, seed);
    mpz_t limit;
    mpz_init(limit);
    mpz_set_ui(limit, 100000);
    mpz_t a, b;
    mpz_init(a);
    mpz_init(b);
    while(true){
        mpz_urandomm(a, state, limit);
        mpz_add_ui(a, a, 10000);
        if(mpz_probab_prime_p(a, 25) != 0) break;

    }
    while(true){
        mpz_urandomm(b, state, limit);
        mpz_add_ui(b, b, 10000);
        if(mpz_probab_prime_p(b, 25) != 0) break;
    }
    
    
    //mpz_set_ui(a, 7);
    //mpz_set_ui(b, 13);
    gmp_printf("a = %Zd \nb =  %Zd\n", a, b);
    
    /*mpz_init(a);
    mpz_init(b);
    gmp_printf("Enter a and b\n");
    gmp_scanf("%Zd", a);
    gmp_scanf("%Zd", b);*/

    
    mpz_init(n);
    mpz_init(phi);
    mpz_init(e);
    mpz_init(d);
    mpz_mul(n, a, b);
    mpz_sub_ui(a, a, 1);
    mpz_sub_ui(b, b ,1);
    mpz_mul(phi, a, b);

    mpz_set_ui(e,2);
    
    while(mpz_cmp(e,n)<0){
        gcd(e, phi);
        if(coprime) break;
        mpz_nextprime(e,e);
    }

    mpz_invert(d, e, phi);
    gmp_printf("e %Zd d %Zd n %Zd phi %Zd\n", e, d, n, phi);
    //cout<<"e "<<e<<" d "<<d<<" n "<<n<<" phi "<<phi<<endl;
    string input;
    //cout<<"Enter input :";
    cin>>input;
    int len = input.length();
    cout<<"input len "<<len<<endl;
    string cipher = encrypt(input);
    printf("\n");
    cout<<"clen "<<cipher.length();
    for(int i=0; i<cipher.length(); i++){
        int x = cipher[i];
        cout<<x<<" ";
    }
    printf("\n");
    //cout<<"Encrypted data : "<<cipher<<endl;
    input = "";
    cout<<endl;
    input = decrypt(cipher);
    printf("\n");
    cout<<"Decrypted data : "<<input<<endl;

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(phi);
    mpz_clear(d);
}