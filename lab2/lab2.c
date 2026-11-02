#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.14159265358979323846
#define DOMAIN_EPS 1e-9
#define MIN_POINTS 1
#define MAX_POINTS 1000
#define MAX_ITERATIONS 100000
#define EPS_1 1e-2
#define EPS_2 1e-3
#define EPS_3 1e-4
#define EPS_COUNT 3

int main(void) {
    double a, b, h, sumY, minY, maxY;
    double calculatedPointsCount;
    double x, y;
    double argumentLog, atanArgument, thirdTerm;
    double averageY;
    double eps, seriesSum, currentTerm, exactValue, difference;
    double z;

    int pointsCount, validCount, invalidCount;
    int epsIndex, termsCount;
    int scanResult, inputCharacter;
    int pointIndex;

    bool isInvalidInput, isBufferCleared;
    bool isIntervalIncorrect, isParametersCorrect;

    sumY = 0.0;
    pointsCount = 0;
    validCount = 0;
    invalidCount = 0;

    isInvalidInput = false;
    isBufferCleared = false;
    isIntervalIncorrect = true;
    isParametersCorrect = false;

    printf("Часть А: таблица значений функции на отрезке [a; b].\n");
    printf("y = ln(cbrt(x^2 + pi)) + atan(x / 3) + exp(5.0 / 3) / x\n");
    printf("Часть В: итерационное вычисление exp(z).\n\n");

    while (isIntervalIncorrect) {
        printf("Введите a: ");
        isInvalidInput = true;
        while (isInvalidInput) {
            scanResult = scanf("%lf", &a);
            if (scanResult == 1) {
                if (a < -1000.0 || a > 1000.0) {
                    printf("Вы вышли за возможный диапазон. Введите число от -1000.00 до 1000.00: ");
                } else {
                    isInvalidInput = false;
                }
            } else {
                printf("Ошибка ввода. Введите вещественное число от -1000.00 до 1000.00: ");
                isBufferCleared = true;
                while (isBufferCleared) {
                    inputCharacter = getchar();
                    if (inputCharacter == '\n' || inputCharacter == EOF) {
                        isBufferCleared = false;
                    }
                }
            }
        }

        printf("Введите b: ");
        isInvalidInput = true;
        while (isInvalidInput) {
            scanResult = scanf("%lf", &b);
            if (scanResult == 1) {
                if (b < -1000.0 || b > 1000.0) {
                    printf("Вы вышли за возможный диапазон. Введите число от -1000.00 до 1000.00: ");
                } else {
                    isInvalidInput = false;
                }
            } else {
                printf("Ошибка ввода. Введите вещественное число от -1000.00 до 1000.00: ");
                isBufferCleared = true;
                while (isBufferCleared) {
                    inputCharacter = getchar();
                    if (inputCharacter == '\n' || inputCharacter == EOF) {
                        isBufferCleared = false;
                    }
                }
            }
        }

        if (a > b) {
            printf("Ошибка: должно выполняться a <= b. Введите a и b снова.\n");
        } else {
            isIntervalIncorrect = false;
        }
    }

    printf("Введите h: ");
    isInvalidInput = true;
    while (isInvalidInput) {
        scanResult = scanf("%lf", &h);
        if (scanResult == 1) {
            if (h < 0.01 || h > 100.0) {
                printf("Вы вышли за возможный диапазон. Введите число от 0.01 до 100.00: ");
            } else {
                isInvalidInput = false;
            }
        } else {
            printf("Ошибка ввода. Введите вещественное число от 0.01 до 100.00: ");
            isBufferCleared = true;
            while (isBufferCleared) {
                inputCharacter = getchar();
                if (inputCharacter == '\n' || inputCharacter == EOF) {
                    isBufferCleared = false;
                }
            }
        }
    }

    calculatedPointsCount = floor((b - a) / h) + 1.0;

    if (calculatedPointsCount >= (double)MIN_POINTS && calculatedPointsCount <= (double)MAX_POINTS) {
        pointsCount = (int)calculatedPointsCount;
        isParametersCorrect = true;
    } else {
        printf("Ошибка: количество точек должно быть от %d до %d.\n", MIN_POINTS, MAX_POINTS);
    }

    if (isParametersCorrect) {
        printf("\n%-12s | %-16s\n", "x", "y");
        printf("--------------------------------\n");

        for (pointIndex = 0; pointIndex < pointsCount; pointIndex++) {
            x = a + (double)pointIndex * h;

            if (fabs(x) > DOMAIN_EPS) {
                argumentLog = cbrt(x * x + PI);
                atanArgument = x / 3.0;
                thirdTerm = exp(5.0 / 3.0) / x;

                y = log(argumentLog) + atan(atanArgument) + thirdTerm;

                printf("%-12.4lf | %-16.6lf\n", x, y);

                if (validCount == 0) {
                    minY = y;
                    maxY = y;
                } else {
                    if (y < minY) {
                        minY = y;
                    }
                    if (y > maxY) {
                        maxY = y;
                    }
                }

                    sumY = sumY + y;
                    validCount++;
            } else {
                printf("%-12.4lf | %-16s\n", x, "UNDEFINED");
                invalidCount++;
            }
        }

        printf("--------------------------------\n");
        printf("valid_count: %d\n", validCount);
        printf("invalid_count: %d\n", invalidCount);

        if (validCount > 0) {
            averageY = sumY / (double)validCount;
            printf("min_y: %.6lf\n", minY);
            printf("max_y: %.6lf\n", maxY);
            printf("average_y: %.6lf\n", averageY);
        } else {
            printf("Статистика недоступна: нет допустимых точек.\n");
        }

        printf("\nЧасть В: итерационное вычисление exp(z).\n");
        printf("Введите z: ");

        isInvalidInput = true;
        while (isInvalidInput) {
            scanResult = scanf("%lf", &z);
            if (scanResult == 1) {
                if (z < -100.0 || z > 100.0) {
                    printf("Вы вышли за возможный диапазон. Введите число от -100.0 до 100.0: ");
                } else {
                    isInvalidInput = false;
                }
            } else {
                printf("Ошибка ввода. Введите вещественное число: ");
                isBufferCleared = true;
                while (isBufferCleared) {
                    inputCharacter = getchar();
                    if (inputCharacter == '\n' || inputCharacter == EOF) {
                        isBufferCleared = false;
                    }
                }
            }
        }

        exactValue = exp(z);

        printf("\n%-10s | %-23s | %-14s | %-22s | %-8s | %s\n", 
               "eps", "Сумма ряда", "exp(z)", "Разность", "N", "Статус");
        printf("--------------------------------------------------------------------------------\n");

        epsIndex = 0;
        while (epsIndex < EPS_COUNT) {
            eps = EPS_1;
            if (epsIndex == 1) {
                eps = EPS_2;
            } else if (epsIndex == 2) {
                eps = EPS_3;
            }

            seriesSum = 0.0;
            currentTerm = 1.0;
            termsCount = 0;

            while (fabs(currentTerm) > eps && (termsCount < MAX_ITERATIONS)) {
                seriesSum = seriesSum + currentTerm;
                termsCount++;
                currentTerm = currentTerm * z / (double)termsCount;
            }

            difference = fabs(seriesSum - exactValue);

            if (termsCount >= MAX_ITERATIONS) {
                printf("%-10g | %-14.8lf | %-14.8lf | %-14.6g | %-8d | TIMEOUT\n", 
                       eps, seriesSum, exactValue, difference, termsCount);
            } else {
                printf("%-10g | %-14.8lf | %-14.8lf | %-14.6g | %-8d | SUCCESS\n", 
                       eps, seriesSum, exactValue, difference, termsCount);
            }

            epsIndex++;
        }

        printf("--------------------------------------------------------------------------------\n");
    }

    return 0;
}
