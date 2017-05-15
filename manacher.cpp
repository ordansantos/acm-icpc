struct Manacher {
    // Two times the lenght of the string + 50
    static const int SZ = 200050;
    int M[SZ];
    string ms;
    Manacher(){}
    Manacher(const string &s){ build(s); }
    void build(const string &s){
        ms = build_string(s);
        int c = -1, l = 0;
        for (int i = 0; i < ms.size(); i++){
            if (c + l < i){
                c = i;
                l = 0;
                while (c - (l + 1) >= 0 && c + (l + 1) < ms.size() && ms[c-(l+1)] == ms[c+(l+1)]) l++;
                M[c] = l;
            } else {
                int i2 = 2 * c - i;
                if (M[i2] + i < c + l)
                    M[i] = M[i2];
                else{
                    l = (c + l) - i;
                    c = i;
                    while (c - (l + 1) >= 0 && c + (l + 1) < ms.size() && ms[c-(l+1)] == ms[c+(l+1)]) l++;
                    M[c] = l;
                }
            }
        }

    }

    int get_longest_pal(){
        int _max = 0;
        for (int i = 0; i < ms.size(); i++)
            _max = max (_max, M[i]/2 * 2 + (ms[i] != '$'));
        return _max;
    }

    // abc -> $a$b$c$
    string build_string(const string &s){
        string ms = "$";
        for (int i = 0; i < s.size(); i++)
            ms += s[i], ms += '$';
        return ms;
    }

};

