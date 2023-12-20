#include "ops.h"

void printTree(Node *root, int level)
{
    if (root != NULL)
    {
        int i;

        for (i = 0; i < root->num_keys; i++)
        {
            printTree(root->children[i], level + 1);
            printf("Level %d: %d\n", level, root->key[i]);
        }

        printTree(root->children[i], level + 1);
    }
}

void insert500Random(struct Node** root)
{
    srand(time(NULL));

    for (int i = 0; i < 500; ++i)
    {
        int random_num = rand() % 500;

        insert(root, random_num);
    }
}


void inOrderTraversal(struct Node* root)
{
    if (root == NULL)
        return;

    int i;

    for (i = 0; i < root->num_keys; i++)
    {
        inOrderTraversal(root->children[i]);

        printf("%d ", root->key[i]);
    }

    inOrderTraversal(root->children[i]);
}

void print2_3_4_tree(struct Node* root, int depth)
{
    if (root == NULL)
        return;

    int i;

    for (i = 0; i < root->num_keys; i++)
    {
        print2_3_4_tree(root->children[i], depth + 1);

        for (int j = 0; j < depth; j++)
            printf("\t");

        printf("%d\n", root->key[i]);
    }

    print2_3_4_tree(root->children[i], depth + 1);
}

int searchKey(struct Node* root, int target, int* comparisons)
{
    *comparisons += 1;

    if (root == NULL)
        return 0;

    //überprüfe in current node ob einer der key = target
    int i = 0;
    while (i < root->num_keys && target > root->key[i])
        i++;

    if (i < root->num_keys && target == root->key[i])
        return 1; // Key found

    //wenn target nicht gefunden, überprüfe ob children nodes existieren und gehe in diese rein. Function wird erneut aufgerufen (rekursion)
    if (root->children[i] != NULL)
        return searchKey(root->children[i], target, comparisons);

    return 0; // Key not found
}

void print234Tree(Node *root)
{

}

int main()
{
    Node *root = createNode();

    // insert500Random(&root);

    insert(&root, 3);
    insert(&root, 1);
    insert(&root, 5);
    insert(&root, 4);

    /*
    insert(&root, 2);
    insert(&root, 9);
    insert(&root, 10);
    insert(&root, 8);
    insert(&root, 7);
    insert(&root, 6);
     */

    // print2_3_4_tree(root, 1);

    // print2_3_4_tree(root, 1);

    /*
    puts("");
    puts("");

    inOrderTraversal(root);

    puts("");
    puts("");

    int depth = maxDepth(root);
    int nodes = countNodes(root);
    printf("Tiefe des Baumes: %d\n", depth);
    printf("Anzahl der Nodes im Baum: %d\n", nodes);

    puts("");
    puts("");

    int target = (int) NULL;

    do
    {
        int comparisons = 0;

        printf("Gebe die zu suchende Zahl ein: (0-500) (600 um Programm zu beenden)\n");
        scanf("%d", &target);

        int found = searchKey(root, target, &comparisons);

        if (found) {
            printf("Key %d found after %d comparisons.\n", target, comparisons);
            puts("");
            puts("");
        } else {
            printf("Key %d not found after %d comparisons.\n", target, comparisons);
            puts("");
            puts("");
        }
    }
    while(target != 600);
     */

    return 0;
}
