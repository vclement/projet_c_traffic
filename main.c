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
void affiche_voiture(VEHICULE* voiture);

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
    int y=0;
    //le tableau ci-dessous représente les 12 trajets possibles pour un véhicule.
    int trajets[12]={16,32,48,64,80,96,112,128,144,160,176,192};
    y=rand()%12;
    *infos = (1+4+8)+trajets[y];
    //*infos = (1+4+8)+(128+32);
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
        voiture->posX=28;
        voiture->posY=36;
    }
    else if(valeur_bit(voiture->infos, 4)=='0' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='0'){
        //Voiture qui pars du Sud vers l'Est
        voiture->posX=28;
        voiture->posY=36;
    }
    else if(valeur_bit(voiture->infos, 4)=='1' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='0'){
        //Voiture qui pars du Sud vers le Nord
        voiture->posX=28;
        voiture->posY=36;
    }
    else if(valeur_bit(voiture->infos, 4)=='0' && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='1' && valeur_bit(voiture->infos,7)=='0'){
        //Voiture qui pars du Sud vers l'Ouest
        voiture->posX=28;
        voiture->posY=36;
    }
    else  if(valeur_bit(voiture->infos, 4)=='1' && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='1' && valeur_bit(voiture->infos,7)=='0' ){
        //Voiture qui pars de l'est vers le l'Ouest
        voiture->posX=80;
        voiture->posY=13;
    }
    else if(valeur_bit(voiture->infos, 4)=='0' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='1' && valeur_bit(voiture->infos,7)=='0'){
        //Voiture qui pars de l'est vers le Sud
        voiture->posX=80;
        voiture->posY=13;
    }
    else if(valeur_bit(voiture->infos, 4)=='1' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='1' && valeur_bit(voiture->infos,7)=='0' ){
        //Voiture qui pars de l'est vers l'Est
        voiture->posX=80;
        voiture->posY=13;
    }
    else if(valeur_bit(voiture->infos, 4)=='0' && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='1' ){
        //Voiture qui pars de l'est vers le Nord
        voiture->posX=80;
        voiture->posY=13;
    }
    else  if(valeur_bit(voiture->infos, 4)=='1' && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='1' ){
        //Voiture qui pars de l'ouest vers l'Est
        voiture->posX=1;
        voiture->posY=25;
    }
    else if(valeur_bit(voiture->infos, 4)=='0' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='1' ){
        //Voiture qui pars de l'ouest vers le Nord
        voiture->posX=1;
        voiture->posY=25;
    }
    else if(valeur_bit(voiture->infos, 4)=='1' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='1' ){
        //Voiture qui pars de l'ouest vers l'Ouest
        voiture->posX=1;
        voiture->posY=25;
    }
    else if(valeur_bit(voiture->infos, 4)=='0' && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='1' && valeur_bit(voiture->infos,7)=='1' ){
        //Voiture qui pars de l'ouest vers le Sud
        voiture->posX=1;
        voiture->posY=25;
    }
    else if(valeur_bit(voiture->infos, 4)=='1' && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='1' ){
        //Si on ne trouve pas ce que l'on veut, la voiture pars de l'ouest vers l'est
        voiture->posX=80;
        voiture->posY=13;
    }
    else{ 
        //Si on ne trouve pas ce que l'on veut, la voiture pars de l'ouest vers l'est
        voiture->posX=80;
        voiture->posY=13;

    }
}
void affiche_vide(VEHICULE *voiture){
    //Fonction pour faire avancer une voiture vers la droite
    printf("\033[%d;%dH  ",voiture->posY,voiture->posX);
    usleep(2);
}

void affiche_voiture(VEHICULE* voiture){
    //Cette fonction permet d'afficher un vehicule a l'ecran
    printf("\033[%d;%dH🚘 ",voiture->posY,voiture->posX);
}

