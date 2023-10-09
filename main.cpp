#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <queue>


using namespace std;

#include "PCB.h"
#include "Interupt.h"
#include "Process.h"
#include "Queue.h"
#include "Kernel.h"
#include "Bios.h"


int main()
{
    BIOS oBIOS;
    oBIOS.Run();
    return 0;
}
