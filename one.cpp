#include "QuasiPD_grid.h"
#include <unistd.h>
using namespace std;


int main(int argc, char** argv){
	srand(time(NULL));
	double alpha = 0.1;
	double rho = 0.5; //FIX
	double b = 1.2;
	double lambd = 0.4;
	double delt = 0.1; //FIX
	double m = 0.2;


	QuasiPD_grid gameOBJ(alpha,rho,b,lambd,delt,m,false,true);
	gameOBJ.game(false);

	


	return 0;
}