
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "machine_Abstraite_Header.h"
#include "fonctElemListe.c"
#include "FonctionClavier.c"
#include "FileManipulation.c"

/*
#define BOTTUM_WIDTH 8

*/

// compil :  cd "d:\usthb\Alsdd\TD\TDProg\" ; if ($?) { g++ fonctionLLC.c -o Biblio_machineAbstraite } ; if ($?) { .\fonctionLLC }

void transferTabToMot(CelluleMot tabLetChange[TailleMaxMot], CelluleMot tabLet[TailleMaxMot], liste_combin p, int TailleMot)
{

  for (int i = 0; i < TailleMot ; i++)
  {
    tabLetChange[i].img = tabLet[abs(p->tab[i]) - 1].img;
    if ((p->tab[i]) < 0)
    {
      // tabLetChange[i].rotationEtPos = -1 *  tabLet[i].rotationEtPos ;
      tabLetChange[i].rotationEtPos = -1 * tabLet[abs(p->tab[i]) - 1].rotationEtPos;
    }
    else
      tabLetChange[i].rotationEtPos = tabLet[abs(p->tab[i]) - 1].rotationEtPos;
  }
}


void grilleMotButChoiceDraw( SDL_Window *Window , SDL_Renderer *renderer){
       if (SDL_SetRenderDrawColor(renderer , 125 , 25 , 33 , SDL_ALPHA_OPAQUE) != 0)
         SDL_ExitWithError("Color Draw Changing");

        if(SDL_RenderDrawLine(renderer , (40 + LETTER_WIDTH*8)   ,  100   ,(40 + LETTER_WIDTH*8) , 100 + 5*(LETTER_WIDTH+20) ) != 0)
        SDL_ExitWithError("Line Draw");

       if(SDL_RenderDrawLine(renderer , (40 + LETTER_WIDTH*16)   ,  100   ,(40 + LETTER_WIDTH*16) , 100 + 5*(LETTER_WIDTH+20) )!= 0)
        SDL_ExitWithError("Line Draw");

}


void AfficheCombinPossibles(SDL_Window *Window, SDL_Renderer *renderer, liste_combin *t, CelluleMot tabLet[TailleMaxMot], int npermut, int TailleMot, int *nbMotCompbin, liste_combin TabAdrComb[15])
{
    SDL_Rect Rectan;
  // remplir tableau eqv liste originale
  int T[TailleMaxMot];
  CelluleMot tabLetChange[TailleMaxMot];
  int x = 40, y = 100, cmp = 0;
  (*nbMotCompbin) = 0;
  int r, nbpossible;
  liste_combin tete, p;

  for (r = 0; r < TailleMaxMot; r++)
  {
    T[r] = r + 1;
  }
  
  printf("test taille max 8 : toute combine \n"); 
  tete = toute_combin(T, npermut, TailleMot);
  printf("test taille max 8 : 00 \n"); 
  (*t) = tete;
  p = tete->svt1;
int j =0 ;  
  if (tete == NULL)
    printf("loooser");
  while (p != NULL)
  {

    if (AfficheBool(p, TailleMot) == 0 && (*nbMotCompbin) < 15)
    {

      transferTabToMot(tabLetChange, tabLet, p, TailleMot);

      initRect(&Rectan, x, y, LETTER_WIDTH, LETTER_WIDTH);
      afficherTabWindow(tabLetChange, Window, renderer, Rectan, TailleMot);
      TabAdrComb[(*nbMotCompbin)] = p;
      x += 320;

      cmp++;
      if (cmp > 2)
      {
        cmp = 0;
        y += LETTER_WIDTH + 20;
        x = 40;
      }
      (*nbMotCompbin)++;
    }

    p = p->svt1;
  }
grilleMotButChoiceDraw( Window , renderer); 
  // afficher : choisissez le mot finale: ----------------------------------------------------------------
   SDL_Surface *ChoixMotFinale  = creeSurface("../src/images/motFinale.png", Window  , renderer ); 
   initRect(&Rectan , WINDOW_WIDTH/2 - 150 , 5 , 100 , 50 ); 
   afficher(Window , renderer , ChoixMotFinale , Rectan );
   SDL_FreeSurface(ChoixMotFinale); 
  //---------------------------------------------------------------------------------------------
  SDL_RenderPresent(renderer);
  printf("finished");
}







