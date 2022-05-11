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
		printf("����: %s	��ȭ��ȣ: %d	�ּ�: %s	�������: %d\n",p->addressList.name,p->addressList.telephone,p->addressList.adress,p->addressList.birthday);//��¹�
		printf("\n");
	}
}

void search(AddressListNode* phead) {
	AddressListNode* p;
	element search;

	printf("��ȸ�� ������ �Է��ϼ��� : ");
	scanf("%s", &search);
	for (p = phead->rlink; p != phead; p = p->rlink) {
		if (strcmp(search, p->addressList.name) == 0) {
			printf("����: %s	��ȭ��ȣ: %d	�ּ�: %s	�������: %d\n", p->addressList.name, p->addressList.telephone, p->addressList.adress, p->addressList.birthday);//��¹�
			printf("\n");
		}
	}
}

void dinsert(DListNode* before, element data) {
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	//newnode->data = data; int �� �ƴϹǷ�
	strcpy(newnode->data, data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

//�ּҷ� �߰� �Լ�
void add(AddressListNode* before) {
	AddressListNode* newnode = (AddressListNode*)malloc(sizeof(AddressListNode));
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;

	printf("�̸��� �Է��ϼ���: ");
	scanf("%s", &newnode->addressList.name);
	printf("��ȭ��ȣ�� �Է��ϼ���: ");
	scanf("%d", &newnode->addressList.telephone);
	printf("�ּҸ� �Է��ϼ���: ");
	scanf("%s", &newnode->addressList.adress); //������⸦ �����ؼ� �޴´�
	printf("��������� �Է��ϼ���: ");
	scanf("%d", &newnode->addressList.birthday);
	printf("\n");
}

//�ּҷ� �����Լ�
void ddelete(AddressListNode* head, element removed) {
	if (strcmp(removed, head->addressList.name) == 0) {
		head->llink->rlink = head->rlink;
		head->rlink->llink = head->llink;
		free(head);
		printf("���� �Ǿ����ϴ�\n");
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

	dinsert(menu, "�ּҷ� ���");
	dinsert(menu, "�ּҷ� �˻�");
	dinsert(menu, "�ּҷ� ����");
	dinsert(menu, "�ּҷ� �߰�");

	current = menu->rlink;
	currentAddressNode = list->rlink;
	print_DList(menu);

	do {
		printf("\n��ɾ�Է��Ͻÿ�(<,>,e,q):");
		input = getchar();
		if (input == '<') {
			current = current->llink;
			if (current == menu) //���� head��� ��ĭ �� �����ϰ�
				current = current->llink;
		}
		else if (input == '>') {
			current = current->rlink;
			if (current == menu) //���� head��� ��ĭ �� �����ϰ�
				current = current->rlink;
		}

		//���Ͱ� �ԷµǾ�����
		else if (input == 'e') {
			if (strcmp(current->data,"�ּҷ� �߰�") == 0){
				add(list);
			}
			
			else if (strcmp(current->data,"�ּҷ� ����") == 0) {
				element removed;
				printf("������ �ּҷ��� ������ �Է��ϼ��� :");
				scanf("%s", &removed);
				ddelete(list, removed);
			}
						
			else if (strcmp(current->data, "�ּҷ� �˻�") == 0){
				search(list);
			}

			else if (strcmp(current->data, "�ּҷ� ���") == 0){
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