// Coding Challenge - WC
// Mimics the functionality of the wc command line utility

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <limits.h>
#include <stdarg.h>
#include <ctype.h>

#define COUNTS 3 // Keeps track of the number of counters; used for array sizing and indexing

bool bytes_flag,lines_flag, words_flag;
int arg_in;
static struct option long_opts [] = {
	{"bytes", no_argument, 0, 'c'},
	{"lines", no_argument, 0, 'l'},
	{"words", no_argument, 0, 'w'},
	{0,0,0,0}
};

/* 
 * Takes in a file and counts the total bytes, words, and lines respective to their flags
 * Returns a pointer to an int array with the total count results
*/
int * counter(const char *filename, bool bytes_flag, bool words_flag, bool lines_flag){
	int * counts = malloc(sizeof(int) * COUNTS);
	FILE * file_stream;

	int line_count = 0;
	int word_count = 0;
	int byte_count = 0;

	file_stream = fopen(filename, "r");

	if (file_stream == NULL) {
		printf("File count not be opened.\n");
	}
	else{
		int last = '\n', c;
        while ((c = getc(file_stream)) != EOF) {
            byte_count++;
            if (isspace(c)) {
                if (c == '\n')
                    line_count++;
            } else {
                if (isspace(last))
                    word_count++;
            }
            last = c;
        }
        if (last != '\n')
            line_count++;
		fclose(file_stream);

		if (lines_flag) {counts[0] = line_count;}
		if (words_flag) {counts[1] = word_count;}
		if (bytes_flag) {counts[2] = byte_count;}
	}
	return counts;
}

/*
 * Print function to output the results to stdout
 */
void print_file_results(const char *filename, int * totals_array){
	int i = 0;
	int array_size = sizeof(int) * COUNTS / sizeof(totals_array[0]);
	for (i = 0; i < array_size; i++){
		if (totals_array[i] != 0){
			printf("%d ", totals_array[i]);
		}
	}
	printf("%s\n", filename);
	return;
}

int main (int argc, char * argv[]){

	while(1){
		arg_in = getopt_long (argc, argv, "clw", long_opts, NULL);

		if (arg_in == -1){
			break;
		}
		switch(arg_in){
			case 'c':
				bytes_flag = true;
				break;
			case 'l':
				lines_flag = true;
				break;
			case 'w':
				words_flag = true;
				break;
			default:
				exit(1);
		}
	}
	
	if (bytes_flag | lines_flag | words_flag){
		if (optind < argc){
			while (optind < argc){
				int bytes_total = 0;
				int lines_total = 0;
				int words_total = 0;

				int * totals = counter(argv[optind], bytes_flag, words_flag, lines_flag);

				print_file_results(argv[optind], totals);
				optind++;
			}
		}
		else{
			printf("No files given\n");
			exit(1);
		}
	}
	else{
		printf("No parameters given.\n");
		exit(1);
	}
		exit(0);
}

