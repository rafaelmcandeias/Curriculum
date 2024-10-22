# Project Statement 2 - IAED 2019/20

## Submission Deadline: 25th May 2020, at 23:59 (11:59 PM)

## Change Log

## 1. Introduction
test

The aim of this project is to develop a system in C language to manage a database of friendly football matches.
Interaction with the program should occur through a series of lines consisting of a letter (command) and a number of arguments depending on the command to execute. The possible commands are listed in the following table and indicate the operations to perform.

| Command | Action |
|:---:|:---|
| __a__ | Adds a new match. |
| __A__ | Adds a new team. |
| __l__ | Lists all matches in the order they were entered. |
| __p__ | Searches for a match. |
| __P__ | Searches for a team. |
| __r__ | Deletes a match. |
| __s__ | Changes the score of a match. |
| __g__ | Finds the teams that won the most matches. |
| __x__ | Terminates the program. |

## 2. Problem Specification

The aim of the project is to have a football match management system that allows associating teams and results with each match.

Each match and each team is characterised by a non-empty string, with a maximum of 1023 characters. Using `scanf`, the string can be read using `%[^:\n]`, i.e., a non-empty string without `:` and `\n`.

Each match is characterised by:

- A _name_, a non-empty string with a maximum of 1023 characters (`%[^:\n]`).
- Two teams, non-empty strings with a maximum of 1023 characters each (`%[^:\n]`).
- A _score_, a pair of non-negative integers.

*Note:* Since long names are rare, the data structures used should only allocate the memory necessary to store the given strings.

## 3. Input Data

During program execution, the instructions should be read from standard input as a series of lines starting with a character, referred to as a _command_, followed by a number of details depending on the command to execute.

The commands should be executed as they are read, and all operations should produce immediate output as necessary.

### Example

For instance, the system might receive the following commands:

