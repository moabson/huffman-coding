/*
 * bitwise_operations.h
 *
 *  Created on: 04/06/2015
 *      Author: eduardo
 */

#ifndef BITWISE_OPERATIONS_H_
#define BITWISE_OPERATIONS_H_

/**
 * Muda o bite i do caracter para 1
 *
 * @param unsigned char - caracter cujos bits serão verificados
 * @param int - indica a posição do bit que será modificado
 * @return um inteiro que representa o novo caracter
 */
int BitwiseOperations_setBit(int c, int i);

/**
 * Verifica se o bit i do inteiro passado é 1
 *
 * @param int - inteiro cujos bits serão verificados
 * @param int - posição do bit que será verificado
 */
int BitwiseOperations_isBitISet(int c, int i);


#endif /* BITWISE_OPERATIONS_H_ */
