#include "QuasiPGG.h"
using namespace std;

QuasiPGG::QuasiPGG(const double A,const double R, const double B,
	const double Lam, const double D, const double M){

	alpha = A;
	b = B;
	rho = R;
	lambd = Lam;
	delt = D;
	m = M;

	Strategy = new int[LL];

	// 0 for D, 1 for C, 2 for QC
	//Strategy initialise, with D,C,QC = (0.5,0.25,0.25)
	for(int i = 0; i < 3; i++)
		Cate_Player[i] = 0;

	for(int i = 0; i < LL; i++){
		Strategy[i] = rand() % 4;
		if(Strategy[i] == 3)
			Strategy[i] = 0;

		Cate_Player[Strategy[i]] ++;
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

QuasiPGG::~QuasiPGG(){
	delete Strategy;
	for(int i = 0; i < LL; i++){
		delete [] Neighbour[i];
	}
	delete [] Neighbour;
}


double QuasiPGG::unit_game(const int cent,const int target){

	double idivd[3] = {0.0,0.0,0.0};
	idivd[Strategy[cent]] += 1;

	int gs = 4;
	for(int i = 0; i < gs; i++){
		int person = Neighbour[cent][i];
		idivd[Strategy[person]] += 1;
	}

	if(Strategy[target] == 0)
		return ( b * idivd[1] + (b - lambd) * idivd[2]) / double(gs+1);

	if(Strategy[target] == 1)
		return ( idivd[1] + (1-alpha) * idivd[2] - delt * idivd[0] )/ double(gs+1);

	// if Strategy is 2, QC
	return ( (1+alpha) * idivd[1] + rho * idivd[2] + (m-delt) * idivd[0] ) /double(gs+1);

}


double QuasiPGG::centre_game(const int cent){
	double profit = unit_game(cent,cent);
	for(int i = 0; i < 4; i++){
		profit += unit_game(Neighbour[cent][i],cent);
	}

	return profit;
}

int QuasiPGG::game(bool ptf){

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
	int iter = 10001;
	int gap = 500;
	for(int i = 0; i < iter; i++){

		if(i % gap == 0){
			for (int j = 0; j < 3; ++j)
				rate[j] = (double) Cate_Player[j] / LL;

			if(ptf)
				fprintf(file, "%06d %.4f %.4f %.4f\n", i, rate[0],rate[1],rate[2]);
			printf( "%06d %.4f %.4f %.4f\n", i, rate[0],rate[1],rate[2]);
		
		}
		bool stop_all = true;

		for (int j = 0; j < 3; j++)
			if(rate[j] - 0.00000001 >= 0 && rate[j] + 0.00000001 <= 1)
				stop_all = false;

		if(stop_all)
			continue;

		for(int j = 0; j < LL; j++){
			int x = rand() % LL;

			int y = Neighbour[x][rand() % 4];
			if (Strategy[x] == Strategy[y])
				continue;

			double x_earn = centre_game(x);
			double y_earn = centre_game(y);

			if ((double)rand()/(double)RAND_MAX < 1.0/( 1.0 + exp((y_earn - x_earn)/K) ) ){
				Cate_Player[ Strategy[y] ] --;
				Strategy[y] = Strategy[x];
				Cate_Player[ Strategy[y] ] ++;
			}

		}
	}
	if(ptf)
		fclose(file);

	return 0;
}

