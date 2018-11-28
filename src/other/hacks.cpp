//stack
//from github.com/koosaga/DeobureoMinkyuParty/blob/master/
int main2(){ return 0; }
int main(){
	size_t  sz = 1<<29;  // 512MB
	void* newstack = malloc(sz);
	void* sp_dest = newstack + sz - sizeof(void*);
	asm  __volatile__("movq %0, %%rax\n\t"
	"movq %%rsp , (%%rax)\n\t"
	"movq %0, %%rsp\n\t": : "r"(sp_dest): );
	main2();
	asm  __volatile__("pop %rsp\n\t");
	return  0;
}

//sse
void sse_example(){
	int32_t a[4]__attribute__((aligned (16))) = {1, 2, 3, 4};
	int32_t b[4]__attribute__((aligned (16))) = {0, 10, 100, 1000};
	__m128i am = _mm_load_si128((__m128i*)a);
	__m128i bm = _mm_load_si128((__m128i*)b);
	am = _mm_add_epi32(am, bm);
	_mm_store_si128((__m128i*)a, am);
	for(int i = 0; i < 4; i++)
		printf("%d ", a[i]);
}
