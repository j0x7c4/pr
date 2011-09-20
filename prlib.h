#define INF 100000000
typedef char state_type;
typedef int probability_type;
typedef int* probability_type_pointer;



class DTW
{
typedef int distance_type;
    int                     xn,yn;
    state_type      *x,*y;
    probability_type_pointer dtw;
public:
    DTW(state_type*, int, state_type*, int);
	DTW(){};
    ~DTW();
	void input_state(state_type*, int, state_type*, int);
    probability_type DTW_process ( );
    distance_type get_distance(state_type,state_type); 
};

