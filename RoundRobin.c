#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TASK{
    char* id;
    int runtime;
    int initialRuntime;
    int compTime;
    int visited;
    struct TASK* next;
} Task;


typedef struct  {
    Task* head;
    Task* tail;
    int size;
}Queue;


int idleTime = 0;


Queue* copyQueue(Queue* queue) {
    Queue* copy = (Queue*) malloc(sizeof(Queue));
    copy->head = NULL;
    copy->tail = NULL;
    copy->size = 0;

    Task* current = queue->head;

    while (current != NULL) {
        Task* taskCopy = (Task*) malloc(sizeof(Task));
        taskCopy->id = strdup(current->id);
        taskCopy->runtime = current->runtime;
        taskCopy->initialRuntime = current->initialRuntime;
        taskCopy->compTime = current->compTime;
        taskCopy->visited = current->visited;
        taskCopy->next = NULL;

        if (copy->tail == NULL) {
            copy->head = taskCopy;
            copy->tail = taskCopy;
        } else {
            copy->tail->next = taskCopy;
            copy->tail = taskCopy;
        }

        copy->size++;
        current = current->next;
    }

    return copy;
}
void sort(Queue* queue)
{
Task **pp, *this;

    if (!queue->head ){
        fprintf(stderr, "OMG Struct is empty\n");
        return;
       }

        for(pp = &queue->head; this = *pp; pp = &(*pp)->next){
        Task *other = this->next;
            if (!this->next) break;
            if (this->compTime > other->compTime) continue;
            *pp = other;              
            this->next = other->next; 
            other->next = this;       
        }
return;
}

void bigsort(Queue* queue){
	if(queue-> head == NULL || queue-> head->next == NULL)return;
	
	for(int i=0;i<queue->size+1;i++){
		if(queue-> head -> compTime > queue-> head->next->compTime ){
			Task* temp = queue-> head->next;
			queue-> head->next=temp->next;
			temp->next=queue-> head;
			queue-> head=temp;
		}
		Task* curr = queue-> head->next;
		Task* nextT = curr-> next;
		Task* prevT = queue-> head;
		while(nextT != NULL){
			if(nextT->compTime >= curr->compTime){
				prevT=curr;
				curr=nextT;
				nextT=nextT->next;	
				continue;
			}
			curr->next = nextT->next;
			nextT->next = curr;
			prevT->next = nextT;
			
			prevT=nextT;
			nextT= curr->next;		
		}
	}
}

void addTask(Queue *taskList,char* id,int rt, int initrt,int comptime){
	Task* newTask = (Task*)malloc(sizeof(Task));		
	newTask->id=id;
	newTask->runtime = rt;
	newTask->initialRuntime = initrt;
	newTask->compTime = comptime;
	newTask->visited=0; // visited 0 yapıldı.
	newTask -> next = NULL;
	
	if(taskList->size == 0){
		taskList -> head = newTask;	
		taskList -> tail = newTask;
		taskList -> size++;
	}
	else{
		Task* curr = taskList->head;
		
		while(curr->next != NULL){
			curr = curr->next;
		}
		curr->next = newTask;
		taskList->size++;
		taskList->tail = newTask;
	}
}

void addCompletedTask(Queue *taskList, Queue *taskCompleted, char *id){
		Task* curr = taskList->head;	
		Task* prev = curr;
		if(curr->next == NULL){
			int iR = curr->initialRuntime;
			int cT = curr->compTime;
			free(curr);
			taskList->size--;
			taskList->head = NULL;
			addTask(taskCompleted, id, 0, iR, cT);
			return;
		}
		for(int i=0; i < taskList->size ; i++){
			
			if(strcmp(curr->id, id)==0){
				if(curr == taskList -> head){ // if curr = head
					taskList->head = curr->next;
					addTask(taskCompleted, id, 0, curr->initialRuntime, curr->compTime);
					taskList->size--;				
					break;
				}
				else if(curr->next == NULL){ //tail
					prev->next = NULL;
					taskList->tail = prev;
					addTask(taskCompleted, id, 0, curr->initialRuntime, curr->compTime);
					taskList->size--;
					break;
				}
				else{
					prev->next = curr->next;
					addTask(taskCompleted, id, 0, curr->initialRuntime, curr->compTime);
					taskList->size--;
				}
			}
			prev = curr;
			curr = curr->next;		
		}
		
}
void deleteTaskandAdd(Queue *taskList){
		Task* curr = taskList->head;	
		if(curr->next == NULL){
			curr = taskList->head;
		}
		else{
			taskList->head = curr->next;
			taskList->tail->next = curr;
			taskList->tail = curr;
			curr->next = NULL;
		}		
}
void execution(Queue *taskList, Queue *taskCompleted, int k){
	Task* temp = taskList->head;
	if(temp == NULL) {
		idleTime += k;
		return;
	}

	int count=0;
	for(int i=0; i < k; i++){
		temp->runtime--;
		count++;
		OIU(taskList);
		if(temp->runtime == 0){
			if(taskList->head->next == NULL){
				temp = taskList->head;
				printf(" Task %s is done with %d completition time.\n", temp->id, temp->compTime);
				addCompletedTask(taskList,taskCompleted,temp->id);
				idleTime += k-count;
				break;
			}
			else{
				printf(" Task %s is done with %d completition time.\n", temp->id,  temp->compTime);
				addCompletedTask(taskList,taskCompleted,temp->id);
				temp = temp->next;
			}
		}
		else{
			if(temp->next == NULL){
				temp = taskList->head;
			}
			else{
				temp = temp->next;
				deleteTaskandAdd(taskList);
			}
		}
	}

}
void OIU(Queue * taskList)
{
	Task* cur = taskList->head;
	
	if(cur == NULL)
		return;
	
	while(cur != NULL)
	{
		cur->compTime++;
		cur = cur->next;		
	}

}
//printing
void printtask(Queue *taskList, int type){
	Task* curr = taskList->head;
	if(curr == NULL){
		return;
	}		
	for(int i=0; i < taskList -> size; i++){
		if(type == 0)
			printf(" %s %d -> ", curr->id, curr->runtime);
		else  
			printf(" %s %d -> ", curr->id, curr->compTime);
		curr = curr->next;			
	}	
	printf("\n");
}

