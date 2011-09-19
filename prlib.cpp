#include "prlib.h"

DTW::DTW ( int m , int n )
{
    xn = m , yn = n;
    x = new state_type[m+1];
    y = new state_type[n+1];

}
