#ifndef MACHINE_ABSTRAITE_HEADER_H
# define MACHINE_ABSTRAITE_HEADER_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_WIDTH  1000 
#define WINDOW_HEIGHT 750 

#define TailleMaxMot 8 
#define MaxButton 7 

#define BUTTON_WIDTH 30 
#define LETTER_WIDTH 40 

#define MAX_TAB_MACHINE_CHOIX 15


#define XMachineDebut (WINDOW_WIDTH /4  - 0.5* (TailleMot* 40))
#define XJoueurDebut (WINDOW_WIDTH*3 /4  - 0.5* (TailleMot* 40))
#define YDebut (WINDOW_WIDTH / 5)
#define XDebut ((WINDOW_WIDTH-LETTER_WIDTH*TailleMot)*0.5)//xdebut=xsolodebut , so we can afficher in the middle

#define MAX_SIZE_Date 10

//#define MAXTAB




//------------------------------------------------------------------------------------
            // Declaration Tableau d'image 
//------------------------------------------------------------------------------------

//typedef  CelluleMot TLettre [10] ;  



typedef struct CelluleMot {
SDL_Surface *img ; 
int rotationEtPos ;

}CelluleMot; 


//typedef CelluleMot TLettre [MAXTAB] ; 


//------------------------------------------------------------------------------------
            // Declaration liste De Combinaisons LLCS 
//------------------------------------------------------------------------------------
typedef struct Cellule *liste ; 
typedef struct Cellule
{
    int info;
    liste svt2;
}Cellule;

typedef struct Cellule_Combine  *liste_combin; 

typedef struct Cellule_Combine 
{
    int tab[TailleMaxMot];
    liste_combin svt1;
    liste chemin;
}Cellule_Combine ;
//------------------------------------------------------------------------------------

typedef struct ScoreCel 
{
    int timeScore; 
    int NameUser[TailleMaxMot];
    char Date[10]; 

}ScoreCel ;

//put your function headers here


/*---------------------------------------------------------------------------------*/
                 //  action : Pour gestion de la SDL 
/*---------------------------------------------------------------------------------*/

void SDL_ExitWithError(const char *Strg); 
void SDL_ExitWithErrorImg(const char *Strg, SDL_Renderer *renderer , SDL_Window *Window ); 
void ecrireSurFenetre(const char *myString , SDL_Color *color , TTF_Font *font , SDL_Rect *rect, SDL_Renderer *renderer , SDL_Surface *surface , SDL_Texture *texture);
void initRect (SDL_Rect* rect , int x , int y , int w , int h ); 
void afficher(SDL_Window *Window,SDL_Renderer *renderer, SDL_Surface *image , SDL_Rect Rectangle); 

void afficherNameWindow(int Name[TailleMaxMot] , SDL_Surface *TabAlphabet[26] , SDL_Window *Window, SDL_Renderer *renderer  , SDL_Rect Rectangle, int TailleName); 

SDL_Surface *creeSurface(const char *pathImg, SDL_Window *Window  ,  SDL_Renderer *renderer );
void inverserImg(SDL_Window *Window ,  SDL_Renderer *renderer, SDL_Surface *img , SDL_Rect *Rectan, double angle ); 
void RemplirTabOfImg_LeMot(SDL_Window *Window , SDL_Renderer *renderer , int *TailleMot , CelluleMot tabLet[TailleMaxMot] , const char *imgPath );
void RemplirTabOfInt_Button (SDL_Window *Window , SDL_Renderer *renderer , int *nbButton , SDL_Surface *tabButton[6] , const char *imgPath ); 
void RemplirTabOfInt_Clavier (SDL_Window *Window , SDL_Renderer *renderer , int indice , SDL_Surface *tabClavier[26] , const char *imgPath ); 
void afficherTabWindow(CelluleMot T[TailleMaxMot] , SDL_Window *Window, SDL_Renderer *renderer  , SDL_Rect Rectangle, int Taille); 
 void BackgroundPlayer (CelluleMot TabLet[TailleMaxMot], CelluleMot tabLetChangeJoueur[TailleMaxMot] ,CelluleMot tabLetBut[TailleMaxMot]  , SDL_Surface *TabClavier[26],  SDL_Window *Window , SDL_Renderer *renderer , int *TailleM , int *npermut , int *minute , int *second ); 
