/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  School of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //큐의 최대 크기

typedef char element; // element 자료형 선언
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //큐의 데이터 저장용 배열
	int front, rear;//큐의 front와 rear 위치 저장용 변수
}QueueType; // QueueType 자료형 선언


QueueType *createQueue(); //큐를 동적할당하는 함수
int freeQueue(QueueType *cQ); //큐를 할당 해제하는 함수
int isEmpty(QueueType *cQ); //큐가 비어있으면 1을 반환, 아니면 0을 반환하는 함수
int isFull(QueueType *cQ); //큐가 가득 차 있다면 1, 아니면 0을 반환하는 함수
void enQueue(QueueType *cQ, element item); //큐에 데이터를 넣는 함수
void deQueue(QueueType *cQ, element* item); //큐에서 데이터를 꺼내는 함수
void printQ(QueueType *cQ); //큐의 데이터를 출력하는 함수
void debugQ(QueueType *cQ); //큐의 현재 상태와 head, rear위치를 표시하는 함수
element getElement();//사용자 입력을 받는 함수


int main(void)
{
	QueueType *cQ = createQueue(); //큐 cQ 생성
	element data; //사용자 입력 데이터 저장용 변수

	char command; //사용자 명령 저장용 변수

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		//메뉴 출력

		printf("Command = ");
		scanf(" %c", &command); //사용자 명령을 입력 받음

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data); //i, I를 입력 받으면 큐에 입력받은 데이터 추가
			break;
		case 'd': case 'D':
			deQueue(cQ, &data); //d, D를 입력 받으면 큐의 데이터 하나 제거
			break; 
		case 'p': case 'P':
			printQ(cQ); //p, P입력 받으면 현재 큐의 데이터 모두 출력
			break;
		case 'b': case 'B'://b,B 입력 받으면 디버깅 실행
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ); //q, Q 누르면 일단 큐를 할당 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //명령어 이외의 문자 입력시 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); //q, Q 입력 받았을 시 반복 종료


	return 1;
}

QueueType *createQueue() //큐를 동적할당하는 함수
{
	QueueType *cQ; //큐 포인터 생성
	cQ = (QueueType *)malloc(sizeof(QueueType)); //큐 포인터에 동적할당
	cQ->front = 0;
	cQ->rear = 0;

	//큐의 front와 rear를 0으로 초기화

    for( int i = 0; i < MAX_QUEUE_SIZE; i++) cQ->queue[i] = '\0'; //큐의 데이터 저장용 배열 초기화
	return cQ; //cQ 주소 반환
}

int freeQueue(QueueType *cQ) //큐를 할당 해제하는 함수
{
    if(cQ == NULL) return 1; //만약 이미 큐가 할당 되어 있지 않다면 아래 과정 생략
    free(cQ); //cQ 할당 해제
    return 1;
}

element getElement() 
{
	element item; //사용자 입력 데이터 저장용 변수
	printf("Input element = "); 
	scanf(" %c", &item); //사용자 입력 받기
	return item; //사용자 입력 데이터 반환
}


/* complete the function */
int isEmpty(QueueType *cQ) //큐가 비어있으면 1을 반환, 아니면 0을 반환하는 함수
{

    if(cQ->front == 0 && cQ->rear == 0)    return 1; 
	//만약 큐의 front와 rear가 같은 위치 가리키고 이쓰면 1반환

    else return 0; // 아니면 0반환
}

/* complete the function */
int isFull(QueueType *cQ) //큐가 가득 차 있다면 1, 아니면 0을 반환하는 함수
{

    int n = cQ->rear; //rear의 값 임시 저장용 변수

    n = (n+1)%MAX_QUEUE_SIZE; // 만약 rear의 바로 다음 위치가

    if(n == cQ->front) return 1; //front라면 1반환

    else return 0; //아니라면 0반환
}


/* complete the function */
void enQueue(QueueType *cQ, element item) //큐에 데이터를 넣는 함수
{

    if(isFull(cQ) == 0){//큐가 가득 차 있지 않다면
          cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		  //rear의 위치를 다음 위치로 이동
       
          cQ->queue[cQ->rear] = item; //이동된 rear의 위치에 데이터 넣기



    }

    else        printf("큐가 가득 차 있습니다\n"); //큐가 가득 차 있다면 출력
    
}

/* complete the function */
void deQueue(QueueType *cQ, element *item) //큐에서 데이터를 꺼내는 함수
{
    
    if(isEmpty(cQ) == 1) printf("큐가 비어 있습니다\n"); //큐가 비어있으면 출력

    else{ //아니면


       cQ->front = (cQ->front + 1) %MAX_QUEUE_SIZE; //front의 위치를 다음 위치로 이동하고

       cQ->queue[cQ->front] = '\0'; // front 위치의 데이터를 초기화
    }

}


void printQ(QueueType *cQ) //큐의 데이터를 출력하는 함수
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;
	//first와 last는 각각 front와 rear의 다음 위치를 가리키게 함

	printf("Circular Queue : ["); //양식

	i = first; //큐를 카리키는 새로운 변수 i 를 first의 위치로 맞춤
	while(i != last){ //i가 last가 아닐 동안
		printf("%3c", cQ->queue[i]); //(3칸으로 맞춰서) 큐의 i번째 데이터 출력
		i = (i+1)%MAX_QUEUE_SIZE; //i를 큐의 다음위치로 이동
	}
	printf(" ]\n");//양식
}


void debugQ(QueueType *cQ) //큐의 현재 상태와 head, rear위치를 표시하는 함수
{

	printf("\n---DEBUG\n");//양식
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)//큐의 크기 만큼 반복
	{
		if(i == cQ->front) {//만약 현재 반복수 i가 front의 값과 같다면
			printf("  [%d] = front\n", i); //front는 i의 위치와 같다고 출력
			continue;//아래 과정 생략
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);//현재 반복수 i의 위치에 있는 큐의 데이터 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //현재 front와 rear의 값 출력
}

