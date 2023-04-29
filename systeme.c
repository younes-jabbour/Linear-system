#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "systeme.h"

// l'initailisation du systeme avec la taille et les valeurs de la matrice et aussi les valeurs du vecteur Y.

systeme_t scan_sys(int N)
{

    systeme_t sys;
    sys.N = N;
    int i, j;
    sys.matrice_a = (double **)malloc(N * sizeof(double *));
    sys.vecteur_y = (double *)malloc(N * sizeof(double));
    sys.vecteur_x = (double *)malloc(N * sizeof(double));

    for (i = 0; i < N; i++)
    {
        sys.matrice_a[i] = (double *)malloc(N * sizeof(double));
        for (j = 0; j < N; j++)
        {
            printf("Entrez la valeur de la matrice A[%d][%d]: ", i, j);
            scanf("%lf", &sys.matrice_a[i][j]);
        }
    }

    for (i = 0; i < N; i++)
    {
        printf("Entrez la valeur du vecteur Y[%d]: ", i);
        scanf("%lf", &sys.vecteur_y[i]);
    }

    return sys;
}

// fonction "triangularize" prend un systeme en parametre et retourne le systeme avec la matrice de la forme triangulaire supérieur

systeme_t triangularize(systeme_t sys)
{

    int i, j, k;
    double pivot, temp;

    for (i = 0; i < sys.N; i++)
    {
        pivot = sys.matrice_a[i][i];

        // la permutation des lignes si le pivot est a 0 .
        if (pivot == 0)
        {
            for (j = i + 1; j < sys.N; j++)
            {
                if (sys.matrice_a[j][i] != 0)
                {
                    for (k = 0; k < sys.N; k++)
                    {
                        temp = sys.matrice_a[i][k];
                        sys.matrice_a[i][k] = sys.matrice_a[j][k];
                        sys.matrice_a[j][k] = temp;
                    }
                    temp = sys.vecteur_y[i];
                    sys.vecteur_y[i] = sys.vecteur_y[j];
                    sys.vecteur_y[j] = temp;
                    break;
                }
            }
        }

        // la combinaison linéaire des lignes pour avoir la forme triangulaire supérieur

        for (j = i + 1; j < sys.N; j++)
        {
            temp = sys.matrice_a[j][i] / sys.matrice_a[i][i];
            for (k = 0; k < sys.N; k++)
            {
                sys.matrice_a[j][k] -= temp * sys.matrice_a[i][k];
            }
            sys.vecteur_y[j] -= temp * sys.vecteur_y[i];
        }
    }
    return sys;
}

/* apres que nous avons obtenu le forme triangulaire supérieur on peut verfier ( si la matrice est m de cramer ou non ) 
a travers le calcule du determinant par la multiplication des elements de la diagonale principale , 
et si le determiant est NULL cela indique qu'il n'est pas inversible et par consequent le systeme n'est pas un systeme de cramer */

int is_cramer(systeme_t sys)
{
    int i, j;
    double det = 1;
    for (i = 0; i < sys.N; i++)
        det *= sys.matrice_a[i][i];
 
    if (det == 0)
             return 0;
    else
             return 1;
}


systeme_t solve_sys(systeme_t sys)
{
    int i, j;
    double temp;
    for (i = sys.N - 1; i >= 0; i--)
    {
        temp = sys.vecteur_y[i];
        for (j = i + 1; j < sys.N; j++)
        {
            temp -= sys.matrice_a[i][j] * sys.vecteur_x[j];
        }
        sys.vecteur_x[i] = temp / sys.matrice_a[i][i];
    }
    return sys;
}

// fonction " print_sys " pour affiche le systeme AX = Y ou A est la forme triangulaire supérieur et X est le vecteur qui contient le N-uplet des solutions .

void print_sys(systeme_t sys)
{
    int i, j;
    for (i = 0; i < sys.N; i++)
    {
        for (j = 0; j < sys.N; j++)
        {
            printf("%.2lf\t", sys.matrice_a[i][j]);
        }
        printf("| %.2lf | %.2lf", sys.vecteur_y[i], sys.vecteur_x[i]);
        printf("\n");
    }
}
