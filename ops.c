#include "ops.h"

Node *createNode()
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->num_keys = 0;
    newNode->parent = NULL;

    for(int i = 0; i < 5; i++)
    {
        newNode->children[i] = NULL;
    }

    for(int i = 0; i < 4; i++)
    {
        newNode->key[i] = (int) NULL;
    }

    return newNode;
}

int is4Node(Node* node)
{
    return node -> num_keys == 3
           && node -> children[0] != NULL
           && node -> children[1] != NULL
           && node -> children[2] != NULL
           && node -> children[3] != NULL;
}

/// @brief Splittet den Knoten auf in zwei, da 4 Schlüssel.
/// @brief Teilt einen Knoten auf in zwei,
///        damit jeder nur maximal 3 Schlüssel enthält.
///        Geht dann rekursiv nach oben im Baum und wiederholt dies
///        für alle weiteren Knoten,
///        wo dies zutrifft.
void split(Node* node)
{
    Node *newLeftNode = createNode();

    newLeftNode -> key[0] = node -> key[0];
    newLeftNode -> num_keys++;
    newLeftNode -> children[0] = node -> children[0];
    newLeftNode -> children[1] = node -> children[1];

    Node *newRightNode = createNode();

    newRightNode -> key[0] = node -> key[1];
    newRightNode -> num_keys++;
    newRightNode -> children[0] = node -> children[2];
    newRightNode -> children[1] = node -> children[3];

    node -> key[0] = node -> key[2]; // mittleren Schlüssel nehmen
    node -> num_keys = 1;
    node -> children[0] = newLeftNode;
    node -> children[1] = newRightNode;
    node -> children[2] = NULL;
    node -> children[3] = NULL;
}

//Schlüssel in einem Knoten einfügen
void insertKey(Node *node, int key)
{
    //i = indexposition des letzten vorhandenen Schlüssels im Knoten
    int i = node->num_keys - 1;

    //durchlaufe Knoten rückwärts und vergleicht einzufügenden Schlüssel mit vorhandenen Schlüssel
    while (i >= 0 && node->key[i] > key)
    {
        //Schiebe aktuellen schlüssel ein nach rechts, um platz für neuen Schlüssel zu machen
        node->key[i + 1] = node->key[i];
        i--;
    }

    //Setze neuen Schlüssel an richtiger Stelle
    node->key[i + 1] = key;
    node->num_keys++;
}

/// @brief Teilt einen Knoten auf in zwei,
///        damit jeder nur maximal 3 Schlüssel enthält.
///        Geht dann rekursiv nach oben im Baum und wiederholt dies
///        für alle weiteren Knoten,
///        wo dies zutrifft.
void splitNode(Node *node, Node **root) {
    // Erstellen neuer Knoten für die rechte Hälfte
    Node *newNode = createNode();
    newNode->key[0] = node->key[2];
    newNode->key[1] = node->key[3];
    newNode->num_keys = 2;

    // Kopieren der rechten Hälfte der Kinder, falls vorhanden
    if (node->children[2] != NULL && node->children[3] != NULL) {
        newNode->children[0] = node->children[2];
        newNode->children[1] = node->children[3];
        newNode->children[2] = node->children[4];
        newNode->children[0]->parent = newNode;
        newNode->children[1]->parent = newNode;
        newNode->children[2]->parent = newNode;
    }

    // Neuen linken Knoten erstellen
    Node *newLeftNode = createNode();
    newLeftNode->key[0] = node->key[0];
    newLeftNode->num_keys = 1;

    if(node->children[0] != NULL && node->children[1] != NULL) {
        newLeftNode->children[0] = node->children[0];
        newLeftNode->children[1] = node->children[1];
        newLeftNode->children[0]->parent = newLeftNode;
        newLeftNode->children[1]->parent = newLeftNode;
    }

    // Ursprungsknoten reduzieren
    node->num_keys = 1;

    // Wenn der Knoten keinen Elternknoten hat (Wurzel)
    if (node->parent == NULL) {
        // Neuen Elternknoten für die aufgeteilten Knoten erstellen
        Node *newRoot = createNode();
        insertKey(newRoot, node->key[1]); // Einfügen des mittleren Schlüssels als Wurzel

        // Platzieren der neuen Kinder im neuen Wurzelknoten
        newRoot->children[0] = newLeftNode;
        newRoot->children[1] = newNode;
        newLeftNode->parent = newRoot;
        newNode->parent = newRoot;

        *root = newRoot; // Aktualisieren der Wurzel
    } else {
        Node *parent = node->parent;
        int middleKey = node->key[1];

        insertKey(parent, middleKey);

        int i = parent->num_keys - 1;
        while (i >= 0 && parent->key[i] > middleKey) {
            parent->children[i + 1] = parent->children[i];
            i--;
        }

        parent->children[i + 1] = newNode;
        newNode->parent = parent;
        parent->children[i] = newLeftNode;
        newLeftNode->parent = parent;

        // Falls Elternknoten ebenfalls ein 4-Knoten ist, wird er auch aufgeteilt
        if (parent->num_keys > 3) {
            splitNode(parent, root);
        }
    }
}


/// @brief Fügt einen Schlüssel in den 2-3-4-Baum ein
///        und führt bei Bedarf auch eine Aufteilung (Split) durch,
///        um die Baumstruktur aufrechtzuerhalten.
/// @param root Baum-Wurzel
/// @param key Schlüssel zum Einfügen
void insert2(Node **root, int key)
{
    Node *current = *root;

    while(1)
    {
        //wenn knoten = blattknoten
        if(current->children[0] == NULL)
        {

            insertKey(current, key);

            //check ob knoten mehr als 3 key hat
            if(current->num_keys > 3)
            {
                //teile Knoten auf
                split(current);
            }

            break;
        }
        else
        {
            //wenn knoten kein Blattknoten, gehe in passenden Kindknoten runter
            //wenn current_key kleiner als key, gehe in Kindknoten + 1
            int i = current->num_keys - 1;

            while(i >= 0 && key < current->key[i])
            {
                i--;
            }

            current = current->children[i + 1];
        }
    }
}

int maxDepth(struct Node* root)
{
    if (root == NULL)
        return 0;

    //Wir nehmen an, dass der Baum ausgeglichen ist
    if (root->children[0] != NULL)
        return maxDepth(root->children[0]) + 1;//+1 für jede level tiefe des baumes
    else
        return 1;//Blattnode
}

/// @brief Zählt alle Knoten im 234-Baum
/// @param root Baum-Wurzel
int countNodes(struct Node* root)
{
    if (root == NULL)
        return 0;

    int count = 1; //current node

    for (int i = 0; i < root->num_keys + 1; i++)
    {
        count += countNodes(root->children[i]);
    }

    return count;
}