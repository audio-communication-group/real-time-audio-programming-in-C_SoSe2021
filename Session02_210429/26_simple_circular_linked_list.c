
#include "26_simple_circular_linked_list.h"

int main() {
    int choice, val;
    
    /* Start with the empty list using g_p_node_t */
    g_p_head = NULL;
    current = NULL;
    
    do {
        printf (" -1- Insert new node\n");
        printf (" -2- Remove node with value\n");
        printf (" -3- List all nodes\n");
        printf (" -4- Search node\n");
        printf (" -0- Exit\n");
        printf ("Choose an action: ");
        
        scanf ("%d", &choice);
        
        switch (choice) {
            case 1: new_node();
                break;
                
            case 2: printf ("Delete node with value: ");
                scanf ("%d", &val);
                remove_node_with_value (val);
                break;
                
            case 3: print_list();
                break;
                
            case 4: printf ("Search value: ");
                scanf ("%d", &val);
                search_node (val);
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


// Implementation

bool is_empty() {
    return g_p_head == NULL;
}


//insert link at the first location
void insert_node(p_node_t new_node) {
    // Check if there is a list
    if (is_empty()) {
        g_p_head = new_node;
        g_p_head->next = g_p_head;
        
    } else {
        //point it to old first node
        new_node->next = g_p_head;
        
        //point first to new first node
        g_p_head = new_node;
    }
}


void insert_node_1(p_node_t new_node) {
    p_node_t p_help;
    
    if (g_p_head == NULL) {
        g_p_head = new_node;
        new_node->next = new_node;
    }
    else {
        p_help = g_p_head;
        while( p_help->next != g_p_head ) {
            p_help = p_help->next;
        }
        p_help->next = new_node;
        new_node->next = g_p_head;
    }
}

// Show the list
void print_list() {
    // Check if there is a list
    if (is_empty()) {
        printf("Empty list\n");
        return;
    }
    
    // Get the head
    p_node_t p_current = g_p_head;
    
    do {
        printf("%d, ",p_current->data);
        p_current = p_current->next;
        }
    while (p_current != g_p_head);
    
    printf("\n");
}


void new_node() {
    p_node_t new_node = malloc(sizeof(node_t));
    
    if (new_node == NULL) {
        printf("No memory!?\n");
        return;
    }
    
    printf("Value for new node: ");
    do {
        scanf("%d", &new_node->data);
    }
    while( getchar() != '\n');
    
    insert_node_1(new_node);
}

// TODO **head
void remove_node_with_value(int val) {
    
    // Check if there is a list
    if (is_empty()) {
        printf("Empty list\n");
        return;
    }
    
    p_node_t p_help_1;
    p_node_t p_help_2;
    bool found = false;
    // Copy the head
    p_help_1 = g_p_head;
    
    // Case if the searched data is in the head node
    if (g_p_head->data == val) {
        found = true;
        // If head is the only node
        if (p_help_1 == p_help_1->next) {
            // Set head to NULL
            g_p_head = NULL;
            // Free the memory of the removed node
            free(p_help_1);
            
            return;
            
        } else {
            // Next node is the new head
            // Cut node to delete and reconnect it's neighbors
            p_help_1 = g_p_head->next;
            p_help_2 = get_last_node(g_p_head);
            p_help_2->next = p_help_1;
            g_p_head = p_help_1;
            
            // Free the memory of the removed node
            if (p_help_1 != p_help_1->next) free(p_help_1);

            return;
            }
        }
        // Search the data in the rest of the list
        else
        {   // Start at the beginning
            p_help_1 = g_p_head;
            
            // Traverse the list till searched data is found
            while (p_help_1->next != g_p_head) {
                p_help_2 = p_help_1->next;
                
                // Cut the node by connecting the previous and the next node together
                if (p_help_2->data == val) {
                    found = true;
                    p_help_1->next = p_help_2->next;
                    // Free the memory of the removed node
                    free(p_help_2);
                    return;
                }
                p_help_1 = p_help_2; // Go ahead
            } // End while
        } // End else
  
    
    if (found == false) printf("Data %d not found!\n", val);
    
}

node_t* get_last_node(node_t *head) {
    node_t *p_help = head;
    
    do {
        p_help = p_help->next;
        if ( p_help->next == g_p_head )  return p_help;
 
    // Stop at the end of the list
    } while (p_help != g_p_head);
    
    return p_help;
}


void search_node(int val) {
    int position = 0;
    // Check if there is a list
    if (is_empty()) {
        printf("Empty list\n");
        return;
    }
    
    // Get the head node pointer
    p_node_t p_help = g_p_head;
    bool found = false;
    
    // Case the data is in the head node
    if (p_help->data == val) {
        found = true;
        printf("Data: '%d' found on position %d!\n", p_help->data, position);
        return;
    }
    
    // Traverse the list till data is found
    do {
        p_help = p_help->next;
        position++;
        
        if ( p_help->data == val )
        {
            found = true;
            printf("Data: '%d' found on position %d!\n", p_help->data, position);
            return;
        }
        
        // Stop at the end of the list
    } while (p_help->next != g_p_head);
    
    if (found == false) printf("Data: '%d' not found!\n", val);
}
