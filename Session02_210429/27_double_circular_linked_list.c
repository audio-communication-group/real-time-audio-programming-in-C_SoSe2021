


/*************************************************************/
/**
 *  @file 27_double_circular_linked_list.c
 *  @brief Main routine and implementation of the functions
 *  @author Markus Hädrich markus.haedrich@tu-berlin.de
 *
 *  @discussion Course: Real-Time Audio Programing in C\n
 *  Supervisors: Thomas Resch, Markus Hädrich, (TU-Berlin)\n
 *  This is one possible solution for the\n
 *  homework about linked lists.
 *
 *  @date 30.04.19. – first implementation
 *
 *  @todo write more functions (e. g. @c sum() or @c mult() all elements)
 *
 *  @bug if you found one - report it!
 *
 *  @version 0.1.1
 **************************************************************/

#include "27_double_circular_linked_list.h"




int main(int argc, char* argv[]) {

    // Start with an empty list
    p_node_t head = NULL;
    
    // Hold menue data
    unsigned int choice, index;
    int data, prev_node_data;

    // Menue
    do {
        printf("\n -1- Insert new node at index\n");
        printf(" -2- Insert new node after node\n");
        printf(" -3- Delete node at index\n");
        printf(" -4- Delete node with data\n");
        printf(" -5- List nodes\n");
        printf(" -6- Sort nodes\n");
        printf(" -0- Exit\n");
        printf("Choose an action: ");

        // Read user action
        scanf("%d", &choice);

        switch (choice) {
                
            case 1: printf("New node at index: ");
                scanf ("%d", &index);
                printf("Value for new node: ");
                scanf("%d", &data);
                head = insert_node_at_index(&head, index, data);
                break;

            case 2: printf("Value of previous node: ");
                scanf("%d", &prev_node_data);
                printf("Value for new node: ");
                scanf("%d", &data);
                head = insert_new_node_after_node(&head, prev_node_data, data);
                break;
                
            case 3: printf("Delete node at index: ");
                scanf ("%d", &index);
                head = delete_node_at_index(&head, index);
                break;
                
            case 4:printf("Value of node to delete: ");
                scanf("%d", &data);
                head = delete_node_with_data(&head, data);
                break;
                
            case 5: printf("List nodes: ");
                print_list(&head);
                break;
                
            case 6:
                sort_list(&head);
                print_list(&head);
                break;

            default: if (choice !=0) {
                printf("Wrong input\n");
                choice = 0; // Exit program
            }
                break;
        }

    } while ( choice != 0 );

    printf ("Exit and good bye!\n");

    return 0;
}



// Function Implementations

bool is_empty(p_node_t *head_ref) {
    return (*head_ref == NULL);
}


p_node_t new_node_with_data(int value) {
    p_node_t new_node = (p_node_t)malloc(sizeof(node_t));
    
    new_node->data = value;
    new_node->next = new_node;
    new_node->prev = new_node;
    
    return new_node;
}



p_node_t insert_first_node(p_node_t *head_ref, int data)
{
    if (is_empty(head_ref)) {
        p_node_t new_node = new_node_with_data(data);
        *head_ref = new_node;
    }
    
    return *head_ref;
}


