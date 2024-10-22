# Project description

For this project, I was asked to devellop a program written in PROLOG to solve binary puzzles. A binary puzzle is a matrix n x n, where n is even and greater or equal to 4. Each position in th puzzle can have the value 1, 0 or no value at all. The puzzle is solved when all positions have values. However, the solution has to follow three rules:

#### 1 - It can not have 3 cells together with the same values. Line or column

#### 2 - All lines and columns must have the same number of 0's and 1's.

#### 3 - All lines are unique. All columns are unique.

More information here: [paper](paper.pdf)

The code was tested here: [tests](/Binary-Puzzle-Solver/public_tests)

This code was auxiliar and previously given by the teacher: [codigo comum](codigo_comum.pl)

This was my solution: [code](code.pl)

### To run an input use:

swipl -q -t halt -f codigo_comum.pl -f code.pl -g "code"

Like such:
swipl -q -t halt -f codigo_comum.pl -f code.pl -g "aplica_R1_triplo([1, _, 1], R), escreve_Linha(R); writeln('falhou')."