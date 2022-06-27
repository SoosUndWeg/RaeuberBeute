#include <iostream>
#include <cmath>

#include "../Log.h"
#include "../Simulation/Map.h"
#include "../Simulation/Controller.h"
#include "../Simulation/Entity/Property.h"
#include "../Simulation/Entity/EntityLoader.h"

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

void kilian() {
    sim::Entity* Ente = new sim::Entity(sim::predator);
    sim::Map map(10);

    Ente->setAge(12);

    map.addEntity(Ente, 2, 2);

    std::cout << map.getEntity(2, 2)->getAge() << std::endl;
    map.print();

    sim::Entity* Fuchs = new sim::Entity(sim::EntityLoader().load("Preset.txt"));
    std::cout << Fuchs->getRole() << " " << Fuchs->getName() << std::endl;

    sim::Vision vision("Vision");
    std::cout << vision.getName() << std::endl;
    vision.setRange(2);
    Fuchs->setVision(vision);


    delete Fuchs;
}

int main() {
    //lina();

    kilian();

    std::cout << "\nAlle Prozesse beendet!" << std::endl;
    return 0;
}