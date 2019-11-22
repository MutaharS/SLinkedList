#include<stdio.h>
#include<stdlib.h>

struct node{
    int value;
    struct node* next;
};

void add_to_list(struct node** list);
void print_nodes(struct node* list);
struct node* clear_list(struct node* list);
struct node* delete_node(struct node* list);

int main(){
    struct node *first = NULL;  // Points to the first node (initially empty)

    //  Add Node, search a node, clear list, delete node,
    char code;
    printf("Welcome to the Linked List database.\n\n");

    for(;;){
        printf("Print the list: 'p'\n");
        printf("Add a node:     'a'\n");
        printf("Delete a node:  'd'\n");
        printf("Clear the list: 'c'\n");
        printf("Quit:           'q'\n");

        printf("Enter operation code: ");
        
        code = getchar();
        if(code == '\n'){
            code = getchar();
        }
        
        switch(code){
            case 'p':   print_nodes(first); // void
                        putchar('\n');
                        break;
            case 'a':   add_to_list(&first);    // takes address of list
                        break;
            case 'd':   first = delete_node(first); // returns list
                        putchar('\n');
                        break;
            case 'c':   first = clear_list(first); // returns list
                        putchar('\n');
                        break;
            case 'q':   return 0;
            default:    printf("Invalid Operation Code.\n\n");
        }
    }

    return 0;
}

// Adding a node to the list
void add_to_list(struct node** list){
    printf("Enter a value to add to linked list: ");
    int n;
    scanf("%d", &n);
    putchar('\n');
    struct node *new_node;

    new_node = malloc(sizeof(struct node));
    if(new_node == NULL){
        printf("Could not create node.");
        return;
    }
    new_node->value = n;
    new_node->next = *list;
    *list = new_node;
}

//  Delete node from list containing value
struct node* delete_node(struct node* list){
    //  Prompt user for value to delete
    printf("Enter value for which node to delete: ");
    int num;
    scanf("%d", &num);


    struct node *prev, *cur;
    for(prev = NULL, cur = list; cur != NULL && cur->value != num; prev = cur, cur = cur->next){
        /* EMPTY LOOP BODY */   ;
    }

    // Special cases:
    //  If we have reached end of list without finding value
    if(cur == NULL){
        printf("Value doesn't exist in list.\n");
        return list;
    }
    //  We found the value at the start of the list
    else if(prev == NULL){
        list = cur->next;
        free(cur);
        return list;
    }
    //  If we are in the middle of the list
    else if(prev != NULL){
        prev->next = cur->next;
        free(cur);
        return list;
    }
    //  If we have reached the last item of the list ...
    else if(cur->next == NULL){

        free(cur);  // We found the value, so we free current node

        //  ... and the value was contained in a list of at least two nodes
        if(prev != NULL){
            prev->next = NULL;
            return list;
        }

        //  ... and the value was contained in the single node at the start
        if(prev == NULL){
            list = NULL;
            return list;
        }
    }

}   // End function

//  Print the linked list's values
void print_nodes(struct node* list){
    if (list == NULL){
        printf("List is empty!\n");
        return;
    }
    struct node* p;
    printf("Values:");
    for(p = list; p != NULL; p = p->next){
        printf(" %d", p->value);
    }
    putchar('\n');
}

//  Clear the linked list
struct node* clear_list(struct node* list){
    printf("Clearing List.\n");
    struct node *prev;
    prev = NULL;

    while(list != NULL){
        prev = list;
        list = list->next;
        free(prev);
    }
    return list;
}