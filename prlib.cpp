#include "prlib.h"
#include <cstring>

DTW::DTW ( char* xs, int m , char* ys, int n )
{
    xn = m , yn = n;
    x = new state_type[m+1];
    y = new state_type[n+1];
	x = strcpy(x,xs);
	y = strcpy(y,ys);
	dtw = new probability_type[(m+1)*(n+1)];
	//dtw[0,j]=INF;
	for ( int i = 0 ; i<=n ; i++ )
	{
		dtw[i]=INF;
	}
	//dtw[i,0]=INF;
	for ( int i=0 ; i<=m ; i++ )
	{
		dtw[i*n]=INF;
	}
	//dtw[0,0]=0;
	dtw[0] = 0;
}

DTW::~DTW( )
{
	delete(x);
	delete(y);
	delete(dtw);
}

void DTW::input_state(state_type* xs, int m, state_type* ys, int n)
{
	xn = m , yn = n;
    x = new state_type[m+1];
    y = new state_type[n+1];
	x = strcpy(x,xs);
	y = strcpy(y,ys);
	dtw = new probability_type[(m+1)*(n+1)];
	//dtw[0,j]=INF;
	for ( int i = 0 ; i<=n ; i++ )
	{
		dtw[i]=INF;
	}
	//dtw[i,0]=INF;
	for ( int i=0 ; i<=m ; i++ )
	{
		dtw[i*n]=INF;
	}
	//dtw[0,0]=0;
	dtw[0] = 0;
}
probability_type DTW::DTW_process ( )
{
	probability_type cost,temp;
	for ( int i=1 ; i<=xn ; i++ )
	{
		for ( int j=1; j<=yn ; j++ )
		{
			cost = get_distance(x[i-1],y[j-1]);
			//temp = min(dtw[i-1,j], dtw[i-1,j-1], dtw[i,j-1]);
			temp = dtw[(i-1)*yn+j-1];
			if ( dtw[i*yn+j-1] < temp ) temp = dtw[i*yn+j-1];
			if ( dtw[(i-1)*yn+j] < temp ) temp = dtw[(i-1)*yn+j];
			//dtw[i,j] = d(x[i],y[j]) + min(dtw[i-1,j], dtw[i-1,j-1], dtw[i,j-1])
			dtw[i*yn+j] = cost + temp;
		}
	}
	return dtw[xn*yn+yn]; //dtw[xn,yn];
}

DTW::distance_type DTW::get_distance(state_type x, state_type y)
{
	return x-y>0?x-y:y-x;
}