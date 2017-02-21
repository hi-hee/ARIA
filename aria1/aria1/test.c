#include "mode.h"
#include <Windows.h>

#define rdtsc(x) \
{ __asm __emit 0fh __asm __emit 031h __asm mov x, eax}
#define rdtscEx(low, high) \
{ __asm __emit 0fh __asm __emit 031h __asm mov low, eax _asm mov high, edx}
#define cpuid {__asm __emit 0fh __asm __emit 0a2h}


int main(){

	LARGE_INTEGER start, end, tmp;
	__int64 freq, diff;

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&freq)) {
	
	rdtscEx(start.LowPart, start.HighPart);
	
	for (int i = 0; i < 100; i++){
		/*CBC*/
		CBCKat();
		CBCMct();
		CBCMmt();

		/*ECB*/
		ECBKat();
		ECBMct();
		ECBMmt();

		/*CTR*/
		CTRKat();
		CTRMct();
		CTRMmt();
	}

	rdtscEx(end.LowPart, end.HighPart);
	diff = (*(__int64*)&end - *(__int64*)&start)/100;

	printf("printf elapsed clock cycle is %I64d\n", diff);
	}
	else
		printf("This computer don't support QueryPerformance function sets!!\n");


	return 0;
}



// 파일 입출력 스트림으로 받는 거 해보기