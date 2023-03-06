#include "QuasiPGG.h"
#include <unistd.h>
using namespace std;


int main(int argc, char** argv){
	srand(time(NULL));
	double alpha = 0.3;
	double rho = 0.5; //FIX
	double b = 1.53;
	double lambd = 0.7;
	double delt = 0.1; //FIX
	double m = 0.2;


	QuasiPGG gameOBJ(alpha,rho,b,lambd,delt,m,false,true);
	gameOBJ.game(false);

	


	return 0;
}