/*
 simple_linked_list.c
 
 A simple linked list example based on
 "Wolf (2010) 'Grundkurs C'"
 (kap014/listing001.c)
 */

// http://users.ece.cmu.edu/~eno/coding/CCodingStandard.html


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

// Globals
typedef struct Node {
    int data;
    struct Node *next;
} node_t;

typedef node_t* p_node_t;
p_node_t g_p_head;

// Function declaration
void new_node(void);
void insert_node(p_node_t new_node);
void remove_node_with_value(int val);
void list_nodes(void);
void search_node(int searched_data);
bool list_available(void);


int main() {
    // Declare some vars
    int choice, val;
    // In the beginning it was nothing - so the global head ptr is NULL
    g_p_head = NULL;

    // Command line interface (CLI)
    // This runs in a loop till the user enters a zero
    do {
        printf("\n");
        printf(" -1- Insert new node\n");
        printf(" -2- Remove node with value\n");
        printf(" -3- List all nodes\n");
        printf(" -4- Search node\n");
        printf(" -0- Exit\n");
        printf("Choose an action: ");
     
        // Get and save user input
        scanf ("%d", &choice);
        // Handle user input
        switch (choice) {
            case 1: new_node();
                break;

            case 2: printf ("Delete value: ");
                scanf ("%d", &val);
                remove_node_with_value(val);
                break;

            case 3: list_nodes();
                break;

            case 4: printf("Search value: ");
                scanf ("%d", &val);
                search_node (val);
                break;

            default: if (choice !=0) {
                printf ("Wrong input - exit\n");
                choice = 0; // Exit program
            }
                break;
        }

    } while (choice != 0);

    printf ("Exit\n");

    return 0;
}


// Function implementation
void insert_node(p_node_t new_node)
{
    // Just a help ptr to work with
    p_node_t p_temp;

    // Case, if this is the first node
    if (g_p_head == NULL) {
        g_p_head = new_node;
        new_node->next = NULL;
    }
    // Case if there exist nodes already
    else {
        // Catch the global head
        p_temp = g_p_head;
        // Step forward till the last node - it will point to NULL
        while( p_temp->next != NULL ) {
            p_temp = p_temp->next;
        }
        // Now the end is reached, insert the new node
        p_temp->next = new_node;    // former last node points to new node
        new_node->next = NULL;      // new node is new last node & points to NULL
    }
}


void new_node(void)
{
    // Allocate the memory for a new node from heap
    p_node_t new_node = (node_t*) malloc(sizeof(node_t));
    // Catch possible memory error, but this will probably never happen
    if (new_node == NULL) {
        printf("No memory!?\n");
        return;
    }
    // Ask for node data
    printf("Value for new node: ");
    do {
        scanf("%d", &new_node->data);
    }
    while( getchar() != '\n');
    // Insert the new node
    insert_node(new_node);
}


void remove_node_with_value(int val)
{
    // Declare two help ptr to work with
    p_node_t p_temp_1;
    p_node_t p_temp_2;
    // Init a found flag with default false
    bool found = false;

    // Check if there is a list
    if (list_available() == true) {
        // Case if the searched data is in the head node
        if (g_p_head->data == val) {
            found = true;
            // Next node is the new head
            p_temp_1 = g_p_head->next;
            g_p_head = p_temp_1;
            free(p_temp_1);
            return;
        }
        // Search the data in the rest of the list
        else
        {   // Start at the beginning
            p_temp_1 = g_p_head;
            // Traverse the list till searched data is found
            while (p_temp_1->next != NULL) {
                p_temp_2 = p_temp_1->next;
                // Cut the node by connecting the previous and the next node together
                if (p_temp_2->data == val) {
                    found = true;
                    p_temp_1->next = p_temp_2->next;
                  // Free the memory of the removed node
                  free (p_temp_2);
                    break;
                }
                p_temp_1 = p_temp_2;
            } // End while
        } // End else
    } // End if
    // Let the user know if the search was unsuccessful
    if (found == false) printf("Data %d not found!\n", val);
}


bool list_available()
{
    // Check if there is a list
    if (g_p_head == NULL) {
        printf("No list, you have to create a node first!\n");
        return false;
    } else {
        return true;
    }
}


void list_nodes()
{
    // Check if there is a list
    if (list_available() == false) return;
    // Copy the head ptr
    p_node_t p_temp = g_p_head;
    // Move forward with temporary ptr
    while (p_temp != NULL) {
        printf ("%d, ", p_temp->data);
        p_temp = p_temp->next;
    }
    
    printf("\n");
}


void search_node(int val)
{
    // Check if there is a list
    if (list_available() == false) return;
    
    if (list_available()) {
    // Get the head node pointer
    p_node_t p_temp = g_p_head;
    bool found = false;

    // Case the data is in the head node
    if (p_temp->data == val) {
        printf ("Data %d found!\n", p_temp->data);
        found = true;
        return;
    }

    // Traverse the list till data is found
    while (p_temp->next != NULL) {
            p_temp = p_temp->next;
            // Handle data found
            if (p_temp->data == val) {
                printf ("Data %d found!\n", p_temp->data);
                found = true;
                return;
            }
    }
    // Let the user know if the search was unsuccessful
    if (found == false) printf("Data %d not found!\n", val);
    }
}

