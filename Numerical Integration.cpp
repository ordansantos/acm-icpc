
#define N 12
double R[N + 1][N + 1];
// >>2d2dd13aba7f0cdd30ac401877c336a1
// a, b: limits of integration
// F: function pointer to function to be integrated.
double romberg(double a, double b, double (*F)(double)){
	int i, j, k;
	double sum, h = (b - a);

	R[0][0] = ((*F)(a) + (*F)(b)) * h / 2;

	for (i = 1; i <= N; i++){
		h = h / 2;

		sum = 0;
		for (k = 1; k < (1<<i); k += 2)
			sum += (*F)(a + k * h);

		R[i][0] = R[i-1][0] / 2 + sum * h;
		for (j = 1; j <= i; j++)
			R[i][j] = R[i][j-1] + (R[i][j-1] - R[i-1][j-1]) / ((1<<(2*j)) - 1);
	}

	return R[N][N];
}
// >>2d2dd13aba7f0cdd30ac401877c336a1

double F(double x){
	return sin(x) + cos(x) + x * x;
}

int main(){
    printf ("%lf", romberg(141, 456, F)); //30671864.145045
    return 0;
}

