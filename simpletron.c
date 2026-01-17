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
#define REMINDER 33
#define MULTIPLY 34

// Control transfer operations
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

// Memory
#define MEMORY_SIZE 100

// Registers
typedef struct Registers
{
    int accumulator;
    int instructionCounter;
    int instructionRegister;
    int operationCode;
    int operand;
} Registers;
    
// Functions
void welcomeToSimpletron (void);
void enterCode (int instructionMemory[], Registers *cpu);
void clearInputBuffer (void);
void dump (int instructionMemory[], int dataMemory[], Registers *cpu);
void runCode (int instructionMemory[], int dataMemory[], Registers *cpu);
void fetchAndDecode (int instructionMemory[], int dataMemory[], Registers *cpu);
void execute (int instructionMemory[], int dataMemory[], Registers *cpu, bool *continueRun);
void read (int dataMemory[], Registers *cpu);
void write (int dataMemory[], Registers *cpu);
void load (int dataMemory[], Registers *cpu);
void store (int dataMemory[], Registers *cpu);
void add (int dataMemory[], Registers *cpu, bool *continueRun);
void subtract (int dataMemory[], Registers *cpu, bool *continueRun);
void divide (int dataMemory[], Registers *cpu, bool *continueRun);
void remainderSimpletron (int dataMemory[], Registers *cpu, bool *continueRun);
void multiply (int dataMemory[], Registers *cpu, bool *continueRun);
void branch (Registers *cpu);
void branchNeg (Registers *cpu);
void branchZero (Registers *cpu);
void halt (int instructionMemory[], int dataMemory[], Registers *cpu, bool *continueRun);

int main (void)
{
    // CPU
    Registers cpu = {0};

    // Memory
    int instructionMemory[MEMORY_SIZE] = {0};
    int dataMemory[MEMORY_SIZE] = {0};

    welcomeToSimpletron ();
    enterCode (instructionMemory, &cpu);
    runCode (instructionMemory, dataMemory, &cpu);
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

void enterCode (int instructionMemory[], Registers *cpu)
{
    int scanResult;
    int tempValue;

    while (1)
    {
        printf ("%02d ? ", cpu->instructionCounter);
        scanResult = scanf ("%d", &tempValue);

        if (tempValue != -99999 && (tempValue < -9999 || tempValue > 9999))
        {
            puts("***   You entered an invalid value. Retry.     ***");
            clearInputBuffer();
            continue;
        }

        else if (tempValue == -99999)
        {
            break;
        }    

        instructionMemory[cpu->instructionCounter] = tempValue; 
        cpu->instructionCounter++;

        if (cpu->instructionCounter >= MEMORY_SIZE)
        {
            puts ("*** Memory overflow: program too large for Simpletron ***");
            return;
        }   
          
    }   
}

void clearInputBuffer (void)
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void dump (int instructionMemory[], int dataMemory[], Registers *cpu)
{
    printf("\n%s\n", "REGISTERS:");
    printf("%-24s%+05d\n", "accumulator", cpu->accumulator);
    printf("%-24s   %02d\n", "instructionCounter", cpu->instructionCounter);
    printf("%-24s%+05d\n", "instructionRegister", cpu->instructionRegister);
    printf("%-24s   %02d\n", "operationCode", cpu->operationCode);
    printf("%-24s   %02d\n", "operand", cpu->operand);

    puts("\nINSTRUCTION MEMORY:");

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

        printf("%+05d ", instructionMemory[x]); 

        if ((x + 1) % 10 == 0)
        {
            puts("");
        }
    }

    puts("\nDATA MEMORY:");

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

        printf("%+05d ", dataMemory[x]); 

        if ((x + 1) % 10 == 0)
        {
            puts("");
        }
    }
}

void runCode (int instructionMemory[], int dataMemory[], Registers *cpu)
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
        fetchAndDecode (instructionMemory, dataMemory, cpu);

        if (continueRun == true)
        {
            execute (instructionMemory, dataMemory, cpu, &continueRun);
        }
        
        else
        {
            puts ("\n*** Simpletron execution abnormally terminated ***\n");
            dump (instructionMemory, dataMemory, cpu);
            break;
        }    
    } while (continueRun == true);
}

void fetchAndDecode (int instructionMemory[], int dataMemory[], Registers *cpu)
{
    cpu->instructionRegister = instructionMemory[cpu->instructionCounter];
    cpu->operationCode = cpu->instructionRegister / 100;
    cpu->operand = cpu->instructionRegister % 100;
}

