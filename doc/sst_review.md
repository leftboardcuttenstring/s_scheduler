# Foreword
You can see the SST project following the link: https://github.com/QuantumLeaps/Super-Simple-Tasker/  
  
# Global architecture
`dbc_assert.h` consists of a lot of basic definitions what're used in source files
SST provides to you a fucntional for:
1. Changing the module's name;
2. Checking the main assesrtionts about hardware parameters and task parameters (existion, usage and etc.);
3. Creating the queue of processing tasks;
4. Doing some arbitration between all of these tasks, what're storing in the queue

## Structure  
### Modules  
SST contains a lot of modules. The module within the framework of the topic of SST - is every .c-file with
appropriate to it .h-file. `main.c` - is a module, `sst.c` is a module too. And looking ahead, SST provides
some functions for debugging - they can show messages about errors in concrete modules. So, there's a global
'list' of modules
  
`DBC` - is a system (what's described in `dbc_assertionb.h`, as far as I remember) for debugging and showing
some debug messages about errors during the processing of some task  
DBC includes macroses `DBC_MODULE_NAME`, `DBC_ASSERT`, `DBC_ALLEGE`, `DBC_ERROR`, `DBC_REQUIRE`, `DBC_ENSURE`,
`DBC_INVARIANT` and all of it only for checking of asserting the user about some errors
  
`SST` - the scheduler itself. In repo there're two variations of it: `sst0` and `sst` (first is the scheduler
what's built following the standart BCC0, and the second one - by BCC2)  
  
  
### Tasks  
Within the framework of the topic of SST task is a fucntion. A task must be framed by preconditions and
postconditions. It helps to scheduler to check the execution of tasks at the time of context switching or 
other interruptions
  
  
### The process of handling
The sequence:
1. At the start - some quantity of active tasks
2. Sorting tasks by theirs prioroty
3. Processing 
  

# What interfaces does SST give to ya?
Welp, this question is connected to structure of tasking in SST. At the start, you have to create an object
of the task structure - by your hands, or using some function (in SST you can create a task via `SST_Task_ctor`
function. That will provide to you the way how you can connect functions of daspatching and init to the main
structure's object (yea, im about the main your task in form of structure's object))  
At this moment (at the moment when you call `SST_Task_ctor` function) you need to have dispatch and preparing.
within the terms of that repo it's name is `init` (the function what prepares the execution environment for 
task execution).
What are they?
1. Dispatching fucntion - the main fucntion when you have to code how your process will work;
2. Init function - yes, I said it alreay, that stuff prepares the execution environment for task execution;