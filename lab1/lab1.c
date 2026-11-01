#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

double readDoubleConsole(void) {

    double numberValue = 0.0;
    char symbol = '\0';
    int scanResult = 0, isIncorrect = 0;

    do {

        isIncorrect = 0;
        scanResult = scanf("%lf%c", &numberValue, &symbol);

        if (scanResult != 2 || symbol != '\n' || !isfinite(numberValue)) {
            isIncorrect = 1;

            printf("Ошибка ввода. Попробуйте еще раз.\n");
            while(getchar() != '\n');
        }
    } while (isIncorrect);
    return numberValue;

}
double checkDoubleConsole(int lowerBound, int upperBound) {

    double numberValue = 0.0;
    int isIncorrect = 0;

    do {

        isIncorrect = 0;
        numberValue = readDoubleConsole();

        if (numberValue < lowerBound || numberValue > upperBound) {
            isIncorrect = 1;

            printf("Число должно быть в диапазоне от %d до %d. Попробуйте еще раз:\n", lowerBound, upperBound);
        }
    } while (isIncorrect);
    return numberValue;

}
int checkIntConsole(int lowerBound, int upperBound) {
    double numberValue = 0.0;
    int isIncorrect = 0;

    do {

        isIncorrect = 0;
        numberValue = checkDoubleConsole(lowerBound, upperBound);

        if (numberValue != (int)numberValue) {
            isIncorrect = 1;
            printf("Число должно быть целым. Попробуйте еще раз:\n");
        }
    } while (isIncorrect);
    return (int)numberValue;

}
void inputParameters(double *routeDistanceKm, int *tripDurationMins, double *batteryCapacityKwh, double *initialChargePercent, double *finalChargePercent, double *electricityTariff, int *passengerCount, int lowerBound, int upperBound) {

    printf("Введите длину маршрута в км (от %d до %d):\n", lowerBound, upperBound);
    *routeDistanceKm = checkDoubleConsole(lowerBound, upperBound);
    
    printf("Введите длительность поездки в мин (от %d до %d):\n", lowerBound, upperBound);
    *tripDurationMins = checkIntConsole(lowerBound, upperBound);
    
    printf("Введите ёмкость батареи в кВт*ч (от %d до %d):\n", lowerBound, upperBound);
    *batteryCapacityKwh = checkDoubleConsole(lowerBound, upperBound);
    
    printf("Введите начальный заряд в процентах (от 0 до 100):\n");
    *initialChargePercent = checkDoubleConsole(0, 100);
    
    printf("Введите конечный заряд в процентах (от 0 до %.2f):\n", *initialChargePercent);
    *finalChargePercent = checkDoubleConsole(0, (int)*initialChargePercent);
    
    printf("Введите тариф в BYN/(кВт*ч) (от 0 до %d):\n", upperBound);
    *electricityTariff = checkDoubleConsole(0, upperBound);
    
    printf("Введите количество пассажиров (от %d до %d):\n", lowerBound, upperBound);
    *passengerCount = checkIntConsole(lowerBound, upperBound);

}
void calculateMetrics(double routeDistanceKm, int tripDurationMins, double batteryCapacityKwh, double initialChargePercent, double finalChargePercent, double electricityTariff, int passengerCount, double *travelHours, double *spentEnergy, double *averageSpeed, double *energyConsumption, double *totalTripCost, double *costPerSinglePassenger) {

    *travelHours = tripDurationMins / 60.0;
    *spentEnergy = batteryCapacityKwh * (initialChargePercent - finalChargePercent) / 100.0;
    *averageSpeed = routeDistanceKm / *travelHours;
    *energyConsumption = *spentEnergy / routeDistanceKm * 100.0;
    *totalTripCost = *spentEnergy * electricityTariff;
    *costPerSinglePassenger = *totalTripCost / passengerCount;

}
void displayInputData(double routeDistanceKm, int tripDurationMins, double batteryCapacityKwh, double initialChargePercent, double finalChargePercent, double electricityTariff, int passengerCount) {

    printf("\nИсходные данные:\n");
    printf("Длина маршрута:              %.2f км\n", routeDistanceKm);
    printf("Длительность поездки:        %d мин\n", tripDurationMins);
    printf("Полная ёмкость батареи:      %.2f кВт*ч\n", batteryCapacityKwh);
    printf("Заряд в начале:              %.2f %%\n", initialChargePercent);
    printf("Заряд в конце:               %.2f %%\n", finalChargePercent);
    printf("Тариф:                       %.2f BYN/(кВт*ч)\n", electricityTariff);
    printf("Количество пассажиров:       %d\n", passengerCount);

}
void displayResults(double travelHours, double spentEnergy, double averageSpeed, double energyConsumption, double totalTripCost, double costPerSinglePassenger) {

    printf("\nВычисленные значения:\n");
    printf("Время поездки:               %.2f ч\n", travelHours);
    printf("Израсходованная энергия:     %.2f кВт*ч\n", spentEnergy);
    printf("Средняя скорость:            %.2f км/ч\n", averageSpeed);
    printf("Расход на 100 км:            %.2f кВт*ч/100 км\n", energyConsumption);
    printf("Стоимость поездки:           %.2f BYN\n", totalTripCost);
    printf("Стоимость на пассажира:      %.2f BYN\n", costPerSinglePassenger);

}

int main(void) {

    const int MIN_LIMIT = 1;
    const int MAX_LIMIT = 1000000;

    double routeDistanceKm = 0.0, batteryCapacityKwh = 0.0, initialChargePercent = 0.0, finalChargePercent = 0.0, electricityTariff = 0.0, travelHours = 0.0, spentEnergy = 0.0, averageSpeed = 0.0, energyConsumption = 0.0, totalTripCost = 0.0, costPerSinglePassenger = 0.0;
    int tripDurationMins = 0, passengerCount = 0;

    setlocale(LC_CTYPE, ".UTF-8");
    inputParameters(&routeDistanceKm, &tripDurationMins, &batteryCapacityKwh, &initialChargePercent, &finalChargePercent, &electricityTariff, &passengerCount, MIN_LIMIT, MAX_LIMIT);
    calculateMetrics(routeDistanceKm, tripDurationMins, batteryCapacityKwh, initialChargePercent, finalChargePercent, electricityTariff, passengerCount, &travelHours, &spentEnergy, &averageSpeed, &energyConsumption, &totalTripCost, &costPerSinglePassenger);
    displayInputData(routeDistanceKm, tripDurationMins, batteryCapacityKwh, initialChargePercent, finalChargePercent, electricityTariff, passengerCount);
    displayResults(travelHours, spentEnergy, averageSpeed, energyConsumption, totalTripCost, costPerSinglePassenger);

    return 0;

}