void execute (int instructionMemory[], int dataMemory[], Registers *cpu, bool *continueRun)
{
    switch (cpu->operationCode)
    {
    case READ:
        read (dataMemory, cpu);
        break;
    
    case WRITE:
        write (dataMemory, cpu);
        break;

    case LOAD:
        load (dataMemory, cpu);
        break;

    case STORE:
        store (dataMemory, cpu);
        break;

    case ADD:
        add (dataMemory, cpu, continueRun);
        break;

    case SUBTRACT:
        subtract (dataMemory, cpu, continueRun);
        break;

    case DIVIDE:
        divide (dataMemory, cpu, continueRun);
        break;

    case REMINDER:
        remainderSimpletron (dataMemory, cpu, continueRun);
        break;

    case MULTIPLY:
        multiply (dataMemory, cpu, continueRun);
        break;

    case BRANCH:
        branch (cpu);
        break;

    case BRANCHNEG:
        branchNeg (cpu);
        break;

    case BRANCHZERO:
        branchZero (cpu);
        break;

    case HALT:
        halt (instructionMemory, dataMemory, cpu, continueRun);
        break;

    default:
        *continueRun = false;
        break;
    }
}

void read (int dataMemory[], Registers *cpu)
{
    int scanResult;
    int tempValue;

    while (1)
    {
        printf ("READ %02d ? ", cpu->operand);
        scanResult = scanf ("%d", &tempValue);

        if (scanResult != 1 || tempValue < -9999 || tempValue > 9999)
        {
            puts("***   You entered an invalid value. Retry.     ***");
            clearInputBuffer();
        }

        else
        {
            dataMemory[cpu->operand] = tempValue;
            cpu->instructionCounter++;
            break;
        }    
    }
}

void write (int dataMemory[], Registers *cpu)
{
    printf ("WRITE %02d : %+05d\n", cpu->operand, dataMemory[cpu->operand]);
    cpu->instructionCounter++;
}

void load (int dataMemory[], Registers *cpu)
{
    cpu->accumulator = dataMemory[cpu->operand];
    cpu->instructionCounter++;
}

void store (int dataMemory[], Registers *cpu)
{
    dataMemory[cpu->operand] = cpu->accumulator;
    cpu->instructionCounter++;
}

void add (int dataMemory[], Registers *cpu, bool *continueRun)
{
    if ((cpu->accumulator + dataMemory[cpu->operand] < -9999) || (cpu->accumulator + dataMemory[cpu->operand] > 9999))
    {
        *continueRun = false;
    }
    
    else
    {
        cpu->accumulator += dataMemory[cpu->operand];
        cpu->instructionCounter++;
    }   
}

void subtract (int dataMemory[], Registers *cpu, bool *continueRun)
{
    if ((cpu->accumulator - dataMemory[cpu->operand] < -9999) || (cpu->accumulator - dataMemory[cpu->operand] > 9999))
    {
        *continueRun = false;
    }
    
    else
    {
        cpu->accumulator -= dataMemory[cpu->operand];
        cpu->instructionCounter++;
    }   
}

void divide (int dataMemory[], Registers *cpu, bool *continueRun)
{
    if (dataMemory[cpu->operand] == 0)
    {
        *continueRun = false;
    }
    
    else
    {
        cpu->accumulator /= dataMemory[cpu->operand];
        cpu->instructionCounter++;
    }   
}

void remainderSimpletron (int dataMemory[], Registers *cpu, bool *continueRun)
{
    if (dataMemory[cpu->operand] == 0)
    {
        *continueRun = false;
    }
    
    else
    {
        cpu->accumulator %= dataMemory[cpu->operand];
        cpu->instructionCounter++;
    }   
}

void multiply (int dataMemory[], Registers *cpu, bool *continueRun)
{
    if ((cpu->accumulator * dataMemory[cpu->operand] < -9999) || (cpu->accumulator * dataMemory[cpu->operand] > 9999))
    {
        *continueRun = false;
    }
    
    else
    {
        cpu->accumulator *= dataMemory[cpu->operand];
        cpu->instructionCounter++;
    }   
}

void branch (Registers *cpu)
{
    cpu->instructionCounter = cpu->operand;
}

void branchNeg (Registers *cpu)
{
    if (cpu->accumulator < 0)
    {
        branch (cpu);
    }

    else
    {
        cpu->instructionCounter++;
    }    
}

void branchZero (Registers *cpu)
{
    if (cpu->accumulator == 0)
    {
        branch (cpu);
    }

    else
    {
        cpu->instructionCounter++;
    }    
}

void halt (int instructionMemory[], int dataMemory[], Registers *cpu, bool *continueRun)
{
    puts ("\n*** Simpletron execution terminated ***\n");
    *continueRun = false;
    dump (instructionMemory, dataMemory, cpu);
}