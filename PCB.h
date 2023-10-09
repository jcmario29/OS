#ifndef PCB_H_INCLUDED
#define PCB_H_INCLUDED

enum STATUS{READY = 0, EXEC, WAIT, INT};


class PCB{ //proc
    private:
        unsigned int iPID; //Process ID
        unsigned int iExecutionState;
        unsigned int iInstructionPointer; //PC
        unsigned int iStackPointer;
        // missing registers, maybe a struct?
        unsigned int iHeapPointer;
        PCB *ParentPointer;
        PCB *ChildrenPointer; // Handle several childs
        string sName;
        string sPrivileges; // kernel, user
        // Many other fields (TO DO..)
    public:
        PCB();
        ~PCB();
        //get/set methods, mostly all will be implemented later
        void setPID(unsigned int iProcessID);
        void setExecutionState(unsigned int iES);
        void setInstructionPointer(unsigned int iIP);
        void setStackPointer(unsigned int iSP);
        void setHeapPointer(unsigned int iHP);
        void setParentPointer(PCB *PP);
        void setNewChildPointer(PCB *CHP);
        void setName(string sName);
        void setPrivileges(string sPrivileges);

        unsigned int getPID();
        unsigned int getExecutionState();
        unsigned int getInstructionPointer();
        unsigned int getStackPointer();
        unsigned int getHeapPointer();
        PCB *getParentPointer();
        PCB *getChildPointer(unsigned int iChildID);
        string getName();
        string getPrivileges();
};

//Constructor
PCB::PCB(){

    //Probably other functionality for next updates
}

//Destructor
PCB::~PCB(){

}

// Sets PID
void PCB::setPID(unsigned int iProcessID){
    iPID = iProcessID;
}

// Sets execution status
void PCB::setExecutionState(unsigned int iES){
    this->iExecutionState = iES;
}

unsigned int PCB::getPID(){
    return this->iPID;
}

#endif // PCB_H_INCLUDED
