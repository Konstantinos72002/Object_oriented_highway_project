#include "headers.h"

int main (int argc,char* argv[]) {
	const int N = atoi(argv[1]), Nsegs = atoi(argv[2]), K = atoi(argv[3]), capacity = atoi(argv[5]), percent = atoi(argv[4]);
	Highway attiki_odos(Nsegs,capacity,K,percent);
	for(unsigned int i=0; i<N;i++) {
		attiki_odos.operate();
	}
	int a;
	cin >>a;
	return 0;
}