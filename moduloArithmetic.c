#include<stdio.h>
#include<gmp.h>

void moduloAdd(mpz_t a, mpz_t b, mpz_t n, mpz_t result)
{
    mpz_add(result, a, b);
    mpz_mod(result, result, n);
}

void moduloSub(mpz_t a, mpz_t b, mpz_t n, mpz_t result)
{
    mpz_sub(result, a, b);
    gmp_printf("res is %Zd\n", result);
    mpz_mod(result, result, n);
}

void moduloMul(mpz_t a, mpz_t b, mpz_t n, mpz_t result)
{
    mpz_mul(result, a, b);
    mpz_mod(result, result, n);
}

int main(){
    mpz_t a, b, n, result;
    mpz_init(a);
    mpz_init(b);
    mpz_init(n);
    mpz_init(result);
    gmp_printf("Enter a, b and n\n");
    gmp_scanf("%Zd", a);
    gmp_scanf("%Zd", b);
    gmp_scanf("%Zd", n);
    moduloAdd(a, b, n, result);
    gmp_printf("Modulo Sum is %Zd\n", result);
    moduloSub(a, b, n, result);
    gmp_printf("Modulo Difference is %Zd\n", result);
    moduloMul(a, b, n, result);
    gmp_printf("Modulo Product is %Zd\n", result);
    
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(n);
    mpz_clear(result);
}