#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESS 10

typedef struct {
    char *name;       
    int arrival;       
    int cpuburst;      
    int turnaround;    
    int wait;          
} Process;

Process processtable[MAX_PROCESS]; 
Process *tempTable;                 
int i = 0;                          // Number of processes
int current_time;                   // Current time during execution

// Function to print turnaround times and waiting times
void PrintStatistics(Process *TempTable, int *turn_around_time, int *wait_time) {
    printf("Turnaround times: ");
    for (int k = 0; k < i; k++) {
        printf("%s[%d], ", TempTable[k].name, turn_around_time[k]);
    }
    printf("\n");

    printf("Wait times      : ");
    for (int k = 0; k < i; k++) {
        printf("%s[%d], ", TempTable[k].name, wait_time[k]);
    }
    printf("\n\n");

    printf("Average turnaround time :");
    float total_turnaround_time = 0;
    float x1 = 0;
    for (int j = 0; j < i; j++) {
        x1++;
        total_turnaround_time = total_turnaround_time + turn_around_time[j];
    }
    printf("%.2f\n", total_turnaround_time / x1);

    printf("Average wait time      :");
    float total_wait_time = 0;
    float x2 = 0;
    for (int j = 0; j < i; j++) {
        x2++;
        total_wait_time = total_wait_time + wait_time[j];
    }
    printf("%.2f\n", total_wait_time / x2);
}

// Function to implement First Come First Served (FCFS) scheduling algorithm
void FCFS() {
    //Assuming that arrival times are different
    tempTable = malloc(i * sizeof(Process));
    if (tempTable == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }

    // Copy processes to temporary table for sorting
    for (int j = 0; j < i; j++) {
        tempTable[j] = processtable[j];
    }

    // Sort processes based on arrival time
    for (int j = 0; j < i; j++) {
        for (int k = j; k < i; k++) {
            if (tempTable[k].arrival < tempTable[j].arrival) {
                Process temp = tempTable[j];
                tempTable[j] = tempTable[k];
                tempTable[k] = temp;
            }
        }
    }

    // Execute processes sequentially
    printf("\n");
    current_time = 0;
    int turn_around_time_FCFS[i];
    int wait_time_FCFS[i];
    for (int j = 0; j < i; j++) {
        printf("[%d-%d]  %s running\n", current_time, current_time + tempTable[j].cpuburst, tempTable[j].name);
        //apply definition of turnaround_time and wait_time
        turn_around_time_FCFS[j] = (current_time + tempTable[j].cpuburst) - tempTable[j].arrival;
        wait_time_FCFS[j] = current_time - tempTable[j].arrival;
        current_time = current_time + tempTable[j].cpuburst;
    }
    printf("\n");
    PrintStatistics(tempTable, turn_around_time_FCFS, wait_time_FCFS);
    printf("\n");
    printf("Hit any Key to continue ...\n");

}

// Function to implement Round Robin (RR) scheduling algorithm
void RR(int quantum) {
    //Assuming that arrival times are different
    tempTable = malloc(i * sizeof(Process));
    if (tempTable == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }

    // Copy processes to temporary table for sorting
    for (int j = 0; j < i; j++) {
        tempTable[j] = processtable[j];
    }

    // Sort processes based on arrival time
    for (int j = 0; j < i; j++) {
        for (int k = j; k < i; k++) {
            if (tempTable[k].arrival < tempTable[j].arrival) {
                Process temp = tempTable[j];
                tempTable[j] = tempTable[k];
                tempTable[k] = temp;
            }
        }
    }

    int turn_around_time[i];
    int wait_time[i];
    int cpuburstcopy[i];

    // Copy remaining CPU burst times to temporary array for future use..
    for (int j = 0; j < i; j++) {
        cpuburstcopy[j] = tempTable[j].cpuburst;
    }

    current_time = 0;
    int done = 0;
    while (!done) {
        done = 1;
        for (int j = 0; j < i; j++) {
            if (tempTable[j].arrival > current_time) {
                continue;
            } else {
                if (cpuburstcopy[j] > 0) {
                    done = 0;
                    int run_time = (cpuburstcopy[j] < quantum) ? cpuburstcopy[j] : quantum;
                    printf("[%d-%d] %s running\n", current_time, current_time + run_time, tempTable[j].name);
                    current_time += run_time;
                    cpuburstcopy[j] -= run_time;
                    if (cpuburstcopy[j] == 0) {
                        //apply definition of turnaround_time and wait_time
                        turn_around_time[j] = current_time - tempTable[j].arrival;
                        wait_time[j] = turn_around_time[j] - tempTable[j].cpuburst;
                    }
                }
            }
        }
    }

    printf("\n");
    PrintStatistics(tempTable, turn_around_time, wait_time);
    printf("\n");
    printf("Hit any Key to continue ...\n");
    free(tempTable);
}