void BackgroundPlayerVsMachine(CelluleMot TabLet[TailleMaxMot], liste_combin *listc ,   SDL_Window *Window , SDL_Renderer *renderer , int TailleMot , int npermut ); 
void BackgroundMachine (CelluleMot TabLet[TailleMaxMot], liste_combin *listc ,   SDL_Window *Window , SDL_Renderer *renderer , int TailleMot , int npermut ); 
void PlayingBackground(CelluleMot tabLetBut[TailleMaxMot] ,CelluleMot TabMotInit[TailleMaxMot] , liste_combin *listc,liste *lchemin , liste_combin TabAdrComb[15] ,SDL_Event event  ,  SDL_Window *Window , SDL_Renderer *renderer , int TailleMot , int mode , int npermut , int nCombinMot ,CelluleMot tabLetChangeJoueur[TailleMaxMot] ,CelluleMot tabLetChangeMachine[TailleMaxMot] ,bool *choixCombin , bool *UserPlayBool  ); 
int getMode(  SDL_Event event ); 
 void GameBeginMenu(SDL_Window *Window , SDL_Renderer *renderer ,CelluleMot TabLet[TailleMaxMot] , CelluleMot TabChangeJoueur[TailleMaxMot], CelluleMot TabBut[TailleMaxMot]  , int *TailleMot , int *Y_avancement , int *minut , int *second , bool *flagTime , int Name[TailleMaxMot] , int *TailleName); 


void AfficheBestScore(SDL_Window *Window , SDL_Renderer *renderer, ScoreCel BestScore[5] , SDL_Surface *TabAlphabet[26],SDL_Surface *TabTemps[10]  , int Name[TailleMaxMot] ); 
void afficherLogoMini( SDL_Window *Window , SDL_Renderer *renderer ,SDL_Rect *Rect); 

/*---------------------------------------------------------------------------------*/
              //  action : actions Elementaires pour la liste et les tableaux
/*---------------------------------------------------------------------------------*/
liste_combin allouer_combin( ); 
liste allouer_liste( ); 
void permute(int T[TailleMaxMot], int n, int indice); 
void permuteJoueur(CelluleMot T[TailleMaxMot], int n, int indice); 
void copy_tab(int T1[TailleMaxMot], int T2[TailleMaxMot], int taille); 
void copy_tab_img(CelluleMot T1[TailleMaxMot], CelluleMot T2[TailleMaxMot], int taille); 
int compare_tab(int T1[TailleMaxMot], int T2[TailleMaxMot], int taille); 

int compare_Mot (CelluleMot tabLetChange[TailleMaxMot],CelluleMot TabLet[TailleMaxMot] ,int TailleMot); 
liste_combin toute_combin(int T[TailleMaxMot],int npermut ,int Taille); 
int AfficheBool ( liste_combin p , int N  ); 
void affiche_chemin(liste_combin p ); 
void affiche_tab(int T[TailleMaxMot], int taille) ; 
void affiche_tabMot(CelluleMot T[TailleMaxMot] , int taille) ; 
void DelTab(CelluleMot T[TailleMaxMot], int *Taille); 
int calculeTailleName(int Name [TailleMaxMot]); 

/*---------------------------------------------------------------------------------*/
                 //  action : Pour gestion du Clavier Et boutons 
/*---------------------------------------------------------------------------------*/

