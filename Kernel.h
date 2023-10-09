#ifndef KERNEL_H_INCLUDED
#define KERNEL_H_INCLUDED



class Kernel{
    private:
        Queue ReadyQueue;  // Ready queue: waiting to be assigned to a CPU. First queue entry
        Queue ExecutingQueue;  // Executing queue: executing on a CPU
        Queue WaitingQueue;  // Waiting queue: waiting for an event
        Queue InterruptQueue; // Processes with interruption
        const int iTOTALPROCESSES = 3; // Total processes
        const int iCPUTIME = 5; //Max cycles per process for RR
    public:
        Kernel();
        ~Kernel();
        // Functions to manage processes
        void createProcesses(int iTotal);
        bool CreateInterruption();
        void Run(int iScheduleType);

        //Scheduling
        void FCFS(); //Scheduling implementing First Come, First Served
        void SJF(); //Scheduling implementing Small Job First
        void RR(); //Scheduling implementing Round Robin

        //Move process to respective queue depending on status
        void MoveToReady(Process *p);
        void MoveToExecuting(Process *p);
        void MoveToWaiting(Process *p);
        void MoveToInterrupted(Process *p);

        //Print queues
        void PrintReadyQ();
        void PrintExecutingQ();
        void PrintWaiting();
        void PrintInterrupted();
};

/*
    Constructor
*/
Kernel::Kernel(){

}

/*
    Destructor
*/
Kernel::~Kernel(){
    // Queue destruction is performed in queue destructor
}

/*
   Create iTotal processes
*/
void Kernel::createProcesses(int iTotal){
    unsigned int iRandom;
    Process *p;

    for(int i = 0; i<iTotal; i++){
        iRandom = rand();
        p = new Process(iRandom);
        MoveToReady(p); //Automatically set process to ready
        cout << "CREATED ";
        p->PrintInfo();
    }
}

bool Kernel::CreateInterruption(){
    int iIntRandom = rand() % 3; // probability of getting and interruption
    if(!iIntRandom){ // if random = 0, interruption was generated
        return true;
    }
    else{
        return false;
    }
}

//Scheduling implementing First Come, First Served
void Kernel::FCFS(){
    Process *p, *pExec, *pWait, *pInt;
    int iTimeExe, iTimeWait, iTimeInterrupt;
    pExec = pWait = pInt = NULL;
    cout << "\n------------------  FCFS Scheduling ------------------" << endl;
    cout << "\tMoving Processes FCFS to Executing Queue..." << endl;
    //Move all processes to Execution queue
    while(!ReadyQueue.isEmtpy()){
        p = ReadyQueue.PopFront();
        MoveToExecuting(p);
    }

    // Processing begins. Each cycle represents a CPU Time cycle.
    while(!ExecutingQueue.isEmtpy() || !WaitingQueue.isEmtpy() || !InterruptQueue.isEmtpy()){ //Loop while at least one queue have processes
        PrintExecutingQ();
        PrintWaiting();
        PrintInterrupted();
        if(!ExecutingQueue.isEmtpy()){ //if not empty
            iTimeExe = ExecutingQueue.CycleFirst(); //Cycle and get the remaining time
            if(CreateInterruption()){ //Randomly create an interruption
                pExec = ExecutingQueue.PopFront(); // pop the process
                pExec->CreateInterruption();
                MoveToInterrupted(pExec); // Move process to interruption list
            }
            else if(iTimeExe == 0){ //If iTimeExe reaches 0, is time to move to next node
                pExec = ExecutingQueue.PopFront(); // remove from executing
                pExec->SetNextPosition(); //move to next cycle
                if(pExec->Terminated()){ // process is done with sequence?
                    delete pExec;
                }
                else{ //not done, so push to waiting
                    MoveToWaiting(pExec); // push to waiting
                }
            }
        }
        if(!WaitingQueue.isEmtpy()){ //if not empty
            iTimeWait = WaitingQueue.CycleFirst(); //Cycle and get the remaining time
            if(iTimeWait == 0){ //If iTimeWait reaches 0, is time to move to next node
                pWait = WaitingQueue.PopFront(); // remove from waiting
                pWait->SetNextPosition(); // move to next cycle
                if(pWait->Terminated()){ // process is done with sequence?
                    delete pWait;
                }
                else{ //not done, so push to executing
                    MoveToExecuting(pWait); // push to executing
                }
            }
        }
        if(!InterruptQueue.isEmtpy()){
            iTimeInterrupt = InterruptQueue.CycleInterrupt();
            iTimeExe = InterruptQueue.GetCurrentTime(); //get last cycle when interruption raised
            if(iTimeInterrupt <= 0){ // Time latency is over, move node where it belonged
                pInt = InterruptQueue.PopFront();
                pInt->IntTerminate();
                if(iTimeExe == 0){ //if interruption occured when executing time was over
                    pInt->SetNextPosition();
                    if(pInt->Terminated()){ // process is done with sequence?
                        delete pInt;
                    }
                    else{ //not done, so push to waiting
                        MoveToWaiting(pInt); // push to waiting
                    }
                }
                else{
                    MoveToExecuting(pInt); // push to executing
                }
            }
        }

        cin.ignore();
    }
}

//Scheduling implementing Small Job First
void Kernel::SJF(){
    Process *p, *pExec, *pWait, *pInt;
    int iTimeExe, iTimeWait, iTimeInterrupt;
    pExec = pWait = pInt = NULL;
    cout << "\n------------------  SJF Scheduling ------------------" << endl;
    cout << "\tMoving Processes SJF to Executing Queue..." << endl;
    //Move all processes to Execution queue
    while(!ReadyQueue.isEmtpy()){
        p = ReadyQueue.GetSmallestJob();
        MoveToExecuting(p);
    }

    // Processing begins. Each cycle represents a CPU Time cycle.
    while(!ExecutingQueue.isEmtpy() || !WaitingQueue.isEmtpy() || !InterruptQueue.isEmtpy()){ //Loop while at least one queue have processes
        PrintExecutingQ();
        PrintWaiting();
        PrintInterrupted();
        if(!ExecutingQueue.isEmtpy()){ //if not empty
            iTimeExe = ExecutingQueue.CycleFirst(); //Cycle and get the remaining time
            if(CreateInterruption()){ //Randomly create an interruption
                pExec = ExecutingQueue.PopFront(); // pop the process
                pExec->CreateInterruption();
                MoveToInterrupted(pExec); // Move process to interruption list
            }
            else if(iTimeExe == 0){ //If iTimeExe reaches 0, is time to move to next node
                pExec = ExecutingQueue.GetSmallestJob(); // remove from executing
                pExec->SetNextPosition(); //move to next cycle
                if(pExec->Terminated()){ // process is done with sequence?
                    delete pExec;
                }
                else{ //not done, so push to waiting
                    MoveToWaiting(pExec); // push to waiting
                }
            }
        }
        if(!WaitingQueue.isEmtpy()){ //if not empty
            iTimeWait = WaitingQueue.CycleFirst(); //Cycle and get the remaining time
            if(iTimeWait == 0){ //If iTimeWait reaches 0, is time to move to next node
                pWait = WaitingQueue.PopFront(); // remove from waiting
                pWait->SetNextPosition(); // move to next cycle
                if(pWait->Terminated()){ // process is done with sequence?
                    delete pWait;
                }
                else{ //not done, so push to executing
                    MoveToExecuting(pWait); // push to executing
                }
            }
        }
        if(!InterruptQueue.isEmtpy()){
            iTimeInterrupt = InterruptQueue.CycleInterrupt();
            iTimeExe = InterruptQueue.GetCurrentTime(); //get last cycle when interruption raised
            if(iTimeInterrupt <= 0){ // Time latency is over, move node where it belonged
                pInt = InterruptQueue.PopFront();
                pInt->IntTerminate();
                if(iTimeExe == 0){ //if interruption occured when executing time was over
                    pInt->SetNextPosition();
                    if(pInt->Terminated()){ // process is done with sequence?
                        delete pInt;
                    }
                    else{ //not done, so push to waiting
                        MoveToWaiting(pInt); // push to waiting
                    }
                }
                else{
                    MoveToExecuting(pInt); // push to executing
                }
            }
        }
        cin.ignore();
    }
}

