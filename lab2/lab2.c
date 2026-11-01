#include <stdio.h>
#include <locale.h>
#include <math.h>

#define PI acos(-1.0)

double readDoubleConsole(void) {
    double num = 0.0;
    char symbol = '\0';
    int scanResult = 0, isIncorrect = 0;
    do {
        isIncorrect = 0;
        scanResult = scanf("%lf%c", &num, &symbol);
        if (scanResult != 2 || symbol != '\n' || !isfinite(num)) {
            isIncorrect = 1;
            printf("Ошибка ввода. Попробуйте ещё раз:\n");
            while (getchar() != '\n');
        }
    } while (isIncorrect);
    return num;
}

double checkDoubleConsole(int min, int max) {
    double num = 0.0;
    int isIncorrect = 0;
    do {
        isIncorrect = 0;
        num = readDoubleConsole();
        if (num < min || num > max) {
            isIncorrect = 1;
            printf("Число должно быть от %d до %d. Попробуйте ещё раз:\n", min, max);
        }
    } while (isIncorrect);
    return num;
}

void readValues(double *a, double *b, double *h, double *z, int *pointsQuantity, int min, int max, int maxPoints) {
    int isIncorrect = 0;
    double points = 0.0;
    do {
        isIncorrect = 0;
        printf("Введите начало диапазона a (от %d до %d):\n", min, max);
        *a = checkDoubleConsole(min, max);

        printf("Введите конец диапазона b (от %d до %d):\n", min, max);
        *b = checkDoubleConsole(min, max);

        printf("Введите шаг h (больше 0, не больше %d):\n", max);
        *h = checkDoubleConsole(0, max);

        if (*a > *b || *h <= 0) {
            isIncorrect = 1;
            printf("Требуется a <= b и h > 0. Повторите ввод диапазона.\n");
        } 
        else {
            points = floor((*b - *a) / *h) + 1.0;
            if (!isfinite(points) || points < 1.0 || points > maxPoints) {
                isIncorrect = 1;
                printf("Количество точек должно быть от 1 до %d. Повторите ввод.\n", maxPoints);
            } 
            else {
                *pointsQuantity = (int)points;
            }
        }
    } while (isIncorrect);

    printf("Введите z для вычисления exp(z) (например, от -10 до 10):\n");
    *z = checkDoubleConsole(-100, 100);
}

int checkDomain(double x, double domainEps) {
    // Знаменатель x не должен быть равен 0
    return fabs(x) > domainEps;
}

double findFormula(double x) {
    return log(cbrt(x * x + PI)) + atan(x / 3.0) + (exp(5.0 / 3.0) / x);
}

void printValue(double x, double y, int isDefined) {
    if (isDefined) {
        printf("%14.6f | %16.10f\n", x, y);
    } 
    else {
        printf("%14.6f | UNDEFINED\n", x);
    }
}

void processTable(double a, double h, int pointsQuantity, double domainEps, int *validCount, int *invalidCount, double *minY, double *maxY, double *averageY) {
    int i = 0, isDefined = 0;
    double x = 0.0, y = 0.0, sum = 0.0;
    *validCount = 0;
    *invalidCount = 0;
    *minY = 0.0;
    *maxY = 0.0;
    *averageY = 0.0;

    for (i = 0; i < pointsQuantity; i++) {
        x = a + i * h;
        y = 0.0;
        isDefined = checkDomain(x, domainEps);

        if (isDefined) {
            y = findFormula(x);
            if (*validCount == 0 || y < *minY) {
                *minY = y;
            }
            if (*validCount == 0 || y > *maxY) {
                *maxY = y;
            }
            sum = sum + y;
            (*validCount)++;
        } 
        else {
            (*invalidCount)++;
        }
        printValue(x, y, isDefined);
    }

    if (*validCount > 0) {
        *averageY = sum / *validCount;
    }
}

void findIteration(double z, double eps, int maxIterations, double *approximation, int *iterations, double *reference, double *difference, int *isConverged) {
    double term = 1.0;
    *approximation = 1.0;
    *iterations = 0;

    while (fabs(term) > eps && *iterations < maxIterations) {
        (*iterations)++;
        term = term * z / *iterations;
        *approximation = *approximation + term;
    }

    *isConverged = (fabs(term) <= eps);
    *reference = exp(z);
    *difference = fabs(*approximation - *reference);
}

void printInput(double a, double b, double h, double z, int pointsQuantity, double eps) {
    printf("\nИсходные данные:\n");
    printf("a = %f; b = %f; h = %f\n", a, b, h);
    printf("Количество точек: %d\n", pointsQuantity);
    printf("z = %f; eps = %f\n", z, eps);

    printf("\nТаблица значений:\n");
    printf("             x |                y\n");
}

void printStatistics(int validCount, int invalidCount, double minY, double maxY, double averageY) {
    printf("\nСтатистика:\n");
    printf("Допустимых точек = %d\n", validCount);
    printf("Недопустимых точек = %d\n", invalidCount);

    if (validCount > 0) {
        printf("Минимальный y = %.10f\n", minY);
        printf("Максимальный y = %.10f\n", maxY);
        printf("Средний y = %.10f\n", averageY);
    } 
    else {
        printf("Допустимых точек нет. Минимум, максимум и среднее не определены.\n");
    }
}

void printOutput(double approximation, double reference, double difference, int iterations, int isConverged) {
    printf("\nИтерационное вычисление exp(z):\n");
    printf("Приближённое значение: %.10f\n", approximation);
    printf("Значение exp(z):       %.10f\n", reference);
    printf("Абсолютная разность:   %.10f\n", difference);
    printf("Количество членов N:   %d\n", iterations);

    if (!isConverged) {
        printf("Достигнут лимит итераций. Требуемая точность не достигнута.\n");
    }
}

int main(void) {
    const int MIN_INPUT = -1000000;
    const int MAX_INPUT = 1000000;
    const int MAX_POINTS = 1000;
    const int MAX_ITERATIONS = 100000;
    const double DOMAIN_EPS = 0.000000001;
    const double EPS = 0.0001;

    double a = 0.0, b = 0.0, h = 0.0, z = 0.0;
    double minY = 0.0, maxY = 0.0, averageY = 0.0;
    double approximation = 0.0, reference = 0.0, difference = 0.0;
    int pointsQuantity = 0, validCount = 0, invalidCount = 0, iterations = 0, isConverged = 0;

    setlocale(LC_CTYPE, ".UTF-8");
    readValues(&a, &b, &h, &z, &pointsQuantity, MIN_INPUT, MAX_INPUT, MAX_POINTS);
    printInput(a, b, h, z, pointsQuantity, EPS);
    processTable(a, h, pointsQuantity, DOMAIN_EPS, &validCount, &invalidCount, &minY, &maxY, &averageY);
    printStatistics(validCount, invalidCount, minY, maxY, averageY);
    findIteration(z, EPS, MAX_ITERATIONS, &approximation, &iterations, &reference, &difference, &isConverged);
    printOutput(approximation, reference, difference, iterations, isConverged);

    return 0;
}