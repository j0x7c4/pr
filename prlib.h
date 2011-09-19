#define INF 100000000
typedef int state_type;
typedef (char*) state_type_pointer;
typedef double probability_type;
typedef (double*) probability_type_pointer;
typedef (int**) probability_type_matrix;


class DTW
{
typedef int distance_type;
    int                     xn,yn;
    state_type_pointer      x,y;
    probability_type_matrix dtw;
public:
    DTW(int m, int n);
    ~DTW();
    probability_type DTW_process ( );
    distance_type get_distance(state_type,state_type); 
};

