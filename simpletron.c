// Simpletron virtual machine

#include <stdio.h>
#include <stdbool.h>

// Input / Output
#define READ 10
#define WRITE 11

// Load / Store
#define LOAD 20
#define STORE 21

// Arithmetic operations
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33

// Control transfer operations
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

// Memory
#define MEMORY_SIZE 100

// Registers
typedef struct
{
    int accumulator;
    int instructionCounter;
    int instructionRegister;
    int operationCode;
    int operand;
} Registers;
    
// Functions
void welcomeToSimpletron (void);
void enterCode (int memory[], Registers *cpu);
void clearInputBuffer (void);
void dump (int memory[], Registers *cpu);
void runCode (int memory[], Registers *cpu);
void fetchAndDecode (int memory[], Registers *cpu);
void execute (int memory[], Registers *cpu, bool *continueRun);
void read (int memory[], Registers *cpu);
void write (int memory[], Registers *cpu);
void load (int memory[], Registers *cpu);
void store (int memory[], Registers *cpu);
void add (int memory[], Registers *cpu, bool *continueRun);
void subtract (int memory[], Registers *cpu, bool *continueRun);
void divide (int memory[], Registers *cpu, bool *continueRun);
void multiply (int memory[], Registers *cpu, bool *continueRun);
void branch (int memory[], Registers *cpu);
void branchNeg (int memory[], Registers *cpu);
void branchZero (int memory[], Registers *cpu);
void halt (int memory[], Registers *cpu, bool *continueRun);

int main (void)
{
    // CPU
    Registers cpu = {0};

    // Memory
    int memory[MEMORY_SIZE] = {0};

    welcomeToSimpletron ();
    enterCode (memory, &cpu);
    runCode (memory, &cpu);
}

void welcomeToSimpletron (void)
{
    printf (
        "%s%s%s%s%s%s%s%s",
        "***          Welcome to Simpletron            ***\n",
        "***                                           ***\n",
        "*** Please enter your program one instruction ***\n",
        "*** (or data word) at a time. I will type the ***\n",
        "*** location number and a question mark (?).  ***\n",
        "*** You then type the word for that location. ***\n",
        "*** Type the sentinel -99999 to stop entering ***\n",
        "*** your program.                             ***\n\n"
    );
}

void enterCode (int memory[], Registers *cpu)
{
    int scanResult;
    int tempValue;

    while (1)
    {
        printf ("%02d ? ", cpu->instructionCounter);
        scanResult = scanf ("%d", &tempValue);

        if (tempValue != -99999 && (tempValue < -9999 || tempValue > 9999))
        {
            puts("***You entered an invalid value. Retry.     ***");
            clearInputBuffer();
            continue;
        }

        else if (tempValue == -99999)
        {
            break;
        }    

        memory[cpu->instructionCounter] = tempValue; 
        cpu->instructionCounter++;

        if (cpu->instructionCounter >= MEMORY_SIZE)
        {
            puts ("***Memory overflow: program too large for Simpletron***");
            return;
        }   
          
    }   
}

void clearInputBuffer (void)
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void dump (int memory[], Registers *cpu)
{
    printf("\n%s\n", "REGISTERS:");
    printf("%-24s%+05d\n", "accumulator", cpu->accumulator);
    printf("%-24s   %02d\n", "instructionCounter", cpu->instructionCounter);
    printf("%-24s%+05d\n", "instructionRegister", cpu->instructionRegister);
    printf("%-24s   %02d\n", "operationCode", cpu->operationCode);
    printf("%-24s   %02d\n", "operand", cpu->operand);

    puts("\nMEMORY:");

    printf("%3s", ""); 
    for (int i = 0; i < 10; i++)
    {
        printf("%5d ", i); 
    }
    puts("");

    for (int x = 0; x < MEMORY_SIZE; x++)
    {
        if (x % 10 == 0)
        {
            printf("%02d ", x);
        }

        printf("%+05d ", memory[x]); 

        if ((x + 1) % 10 == 0)
        {
            puts("");
        }
    }
}

void runCode (int memory[], Registers *cpu)
{
    bool continueRun = true;

    puts("\n*** Program loading completed ***");
    puts("*** Program execution begins  ***\n");
    
    if (cpu->instructionCounter >= MEMORY_SIZE)
    {
        return;
    }
    
    cpu->instructionCounter = 0;

    do
    {
        fetchAndDecode (memory, cpu);

        if (continueRun == true)
        {
            execute (memory, cpu, &continueRun);
        }
        
        else
        {
            puts ("\n*** Simpletron execution abnormally terminated ***\n");
            dump (memory, cpu);
            break;
        }    
    } while (continueRun == true);
}

