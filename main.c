#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_manager.h"

#define MAX 256

int main(int argc, char *argv[]) {
	int compress = 0;
	int decompress = 0;
	char filePath[MAX];

	if(argc == 3) {
		if(strcmp(argv[1], "-c") == 0) {
			compress = 1;
		} else if(strcmp(argv[1], "-d") == 0) {
			decompress = 1;
		}

		strncpy(filePath, argv[2], MAX);
	}

	if(compress) {
		FileManager_compressFile(filePath);
	} else if(decompress) {
		printf("Descomprimir arquivo %s\n", filePath);
		FileManager_decompressFile(filePath);
	} else {
		// usage
	}

	return 0;
}
