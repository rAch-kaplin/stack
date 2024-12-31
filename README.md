# Stack

## Overview

This is a stack for any type of data.
The default data type is defined in stack.h   ```  typedef int stackElem ```

**Note:** If you are changing the data type, do not forget to change the print format in ``` printf()``` -->

The program has two types of protection: canaries protection and a hash protection (djb2) for the data.

## Build
Clone the repository:
``` git clone git@github.com:rAch-kaplin/stack.git ```

Run ``` make ``` to build the program. Type ``` ./do ``` to run the program.

Run ``` make clean ``` to remove obj and dependencies files (clean build folder).

## The logger

The program has a simple logging system that shows every change in the stack.
 The logger has *three* *levels*:
- **debug**
- **info**
- **error**

Prints the ``` stack.log ``` file to the log.


