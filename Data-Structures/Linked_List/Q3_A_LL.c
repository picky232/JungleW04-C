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
// 알고리즘 : 가장앞에 위치한 값이 홀수인 노드를 기준으로 잡고 기준노드 뒤부터 순회하여 짝수를 기준노드 앞으로 이동함
{
	ListNode *cur, *ptr, *prev=NULL, *ptr_prev=NULL;
	cur = ll->head;
	ptr = ll->head;
	if(ll->head == NULL || ll->size == 0){
		return;
	}

	while (ptr != NULL)
	{
		if(ptr->item%2==1){
			break;
		}
		ptr_prev = ptr;
		ptr = ptr->next;
	}
	if(ptr==NULL){
		return ;
	}
	cur = ptr->next;
	prev = ptr;
	while (cur != NULL)
	{
		ListNode *next_node = cur->next; // 다음 노드 미리 저장(순회하는 노드 위치 변경하면 next도 바뀜)
		if(cur->item%2==0){ // 짝수일때
			if(ptr_prev==NULL){ // ptr이 링크드 리스트의 헤드일때
				prev->next = cur->next; // prev의 next 갱신 - 기준노드로
				cur->next = ptr; // 현재 노드의 next 변경(ptr)로 - 기준노드 앞에 옮겼음
				ptr_prev = cur; // 기준점 prev 갱신
				ll->head = ptr_prev; // 링크드 리스트 헤드 갱신
			}
			else{ // ptr이 헤드 아닐때
				prev->next = cur->next; // 이전노드의 next 갱신
				cur->next = ptr; // 현재노드의 next 갱신 - 기준노드로
				ptr_prev->next = cur; // 기준노드의 이전노드 next 갱신
				ptr_prev = cur; // * 기준점 prev 갱신
			}
		}
		else{ // 홀수알때
			prev = cur; // cur만 바뀜으로 prev도 이동
			// cur이 짝수이면 이전노드는 바뀌지 않음 왜냐? cur이 빠지면 다음노드가 prev->next가 됨. 고로 바꿀 필요 없음
		}
		cur = next_node; // cur을 다음노드의 주소로 변경
	}
}

// 	// 함수 사용으로 구현하기
// void moveOddItemsToBack(LinkedList *ll)
// {
// 	ListNode *cur, *next;
// 	int idx = 0;
// 	int ori_size;
// 	int i;
// 	// 예외 처리
// 	if(ll->head == NULL || ll->size==0){ 
// 		return;
// 	}
// 	// for문으로 사용하면 굳이 마지막까지 순회하지 않고 기존의 배열 크기만큼만 돌면 됨
// 	ori_size = ll->size; // 원래 링크드 리스트 크기
// 	cur = ll->head; // 순회할 노드
// 	for(i=0; i<ori_size; i++){
// 		next = cur->next; // 현재노드의 다음노드 주소를 미리 담아둠(삭제하면 사라짐)
// 		if(cur->item%2==1){
// 			insertNode(ll, ll->size, cur->item); // 현재 노드값 맨 뒤에 추가
// 			removeNode(ll, idx); // 현재 노드 삭제
// 			idx--; // 노드가 사라졌음으로 idx값 현재노드를 기점으로 뒤에까지 다 -1해야함으로
// 		}
// 		cur = next; // 미리 담아둔 다음노드 주소를 cur에 넣고 다시 순회
// 		idx++; // 인덱스 값 증가
// 	}
// }

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


void removeAllItems(LinkedList *ll) // 전체 삭제
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next; // free하고 나면 재지정 못하니까 미리 다음 노드 주소 담기
		free(cur); // 할당된거 풀어주기
		cur = tmp; // 옮기기
	}
	// 링크드 리스트를 빈상태로 초기화
	ll->head = NULL; // 헤드 노드를 NULL로 변경
	ll->size = 0; // 사이즈 초기화
}

// 노드의 주소를 찾아서 반환
ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp; // temp 포인터 공간에 listNode담겠다.

	// 매개변수의 값 예외처리
	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head; // 초기값 설정

	if (temp == NULL || index < 0) // 배열이 빈배열일때
		return NULL;

	// 원하는 노드 위치 찾기
	while (index > 0){ // index값이 0보다 작으면 중단
		temp = temp->next; // 노드 순회
		if (temp == NULL) // 노드가 없으면
			return NULL;
		index--; // index값 감소 (while 종료조건)
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	// 링크드 리스트가 비었을때 or 맨 앞에 원소 삽입할때 추가하기
	if (ll->head == NULL || index == 0){
		cur = ll->head; // cur을 링크드 리스트의 헤드 노드를 가리키도록 변경
		ll->head = malloc(sizeof(ListNode)); // ListNode구조체 하나가 들어갈 크기의 빈공간 확보 후 확보한 공간의 시작수조 반환
		ll->head->item = value; // 새 노드에 값 채우기
		ll->head->next = cur; // 새 노드의 next를 head로 연결
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	// 특정위치에 새 값 삽입
	if ((pre = findNode(ll, index - 1)) != NULL){ // 인덱스 위치가 현재 링크드 리스트 크기보다 큰지 확인, pre에 index-1위치의 노드 담음
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



void moveOddItemsToBack(LinkedList *ll)
{
	ListNode *prev, *cpt, *cur, *temp, *cpt_prev;
	if(ll->head==NULL){
		return;
	}
	cur = ll->head; // 현재노드
	prev = NULL; // 현재 노드에서 이전위치
	cpt = cur; // 가장 앞에 있는 홀수
	cpt_prev = NULL;
	int cpt_idx = 0, idx = 0;
	while (cur != NULL)
	{
		if(cpt->item%2==0){ // 맨앞 홀수 노드 포인터 홀수면 고정
			cpt_prev = cpt;
			cpt = cpt->next;
			cpt_idx++;
		}
		if(cur->item%2==0 && cpt_idx<idx){
			if(cpt_idx==0){ // 맨앞노드에 앞에 추가
				prev->next = cur->next; // 헤드의 next를 현재노드의 next로 바꿈, 어짜피 붙어있는 첫번째 두번째 노드를 바꾸나, 떨어져있는 첫번째 세번째 노드를 바꾸나 똑같음.
				cur->next = cpt;
				ll->head = cur;
				cpt_idx++;
			}else{ // 중간에 포인터, 중간에 현재 노드 변경
				prev = cur->next; // 현재 노드의 이전노드의 next포인터 주소를 현재 노드의 포인터 주소로 변경
				cur->next = cpt; // 현재 노드의 next포인터 주소를 cpt로 변경
				cpt_prev->next = cur; // 기준인 ptr의 이전노드의 next포인터 주소를 현재 노드로 변경
			}
		}
		
		idx++;
		prev = cur; // 현재 노드의 이전
		cur = cur->next; // 다음 노드의 주소 저장
		/* code */
	}
	return;
}