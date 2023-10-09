#ifndef BIOS_H_INCLUDED
#define BIOS_H_INCLUDED

/*
Class BIOS. This class performs the hardware checking, if everything is OK, it runs the kernel.
*/

class BIOS{
    private:
        Kernel FCFSKernel, SJFKernel, RRKernel; // Kernel objects

        bool HardwareCheck();
    public:
        BIOS();
        ~BIOS();
        void Run();
};

/*
    Constructor
*/
BIOS::BIOS(){
    srand(18); //Set random seed, so we can reproduce values
}

/*
    Destructor
*/
BIOS::~BIOS(){

}

/*
    performs a hardware checking
*/
bool BIOS::HardwareCheck(){
    int iRandom = rand()%5 + 1; //Generate a number between 1 - 5.
    if(iRandom == 4){ //Set a random hardware failure. Only if iRandom is 4.
        return false;
    }
    else{
        return true;
    }
}

/*
    performs a hardware checking
*/
void BIOS::Run(){
    if( HardwareCheck() ){ // If hardware check was succesful.
        //FCFSKernel.Run(1);  // Run scheduling FCFS
        //SJFKernel.Run(2); // Run scheduling SJF
        RRKernel.Run(3); // Run scheduling RR
    }
    else{
        cout << "Hardware check failed. Kernel was not initiated" << endl;
    }
}

#endif // BIOS_H_INCLUDED