void UserPlays(SDL_Window *Window, SDL_Renderer *renderer, CelluleMot tabLetChange[TailleMaxMot], CelluleMot TabLetBut[TailleMaxMot],liste *lchemin ,CelluleMot tabLetChangeMachine[TailleMaxMot], SDL_Event event, int npermut, int TailleMot, int *Y_avancement, int mode , bool *flagTime , ScoreCel BestScore [5] , int minute , int second , int Name[TailleMaxMot] , int TailleName , char bufferDate[ MAX_SIZE_Date ] , SDL_Surface *TabTemps[10] )
{
  
selection(Window , renderer, event, flagTime);   // menu Timer selection

if((*flagTime)==true){
int x;
SDL_Surface *scroll  = creeSurface("../src/images/wallpaper.png", Window  , renderer ); 
  if (mode == 0)
    x = XJoueurDebut;
  else
    x = XDebut;
  if ((event.button.x > x) && (event.button.x < x + LETTER_WIDTH * (TailleMot - npermut + 1)) && (event.button.y > YDebut) && (event.button.y < YDebut + 50))
  {
    SDL_Rect Recatn;
    if (compare_Mot(tabLetChange, TabLetBut, TailleMot) != 0)
    {
      int indiceTabBoutons = ((int)((event.button.x - x)) / LETTER_WIDTH);
      // permutation apres clicker
      permuteJoueur(tabLetChange, npermut, indiceTabBoutons);
      // affichage
      if ((*Y_avancement) < WINDOW_HEIGHT - YDebut ){
      initRect(&Recatn, x, YDebut + (*Y_avancement), LETTER_WIDTH, LETTER_WIDTH);
     (*Y_avancement) += 50;
      }
      else{ // scroll bar : 
        (*Y_avancement) = 100;
        // then mot : 
         initRect(&Recatn, x, YDebut + (*Y_avancement), LETTER_WIDTH, LETTER_WIDTH);
         afficher(Window , renderer , scroll , Recatn ); 
         (*Y_avancement) += 50;
      }
      printf("y Avencement Mot test : %d\n", (*Y_avancement)); 
      //afficherTabWindow(TabLetBut, Window, renderer, Recatn, TailleMot); // error here 
      afficherTabWindow(tabLetChange, Window, renderer, Recatn, TailleMot); // error here 
      saveCodeMotCurntFile(indiceTabBoutons);
      // we stop timer if we find the correct word 
      if  (compare_Mot(tabLetChange, TabLetBut, TailleMot) == 0){
        // on a trouver la combinaison donc : save score meilleur + stop timer 
        BestScoreMiseAJours(BestScore ,  minute ,  second ,  Name ,  TailleName , bufferDate);
        (*flagTime)=false ; 
            // partie termineé donc vider les fichiers : 
          supprimFile("motCurnt.txt"); 
          supprimFile("motInit.txt"); 
          supprimFile("motBut.txt");
          supprimFile("motName.txt");
          SDL_Surface *bravo = creeSurface("../src/images/bravo.png", Window  , renderer ); 

          SDL_Rect rect ; // afficher u won :  
          initRect(&rect , WINDOW_WIDTH / 4 , WINDOW_HEIGHT/2 , 500 , WINDOW_HEIGHT/2 ); 
          afficher(Window , renderer , bravo, rect );
                          // afficher score 
         initRect(&rect , WINDOW_WIDTH/2 , WINDOW_HEIGHT*4/5 - 1*BUTTON_WIDTH , BUTTON_WIDTH , BUTTON_WIDTH );                  

          initRect(&rect , WINDOW_WIDTH/2 , WINDOW_HEIGHT*4/5 - 1*BUTTON_WIDTH , BUTTON_WIDTH , BUTTON_WIDTH ); 
          afficher(Window , renderer , TabTemps[minute/10] , rect) ; 
          rect.x += BUTTON_WIDTH ; 
          afficher(Window , renderer , TabTemps[minute%10] , rect) ;
          rect.x += BUTTON_WIDTH ; 
          afficher(Window , renderer , TabTemps[second/10] , rect) ;
          rect.x += BUTTON_WIDTH ; 
          afficher(Window , renderer , TabTemps[second%10] , rect) ;

          SDL_FreeSurface(bravo); 
      }
      else if (mode == 0 ) MachinePlaysWithUser(Window , renderer , tabLetChangeMachine , lchemin , npermut , Y_avancement , TailleMot); 
  
      SDL_RenderPresent(renderer);

    }

     else{ // : u found it !

     } 

  }
  SDL_FreeSurface(scroll); 
  }
  
}

