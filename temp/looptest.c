#include <stdio.h>

int main() {
    float pO2;
    char group = 'A';

    printf("Enter partial pressure of oxygen (in atmospheres): ");
    scanf("%f", &pO2);

    while (pO2 >= 0.1) {
        group++;
        pO2 -= 0.1;
    }

    if (group > 'N') {
        printf("Error: oxygen mixture is too strong.\n");
    } else {
        printf("Oxygen pressure group: %c\n", group);
    }

    return 0;
}

