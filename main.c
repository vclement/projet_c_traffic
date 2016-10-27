#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


typedef struct voiture VEHICULE;
struct voiture
{
    unsigned char car; /* N, S, E, O, A, P, D */
    unsigned char infos; /*Les infos doivent etre stockes sur les 8 bits*/
    int posX, posY;
};

//Cette fonction permet de faire avancer le tram tout en gérant les sens de ciruclation
void bouge_tram1(int posX, int posY, int *sens, int numero, int i){
    //Fonction qui s'execute apres le temps de fin.
    printf("\033[%d;%dH🚌 🚌 🚌 \n",posX,posY);
    if(*sens==0 && numero==0 && posY%75==0 && i>0){
        *sens=1;
    }
    else if(*sens==1 && numero==0 && posY%75==0 && i>0)
        *sens=0;
}

//Cette fonction permet de gérer l'effacement du tram précédent.
void bouge_tram2(int posX,int* posY, int sens, int numero){
    //Fonction qui s'execute apres l'ecoulement du temps.
    printf("\033[1;91m");
    printf("\033[%d;%dH------\n",posX,*posY);
    printf("\033[0m");
    if(sens==0 && numero==0)
        *posY= *posY+1;
    else if(sens==0 && numero==1)
        *posY= *posY-1;

    else if(sens==1 && numero==0)
        *posY = *posY-1;
    else if(sens==1 && numero==1)
        *posY = *posY+1;
}


/*
 * Cette fonction va s'occuper de gérer les feux rouges
 * Lorsque les feux rouges sont allumés dans le nord de la circulation il le sont aussi dans l'est
 * Et le feu du sud est allumé
 */
void gestion_feu_rouge(int allume){
    //Feu rouge
    if(allume == 1)
        printf("\033[1;91m"); 
    else
        printf("\033[0m");
    printf("\033[12;39H█\n"); //Pos 12,39
    printf("\033[16;39H█\n"); //Pos 16,39
    printf("\033[22;21H█\n"); //Pos 22,22
    printf("\033[26;21H█\n"); //Pos 26,22
    if(allume == 1)
        printf("\033[1;32m");
    else
        printf("\033[0m");
    printf("\033[29;30H█\n"); //Pos 24,34
    printf("\033[0m");
}

//Pour des raisons de simplification, le feu passe a l'orange a chaque fois que l'on passe du feu vert au rouge et inversement.
void gestion_feu_orange(int allume){
    //Feu orange
    if(allume == 1)
        printf("\033[1;33m");
    else
        printf("\033[0m");

    printf("\033[12;40H█\n"); //Pos 12,39
    printf("\033[16;40H█\n"); //Pos 16,39
    printf("\033[22;20H█\n"); //Pos 22,23
    printf("\033[26;20H█\n"); //Pos 26,23
    printf("\033[28;30H█\n"); //Pos 24,34
    printf("\033[0m");
}

// Cette fonction est l'inverse de la fonction feu rouge
void gestion_feu_vert(int allume){
    //Feu Vert 
    if(allume == 1)
        printf("\033[1;32m");
    else
        printf("\033[0m");

    printf("\033[12;41H█\n"); //Pos 12,39
    printf("\033[16;41H█\n"); //Pos 16,39
    printf("\033[22;19H█\n"); //Pos 22,23
    printf("\033[26;19H█\n"); //Pos 26,23
    if(allume == 1)
        printf("\033[1;91m");
    else
        printf("\033[0m");
    printf("\033[27;30H█\n"); //Pos 26,34

    printf("\033[0m");
}

//Cette fonction permet de generer automatiquement les informations concernant le vehicule.
void genere_infos(unsigned char *infos){
    //int y=0;
    //y=rand()%(240-16)+16;
    *infos = (1+4+8+16+32+128);
}


