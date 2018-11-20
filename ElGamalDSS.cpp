#include<stdio.h>
#include<gmp.h>
#include<time.h>
#include<bits/stdc++.h>
using namespace std;

mpz_t P,G,x,y;
bool coprime = false;


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

        mpz_t r1;
        mpz_init(r1);

        mpz_mul(r1, a, x1);
        mpz_addmul(r1, b, y1);
        if(mpz_cmp_ui(r1, 0)==0) break;
        mpz_set(r_1, r0);
        mpz_set(x_1, x0);
        mpz_set(y_1, y0);
        mpz_set(r0, r1);
        mpz_set(x0, x1);
        mpz_set(y0, y1);
    }
    mpz_abs(r0, r0);
    if(mpz_cmp_ui(r0, 1) == 0) coprime = true;
    else coprime = false;
    
}

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
    mpz_set(limit, P);
    mpz_add_ui(P,P,1);
    mpz_t temp;
    mpz_init(temp);
    for(int i=2; i<=20;i++){
        mpz_set_ui(G,i);
        mpz_powm_ui(temp,G,2,P);
        if(mpz_cmp_ui(temp, 1)==0) continue;
        mpz_powm(temp,G,Q,P);
        if(mpz_cmp_ui(temp, 1)!=0) break;
    }
    
    mpz_set(limit, Q);
    mpz_urandomm(x, state, limit);
    mpz_powm(y,G,x,Q);
    gmp_printf("P: %Zd\nG: %Zd\nx: %Zd\ny: %Zd\n\n",P,G,x,y);

    mpz_t k;
    mpz_init(k);
    while(true){
        mpz_urandomm(k,state,limit);
        gcd(limit, k);
        if(coprime) break;
    }
    mpz_t m, K;
    mpz_init(m);
    mpz_init(K);
    mpz_urandomm(m, state, limit);
    gmp_printf("m: %Zd\n",m);
    
    while(true){
        mpz_urandomm(K, state, limit);
        mpz_set(temp,Q);
        mpz_sub_ui(temp,Q,1);
        mpz_gcd(temp,K,temp);
        if(mpz_cmp_ui(temp, 1)==0) break;
    }
    gmp_printf("K: %Zd\n",K);

    mpz_t s1,s2,v1,v2;
    mpz_init(s1);
    mpz_init(s2);
    mpz_init(v1);
    mpz_init(v2);
    mpz_powm(s1,G,K,Q);
    mpz_set(temp,Q);
    mpz_sub_ui(temp,Q,1);
    mpz_t kinv, temp1;
    mpz_init(kinv);
    mpz_init(temp1);
    mpz_invert(kinv,K,temp);
    mpz_mul(temp1,x,s1);
    mpz_sub(temp1,m,temp1);
    mpz_mul(temp1,temp1,kinv);
    mpz_mod(s2,temp1,temp);

    mpz_powm(v1,G,m,Q);
    mpz_powm(v2,y,s1,Q);
    mpz_powm(temp1,s1,s2,Q);
    mpz_mul(v2,v2,temp1);
    mpz_mod(v2,v2,Q);

    gmp_printf("v1: %Zd\n",v1);
    gmp_printf("v2: %Zd\n",v2);



    mpz_clear(P);
    mpz_clear(G);
    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(temp);
    return 0;
}
