#include "QuasiPD_grid.h"
using namespace std;

QuasiPD_grid::QuasiPD_grid(const double A,const double R, const double B,
	const double Lam, const double D, const double M,bool Two, bool Grid){

	alpha = A;
	b = B;
	rho = R;
	lambd = Lam;
	delt = D;
	m = M;
	grid = Grid;

	Strategy = new int[LL];

	// 0 for D, 1 for C, 2 for QC
	//Strategy initialise, with D,C,QC = (0.5,0.25,0.25)
	for(int i = 0; i < 3; i++)
		Cate_Player[i] = 0;

	if(Two){
		for(int i = 0; i < LL; i++){
			Strategy[i] = rand() % 2;

			Cate_Player[Strategy[i]] ++;
		}		
	}
	else{
		for(int i = 0; i < LL; i++){
			Strategy[i] = rand() % 4;
			if(Strategy[i] == 3)
				Strategy[i] = 0;

			Cate_Player[Strategy[i]] ++;
		}
	}

	Neighbour = new int *[LL];
	for(int i = 0; i < LL; i++)
		Neighbour[i] = new int[4];

	for(int i = 0; i < LL; i++){
		Neighbour[i][0] = (i - L + LL ) % LL; //North
		Neighbour[i][1] = (i + L) % LL;
		Neighbour[i][2] = (i + 1) % LL;
		Neighbour[i][3] = (i - 1 + LL) % LL;
	}//initialise the neighbour




}

QuasiPD_grid::~QuasiPD_grid(){
	delete Strategy;

}


double QuasiPD_grid::centre_game(const int cent){
	double profit = 0;
	double pay_table[3][3] = 
	{{0, b, b-lambd}, {-delt,1,1-alpha}, {m - delt, 1+alpha, rho} };

/*
	int rand_four[4];

	for(int i = 0;i<4;i++){
		int rand_1;
		bool used = true;

		while(used){
			rand_1 = rand() % LL;
			used = (rand_1 == cent);
			for(int j = 0; j < i; j++)
				if(rand_four[j] == rand_1)
					used = true;
		}
		rand_four[i] = rand_1;

	}
*/

	for(int i = 0; i < 4; i++){
		profit += pay_table[ Strategy[cent]][Strategy[ Neighbour[cent][i] ]] ;
	}

	return profit;
}

int QuasiPD_grid::game(bool ptf){

	FILE *file;
	if(ptf){
		char path[100];
		
		sprintf(path,"A_%04d_b_%04d_l_%04d_m_%04d_d_%04d_r_%04d.dat", 
		(int)((alpha + 0.000001) * 100), (int)((b + 0.000001) * 100),
		(int)((lambd + 0.000001) * 100), (int)((m + 0.000001) * 100),
		(int)((delt + 0.000001) * 100), (int)((rho + 0.000001) * 100));

		printf("Now file:%s\n",path);
		file = fopen(path,"a+");
	}

	double rate[3] = {0.0, 0.0, 0.0};
	double previous[5][3];
	int iter = 1001;
	int gap = 100;
	bool stop_all_0 = true;

	for(int i = 0; i < iter; i++){
		bool stop_all = true;

 
		if(i % gap == 0){
			for (int j = 0; j < 3; ++j)
				rate[j] = (double) Cate_Player[j] / LL;

			if(ptf)
				fprintf(file, "%06d %.4f %.4f %.4f\n", i, rate[0],rate[1],rate[2]);
			printf( "%06d %.4f %.4f %.4f\n", i, rate[0],rate[1],rate[2]);

			double pert = 0.02;
			for(int j = 1; j < 5; j++)
				for(int k = 0; k < 3; k ++)
					previous[j-1][k] = previous[j][k];
			for(int k = 0; k < 3; k++)
				previous[4][k] = rate[k];

			if(i > iter/4){
				stop_all_0 = true;

				for(int j = 0; j < 5; j++)
					for(int k = 0; k < 3; k ++)
						if(abs(rate[k] - previous[j][k]) > pert){
							stop_all_0 = false;
						}
			}
			else{
				stop_all_0 = false;
			}
		}

		for (int j = 0; j < 3; j++)
			if(rate[j] - 0.00000001 >= 0 && rate[j] + 0.00000001 <= 1)
				stop_all = false;

		if(stop_all || stop_all_0)
			continue;

		if(grid && i % gap == 0){
			char path2[100];
			sprintf(path2,"A_%04d_b_%04d_l_%04d_m_%04d_d_%04d_r_%04d_i_%05d.dat", 
					(int)((alpha + 0.000001) * 100), (int)((b + 0.000001) * 100),
					(int)((lambd + 0.000001) * 100), (int)((m + 0.000001) * 100),
					(int)((delt + 0.000001) * 100), (int)((rho + 0.000001) * 100),
					i);
			FILE *gfile = fopen(path2,"a+");	
			for(int j = 0; j < LL;j++){
				fprintf(gfile, "%d", Strategy[j]);

			}
		}

		for(int j = 0; j < LL; j++){
			int x = rand() % LL;
			int old_st = Strategy[x];

			int alter = (old_st + 1 + rand() % 2) % 3;

			bool exist = false;
			for(int k =0; k < 4; k++)
				if (Strategy[ Neighbour[x][k]] == alter)
					exist = true;

			if (!exist){
				alter = (2 * old_st - alter + 3) % 3;
				for(int k =0; k < 4; k++)
					if (Strategy[ Neighbour[x][k]] == alter)
						exist = true;				
			}

			if (!exist)
				continue;

			double x_earn = centre_game(x);
			Strategy[x] = alter;
			double y_earn = centre_game(x);

			if ((double)rand()/(double)RAND_MAX < 1.0/( 1.0 + exp((y_earn - x_earn)/K) ) ){
				Strategy[x] = old_st;
			}
			else{
				Cate_Player[ old_st ] --;
				Cate_Player[ alter ] ++;
			}

		}
	}
	if(ptf)
		fclose(file);

	return 0;
}

