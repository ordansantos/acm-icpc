template<typename T>
T det (vector <vector<T>> m, T mod){
    T det = 1;
    for (auto& v: m) for (auto& x: v) x %= mod;
    for (int j = 0; j < m.size(); j++){
        for (int i = j + 1; i < m.size(); i++){
            while (m[i][j]){
                T t = m[j][j] / m[i][j];
                for (int k = j; k < m.size(); k++){
                    m[j][k] = (m[j][k] - m[i][k] * t % mod) % mod;
                    swap(m[j][k], m[i][k]);
                }
                det = -det;
            }
        }
        det = det * m[j][j] % mod;
    }
    return (det % mod + mod) % mod;
}
