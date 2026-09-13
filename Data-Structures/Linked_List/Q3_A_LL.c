//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void moveOddItemsToBack(LinkedList *ll)
{
	//뻘짓 - 찾아서 기준점 앞에다가 하나씩 넣으려고함 
	// ListNode *ptr, *ptr_prev, *cur, *prev;
	// ptr_prev = NULL, prev = NULL; // 기준점 노드의 이전 노드, 현재 노드의 이전 노드
	// ptr = ll->head; // 기준점이 되는 노드
	// cur = ll->head; // 순회용 현재 노드
	// if(ptr==NULL || cur==NULL){ // 링크드 리스트안이 비었을 경우 - 예외처리1
	// 	return;
	// }
	// while (ptr!=NULL) // 기준점 노드 구하기 기준노드의 Item이 홀수면 중단 / 짝수면 계속 반복
	// {
	// 	if(ptr->item%2==1){
	// 		break;
	// 	}
	// 	ptr_prev = ptr;
	// 	ptr = ptr->next;
	// }
	// if(ptr!=NULL && ptr->item%2==0){
	// 	return;
	// }
	// while (cur!=NULL)
	// {
	// 	if(cur->item%2==0){ // 순서 변경 로직 - 현재 노드의 item이 짝수이면
	// 		if(ptr_prev==NULL){ // 기준점이 맨앞
	// 			prev->next = cur->next; // cur의 이전노드를 cur 다음 노드로 연결
	// 			cur->next = ptr; // cur의 next 포인터를 기준 노드 주소로 변경
	// 			ll->head = cur; // 헤더 변경
	// 			ptr_prev = cur; // 기준 노드의 이전노드 변경(추가했으니까)
	// 			cur = ptr; // 현재노드를 기준점으로 이동(기준점앞으로 이동했으니까 기준점 뒤부터 확인하도록)
	// 		}else{ // 기준점이 맨앞이 아님
	// 			prev->next = cur->next; // cur 이전 노드를 cur 다음노드랑 연결
	// 			cur->next = ptr; // cur의 포인터를 기준노드로 변경
	// 			ptr_prev->next = cur; // 기준노드의 이전노드의 포인터를 현재노드로 변경
	// 			cur = ptr; // 현재 노드를 기준점으로 이동
	// 		}
	// 	}
	// 	prev = cur;
	// 	cur = cur->next;
	// 	/* code */
	// }
	// return ;

	// 함수 사용으로 구현하기
	ListNode *cur, *next;
	cur = ll->head;
	int idx = 0;
	while (cur!=NULL)
	{
		next = cur->next;
		if(cur->item%2==1){
			// 홀수면 맨뒤에 삽입 (삭제, 삽입 함수 사용)
			insertNode(ll, ll->size, cur->item);
			removeNode(ll, idx);
		}
		cur = next;
		idx++;
	}
	
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
