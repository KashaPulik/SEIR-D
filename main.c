#include <stdio.h>

double SEIRD(double S0, double E0, double I0, double R0, double D0, double N0, int t0, int t, double h)
{
    double S = S0, E = E0, I = I0, R = R0, D = D0, N = N0;
    double Sn, En, In;
    int i = t0;
    for (; i < t - 1; i++) {
        Sn = S0 + h * (((0.999 * S0) / N0) * (I0 + E0));
        En = E0 + h * (((0.999 * S0) / N0) * (I0 + E0) - 0.994 * E0);
        In = I0 + h * (0.042 * E0 - 1.0178 * I0);
        R = R0 + h * 0.5 * (0.999 * I0 + 0.952 * E0 + 0.999 * In + 0.952 * En);
        D = D0 + h * 0.5 * (0.0188 * I0 + 0.0188 * In);
        N = Sn + En + In + R + D;
        S = S0 + h * 0.5 * (((0.999 * S0) / N0) * (I0 + E0) + ((0.999 * Sn) / N) * (In + En));
        E = E0 + h * 0.5 * (((0.999 * S0) / N0) * (I0 + E0) - 0.994 * E0 + ((0.999 * Sn) / N) * (In + En) - 0.994 * En);
        I = I0 + h * 0.5 * (0.042 * E0 - 1.0178 * I0 + 0.042 * En - 1.0178 * In);
        S0 = S;
        E0 = E;
        I0 = I;
        R0 = R;
        D0 = D;
        N0 = S + E + I + R + D;
    }
    return ((i + 1) * E) / 0.58;
}

int main()
{
    FILE *file = fopen("data.txt", "w");
    for (int i = 1; i <= 90; i++) {
        fprintf(file, "%d  %f\n", i, SEIRD(2798047, 99, 0, 24, 0, 2798170, 0, i, 1));
    }
    fclose(file);
}