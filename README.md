# Simpletron Virtual Machine

A software simulation of the **Simpletron** computer, a simple yet powerful CPU that operates in **Simpletron Machine Language (SML)**. This project is written in C and simulates a computer's internal registers, memory, and execution cycle.



## 🚀 Overview
The Simpletron executes programs written in a decimal-based machine language. Each instruction is a **4-digit signed integer** (e.g., `+1007`):
* **First two digits:** Operation Code (The action to perform).
* **Last two digits:** Operand (The memory address/location).

## 🛠️ System Architecture
* **Memory:** 100 words (addressed 00 to 99).
* **Accumulator:** A special register where all calculations and data transfers are processed.
* **Instruction Counter:** Tracks the location of the next instruction to execute.
* **Instruction Register:** Holds the current instruction being processed.

## 📖 SML Instruction Set

| Category | Operation | Code | Description |
| :--- | :--- | :--- | :--- |
| **Input/Output** | `READ` | **10** | Read a word from the keyboard into a memory location. |
| | `WRITE` | **11** | Write a word from a memory location to the screen. |
| **Load/Store** | `LOAD` | **20** | Load a word from memory into the Accumulator. |
| | `STORE` | **21** | Store the Accumulator value into memory. |
| **Arithmetic** | `ADD` | **30** | Add a word from memory to the Accumulator. |
| | `SUBTRACT` | **31** | Subtract a word from memory from the Accumulator. |
| | `DIVIDE` | **32** | Divide the Accumulator by a word from memory. |
| | `MULTIPLY` | **33** | Multiply the Accumulator by a word from memory. |
| **Control** | `BRANCH` | **40** | Jump to a specific memory location. |
| | `BRANCHNEG` | **41** | Jump if the Accumulator is negative. |
| | `BRANCHZERO` | **42** | Jump if the Accumulator is zero. |
| | `HALT` | **43** | Terminate the program execution. |

## 💻 Example Program
This program reads two integers from the user, sums them, and displays the result:

| Location | Instruction | Description |
| :--- | :--- | :--- |
| **00** | `1007` | Read first number into address 07 |
| **01** | `1008` | Read second number into address 08 |
| **02** | `2007` | Load address 07 into Accumulator |
| **03** | `3008` | Add address 08 to Accumulator |
| **04** | `2109` | Store result in address 09 |
| **05** | `1109` | Print value from address 09 |
| **06** | `4300` | Halt execution |

## 🔧 Installation and Usage
1.  **Compile the source code:**
    ```bash
    gcc simpletron.c -o simpletron
    ```
2.  **Run the simulator:**
    ```bash
    ./simpletron
    ```
3.  **Enter your SML code** one instruction at a time.
4.  Type `-99999` to finish loading and start the execution.

## ⚠️ Error Handling
The simulator includes built-in safety checks for:
* **Invalid values:** Inputs must be between -9999 and +9999.
* **Division by Zero:** The program will terminate if a division by zero is attempted.
* **Overflows:** Calculation results exceeding the 4-digit limit will stop execution.

## 👤 Author

Stefano Caiula (steve-caiula)