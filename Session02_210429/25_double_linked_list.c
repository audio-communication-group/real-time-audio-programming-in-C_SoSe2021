#include "25_double_linked_list.h"

int main() {
    
    /* Start with the empty list using g_p_node_t */
    g_p_head = NULL;
    g_p_tail = NULL;
    
    int choice, position, data;
    
    do {
        printf("\n");
        printf (" -1- Insert new node at beginning\n");
        printf (" -2- Insert new node at the end\n");
        printf (" -3- Remove node at position\n");
        printf (" -4- List all nodes\n");
        printf (" -5- Search data forward\n");
        printf (" -6- Search data backwards\n");
        printf (" -0- Exit\n");
        printf ("Choose an action: ");
        
        scanf ("%d", &choice);
        
        switch (choice) {
            case 1: insert_at_beginning(&g_p_head);
                break;
            
            case 2: insert_at_end(&g_p_head);
                break;
                
            case 3: printf ("Delete position: ");
                scanf ("%d", &position);
                delete_node_at_position(&g_p_head, position );
                break;
                
            case 4: list_nodes(g_p_head);
                break;
                
            case 5: printf ("Search value: ");
                scanf ("%d", &data);
                search_node_forward(g_p_head, data);
                break;
                
            case 6: printf ("Search value: ");
                scanf ("%d", &data);
                search_node_backwards(g_p_tail, data);
                break;
                
            default: if (choice !=0) {
                printf ("Wrong input - exit\n");
                choice = 0; // Exit program
            }
                break;
        }

        
    } while ( choice != 0 );
    
    printf ("Exit\n");
    
    return 0;
}


/* Help function for cleaner code */
bool check_validity(p_node_t node) {
    /* If list is NULL or invalid position is given */
    if (node == NULL) {
        printf("Empty list, you have to create at least one node first!\n");
        return false;
    } else {
        return true;
    }
}


/* Function to delete a node in a Doubly Linked List.
 p_head --> pointer to head node pointer.
 del  -->  pointer to node to be deleted. */
void delete_node(p_node_t *p_head, p_node_t p_del)
{
    /* Base case */
    if (*p_head == NULL || p_del == NULL)
        return;
    
    /* If node to be deleted is head node */
    if (*p_head == p_del)
        *p_head = p_del->p_next;
    
    /* Change next only if node to be deleted is NOT
     the last node */
    if (p_del->p_next != NULL)
        p_del->p_next->p_prev = p_del->p_prev;
    
    
    /* Change prev only if node to be deleted is NOT
     the first node */
    if (p_del->p_prev != NULL)
        p_del->p_prev->p_next = p_del->p_next;
    
    /* Write the tail into the global node ptr */
    if (g_p_head != NULL) g_p_tail = get_tail(g_p_head);
    
    /* Finally, free the memory occupied by del*/
    free(p_del);
}



/* Function to delete the node at the given position
 in the doubly linked list */
void delete_node_at_position(p_node_t *p_head, int position)
{
    /* If list in NULL or invalid position is given */
    if ((*p_head == NULL) || (position < 0))
        return;
    
    p_node_t p_current = *p_head;
    
    /* Traverse up to the node at position from
     the beginning */
    int i;
    for (i = 0; (p_current != NULL) && (i < position); i++)
        p_current = p_current->p_next;
    
    /* If position is greater than the number of nodes
     in the doubly linked list */
    if (p_current == NULL) {
        printf("This is not a valid position!\nYou currently have %d node(s).\n", i);
        return;
    }
    
    /* Delete the node pointed to by 'current' */
    delete_node(p_head, p_current);
}





/* Function to insert a node at the beginning
 of the Doubly Linked List */
