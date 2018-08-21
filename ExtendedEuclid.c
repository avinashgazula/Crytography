#include<stdio.h>
#include<gmp.h>
#include<time.h>

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
    gmp_printf("GCD is %Zd = %Zd*%Zd + %Zd*%Zd\n", r0, a, x0, b, y0);
    
}

int main(){

    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    seed = time(NULL);
    gmp_randseed_ui(state, seed);
    mpz_t limit;
    mpz_init(limit);
    mpz_set_ui(limit, 1000);
    mpz_t a, b;
    mpz_init(a);
    mpz_init(b);
    mpz_urandomm(a, state, limit);
    mpz_urandomm(b, state, limit);
    gmp_printf("a = %Zd \nb =  %Zd\n", a, b);
    
    /*mpz_init(a);
    mpz_init(b);
    gmp_printf("Enter a and b\n");
    gmp_scanf("%Zd", a);
    gmp_scanf("%Zd", b);*/
    gcd(a, b);
    mpz_clear(a);
    mpz_clear(b);
}