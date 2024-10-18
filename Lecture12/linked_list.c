#include <stdlib.h>
#include <stdio.h>

#define EXAMPLE_LIST_LENGTH 10

struct ListNode {
    int value;
    struct ListNode* next;
};

void free_list(struct ListNode *head) {
    struct ListNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // Construct List
    struct ListNode *head = malloc(sizeof(struct ListNode));
    head->value = 0;
    head->next = NULL;

    struct ListNode *current = head;
    for (int i = 1; i < EXAMPLE_LIST_LENGTH; i++) {
        current->next = malloc(sizeof(struct ListNode));
        current = current->next;
        current->value = i;
        current->next = NULL;
    }

    // Print List
    current = head;
    while (current != NULL) {
        printf("%d\n", current->value);
        current = current->next;
    }

    free_list(head);
    head = NULL;

    return 0;
}