#include <stdio.h>

int main(void)
{
    // --- Variables contenant les valeurs affichees ---
    int vitesse  = 245;   // km/h, echelle 0 a 300
    int altitude = 3200;  // ft, echelle 2000 a 4000
    int cap      = 235;   // degres, 0 a 360
    int tangage  = 5;     // degres, angle de montee/descente, echelle -10 a 10
    int virage   = -12;   // degres, angle d'inclinaison (banque), echelle -20 a 20

    // --- Positions (colonnes) des reperes deduites par calcul ---
    // la ligne "0  100  200  300" commence a la colonne 3, "300" est a la colonne 21
    int col_vitesse = 3 + vitesse * 18 / 300;
    // la ligne "2000  3000  4000" commence a la colonne 59, "4000" est a la colonne 74
    int col_altitude = 59 + (altitude - 2000) * 15 / 2000;
    // la ligne "L  20   10   0   10   20  R" : "L" est a la colonne 26, "R" a la colonne 52
    int col_virage = 26 + (virage + 20) * 26 / 40;

    // --- Repere de tangage deduit par comparaisons (l'un des 5 barreaux) ---
    char m10[3] = "  ", m5[3] = "  ", m0[3] = "  ", mm5[3] = "  ", mm10[3] = "  ";
    if (tangage >= 8)                        { m10[0]  = '-'; m10[1]  = '>'; }
    else if (tangage >= 3)                   { m5[0]   = '-'; m5[1]   = '>'; }
    else if (tangage > -3)                   { m0[0]   = '-'; m0[1]   = '>'; }
    else if (tangage > -8)                   { mm5[0]  = '-'; mm5[1]  = '>'; }
    else                                      { mm10[0] = '-'; mm10[1] = '>'; }

    // --- Point cardinal deduit du cap par comparaisons ---
    char cardinal[3];
    if (cap >= 338 || cap < 23)  { cardinal[0] = 'N'; cardinal[1] = '\0'; }
    else if (cap < 68)  { cardinal[0] = 'N'; cardinal[1] = 'E'; cardinal[2] = '\0'; }
    else if (cap < 113) { cardinal[0] = 'E'; cardinal[1] = '\0'; }
    else if (cap < 158) { cardinal[0] = 'S'; cardinal[1] = 'E'; cardinal[2] = '\0'; }
    else if (cap < 203) { cardinal[0] = 'S'; cardinal[1] = '\0'; }
    else if (cap < 248) { cardinal[0] = 'S'; cardinal[1] = 'O'; cardinal[2] = '\0'; }
    else if (cap < 293) { cardinal[0] = 'O'; cardinal[1] = '\0'; }
    else                { cardinal[0] = 'N'; cardinal[1] = 'O'; cardinal[2] = '\0'; }

    // --- Affichage du tableau de bord ---
    printf("        ANEMOMETRE              HORIZON ARTIFICIEL            ALTIMETRE\n");
    printf("       +----------+                                          +----------+\n");
    printf("       |          |         %s 10 ----------------          |          |\n", m10);
    printf("       |   %3d    |         %s  5 -------------             |  %4d    |\n", vitesse, m5, altitude);
    printf("       |   km/h   |         %s----[     +     ]----          |    ft    |\n", m0);
    printf("       |          |         %s -5 -------------              |          |\n", mm5);
    printf("       +----------+         %s-10 ----------------           +----------+\n", mm10);
    printf("   0   100   200   300                                     2000  3000  4000\n");
    printf("   |....|....|....|....|                                    |.....|.....|\n");
    printf("%*c%*c\n", col_vitesse + 1, '^', col_altitude - col_vitesse, '^');
    printf("\n");
    printf("                          L  20   10   0   10   20  R\n");
    printf("                          |...|...|...|...|...|...|\n");
    printf("%*c\n", col_virage + 1, '^');
    printf("                                 VIRAGE : %3d deg\n", virage);
    printf("\n");
    printf("                            ----------------------\n");
    printf("                           |          N           |\n");
    printf("                           |     NO       NE      |\n");
    printf("                           |   O      X      E    |\n");
    printf("                           |     SO       SE      |\n");
    printf("                           |          S           |\n");
    printf("                            ----------------------\n");
    printf("                               CAP : %3d deg (%s)\n", cap, cardinal);

    return 0;
}