void chargerClavierOnMemoire(SDL_Window *Window , SDL_Renderer *renderer  , SDL_Surface *TabLettres[26]); 
void afficherClavierWindow(SDL_Surface *TabLettres[26] , SDL_Window *Window, SDL_Renderer *renderer  , SDL_Rect Rectangle); 
void chargerLesBoutonsOnMemoire (SDL_Window *Window , SDL_Renderer *renderer , int* nbButton , SDL_Surface *TabButton[7]); 
void afficherTabButtonWindow (SDL_Surface *T[7] , SDL_Window *Window, SDL_Renderer *renderer  , SDL_Rect Rectangle, int Taille , int npermut); 
void UserChoixLetClavier (SDL_Surface *TabAlohabet[26]  , SDL_Window *Window , SDL_Renderer *renderer ,SDL_Event event , SDL_Rect *RectanAffMotClav ,CelluleMot TabLet[TailleMaxMot],CelluleMot tabLetChangeJoueur[TailleMaxMot], CelluleMot tabLetBut[TailleMaxMot], int Name[TailleMaxMot] ,  int *TailleMot , int *TailleName   , SDL_Surface *eraser ,  SDL_Surface *TabButton[7] , bool *clavActive , bool* npermutChoix , bool *NameEnter , int mode , int *npermut , int *minut , int *second); 
void AfficheurClavierWall(SDL_Surface *TabLettres[26] , SDL_Window *Window, SDL_Renderer *renderer , int mode ); 
void destruction(SDL_Window *Window, SDL_Renderer *renderer, SDL_Surface *TabLettres[26], CelluleMot TabMot[TailleMaxMot], int *Taille , int mode ); 
void afficherBoutonsPermite(SDL_Window *Window , SDL_Renderer *renderer , SDL_Surface *TabButton[MaxButton] , int TailleMot); 
void KeyBordChoixLetMotInit(SDL_Window *Window ,SDL_Renderer *renderer ,  CelluleMot TabLet[TailleMaxMot],CelluleMot tabLetchange[TailleMaxMot] , CelluleMot tabLetBut[TailleMaxMot], int Name[TailleMaxMot] , SDL_Surface* TabButton[7] ,  SDL_Surface *TabClavier[26] ,int *TailleMot ,int *TailleName , SDL_Event event, SDL_Rect *RectanAffMotClav , SDL_Surface *eraser , bool *clavActive , bool *npermutChoix , bool *NameEnter , int mode , int *npermut , int *minute , int *second  ); 
void UserPlaysWithKeybored(SDL_Window *Window, SDL_Renderer *renderer, CelluleMot tabLetChange[TailleMaxMot], CelluleMot TabBut[TailleMaxMot],CelluleMot tabLetChangeMachine[TailleMaxMot], SDL_Event event,liste *lchemin, int npermut, int TailleMot, int *Y_avancement, int mode, int minute , int second  , bool *flagTime , SDL_Surface *TabTemps[10], ScoreCel BestScore [5], int Name[TailleMaxMot] , int TailleName, char bufferDate[ MAX_SIZE_Date ]); 
void KeyBordPlaying(SDL_Window *Window ,SDL_Renderer *renderer ,  CelluleMot TabLet[TailleMaxMot] ,CelluleMot tabLetChangeJoueur[TailleMaxMot],CelluleMot tabLetChangeMachine[TailleMaxMot],int Name[TailleMaxMot],CelluleMot tabLetBut[TailleMaxMot],liste *lchemin, SDL_Surface* TabButton[7] ,  SDL_Surface *TabClavier[26] ,int *TailleMot , int *TailleName  , SDL_Event event, int mode ,  SDL_Rect *Recatn , SDL_Surface *eraser, int *npermut, int *Y_avancement, liste_combin *listeCombin   , int *nbCpmbinMot ,liste_combin TabAdrComb[15],bool *choixCombin  , bool *clavActive , bool *npermutChoix , bool *timeFalgRunning , bool *NameEnter ,int *minute ,int *seconde, SDL_Surface *TabTemps[10], ScoreCel BestScore [5] , char bufferDate[ MAX_SIZE_Date ]  ); 
/*---------------------------------------------------------------------------------*/
                 //  action : Pour la Resolution logique  
/*---------------------------------------------------------------------------------*/
void transferTabToMot (CelluleMot tabLetChange[TailleMaxMot],CelluleMot tabLet[TailleMaxMot], liste_combin p, int TailleMot ); 
void /*affichage avec creation*/AfficheCombinPossibles ( SDL_Window *Window , SDL_Renderer *renderer, liste_combin * t ,   CelluleMot tabLet[TailleMaxMot] , int npermut  , int TailleMot , int *nbMotCompbin , liste_combin TabAdrComb[15]  ); 


/*---------------------------------------------------------------------------------*/
                 //  action : we re playing !  
