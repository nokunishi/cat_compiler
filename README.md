Compiler that converts a simple, intuitive language into ASM. Aims to allow users to learn assembly without programming experience

COMMANDS:
1. cd src
2. make 
3. ./main {inputfile_name}
    > i.e.) ./main input.tx
4. ../out/{filename}.o
    > each file in the ./out directory has name corresponding to the line number in the input file (0-based indexing)
    > this prints out msg of each line in the input file

How to write an input file:
- by default, types of animals it supports are:
    > cat (meow), dog(woof)
- to customize, write #define \<animal> \<sound>
- currently supported modes of messages are:
    > normal(.), exclaiming(!), demanding(!!)
- messages can be at most 100 chars long.
- each line should have a structure of: {animal}{mode}({msg})

