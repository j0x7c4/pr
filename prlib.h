#include <iostream>
#include <memory>

#define INF 1000000

typedef char state_type;
typedef int probability_type;

class DTW
{
typedef int distance_type;
    int                     xn,yn;
    state_type      *x,*y;
    probability_type *dtw;
public:
    DTW(state_type*, int, state_type*, int);
	DTW(){};
    ~DTW();
	void input_state(state_type*, int, state_type*, int);
    probability_type DTW_process ( );
    distance_type get_distance(state_type,state_type); 
};

class HMM
{
	int max_iters;
	int iters;
	int old_log_prob;
	int M,N,T,*O;
	double *A, *B , *pi;
public:
	HMM(int,int, int , int* , int _max_iters=10);
	void forward_algorithm ( double*, double* );
	void backward_algorithm ( double* , double*);
	void compute_r ( double* , double*, double* , double* );
	void estimate( double*, double* );
	double compute_log_prob ( double* );
	void learn_process( );
	~HMM();
};