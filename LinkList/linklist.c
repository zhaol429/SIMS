#include <linklist.h>

// Creat a LinkList with n nodes
LinkList linklist_creat(int n)
{
	LinkList list;

	list.head = linklist_node_creat();
	if(n < 0)
	{
		printf("Warning: in \"LinkList linklist_creat(int n)\", n is negetive.\n");
		printf("Creat an empty list.\n");
		return list;
	}

	LinkNode* p = list.head;
	for(int i = 1; i <= n; i++)
	{
		LinkNode* node = linklist_node_creat();
		p->link = node;
		p = p->link;
	}

	return list;
}

// Clear all nodes in a LinkList
void linklist_clear(LinkList list)
{
	LinkNode* p = list.head;
	while(list.head->link)
	{
		p = list.head->link;
		list.head->link = p->link;
		linklist_node_delete(p);
		free(p);
	}
}

// To judege if a LinkList is empty.
bool linklist_empty(LinkList list)
{
	return !(list.head->link);
}

// To count the length of a LinkList
int linklist_length(LinkList list)
{
	int length = 0;
	LinkNode* p = list.head->link;
	while(p)
	{
		p = p->link;
		length++;
	}

	return length;
}

// To get the pointer of node that you specify by index number n
LinkNode* linklist_getnode(LinkList list, int n)
{
	if(n <= -2)
	{
		printf("Warning: in \"LinkNode* linklist_getnode(LinkList list, int n)\", n < -2 now!\n");
		printf("Return a null pointer!\n");
		return NULL;
	}
	if(n >= linklist_length(list))
	{
		printf("Warning: in \"LinkNode* linklist_getnode(LinkList list, int n)\", n is over list's length!\n");
		printf("Return a null pointer!\n");
		return NULL;
	}

	LinkNode* p = list.head;
	for(int i = 0; i <= n; i++)
	{
		p = p->link;
	}

	return p;
}

// To throw out a warning when position n is not in the LinkList.
void position_warning(int n, int n_upperlimit, char* function_name)
{
	printf("Warning: in ");
	printf("\"%s\"", function_name);
	if(n < 0)
	{
		printf(", n is negtive!\n");
	}
	if(n >= n_upperlimit)
	{
		printf(", n over list's length!\n");
	}
	printf("Nothing has been done!\n");
}

// To set the node in a LinList by given node
void linklist_setnode(LinkList list, int n, LinkNode node)
{
	if(n < 0 || n >= linklist_length(list))
	{
		return position_warning(n, linklist_length(list), "void linklist_setnode(LinkList list, int n, LinkNode node)");
	}

	LinkNode* p = linklist_getnode(list, n);
	LinkNode* p_link = p->link;
	*p = node;
	p->link = p_link;
}

// To append a node in the tail of a LinkList
void linklist_push_back(LinkList list, LinkNode node)
{
	LinkNode* p = list.head;
	while(p->link)
	{
		p = p->link;
	}
	p->link = linklist_node_creat();
	node.link = NULL;
	*(p->link) = node;
}

// To pop out a node from the tail of a LinkList
LinkNode linklist_pop_back(LinkList list)
{
	LinkNode* p = list.head;
	while(p->link)
	{
		p = p->link;
	}
	LinkNode node = *p;
	linklist_node_delete(p);
	free(p);

	return node;
}

// To insert a new node in the specify position n
void linklist_insert(LinkList list, int n, LinkNode node)
{
	int N = linklist_length(list);
	if(n < 0 || n >= N)
	{
		return position_warning(n, N, "void linklist_insert(LinkList list, int n, LinkNode node)");
	}

	LinkNode* p = linklist_getnode(list, n-1);
	LinkNode* p_next = p->link;
	LinkNode* newNode = linklist_node_creat();
	*newNode = node;
	p->link = newNode;
	newNode->link = p_next;
}

// To erase a node in LinkList
void linklist_erase(LinkList list, LinkNode* p_current)
{
	LinkNode* p_before = list.head->link;
	while(p_before->link != p_current)
	{
		p_before = p_before->link;
	}

	p_before->link = p_current->link;
	linklist_node_delete(p_current);
	free(p_current);
}

// Copy a LinkList to another
void linklist_copy(LinkList list1, LinkList list2)
{
	if(!linklist_empty(list1))
	{
		linklist_clear(list1);
	}

	for(LinkNode* p = list2.head->link; p != NULL; p = p->link)
	{
		linklist_push_back(list1, *p);
	}
}

// To make a clone body of current LinkList
LinkList linklist_clone(LinkList list)
{
	LinkList list_result = linklist_creat(0);
	linklist_copy(list_result, list);
	return list_result;
}

// Swap tow LinkNodes in a LinkList
void linklist_node_swap(LinkNode* p_before, LinkNode* q_before)
{
	if(!p_before || !q_before || !p_before->link || !q_before->link)
	{
		printf("Warning in \"void linklist_node_swap(LinkNode* p_before, LinkNode* q_before)\"!\n");
		printf("Tail node has participate in swap!\n");
		printf("Nothing has been done!\n");
		return;
	}

	LinkNode* p = p_before->link;
	LinkNode* p_after = p->link;
	LinkNode* q = q_before->link;
	LinkNode* q_after = q->link;

	if(p_after == q)
	{
		p_before->link = q;
		q->link = p;
		p->link = q_after;
	}
	else if(q_after == p)
	{
		q_before->link = p;
		p->link = q;
		q->link = p_after;
	}
	else
	{
		p_before->link = q;
		q->link = p_after;
		q_before->link = p;
		p->link = q_after;
	}
}

// Swap tow LinkNodes in a LinkList by using index number
void linklist_node_swap2(LinkList list, int m, int n)
{
	int N = linklist_length(list);
	if(m < 0 || m >= N)
	{
		return position_warning(m, N, "void linklist_node_swap(LinkList list, int m, int n)");
	}
	if(n < 0 || n >= N)
	{
		return position_warning(n, N, "void linklist_node_swap(LinkList list, int m, int n)");
	}
	if(m == n)
	{
		return;
	}

	LinkNode* p_before_m = linklist_getnode(list, m-1);
	LinkNode* p_before_n = linklist_getnode(list, n-1);

	linklist_node_swap(p_before_m, p_before_n);
}