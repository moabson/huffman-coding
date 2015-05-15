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
};

HuffmanTree* HuffmanTree_createEmpty();

HuffmanTree* HuffmanTree_build();

int HuffmanTree_isEmpty(HuffmanTree *huffmanTree);

void HuffmanTree_fillTable(HuffmanTree *huffmanTree);

void HuffmanTree_catchCode(HuffmanTree *huffmanTree, HuffmanNode *root, LinkedList *linkedList);

void HuffmanTree_printTable(HuffmanTree *huffmanTree);

#endif /* HUFFMAN_TREE_H_ */
