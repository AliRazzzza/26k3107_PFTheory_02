#include <stdio.h>

int main() {
    int seats[50][50];
    int rows, cols, i, j, k, d, t, r;
    int total = 0, rowFree;
    int mid, count;
    int found = 0, foundRow = -1, startSeat = -1;
    char ch;

    /* 1. Input seating plan */
    printf("Enter number of rows (1-50): ");
    scanf("%d", &rows);
    while (rows < 1 || rows > 50) {
        printf("Invalid. Enter rows between 1 and 50: ");
        scanf("%d", &rows);
    }

    printf("Enter number of seats per row (1-50): ");
    scanf("%d", &cols);
    while (cols < 1 || cols > 50) {
        printf("Invalid. Enter seats between 1 and 50: ");
        scanf("%d", &cols);
    }

    printf("Enter seat status (0 = available, 1 = booked):\n");
    for (i = 0; i < rows; i++) {
        printf("Row %d: ", i);
        for (j = 0; j < cols; j++) {
            scanf("%d", &seats[i][j]);
            while (seats[i][j] != 0 && seats[i][j] != 1) {
                printf("Only 0 or 1 allowed, enter again: ");
                scanf("%d", &seats[i][j]);
            }
        }
    }

    /* 2. Display seating arrangement */
    printf("\nSeating plan:\n");
    printf("    ");
    for (j = 0; j < cols; j++) {
        printf("%-3d", j);
    }
    printf("\n");
    for (i = 0; i < rows; i++) {
        printf("R%-2d ", i);
        for (j = 0; j < cols; j++) {
            if (seats[i][j] == 0) {
                ch = '_';
            } else {
                ch = 'X';
            }
            printf("%c  ", ch);
        }
        printf("\n");
    }

    /* 3. Seat availability report */
    printf("\nFree seats per row: ");
    for (i = 0; i < rows; i++) {
        rowFree = 0;
        for (j = 0; j < cols; j++) {
            if (seats[i][j] == 0) {
                rowFree++;
            }
        }
        printf("%d ", rowFree);
        total = total + rowFree;
    }
    printf("   Total free: %d\n", total);

    /* 4. Group booking input */
    printf("\nEnter number of customers (k): ");
    scanf("%d", &k);
    while (k <= 0 || k > cols) {
        printf("Invalid. k must be between 1 and %d: ", cols);
        scanf("%d", &k);
    }

    /* 5. Search starting from the middle row, then going outwards */
    mid = rows / 2;
    for (d = 0; d < rows && found == 0; d++) {
        for (t = 0; t < 2 && found == 0; t++) {
            if (t == 0) {
                r = mid - d;      /* smaller row number first */
            } else {
                r = mid + d;
            }
            if (t == 1 && d == 0) {
                continue;         /* middle row already checked */
            }
            if (r < 0 || r >= rows) {
                continue;
            }

            count = 0;
            for (j = 0; j < cols && found == 0; j++) {
                if (seats[r][j] == 0) {
                    count++;
                    if (count == k) {
                        found = 1;
                        foundRow = r;
                        startSeat = j - k + 1;
                    }
                } else {
                    count = 0;
                }
            }
        }
    }

    /* 6 and 7. Confirm booking or show failure message */
    if (found == 1) {
        for (j = startSeat; j < startSeat + k; j++) {
            seats[foundRow][j] = 1;
        }
        printf("\nGroup of %d seated in Row %d, Seats %d to %d\n", k, foundRow, startSeat, startSeat + k - 1);
        printf("Allocated seat numbers: ");
        for (j = startSeat; j < startSeat + k; j++) {
            printf("%d ", j);
        }
        printf("\n");

        printf("\nUpdated seating plan:\n");
        printf("    ");
        for (j = 0; j < cols; j++) {
            printf("%-3d", j);
        }
        printf("\n");
        for (i = 0; i < rows; i++) {
            printf("R%-2d ", i);
            for (j = 0; j < cols; j++) {
                if (seats[i][j] == 0) {
                    ch = '_';
                } else {
                    ch = 'X';
                }
                printf("%c  ", ch);
            }
            printf("\n");
        }
        printf("\nRemaining available seats: %d\n", total - k);
    } else {
        printf("\nSorry, no row has %d consecutive available seats. Seating plan unchanged.\n", k);
    }

    return 0;
}
