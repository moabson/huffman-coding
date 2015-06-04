/*
 * huffman_tree.h
 *
 */

#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequency_queue.h"
#include "huffman_node.h"
#include "debug.h"
#include "linked_list.h"

#define MAX 256

typedef struct huffmanTree HuffmanTree;

struct huffmanTree {
	HuffmanNode *root;
	char *table[MAX];
	int number_nodes;
};

/*
*Cria a arvore de Huffman vazia, com ponteiros apontando para VAZIO.
*@Retorna ponteiro para a arvore emptyHuffmantree.
*/
HuffmanTree* HuffmanTree_createEmpty();

/*
*Gera a arvore de Huffman a partir da fila de frequencia.
*@Recebe o ponteiro para a fila frequencyQueue.
*@Retorna o ponteiro huffmanTree.
*/
HuffmanTree* HuffmanTree_build(FrequencyQueue *frequencyQueue);

/*
*Verifica se a arvore de Huffman está vazia.
*@Recebe o ponteiro para a arvore huffmanTree.
*@Retorna TRUE e estiver vazia e FALSE caso o contrario.
*/
int HuffmanTree_isEmpty(HuffmanTree *huffmanTree);

/*
*Gera a tabela de codigo da arvore de Huffman.
*@Recebe o ponteiro para a arvore huffmanTree.
*/
void HuffmanTree_fillTable(HuffmanTree *huffmanTree);

/*
*Gera o codigo para cada caractere da arvore.
*@Recebe o ponteiro para a arvore huffmanTree, o ponteiro para o nó root e o ponteiro para a lista linkedList.
*/
void HuffmanTree_catchCode(HuffmanTree *huffmanTree, HuffmanNode *root, LinkedList *linkedList);

/*
*Imprime a tabela de codigo da arvore.
*@Recebe o ponteiro para a arvore huffmanTree.
*/
void HuffmanTree_printTable(HuffmanTree *huffmanTree);

void Write_Tree(HuffmanNode * root,FILE * file);

#endif /* HUFFMAN_TREE_H_ */
