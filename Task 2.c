#include <stdio.h>
int sumDivisors(int x) {
    int sum, i;
    if (x == 1){
        return 0;
    }
    sum = 1;
    for (i = 2; i * i <= x; i++){
        if (x % i == 0) {
            sum = sum + i;
            if(i != x / i){
                sum = sum + x / i;
            }
        }
    }
    return sum;
}

int main() {
    int n, a, b;
    int count = 0;

    printf("Enter n: ");
    scanf("%d", &n);
    while (n < 1) {
        printf("n must be positive, enter again: ");
        scanf("%d", &n);
    }
    printf("\nAmicable pairs up to %d:\n", n);
    for (a = 2; a <= n; a++) {
        b = sumDivisors(a);
        if (b > a && b <= n && sumDivisors(b) == a) {
            printf("(%d, %d)\n", a, b);
            count++;
        }
    }
    if (count == 0) {
        printf("No amicable pairs found up to %d\n", n);
    } else {
        printf("Total pairs: %d\n", count);
    }

    return 0;
}
