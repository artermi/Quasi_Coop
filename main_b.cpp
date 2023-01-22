#include "QuasiPGG.h"
#include <unistd.h>
using namespace std;


int main(int argc, char** argv){
	srand(time(NULL));
//	double rho = 0.5; //FIX
//	double lambd = 0.7;

	double alpha = 0.1;
	double rho = 0.5; //FIX
	double b = 1.2;
	double lambd = 0.7;
	double delt = 0.1; //FIX
	double m = 0.2;


	
	printf("Now doing QuasiPGG with (a,b,l,d) = (%f,%f,%f,%f)\n",
		alpha,b,lambd,delt);

	for(double b = 1.0; b < 2.01; b += 0.02 ){
		char file_n[100];
		sprintf(file_n,"b_%04d_A_%04d_m_%04d_L_%04d.dat", 
			(int)((b + 0.000001) * 100),  (int)((alpha + 0.000001) * 1000),
			(int)((m + 0.000001) * 1000), (int)((lambd + 0.000001) * 1000));

		FILE *file;
  		file = fopen(file_n, "r");

		if (file) {
			fclose(file);
			printf("file:'%s' exists\n",file_n);
			usleep(100000);
			continue;
		}

		file = fopen(file_n, "w");
		fclose(file);

		QuasiPGG gameOBJ(alpha,rho,b,lambd,delt,m);
		gameOBJ.game(true);

	}


	return 0;
}
