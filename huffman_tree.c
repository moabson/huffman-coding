/*
 * huffman_tree.c
 *
 */

#include "huffman_tree.h"

#define NULL_CHAR 0

HuffmanTree* HuffmanTree_createEmpty() {
	HuffmanTree *emptyHuffmanTree = (HuffmanTree *) malloc(sizeof(HuffmanTree));
	int i;

	emptyHuffmanTree->root = NULL;
	for (i = 0; i < 246; i++) {
		emptyHuffmanTree->table[i] = NULL;
	}
	return emptyHuffmanTree;
}

HuffmanTree* HuffmanTree_build(FrequencyQueue *frequencyQueue) {
	HuffmanTree *huffmanTree = HuffmanTree_createEmpty();

	if (!FrequencyQueue_isEmpty(frequencyQueue)) {
		LOG_INFO("building HuffmanTree");

		while (frequencyQueue->length > 1) {
			HuffmanNode *left = FrequencyQueue_get(frequencyQueue);
			HuffmanNode *right = FrequencyQueue_get(frequencyQueue);

			HuffmanNode *newHuffmanNode = HuffmanNode_createNode(NULL_CHAR,
					(left->frequency + right->frequency), left, right);

			FrequencyQueue_insert(frequencyQueue, newHuffmanNode,
					newHuffmanNode->frequency);
		}

		if ((frequencyQueue->length == 1) && (frequencyQueue->first != NULL)) {
			huffmanTree->root = FrequencyQueue_get(frequencyQueue);

			LOG_INFO("HuffmanTree successfully created")
		} else {
			LOG_ERR("failed in building the HuffmanTree: FrequencyQueue length")
		}
	} else {
		LOG_ERR("failed in building the HuffmanTree: FrequencyQueue is empty")
	}

	return huffmanTree;
}

void Catch_code(HuffmanTree* tree, HuffmanNode * root, List * list,
		int size_list) {

	if (!HuffmanNode_isLeaf(root)) {

		list = insert(list, '0');
		Catch_code(tree, root->left, list, size_list + 1);
		list = delete(list);
		list = insert(list, '1');
		Catch_code(tree, root->right, list, size_list + 1);
		list = delete(root);
	} else {

		char * code = (char*) malloc((size_list + 1) * sizeof(char));
		List * aux = list;
		int i;

		code[size_list] = '\0';
		i = size_list - 1;
		while (aux != NULL) {
			code[i] = aux->bit;
			aux = aux->next;
			i--;
		}
		tree->table[root->character] = code;
	}

}

void print_table(HuffmanTree* tree) {
	int i;
	for (i = 0; i < 256; i++) {
		if (tree->table[i] != NULL)
			printf("%d %s\n", i, tree->table[i]);

	}
}
