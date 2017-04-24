C[0][0] = 1;
for (int i = 1; i <= N; i++)
    for (int j = 0; j <= i; j++)
        C[i][j] = (j-1 >= 0? C[i-1][j-1] : 0) + C[i-1][j];
