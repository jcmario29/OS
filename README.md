OS simulator

1. Defining basic clases.

Base class BIOS, performs hardware checking. If everything OK, it thens
call the Kernel object.

Base class Kernel, contains several methods to handle processes, which will
be stored in a priority queue. The priority queue will decide which 
processes will be executed first. This will be considered in a future
release to be another class.
The Run() method is the starting point for the kernel class.
Other considerations can be taken place in future versions (e.g. memory
handling, devices handling, etc)

Base class Process, contains all information regarding a single process.
(name, id, user that called it, image path, type, etc). Each Process can
be run, pause and stopped.

**********************************************************************
2. Update. Feb, 25

Added functionality to kernel class:
a) Cycle until user shuts down computer
b) Create random processes (with unique id)
c) Add queues for procs (one for each state supported)
d) When shuting down, delete all processes
e) Deleted unused methods and added new ones to handle processes.
f) When process is created, automatically store them in Ready queue.

Thoughts: Probably change queue for list, so we can print the status
queues without popping.


Updated the process class:
a) Removed redundant attributes (moved to pcb)
b) Added a pcb object. - Originally thought of a separated class, but
	at the end is a simulation, so no real processes are created.

Created PCB (proc) class:
a) Added some of the information for the PCB. Some data were left
	behind, eg. Registers values. Struct to handle this in the
	future?
b) Added STATUS enumeration

**********************************************************************
3. Update. Apr, 11

Added functionallity for three types of scheduling: FCFS, SJR, RR.

Updated Process class:
- Added a dynamic array to store Burst Time and I/O Time, where even
	positions are the Burst times, the odd positions are the I/O.
- Added an integer to control the position on the burst-IO time array.
- Added an integer to store the size of the array.
- Added new functions to print process info, retrieve current position,
	Current time, set states, etc

Updated Kernel class:
- Added functions to handle FCFS, SJR and RR scheduling methods
- n processes will be created for each scheduling method and display
	the behaviour. This can be changed with constant defined.
- FCFS serves processes Burst time as they come.
- SJF gets the smalles job and process it first. This is checked everytime
	a process moves to executing queue
- RR serves processes as they come, assign a constant CPU "time" for each
	process. If CPU "time" is over and process is not done with burst
	time, it will be moved to the back of the executing queue again.

Added Queue class to handle the different queues.

**********************************************************************
4. Update. May, 2

Added functionallity for interrupts handling

New class Interrupt:
- Stores the interrupt information

Updated Process class:
- Added Interrupt object to process
- Interrupts are created randomly. 
- Process may or may not have an interruption

Updated kernel class:
- Added a queue for processes interrupted
- When an interruption occurs, process is sent to interrupt queue
	and waits x cycles (latency). Then it comes back to the
	process manager and continues.
- The interruption process is implemented for all three scheduling
	types
- Interruptions only occur when process is executing