//Scheduling implementing Round Robin
void Kernel::RR(){
    Process *p, *pExec, *pWait, *pInt;
    int iTimeExe, iTimeWait, iCPUMaxCycles = 0, iTimeInterrupt;
    pExec = pWait = pInt = NULL;
    cout << "\n------------------  RR Scheduling ------------------" << endl;
    cout << "\tMoving Processes RR to Executing Queue..." << endl;
    //Move all processes to Execution queue
    while(!ReadyQueue.isEmtpy()){
        p = ReadyQueue.PopFront();
        MoveToExecuting(p);
    }

    // Processing begins. Each cycle represents a CPU Time cycle.
    while(!ExecutingQueue.isEmtpy() || !WaitingQueue.isEmtpy() || !InterruptQueue.isEmtpy()){ //Loop while at least one queue have processes
        PrintExecutingQ();
        PrintWaiting();
        PrintInterrupted();
        if(!ExecutingQueue.isEmtpy()){ //if not empty
            iTimeExe = ExecutingQueue.CycleFirst(); //Cycle and get the remaining time
            if(CreateInterruption()){ //Randomly create an interruption
                pExec = ExecutingQueue.PopFront(); // pop the process
                pExec->CreateInterruption();
                MoveToInterrupted(pExec); // Move process to interruption list
            }
            else if(iTimeExe == 0){ //If iTimeExe reaches 0, is time to move to next node
                pExec = ExecutingQueue.PopFront(); // remove from executing
                pExec->SetNextPosition(); //move to next cycle
                if(pExec->Terminated()){ // process is done with sequence?
                    delete pExec;
                }
                else{ //not done, so push to waiting
                    MoveToWaiting(pExec); // push to waiting
                }
                iCPUMaxCycles = 0; // Reset max cycles for next process
            }
            else if(iCPUMaxCycles == iCPUTIME){ // Check if max cycles is reached
                pExec = ExecutingQueue.PopFront(); // remove from executing
                MoveToExecuting(pExec); // As burst time is > 0, push process again to executing
                iCPUMaxCycles = 0; // Reset max cycles for next process
            }
            else{
                iCPUMaxCycles++;
            }
        }
        if(!WaitingQueue.isEmtpy()){ //if not empty
            iTimeWait = WaitingQueue.CycleFirst(); //Cycle and get the remaining time
            if(iTimeWait == 0){ //If iTimeWait reaches 0, is time to move to next node
                pWait = WaitingQueue.PopFront(); // remove from waiting
                pWait->SetNextPosition(); // move to next cycle
                if(pWait->Terminated()){ // process is done with sequence?
                    delete pWait;
                }
                else{ //not done, so push to executing
                    MoveToExecuting(pWait); // push to executing
                }
            }
        }
        if(!InterruptQueue.isEmtpy()){
            iTimeInterrupt = InterruptQueue.CycleInterrupt();
            iTimeExe = InterruptQueue.GetCurrentTime(); //get last cycle when interruption raised
            if(iTimeInterrupt <= 0){ // Time latency is over, move node where it belonged
                pInt = InterruptQueue.PopFront();
                pInt->IntTerminate();
                if(iTimeExe == 0){ //if interruption occured when executing time was over
                    pInt->SetNextPosition();
                    if(pInt->Terminated()){ // process is done with sequence?
                        delete pInt;
                    }
                    else{ //not done, so push to waiting
                        MoveToWaiting(pInt); // push to waiting
                    }
                }
                else{
                    MoveToExecuting(pInt); // push to executing
                }
            }
        }
        cin.ignore();
    }
}

// Ready queue.
void Kernel::MoveToReady(Process *p){
    ReadyQueue.PushBack(p);
}

// Executing queue
void Kernel::MoveToExecuting(Process *p){
    p->Execute();
    ExecutingQueue.PushBack(p);
}

// Blocked or waiting queue
void Kernel::MoveToWaiting(Process *p){
    p->Wait();
    WaitingQueue.PushBack(p);
}

// Interrupted queue
void Kernel::MoveToInterrupted(Process *p){
    InterruptQueue.PushBack(p);
}

void Kernel::PrintReadyQ(){
    cout << "\t------------ Ready queue -------------" << endl;
    ReadyQueue.PrintQueue();
}

void Kernel::PrintExecutingQ(){
    cout << "\t------------ Executing queue -------------" << endl;
    ExecutingQueue.PrintQueue();
}

void Kernel::PrintWaiting(){
    cout << "\t------------ Waiting queue -------------" << endl;
    WaitingQueue.PrintQueue();
}

void Kernel::PrintInterrupted(){
    cout << "\t------------ Interrupted queue -------------" << endl;
    InterruptQueue.PrintQueue();
}

/*
    Runs the kernel
*/
void Kernel::Run(int iScheduleType){
    // Perform all kernel configurations, manages the process queue
    // First create iTOTALPROCESSES processes and move them to ready
    createProcesses(iTOTALPROCESSES);
    // Schedule processes using different approaches
    switch(iScheduleType){
        case 1: FCFS(); break;
        case 2: SJF(); break;
        case 3: RR(); break;
    }
}

#endif // KERNEL_H_INCLUDED
