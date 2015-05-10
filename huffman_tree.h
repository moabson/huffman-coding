/*
 * huffman_tree.h
 *
 */

#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include "frequency_queue.h"
#include "huffman_node.h"
#include "debug.h"

typedef struct huffmanTree HuffmanTree;

struct huffmanTree {
	HuffmanNode *root;
};

HuffmanTree* HuffmanTree_createEmpty();

HuffmanTree* HuffmanTree_build();

#endif /* HUFFMAN_TREE_H_ */
