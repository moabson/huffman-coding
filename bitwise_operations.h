/*
 * bitwise_operations.h
 *
 *  Created on: 04/06/2015
 *      Author: eduardo
 */

#ifndef BITWISE_OPERATIONS_H_
#define BITWISE_OPERATIONS_H_

/**
 * Muda o bit i do caractere para 1.
 *
 * @param character - caractere cujo os bits serão verificados.
 * @param position - indica a posição do bit que será modificado.
 * @return um inteiro que representa um novo character.
 *
 */
int BitwiseOperations_setBit(int character, int position);

/**
 * Verifica se o bit i do inteiro passado é 1.
 *
 * @param character - caractere cujo o bit será verificados.
 * @param position - indica a posição do caractere no qual o bit será verificado.
 * @return retorna 0 (false) se o bit não estiver setado ou um número maior que 0 caso contrário.
 *
 */
int BitwiseOperations_isBitISet(int character, int position);


#endif /* BITWISE_OPERATIONS_H_ */
