#include "common/common.h"
#include "common/timer.h"
#include "common/matrix.h"
#include "common/matmat.h"


int main(int argc, char * argv[]) {
	INIT_MATMAT

	mat_t matBT = mat_make(size, size);
	mat_transpose(size, size, matB, matBT);
	mul_matmat_transposed(size, size, size, matA, matBT, matC);
	free(matBT);

	DONE_MATMAT
}
