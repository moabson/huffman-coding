/*
 * bitwise_operations.c
 *
 *  Created on: 04/06/2015
 *      Author: eduardo
 */

#include "bitwise_operations.h"

int BitwiseOperations_setBit(int c, int i){

	int mask = 1 << i;
	return mask | c;
}
int BitwiseOperations_isBitISet(int c, int i){
    int mask = 1 << i;
    return mask & c;
}
