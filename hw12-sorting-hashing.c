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

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);  // �ʱ�ȭ �Լ�
int freeArray(int *a); // �޸� ��ü �Լ�
void printArray(int *a); // ��� �Լ�

int selectionSort(int *a); // ���� ����
int insertionSort(int *a); // ���� ����
int bubbleSort(int *a); // ���� ����
int shellSort(int *a); // �� ����
/* recursive function���� ���� */
int quickSort(int *a, int n); // �� ����


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command; // ������ ���� ����
	int *array = NULL; // �迭 null ��
	int *hashtable = NULL; // �ؽ����̺� null�� 
	int key = -1; // Ű�� 
	int index = -1; // �ε��� ��

	srand(time(NULL)); // ���� �Լ� 
    printf("[----- [�����] [2018038099] -----]");
    
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
		scanf(" %c", &command); // ������ ���� �Է� ����

		switch(command) {
		case 'z': case 'Z':
			initialize(&array); // �迭 �ʱ�ȭ 
			break;
		case 'q': case 'Q':
			freeArray(array); // �޸� ����
			break;
		case 's': case 'S':
			selectionSort(array); // ���� ����
			break;
		case 'i': case 'I':
			insertionSort(array); // ���� ����
			break;
		case 'b': case 'B':
			bubbleSort(array); // ���� ����
			break;
		case 'l': case 'L':
			shellSort(array); // �� ����
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE); // �� ����
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable); // �ؽ�
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable); // �ؽ����̺� �迭 ��� 
			index = search(hashtable, key); // �ε����� ã�� Ű��
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array); // �迭 ��� 
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a) // �ʱ�ȭ �Լ�
{
	int *temp = NULL; // temp�� null ��

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) { // a�� null�̸�
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // �����޸� �Ҵ�
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a; // temp�� *a��

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a) // �޸� ���� �Լ� 
{
	if(a != NULL) // a�� null �� �ƴϸ� 
		free(a); // �޸����� 
	return 0;
}

void printArray(int *a) // ��� �Լ� 
{
	if (a == NULL) { // a�� null �̸�
		printf("nothing to print.\n"); // ���
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // �迭 �ƽ��� ��ŭ �ݺ� 
		printf("a[%02d] ", i); // ���
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // �迭 �ƽ��� ��ŭ �ݺ� 
		printf("%5d ", a[i]); // ��� 
	printf("\n");
}


int selectionSort(int *a) // ���� ���� �Լ� 
{
	int min; // ������ ���� ���� 
	int minindex; // ������ ���� ����
	int i, j; // ������ ���� ����

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // a���

	for (i = 0; i < MAX_ARRAY_SIZE; i++) //  max�� ��ŭ �ݺ�
	{
		minindex = i; // minindex�� i��
		min = a[i]; // min�� a[i]��
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //  max�� ��ŭ �ݺ�
		{
			if (min > a[j]) // a[j]�� min���� ������
			{
				min = a[j]; // min�� a[j]��
				minindex = j; //minindex�� j�� 
			}
		}
		a[minindex] = a[i]; // a[i]�� ���� 
		a[i] = min; // min�� ���� 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // ��� 
	return 0;
}

int insertionSort(int *a) // ���� ���� �Լ� 
{
	int i, j, t; // ������ ���� ���� 

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // ��� 

	for(i = 1; i < MAX_ARRAY_SIZE; i++) // �ƽ��� ��ŭ �ݺ� 
	{
		t = a[i]; // t�� a[i]��
		j = i; // j�� i��
		while (a[j-1] > t && j > 0) // a[j-1]�� t���� ũ�鼭 j�� 0�� �ƴϸ� �ݺ� 
		{
			a[j] = a[j-1]; // a[j]�� a[j-1]�� ���� 
			j--; // j--
		}
		a[j] = t; // t�� ���� 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // ��� 

	return 0;
}

int bubbleSort(int *a) // ���� ���� 
{
	int i, j, t; // ������ ���� ����

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // ���

	for(i = 0; i < MAX_ARRAY_SIZE; i++) // �ƽ��� ��ŭ �ݺ� 
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++) // �ƽ��� ��ŭ �ݺ�
		{
			if (a[j-1] > a[j]) // a[j-1]�� a[j]���� ũ��
			{
				t = a[j-1]; // t�� a[j-1]��
				a[j-1] = a[j]; // a[j-1]�� a[j] ��
				a[j] = t; // a[j]�� t�� ���� 
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //���

	return 0;
}

int shellSort(int *a) // �� ���� 
{
	int i, j, k, h, v; // ������ ���� ����

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // ��� 

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // �ƽ���/2���� h�� 0���� Ŭ������ h/2
	{
		for (i = 0; i < h; i++) // 0���� h���� ���������� �ݺ� 
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // �ƽ�����ŭ �ݺ� 
			{
				v = a[j]; // v�� a[j]�� ����
				k = j; // k�� j�� ���� 
				while (k > h-1 && a[k-h] > v) // k�� h-1���� ũ�鼭  a[k-h]�� v���� ũ�� �ݺ�
				{
					a[k] = a[k-h]; // a[k]d�� a[k-h]��
					k -= h; // k = k - h
				}
				a[k] = v; // a[k]�� v�� ���� 
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // ��� 

	return 0;
}

int quickSort(int *a, int n) // �� ���� �Լ� 
{
	int v, t; // ������ ���� ����
	int i, j; // ������ ���� ����

	if (n > 1) // n�� 1���� ũ�� 
	{
		v = a[n-1]; // v�� a[n-1]��
		i = -1; // -1��
		j = n - 1; // n-1��

		while(1) // �ݺ�
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break; // i�� j���� ũ�ų� ������ ���� 
			t = a[i]; // t�� a[i]��
			a[i] = a[j]; // a[i]�� a[j]��
			a[j] = t; // a[j]�� t��
		}
		t = a[i]; // t�� a[i]��
		a[i] = a[n-1]; //a[i]�� a[n-1]��
		a[n-1] = t; //a[n-1]�� t��

		quickSort(a, i); // a��i�� �����Ŀ� �ѱ�
		quickSort(a+i+1, n-i-1); // a+i+1�� n+i-1�� �Լ��� �ѱ�
	}


	return 0;
}

int hashCode(int key) { // �ؽ� �ڵ� �Լ� 
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht) // �ؽ� �Լ� 
{
	int *hashtable = NULL; // null�� 

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) { 
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // �ƽ� ����ŭ �ݺ�
		hashtable[i] = -1; // -1�� 

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1; // Ű�� -1
	int hashcode = -1; // -1��
	int index = -1; // -1��
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // �ƽ�����ŭ �ݺ�
	{
		key = a[i]; //key�� a[i]��
		hashcode = hashCode(key); //�ؽ��ڵ忡 
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) // -1���̶� ������ 
		{
			hashtable[hashcode] = key; // key�� ���� 
		} else 	{

			index = hashcode; // index�� hashcode�� 

			while(hashtable[index] != -1) // -1�� �ƴϸ� �ݺ�
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; // �������ε����� % �ƽ������� �� 
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; // key�� ���� 
		}
	}

	return 0;
}

int search(int *ht, int key) // ��ġ �Լ� 
{
	int index = hashCode(key); // index�� �ؽ��ڵ� Ű��

	if(ht[index] == key) // ht[index]�� key�� ������
		return index; //index�� ��ȯ

	while(ht[++index] != key) // key�� ���� ������ �ݺ�
	{
		index = index % MAX_HASH_TABLE_SIZE; //index�� index%�ƽ���
	}
	return index; // index�� ��ȯ
}



