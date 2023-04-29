
typedef struct systeme {    

    double** matrice_a ; // Matrice A
    double* vecteur_y ; // Vecteur Y
    double* vecteur_x ; // Vecteur X
    int N ; // Taille de la matrice
}systeme_t ;


//----------------------------- prototype des fonctions ----------------------------- //

systeme_t scan_sys(int N );


systeme_t triangularize(systeme_t sys);


int is_cramer(systeme_t sys);


systeme_t solve_sys(systeme_t sys);

void print_sys(systeme_t sys);
