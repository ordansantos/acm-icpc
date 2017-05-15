
static long long MOD = 1000000007;

template <typename T, int N>
struct Matrix{
    T matrix[N][N];
    Matrix (){ memset(matrix, 0, sizeof matrix); }
    T* operator [] (int i) { return matrix[i]; }
    Matrix operator * (Matrix other){
        Matrix m;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < N; k++)
                    m[i][j] = (m[i][j] + matrix[i][k] * other[k][j]) % MOD;
        return m;
    }
    Matrix operator ^ (T p){
        return power (*this, p);
    }
    Matrix power (Matrix m, T p){
        assert (p > 0);
        if (p == 1) return m;
        if (p%2) return m * power (m, p - 1);
        Matrix aux = power (m, p/2);
        return aux * aux;
    }
};
