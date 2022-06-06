/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);  // 초기화 함수
int freeArray(int *a); // 메모리 해체 함수
void printArray(int *a); // 출력 함수

int selectionSort(int *a); // 선택 정렬
int insertionSort(int *a); // 삽입 정렬
int bubbleSort(int *a); // 버블 정렬
int shellSort(int *a); // 셀 정렬
/* recursive function으로 구현 */
int quickSort(int *a, int n); // 퀵 정렬


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command; // 문자형 변수 선언
	int *array = NULL; // 배열 null 값
	int *hashtable = NULL; // 해시테이블 null값 
	int key = -1; // 키값 
	int index = -1; // 인덱스 값

	srand(time(NULL)); // 랜덤 함수 
    printf("[----- [장원도] [2018038099] -----]");
    
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 문자형 변수 입력 받음

		switch(command) {
		case 'z': case 'Z':
			initialize(&array); // 배열 초기화 
			break;
		case 'q': case 'Q':
			freeArray(array); // 메모리 해제
			break;
		case 's': case 'S':
			selectionSort(array); // 선택 정렬
			break;
		case 'i': case 'I':
			insertionSort(array); // 삽입 정렬
			break;
		case 'b': case 'B':
			bubbleSort(array); // 버블 정렬
			break;
		case 'l': case 'L':
			shellSort(array); // 셀 정렬
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE); // 퀵 정렬
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable); // 해싱
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable); // 해싱테이블 배열 출력 
			index = search(hashtable, key); // 인덱스에 찾는 키값
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array); // 배열 출력 
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a) // 초기화 함수
{
	int *temp = NULL; // temp에 null 값

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) { // a가 null이면
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // 동적메모리 할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a; // temp에 *a값

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a) // 메모리 해제 함수 
{
	if(a != NULL) // a가 null 이 아니면 
		free(a); // 메모리해제 
	return 0;
}

void printArray(int *a) // 출력 함수 
{
	if (a == NULL) { // a가 null 이면
		printf("nothing to print.\n"); // 출력
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 맥스값 만큼 반복 
		printf("a[%02d] ", i); // 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 맥스값 만큼 반복 
		printf("%5d ", a[i]); // 출력 
	printf("\n");
}


int selectionSort(int *a) // 선택 정렬 함수 
{
	int min; // 정수형 변수 선언 
	int minindex; // 정수형 변수 선언
	int i, j; // 정수형 변수 선언

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // a출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++) //  max값 만큼 반복
	{
		minindex = i; // minindex에 i값
		min = a[i]; // min에 a[i]값
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //  max값 만큼 반복
		{
			if (min > a[j]) // a[j]가 min보다 작으면
			{
				min = a[j]; // min에 a[j]값
				minindex = j; //minindex에 j값 
			}
		}
		a[minindex] = a[i]; // a[i]값 넣음 
		a[i] = min; // min값 넣음 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 출력 
	return 0;
}

int insertionSort(int *a) // 삽입 정렬 함수 
{
	int i, j, t; // 정수형 변수 선언 

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 출력 

	for(i = 1; i < MAX_ARRAY_SIZE; i++) // 맥스값 만큼 반복 
	{
		t = a[i]; // t에 a[i]값
		j = i; // j에 i값
		while (a[j-1] > t && j > 0) // a[j-1]이 t보다 크면서 j가 0이 아니면 반복 
		{
			a[j] = a[j-1]; // a[j]에 a[j-1]값 넣음 
			j--; // j--
		}
		a[j] = t; // t값 넣음 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 출력 

	return 0;
}

int bubbleSort(int *a) // 버블 정렬 
{
	int i, j, t; // 정수형 변수 선언

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++) // 맥스값 만큼 반복 
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++) // 맥스값 만큼 반복
		{
			if (a[j-1] > a[j]) // a[j-1]이 a[j]보다 크면
			{
				t = a[j-1]; // t에 a[j-1]값
				a[j-1] = a[j]; // a[j-1]에 a[j] 값
				a[j] = t; // a[j]에 t값 넣음 
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //출력

	return 0;
}

int shellSort(int *a) // 셀 정렬 
{
	int i, j, k, h, v; // 정수형 변수 선언

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 출력 

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // 맥스값/2부터 h가 0보다 클때까지 h/2
	{
		for (i = 0; i < h; i++) // 0부터 h보다 작을때까지 반복 
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // 맥스값만큼 반복 
			{
				v = a[j]; // v에 a[j]값 넣음
				k = j; // k에 j값 넣음 
				while (k > h-1 && a[k-h] > v) // k가 h-1보다 크면서  a[k-h]가 v보다 크면 반복
				{
					a[k] = a[k-h]; // a[k]d에 a[k-h]값
					k -= h; // k = k - h
				}
				a[k] = v; // a[k]에 v값 넣음 
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 출력 

	return 0;
}

int quickSort(int *a, int n) // 퀵 정렬 함수 
{
	int v, t; // 정수형 변수 선언
	int i, j; // 정수형 변수 선언

	if (n > 1) // n이 1보다 크면 
	{
		v = a[n-1]; // v에 a[n-1]값
		i = -1; // -1값
		j = n - 1; // n-1값

		while(1) // 반복
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break; // i가 j보다 크거나 같으면 멈춤 
			t = a[i]; // t에 a[i]값
			a[i] = a[j]; // a[i]에 a[j]값
			a[j] = t; // a[j]에 t값
		}
		t = a[i]; // t에 a[i]값
		a[i] = a[n-1]; //a[i]에 a[n-1]값
		a[n-1] = t; //a[n-1]에 t값

		quickSort(a, i); // a값i값 퀵정렬에 넘김
		quickSort(a+i+1, n-i-1); // a+i+1값 n+i-1값 함수에 넘김
	}


	return 0;
}

int hashCode(int key) { // 해시 코드 함수 
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht) // 해싱 함수 
{
	int *hashtable = NULL; // null값 

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) { 
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // 맥스 값만큼 반복
		hashtable[i] = -1; // -1값 

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1; // 키값 -1
	int hashcode = -1; // -1깂
	int index = -1; // -1값
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // 맥스값만큼 반복
	{
		key = a[i]; //key에 a[i]값
		hashcode = hashCode(key); //해시코드에 
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) // -1값이랑 같으면 
		{
			hashtable[hashcode] = key; // key값 넣음 
		} else 	{

			index = hashcode; // index에 hashcode값 

			while(hashtable[index] != -1) // -1이 아니면 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; // 증가된인덱스값 % 맥스사이즈 값 
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; // key값 넣음 
		}
	}

	return 0;
}

int search(int *ht, int key) // 서치 함수 
{
	int index = hashCode(key); // index에 해시코드 키값

	if(ht[index] == key) // ht[index]가 key랑 같으면
		return index; //index값 반환

	while(ht[++index] != key) // key랑 같지 않으면 반복
	{
		index = index % MAX_HASH_TABLE_SIZE; //index에 index%맥스값
	}
	return index; // index값 반환
}



