#include "QuasiPGG.h"
#include <unistd.h>
using namespace std;


int main(int argc, char** argv){
	srand(time(NULL));
	double alpha = 0.1;
	double rho = 0.95; //FIX
	double b = 12.0;
	double lambd = 0.05;
	double delt = 0.1; //FIX
	double m = 0.2;

	
	printf("Now doing QuasiPGG with (a,b,l,d) = (%f,%f,%f,%f)\n",
			alpha,b,lambd,delt);



	QuasiPGG gameOBJ(alpha,rho,b,lambd,delt,m);
	gameOBJ.game(false);

	


	return 0;
}