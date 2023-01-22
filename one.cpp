#include "QuasiPGG.h"
#include <unistd.h>
using namespace std;


int main(int argc, char** argv){
	srand(time(NULL));
	double alpha = 0.3;
	double rho = 0.5; //FIX
	double b = 1.1;
	double lambd = 0.7;
	double delt = 0.1; //FIX
	double m = 0.2;

	
	printf("Now doing QuasiPGG with (a,b,l,d) = (%f,%f,%f,%f)\n",
			alpha,b,lambd,delt);



	QuasiPGG gameOBJ(alpha,rho,b,lambd,delt,m);
	gameOBJ.game(false);

	


	return 0;
}