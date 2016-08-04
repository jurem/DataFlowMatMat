#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>

#include <MaxSLiCInterface.h>
#include "Maxfiles.h"

#include "common/common.h"
#include "common/timer.h"
#include "common/matrix.h"
#include "common/matmat.h"


#define BLOCK_SIZE MatMat_BLOCK_SIZE

void block_reorder(size_t n, size_t blockCount, mat_t src, mat_t dst) {
	int pos = 0;
	for (size_t i = 0; i < blockCount; i++)
		for (size_t j = 0; j < blockCount; j++)
			for (int ii = 0; ii < BLOCK_SIZE; ii++) {
				size_t row = i * BLOCK_SIZE + ii;
				for (int jj = 0; jj < BLOCK_SIZE; jj++) {
					size_t col = j * BLOCK_SIZE + jj;
					dst[pos++] = row < n && col < n ? src[row * n + col] : 0;
				}
			}
}


int main(int argc, char * argv[]) {
	INIT_MATMAT;

	size_t blockCount = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
	size_t size_align = blockCount * BLOCK_SIZE;

	mat_t matA_blocks = mat_make(size_align, size_align);
	mat_t matB_blocks = mat_make(size_align, size_align);

	block_reorder(size, blockCount, matA, matA_blocks);
	block_reorder(size, blockCount, matB, matB_blocks);

	memset(matC, 0, sizeof matC);
	mat_t out_block = mat_make(BLOCK_SIZE, BLOCK_SIZE);

	for (size_t i = 0; i < blockCount; i++)
		for (size_t j = 0; j < blockCount; j++)
			for (size_t k = 0; k < blockCount; k++) {
				int a_tile = (i * blockCount + k) * BLOCK_SIZE*BLOCK_SIZE;
				int b_tile = (k * blockCount + j) * BLOCK_SIZE*BLOCK_SIZE;
				MatMat(&matA_blocks[a_tile], &matB_blocks[b_tile], out_block);
				// copy to matC
				size_t start = i * BLOCK_SIZE * size + j * BLOCK_SIZE;
				size_t p = 0;
				for (size_t ii = 0; ii < BLOCK_SIZE; ii++)
					for (size_t jj = 0; jj < BLOCK_SIZE; jj++)
						if (ii < size && jj < size)
							matC[start + ii*size + jj] += out_block[p++];
			}

	free(matA_blocks);
	free(matB_blocks);
	free(out_block);

	DONE_MATMAT;
}
