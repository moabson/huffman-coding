/*
 * bitwise_operations.c
 *
 *  Created on: 04/06/2015
 *      Author: eduardo
 */

#include "bitwise_operations.h"

int BitwiseOperations_setBit(int character, int position){
	int mask = 1 << position;
	return mask | character;
}

int BitwiseOperations_isBitISet(int character, int position){
    int mask = 1 << position;
    return mask & character;
}
