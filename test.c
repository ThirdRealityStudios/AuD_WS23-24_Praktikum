//
// Created by lukas on 17.12.2023.
//
/*
if (*root == NULL) {
*root = initNode();
insertKey(*root, key);
} else {
Node *current = *root;

while (1) {
if (current->num_keys == 3 && current->children[0] == NULL) {
insertKey(current, key);
splitNode(current, root);
break;
} else if (current->num_keys == 3 && current->children[0] != NULL) {
int i = current->num_keys - 1;
while (i >= 0 && key < current->key[i]) {
i--;
}
current = current->children[i + 1];
} else {
//Aktueller Knoten ist ein 2-Knoten oder noch nicht voller 4-Knoten
int i = current->num_keys - 1;
if (current->children[0] == NULL) {
// Der aktuelle Knoten ist ein Blattknoten
insertKey(current, key);
break;
} else {
while (i >= 0 && key < current->key[i]) {
i--;
}
if (current->children[i + 1]->num_keys == 3) {
// Der Kindknoten, in den wir absteigen wollen, ist ein voller 4-Knoten
current = current->children[i + 1];
} else {
// Der Kindknoten, in den wir absteigen wollen, ist noch nicht voller 4-Knoten
current = current->children[i + 1];
break;
}
}
}
}
}
 **/