void print_list(p_node_t *head_ref)
{
    if (is_empty(head_ref)) {
        printf("Empty list!\n");
        return;
    }
    
    p_node_t current = *head_ref;

    printf("\nTraversal in forward direction \n");
    while (current->next != *head_ref)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("%d ", current->data);
    
    printf("\nTraversal in reverse direction \n");
    p_node_t tail = (*head_ref)->prev;
    current = tail;
    while (current->prev != tail)
    {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("%d ", current->data);
    printf("\n");
}


p_node_t insert_new_head(p_node_t *head_ref, int data)
{
    if (is_empty(head_ref)) {
        return (insert_first_node(head_ref, data));
    }
    
    else {
        // Pointer tail points to last node
        p_node_t tail = (*head_ref)->prev;
        
        // Allocate new node
        p_node_t new_node = new_node_with_data(data);
        
        // Setting up previous and next of new node
        new_node->next = *head_ref;
        new_node->prev = tail;
        
        // Update next and previous pointers of head
        // and tail
        tail->next = (*head_ref)->prev = new_node;
        
        // Update head pointer
        *head_ref = new_node;
    
        return *head_ref;
    }
}



p_node_t insert_new_tail(p_node_t *head_ref, int data)
{
    // If the list is empty, create a single node
    if (head_ref == NULL){
        p_node_t new_node = new_node_with_data(data);
        *head_ref = new_node;
        return *head_ref;
    }
    
    // If list is not empty
    // Get last node
    p_node_t tail = (*head_ref)->prev;
    
    // Create node dynamically
    p_node_t new_node = new_node_with_data(data);
    
    // Start is going to be next of new_node
    new_node->next = *head_ref;
    
    // Make new node previous of head
    (*head_ref)->prev = new_node;
    
    // Make tail previous of new node
    new_node->prev = tail;
    
    // Make new node next of old last
    tail->next = new_node;
    
    new_node->next = (*head_ref);
    
    return *head_ref;
}



p_node_t insert_node_at_index(p_node_t *head_ref, unsigned int index, int data)
{
    // Check if we have a node
    if (is_empty(head_ref)) {
        return insert_first_node(head_ref, data);
    }
    
    // Get head pointer
    p_node_t temp = *head_ref;
    
    // Search index
    // Step through the list
    int i = 0;
    
    do {// Find index
        // Create and insert new node at index
        if (i == index) {
            
            // Creating new node
            p_node_t new_node = new_node_with_data(data);
            
            // Insert new_node at index.
            new_node->prev = temp->prev;
            new_node->next = temp;
            temp->prev->next = new_node;
            temp->prev = new_node;
            
            // Check if we have a new head
            if (index == 0) *head_ref = new_node;
            
            return *head_ref;
        }
        temp = temp->next;
        i++;
        
    } while (temp != *head_ref);
    
    // Check if we have a new tail
    if (index == i) {
        *head_ref = insert_new_tail(head_ref, data);
        
    } else {
        printf("Entered index not possible, list only have %d nodes\n", i);
    }
    
    return *head_ref;
}



p_node_t insert_new_node_after_node(p_node_t *head_ref, int prev_data, int data)
{
    // Check if we have a node
    if (is_empty(head_ref)) {
        printf("Empty list, inserted as first node.\n");
        
        return insert_first_node(head_ref, data);
    }
    
    // Allocate new node
    p_node_t new_node = new_node_with_data(data);
    
    // Find node having prev_node_data and next node of it
    p_node_t temp = *head_ref;
    while ((temp->data != prev_data) && (temp->next != *head_ref))
        temp = temp->next;
    
    if (temp->data == prev_data) {
        p_node_t next = temp->next;
    
        // Insert new_node between temp and next.
        temp->next = new_node;
        new_node->prev = temp;
        new_node->next = next;
        next->prev = new_node;
        
    } else {
        printf("No node with data %d", prev_data);
    }
    
    return *head_ref;
}



p_node_t delete_node_at_index(p_node_t *head_ref, unsigned int index)
{
    if (is_empty(head_ref)) return NULL;
    
    // Set node to delete to the head
    p_node_t temp = *head_ref;
    
    // Search index
    unsigned int i=0;
    do {
        // Create and insert new node after index
        if (i == index) return delete_node(head_ref, temp);
        temp = temp->next;
        
        // Count iterations
        i++;
        
    } while (temp != *head_ref);
    
    // Message if the user request exceeds the list length
    if (index > i) printf("Entered index not possible, list only have %d nodes\n", i);
    
    return *head_ref;
}



p_node_t delete_node_with_data(p_node_t *head_ref, int data)
{
    // Error check
    if (is_empty(head_ref)) return NULL;
    
    // Get head reference
    p_node_t temp = *head_ref;
    
    // Search index of data
    do {
        if (temp->data == data) return delete_node(head_ref, temp);
        temp = temp->next;
        
    } while (temp != *head_ref);
    
    return *head_ref;
}



p_node_t delete_node(p_node_t *head_ref, p_node_t del)
{
    // Error check
    if (*head_ref == NULL || del == NULL) return NULL;
    
    // Case if del is the last & only node
    if ((del->next == del) && (del->prev == del)) {
        *head_ref = NULL;
        
        // All other cases
    } else {
        del->next->prev = del->prev;
        del->prev->next = del->next;
        if (del == *head_ref) *head_ref = del->next;
    }
    
    // Give back occupied memory of cutted node
    free(del);
    
    return *head_ref;
}



void sort_list(p_node_t *head_ref) {
    
    // Hold data while swap
    int temp;
    
    /* Initialisation here only to silence compiler warning of derefencing
     a NULL pointer */
    p_node_t before = *head_ref;
    p_node_t after = before->next;
    
    for (before = *head_ref; before->next != *head_ref; before = before->next)
    {
        for (after = before->next; after != *head_ref; after = after->next)
        {
            // Swap data here if necessary - node structure stay the same
			// TASK: Implement a sort func where the pointers are changed, instead of the data!
            if (before->data > after->data) {
                temp = before->data;
                before->data = after->data;
                after->data = temp;
            }
        }
    }
}
