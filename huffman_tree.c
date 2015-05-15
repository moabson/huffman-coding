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

	for(i = 0; i < MAX; i++) {
		emptyHuffmanTree->table[i] = NULL;
	}

	return emptyHuffmanTree;
}

HuffmanTree* HuffmanTree_build(FrequencyQueue *frequencyQueue) {
	HuffmanTree *huffmanTree = HuffmanTree_createEmpty();

	if(!FrequencyQueue_isEmpty(frequencyQueue)) {
		LOG_INFO("building HuffmanTree");

		while(frequencyQueue->length > 1) {
			HuffmanNode *left = FrequencyQueue_get(frequencyQueue);
			HuffmanNode *right = FrequencyQueue_get(frequencyQueue);

			HuffmanNode *newHuffmanNode = HuffmanNode_createNode(NULL_CHAR,
					(left->frequency + right->frequency), left, right);

			FrequencyQueue_insert(frequencyQueue, newHuffmanNode,
					newHuffmanNode->frequency);
		}

		if((frequencyQueue->length == 1) && (frequencyQueue->first != NULL)) {
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

int HuffmanTree_isEmpty(HuffmanTree *huffmanTree) {
	return (huffmanTree->root == NULL);
}

void HuffmanTree_fillTable(HuffmanTree *huffmanTree) {
	LOG_INFO("loading HuffmanTree code table")

	if(!HuffmanTree_isEmpty(huffmanTree)) {
		LinkedList *linkedList = LinkedList_createEmpty();

		HuffmanTree_catchCode(huffmanTree, huffmanTree->root, linkedList);
	} else {
		LOG_ERR("failed on load code table: HuffmanTree is empty");
	}
}

void HuffmanTree_catchCode(HuffmanTree *huffmanTree, HuffmanNode *root, LinkedList *linkedList) {
	if(!HuffmanNode_isLeaf(root)) {
		LinkedList_insert(linkedList, '0');
		HuffmanTree_catchCode(huffmanTree, root->left, linkedList);
		LinkedList_deleteFirst(linkedList);

		LinkedList_insert(linkedList, '1');
		HuffmanTree_catchCode(huffmanTree, root->right, linkedList);
		LinkedList_deleteFirst(linkedList);
	} else {
		char *code = (char *) malloc(sizeof(char) * (linkedList->length + 1));
		Node *aux = linkedList->first;
		int i;

		code[linkedList->length] = '\0';
		i = linkedList->length - 1;

		while(aux != NULL) {
			code[i] = aux->bit;

			aux = aux->nextNode;
			i--;
		}

		huffmanTree->table[root->character] = code;
	}
}

void HuffmanTree_printTable(HuffmanTree *huffmanTree) {
	LOG_INFO("priting HuffmanTree code table")

	int i;

	for(i = 0; i < MAX; i++) {
		if(huffmanTree->table[i] != NULL) {
			printf("~ [%d | %s | %d bit(s)]\n", i, huffmanTree->table[i], (int) strlen(huffmanTree->table[i]));
		}
	}
}
