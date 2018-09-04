#include<bits/stdc++.h>
#include<gmp.h>
using namespace std;

int main(){
    int n;
    bool correct = true;
    cout<<"Enter the number of values :";
    cin>>n;
    mpz_t r[n], m[n];
    for(int i=0; i<n; i++){
        mpz_t a, b;
        mpz_init(a);
        mpz_init(b);
        gmp_scanf("%Zd", a);
        gmp_scanf("%Zd", b);
        mpz_init_set(r[i], a);
        mpz_init_set(m[i], b);
    }

   /* for(int i=0; i<n; i++){
        gmp_printf("%Zd %Zd\n", r[i], m[i]);
    }*/
    for(int i=0; i<n-1; i++){
        mpz_t g;
        mpz_init(g);
        mpz_gcd(g, m[i], m[i+1]);
        if (mpz_cmp_ui(g, 1)!=0)
        correct = false;
    }


    if(correct){
        mpz_t M;
        mpz_init_set_ui(M, 1);
        for(int i=0; i<n; i++){
            mpz_mul(M, M, m[i]);
        }
        gmp_printf("M is %Zd\n", M);

        mpz_t x;
        mpz_init_set_ui(x, 0);
        for(int i=0; i<n; i++){
            mpz_t temp, temp2, temp3;
            mpz_init_set_ui(temp, 1);
            mpz_init_set_ui(temp2, 1);
            mpz_init_set_ui(temp3, 1);
            mpz_cdiv_q(temp, M, m[i]);
            mpz_cdiv_q(temp3, M, m[i]);
            mpz_mul(temp, temp, r[i]);
            mpz_invert(temp2, temp3, m[i]);
            mpz_mul(temp, temp, temp2);
            mpz_add(x, x, temp);
        }
        mpz_mod(x, x, M);
        gmp_printf("x is %Zd\n", x);
    }

    
}


/*
3
2 3
3 5
2 7
*/