//Cette fonction permet de connaitre la valeur d'un bit à la position donné.
unsigned char valeur_bit(unsigned char info, int numero){
    unsigned char val;
    switch(numero){
        case 0:
            val = ((info>>numero)&1) ? '1':'0';
            break;
        case 1:
            val = ((info>>numero)&1) ? '1':'0';
            break;
        case 2:
            val = ((info>>numero)&1) ? '1':'0';
            break;
        case 3:
            val = ((info>>numero)&1) ? '1':'0';
            break;
        case 4:
            val = ((info>>numero)&1) ? '1':'0';
            break;
        case 5:
            val = ((info>>numero)&1) ? '1':'0';
            break;
        case 6:
            val = ((info>>numero)&1) ? '1':'0';
            break;
        case 7:
            val = ((info>>numero)&1) ? '1':'0';
            break;
        case 8:
            val = ((info>>numero)&1) ? '1':'0';
            break;
        default:
            val='?';
            break;
    }
    return val;
}

void place_voiture(VEHICULE *voiture){
    if(valeur_bit(voiture->infos, 4)=='1' && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='0'){
        //Voiture qui pars du Sud vers le Sud
        voiture->posX=36;
        voiture->posY=24;
    }
    if(valeur_bit(voiture->infos, 4)==0 && valeur_bit(voiture->infos,5)==1 && valeur_bit(voiture->infos,6)==0 && valeur_bit(voiture->infos,7)==0){
        //Voiture qui pars du Sud vers l'Est
        voiture->posX=36;
        voiture->posY=22;
    }
    if(valeur_bit(voiture->infos, 4)==1 && valeur_bit(voiture->infos,5)==1 && valeur_bit(voiture->infos,6)==0 && valeur_bit(voiture->infos,7)==0){
        //Voiture qui pars du Sud vers le Nord
        voiture->posX=36;
        voiture->posY=22;
    }
    if(valeur_bit(voiture->infos, 4)==0 && valeur_bit(voiture->infos,5)==0 && valeur_bit(voiture->infos,6)==1 && valeur_bit(voiture->infos,7)==0){
        //Voiture qui pars du Sud vers l'Ouest
        voiture->posX=36;
        voiture->posY=22;
    }
    if(valeur_bit(voiture->infos, 4)==1 && valeur_bit(voiture->infos,5)==0 && valeur_bit(voiture->infos,6)==1 && valeur_bit(voiture->infos,7)==0 ){
        //Voiture qui pars de l'Ouest vers le l'Ouest
        voiture->posX=36;
        voiture->posY=22;
    }
    if(valeur_bit(voiture->infos, 4)==0 && valeur_bit(voiture->infos,5)==1 && valeur_bit(voiture->infos,6)==1 && valeur_bit(voiture->infos,7)==0){
        //Voiture qui pars de l'Ouset vers le Sud
        voiture->posX=36;
        voiture->posY=22;
    }
    if(valeur_bit(voiture->infos, 4)==1 && valeur_bit(voiture->infos,5)==1 && valeur_bit(voiture->infos,6)==1 && valeur_bit(voiture->infos,7)==0 ){
        //Voiture qui pars de l'Ouest vers l'Est
        voiture->posX=36;
        voiture->posY=22;
    }
    if(valeur_bit(voiture->infos, 4)==0 && valeur_bit(voiture->infos,5)==0 && valeur_bit(voiture->infos,6)==0 && valeur_bit(voiture->infos,7)==1 ){
        //Voiture qui pars de l'Ouest vers le Nord
        voiture->posX=36;
        voiture->posY=22;
    }
    if(valeur_bit(voiture->infos, 4)==1 && valeur_bit(voiture->infos,5)==0 && valeur_bit(voiture->infos,6)==0 && valeur_bit(voiture->infos,7)==1 ){
        //Voiture qui pars de l'Est vers l'Est
        voiture->posX=36;
        voiture->posY=22;
    }
    if(valeur_bit(voiture->infos, 4)==0 && valeur_bit(voiture->infos,5)==1 && valeur_bit(voiture->infos,6)==0 && valeur_bit(voiture->infos,7)==1 ){
        //Voiture qui pars de l'Est vers le Nord
        voiture->posX=36;
        voiture->posY=22;
    }
    if(valeur_bit(voiture->infos, 4)=='1' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='1' ){
        //Voiture qui pars de l'Est vers l'Ouest
        voiture->posX=24;
        voiture->posY=36;
    }
    if(valeur_bit(voiture->infos, 4)==0 && valeur_bit(voiture->infos,5)==0 && valeur_bit(voiture->infos,6)==1 && valeur_bit(voiture->infos,7)==1 ){
        //Voiture qui pars de l'Est vers le Sud
        voiture->posX=36;
        voiture->posY=24;
    }
}

