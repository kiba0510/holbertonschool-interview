#include "binary_trees.h"

/**
 * free_queue - free the allocated memory for our queue
 * @q: pointer to queue
 *
 * Return: nothing
 **/
void free_queue(que **q)
{
    que *temp = *q;

    *q = (*q)->next;
    free(temp);
}

/**
 * to_queue - allocating memory and pushing nodes into our queue struct
 * @qu: pointer to queue
 * @q_node: pointer to a node
 *
 * Return: pointer to a node added to our queue
 **/
que *to_queue(que **qu, heap_t *q_node)
{
    que *new;
    que *current;

    new = malloc(sizeof(que));
    if (!new)
    {
        return (NULL);
    }
    new->node = q_node;
    new->next = NULL;
    current = *qu;

    if (!*qu)
    {
        *qu = new;
        return (new);
    }

    while (current->next)
        current = current->next;
    current->next = new;
    return (new);
}

/**
 * add_node_to_tree - adding a new node to the and of our heap
 * @root: pointer to the head of the heap
 * @value: value to to_queue in node
 *
 * Return: a pointer to a new node
 **/
heap_t *add_node_to_tree(heap_t **root, int value)
{
    que *qu = NULL;
    heap_t *curr;
    heap_t *new = NULL;

    if (!to_queue(&qu, *root))
        return (NULL);
    while (qu)
    {
        curr = qu->node;
        if (curr->left)
        {
            if (!to_queue(&qu, curr->left))
                return (NULL);
        }
        else if (!new)
        {
            new = binary_tree_node(curr, value);
            curr->left = new;
            if (!new)
                return (NULL);
        }
        if (curr->right)
        {
            if (!to_queue(&qu, curr->right))
                return (NULL);
        }
        else if (!new)
        {
            new = binary_tree_node(curr, value);
            curr->right = new;
            if (!new)
                return (NULL);
        }
        free_queue(&qu);
    }
    return (new);
}

/**
 * swap - checking for the right position to to_queue the value
 * @new: pointer to the new node with the value
 *
 * Return: pointer to the nide with the swaped value
 **/
heap_t *swap(heap_t *new)
{
    int temp = 0;
    heap_t *t_node = new;

    while (t_node->parent)
    {
        if (t_node->n > t_node->parent->n)
        {
            temp = t_node->n;
            t_node->n = t_node->parent->n;
            t_node->parent->n = temp;
            new = new->parent;
        }
        t_node = t_node->parent;
    }
    return (new);
}
/**
* heap_insert - to_queues a value into a Max Binary Heap
* @root: pointyer to a root node
* @value: value to to_queue
*
* Return: pointer to a node or NULL
**/
heap_t *heap_insert(heap_t **root, int value)
{
    heap_t *node;

    if (!root)
    {
        return (NULL);
    }
    if (!*root)
    {
        return (*root = binary_tree_node(NULL, value));
    }
    node = add_node_to_tree(root, value);
    return (swap(node));
}