void savingNewScore(int *minut , int *second , int *Name , int TailleName){
      time_t timestamp = time( NULL );
     struct tm * pTime = localtime( & timestamp );
     char buffer[MAX_SIZE_Date]; 
     int timeScore; 
       FILE* fileScore = fopen("Score.txt","r+");
    if (fileScore != NULL){
      bool remplace = false ; 

     while(fgetc(fileScore) != EOF && remplace == false ){

        fscanf(fileScore ,"%d ", timeScore ); // on parcours les anciens scores pour comparer

        if(timeScore < (*minut)*100 + (*second)){ // si on trouve un score inferieur on remplace 
        remplace = true ; 
        fseek(fileScore, -4 , SEEK_CUR); 
        // write the new score on fichier
        // score :  
        if((*minut)<10) fputc('0' ,fileScore ); 
        fprintf(fileScore,"%d", minut );
        if((*second)<10) fputc('0' ,fileScore ); 
        fprintf(fileScore,"%d ", second);

        // date : 
        strftime( buffer, MAX_SIZE_Date, "%d/%m/%Y ", pTime );
        fputs(buffer, fileScore);
        fputc(' ', fileScore);

        // Name :  
        for (int i = 0; i < TailleMaxMot ; i++)
        {
          if(i<TailleName)
           fprintf(fileScore,"%d ", Name[i]);
           else{  // remplir la taille vide de nom  avec -1
             fputs("-1 ", fileScore);
           }
        }


        // remplacer 
       }
       else{ // on continue la rechreche dans la ligne suivante 
           fseek(fileScore, 6 + 1 + 8*3 , SEEK_CUR);   
      }

     }
     
      fclose(fileScore); 
    }
}

void MachinePlays(SDL_Window *Window, SDL_Renderer *renderer, CelluleMot tabLetChange[TailleMaxMot], liste_combin teteCombin, int nbpermut, int y, int TailleMot, int debut , int mode )
{
  SDL_Rect Rectan;
  while (teteCombin->chemin != NULL)
  {
    permuteJoueur(tabLetChange, nbpermut, (teteCombin->chemin)->info);

    initRect(&Rectan, debut, YDebut + y, LETTER_WIDTH, LETTER_WIDTH);
    if (mode != 0) afficherTabWindow(tabLetChange, Window, renderer, Rectan, TailleMot);
    y += 50;
    if ((teteCombin->chemin)->svt2 == NULL)// c le mot but il faux l'afficher au debut {
   {
    if (mode == 1) /*machine mode */initRect(&Rectan, WINDOW_WIDTH/2 +2*LETTER_WIDTH, WINDOW_HEIGHT/4 - LETTER_WIDTH, LETTER_WIDTH, LETTER_WIDTH);
    else if(mode == 0) initRect(&Rectan, 550, 90, LETTER_WIDTH, LETTER_WIDTH);
    afficherTabWindow(tabLetChange, Window, renderer, Rectan, TailleMot);
    }
    teteCombin->chemin = (teteCombin->chemin)->svt2;
    
  }
}