// Function to implement Shortest Remaining Burst First (SRBF) scheduling algorithm
void SRBF() {
    //Assuming that arrival times are different
    int process_count = i;

    // Sort processes based on arrival time
    for (int k = 0; k < process_count - 1; k++) {
        for (int j = 0; j < process_count - k - 1; j++) {
            if (processtable[j].arrival > processtable[j + 1].arrival) {
                Process temp = processtable[j];
                processtable[j] = processtable[j + 1];
                processtable[j + 1] = temp;
            }
        }
    }

    // Initialize arrays to store remaining burst times
    int remaining_burst[process_count];
    for (int k = 0; k < process_count; k++) {
        remaining_burst[k] = processtable[k].cpuburst;
        processtable[k].wait = 0;
    }

    int completed_processes = 0;
    int shortest_remaining_burst_index;

    while (completed_processes < process_count) {
        shortest_remaining_burst_index = -1;
        for (int k = 0; k < process_count; k++) {
            if (processtable[k].arrival > current_time) {
                continue;
            } else {
                if (remaining_burst[k] > 0 && (shortest_remaining_burst_index == -1 || remaining_burst[k] < remaining_burst[shortest_remaining_burst_index])) {
                    shortest_remaining_burst_index = k;
                }
            }
        }
        printf("%s running [%d-%d]\n", processtable[shortest_remaining_burst_index].name, current_time, current_time + 1);
        current_time += 1;
        for (int k = 0; k < process_count; k++) {
            if ((remaining_burst[k] > 0) && (k != shortest_remaining_burst_index)) {
                processtable[k].wait += 1;
            }
        }
        remaining_burst[shortest_remaining_burst_index] -= 1;

        if (remaining_burst[shortest_remaining_burst_index] == 0) {
            completed_processes++;
            processtable[shortest_remaining_burst_index].turnaround = current_time - processtable[shortest_remaining_burst_index].arrival;
        }
    }

    for (int k = 0; k < process_count; k++) {
        processtable[k].wait -= processtable[k].arrival;
    }

    // Copy turnaround times and waiting times to arrays for printing statistics
    int turn_around_time[i];
    int wait_time[i];
    for (int j = 0; j < i; j++) {
        turn_around_time[j] = processtable[j].turnaround;
        wait_time[j] = processtable[j].wait;
    }

    printf("\n");
    PrintStatistics(processtable,turn_around_time, wait_time);
    printf("\n");
    printf("Hit any Key to continue ...\n");
}

// Function to print the process table
void PrintProcessTable() {
    for (int j = 0; j < i; j++) {
        printf("%s %d %d\n", processtable[j].name, processtable[j].arrival, processtable[j].cpuburst);
    }
    printf("Output is identical to data stored in the input file!!\n");
}

// Function to read process information from a file
void ReadProcessTable(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error in opening the file!!");
        return;
    }
    char process[100];
    int arrival;
    int burst;
    while (fscanf(file, "%s %d %d", process, &arrival, &burst) == 3) {
        processtable[i].name = malloc(strlen(process) + 1);
        if (processtable[i].name == NULL) {
            printf("Memory allocation failed!");
            exit(1);
        }
        strcpy(processtable[i].name, process);
        processtable[i].arrival = arrival;
        processtable[i].cpuburst = burst;
        i++;
    }
    PrintProcessTable();
}

int main(int arg_count, char * args[]) {
    char filename[100];
    printf("Enter the file name of Process information :");
    scanf("%s", filename);
    ReadProcessTable(filename);
    int choice;
    while (1) {
        char newline;
        printf("-------------------------------------------------\n");
        printf("CPU Scheduling Simulation\n");
        printf("-------------------------------------------------\n");
        printf("Select the scheduling algorithm [1,2,3 or 4]:\n");
        printf("1. First Come First Served (FCFS)\n");
        printf("2. Round Robin (RR)\n");
        printf("3. SRBF\n");
        printf("4. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("-------------------------------------------------\n");
                printf("First Come First Served Scheduling\n");
                printf("-------------------------------------------------\n");
                FCFS();
                //Initialize current_time to Zero for every scheduling method
                current_time = 0;
                break;
            case 2:
                printf("-------------------------------------------------\n");
                printf("Round Robin Scheduling\n");
                printf("-------------------------------------------------\n");
                int quantum;
                printf("Enter the time quantum: ");
                scanf("%d", &quantum);
                RR(quantum);
                //Initialize current_time to Zero for every scheduling method
                current_time = 0;
                break;
            case 3:
                printf("-------------------------------------------------\n");
                printf("Shortest Remaining Burst First Scheduling\n");
                printf("-------------------------------------------------\n");
                SRBF();
                //Initialize current_time to Zero for every scheduling method
                current_time = 0;
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Enter a valid option\n");
                printf("Exiting...\n");
                exit(0);
        }
    }
    return 0;
}


