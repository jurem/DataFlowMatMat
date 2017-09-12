#include "common/common.h"
#include "common/timer.h"
#include "common/matrix.h"
#include "common/matmat.h"


int main(int argc, char * argv[]) {
	INIT_MATMAT

	mul_matmat(size, size, size, matA, matB, matC);

	DONE_MATMAT
}
