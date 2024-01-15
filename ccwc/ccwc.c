#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <limits.h>

bool bytes_flag,lines_flag, words_flag;
int arg_in;
static struct option long_opts [] = {
	{"bytes", no_argument, 0, 'c'},
	{"lines", no_argument, 0, 'l'},
	{0,0,0,0}
};

int count_bytes(const char *filename){
	FILE * file_stream;
	int byte_count = 0;

	file_stream = fopen(filename, "r");
	
	if (file_stream == NULL){
		printf("File could not be opened.\n");
	}
	else{
		while (getc(file_stream) != EOF){
			byte_count ++;
		}
		fclose(file_stream);
	}
	return byte_count;
}

int count_lines(const char *filename){
	FILE * file_stream;
	char * line_buffer;
	size_t line_size = LINE_MAX;
	int line_count = 0;

	file_stream = fopen(filename, "r");

	if (file_stream == NULL) {
		printf("File count not be opened.\n");
	}
	else{
		line_buffer = (char *)malloc(line_size);
		while (getline(&line_buffer, &line_size, file_stream) != EOF){
			line_count++;
		}
		fclose(file_stream);
	}
	return line_count;
}

void print_file_results(const int bytes, const int lines, const int  words, const char *filename){
	if (lines != 0) { 
		printf("%d ", lines);
	}
	if (words != 0) {
		printf("%d ", words);
	}
	if (bytes != 0) {
		printf("%d ", bytes);
	}
	printf("%s\n", filename);
	return;
}

int main (int argc, char * argv[]){

	while(1){
		arg_in = getopt_long (argc, argv, "cl", long_opts, NULL);

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

				if ( bytes_flag ){
					bytes_total = count_bytes(argv[optind]);
				}
				if (lines_flag){
					lines_total = count_lines(argv[optind]);
				}
				if (words_flag){
					break;
				}

				print_file_results(bytes_total, lines_total, words_total, argv[optind]);
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

