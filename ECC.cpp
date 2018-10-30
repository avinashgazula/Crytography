#include<stdio.h>
#include<gmp.h>
#include<time.h>
#include<bits/stdc++.h>
using namespace std;

mpz_t a,b,p;

int hexadecimalToDecimal(mpz_t res, string hexVal) 
{    
    int len = (hexVal.length()); 
    mpz_t base; 
    mpz_init_set_ui(base, 1);
      
    mpz_t dec_val; 
    mpz_init_set_ui(dec_val, 0);
      
    for (int i=len-1; i>=0; i--) 
    {    
        mpz_t temp;
        mpz_init(temp);
        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            mpz_mul_ui(temp, base, (hexVal[i] - 48));
            mpz_add(dec_val, dec_val, temp);
            
            mpz_mul_ui(base, base, 16);
        } 
        else if (hexVal[i]>='A' && hexVal[i]<='F') 
        { 
            mpz_mul_ui(temp, base, (hexVal[i] - 55));
            mpz_add(dec_val, dec_val, temp);
          
            mpz_mul_ui(base, base, 16); 
        } 
        mpz_clear(temp);
    } 
    mpz_set(res, dec_val);
}

void addPoints(mpz_t xR, mpz_t yR, mpz_t xP, mpz_t yP, mpz_t xQ, mpz_t yQ){
    mpz_t m;
    mpz_init(m);
    mpz_t num, den;
    mpz_init(num);
    mpz_init(den);

    if(mpz_cmp(xP, xQ)==0 && mpz_cmp(yP, yQ)==0){
        mpz_mul(num, xP, xP);
        mpz_mul_ui(num, num, 3);
        mpz_add(num, num, a);
        mpz_mul_ui(den, yP, 2);
    }
    else{
        mpz_sub(num,yQ,yP);
        mpz_sub(den,xQ,xP);
    }
    mpz_invert(den, den, p);
    mpz_mul(m, num, den);
    mpz_mod(m, m, p);

    mpz_mul(xR,m,m);
    mpz_sub(xR,xR,xP);
    mpz_sub(xR,xR,xQ);
    mpz_mod(xR,xR,p);

    mpz_sub(yR,xP,xR);
    mpz_mul(yR,yR,m);
    mpz_sub(yR,yR,yP);
    mpz_mod(yR,yR,p);

}


int main(int argc, char const *argv[])
{
    
    mpz_init_set_ui(a,0);
    mpz_init_set_ui(b,7);
    string ps = "FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE FFFFFC2F";
    mpz_init(p);
    hexadecimalToDecimal(p, ps);
    //gmp_printf("p: %Zd\n",p);

    mpz_t x, y, n;
    mpz_init(x);
    mpz_init(y);
    mpz_init(n);
    string xs = "79BE667E F9DCBBAC 55A06295 CE870B07 029BFCDB 2DCE28D9 59F2815B 16F81798";
    string ys = "483ADA77 26A3C465 5DA4FBFC 0E1108A8 FD17B448 A6855419 9C47D08F FB10D4B8";
    string ns = "FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE BAAEDCE6 AF48A03B BFD25E8C D0364141";
    hexadecimalToDecimal(x, xs);
    hexadecimalToDecimal(y, ys);
    hexadecimalToDecimal(n, ns);

    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    seed = time(NULL);
    gmp_randseed_ui(state, seed);
    mpz_t limit;
    mpz_init(limit);
    mpz_set(limit, n);

    mpz_t n1, n2;
    mpz_init(n1);
    mpz_init(n2);

    mpz_t r1,r2;
    mpz_init(r1);
    mpz_init(r2);

    //user 1 key generation
    //mpz_urandomm(n1, state, limit);
    mpz_set_ui(n1,5);
    mpz_t P1x, P1y, temp1;
    mpz_init_set(P1x,x);
    mpz_init_set(P1y,y);
    mpz_init_set(temp1, n1);
    while(mpz_cmp_ui(temp1,0)!=0){
        addPoints(r1,r2,P1x,P1y,x,y);
        mpz_set(P1x,r1);
        mpz_set(P1y,r2);
        mpz_sub_ui(temp1,temp1,1);
    }
    gmp_printf("P1x: %Zd\tP1y: %Zd\n",P1x, P1y);

    //user 2 key generation
    //mpz_urandomm(n2, state, limit);
    mpz_set_ui(n2,7);
    mpz_t P2x, P2y, temp2;
    mpz_init_set(P2x,x);
    mpz_init_set(P2y,y);
    mpz_init_set(temp2, n2);
    while(mpz_cmp_ui(temp2,0)!=0){
        addPoints(r1,r2,P2x,P2y,x,y);
        mpz_set(P2x,r1);
        mpz_set(P2y,r2);

        mpz_sub_ui(temp2,temp2,1);
    }
    gmp_printf("P2x: %Zd\tP2y: %Zd\n",P2x, P2y);

    //Secret Key of User 1
    mpz_t K1x, K1y;
    mpz_init_set(K1x,P2x);
    mpz_init_set(K1y,P2y);
    mpz_set(temp1, n1);
    while(mpz_cmp_ui(temp1,0)!=0){
        addPoints(r1,r2,K1x,K1y,P2x,P2y);
        mpz_set(K1x,r1);
        mpz_set(K1y,r2);
        mpz_sub_ui(temp1,temp1,1);
    }
    gmp_printf("K1x: %Zd\tK1y: %Zd\n",K1x, K1y);

    //Secret Key of User 2
    mpz_t K2x, K2y;
    mpz_init_set(K2x,P1x);
    mpz_init_set(K2y,P1y);
    mpz_set(temp2, n2);
    while(mpz_cmp_ui(temp2,0)!=0){
        addPoints(r1,r2,K2x,K2y,P1x,P1y);
        mpz_set(K2x,r1);
        mpz_set(K2y,r2);
        mpz_sub_ui(temp2,temp2,1);
    }
    gmp_printf("K2x: %Zd\tK2y: %Zd\n",K2x, K2y);

}
