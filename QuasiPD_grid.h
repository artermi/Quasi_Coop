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


#define K 1.2
#define L 200
#define LL (L*L)

class QuasiPD_grid{
public:
	double alpha;
	double b;
	double rho;
	double lambd;
	double delt;
	double m;
	bool grid;
	char dir_name[100];

	int Cate_Player[3];
	
	int *Strategy;
	int **Neighbour;

	QuasiPD_grid(const double A,const double R, const double B,
		const double Lam, const double D, const double M,
		bool Two = false, bool Grid = false);
	~QuasiPD_grid();
	//double unit_game(const int cent,const int target);
	double centre_game(const int cent);
	int game(bool ptf);
};
