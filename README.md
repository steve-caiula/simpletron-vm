\# Simpletron VM



Simpletron VM is a small C project implementing a \*\*virtual machine\*\* inspired by the Simpletron computer.  

It is designed to help understand how a CPU, memory, and instructions work at a low level.



\## Project Structure



\- `simpletron-vm/simpletron.c` : the main source code of the virtual machine

\- `simpletron-vm/simpletron.exe` : compiled executable

\- `.gitignore` : file to ignore compiled and temporary files



\## Compilation



On Windows with `gcc` (MinGW) or Linux:



```bash

gcc simpletron-vm/simpletron.c -o simpletron

```



\## Running



```bash

./simpletron

```



On Windows:


```bash

simpletrone.exe

```



\## Features




\- Reads and executes instructions in memory

\- Simple fetch-decode-execute cycle

\- Handles basic numeric input/output



\## Author



Stefano Caiula (steve-caiula)