#include <iostream>
#include "../Log.h"
#include <cmath>
#include "../Simulation/Entity/Animal.h"

double f(double t, double x) {                                        // Definition der Funktion f(t,x) 
    int i = 1;
    const int N = 2;
    double r[N] = { 0.9, -0.8 };
    double b[N][N] = { {-0.01, -0.02},
                       { 0.25, -0.05} };
    double summe = 0;
    double wert = 0;
    for (unsigned int j = 1; j < N; ++j) {
        summe += b[i][j] * x;
    }
    return (r[i] + summe) * x;                                        // Rueckgabewert der Funktion f(t,x)
}

void lina() {
    const int N = 2;
    double t_intervall[2] = { 0, 2 };                                   // Zeit-Intervall [a,b] in dem die Loesung berechnet werden soll
    double h = (t_intervall[0] - t_intervall[1]) / N;                   // Abstand dt zwischen den aequidistanten Punkten des t-Intervalls (h=dt)                                       
    double alpha = 0.5;                                               // Anfangswert bei t=a: y(a)=alpha
    double t;                                                         // Aktueller Zeitwert
    double x_RungeK_4 = alpha;                                        // Deklaration und Initialisierung der numerischen Loesung der Runge-Kutta Ordnung vier Methode
    double k1, k2, k3, k4;                                            // Deklaration der vier Runge-Kutta Parameter

    for (int i = 0; i <= N; ++i) {                                    // for-Schleife ueber die einzelnen Punkte des t-Intervalls
        t = t_intervall[0] + i * h;
        printf("%19.15f \n", x_RungeK_4);

        k1 = h * f(t, x_RungeK_4);                                    // Runge-Kutta Parameter 1
        k2 = h * f(t + h / 2, x_RungeK_4 + k1 / 2);                   // Runge-Kutta Parameter 2
        k3 = h * f(t + h / 2, x_RungeK_4 + k2 / 2);                     // Runge-Kutta Parameter 3
        k4 = h * f(t + h, x_RungeK_4 + k3);                           // Runge-Kutta Parameter 4
        x_RungeK_4 = x_RungeK_4 + (k1 + 2 * k2 + 2 * k3 + k4) / 6;    // Runge-Kutta Ordnung vier Methode
    }
}

int main() {
    //lina();

    sim::Animal Ente(sim::predator);
}
