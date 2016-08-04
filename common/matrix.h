#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include "rand.h"


// ********** common ***********


#define PRECISION	0.01


typedef float elt_t;


// ********** vector **********


typedef elt_t * vec_t;


vec_t vec_make(int n) {
	return malloc(n * sizeof(elt_t));
}


void vec_copy(int n, vec_t src, vec_t dst) {
	for (int i = 0; i < n; i++)
		dst[i] = src[i];
}


void vec_rand(int n, vec_t vector, int range) {
	for (int i = 0; i < n; i++)
		vector[i] = rand_signdouble(range);
}


void vec_print(int n, vec_t vec) {
	for (int i = 0; i < n; i++)
		printf("%6.2f ", vec[i]);
	printf("\n");
}


elt_t vec_sum(int n, vec_t vec) {
	elt_t sum = 0;
	for (int i = 0; i < n; i++)
		sum += vec[i];
	return sum;
}


char vec_equals(int n, vec_t vecA, vec_t vecB) {
	for (int i = 0; i < n; i++)
		if (vecA[i] != vecB[i]) return 0;
	return 1;
}


char vec_check(int n, vec_t vecA, vec_t vecB, int trace) {
	char status = 1;
	for (int i = 0; i < n; i++) {
		// check to int precision, float may variate too much
		if (abs(vecA[i] - vecB[i]) > PRECISION) {
			if (trace) fprintf(stderr, "[%d] error, output: %f != expected: %f\n", i, vecA[i], vecB[i]);
			status = 0;
		}
	}
	return status;
}


// ********** matrix **********


typedef elt_t * mat_t;


mat_t mat_make(int n, int m) {
	return malloc(n * m * sizeof(elt_t));
}


void mat_copy(int n, int m, mat_t src, mat_t dst) {
	vec_copy(n * m, src, dst);
}


void mat_rand(int n, int m, mat_t mat, float range) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			mat[i * m + j] = rand_signdouble(range);
}



void mat_print(int n, int m, mat_t mat) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			printf("%-6.2f ", mat[i * m + j]);
		printf("\n");
	}
}


elt_t mat_sum(int n, int m, mat_t mat) {
	return vec_sum(n * m, mat);
}


elt_t mat_check(int n, int m, mat_t matA, mat_t matB, int trace) {
	return vec_check(n * m, matA, matB, trace);
}

void mat_transpose(int n, int m, mat_t src, mat_t dst){
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			dst[j * n + i] = src[i * m + j];
}


void mat_transform_rowstripes(int n, int m, int s, mat_t src, mat_t dst) {
	int d = 0;
	for (int i = 0; i < n; i += s)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < s; k++)
				dst[d++] = src[(i + k) * m + j];
}


void mat_transform_colstripes(int n, int m, int s, mat_t src, mat_t dst){
	int d = 0;
	for (int j = 0; j < m; j += s)
		for (int i = 0; i < n; i++)
			for (int k = 0; k < s; k++)
				dst[d++] = src[i * m + j + k];
}


// ********** operations on matrices and vectors **********


void mul_matvec(int n, int m, mat_t mat, mat_t vec, mat_t dst) {
	for (int i = 0; i < n; i++) {
		dst[i] = 0;
		for (int j = 0; j < m; j++)
			dst[i] += mat[i * m + j] * vec[j];
	}
}


void mul_matmat(int n, int l, int m, mat_t matA, mat_t matB, mat_t matC) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			elt_t sum = 0;
			for (int k = 0; k < l; k++)
				sum += matA[i * m + k] * matB[k * l + j];
			matC[i * m + j] = sum;
		}
}


#endif
