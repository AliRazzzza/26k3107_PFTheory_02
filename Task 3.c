#include <stdio.h>
void inputReadings(int temp[][50], int sensors, int hours) {
    int i, j;
    for (i = 0; i < sensors; i++){
        printf("Sensor %d readings: ",i+1);
        for (j = 0; j < hours; j++){
            scanf("%d", &temp[i][j]);
        }
    }
}
float analyzeSensor(int readings[], int hours, int sensorNo) {
    int i;
    int total = 0, max, min;
    int critical = 0, warning = 0;
    int streak = 0, longest = 0;
    float avg;
    max = readings[0];
    min = readings[0];
    for(i = 0; i<hours; i++){
        total = total + readings[i];

        if (readings[i] > max){
            max = readings[i];
        }
        if(readings[i] < min) {
            min = readings[i];
        }
        if(readings[i]>=40) {
            critical++;
        }else if(readings[i] >= 35 && readings[i] <= 39){
            warning++;
        }
        if (readings[i] >= 35) {
            streak++;
            if (streak > longest) {
                longest = streak;
            }
        } else {
            streak = 0;
        }
    }
    avg = (float)total / hours;
    printf("Sensor %d: Total=%d Avg=%.2f Max=%d Min=%d\n", sensorNo, total, avg, max, min);
    printf("          Critical=%d Warning=%d Longest hot streak=%d\n", critical, warning, longest);

    return avg;
}
int findHighestAverage(float averages[], int sensors) {
    int i, best = 0;
    for (i = 1; i < sensors; i++) {
        if (averages[i] > averages[best]) {
            best = i;
        }
    }
    return best + 1;
}

int main(){
    int temp[20][50];
    float averages[20];
    int sensors, hours, i, best;

    printf("Enter number of sensors (1-20): ");
    scanf("%d", &sensors);
    while (sensors < 1 || sensors > 20) {
        printf("Invalid. Enter between 1 and 20: ");
        scanf("%d", &sensors);
    }
    printf("Enter number of hourly readings (1-50): ");
    scanf("%d", &hours);
    while (hours < 1 || hours > 50) {
        printf("Enter between 1 and 50: ");
        scanf("%d", &hours);
    }
    inputReadings(temp, sensors, hours);
    printf("\n");
    for (i = 0; i < sensors; i++) {
        averages[i] = analyzeSensor(temp[i], hours, i + 1);
    }
    best = findHighestAverage(averages, sensors);
    printf("\nHighest average: Sensor %d (%.2f)\n", best, averages[best - 1]);
    return 0;
}
