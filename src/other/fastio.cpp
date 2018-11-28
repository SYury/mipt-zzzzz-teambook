#define FASTIO_BUF_SZ  (1<<12)
static char in_buf[FASTIO_BUF_SZ];
static size_t in_buf_ptr = 0, in_buf_len = 0;
static char out_buf[FASTIO_BUF_SZ];
static size_t out_buf_ptr = 0;

static inline char read_char(){
	if(__builtin_expect(in_buf_ptr == in_buf_len, 0)){
		in_buf_ptr = 0;
		in_buf_len =
			fread(in_buf, 1, FASTIO_BUF_SZ, stdin);
	}
	return in_buf[in_buf_ptr++];
}

static inline void flush(){
	fwrite(out_buf, 1, out_buf_ptr, stdout);
	out_buf_ptr = 0;
}

static inline void write_char(char c){
	if(__builtin_expect(out_buf_ptr == FASTIO_BUF_SZ, 0))
		flush();
	out_buf[out_buf_ptr++] = c;
}

static char write_tmp[FASTIO_BUF_SZ];

#define rint(x) for(int rinttmp = 0; rinttmp < 1; rinttmp++){\
	x = 0;\
	char c = 0;\
	while(c != '-' && !isdigit(c))\
		c = read_char();\
	int neg = 0;\
	if(c == '-'){neg = 1; c = read_char();}\
	while(isdigit(c)){\
		x = x*10 + (c - '0');\
		c = read_char();\
	}\
	if(neg)x = -x;\
	}

#define wint(x) for(int winttmp = 0; winttmp < 1; winttmp++){\
	if(x < 0){write_char('-'); x = -x;}\
	int pos = 0;\
	if(!x)write_tmp[pos++] = '0';\
	while(x){\
		write_tmp[pos++] = '0' + x%10;\
		x /= 10;\
	}\
	for(int i = pos - 1; i >= 0; i--)\
		write_char(write_tmp[i]);\
	}