void insert_at_beginning(p_node_t *p_head)
{
    /* Allocate node */
    p_node_t p_new_node =
    (p_node_t)malloc(sizeof(node_t));
    
    if (p_new_node == NULL) {
        printf("No memory!?\n");
        return;
    }
    
    printf("Value for new node: ");
    do { scanf("%d", &p_new_node->data); }
    while( getchar() != '\n');
    
    /* Since we are adding at the beginning,
     prev is always NULL */
    p_new_node->p_prev = NULL;
    
    /* Link the old list off the new node */
    p_new_node->p_next = (*p_head);
    
    /* Change prev of head node to new node */
    if ((*p_head) != NULL)
        (*p_head)->p_prev = p_new_node;
    
    /* Move the head to point to the new node */
    (*p_head) = p_new_node;
    
    /* Write the tail into the global node ptr */
    if (g_p_head != NULL) g_p_tail = get_tail(g_p_head);
}

void insert_at_end(p_node_t *p_head)
{
    /* Allocate node */
    p_node_t p_new_node =
    (p_node_t)malloc(sizeof(node_t));
    
    // Catch memory error
    if (p_new_node == NULL) {
        printf("No memory!?\n");
        return;
    }
    
    // Get data
    printf("Value for new node: ");
    do { scanf("%d", &p_new_node->data); }
    while( getchar() != '\n');
    
    /* Since we are adding at the end,
     next is always NULL */
    p_new_node->p_next = NULL;
    
    // Case 1, new node is first and only node
    if (g_p_head == NULL) {
        // Prepare new node to be new head AND tail
        p_new_node->p_prev = NULL;
        g_p_head = p_new_node;
        g_p_tail = p_new_node;
        
    } else { // Case 2, all other cases
        p_node_t p_old_tail = get_tail(g_p_head);
        // Glue the new node onto the old tail
        p_new_node->p_prev = p_old_tail;
        p_old_tail->p_next = p_new_node;
        // Update global tail
        g_p_tail = p_new_node;
    }

}


/* Function to print nodes in a given double
 linked list */
void list_nodes(p_node_t p_head)
{
    if (check_validity(p_head) == false) return;
    
    while (p_head != NULL) {
        printf("%d ", p_head->data);
        p_head = p_head->p_next;
    }
    printf("\n");
}

void search_node_forward(p_node_t p_head, int searched_data)
{
    /* If list in NULL or invalid position is given */
    if (check_validity(p_head) == false) return;
    
    p_node_t p_current = p_head;
    int i;
    /* Traverse up to the node at position from
     the beginning */
    for (i = 0; p_current != NULL; i++) {
        if (p_current->data == searched_data) {
            printf("Data \'%d\' found on ", searched_data);
            // Remember the ternary operator: CONDITION ? ACTION_IF_TRUE : ACTION_IF_FALSE
            (i==0) ? (printf("head!\n\n")) : (printf("position head+%d!\n\n", i));
            return;
        }
        p_current = p_current->p_next;
    }
    
    if (p_current == NULL) {
        printf("Data \'%d\' not found!\n", searched_data);
    }
}



void search_node_backwards(p_node_t p_tail, int searched_data) {
    
    /* If list is NULL or invalid position is given */
    if (check_validity(p_tail) == false) return;
    
    p_node_t p_current = p_tail;
    int i;
    /* Traverse up to the node at position from
     the beginning */
    for (i = 0; p_current != NULL; i--) {
        if (p_current->data == searched_data) {
            printf("Data \'%d\' found on ", searched_data);
            (i==0) ? (printf("tail!\n")) : (printf("position tail%d!\n", i));
            return;
        }
        p_current = p_current->p_prev;
    }
    
    if (p_current == NULL) {
        printf("Data \'%d\' not found!\n", searched_data);
    }
    
}

p_node_t get_tail(p_node_t p_head) {
    
    p_node_t p_tail = NULL;
    p_node_t p_current = p_head;
    
    /* Traverse up to the node at position from
     the beginning */
    // Case, if there is only one node
    if (p_current->p_next == NULL) {
        p_tail = p_current;
    }
    // Case, if there are more than one node
    else {
        while (p_current->p_next != NULL) {
               p_current = p_current->p_next;
               p_tail = p_current;
           }
    }
    
    return p_tail;
}