void affiche_voiture(VEHICULE voiture){
    //affiche la voiture a sa position
    printf("  %d ; %d", voiture.posX, voiture.posY); 
    printf("\033[%d;%dH🚘\n",voiture.posY,voiture.posX); //Pos x,y
}

int main(){
    //Corps du code
    srand(time(NULL));
    VEHICULE rouge;
    FILE * carte;
    char c;
    int i=0;

    carte = fopen("carte.texte","r");

    printf("Ouverture du fichier, demarrage de la lecture et démarrage des moteurs...\n");

    //Cette première boucle while vient lire la carte et pose le décor ;-)
    while((c=fgetc(carte))!=EOF){
        //printf("%c",c);
        if(c=='o')
            printf("\033[m ");
        else if(c=='f')
            printf("\033[m█");
        else if(c=='g')
            printf("\033[m≡");
        else if(c=='t' || c=='x')
            printf("\033[1;91m-\033[0m");
        else if(c=='T')
            printf("\033[m▓");
        else if(c=='_')
            printf("\033[m═");
        else if(c=='|')
            printf("\033[m║");
        else if(c=='p')
            printf("\033[m■");
        else if(c=='c')
            printf("\033[m╝");
        else if(c=='v')
            printf("\033[m╚");
        else if(c=='n')
            printf("\033[m╗");
        else if(c=='w')
            printf("\033[m╔");
        else if(c=='h')
            printf("\033[m═");
        else
            printf("\033[0m%c",c);
    }
    //Pour mettre a une position: printf("\033[%d;%dH🚘",45,12);
    //printf("\033[%d;%dH🚘",16,15);
    int x=13, y=0, y2=80, x2=15;
    int tramX1=18, tramY1=0, tramX2=20, tramY2=75;
    int sens_tram=0;
    unsigned char temp = temp^temp;;
    rouge.posX=x;
    rouge.posY=y;
    rouge.car=' ';
    gestion_feu_rouge(0);
    genere_infos(&rouge.infos);

    for(y=7;y>=0;y--){
        temp = valeur_bit(rouge.infos, y);
        printf("%c",temp);
    } 
   
    place_voiture(&rouge); 
    
    affiche_voiture(rouge);
   
    //Boucle infini permettant la visualisation du traffic
    while(i<240){
        //printf("\033[%d;%dH🚘\n",rouge.posX,rouge.posY);
        //printf("\033[%d;%dH🚘\n",x2,y2);

        //On fait avancer le tram
        bouge_tram1(tramX1,tramY1, &sens_tram, 0, i);
        bouge_tram1(tramX2,tramY2, &sens_tram, 1, i);
        //On ne gere que 2 tramway

        if(i<40){
            gestion_feu_rouge(1);
            gestion_feu_vert(0);
        }
        else if(i==40){
            gestion_feu_rouge(0);
            gestion_feu_orange(1);
        }


        usleep(100000);




        if(i>42){
            gestion_feu_orange(0);
            gestion_feu_vert(1);
        }


        bouge_tram2(tramX1,&tramY1, sens_tram, 0);
        bouge_tram2(tramX2,&tramY2, sens_tram, 1);

        //printf("\033[%d;%dH  \n",x2,y2);
        //printf("\033[%d;%dH  \n",rouge.posX,rouge.posY);
        rouge.posY++;
        y2--;

        //On fait avancer notre compteur pour savoir ou on en est dans le temps.
        i++;
    }


    printf("\033[45;0H ");
    return 0;
}

