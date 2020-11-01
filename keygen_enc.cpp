#include<iostream>
#include "/home/dm/all/pbc-0.5.14/include/pbc.h"
#include<ctime>
#include<gmp.h>

using namespace std;


int main(){

	int check = 0;		//will be 2 if prime, else 1 or 0
	mpz_t p, q, t;			//two very large prime numbers
	int bits = 128;
	//mp_bitcnt_t bits;
	mpz_init(p);
	mpz_init(q);
	mpz_init(t);


	gmp_randstate_t state;
	gmp_randinit_default(state);
	
	while(check!=2 && check!=1){
		mpz_init_set_ui(t, time(0));
		gmp_randseed(state, t);
		mpz_rrandomb(p, state, bits);
		check = mpz_probab_prime_p(p, 50);	
	}
	
	check = 0;

	while(check!=2 && check!=1){
		mpz_init_set_ui(t, time(0));
		gmp_randseed(state, t);
		mpz_rrandomb(q, state, bits);
		check = mpz_probab_prime_p(q, 50);
		if(mpz_cmp(p, q)==0){
			check = 0;
		}	
	}
	//   mpz_init_set_str (p, "340282365653906833253643981767154204671", 10);
	//   mpz_init_set_str (q, "340282366920933627760096148915069386783", 10);
	//   mpz_init_set_str (p, "61", 10);
	//   mpz_init_set_str (q, "53", 10);
	mpz_t P, Q,tot_n, e, en_gcd;			//totient on n=pq; which is LCM(p-1, q-1)
	mpz_init(P);
	mpz_init(Q);
	mpz_init(e);
	mpz_init(tot_n);
	mpz_init(en_gcd);
	mpz_sub_ui(P, p, 1);
	mpz_sub_ui(Q, q, 1);
	mpz_lcm(tot_n, P, Q);		//tot_n is supposed to be a secret 
	//cout<<"totoan"<<tot_n<<endl;
	mpz_init_set_ui(t, time(0));
	gmp_randseed(state, t);
	mpz_urandomm(e, state, tot_n); //({0,tot_n-1})
	mpz_gcd(en_gcd, e, tot_n);

	while(mpz_cmp_ui(en_gcd, 1)!=0){
		mpz_init_set_ui(t, time(0));
		gmp_randseed(state, t);
		mpz_urandomm(e, state, tot_n);
		mpz_gcd(en_gcd, e, tot_n);
	}

	//cout << secret_key << "\n";
	cout << "public_key:\n" << e << "\n";
	//---------------------
	//d as d ≡ e−1 (mod λ(n)); modular multipacative invere ecluden
	//mpz_gcdext(g,x,y,a,b);
	// ax + my = 1 
		mpz_t gcdex,y,x;
		mpz_inits(gcdex,x,y,NULL);
	mpz_gcdext(gcdex,x,y,e,tot_n);
	cout<<"secret_key:\n"<<x<<endl;

	//to test keys run the code below 
	/*
	mpz_t n;
	mpz_inits(n,NULL);
	mpz_mul ( n, p, q);
	cout<<"N "<<n<<endl;




	long long  plain_text;  //plain text 

	cout<<"Enter the number to encrypt:\n"<<endl;
	cin>>plain_text;
	cout<<"before encryption :"<<plain_text<<endl;
    mpz_t ctext,base,exp, mod,ptext;
    mpz_inits(ctext ,base,exp,mod,ptext,NULL);
	mpz_init_set (exp, e);
	mpz_init_set (mod,n);

      
	mpz_set_si (base, plain_text);
	mpz_powm(ctext,  base, exp, mod);
	cout<<"cyter text: "<< ctext<<endl;
        
    mpz_init_set (exp,x);
    mpz_powm(ptext,  ctext, exp, mod);
    cout<<"plane text: "<<ptext<<endl;

	*/








	gmp_randclear(state);
	return 0;
}