void MachinePlaysWithUser(SDL_Window *Window, SDL_Renderer *renderer,CelluleMot tabMachineChange[TailleMaxMot], liste *lchemin, int nbpermut, int *y_avencement, int TailleMot )
{
  SDL_Rect Rectan;
  if((*lchemin)!=NULL){
    permuteJoueur(tabMachineChange, nbpermut, (*lchemin)->info);
    initRect(&Rectan, (WINDOW_WIDTH/4)-(TailleMot*LETTER_WIDTH/2), YDebut + (*y_avencement)-100, LETTER_WIDTH, LETTER_WIDTH);
    afficherTabWindow(tabMachineChange, Window, renderer, Rectan, TailleMot);
    //(*y_avencement) += 50; // pas besoin can incrementation dans user plays ( c'est le meme parametre )
    (*lchemin)=(*lchemin)->svt2; 
  }
}



void destruction(SDL_Window *Window, SDL_Renderer *renderer, SDL_Surface *TabLettres[26], CelluleMot TabMot[TailleMaxMot], int *Taille , int mode )
{
  DelTab(TabMot, Taille);
  AfficheurClavierWall(TabLettres, Window, renderer , mode );
}

int getMode(SDL_Event event)
{
  // if(mode == 0 ) player vs machine  //   if (mode == 1 )machine plays // if (mode == 1 )   userPlays
  if ((event.button.x > 275) && (event.button.x < 725) && (event.button.y < 545) && (event.button.y > 463))
    return 0;
  else
  {
    if ((event.button.x > 275) && (event.button.x < 725) && (event.button.y < 438) && (event.button.y > 357))
      return 1;
    else if ((event.button.x > 275) && (event.button.x < 725) && (event.button.y < 330) && (event.button.y > 250))
      return 2;
    else if ((event.button.x > 275) && (event.button.x < 725) && (event.button.y < 650) && (event.button.y > 570))
         return 3;
         else return 4 ; 
  }
}

/*--------------------------------------------------------------------------------------------------------------------------*/
// Machine uses randomly mot for user
/*--------------------------------------------------------------------------------------------------------------------------*/

void MachineRandomChoixMotInit(int *npbermut, int *TailleMot, SDL_Surface *TabClavier[26], CelluleMot TabChoixMachineinit[TailleMaxMot])
{
  (*TailleMot) = rand() % 6 + 3;
  //(*npbermut) = rand() % ((*TailleMot) - 2) + 2;
  if ((*TailleMot)==3 ) (*npbermut) = 2 ; 
  else (*npbermut) = rand() % ((*TailleMot)/2 ) + (*TailleMot)/2;
  
  int indice;
  for (int i = 0; i < (*TailleMot); i++)
  {
    indice = rand() % 26;
    saveCodeMotInitFile(TabClavier , indice ); 
    TabChoixMachineinit[i].img = TabClavier[indice];
    TabChoixMachineinit[i].rotationEtPos = i + 1;
  }
}

void RemplirTabOfCombinPossible(liste_combin *t, CelluleMot TabChoixMachineinit[TailleMaxMot], int npermut, int TailleMot, liste_combin TabChoixRand[MAX_TAB_MACHINE_CHOIX], int *tailleTabChoixRand)
{
  // remplir tableau eqv liste originale
  int T[TailleMaxMot];

  (*tailleTabChoixRand) = 0;
  int r, nbpossible;
  liste_combin tete, p;

  for (r = 0; r < TailleMaxMot; r++)
  {
    T[r] = r + 1;
  }

  (*t) = toute_combin(T, npermut, TailleMot);
  p = (*t)->svt1;

  if ((*t) == NULL)
    printf("loooser");
  while (p != NULL)
  {

    if (AfficheBool(p, TailleMot) == 0 && (*tailleTabChoixRand) < MAX_TAB_MACHINE_CHOIX)
    {

      TabChoixRand[(*tailleTabChoixRand)] = p;

      (*tailleTabChoixRand)++;
    }
    p = p->svt1;
  }
}

