#include "prlib.h"

HMM::HMM(int m, int n , int t, int* o, int _max_iters)
{
	M=m, N=n , T=t;
	memcpy(O,o,T);
	max_iters = _max_iters;
	iters = 0;
	old_log_prob = DBL_MIN;
	A = new double[N*N];
	B = new double[N*M];
	pi = new double[N];
	//initialize
	for ( int i = 0 ; i<N ; i++ )
	{
		pi[i] = 1/(double)N;
		for ( int j=i ; j<N ; j++ )
		{
			*(A+i*N+j) = *(A+j*N+i) = 1/(double)N;
		}
	}
	for ( int i = 0 ; i<N ; i++ )
		for ( int j=0 ; j<M ; j++ )
		{
			*(B+i*M+j) = 1/(double)M;
		}
}

HMM::~HMM()
{
	delete A;
	delete B;
	delete pi;
}

void HMM::forward_algorithm( double* a, double *c )
{
	//compute a[0][i];
	c[0]=0;
	for ( int i=0 ; i<N ; i++ )
	{
		*(a+i) = pi[i]*(*(B+i*M));
		c[0]+=*(a+i);
	}

	//scale the a[0][i]
	c[0] = 1/c[0];
	for ( int i = 0 ; i<N ; i++ )
	{
		*(a+i) = c[0]*(*(a+i));
	}

	//compute a[t][i]
	for ( int t=1 ; t<T ; t++ )
	{
		c[t] = 0;
		for ( int i = 0 ; i<N ; i++ )
		{
			*(a+t*N+i) = 0;
			for ( int j = 0 ; j<N ; j++ )
			{
				*(a+t*N+i)+=*(a+(t-1)*N+j)*(*(A+j*N+i));
			}
			*(a+t*N+i)*=*(B+i*M+O[t]);
			c[t]+=*(a+t*N+i);
		}
		//scale a[t][i]
		c[t] = 1/c[t];
		for ( int i = 0 ; i<N ; i++ )
		{
			*(a+t*N+i)*=c[t];
		}
	}
}

void HMM::learn_process( )
{
	double* a,*b,*r3,*r2,*c;
	double log_prob = old_log_prob;
	c = new double[T];
	a = new double[T*N];
	r3 = new double[T*N*N];
	r2 = new double[T*N];
	do
	{
		old_log_prob = log_prob;
		forward_algorithm(a,c);
		backward_algorithm(b,c);
		compute_r(a,b,r3,r2);
		estimate(r3,r2);
		log_prob = compute_log_prob(c);
	}	
	while ( ++iters < max_iters && log_prob > old_log_prob );
	delete a;
	delete b;
	delete c;
	delete r3;
	delete r2;
}

void HMM::compute_r (double* a, double* b, double* r3 , double* r2 )
{
	for ( int t = 0 ; t<T-1 ; t++ )
	{
		double denom = 0 ;
		for ( int i = 0 ; i<N ; i++ )
		{
			for ( int j=0 ; j<N ; j++ )
			{
				denom+=*(a+t*N+j)*(*(A+i*N+j))*(*(B+j*M+O[t+1]))*(*(b+(t+1)*N+j));
			}
		}
		for ( int i=0 ; i<N ; i++ )
		{
			*(r2+t*N+i)=0;
			for ( int j=0 ; j<N ; j++ )
			{
				*(r3+t*N*N+i*N+j)=((*(a+t*N+i))*(*(A+i*N+j))*(*(B+j*M+O[t+1]))*(*(b+(t+1)*N+j)))/denom;
				*(r2+t*N+i)+=*(r3+t*N*N+i*N+j);
			}
		}
	}
}

double HMM::compute_log_prob( double* c )
{
	double log_prob = 0;
	for ( int i = 0 ; i<T ; i++ )
		log_prob += log(c[i]);
	return -log_prob;
}