void fetchAndDecode (int memory[], Registers *cpu)
{
    cpu->instructionRegister = memory[cpu->instructionCounter];
    cpu->operationCode = cpu->instructionRegister / 100;
    cpu->operand = cpu->instructionRegister % 100;
}

void execute (int memory[], Registers *cpu, bool *continueRun)
{
    switch (cpu->operationCode)
    {
    case READ:
        read (memory, cpu);
        break;
    
    case WRITE:
        write (memory, cpu);
        break;

    case LOAD:
        load (memory, cpu);
        break;

    case STORE:
        store (memory, cpu);
        break;

    case ADD:
        add (memory, cpu, continueRun);
        break;

    case SUBTRACT:
        subtract (memory, cpu, continueRun);
        break;

    case DIVIDE:
        divide (memory, cpu, continueRun);
        break;

    case MULTIPLY:
        multiply (memory, cpu, continueRun);
        break;

    case BRANCH:
        branch (memory, cpu);
        break;

    case BRANCHNEG:
        branchNeg (memory, cpu);
        break;

    case BRANCHZERO:
        branchZero (memory, cpu);
        break;

    case HALT:
        halt (memory, cpu, continueRun);
        break;

    default:
        *continueRun = false;
        break;
    }
}

void read (int memory[], Registers *cpu)
{
    int scanResult;
    int tempValue;

    while (1)
    {
        printf ("READ %02d ? ", cpu->operand);
        scanResult = scanf ("%d", &tempValue);

        if (scanResult != 1 || tempValue < -9999 || tempValue > 9999)
        {
            puts("***You entered an invalid value. Retry.     ***");
            clearInputBuffer();
        }

        else
        {
            memory[cpu->operand] = tempValue;
            cpu->instructionCounter++;
            break;
        }    
    }
}

void write (int memory[], Registers *cpu)
{
    printf ("WRITE %02d : %+05d\n", cpu->operand, memory[cpu->operand]);
    cpu->instructionCounter++;
}

void load (int memory[], Registers *cpu)
{
    cpu->accumulator = memory[cpu->operand];
    cpu->instructionCounter++;
}

void store (int memory[], Registers *cpu)
{
    memory[cpu->operand] = cpu->accumulator;
    cpu->instructionCounter++;
}

void add (int memory[], Registers *cpu, bool *continueRun)
{
    if ((cpu->accumulator + memory[cpu->operand] < -9999) || (cpu->accumulator + memory[cpu->operand] > 9999))
    {
        *continueRun = false;
    }
    
    else
    {
        cpu->accumulator += memory[cpu->operand];
        cpu->instructionCounter++;
    }   
}

void subtract (int memory[], Registers *cpu, bool *continueRun)
{
    if ((cpu->accumulator - memory[cpu->operand] < -9999) || (cpu->accumulator - memory[cpu->operand] > 9999))
    {
        *continueRun = false;
    }
    
    else
    {
        cpu->accumulator -= memory[cpu->operand];
        cpu->instructionCounter++;
    }   
}

void divide (int memory[], Registers *cpu, bool *continueRun)
{
    if (memory[cpu->operand] == 0)
    {
        *continueRun = false;
    }
    
    else
    {
        cpu->accumulator /= memory[cpu->operand];
        cpu->instructionCounter++;
    }   
}

void multiply (int memory[], Registers *cpu, bool *continueRun)
{
    if ((cpu->accumulator * memory[cpu->operand] < -9999) || (cpu->accumulator * memory[cpu->operand] > 9999))
    {
        *continueRun = false;
    }
    
    else
    {
        cpu->accumulator *= memory[cpu->operand];
        cpu->instructionCounter++;
    }   
}

void branch (int memory[], Registers *cpu)
{
    cpu->instructionCounter = cpu->operand;
}

void branchNeg (int memory[], Registers *cpu)
{
    if (cpu->accumulator < 0)
    {
        branch (memory, cpu);
    }

    else
    {
        cpu->instructionCounter++;
    }    
}

void branchZero (int memory[], Registers *cpu)
{
    if (cpu->accumulator == 0)
    {
        branch (memory, cpu);
    }

    else
    {
        cpu->instructionCounter++;
    }    
}

void halt (int memory[], Registers *cpu, bool *continueRun)
{
    puts ("\n*** Simpletron execution terminated ***\n");
    *continueRun = false;
    dump (memory, cpu);
}