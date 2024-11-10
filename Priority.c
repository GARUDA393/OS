#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pno;
    int pri;
    int btime;
    int wtime;
} sp;

int main() {
    int i, j, n;
    int tbm = 0, totwtime = 0, totttime = 0;
    sp *p, t;

    printf("\nPRIORITY SCHEDULING.\n");
    printf("\nEnter the number of processes:\n");
    scanf("%d", &n);

    // Allocate memory for 'n' processes
    p = (sp *)malloc(n * sizeof(sp));

    if (p == NULL) {
        printf("Memory allocation failed.");
        return 1;
    }

    printf("Enter the burst time and priority:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &p[i].btime, &p[i].pri);
        p[i].pno = i + 1;
        p[i].wtime = 0;
    }

    // Sorting processes based on priority
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].pri > p[j].pri) {
                t = p[i];
                p[i] = p[j];
                p[j] = t;
            }
        }
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        p[i].wtime = tbm; // Waiting time is cumulative burst time of previous processes
        totwtime += p[i].wtime;
        tbm += p[i].btime;
        printf("%d\t\t%d\t\t%d\t\t%d\n", p[i].pno, p[i].btime, p[i].wtime, p[i].wtime + p[i].btime);
    }

    totttime = tbm; // Total turnaround time is cumulative burst time for all processes

    printf("\nTotal Waiting Time: %d", totwtime);
    printf("\nAverage Waiting Time: %.2f", (float)totwtime / n);
    printf("\nTotal Turnaround Time: %d", totttime);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totttime / n);

    free(p); // Free allocated memory
    return 0;
}