void MachineRandomChoixMotbut(SDL_Window *Window, SDL_Renderer *renderer, CelluleMot TabChoixMachineinit[TailleMaxMot], CelluleMot TabChoixMachineBut[TailleMaxMot], int *TailleMot, int *npbermut, SDL_Surface *TabClavier[26])
{
  MachineRandomChoixMotInit(npbermut, TailleMot, TabClavier, TabChoixMachineinit);
  liste_combin t = NULL;
  liste_combin TabChoixRand[MAX_TAB_MACHINE_CHOIX];
  int tailleTabChoixRand = 0;
  RemplirTabOfCombinPossible(&t, TabChoixMachineinit, *npbermut, *TailleMot, TabChoixRand, &tailleTabChoixRand);
  liste_combin p  = TabChoixRand[rand() % tailleTabChoixRand] ;  
  saveCodeMotButFile( p , *npbermut); 
  transferTabToMot(TabChoixMachineBut, TabChoixMachineinit, p  , *TailleMot);
  SDL_Rect Rect;
  initRect(&Rect, 10, 10, LETTER_WIDTH * (*TailleMot), LETTER_WIDTH);
  afficherTabWindow(TabChoixMachineinit, Window, renderer, Rect, *TailleMot);
  initRect(&Rect, 10, 100, LETTER_WIDTH * (*TailleMot), LETTER_WIDTH);
  afficherTabWindow(TabChoixMachineBut, Window, renderer, Rect, *TailleMot);
}

// lire le mot initial ( ancien ) depuis un fichier retourne la taille et le mode
void oldMotInit(CelluleMot Tablet[TailleMaxMot], SDL_Surface *TabClavier[26], int *TailleMot, int *mode )
{
  (*TailleMot) = (nbCharFile("motInit.txt") - 2) / 3;
  printf("TailleMot dans fonc oldMotInit : %d \n", (*TailleMot));
  int indice;
  FILE *fichierMotSave = fopen("motInit.txt", "r");
  if (fichierMotSave != NULL)
  {
    fscanf(fichierMotSave, "%d ", mode);
    for (int i = 0; i < (*TailleMot); i++)
    {
      fscanf(fichierMotSave, "%d", &indice);
      Tablet[i].img = TabClavier[indice];
      Tablet[i].rotationEtPos = i + 1;
    }
    fclose(fichierMotSave);
  }
}
// lire le Nom d'utilisateur ( ancien ) depuis un fichier retourne la taille du nom et Nom
void oldMotName(int Name[TailleMaxMot], int *TailleName )
{
  int indice = 0 ; 
  int i = 0 ; 
  (*TailleName) = 0 ; 
  FILE *fichierMotSave = fopen("motName.txt", "r");
  if (fichierMotSave != NULL)
  {

    while (i<TailleMaxMot )
    {
      fscanf(fichierMotSave, "%d ", &indice);
       Name [i]= indice;
      if(indice != -1 )(*TailleName) ++ ; 
      i++ ; 
    }
    fclose(fichierMotSave);
  }
}
// lire le chemin de transformation du mot init pour avoir mot but ( ancien ) depuis un fichier
void oldMotBut(CelluleMot TabMotInit[TailleMaxMot], CelluleMot TabBut[TailleMaxMot], int TailleMot, int *nbpermut)
{
  copy_tab_img(TabBut, TabMotInit, TailleMot);
  int n = ((nbCharFile("motBut.txt") - 2) / 2) + 1; // nombre de chemin a suivre
  FILE *fichierMotSave = fopen("motBut.txt", "r");
  int chemin;
  if (fichierMotSave != NULL)
  {
    fscanf(fichierMotSave, "%d ", nbpermut);
    printf("nbpermut : %d \n", *nbpermut);
    for (int i = 0; i < n - 1; i++)
    {
      fscanf(fichierMotSave, "%d ", &chemin);
      printf("chemin : %d \n", chemin);
      permuteJoueur(TabBut, *nbpermut, chemin);
    }

    fclose(fichierMotSave);
  }
}






