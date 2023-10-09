#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

class Queue{
    private:
        Process *Head;
    public:
        Queue();
        ~Queue();
        void PushBack(Process *p);
        Process * PopFront();
        void Pop();
        void PrintQueue();
        bool isEmtpy();
        Process *GetSmallestJob();
        int CycleFirst();
        int CycleInterrupt();
        int GetCurrentTime();
};

// Constructor. Set Head to NULL
Queue::Queue(){
    Head = NULL;
}

// Destructor, remove all nodes
Queue::~Queue(){
    while(!isEmtpy()){ //while not empty
        Pop();
    }
    Head = NULL;
}

// Pushes a process to the back of the queue
void Queue::PushBack(Process *p){
    Process *aux = Head;
    p->Next = NULL; // Safe check, make sure next pointer goes to NULL
    p->Prev = NULL; // Safe check, make sure prev pointer goes to NULL
    if(!isEmtpy()){ //if not empty
        while(aux->Next){ //Loop until last node is found
            aux = aux->Next;
        }
        aux->Next = p;
        p->Prev = aux;
    }
    else{
        Head = p;
    }
}

// Pops an element from the queue, returns popped node
Process * Queue::PopFront(){
    Process *aux = Head;
    if(!isEmtpy()){ //If queue is not empty
        Head = Head->Next;
        if(Head){
            Head->Prev = NULL;
        }
        aux->Next = NULL; // Safe check
        aux->Prev = NULL;
    }
    return aux;
}

// Pops the front of the queue, deleting this node
void Queue::Pop(){
    Process *aux = Head;
    if(!isEmtpy()){ //If queue is not empty
        Head = Head->Next;
    }
    delete aux;
}

// Prints the queue without deleting any node
void Queue::PrintQueue(){
    Process *aux = Head;
    if(!isEmtpy()){ //Check if not empty
        while(aux){
            aux->PrintInfo();
            aux = aux->Next;
        }
    }
    else{
        cout << "\t*** Queue empty ***" << endl;
    }
}

//Returns the node with smallest job
Process * Queue::GetSmallestJob(){
    Process *aux, *temp, *prev;
    aux = temp = prev = Head;
    if(!isEmtpy()){
        while(aux){ //loop while aux is different than NULL
            if(aux->GetCurrentTime() < temp->GetCurrentTime()){
                temp = aux;
            }
            aux = aux->Next;
        }
        if(temp == Head){ //if temp is the first node
            Head = Head->Next;
            if(Head){
                Head->Prev = NULL;
            }
        }
        else if(temp->Next == NULL){ //if temp is the last node
            temp->Prev->Next = NULL;
        }
        else{ // General case
            temp->Prev->Next = temp->Next;
            temp->Next->Prev = temp->Prev;
        }
        temp->Prev = NULL;
        temp->Next = NULL;
    }
    return temp;
}

// checks if queue is empty
bool Queue::isEmtpy(){
    if(Head){
        return false;
    }
    else{
        return true;
    }
}

// Decrease time for the head of the queue
int Queue::CycleFirst(){
    if(!isEmtpy()){
        Head->DecreaseCurrentTime();
        return Head->GetCurrentTime();
    }
    else{
        return -1; // Return error
    }
}

// Decrease time of latency
int Queue::CycleInterrupt(){
    if(!isEmtpy()){
        Head->DecreaseLatency();
        return Head->GetLatency();
    }
    else{
        return -1; // Return error
    }
}

int Queue::GetCurrentTime(){
    return Head->GetCurrentTime();
}

#endif // QUEUE_H_INCLUDED