void secteur_1(){
    //Premier tronçon qui se trouve sur le nord
}
void secteur_2(VEHICULE *voiture){
    //C'est la route qui permet de sortir à l'est et qui vient de l'ouest
    affiche_vide(voiture);
    voiture->posX++;
    affiche_voiture(voiture);
}
void secteur_3(){
    //C'est le carrefour avec le tram
}
void secteur_4(VEHICULE *voiture){
    //C'est la route qui permet de sortir à l'ouest et qui vient de l'est
    affiche_vide(voiture);
    voiture->posX--;
    affiche_voiture(voiture);
}
void secteur_5(VEHICULE* voiture){
    //C'est la route du Sud qui vient et qui pars du Sud
    int temp;
    temp=voiture->posY;
    voiture->posY--;
    printf("\033[%d;%dH🚘 ",voiture->posY,voiture->posX);
    printf("\033[%d;%dH ",temp,voiture->posX);
}

void secteur_6(VEHICULE* voiture){
    affiche_vide(voiture);
    voiture->posY++;
    affiche_voiture(voiture);

}

void avance_voiture(VEHICULE* voiture, int feu){
    //On gère l'avancée de la voiture test, puis apres on aura une boucle pour gérer tous les vehicules.
    
        if(voiture->posX<=80 && voiture->posX>=37 && voiture->posY == 13){// Cas 6
            //printf("chevre ");
            secteur_4(voiture);
        }
        if(voiture->posX>=-1 && voiture->posX<=23 && (voiture->posY >= 22 || voiture->posY <= 26)){ // Cas 1
            //printf("vache");
            secteur_2(voiture);
        }
        if(voiture->posY<=36 && voiture->posY>=26 && voiture->posX==28){ // Cas 3
            //printf("mouton");
            secteur_5(voiture);
        }
        if(voiture->posX == 24 && voiture->posY<=36 && voiture->posY >= 25 ){ // Cas 2
            secteur_6(voiture);
        }
        else if( voiture->posX == 24 && voiture->posY>=16 && voiture->posY<=22){//Cas 9
            secteur_6(voiture);
        }
        if(voiture->posX >= 25 && voiture->posX <36 && voiture->posY==25){// Cas 4
            secteur_2(voiture);
        }
        if(voiture->posY == 25 && voiture->posX >37 && voiture->posX <81){// Cas 5
            secteur_2(voiture);
        }
        if( (voiture->posY == 15 || voiture->posY == 13) && voiture->posX <= 35 && voiture->posX > 24){// Cas 7
            secteur_4(voiture);
        }
        if( (voiture->posY == 15 || voiture->posY == 13) && voiture->posX <= 23 && voiture->posX >= 1  ){// Cas 8
            secteur_4(voiture);
        }
        if( (voiture->posX == 32 || voiture->posX == 36) && voiture->posY <= 12 && voiture->posY > 0  ){// Cas 11
            secteur_5(voiture);
        }
        else if( voiture->posX == 36 && voiture->posY >= 16 && voiture->posY<=23 ){//Cas 10
            secteur_5(voiture);
        }
            
        if(voiture->posX==24 && voiture->posY == 24 && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='1' && valeur_bit(voiture->infos,7)=='1' ){ //Cas 12
            secteur_6(voiture);
        }
         
        if(voiture->posX==36 && (voiture->posY == 13 || voiture->posY == 15)){//Cas 14
            if(valeur_bit(voiture->infos,4)=='1' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='0'  ){
                secteur_5(voiture);
                secteur_5(voiture);
                secteur_5(voiture);
            }
            else if( valeur_bit(voiture->infos,4)=='0' && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='1' ){
                secteur_5(voiture);
                secteur_5(voiture);
                secteur_5(voiture);
            }
            else if( valeur_bit(voiture->infos,4)=='0' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='1' ){
                secteur_5(voiture);
                secteur_5(voiture);
                secteur_5(voiture);
            }
            else 
                secteur_4(voiture);
        }

        if(voiture->posX==24 && (voiture->posY == 13 || voiture->posY ==15)){//Cas 15
            if(valeur_bit(voiture->infos,4)=='0' && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='1' && valeur_bit(voiture->infos,7)=='0'  ){
                secteur_4(voiture);
            }
            else if( valeur_bit(voiture->infos,4)=='1' && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='1' && valeur_bit(voiture->infos,7)=='0' ){
                secteur_4(voiture);
            }
            else if( valeur_bit(voiture->infos,4)=='1' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='1' ){
                secteur_4(voiture);
            }
            else{ 
                secteur_6(voiture);
                secteur_6(voiture);
                secteur_6(voiture);
            }
        }
        
        else if(voiture->posX==24 && voiture->posY == 23  ){//Cas 12
            if(valeur_bit(voiture->infos,4)=='1' && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='0'  ){
                secteur_6(voiture);            
                secteur_6(voiture);
                secteur_6(voiture);
            }
            else if( valeur_bit(voiture->infos,4)=='0' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='1' && valeur_bit(voiture->infos,7)=='0' ){
                secteur_6(voiture);   
                secteur_6(voiture);   
                secteur_6(voiture);   
            }         
            else if( valeur_bit(voiture->infos,4)=='0' && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='1' && valeur_bit(voiture->infos,7)=='1' ){
                secteur_6(voiture);   
                secteur_6(voiture);   
                secteur_6(voiture);
            }
            else if( valeur_bit(voiture->infos,4)=='0' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='1' ){
                secteur_6(voiture);   
                secteur_6(voiture);   
                secteur_6(voiture);
            }
            else{ 
                secteur_6(voiture);
                secteur_6(voiture);
                secteur_2(voiture);
                secteur_2(voiture);
                secteur_2(voiture);
            }
        }
        
        if(voiture->posX==36 && voiture->posY == 25){//Cas 13
            if(valeur_bit(voiture->infos,4)=='1' && valeur_bit(voiture->infos,5)=='0' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='1'  ){
                secteur_2(voiture);
                secteur_2(voiture);
            }
            else if( valeur_bit(voiture->infos,4)=='1' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='1' && valeur_bit(voiture->infos,7)=='0' ){
                secteur_2(voiture);
                secteur_2(voiture);
            }
            else if( valeur_bit(voiture->infos,4)=='0' && valeur_bit(voiture->infos,5)=='1' && valeur_bit(voiture->infos,6)=='0' && valeur_bit(voiture->infos,7)=='0' ){
                secteur_2(voiture);
                secteur_2(voiture);
            }
            else{
                secteur_5(voiture);
                secteur_5(voiture);
                secteur_5(voiture);
            }
        }
        
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
    int x=13, y=0, y2=80;
    int tramX1=18, tramY1=0, tramX2=20, tramY2=75;
    int sens_tram=0;
    int feu=0;
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

    int j=0;
    VEHICULE voit[12];
    for(j=0; j<12; j++){
        voit[j].posX=0;
        voit[j].posY=0;
        genere_infos(&voit[j]);
    }
    j=0;
    int t;
    
    //Boucle infini permettant la visualisation du traffic
    while(i<240){
        place_voiture(&voit[j]);
           
        //On fait avancer le tram
        bouge_tram2(tramX1,&tramY1, sens_tram, 0);
        bouge_tram2(tramX2,&tramY2, sens_tram, 1);
        bouge_tram1(tramX1,tramY1, &sens_tram, 0, i);
        bouge_tram1(tramX2,tramY2, &sens_tram, 1, i);
        //On ne gere que 2 tramway

        //On gère uniquement la couleur des feux.
        if(i<40){
            gestion_feu_rouge(1);
            gestion_feu_vert(0);
            feu =0;
        }
        else if(i==40){
            gestion_feu_rouge(0);
            gestion_feu_orange(1);
            feu=0;
        }
        else if(i>42){
            gestion_feu_orange(0);
            gestion_feu_vert(1);
            feu=1;
        }

        if(rouge.posX>0 && rouge.posX<=80 && rouge.posY>=0 && rouge.posY<=36){
            avance_voiture(&rouge, feu);
            //printf("%d ; %d", rouge.posX, rouge.posY);
        }
        else
            affiche_vide(&rouge);
        //printf("toto");
        //affiche_voiture(rouge);


        for(t=0; t<j; t++){
            if(voit[t].posX>0 && voit[t].posX<=80 && voit[t].posY>=0 && voit[t].posY<=36)
                avance_voiture(&voit[t], feu);
            else
                affiche_vide(&voit[t]);
        }
        usleep(100000);
        if(j<12)
            j++;
        y2--;
        //On fait avancer notre compteur pour savoir ou on en est dans le temps.
        i++;
    }


    printf("\033[45;0H ");
    return 0;
}

