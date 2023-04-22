#include "QuasiPD.h"
#include <unistd.h>
using namespace std;


int main(int argc, char** argv){
	srand(time(NULL));
//	double rho = 0.5; //FIX
//	double b = 1.2;
//	double lambd = 0.7;


	double a = 0.1;
	double r = 0.5; //FIX
	double b = 1.2;
	double l = 0.7;
	double d = 0.1; //FIX
	double m = 0.2;

	
	printf("Now doing QuasiPD with (a,b,l,d) = (%f,%f,%f,%f)\n",
		a,b,l,d);

	for(double l = 0; l < 1.001; l += 0.02 ){

		char file_n[100];
		sprintf(file_n,"A_%04d_b_%04d_l_%04d_m_%04d_d_%04d_r_%04d.dat", 
			(int)((a + 0.000001) * 100), (int)((b + 0.000001) * 100),
			(int)((l + 0.000001) * 100), (int)((m + 0.000001) * 100),
			(int)((d + 0.000001) * 100), (int)((r + 0.000001) * 100));

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

		QuasiPD gameOBJ(a,r,b,l,d,m);
		gameOBJ.game(true);

	}


	return 0;
}
