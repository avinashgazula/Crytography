#include<stdio.h>
#include<gmp.h>
#include<time.h>
#include<bits/stdc++.h>
using namespace std;

mpz_t P,G,a,b;

int main(int argc, char const *argv[])
{
    mpz_t Q;
    mpz_init(Q);
    mpz_init(P);
    mpz_init(G);
    mpz_init(a);
    mpz_init(b);
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
    /*while(true){
        mpz_urandomm(G, state, limit);
        mpz_powm_ui(temp,G,2,P);
        if(mpz_cmp_ui(temp, 1)==0) continue;
        mpz_powm(temp,G,Q,P);
        if(mpz_cmp_ui(temp, 1)!=0) break;
        
    }*/
    mpz_clear(temp);
    mpz_urandomm(a, state, limit);
    mpz_urandomm(b, state, limit);
    gmp_printf("P: %Zd\nG: %Zd\na: %Zd\nb: %Zd\n\n",P,G,a,b);
    mpz_t A,B,s1,s2;
    mpz_init(A);
    mpz_init(B);
    mpz_init(s1);
    mpz_init(s2);
    mpz_powm(A,G,a,P);
    mpz_powm(B,G,b,P);
    gmp_printf("A: %Zd\nB: %Zd\n\n",A,B);
    mpz_powm(s1,B,a,P);
    mpz_powm(s2,A,b,P);
    gmp_printf("s1: %Zd\ns2: %Zd\n\n",s1,s2);
    mpz_clear(P);
    mpz_clear(G);
    mpz_clear(a);
    mpz_clear(b);
    return 0;
}