int main(int argc,char* argv[]){
	Queue* taskList = (Queue*)malloc(sizeof(Queue)); // uncompilted tasks
	Queue* taskListCompleted = (Queue*)malloc(sizeof(Queue)); // completed tasks
	int quit = 0;
	char choice[100]; 
	int totalTime = 0; // system time
	
	while(quit == 0){
		scanf("%s", choice);
		
		if (strcmp(choice,"SNT") == 0) {	
			getchar(); // boşluk için	
			int runtime;
			char* id;
			int control = 0;
			 
			id = malloc(1);
			id[0] = '\0';
		    char c;
		   
		    while (( c = getchar()) != '\n' ) {
			if ( c == EOF || c == ' ') break;
				int size = strlen(id);
				id = realloc( id, size+2 );
				id[size] = c;
				id[size+1] = '\0';
				control = 1;
		    }		
			if(scanf("%d",&runtime) == 1){	
				printf("Command is: %s %s %d\n", choice, id, runtime);
				addTask(taskList,id,runtime, runtime, 0);			
			}
		}
		else if(strcmp(choice,"S") == 0){
			int k;
			getchar();
			if(scanf("%d",&k) == 1){	 
				printf("Command is: %s %d\n", choice, k);
				printf(" Running for %d units...\n",k);
				execution(taskList,taskListCompleted,k);
				totalTime+=k;
			}
			getchar();
		}		
		else if(strcmp(choice,"DST") == 0){
			printf("Command is: %s\n", choice);
			printf(" System time is: %d \n", totalTime);
		}
		else if(strcmp(choice,"DTIT")  == 0){
			printf("Command is: %s\n", choice);
			printf(" Idle time is: %d \n", idleTime);
		}
		else if(strcmp(choice,"DIMRCT")  == 0){
			printf("Command is: %s\n", choice);
			if(taskListCompleted->head != NULL){
				printf(" Task id is: %s, initial runtime is: %d, completition time is: %d \n",taskListCompleted->tail->id, taskListCompleted->tail->initialRuntime, taskListCompleted->tail->compTime);
			}else{
				printf(" There is no completed task in queue!\n");
			}
		}
		else if(strcmp(choice,"DCTQ")  == 0){
			printf("Command is: %s\n", choice);
			char* filename = malloc(sizeof(char) * 256);
			scanf(" %ms", &filename);
			FILE *dosya;	
	   		Task* current = taskListCompleted->head;
	   		int Csize = 0;
	   		while(current != NULL){
	   			current = current->next;
	   			Csize++;
	   		}
	   		dosya = fopen(filename, "w");
	   		Queue* copy = copyQueue(taskListCompleted);
	   		bigsort(copy);
	   		Task* current2 = copy->head;
	   		char * str= malloc(sizeof(char) * 256);
	   		
	   		for (int i = 0; i < Csize; i++) {
	   		  	sprintf(str, "Task id: %s , Initial Runtime: %d Completition Time: %d \n", current2->id, current2->initialRuntime,current2->compTime);
	   		  	fprintf(dosya, "%s", str);
				current2 = current2->next;
	    	}
	    	fclose(dosya);
	    	printf(" Writing in file named %s... Done!\n", filename);
									
		}
		else if(strcmp(choice,"ECTS")  == 0){ 
			printf("Command is: %s\n", choice);
			Task* current = taskListCompleted->head;
			if(current==NULL){
				printf(" Completed Task Queue is already empty!\n");
			}
			else{
				Task* next;
				while(current != NULL){	
					next = current->next;
					free(current->id);		
					free(current);
					current = next;
				}
				taskListCompleted->head = NULL;
				taskListCompleted->size=0;
				printf(" Completed Task Queue is emptied.\n");
			}

		}
		else if(strcmp(choice,"QUIT")  == 0){
			printf("Command is: %s\n", choice);
			quit = 1;
			return 0;
		}
		else{
			printf(" Wrong command!\n");
		}

		if(taskList->head != NULL){	
			printf(" Task List: ");
			printtask(taskList, 0);
		}
		else{
			printf(" TaskList is empty.\n");
		}
		if(taskListCompleted->head != NULL){
			printf(" Completed Task Queue: ");
			printtask(taskListCompleted, 1);
		}
		else{
			printf(" Completed Task Queue is empty.\n");
		}
		
	}
	return 0;
}
