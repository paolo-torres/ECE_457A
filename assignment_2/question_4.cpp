#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

double getRandomValue(double min, double max) {
    double num = (double) rand() / RAND_MAX;
    return min + num * (max - min);
}

void applyAnnealingSchedule(double &temp, double alpha, int schedule) {
    if (schedule == 0 || schedule == 1) {
        temp -= alpha;
    } else if (schedule == 2) {
        temp -= 2 * alpha;
    } else if (schedule == 3) {
        temp -= 3 * alpha;
    } else if (schedule == 4) {
        temp *= alpha;
    } else if (schedule == 5) {
        temp *= 1.05 * alpha;
    } else if (schedule == 6) {
        temp *= 1.1 * alpha;
    } else if (schedule == 7) {
        temp /= 1 + 0.1 * alpha * temp;
    } else if (schedule == 8) {
        temp /= 1 + 0.01 * alpha * temp;
    } else if (schedule == 9) {
        temp /= 1 + 0.001 * alpha * temp;
    }
}

void simulatedAnnealing(double &x1Final, double &x2Final, double &easomFinal,
    double temp, double alpha, int schedule) {
    double tempFinal = 1;
    int iterations = 10;

    while (temp > tempFinal) {
        int i = 0;
        while (i < iterations) {
            double x1 = getRandomValue(-100, 100);
            double x2 = getRandomValue(-100, 100);
            double easom = -cos(x1) * cos(x2) * 
                exp(-(pow(x1 - M_PI, 2)) - pow(x2 - M_PI, 2));

            double change = easom - easomFinal;
            if (change < 0) {
                x1Final = x1;
                x2Final = x2;
                easomFinal = easom;
            } else {
                double x = getRandomValue(0, 1);
                if (x < exp(-change / temp)) {
                    x1Final = x1;
                    x2Final = x2;
                    easomFinal = easom;
                }
            }
            i++;
        }
        applyAnnealingSchedule(temp, alpha, schedule);
    }
}

int main() {
    srand((unsigned int) time(NULL));

    for (int i = 0; i < 10; i++) {
        double x1Final = getRandomValue(-100, 100);
        double x2Final = getRandomValue(-100, 100);
        double easomFinal = -cos(x1Final) * cos(x2Final) * 
            exp(-(pow(x1Final - M_PI, 2)) - pow(x2Final - M_PI, 2));

        double temp = getRandomValue(100, 1000);
        double alpha = getRandomValue(0.1, 0.9);

        simulatedAnnealing(x1Final, x2Final, easomFinal, temp, alpha, i);

        cout << "x1: " << x1Final << endl 
             << "x2: " << x2Final << endl 
             << "f(x1, x2): " << easomFinal << endl << endl;
    }

    return 0;
}
