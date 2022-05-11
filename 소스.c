#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];

typedef struct AddressList {
	char name[10];
	int telephone;
	char adress[100];
	int birthday;
}AddressList;

typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode;

typedef struct AddressListNode {
	AddressList addressList;
	struct AddressListNode* llink;
	struct AddressListNode* rlink;
}AddressListNode;

DListNode* current;
AddressListNode* currentAddressNode;

void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

void init_addressListNode(AddressListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

void print_DList(DListNode* phead) {
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		if (p == current)
			printf("<-| #%s# |->", p->data);
		else
			printf("<-| %s |->", p->data);
	}
	printf("\n");
}

void print_address(AddressListNode* phead) {
	AddressListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("성명: %s	전화번호: %d	주소: %s	생년월일: %d\n",p->addressList.name,p->addressList.telephone,p->addressList.adress,p->addressList.birthday);//출력문
		printf("\n");
	}
}

void search(AddressListNode* phead) {
	AddressListNode* p;
	element search;

	printf("조회할 성명을 입력하세요 : ");
	scanf("%s", &search);
	for (p = phead->rlink; p != phead; p = p->rlink) {
		if (strcmp(search, p->addressList.name) == 0) {
			printf("성명: %s	전화번호: %d	주소: %s	생년월일: %d\n", p->addressList.name, p->addressList.telephone, p->addressList.adress, p->addressList.birthday);//출력문
			printf("\n");
		}
	}
}

void dinsert(DListNode* before, element data) {
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	//newnode->data = data; int 가 아니므로
	strcpy(newnode->data, data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

//주소록 추가 함수
void add(AddressListNode* before) {
	AddressListNode* newnode = (AddressListNode*)malloc(sizeof(AddressListNode));
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;

	printf("이름을 입력하세요: ");
	scanf("%s", &newnode->addressList.name);
	printf("전화번호를 입력하세요: ");
	scanf("%d", &newnode->addressList.telephone);
	printf("주소를 입력하세요: ");
	scanf("%s", &newnode->addressList.adress); //띄워쓰기를 포함해서 받는다
	printf("생년월일을 입력하세요: ");
	scanf("%d", &newnode->addressList.birthday);
	printf("\n");
}

//주소록 삭제함수
void ddelete(AddressListNode* head, element removed) {
	if (strcmp(removed, head->addressList.name) == 0) {
		head->llink->rlink = head->rlink;
		head->rlink->llink = head->llink;
		free(head);
		printf("삭제 되었습니다\n");
		printf("\n");
	}
	else {
		head = head->llink;
		ddelete(head, removed);
	}
	return;
}

int main(void) {
	char input;
	DListNode* menu = (DListNode*)malloc(sizeof(DListNode));
	AddressListNode* list = (AddressListNode*)malloc(sizeof(AddressListNode));
	init(menu);
	init_addressListNode(list);

	dinsert(menu, "주소록 출력");
	dinsert(menu, "주소록 검색");
	dinsert(menu, "주소록 삭제");
	dinsert(menu, "주소록 추가");

	current = menu->rlink;
	currentAddressNode = list->rlink;
	print_DList(menu);

	do {
		printf("\n명령어를입력하시오(<,>,e,q):");
		input = getchar();
		if (input == '<') {
			current = current->llink;
			if (current == menu) //만약 head라면 한칸 더 움직일것
				current = current->llink;
		}
		else if (input == '>') {
			current = current->rlink;
			if (current == menu) //만약 head라면 한칸 더 움직일것
				current = current->rlink;
		}

		//엔터가 입력되었을때
		else if (input == 'e') {
			if (strcmp(current->data,"주소록 추가") == 0){
				add(list);
			}
			
			else if (strcmp(current->data,"주소록 삭제") == 0) {
				element removed;
				printf("제거할 주소록의 성명을 입력하세요 :");
				scanf("%s", &removed);
				ddelete(list, removed);
			}
						
			else if (strcmp(current->data, "주소록 검색") == 0){
				search(list);
			}

			else if (strcmp(current->data, "주소록 출력") == 0){
				print_address(list);
			}
		}
		print_DList(menu);
		getchar();
	} while (input != 'q');

	free(menu);
	free(list);
	return 0;
}