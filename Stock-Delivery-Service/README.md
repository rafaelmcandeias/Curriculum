# Project Statement 1 - IAED 2019/20

## Submission Deadline: 7th April 2020, at 23:59 (11:59 PM)

## Change Log

- 31st March 2020 - Mooshak opened. See information in the Project Section on the course page. We remind you that you cannot use the native `qsort` function from C, and this string should not appear in your code.
- 24th March 2020 - Clarification on command `r`

## 1. Introduction

The aim of this project is to develop a logistics system in C language. Interaction with the program should occur through a series of lines consisting of a letter (command) and a number of arguments depending on the command to execute. The possible commands are listed in the following table and indicate the operations to perform.

| Command | Action |
|:---:|:---|
| __a__ | Adds a new product to the system |
| __q__ | Adds stock to an existing product in the system |
| __N__ | Creates a new order |
| __A__ | Adds a product to an order |
| __r__ | Removes stock from an existing product |
| __R__ | Removes a product from an order |
| __C__ | Calculates the cost of an order |
| __p__ | Changes the price of an existing product in the system |
| __E__ | Returns the description and quantity of a product in a given order |
| __m__ | Returns the identifier of the order where a given product occurs most often |
| __l__ | Lists all products in the system in ascending order of price |
| __L__ | Lists all products of an order in alphabetical order by description |
| __x__ | Terminates the program |

## 2. Problem Specification

The goal of the project is to have a logistics system that allows the management of product stocks and orders.

There are several products that can be added to the orders.

Each __product__ is characterised by:

- an identifier (an integer in the range [0, 9999])
- a description (a non-empty string with a maximum of 63 characters)
- its price (a positive integer greater than 0)
- its weight (a positive integer greater than 0)

Each __order__ is characterised by:

- an identifier (a unique integer that is automatically assigned when an order is created)
- a list of products in the order (where a product can occur multiple times)

The logistics system will process commands as they are read and must ensure that all requirements of the command are met.

### Example

For example, the system might receive the following sequence of commands:

