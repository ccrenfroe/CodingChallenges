#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

int arg_in;
static struct option long_opts [] = {
	{"bytes", no_argument, 0, 'c'},
	{"lines", no_argument, 0, 'l'},
	{0,0,0,0}
};

int bytes_flag=0;
int lines_flag=0;

int count_bytes(const char *filename){
	FILE * file_stream;
	int byte_count = 0;

	file_stream = fopen(filename, "r");
	
	if (file_stream == NULL){
		printf("File could not be opened.\n");
	}
	else{
		printf("starting byte count : %d\n", byte_count);
		while (getc(file_stream) != EOF){
			byte_count ++;
		}
		fclose(file_stream);
	}
	return byte_count;
}

int main (int argc, char * argv[]) {

	while(1){
		arg_in = getopt_long (argc, argv, "cl", long_opts, NULL);

		if (arg_in == -1){
			break;
		}
		switch(arg_in){
			case 'c':
				printf("Byte count\n");
				break;
			case 'l':
				printf("Line count\n");
				break;
			default:
				abort();
		}
	}

	if (optind < argc){
		while (optind < argc){
			printf ("non-option argv-elements: %s\n", argv[optind++]);
		}
	}
	else {
		printf("No files given\n");
		exit(1);
	}

	exit(0);
}

/*
	*    else {
	*        for ( int i = 0; i < argc; i++)
	*        {
	*            //printf("%s\n", argv[i]);
	*            if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--count") == 0){
	*                if (argv[i+1])
	*                {
	*                    char * filename = argv[i+1];
	*                    int total_bytes = count_bytes(filename);
	*                    printf("%d bytes\n", total_bytes);
	*                }
	*                else{
	*                    printf("please provide a file.\n");
	*                    return 0;
	*                }
	*            }
	*        }
	*
	*/

