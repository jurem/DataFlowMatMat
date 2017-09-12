#ifndef MATVEC_H
#define MATVEC_H


#include <getopt.h>


// show help
int help_flag = 0;

/* tracing
	0 - prints only n, sum of result, correctness, realtime, cputime
	1 - prints input, output, final result
*/
int trace = 0;

// seed for random numbers
int seed = 0;

// number of rows / columns. Matrix size is n*n
size_t size = 64;

// elements of matrix are in -range  to +range interval
float range = 100.0;


void help(const char * cmd) {
    printf("Usage: %s [filename]\n", cmd);
    printf("\nOptions:\n");
    printf("  -h, --help\n\tPrint short help\n");
    printf("  -t, --trace\n\tTrace level: 0,1,2\n");
    printf("  -s, --seed\n\tSeed for random numbers\n");
    printf("  -n, --size\n\tSize n of matrix\n");
    printf("  -r, --range\n\tRange of elements\n");
};


struct option options[] = {
	{ "help",	required_argument, 0, 'h' },
	{ "trace",	required_argument, 0, 't' },
	{ "seed",	required_argument, 0, 's' },
	{ "size",	required_argument, 0, 'n' },
	{ "range",	required_argument, 0, 'r' },
	{ 0, 0, 0, 0 }
};

#define SHORTOPT "ht:n:r:s:"


void parse_args(int argc, char * argv[]) {
	while (1) {
		int option_index = 0;
		int opt = getopt_long(argc, argv, SHORTOPT, options, &option_index);
		if (opt == -1) break;

		switch (opt) {
			case 'h':
				help_flag = 1;
				break;
			case 't':
				trace = atoi(optarg);
				break;
			case 's':
				seed = atoi(optarg);
				break;
			case 'n':
				size = atoi(optarg);
				break;
			case 'r':
				range = atoi(optarg);
				break;
			case '?':
				error(1, "Invalid option '%c'", optopt);
			default:
				abort();
		}
	}
	if (help_flag) {
		help(argv[0]);
		exit(0);
	}
}


void trace_inputs(size_t n, mat_t matA, mat_t matB) {
	if (trace < 1) return;
	printf("\nInput matrix\n");
	mat_print(n, n, matA);
	printf("\nInput matrix\n");
	mat_print(n, n, matB);
}


void trace_outputs(size_t n, mat_t out) {
	if (trace < 1) return;
	printf("\nOutput matrix\n");
	mat_print(n, n, out);
}


int check_outputs(size_t n, mat_t matA, mat_t matB, mat_t matC) {
	mat_t expected = mat_make(n, n);
	mul_matmat(n, n, n, matA, matB, expected);
	int status = mat_check(n, n, matC, expected, trace >= 1);
	free(expected);
	return status;
}


#define INIT_MATMAT \
	if (argc > 1) parse_args(argc, argv); \
\
	mat_t matA = mat_make(size, size); \
	mat_t matB = mat_make(size, size); \
	mat_t matC = mat_make(size, size); \
\
	mat_rand(size, size, matA, range); \
	mat_rand(size, size, matB, range); \
\
	trace_inputs(size, matA, matB); \
\
	timing_t timer; \
	timer_start(&timer);


#define DONE_MATMAT \
	timer_stop(&timer); \
\
	trace_outputs(size, matC); \
\
	float sum = mat_sumall(size, size, matC); \
	char* status = check_outputs(size, matA, matB, matC) ? "ok" : "err"; \
	printf("%ld %f %s %ld %ld\n", size, sum, status, timer.realtime, timer.cputime); \
\
	free(matA); \
	free(matB); \
	free(matC); \
\
	return 0;


#endif
