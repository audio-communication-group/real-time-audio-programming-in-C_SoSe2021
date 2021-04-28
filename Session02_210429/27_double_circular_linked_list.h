
/*************************************************************/
/**
 *  @header 28_double_circular_linked_list.h
 *  @brief Prototypes of data types and declarations of the functions
 *  @author Markus Hädrich, markus.haedrich@tu-berlin.de
 *
 *  @discussion Course: Real-Time Audio Programing in C\n
 *  Supervisors: Thomas Resch, Markus Hädrich, (TU-Berlin) \n
 *  This is one possible solution for the \n
 *  homework about linked lists.
 *
 *
 *  @date 30.04.19. – first implementation
 *
 *  @todo write more functions (e. g. @c sum() or @c mult() all elements)
 *
 *  @bug please report any bug
 *
 *  @version 0.1.1
 *************************************************************/





#ifndef _27_double_circular_linked_list_h
#define _27_double_circular_linked_list_h



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Prototypes

/**
 * @typedef struct Node with data element and two struct Node pointers.
 * @brief Node of a circular doubly linked list
 * @discussion A typedef of a node of a circular doubly linked list.
 */
typedef struct Node {
    int data;               /**< Node variable data. */
    struct Node* next;      /**< Node pointer to next node. */
    struct Node* prev;      /**< Node pointer to previous node. */
} node_t;

/**
 * Typedef of a pointer to a node_t.
 * @typedef pointer of type *node_t.
 */
typedef node_t *p_node_t;

/**
 * @brief Function to insert a new node at given index.
 * @param head_ref pointer to the head node pointer.
 * @param index position in the node chain.
 * @param data data of the new node.
 * @return p_node_t pointer to the head node.
 */
p_node_t insert_node_at_index(p_node_t *head_ref, unsigned int index, int data);

/**
 * @brief Function to insert a new node after node with given data.
 * @param head_ref pointer to the head node pointer.
 * @param prev_data data of the previous node.
 * @param data data of the new node.
 * @return p_node_t pointer to the head node.
 */
p_node_t insert_new_node_after_node(p_node_t *head_ref, int prev_data, int data);

/**
 * @brief Function to delete a node at a given index.
 * @param head_ref pointer to the head node pointer.
 * @param index index of the node to delete.
 * @return p_node_t pointer to the head node.
 */
p_node_t delete_node_at_index(p_node_t *head_ref, unsigned int index);

/**
 * @brief Function to delete a node with given data.
 * @param head_ref pointer to the head node pointer.
 * @param data data of the node to delete.
 * @return p_node_t pointer to the head node.
 */
p_node_t delete_node_with_data(p_node_t *head_ref, int data);

/**
 * @brief Function to print the nodes to console.
 * @param head_ref pointer to the head node pointer.
 *
 * The function first prints the elements of the linked list forward and then
 * backward. It is also an example of how to iterate through the circular
 * doubly linked list.
 */
void print_list(p_node_t *head_ref);

/**
 * @brief Function to sort the nodes in ascending data order.
 * @param head_ref pointer to the head node pointer.
 */
void sort_list(p_node_t *head_ref);


// Help functions

/**
 * @brief Function to insert the first node with given data.
 * @param head_ref pointer to the head node pointer.
 * @param data data of the new node.
 * @return p_node_t pointer to the head node.
 */
p_node_t insert_first_node(p_node_t *head_ref, int data);

/**
 * @brief Function to insert a new head node with given data.
 * @param head_ref pointer to the head node pointer.
 * @param data data of the new node.
 * @return p_node_t pointer to the head node.
 */
p_node_t insert_new_head(p_node_t *head_ref, int data);

/**
 * @brief Function to insert a new tail node with given data.
 * @param head_ref pointer to the head node pointer.
 * @param data data of the new node.
 * @return p_node_t pointer to the head node.
 */
p_node_t insert_new_tail(p_node_t *head_ref, int data);

/**
 * @brief Function to check if the list is empty.
 * @param head_ref pointer to the head node pointer.
 * @return bool is true if the list is empty.
 */
bool is_empty(p_node_t *head_ref);

/**
 * @brief Function to insert a new tail node with given data.
 * @param head_ref pointer to the head node pointer.
 * @param delete pointer to the node to delete.
 * @return p_node_t pointer to the head node.
 */
p_node_t delete_node(p_node_t *head_ref, p_node_t delete);


#endif /* _27_double_circular_linked_list_h */
