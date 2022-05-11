#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
#define MAX_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int list[], int n) { //정렬 함수
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) { //배열의 맨 마지막칸은 비워둠
		least = i; //최솟값의 위치를 처음엔 i로 놓고
		for (j = i + 1; j < n; j++) {
			if (list[j] < list[least]) least = j;
		} //i다음 배열부터 n까지 돌아가면서 list의 최솟값보다 더 작은 값이 있을경우 그 값을 최솟값으로 지정
		SWAP(list[i], list[least], temp); //처음 i위치와 최종 least위치를 서로 바꿈
	}
}
int main(void) {
	int i, n;
	int list[MAX_SIZE];
	n = MAX_SIZE;

	srand(time(NULL)); //0부터 100까지의 랜덤 수를 n개 만큼 생성
	for (i = 0; i < n; i++) {
		list[i] = rand() % 100;
	}
	selection_sort(list, n);
	for (i = 0; i < n; i++) //list[]배열 내에 있는 모든값을 출력
		printf("%d ", list[i]);
	printf("\n");
	return 0;
}
