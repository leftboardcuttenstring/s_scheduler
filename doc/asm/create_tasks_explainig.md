Here I would describe the way how I made a pipeline for creating tasks in assembler. And I'm talking about the `stm32f4xx_asm` example  
  
# How I made it?
Welp, there's the frist thing what I wanted to say - there's no assembler. Clean assembler. But here's assembler with GCC preprocessor support. So, the first thign what I can say now - .s files are assembler source code, but .S files are assembler source code with GCC preprocessor support. That means you can use #include and other C-magic right inside the asm code!  
And here we go - look at `create_tasks.S` file - there's include! But...what the file `sch_asm_offsets.h` file is? That is the buffer. Buffer of data. So, the buffer of data must to get this data from somewhere - the source is the `gen_offsets.c` file. In that file describes the macro what convers size of structure into the #define value. And then this value moves into the `sch_asm_offsets.h` file, and then that includes in `create_tasks.S`  
What moves the data from .c-file into .h-file? Makefile does. And it does it with a regular expression: `'s/^-> \([^ ]*\) [\$$#]\?\([^ ]*\).*/#define \1 \2/p'`. This shit is absolutely fucked up. In two words it searches the string from .c-file where macro works and inserts needed data when it needs. Then, in the `gen_offsets.c` file are a couple of this things - and actually these data is Makefile searches for. This data what we can get after executing the macro  
Let's break down the mechanics:
1. Search and Boundaries (.* at the beginning and end) .* at the beginning and end means "I don't care what comes before our -> arrow and what comes after the number." The compiler often adds tabs or comments on the same line. This expression tells sed to discard all unnecessary stuff and keep only what we'll extract into the "pockets."
2. Marker and Spaces (->[[:space:]]*). -> is our hard-coded "anchor." [[:space:]]* is a very important part. It means "any number of spaces or tabs." Different versions of gcc may indent the line after the arrow differently, and this command makes the search universal.
3. First Pocket: Constant Name (\([A-Z_0-9]*\)). \( ... \) are "remembering brackets" (pockets). Whatever ends up here, we'll later call it with \1.
[A-Z_0-9]* — we only allow uppercase letters, numbers, and underscores in the name. This is the standard for #define.
4. Garbage before a number ([#$$]\?). In ARM assembler, constants are often written as #12 or $12. [#$$]\?] says: "There might be a # or $ symbol here, or there might not be one (?)." We find this symbol, but don't put it in the pocket, thereby simply deleting it.
5. Second pocket: Value (\([0-9]*\)). \([0-9]*\) — we only take digits. This value will go in \2.
6. Replacement (/#define \1 \2/p). This is where the constructor is assembled. sed takes the word from the first pocket and the number from the second, then concatenates them into a ready-made C string: #define SCH_TASK_SIZE 12.

The p flag at the end (along with sed's -n switch) forces the utility to print only those lines where the replacement was successful. All other assembly code from gen_offsets.s is simply removed.

# Afterword
If I'll have an opportunity, for humanity's sake I'll add other folder with wikis. Wikis about...the truth