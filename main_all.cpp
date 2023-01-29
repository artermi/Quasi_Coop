#include "QuasiPGG.h"
#include <unistd.h>
using namespace std;

int do_once(double a,double b,double l,double m,double d,double r){

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
		return 0;
	}

	file = fopen(file_n, "w");
	fclose(file);

	QuasiPGG gameOBJ(a,r,b,l,d,m);
	gameOBJ.game(true);

	return 0;
}


int main(int argc, char** argv){
	srand(time(NULL));

	double gap = 0.125;


	for(double b = 1.25; b < 2.01; b += gap ){
		for (double a = 0.25; a < 1.01; a += gap){
			for(double l = 0.25; l < 1.01; l += gap){
				for(double m = 0.25; m < 1.01; m += gap){
					for (double d = 0.25; d < 1.01; d += gap){
						for (double r = 0.25; r < 1.01; r += gap){
							do_once(a,b,l,m,d,r);
						}
					}
				}
			}
		}

	}


	return 0;
}