/*---------------------------------------------------------------------------------*/
void UserPlays(SDL_Window *Window, SDL_Renderer *renderer, CelluleMot tabLetChange[TailleMaxMot], CelluleMot TabLetBut[TailleMaxMot],liste *lchemin ,CelluleMot tabLetChangeMachine[TailleMaxMot], SDL_Event event, int npermut, int TailleMot, int *Y_avancement, int mode , bool *flagTime , ScoreCel BestScore [5] , int minute , int second , int Name[TailleMaxMot] , int TailleName , char bufferDate[ MAX_SIZE_Date ] , SDL_Surface *TabTemps[10] ); 
void MachinePlays(SDL_Window *Window, SDL_Renderer *renderer, CelluleMot tabLetChange[TailleMaxMot], liste_combin teteCombin, int nbpermut, int y, int TailleMot, int debut , int mode ); 
void MachinePlaysWithUser(SDL_Window *Window, SDL_Renderer *renderer,CelluleMot tabMachineChange[TailleMaxMot], liste *lchemin, int nbpermut, int *y_avencement, int TailleMot ); 
void UserChoixMotBut(CelluleMot tabLetBut[TailleMaxMot],CelluleMot TabMotInit[TailleMaxMot], liste_combin *listecomb  ,liste_combin TabAdrComb[15] , SDL_Window *Window , SDL_Renderer *renderer , SDL_Event event , int TailleMot  , int nCombinMot ,CelluleMot tabLetChangeJoueur[TailleMaxMot] ,CelluleMot tabLetChangeMachine[TailleMaxMot] ); 
void MachineRandomChoixMotInit(int *npbermut , int *TailleMot , SDL_Surface *TabClavier[26] , CelluleMot TabChoixMachineinit[TailleMaxMot]); 
void RemplirTabOfCombinPossible (  liste_combin * t ,   CelluleMot TabChoixMachineinit[TailleMaxMot] , int npermut  , int TailleMot, liste_combin TabChoixRand[MAX_TAB_MACHINE_CHOIX]  , int *tailleTabChoixRand  );
void MachineRandomChoixMotbut(SDL_Window *Window ,  SDL_Renderer *renderer , CelluleMot TabChoixMachineinit[TailleMaxMot], CelluleMot TabChoixMachineBut[TailleMaxMot] ,  int *TailleMot , int *npbermut , SDL_Surface *TabClavier[26] );
void saveCodeMotInitFile( SDL_Surface *TabClavier[26] , int indice ); 
void saveCodeName ( int indice ); 
void oldMotName(int Name[TailleMaxMot], int *TailleName ); 
void saveCodeMotButFile( liste_combin t , int npermut  ); 
void saveCodeMotCurntFile( int indiceperm ); 
void supprimFile(const char *Strg); 
int nbCharFile (const char *Strg); 
void OldTimer (int *minut , int *second); 
bool FichierEstVide(const char *Strg); 
void oldMotInit(CelluleMot Tablet[TailleMaxMot], SDL_Surface *TabClavier[26], int *TailleMot, int *mode ); 
void oldMotBut(CelluleMot TabMotInit[TailleMaxMot] , CelluleMot TabBut[TailleMaxMot] ,  int TailleMot , int *nbpermut); 
void SupEtAjoutFile(const char *Strg , int n); 
void interfaceBegin(SDL_Window *Window , SDL_Renderer *renderer , int *Y_avancement , bool *continueask , bool *Menu ,CelluleMot TabLet[TailleMaxMot],CelluleMot TabLetChangeJoueur[TailleMaxMot], CelluleMot TabBut[TailleMaxMot] , int TailleMot,int *minut ,int *second ,bool *flag ,int  Name[TailleMaxMot] ,int *TailleName); 
void oriantationAfterSaving (SDL_Window *Window, SDL_Renderer *renderer, CelluleMot TabMotInit[TailleMaxMot], CelluleMot tabLetBut[TailleMaxMot], CelluleMot tabLetChangeJoueur[TailleMaxMot], CelluleMot tabLetChangemachine[TailleMaxMot], int *TailleMotInit, SDL_Surface *TabLettres[26], bool *clavActive, bool *Menu, bool *UserPlayBool, bool *choixCombin, int *mode, int *Y_avencement, int *npermut, liste_combin *listeC,liste *lchemin, liste_combin TabAdrComb[15], int *nbCpmbinMot , int *minut , int *second , bool *flageTime  ,int Name[TailleMaxMot] ,int *TailleName); 
void askContinue(SDL_Window *Window , SDL_Renderer *renderer , SDL_Event event,CelluleMot TabMotInit[TailleMaxMot] ,CelluleMot tabLetBut[TailleMaxMot],CelluleMot tabLetChangeJoueur[TailleMaxMot], CelluleMot tabLetChangemachine[TailleMaxMot] ,int *TailleMot ,SDL_Surface *TabClavier[26], SDL_Surface *TabButton[7], bool *clavActive  , bool *Menu  , bool *UserPlayBool , bool *choixCombin , bool *continueask , bool *npermutChoix , int *mode , int *Y_avancement , int *npermut , liste_combin *listc, liste *lchemin ,liste_combin TabAdrComb[15], int *nbCpmbinMot,int *minute, int *second ,bool *timeFlag , int Name[TailleMaxMot] ,int *TailleName); 
void affiche_time(SDL_Window *Window , SDL_Renderer *renderer, SDL_Surface *TabTemps[10] , int *minute , int *second ,SDL_Rect *RectangleTemp); 
int choixNbPermut(SDL_Event event , int TailleMot , SDL_Window *Window, SDL_Renderer *renderer, liste_combin *t, CelluleMot tabLet[TailleMaxMot],int *nbcombpossible,  liste_combin TabAdrComb[15]); 
void saveTimerTxt(int minute , int second , bool fichInitVide); 
void recupBestScore(ScoreCel BestScore [5]); 
void BestScoreMiseAJours(ScoreCel BestScore [5] , int minute , int second , int Name[TailleMaxMot] , int TailleName , char bufferDate[ MAX_SIZE_Date ] ); 


#endif