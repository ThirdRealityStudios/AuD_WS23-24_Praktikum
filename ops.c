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

int isNodeFull(Node *node)
{
    return node -> num_keys == 3;
}

/// @brief Sorts keys of a node
void sortKeys(Node *node)
{
    int keyListLength = node -> num_keys;
    int *keys = node -> key;

    for(int rounds = 0; rounds < keyListLength && keyListLength > 1; rounds++)
    {
        for(int index = 0; index < (keyListLength - 1); index++)
        {
            // Swap the values if one is bigger.
            if(keys[index] > keys[index + 1])
            {
                int temp = keys[index + 1];

                keys[index + 1] = keys[index];

                keys[index] = temp;
            }
        }
    }
}

/// @brief Make sure it is a 4-Node node, so with 3 keys!
void keysToNewChildren(Node *newLeftChild, Node *newRightChild, Node *parentNode)
{
    int middleKey = parentNode -> key[1];

    for(int i = 0; i < parentNode -> num_keys; i++)
    {
        // Skip middle key
        if(i == 1)
        {
            continue;
        }

        int insertableKey = parentNode -> key[i];

        if(insertableKey < middleKey)
        {
            newLeftChild -> key[newLeftChild -> num_keys] = insertableKey;
            newLeftChild -> num_keys++;
        }
        else
        {
            newRightChild -> key[newRightChild -> num_keys] = insertableKey;
            newRightChild -> num_keys++;
        }
    }

    sortKeys(newLeftChild);
    sortKeys(newRightChild);
}

int hasNoChildren(Node *node)
{
    return    node -> children[0] == NULL
              && node -> children[1] == NULL
              && node -> children[2] == NULL
              && node -> children[3] == NULL;
}

int splitIfNeeded(Node *node)
{
    if(isNodeFull(node))
    {
        Node *parent = node;

        if(hasNoChildren(parent))
        {
            Node *newLeftChild = createNode();
            Node *newRightChild = createNode();

            keysToNewChildren(newLeftChild, newRightChild, parent);

            parent -> children[0] = newLeftChild;
            parent -> children[1] = newRightChild;

            newLeftChild -> parent = parent;
            newRightChild -> parent = parent;

            // Delete children keys from parent
            parent -> key[0] = parent -> key[1]; // middle key on first place now
            parent -> key[1] = 0;
            parent -> key[2] = 0;
            parent -> key[3] = 0;
            parent -> num_keys = 1;

            return parent -> key[0]; // Middle key used to split
        }
    }

    return INT_MIN; // No split applied
}

void insertInternally(Node *node, int key)
{
    node -> key[node -> num_keys] = key;
    node -> num_keys++;

    sortKeys(node);
}

void insertAtNode(Node *node, int key)
{
    int splitValue = INT_MIN;

    splitValue = splitIfNeeded(node);

    if(splitValue > INT_MIN) // it was splitted
    {
        // Now the "node" can be regarded as the "parent"
        // because split will make "node" the highest node.
        Node *parent = node;

        if(key < splitValue)
        {
            insertInternally(parent -> children[0], key);
        }
        else
        {
            insertInternally(parent -> children[1], key);
        }
    }
    else // Normal insertion to the key array
    {
        insertInternally(node, key);
    }
}

void insert(Node **root, int key)
{
    insertAtNode(*root, key);
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