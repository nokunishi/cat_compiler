Compiler that converts a simple, intuitive language into ASM. Aims to allow users to learn assembly without programming experience

To run 'tx' language, store your input file and use the command-line-interface 
`python3 main.py {file name} {animal name}`

Instructions to writing the input file:
- by default, types of animals it supports are:
    > cat (meow), dog(woof)
- to customize, write #define \<animal> \<sound>
- currently supported modes of messages are:
    > normal(.), exclaiming(!), demanding(!!)
- messages can be at most 100 chars long.
- each line should have a structure of: {animal}{mode}({msg})