void oriantationAfterSaving (SDL_Window *Window, SDL_Renderer *renderer, CelluleMot TabMotInit[TailleMaxMot], CelluleMot tabLetBut[TailleMaxMot], CelluleMot tabLetChangeJoueur[TailleMaxMot], CelluleMot tabLetChangemachine[TailleMaxMot], int *TailleMotInit, SDL_Surface *TabLettres[26], bool *clavActive, bool *Menu, bool *UserPlayBool, bool *choixCombin, int *mode, int *Y_avencement, int *npermut, liste_combin *listeC,liste *lchemin, liste_combin TabAdrComb[15], int *nbCpmbinMot , int *minut , int *second , bool *flageTime  ,int Name[TailleMaxMot] ,int *TailleName){
 
  if (nbCharFile("motInit.txt") <3  || nbCharFile("motBut.txt") < 3  )//nb char de motBut au moins 3 car 2premiers char represente nbpermute
    {
      GameBeginMenu(Window, renderer,TabMotInit,tabLetChangeJoueur , tabLetBut , TailleMotInit ,  Y_avencement , minut , second , flageTime , Name , TailleName);
      (*Menu) = true;
    }
    else{
      // decaration var needed
      int chemin , i , n , indiceTabBoutons , TailleMot , X ; 
      liste_combin p ; 
      FILE *MotInit = fopen("motInit.txt", "r");
      if (MotInit != NULL){
       FILE *MotBut = fopen("motBut.txt", "r");
         if (MotBut != NULL)
         {
           fscanf(MotInit, "%d ", mode);
             FILE *MotCurnt = fopen("motCurnt.txt", "r");
             if (MotCurnt != NULL)
             {
                   // recuperer ancien timer 
                  OldTimer (minut , second); 
                  // recuperer ancien  mot init et mot but et Name 
                  oldMotInit(TabMotInit, TabLettres, TailleMotInit, mode);
                  oldMotBut(TabMotInit, tabLetBut, *TailleMotInit, npermut);
                  oldMotName(Name , TailleName); 
                  // si on a deje trouvee le mot pas besoin de activer timer : 
                  if(compare_Mot(TabMotInit , tabLetBut , *TailleMotInit) == 0 ) (*flageTime)=false ; 
                  // nombre de chemin a suivre (nb char vdans file - espace blanc - mode)
                  n = (nbCharFile("motBut.txt") - 2 ) / 2 + 1 ; 
                  // recuperer ancien mode choisi
                  fscanf(MotBut, "%d ", npermut);
                  // construire Mot but a partir du fichier (we only have chemin a suivre depuis mot init dans fichier )
                   fscanf(MotBut, "%d ", &chemin);
                   liste_combin p = allouer_combin(); 
                   ajouterTete(&(p->chemin), chemin);
                    (*lchemin) = p->chemin; // l est derniere elem de la liste du chemin 
                     for ( i = 0; i < n ; i++)
                    {
                      fscanf(MotBut, "%d ", &chemin);
                      ajouterApresAdress(lchemin, chemin);
                      (*lchemin) = (*lchemin)->svt2;
                     }
                     listeC = &p;
                     (*lchemin) = (*listeC)->chemin ; 
                    copy_tab_img(tabLetChangeJoueur, TabMotInit, *TailleMotInit);
                    copy_tab_img(tabLetChangemachine, TabMotInit, *TailleMotInit);
                   // now we have Mot Init dans TabMotInit and mot but inside listeC

              if((*mode)==0 || (*mode) == 2 ){ // mode  0 == PlayerVsMachine  // mode 2 == Joueur alone 
                  TailleMot = *TailleMotInit ; 
                 // show background first  : 
                 if((*mode)==0){/* PlayerVsMachine*/
                   BackgroundPlayerVsMachine(TabMotInit, listeC, Window, renderer, *TailleMotInit, *npermut);
                   X = XJoueurDebut ;  //
                 } 
                 else {/*joueur */
                  BackgroundPlayer(TabMotInit, tabLetChangeJoueur , tabLetBut , TabLettres , Window , renderer ,  TailleMotInit , npermut, minut , second ); 
                  X = XDebut ; 
                 }
               // construire ancien mot Curnt 
               if (nbCharFile("motCurnt.txt")!= 0)
               { 
                n = nbCharFile("motCurnt.txt") / 2 + 1;// nb char dans "motCurnt.txt"
                SDL_Rect Recatn;
                for (i = 0; i < n-1 ; i++)
                {
                  fscanf(MotCurnt, "%d ", &indiceTabBoutons);
                  permuteJoueur(tabLetChangeJoueur, *npermut, indiceTabBoutons);
                  // affichage 
                  if ((*Y_avencement) < WINDOW_HEIGHT - YDebut ){
                       initRect(&Recatn, X, YDebut + (*Y_avencement), LETTER_WIDTH, LETTER_WIDTH);
                       (*Y_avencement) += 50;
                    }
                  else{ // scroll bar : 
                  SDL_Surface *scroll  = creeSurface("../src/images/wallpaper.png", Window  , renderer ); 
                    (*Y_avencement) = 100;
                   // then mot :
                     initRect(&Recatn, X, YDebut + (*Y_avencement), LETTER_WIDTH, LETTER_WIDTH);
                    afficher(Window , renderer , scroll , Recatn );
                    SDL_FreeSurface(scroll);  
                   (*Y_avencement) += 50;
                       }
                  //initRect(&Recatn, X , YDebut + (*Y_avencement), LETTER_WIDTH, LETTER_WIDTH);
                  //(*Y_avencement) += 50;
                  afficherTabWindow(tabLetChangeJoueur, Window, renderer, Recatn, *TailleMotInit);
                  if ((*mode) == 0){
                    MachinePlaysWithUser(Window , renderer , tabLetChangemachine , lchemin , *npermut , Y_avencement , TailleMot); 
                  }
                }
                }
                }
                else /*machine*/{
                  BackgroundMachine ( tabLetChangeJoueur , listeC ,  Window , renderer , *TailleMotInit , *npermut ); 

                }

              fclose(MotCurnt); 
             }
             fclose(MotBut); 
         }
         fclose(MotInit); 
      }

    }
}


 void BackgroundPlayer (CelluleMot TabLet[TailleMaxMot], CelluleMot tabLetChangeJoueur[TailleMaxMot] ,CelluleMot tabLetBut[TailleMaxMot]  , SDL_Surface *TabClavier[26],  SDL_Window *Window , SDL_Renderer *renderer , int *TailleM , int *npermut , int *minute , int *second )

  {
     if(nbCharFile("motBut.txt")==0)
    MachineRandomChoixMotbut(Window , renderer , TabLet , tabLetBut , TailleM , npermut , TabClavier ); // error here ? 
    else{
      int mode ;
      oldMotInit(TabLet,TabClavier, TailleM ,   &mode); 
      oldMotBut(TabLet, tabLetBut , *TailleM , npermut); 
    }
        copy_tab_img(tabLetChangeJoueur , TabLet , *TailleM );
    int TailleMot = (*TailleM) ;
       SDL_Rect Rectan ;
       SDL_Surface *Wallpaper = creeSurface("../src/images/wallpaper.png", Window  , renderer );
      initRect(&Rectan , 0 , 0 , WINDOW_WIDTH , WINDOW_HEIGHT);
      afficher(Window , renderer , Wallpaper , Rectan );

      // mini logo : 
       afficherLogoMini( Window , renderer , &Rectan); 

        // afficher machine 
       SDL_Surface *Joueurimg = creeSurface("../src/images/joueur.png", Window  , renderer );
      initRect(&Rectan , WINDOW_WIDTH/2- 350/2  , WINDOW_HEIGHT/8 , LETTER_WIDTH, LETTER_WIDTH);
      afficher(Window , renderer , Joueurimg , Rectan );

            // afficher mot a trouver : 
      SDL_Surface *motTrouv = creeSurface("../src/images/motToFind.png", Window  , renderer );
      initRect(&Rectan , WINDOW_WIDTH/6   , WINDOW_HEIGHT/5 , LETTER_WIDTH, LETTER_WIDTH);
      afficher(Window , renderer , motTrouv , Rectan );
      
      // draw a mine 
       if (SDL_SetRenderDrawColor(renderer , 125 , 25 , 33 , SDL_ALPHA_OPAQUE) != 0)
         SDL_ExitWithError("Color Draw Changing");

      if(SDL_RenderDrawLine(renderer , 0 ,  WINDOW_HEIGHT /5.25  ,WINDOW_WIDTH  ,  WINDOW_HEIGHT/ 5.25 ) != 0)
        SDL_ExitWithError("Line Draw");

      if(SDL_RenderDrawLine(renderer , 0 ,  WINDOW_HEIGHT /4 + 15  ,WINDOW_WIDTH  ,  WINDOW_HEIGHT/ 4 +15 ) != 0)
        SDL_ExitWithError("Line Draw");

    initRect(&Rectan , WINDOW_WIDTH/2 +30 , WINDOW_HEIGHT/5 , LETTER_WIDTH , LETTER_WIDTH);
    afficherTabWindow(tabLetBut , Window , renderer , Rectan , TailleMot); 

      SDL_Surface *resume = creeSurface("../src/images/resume.png", Window  , renderer );
      initRect(&Rectan , WINDOW_WIDTH/2 +80 , 10 , 50, 50);
      afficher(Window , renderer , resume , Rectan );

      SDL_Surface *pause = creeSurface("../src/images/pause.png", Window  , renderer );
      initRect(&Rectan , WINDOW_WIDTH/2- 120 , 10 , LETTER_WIDTH, LETTER_WIDTH);
      afficher(Window , renderer , pause , Rectan );
         
   SDL_Surface *TabButton[7];
     int nbButton = 0 ;
     chargerLesBoutonsOnMemoire(Window , renderer , &nbButton , TabButton );

          //pour utilisateur
     initRect(&Rectan , XDebut, YDebut + 50  , LETTER_WIDTH , LETTER_WIDTH );
     afficherTabWindow( TabLet, Window, renderer , Rectan , TailleMot  )  ;

      //affichage des bouttons
     initRect(&Rectan , XDebut, YDebut  , LETTER_WIDTH , LETTER_WIDTH );
     afficherTabButtonWindow( TabButton , Window, renderer , Rectan , TailleMot , *npermut  )  ;
        // Home Button :
        initRect(&Rectan , WINDOW_WIDTH - (LETTER_WIDTH + 20 )  , 20 , LETTER_WIDTH , LETTER_WIDTH) ;
        SDL_Surface *homebutton = creeSurface("../src/images/homeButton.png", Window  , renderer );
        afficher(Window , renderer , homebutton , Rectan);
        SDL_RenderPresent(renderer);

          SDL_FreeSurface(Wallpaper); 
         SDL_FreeSurface(homebutton); 
        SDL_FreeSurface(pause) ;
        SDL_FreeSurface(resume); 
        SDL_FreeSurface(Joueurimg); 
        SDL_FreeSurface(motTrouv); 
  }

