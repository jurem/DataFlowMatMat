#ifndef MATRIX_H
#define MATRIX_H


#include "rand.h"

// ********** type of elements ***********


#define PRECISION	0.01


typedef float elt_t;


// ********** vector **********


typedef elt_t * vec_t;


vec_t vec_make(size_t n) {
	return malloc(n * sizeof(elt_t));
}


void vec_copy(size_t n, vec_t src, vec_t dst) {
	for (size_t i = 0; i < n; i++)
		dst[i] = src[i];
}


void vec_rand(size_t n, vec_t vector, int range) {
	for (size_t i = 0; i < n; i++)
		vector[i] = rand_signdouble(range);
}


void vec_print(size_t n, vec_t vec) {
	for (size_t i = 0; i < n; i++)
		printf("%6.2f ", vec[i]);
	printf("\n");
}


elt_t vec_sumall(size_t n, vec_t vec) {
	elt_t sum = 0;
	for (size_t i = 0; i < n; i++)
		sum += vec[i];
	return sum;
}


char vec_equals(size_t n, vec_t vecA, vec_t vecB) {
	for (size_t i = 0; i < n; i++)
		if (abs(vecA[i] - vecB[i]) > PRECISION) return 0;
	return 1;
}


char vec_check(size_t n, vec_t vecA, vec_t vecB, char trace) {
	char status = 1;
	for (size_t i = 0; i < n; i++)
		if (abs(vecA[i] - vecB[i]) > PRECISION) {
			if (trace) fprintf(stderr, "[%ld] error, output: %f != expected: %f\n", i, vecA[i], vecB[i]);
			status = 0;
		}
	return status;
}


// ********** matrix **********


typedef elt_t * mat_t;


mat_t mat_make(size_t n, int m) {
	return malloc(n * m * sizeof(elt_t));
}


void mat_copy(size_t n, size_t m, mat_t src, mat_t dst) {
	vec_copy(n * m, src, dst);
}


void mat_rand(size_t n, size_t m, mat_t mat, float range) {
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < m; j++)
			mat[i * m + j] = rand_signdouble(range);
}



void mat_print(size_t n, size_t m, mat_t mat) {
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++)
			printf("%-6.2f ", mat[i * m + j]);
		printf("\n");
	}
}


float mat_sumall(size_t n, size_t m, mat_t mat) {
	return vec_sumall(n * m, mat);
}


char mat_check(size_t n, size_t m, mat_t matA, mat_t matB, char trace) {
	return vec_check(n * m, matA, matB, trace);
}


void mat_transpose(size_t n, size_t m, mat_t src, mat_t dst){
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < m; j++)
			dst[j * n + i] = src[i * m + j];
}


void mat_transform_rowstripes(size_t n, size_t m, size_t s, mat_t src, mat_t dst) {
	int d = 0;
	for (size_t i = 0; i < n; i += s)
		for (size_t j = 0; j < m; j++)
			for (size_t k = 0; k < s; k++)
				dst[d++] = src[(i + k) * m + j];
}


void mat_transform_colstripes(size_t n, size_t m, size_t s, mat_t src, mat_t dst){
	int d = 0;
	for (size_t j = 0; j < m; j += s)
		for (size_t i = 0; i < n; i++)
			for (size_t k = 0; k < s; k++)
				dst[d++] = src[i * m + j + k];
}


// ********** operations on matrices and vectors **********


void mul_matvec(size_t n, size_t m, mat_t mat, mat_t vec, mat_t dst) {
	for (size_t i = 0; i < n; i++) {
		dst[i] = 0;
		for (size_t j = 0; j < m; j++)
			dst[i] += mat[i * m + j] * vec[j];
	}
}


void mul_matmat(size_t n, size_t l, size_t m, mat_t matA, mat_t matB, mat_t matC) {
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < m; j++) {
			elt_t sum = 0;
			for (size_t k = 0; k < l; k++)
				sum += matA[i * m + k] * matB[k * l + j];
			matC[i * m + j] = sum;
		}
}


#endif
