#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef AUD_WS23_24_PRAKTIKUM_OPS_H
#define AUD_WS23_24_PRAKTIKUM_OPS_H

//Struktur für 2-3-4-Baum Knoten
typedef struct Node
{
    int key[4]; //Array für die Schlüsselwerte (eigentlich 3 aber da ich bevor ich die node splitte noch den neuen key dranhänge 4)
    struct Node *children[5]; //Array für die Kinderknoten (eigentlich 4 aber aus dem oben genannten Grund hier + 1 also 5)
    int num_keys; //Anzahl der aktuellen Schlüssel
    struct Node *parent;
} Node;

Node* createNode();
void insert(Node **root, int key);
void insertAtNode(Node *node, int key);
int splitIfNeeded(Node *node);
int hasNoChildren(Node *node);
void keysToNewChildren(Node *newLeftChild, Node *newRightChild, Node *parentNode);
void sortKeys(Node *node);
int isNodeFull(Node *node);
int maxDepth(struct Node* root);
int countNodes(struct Node* root);
#endif
