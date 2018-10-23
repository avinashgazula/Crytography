#include<stdio.h>
#include<gmp.h>
#include<time.h>
#include<bits/stdc++.h>
using namespace std;

mpz_t P,G,x,y;

int main(int argc, char const *argv[])
{
    mpz_t Q;
    mpz_init(Q);
    mpz_init(P);
    mpz_init(G);
    mpz_init(x);
    mpz_init(y);
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    seed = time(NULL);
    gmp_randseed_ui(state, seed);
    mpz_t limit;
    mpz_init(limit);
    mpz_set_ui(limit, 100000);
    while(true){
        mpz_urandomm(Q, state, limit);
        if(mpz_probab_prime_p(Q, 25) != 0) break;
    }
    mpz_mul_ui(P,Q,2);
    mpz_add_ui(P,P,1);
    mpz_set(limit, P);
    mpz_t temp;
    mpz_init(temp);
    for(int i=2; i<=20;i++){
        mpz_set_ui(G,i);
        mpz_powm_ui(temp,G,2,P);
        if(mpz_cmp_ui(temp, 1)==0) continue;
        mpz_powm(temp,G,Q,P);
        if(mpz_cmp_ui(temp, 1)!=0) break;
    }
    mpz_clear(temp);
    mpz_urandomm(x, state, limit);
    mpz_powm(y,G,x,P);
    gmp_printf("P: %Zd\nG: %Zd\nx: %Zd\ny: %Zd\n\n",P,G,x,y);


    mpz_t message;
    mpz_init(message);
    mpz_urandomm(message, state, limit);
    gmp_printf("message :%Zd\n\n",message);

    //Encryption

    mpz_t k, c1, c2;
    mpz_init(k);
    mpz_init(c1);
    mpz_init(c2);
    mpz_urandomm(k,state,limit);
    mpz_powm(c1,G,k,P);
    mpz_powm(c2,y,k,P);
    mpz_mul(c2,c2,message);
    mpz_mod(c2,c2,P);
    gmp_printf("c1: %Zd\nc2: %Zd\n\n",c1,c2);

    //Decryption
    mpz_powm(c1,c1,x,P);
    mpz_invert(c1,c1,P);
    mpz_mul(c1,c1,c2);
    mpz_mod(message,c1,P);
    gmp_printf("Decrypted message :%Zd\n\n",message);

    mpz_clear(P);
    mpz_clear(G);
    mpz_clear(x);
    mpz_clear(y);
    return 0;
}
