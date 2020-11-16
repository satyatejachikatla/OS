//gcc produce_consumer.c -lpthread && ./a.out 20 20
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

#define MAX_BUFFER_SIZE 1000

static int buffer[MAX_BUFFER_SIZE];
static int fill = 0;
static int use = 0;

static int prod_amount,cons_amount;

void put(int i) {
	buffer[fill] = i;
	fill=(fill+1)%MAX_BUFFER_SIZE;
}

int get() {
	int t= buffer[use];
	use = (use+1)%MAX_BUFFER_SIZE;
	return t;
}


sem_t table_emptied;
sem_t table_filled;
sem_t mutex;


void* producer_worker(void * args)  {

	int amount = *(int *)args;

	for(int i =0;i<amount ;i++)	{

		
		sem_wait(&table_emptied);
		sem_wait(&mutex);
			put(i);
			printf("Produce : Table  %d\n",i);
		sem_post(&mutex);
		sem_post(&table_filled);
	}


	return NULL;
}

void* consumer_worker(void * args)  {

	int amount = *(int *)args;
	int t;

	for(int i =0;i<amount ;i++)	{
		sem_wait(&table_filled);
		sem_wait(&mutex);

		t=get(i);
		printf("Consumer : Table  %d\n",t);
		sem_post(&mutex);
		sem_post(&table_emptied);
	}

	return NULL;
}


int main(int argc,char** argv) {

	pthread_t prod_tid,cons_tid;

	prod_amount = atoi(argv[1]);
	cons_amount = atoi(argv[2]);


	sem_init(&table_emptied,0,MAX_BUFFER_SIZE);
	sem_init(&table_filled,0,0);
	sem_init(&mutex,0,1);


	pthread_create(&prod_tid,NULL,producer_worker,&prod_amount);
	pthread_create(&cons_tid,NULL,consumer_worker,&cons_amount);
	pthread_join(prod_tid,NULL);
	pthread_join(cons_tid,NULL);

	printf("Tables Left to Consume\n");
	for(int i=use; i != fill ; i=(i+1)%MAX_BUFFER_SIZE)
	{
		printf("%d ",buffer[i]);
	}
	printf("\n");

	return 0;

}