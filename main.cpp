#include "prlib.h"
#include <iostream>
using namespace std;

int main ( )
{
	char* x = "hii";
	char* y = "aiii";

	//DTW dtw(x,strlen(x),y,strlen(y));
	DTW dtw;
	dtw.input_state(x,strlen(x),y,strlen(y));
	printf("%d\n",dtw.DTW_process());
}