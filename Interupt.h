#ifndef INTERUPT_H_INCLUDED
#define INTERUPT_H_INCLUDED


/*
    class Interrupt. Stores information of the interruption.
*/

class Interrupt{
    private:
        int iProcessID;
        int iCode; // Interruption code
        int iLatency; // Cycles of Interrupt Latency.
    public:
        Interrupt();
        ~Interrupt();
        void Init(int iProcessID);
        void PrintInfo(); // Print information
        int GetLatency(); // Gets Latency
        void DecreaseLatency();
};

/*
    Constructor. Set all Interrupt variables
*/
Interrupt::Interrupt(){
    iLatency = 0;
    iCode = 0;
}

/*
    Destructor
*/
Interrupt::~Interrupt(){

}

// Get process id
void Interrupt::Init(int iProcessID){
    this->iProcessID = iProcessID;
    iLatency = 2 + (rand() % 10); // Generate value from 2 to 8.
    iCode = 1 + (rand() % 10); // Generate value from 1 to 10
}

 // Print information
void Interrupt::PrintInfo(){
    cout << "\t_____INTERRUPT!! Process " << iProcessID << ": ";
    switch(iCode){
        case 1: cout <<"Integer or floating-point divide by zero"; break;
        case 2: cout <<"Debugger breakpoint"; break;
        case 3: cout <<"Illegal instruction"; break;
        case 4: cout <<"Data misalignment"; break;
        case 5: cout <<"Privileged instruction"; break;
        case 6: cout <<"Access violation"; break;
        case 7: cout <<"Invalid OpCode"; break;
        case 8: cout <<"Bound Range Exception"; break;
        case 9: cout <<"Stack Fault"; break;
        case 10: cout <<"Integer or floating-point overflow"; break;
    }
    cout << ". Latency: " << iLatency <<endl;
}

//Gets latency
int Interrupt::GetLatency(){
    return iLatency;
}

// Decrease Latency
void Interrupt::DecreaseLatency(){
    iLatency--;
}



#endif // INTERUPT_H_INCLUDED
