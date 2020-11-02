#include<iostream>
//#include "/home/dm/all/pbc-0.5.14/include/pbc.h"
#include<ctime>
#include<gmp.h>
#include<string>
#include<cmath>
using namespace std;

int main(){
    unsigned long int i=0;
    i++;
    int i_size=trunc(log10(i)) + 1;
	int check = 0;		                                    //will be 2 if prime, else 1 or 0
	mpz_t prime_p, prime_q, t;			                    //two very large prime numbers
	int bits = 128;
	mpz_init(prime_p);
	mpz_init(prime_q);
	mpz_init(t);
	gmp_randstate_t state;
	gmp_randinit_default(state);

	/*while(check!=2 && check!=1){
		mpz_init_set_ui(t, time(0));
		gmp_randseed(state, t);
		mpz_rrandomb(prime_p, state, bits);
		check = mpz_probab_prime_p(prime_p, 50);
	}
	check = 0;
	while(check!=2 && check!=1){
		mpz_init_set_ui(t, time(0));
		gmp_randseed(state, t);
		mpz_rrandomb(prime_q, state, bits);
		check = mpz_probab_prime_p(prime_q, 50);
		if(mpz_cmp(prime_p, prime_q)==0){
			check = 0;
		}
	}*/

    mpz_init_set_str (prime_p, "340282365653906833253643981767154204671", 10);
    mpz_init_set_str (prime_q, "340282366920933627760096148915069386783", 10);

	mpz_t P, Q,tot_n, pk, en_gcd;			                    //totient on n=prime_p*prime_q; which is LCM(prime_p-1, prime_q-1)
	mpz_init(P);
	mpz_init(Q);
	mpz_init(pk);
	mpz_init(tot_n);
	mpz_init(en_gcd);

	mpz_sub_ui(P, prime_p, 1);
	mpz_sub_ui(Q, prime_q, 1);
	mpz_lcm(tot_n, P, Q);
	mpz_init_set_ui(t, time(0));
	gmp_randseed(state, t);
	mpz_urandomm(pk, state, tot_n);
	mpz_gcd(en_gcd, pk, tot_n);
	while(mpz_cmp_ui(en_gcd, 1)!=0){
		mpz_init_set_ui(t, time(0));
		gmp_randseed(state, t);
		mpz_urandomm(pk, state, tot_n);
		mpz_gcd(en_gcd, pk, tot_n);
	}
	cout << "public_key:\n" << pk << "\n";
    mpz_t gcdex,y,sk;
    mpz_inits(gcdex,sk,y,NULL);
    mpz_init_set_ui(gcdex,1);
	mpz_gcdext(gcdex,sk,y,pk,tot_n);
	cout<<"secret_key:\n"<<sk<<endl;
	mpz_t N;
	mpz_inits(N,NULL);
	mpz_mul ( N, prime_p, prime_q);
	cout<<"N = "<<N<<endl;
    mpz_t a;
	mpz_t aN_gcd;
	mpz_init(a);
	mpz_init(aN_gcd);
    while(mpz_cmp_ui(aN_gcd, 1)!=0){
		mpz_init_set_ui(t, time(0));
		gmp_randseed(state, t);
		mpz_urandomm(a, state, tot_n);
		mpz_gcd(aN_gcd, a, tot_n);
	}
	cout<<endl<<"a= "<<a<<endl;
	mpz_sub_ui(a, a, 1);
	mpz_t g;
	mpz_init(g);
	mpz_mul ( g, a, a);
	cout<<endl<<"g = "<<g<<endl;
	mpz_t Wi;
	mpz_init(Wi);
	mpz_t v;
	mpz_init_set(v,sk);
	string i_str;
	i_str=to_string(i);
	mpz_t ten;
	mpz_init_set_ui(ten,10);
	while(i_size){
        mpz_mul(v,v,ten);
        i_size--;
	}
	mpz_t mpzi;
	mpz_init_set_ui(mpzi,i);
	mpz_add(Wi,v,mpzi);
//	mpz_add(Wi,v,i_str);
	cout<<"Wi ="<<endl<<Wi;




		/*long long  plain_text;  //plain text

		cout<<"Enter the number to encrypt:\n"<<endl;
		cin>>plain_text;
		cout<<"before encryption :"<<plain_text<<endl;
        mpz_t ctext,base,exp, mod,ptext;
        mpz_inits(ctext ,base,exp,mod,ptext,NULL);
		mpz_init_set (exp, pk);
		mpz_init_set (mod,n);


        mpz_set_si (base, plain_text);
        mpz_powm(ctext,  base, exp, mod);
        cout<<"cyter text: "<< ctext<<endl;

        mpz_init_set (exp,sk);
        mpz_powm(ptext,  ctext, exp, mod);
        cout<<"plane text: "<<ptext<<endl;

        */








	gmp_randclear(state);
	return 0;
}
