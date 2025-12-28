# THIS IS A DOCUMENT ABOUT OLD VERSION OF PROGRAM, READ THIS AT YOUR OWN RISK (at least, everything what've been described here didn't work hehe)
  
I always liked to describe my own expirience of making something. So, here we are - I'm going to try write some code in ASM for ARM arch. Of course I like it. Obviously, because it's hard, it's interesting and it can give to ya real expirience and knowledge how the fuck is CPU working  
  
# First part: definitions
That is the strange thing what you can see at the begginning of the file (we're always talking about `create_tasks.s` file). That is basic defs not for CPU even, but for interpreter of ASM (gcc/as). So, first lines what use directives `.thumb`, `.cpu` and some things like that do not have a role in CPU working.  
So, we're going to explaunb what these definitions do:
1. `.thumb` - the first thing. That 'marker' says to the GCC/AS interpreter the thing, like: 'we're gonna to use the instruction set what's name is Thumb! Get prepare for that!'. What Thumb is? It's a instruction set of CPU by what we can command the CPU. That list containts a lot of commands what we can send to the CPU and it weill execute that. There's a lot of other lists, like the list 'ARM mode', but they have different structure, different quantity of CPU intructions, and, at least, we're writing the code for STM32F4xx - and it uses Cortex-M4 hardware CPU core, and this core can use only Thumb instructions list. There's a lof of other CPU what support other lists, but for now we're using Cortex-M4, and, then we have to use Thumb list
2. `.cpu cortex-m4` - the second one, it defines what CPU we use. That's not a thing what we have to use only for formal agreement, but it activates some stuff within GCC/AS for working with right this type of CPU. That things are: version of CPU modules, instruction set and other and other stuff
3. `.section .text` - a marker again. Using that, we're opening the gate of the topic of sections in Assembler - and for now, that line tells to interpreter the thing, like 'there we go! We're gonna to write the code, actually!' - yea, section '.text' (rightly with that name) defines the main program code. By the way, that section (name of this section, honestly) is reserved. That thing is kinda like the main function in C - it contains the main code of the program. And by the way again - ya, Assembler has other reserved sections:'.bss', for example: in that section you can describe the using of stack in your program
4. `.syntax unified` - another marker-definition what says that we're gonna to write our progam with unified syntax. What is that? That is actually the syntax what we're wanna to use - unified syntax supports two instruction set: ARM mode and Thumb. And that line of code defines the list for the programmer now: the previous declaration of it defined the list only for CPU, and now we're saying to the interpreter what WE're gonna to use. It works like that

# Creating the subjects (actually, the main goal of this file)
Here you have to see two file at the same time: obviously, it's `create_tasks.s`, of course, and `gen_offsets.c`. For what do I need the second one? Welp, see: if you're gotta to create a structure's subject, you have to create 'blocks' in memory: evey one for every subject, because ASM does not understand what the fuck subject is. And, then, you have to reserve memory for the things what you wanna to create. And, of course, if you're gonna to free some memory for subject, you have to know what size of memory do you have to free (in bytes)  
I thought: I don't want to count the size of subject (I could do that by only sum of every field in structure (I mean, count a real sum of everything what structure stores within)). Like, at everytime I'll need to count it again and again. No, I can do it by other way: create a function what will count the size. And I made it in C - in the file `get_offsets.c`. Let's see what does it consist:  

```
#include <stddef.h>
#include "sch.h"

#ifdef __GNUC__ 
#define EMIT(name, value) \
    __asm__ volatile (".equ " #name ", %0" :: "i"(value))
#else
#define EMIT(name, value)
#endif

EMIT(__task_size, sizeof(sch_task_t));
EMIT(__priority_offset, offsetof(sch_task_t, priority));
```
  
There's using the thing what world knows as 'inline ASM' - that means that you can write ASM code, using the code of C. Then, let's see - there you have the macro: 
``` 
#ifdef __GNUC__ 
#define EMIT(name, value) \
    __asm__ volatile (".equ " #name ", %0" :: "i"(value))
#else
#define EMIT(name, value)
#endif
```
  
The main part of it is: 
```
#define EMIT(name, value) \
    __asm__ volatile (".equ " #name ", %0" :: "i"(value))
```  
  
That means, we're defining the macro EMIT with arguments name and value, and setting the value of it: the expression `__asm__ volatile (".equ " #name ", %0" :: "i"(value))`, and there's magic: that is the line of ASM code. Remember, I told about inline ASM? That is, inline - you're configuring the line of code, and then we're going to insert that in ASM-file (welp, actually, we won't, but that will execute like a real ASM code within the C-file). And next, see the details of inserting line: `".equ " #name ", %0" :: "i"(value)` that is the form of it. And there're some kind of arfuments:
1. `.equ` - the name of ASM command. Well, it's actually gonna to execute as average ASM code (do ya still remember about inline ASM?). That command will create ASM-in constant what name is `#name` what's defined next
2. `#name` - welp, actually the name of the constant
3. `"%0" :: "i"(value)` - that thing works like `printf`. You're giving to it a template of expression with markers, and list of values what it husts to insert where markers are. So, `%0` is the marker, and it's value is `"i"(value)`
  
And then, using:
```
EMIT(__task_size, sizeof(sch_task_t));
EMIT(__priority_offset, offsetof(sch_task_t, priority));
```
  
That code uses the macro for creating two constants: `__task_size`, `__priority_offset`. And connects to that constants to values what counts by the function `sizeof` from standart C-libraries.  
  
