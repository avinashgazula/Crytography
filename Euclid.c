#include<stdio.h>
#include<gmp.h>
#include<time.h>
void gcd(mpz_t a, mpz_t b)
{
    if (mpz_cmp_ui(a, 0)==0){
        gmp_printf("GCD is %Zd \n", b);
        return;
    }
     mpz_mod(b, b, a);
     gcd(b, a);
}

int main(){

    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    seed = time(NULL);
    gmp_randseed_ui(state, seed);
    int bitcount = 10;
    mpz_t a, b;
    mpz_init(a);
    mpz_init(b);
    mpz_urandomb(a, state, bitcount);
    mpz_urandomb(b, state, bitcount);
    gmp_printf("a = %Zd \nb =  %Zd\n", a, b);

    /*mpz_t a, b;
    mpz_init(a);
    mpz_init(b);
    gmp_printf("Enter a and b\n");
    gmp_scanf("%Zd", a);
    gmp_scanf("%Zd", b);
    if(mpz_cmp(a, b)>0)
    mpz_swap(a,b);*/
    gcd(a, b);
    mpz_clear(a);
    mpz_clear(b);
}