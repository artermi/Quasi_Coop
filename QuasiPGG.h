#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>


#define K 0.5
#define L 200
#define LL (L*L)

class QuasiPGG{
public:
	double alpha;
	double b;
	double rho;
	double lambd;
	double delt;
	double m;
	char dir_name[100];

	int Cate_Player[3];
	
	int *Strategy;
	int **Neighbour;

	QuasiPGG(const double A,const double R, const double B,
		const double Lam, const double D, const double M);
	~QuasiPGG();
	double unit_game(const int cent);
	double centre_game(const int cent);
	int game(bool ptf);
};
