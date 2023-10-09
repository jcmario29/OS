#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

/*
    class Process. Stores information of the process. Each one can be paused, run, stopped.
*/

class Process{
    private:
        unsigned int iPID; //Track process by an ID
        string sCode; //the code being executed
        int *iBurstIOTime; // Sequence of Burst-I/O Time. Even positions are burst, odd positions are I/O.
        int iPosTime; // Stores the position of the current state in Burst-I/O Time sequence
        int iSize; // Stores the size of the Burst-I/O Time array.
        bool bInterruptFlag;
    public:
        Process *Next, *Prev; // Points to next process in queue
        PCB proc; //make it public so kernel can have full access
        Interrupt IntBlock; // Process may have an interruption
        Process();
        Process(unsigned int iProcessID);
        ~Process();
        // Run, stop and pause the process
        void Execute(); // Sets process state to executing
        void Wait(); // Sets process state to waiting
        void PrintInfo(); // Print information
        void PrintInterruption(); // Print interruption info
        string TimeArrayToString(); // Returns the sequence as string
        int GetPosition(); // Gets iPosTime
        int GetCurrentTime(); //Gets value at iPosTime
        void SetNextPosition(); // Sets iPosTime + 1
        void DecreaseCurrentTime(); // iBurstIOTime[iPosTime] is decreased
        bool Terminated(); // Returns true if sequence is done
        void IntTerminate(); // terminate interruption
        void CreateInterruption();
        int GetLatency(); // Gets Latency
        void DecreaseLatency();
};

/*
    Constructor. Set all process variables
*/
Process::Process(){
    iBurstIOTime = NULL;
}

/*
    Constructor. Set all process variables
*/
Process::Process(unsigned int iProcessID){
    this->iPID = iProcessID;
    this->proc.setPID(iProcessID);
    this->proc.setExecutionState(READY);
    this->iPosTime = 0;
    this->iSize = 1 + (rand() % 5); //Max 5 spots
    iBurstIOTime = new int[iSize]; // Create the dynamic array size iRand
    for(int i=0; i<iSize; i++){ // Generate burst and IO times randomly
        iBurstIOTime[i] = 1 + (rand() % 10); // Generate value from 1 to 10
    }
    bInterruptFlag = false; // turn off interruption flag
}

/*
    Destructor
*/
Process::~Process(){
    if (iBurstIOTime){ // Delete dynamic array
        delete[] iBurstIOTime;
        iBurstIOTime = NULL;
    }
}

// Returns the sequence as string
string Process::TimeArrayToString(){
    string sReturn;
    for(int i=0; i<iSize; i++){ // Generate burst and IO times randomly
        sReturn += to_string(iBurstIOTime[i]) + " "; // Generate value from 1 to 100
    }
    return sReturn;
}

 // Print information
void Process::PrintInfo(){
    cout << "\tProcess: " << iPID << ".\tBurst-I/O Sequence: " << TimeArrayToString() << endl;
    PrintInterruption();
}

void Process::PrintInterruption(){
    if(bInterruptFlag){
        IntBlock.PrintInfo();
    }
}

// Gets iPosTime
int Process::GetPosition(){
    return iPosTime;
}

//Gets value at iPosTime
int Process::GetCurrentTime(){
    return iBurstIOTime[iPosTime];
}

// Sets process state to executing
void Process::Execute(){
    this->proc.setExecutionState(EXEC);
}

// Sets process state to waiting
void Process::Wait(){
    this->proc.setExecutionState(WAIT);
}

// Sets iPosTime + 1
void Process::SetNextPosition(){
    iPosTime++;
}

// iBurstIOTime[iPosTime] is decreased
void Process::DecreaseCurrentTime(){
    iBurstIOTime[iPosTime]--;
}

// Returns true if sequence is done
bool Process::Terminated(){
    if(iPosTime == iSize){
        return true;
    }
    else{
        return false;
    }
}

// Randomly create interruption
 void Process::CreateInterruption(){
    bInterruptFlag = true; // Raise interruption flag
    IntBlock.Init(iPID); // Create new data for interruption
 }

 //Gets latency
int Process::GetLatency(){
    return IntBlock.GetLatency();
}

// Decrease Latency
void Process::DecreaseLatency(){
    IntBlock.DecreaseLatency();
}

// set Interrupt flag to false
void Process::IntTerminate(){
    bInterruptFlag = false; // turn off interruption flag
}

#endif // PROCESS_H_INCLUDED
