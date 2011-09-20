#include "prlib.h"

DTW::DTW ( int m , int n )
{
    xn = m , yn = n;
    x = new state_type[m+1];
    y = new state_type[n+1];
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
}

DTW::~DTW( )
{
	delete(x);
	delete(y);
	delete(dtw);
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
			temp = dtw[(i-1)*xn+j-1];
			if ( dtw[i*xn+j-1] > temp ) temp = dtw[i*xn+j-1];
			if ( dtw[(i-1)*xn+j] > temp ) temp = dtw[(i-1)*xn+j];
			//dtw[i,j] = d(x[i],y[j]) + min(dtw[i-1,j], dtw[i-1,j-1], dtw[i,j-1])
			dtw[i*xn+j] = cost + temp;
		}
	}
	return dtw[xn*yn]; //dtw[xn,yn];
}