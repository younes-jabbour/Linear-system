#include <stdio.h>
#include <stdlib.h>
#include "systeme.h"

int main()
{

    int N;
    printf("Entrez la taille de la matrice: ");
    scanf("%d", &N);
    systeme_t sys = scan_sys(N);
    sys = triangularize(sys);

    if (is_cramer(sys))
    {
        sys = solve_sys(sys);
        printf("\n");
        printf("Le systeme est un systeme de cramer\n");
        printf("\n");
        print_sys(sys);
    }
    else

        printf("Le systeme n'est pas un systeme de cramer");

    return 0;
}