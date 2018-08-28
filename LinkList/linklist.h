/* This head file give interface of all operations of linked list. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <student.h>

// Define a type: LinkList
typedef struct LinkList
{
	LinkNode* head;
}LinkList;

// Creat a LinkNode
LinkNode* linklist_node_creat();

// Delete a LinkNode
void linklist_node_delete(LinkNode* p);

// Swap tow LinkNodes in a LinkList
void linklist_node_swap(LinkNode* p_before, LinkNode* q_before);

// Swap tow LinkNodes in a LinkList by using index number
void linklist_node_swap2(LinkList list, int m, int n);

// Creat a LinkList with n nodes
LinkList linklist_creat(int n);

// Clear all nodes in a LinkList
void linklist_clear(LinkList list);

// To get the pointer of node that you specify by index number n
LinkNode* linklist_getnode(LinkList list, int n);

// To set the node in a LinList by given node
void linklist_setnode(LinkList list, int n, LinkNode node);

// To append a node in the tail of a LinkList
void linklist_push_back(LinkList list, LinkNode node);

// To pop out a node from the tail of a LinkList
LinkNode linklist_pop_back(LinkList list);

// To insert a new node in the specify position n
void linklist_insert(LinkList list, int n, LinkNode node);

// To erase a node in LinkList
void linklist_erase(LinkList list, LinkNode* p);

// Copy a LinkList to another
void linklist_copy(LinkList list1, LinkList list2);

// To make a clone body of current LinkList
LinkList linklist_clone(LinkList list);

// To count the length of a LinkList
int linklist_length(LinkList list);

// To judege if a LinkList is empty.
bool linklist_empty(LinkList list);

// To throw out a warning when position n is not in the LinkList.
void position_warning(int n, int n_upperlimit, char* function_name);
