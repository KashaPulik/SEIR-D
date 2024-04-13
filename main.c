#include <stdio.h>

double N(double S, double E, double I, double R, double D)
{
    return S + E + I + R + D;
}

double SEIRD(double S0, double E0, double I0, double R0, double D0, int t0, double t, double h)
{
    double S = S0, E = E0, I = I0, R = R0, D = D0;
    int i = t0;
    t /= h;
    for (; i < t; i++) {
        S = S0 + h * (((0.999 * S0) / N(S0, E0, I0, R0, D0)) * (I0 + E0));
        E = E0 + h * (((0.999 * S0) / N(S0, E0, I0, R0, D0)) * (I0 + E0) - 0.994 * E0);
        I = I0 + h * (0.042 * E0 - 1.0178 * I0);
        R = R0 + h * (0.999 * I0 + 0.952 * E0);
        D = D0 + h * (0.0188 * I0);
        S0 = S;
        E0 = E;
        I0 = I;
        R0 = R;
        D0 = D;
    }
    return ((i + 1) * E) / 0.58;
}

int main()
{
    FILE* file = fopen("data.txt", "w");
    for (int i = 1; i <= 90; i++) {
        fprintf(file, "%d  %f\n", i, SEIRD(2798047, 99, 0, 24, 0, 0, i, 0.01));
    }
    fclose(file);
}