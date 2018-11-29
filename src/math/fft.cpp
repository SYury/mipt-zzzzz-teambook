typedef complex<double> ftype;
const double pi = acos(-1);
ftype w[maxn];

template<typename T>
void fft(T *in, ftype *out, int n, int k = 1) {
    if(n == 1) {
        *out = *in;
        return;
    }
    n /= 2;
    fft(in, out, n, 2 * k);
    fft(in + k, out + n, n, 2 * k);
    for(int i = 0; i < n; i++) {
        ftype t = out[i + n] * w[i + n];
        out[i + n] = out[i] - t;
        out[i] += t;
    }
}

vector<int> nrm(vector<int> x) {
    while(x.size() && x.back() == 0) {
        x.pop_back();
    }
    return x;
}

vector<int> mul(vector<int> a, vector<int> b) {
    int n = a.size() + b.size() - 1;
    while(__builtin_popcount(n) != 1) {
        n++;
    }
    while((int)a.size() < n) {
        a.push_back(0);
    }
    while((int)b.size() < n) {
        b.push_back(0);
    }
    static ftype A[maxn], B[maxn];
    static ftype C[maxn], D[maxn];
    for(int i = 0; i < n; i++) {
        A[i] = {a[i] & mask, a[i] >> shift};
        B[i] = {b[i] & mask, b[i] >> shift};
    }
    fft(A, C, n);
    fft(B, D, n);
    for(int i = 0; i < n; i++) {
        ftype c0 = (C[i] + conj(C[(n - i) % n])) / ftype(2, 0);
        ftype c1 = (C[i] - conj(C[(n - i) % n])) / ftype(0, 2);
        ftype d0 = (D[i] + conj(D[(n - i) % n])) / ftype(2, 0);
        ftype d1 = (D[i] - conj(D[(n - i) % n])) / ftype(0, 2);
        A[i] = c0 * d0 + ftype(0, 1) * c1 * d1;
        B[i] = c0 * d1 + d0 * c1;
    }
    fft(A, C, n);
    fft(B, D, n);
    reverse(C + 1, C + n);
    reverse(D + 1, D + n);
    for(int i = 0; i < n; i++) {
        int64_t A0 = llround(real(C[i]) / n);
        int64_t A1 = llround(real(D[i]) / n);
        int64_t A2 = llround(imag(C[i]) / n);
        a[i] = (A0 + (A1 % mod << shift) + (A2 % mod << 2 * shift)) % mod;
    }
    return a;
}

void init() {
    for(int i = 1; i < maxn; i *= 2) {
        for(int j = 0; j < i; j++) {
            w[i + j] = polar(1., pi * j / i);
        }
    }
}
