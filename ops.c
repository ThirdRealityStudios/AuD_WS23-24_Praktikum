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

void insertInternally(Node *node, int key)
{
    node -> key[node -> num_keys] = key;
    node -> num_keys++;

    sortKeys(node);
}

Node *newParent = NULL;

int splitIfNeeded(Node *node)
{
    newParent = node; // default if nothing happens inside this function.

    if(isNodeFull(node))
    {
        if(hasNoChildren(node))
        {
            Node *newLeftChild = createNode();
            Node *newRightChild = createNode();

            keysToNewChildren(newLeftChild, newRightChild, node);

            Node *parent = (node -> parent == NULL) ? node : node -> parent;

            newParent = parent;

            // Make sure not to overwrite existing children
            if(parent -> children[0] != NULL &&
               parent -> children[1] != NULL &&
               parent -> children[2] == NULL &&
               parent -> children[3] == NULL)
            {
                parent -> children[1] = newLeftChild;
                parent -> children[2] = newRightChild;
            }
            else
            {
                parent -> children[0] = newLeftChild;
                parent -> children[1] = newRightChild;
            }

            newLeftChild -> parent = parent;
            newRightChild -> parent = parent;

            int middleKey = node -> key[1];

            if(node != parent)
            {
                // Copy middle key up to parent
                insertInternally(parent, middleKey);
            }
            else // Otherwise clear everything because other keys than middleKey have been copied to their corresponding children
            {
                parent -> key[0] = 0;
                parent -> key[1] = 0;
                parent -> key[2] = 0;
                parent -> num_keys = 0;

                insertInternally(parent, middleKey);
            }

            return middleKey; // Middle key used to split
        }
    }

    return INT_MIN; // No split applied
}

Node* lastChild(Node *node)
{
    if(node -> children[0] != NULL &&
       node -> children[1] == NULL &&
       node -> children[2] == NULL &&
       node -> children[3] == NULL)
    {
        return node -> children[0];
    }

    if(node -> children[0] != NULL &&
       node -> children[1] != NULL &&
       node -> children[2] == NULL &&
       node -> children[3] == NULL)
    {
        return node -> children[1];
    }

    if(node -> children[0] != NULL &&
       node -> children[1] != NULL &&
       node -> children[2] != NULL &&
       node -> children[3] == NULL)
    {
        return node -> children[2];
    }

    if(node -> children[0] != NULL &&
       node -> children[1] != NULL &&
       node -> children[2] != NULL &&
       node -> children[3] != NULL)
    {
        return node -> children[3];
    }

    return NULL;
}

Node* findLeafForKey(Node *node, int key)
{
    if(hasNoChildren(node))
    {
        // Leaf found.
        return node;
    }

    if(key < node -> key[0])
    {
        // take left node
        return findLeafForKey(node -> children[0], key);
    }

    // take right node
    return findLeafForKey(lastChild(node), key);
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
            // if splitting up changed the node we want to continue looking at for insertion (old node does not exist anymore).
            if(node != newParent)
            {
                insertInternally(newParent -> children[0], key);
            }
            else
            {
                insertInternally(parent -> children[0], key);
            }
        }
        else
        {
            if(node != newParent)
            {
                insertInternally(lastChild(newParent), key);
            }
            else
            {
                insertInternally(lastChild(parent), key);
            }
        }
    }
    else // Normal insertion to the key array but first traverse to the required node
    {
        Node *leaf = findLeafForKey(node, key);

        if(isNodeFull(leaf))
            insertAtNode(leaf, key); // Splitting needed
        else
            insertInternally(leaf, key);
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