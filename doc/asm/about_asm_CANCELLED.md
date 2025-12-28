# THIS IS A DOCUMENT ABOUT OLD VERSION OF PROGRAM, READ THIS AT YOUR OWN RISK (at least, everything what've been described here didn't work hehe)

# Foreword
I went crazy and decided to rewrite part of the code in assembler, 
and I will include this assembler code in the repository, however, 
if someone uses SCH, you may not use this ASM code, because this 
is just something for a learning project
  
# What actually did I want to rewrite in Assembler?
Well, actually (for now) it's just a piece of code that initializes 
static structures for tasks. That is, in main.c (I'll comment out 
these lines, not delete them), before the main function itself, 
there's a block responsible for creating the sch_task_t type 
structures — I wanted to move this to a separate file, written in 
assembly