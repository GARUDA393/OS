#include <stdio.h>
#include <stdlib.h>

struct rr {
    int pno, btime, sbtime, wtime, lst;
} p[10];

int main() {
    int pp = -1, ts, flag, count, ptm = 0, i, n, twt = 0, totttime = 0;

    printf("\nRound Robin Scheduling...\n");
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time slice: ");
    scanf("%d", &ts);
    
    printf("Enter the burst time:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &p[i].btime);
        p[i].wtime = p[i].lst = 0;
        p[i].pno = i + 1;
        p[i].sbtime = p[i].btime;
    }

    printf("\nScheduling...\n");
    do {
        flag = 0;
        for (i = 0; i < n; i++) {
            count = p[i].btime;
            if (count > 0) {
                flag = 1;  // Indicates that there are still processes left to schedule
                count = (count >= ts) ? ts : count;
                printf("\nProcess %d from %d", p[i].pno, ptm);
                ptm += count;
                printf(" to %d", ptm);
                p[i].btime -= count;

                if (pp != i) {
                    pp = i;
                    p[i].wtime += ptm - p[i].lst - count;
                    p[i].lst = ptm;
                }
            }
        }
    } while (flag);  // Continue as long as there are processes left

    printf("\n\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        int turnaround_time = p[i].wtime + p[i].sbtime;
        twt += p[i].wtime;
        totttime += turnaround_time;
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pno, p[i].sbtime, p[i].wtime, turnaround_time);
    }

    printf("\nTotal Waiting Time: %d", twt);
    printf("\nAverage Waiting Time: %.2f", (float)twt / n);
    printf("\nTotal Turnaround Time: %d", totttime);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totttime / n);

    return 0;
}
