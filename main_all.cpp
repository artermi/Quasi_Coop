#include "QuasiPGG.h"
#include <unistd.h>
using namespace std;

int do_once(a,b,l,m,d,r){

	char file_n[100];
	sprintf(file_n,"A_%04d_b_%4d_l_%04d_m_%4d_d_%4d_r_%4d.dat", 
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

	QuasiPGG gameOBJ(a,r,b,l,d,m);
	gameOBJ.game(true);

	return 0;
}


int main(int argc, char** argv){
	srand(time(NULL));

	double gap = 0.1


	for(double b = 1; b < 2.01; b += gap ){
		for (double a = 0; a < 1; a += gap){
			for(double l = 0; l < 1; l += gap){
				for(double m = 0; m < 1; m += gap){
					for (double d = 0; d < 1; d += gap){
						for (double r = 0; r < 1; r += gap){
							do_once(a,b,l,m,d,r)
						}
					}
				}
			}
		}

	}


	return 0;
}
