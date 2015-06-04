/*
 * bitwise_operations.c
 *
 *  Created on: 04/06/2015
 *      Author: eduardo
 */

#include "bitwise_operations.h"

int setBit(unsigned char c, int i){

	unsigned char mask = 1 << i;
	return mask | c;
}
int isBitISet(int c, int i){
    int mask = 1 << i;
    return mask & c;
}
