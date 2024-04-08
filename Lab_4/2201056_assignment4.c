#include <stdio.h>
#include <stdbool.h>

int r;
int p;

bool is_Safe(int alloc[p][r], int need[p][r], int available[], int *deadlock_procs) {
    int count = 0;
    int done[p];
    int safe_order[p];
    int count_safe=0;
    for (int i = 0; i < p; i++)
        done[i] = 0;

    while (count < p * r) {
        bool found = false;
        for (int i = 0; i < p; i++) {
            if (!done[i]) {
                bool safe = true;
                for (int j = 0; j < r; j++) {
                    if (available[j] < need[i][j]) {
                        safe = false;
                        break;
                    }
                }
                if (safe) {
                    found = true;
                    for (int j = 0; j < r; j++) {
                        available[j] += alloc[i][j];
                        need[i][j] = 0;
                        count++;
                    }
                    safe_order[count_safe] = i;
                    count_safe++;
                    done[i] = 1;
                    deadlock_procs[i] = 1;  
                }
            }
        }
        if (!found)
            break;
    }

    printf("Order of safe processes: ");
    for (int i = 0; i < p; i++) {
        printf("P%d ", safe_order[i]);
    }
    printf("\n");

    return count == p * r;
}

int main() {
    printf("Enter the number of resources: ");
    scanf("%d", &r);
    printf("Enter the number of processes: ");
    scanf("%d", &p);

    int alloc[p][r];
    int need[p][r];

    printf("-------- ALLOCATION MATRIX --------\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            printf("Enter the instance of process P%d of resource R%d: ", i, j);
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("--------- NEED MATRIX/REQUEST MATRIX ----------\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            printf("Enter the instance of process P%d of resource R%d: ", i, j);
            scanf("%d", &need[i][j]);
        }
    }

    int available[r];
    printf("Enter the available instances of each resource type: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &available[i]);
    }

    printf("-------- ALLOCATION MATRIX --------\n");
    for (int i = 0; i < r; i++) {
        printf("  R%d ", i);
    }
    printf("\n");
    for (int i = 0; i < p; i++) {
        printf("P%d", i);
        for (int j = 0; j < r; j++) {
            printf(" %d  ", alloc[i][j]);
        }
        printf("\n");
    }

    printf("--------- NEED MATRIX/REQUEST MATRIX ----------\n");
    for (int i = 0; i < r; i++) {
        printf("  R%d ", i);
    }
    printf("\n");
    for (int i = 0; i < p; i++) {
        printf("P%d", i);
        for (int j = 0; j < r; j++) {
            printf(" %d  ", need[i][j]);
        }
        printf("\n");
    }

    printf("-------------AVAILABLE---------------\n");
    for (int i = 0; i < r; i++) {
        printf("R%d ", i);
    }
    printf("\n");
    for (int i = 0; i < r; i++) {
        printf("%d  ", available[i]);
    }
    printf("\n");
    printf("----------------------------*----------------------------\n");

    int deadlock_procs[p];
    for (int i = 0; i < p; i++)
        deadlock_procs[i] = 0;

    if (is_Safe(alloc, need, available, deadlock_procs)) {
        printf("No Deadlock.\n");
    } else {
        printf("Deadlock exists!!\n");

        printf("All the set of process except the given below process can be removed :\n");
        for (int i = 0; i < p; i++) {
            if (deadlock_procs[i] == 1) {
                printf("P%d ", i);
            }
        }
        printf("\n");
    }

    return 0;
}
