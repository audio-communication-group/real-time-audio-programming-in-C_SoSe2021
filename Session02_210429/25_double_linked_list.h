
#ifndef _25_double_linked_list_h
#define _25_double_linked_list_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* A node of the double linked list */
typedef struct Node {
    int data;
    struct Node* p_next;
    struct Node* p_prev;
} node_t;

/* Custom data type (pointer to a node struct) */
typedef node_t *p_node_t;
/* Store global head */
p_node_t g_p_head;
/* Store global tail */
p_node_t g_p_tail;

// Declarations
bool check_validity(p_node_t node);
p_node_t get_tail(p_node_t p_head); 
void delete_node(p_node_t *p_head, p_node_t p_del);
void delete_node_at_position(p_node_t *head_ref, int position);
void insert_at_beginning(p_node_t *p_head);
void insert_at_end(p_node_t *p_tail);
void list_nodes(struct Node* head);
void search_node_backwards(p_node_t p_tail, int searched_data);
void search_node_forward(p_node_t p_head, int searched_data);



#endif /* _25_double_linked_list */
