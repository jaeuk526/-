#define _CRT_SECURE_NO_WARNINGS //scanf 실행 오류 방지

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];

typedef struct AddressList { //주소록을 담고있는 구조체
	char name[10];
	int telephone;
	char adress[100];
	int birthday;
}AddressList;

typedef struct DListNode { //메뉴의 노드
	element data; //메뉴 정보(추가, 삭제, 검색, 조회 등등)
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode;

typedef struct AddressListNode { //주소록 노드
	AddressList addressList;
	struct AddressListNode* llink;
	struct AddressListNode* rlink;
}AddressListNode;

DListNode* current; //메뉴의 현재 노드
AddressListNode* currentAddressNode; //주소록의 현재 노드

void init(DListNode* phead) { //메뉴 노드 초기화
	phead->llink = phead;
	phead->rlink = phead;
}

void init_addressListNode(AddressListNode* phead) { //주소록 노드 초기화
	phead->llink = phead;
	phead->rlink = phead;
}

void print_DList(DListNode* phead) { //메뉴 노드 전체 출력
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) { 
		if (p == current) //메뉴노드인 p가 다시 원래의 노드로 돌아오기 전까지 노드의 오른쪽으로 계속 한칸씩 이동할것
			printf("<-| #%s# |->", p->data);
		else
			printf("<-| %s |->", p->data);
	}
	printf("\n");
}

void print_address(AddressListNode* phead) { //주소록 전체 출력
	AddressListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("성명: %s	전화번호: %d	주소: %s	생년월일: %d\n",p->addressList.name,p->addressList.telephone,p->addressList.adress,p->addressList.birthday);//출력문
		printf("\n");
	}
}

void search(AddressListNode* phead) {
	AddressListNode* p;
	element search; //입력받을 값을 저장할 변수

	printf("조회할 성명을 입력하세요 : ");
	scanf("%s", &search);
	for (p = phead->rlink; p != phead; p = p->rlink) {
		if (strcmp(search, p->addressList.name) == 0) { //strcmp()를 이용해 입력받은 문자열과 비교
			printf("성명: %s	전화번호: %d	주소: %s	생년월일: %d\n", p->addressList.name, p->addressList.telephone, p->addressList.adress, p->addressList.birthday);//출력문
			printf("\n");
		}
	}
}

void dinsert(DListNode* before, element data) { //메뉴 노드 삽입
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
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
	scanf("%s", &newnode->addressList.name); //새로 생성된 노드의 주소록 구조체에 저장
	printf("전화번호를 입력하세요: ");
	scanf("%d", &newnode->addressList.telephone);
	printf("주소를 입력하세요: ");
	scanf("%s", &newnode->addressList.adress);
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
		ddelete(head, removed); //재귀함수를 이용해 주소록의 이름과 입력받은 이름이 일치할때까지 반복
	}
	return;
}


int main(void) { //메인함수 시작
	char input; //입력받은 명령을 저장할 변수
	DListNode* menu = (DListNode*)malloc(sizeof(DListNode));
	AddressListNode* list = (AddressListNode*)malloc(sizeof(AddressListNode));
	init(menu);
	init_addressListNode(list);
	//메뉴, 주소록 노드 생성 및 초기화

	dinsert(menu, "주소록 출력");
	dinsert(menu, "주소록 검색");
	dinsert(menu, "주소록 삭제");
	dinsert(menu, "주소록 추가");
	//메뉴 삽입

	current = menu->rlink; 
	currentAddressNode = list->rlink;
	print_DList(menu);

	do { //q가 입력되지 않는한 계속 반복해서 실행할것
		printf("\n명령어를입력하시오(<,>,e,q):");
		input = getchar(); //입력받은 첫번째 문자를 input에 넣기
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

		//e가 입력되었을때
		else if (input == 'e') { //현재 current의 내용물에 따라 해당 함수 실행
			if (strcmp(current->data,"주소록 추가") == 0){
				add(list);
			}
			
			else if (strcmp(current->data,"주소록 삭제") == 0) {
				element removed; //제거할 노드를 입력받을 변수
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
		print_DList(menu); //작업이 끝나면 다시 메뉴화면 출력
		getchar();
	} while (input != 'q');

	free(menu); //종료하기전에 모든 자료 제거
	free(list);
	return 0;
}
