#include "binary_trees.h"
#define POW2(x) (1 << (x))

heap_t *heap_append(heap_t *root, int value);
int count_nodes(heap_t *root);
void index_to_lvl_pos(int index, int *level, int *position);
void swap(int *a, int *b);

/**
 * heap_insert - insert value into a Max Binary Heap
 * @root: a reference of a pointer to the root of the Heap
 * @value: the value to store in the node to be inserted
 *
 * Description: If the root is NULL. The created node becoma the root
 * The program respect the Max Heap
 * Return: a pointer to inserted node or NULL of failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *runner = *root;

	if (*root == NULL)
	{
		*root = binary_tree_node(*root, value);
		return (*root);
	}

	runner = heap_append(*root, value);

	while (runner->parent && runner->parent->n < runner->n)
	{
		swap(&(runner->n), &(runner->parent->n));
		runner = runner->parent;
	}

	return (runner);
}

/**
 * heap_append - insert node at the end of the heap (a complete binary tree)
 * @root: reference to pointer of the root of the binary tree
 * @value: value of node (int)
 * Return: a pointer to the new node
 */
heap_t *heap_append(heap_t *root, int value)
{
	int level, r_pos, size;
	heap_t *runner = root;


	size = count_nodes(runner);
	index_to_lvl_pos(size, &level, &r_pos);
	/* printf("counter=%d, level=%d, pos=%d\n", size, level, r_pos); */

	while (level > 1)
	{
		if (((r_pos >> (level - 1)) & 1) == 1)
			runner = runner->right;
		else
			runner = runner->left;
		level--;
	}
	if ((r_pos & 1) == 1)
	{
		runner->right = binary_tree_node(runner, value);
		runner = runner->right;
	}
	else
	{
		runner->left = binary_tree_node(runner, value);
		runner = runner->left;
	}

	return (runner);
}

/**
 * count_nodes - count number of nodes
 * @root: pointer to root of tree
 * Return: number of nodes
 */
int count_nodes(heap_t *root)
{

	if (root == NULL)
		return (0);
	return (1 + count_nodes(root->left) + count_nodes(root->right));
}

/**
 * index_to_lvl_pos - convert index to level and position in a complete binary
 * @index: the index in the equivalent array of the heap
 * @level: an int reference for the level (every level is a new child)
 * @position: an int reference for the relative position in the level
 *
 * Example:
 *   |         index         Level   position (in the Level)
 *   |           0             0               0
 *   |       1       2         1           0       1
 *   |     3   4   5   6       2         0   1   2   3
 *   |    7 8 9 A B C D E      3        0 1 2 3 4 5 6 7
 *
 * offset = 2^level - 1
 * level:  0, 1, 2, 3,  4,  5
 * offset: 0, 1, 3, 7, 15, 32
 */
void index_to_lvl_pos(int index, int *level, int *position)
{
	int offset;

	*level = 0;
	while (POW2(*level + 1) - 1 <= index)
	{
		(*level)++;
	}

	offset = (POW2(*level)) - 1;
	*position = index - offset;
}

/**
 * swap - swap 2 variables
 * @a: a reference to the value
 * @b: a reference to the value
 */
void swap(int *a, int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}
