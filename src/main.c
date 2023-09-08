#include <SDL.h> 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <conio.h>  
#include <stdbool.h>
#include <time.h>
#include "timeFonc.c"
#include "fonctionJeuxSDL.c"
#include "fonctionLLC.c"

/*
gcc src/main.c -o bin/main -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
gcc -mwindows src/main.c -o bin/JeuxDeMot -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image   
*/ 
/********************************************************************************/          
int main(int agrc, char **argv){

/*--------------------------------------------------------------------------------------------------------------------------*/
                                          //creation window + Renderer
/*--------------------------------------------------------------------------------------------------------------------------*/
if( 0!=SDL_Init(SDL_INIT_EVERYTHING)){
SDL_ExitWithError("Init SDL");
}
/*--------------------------------------------------------------------------------------------------------------------------*/
                                          //creation window + Renderer
/*--------------------------------------------------------------------------------------------------------------------------*/
    SDL_Window *Window  = SDL_CreateWindow ("Jeux De Mots",  SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WINDOW_WIDTH , WINDOW_HEIGHT , 0); 
        if (Window == NULL)
        SDL_ExitWithError("Window Creation");


    SDL_Renderer *renderer =  SDL_CreateRenderer(Window , -1 , 0) ; 
        if (renderer == NULL)
        SDL_ExitWithError("Render Creation");
/*--------------------------------------------------------------------------------------------------------------------------*/
                                            // Charger les photos dans TabLet ( le Mot ) 
/*--------------------------------------------------------------------------------------------------------------------------*/


     CelluleMot tabLetChangeJoueur [TailleMaxMot]  ; 
     CelluleMot tabLetChangeMachine[TailleMaxMot]; 
     CelluleMot TabMotInit[TailleMaxMot];
     CelluleMot tabLetBut[TailleMaxMot]; 

     SDL_Surface *TabButton[7];
     SDL_Surface *TabTemps[10] ; 
     SDL_Surface *TabClavier[26]; 
    //  int Name[TailleMaxMot];  // [ 1 , 2 ,  3 , 4 ] == ABCD

     int nbButton = 0 ;  
     int npermut = 4 ; 
     chargerLesBoutonsOnMemoire(Window , renderer , &nbButton , TabButton ); 
     chargerTempsPhotoEnMemoire(Window , renderer , TabTemps );
/*--------------------------------------------------------------------------------------------------------------------------*/
                               // Afficher Le Clavier tabLetChangeJoueur
/*--------------------------------------------------------------------------------------------------------------------------*/
     chargerClavierOnMemoire(Window , renderer ,TabClavier);
/*--------------------------------------------------------------------------------------------------------------------------*/
                                            // Initialisation Vars 
/*--------------------------------------------------------------------------------------------------------------------------*/
  SDL_Rect RectanAffMotClav ; 
  initRect(&RectanAffMotClav , WINDOW_WIDTH/3 ,  WINDOW_HEIGHT*2/3 - 70 , LETTER_WIDTH ,  LETTER_WIDTH ); 
  int TailleMot = 0 ; 
  int TailleName = 0 ; 
  int Name[TailleMaxMot]= {-1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 }; // Name Vide 

  SDL_Surface *eraser = creeSurface("../src/images/eraserEcran.jpg", Window  , renderer ); 

  liste_combin listeCombin = NULL ;
  int y = 0 ; 
  liste_combin TabAdrComb[15]; 
  liste lchemin ; 
  int nbCpmbinMot ; 
  liste_combin listc = NULL ;
    SDL_Rect RectanTime ; 
 int  Y_avancement  = 100 ;  
  bool clavActive = false , Menu = false  , UserPlayBool = false , choixCombin = false , npermutChoix =false , affCombin= false  , continueask=true , timeFalgRunning=true , NameEnrer = false; 
   int mode = 4 ;  //nonsens on purpos
  int minute,second ; 
  bool fichInitVide = FichierEstVide("motInit.txt"); 
  interfaceBegin (Window , renderer , &Y_avancement , &continueask , &Menu , TabMotInit, tabLetChangeJoueur , tabLetBut , TailleMot , &minute , &second , &timeFalgRunning , Name , &TailleName);

                    minute = 0 ;  second = 0 ; 
                    ScoreCel BestScore [5]; 
                   recupBestScore( BestScore); 

 time_t timestamp = time( NULL );
 struct tm * pTime = localtime( & timestamp );
 char bufferDate[ MAX_SIZE_Date ];
 strftime( bufferDate, 20 , "%d/%m/%Y", pTime );
/*--------------------------------------------------------------------------------------------------------------------------*/
                                                 // EVENTS 
/*--------------------------------------------------------------------------------------------------------------------------*/
        SDL_bool programLaunched = SDL_TRUE ;                                                                                                                                        

        while (programLaunched)
        {   // timer for user or userVsMachine
            if((mode == 0 || mode ==2 ) && ( clavActive==false) && (npermutChoix == false) && (choixCombin ==false) && (timeFalgRunning==true) ){
            count_time(&minute , &second); 
            affiche_time(Window , renderer, TabTemps , &minute , &second , &RectanTime); 

           }
          SDL_Event event ; 
         while (SDL_PollEvent(&event))
         {
            switch (event.type){
                case SDL_MOUSEBUTTONUP : 
                {    // go to clavier from menu to play user vs machine
                  printf("x : %d , Y : %d\n", event.button.x , event.button.y); 
                   if(continueask == true )
                    askContinue(Window , renderer , event,TabMotInit ,tabLetBut,tabLetChangeJoueur, tabLetChangeMachine ,&TailleMot ,TabClavier, TabButton, &clavActive  , &Menu  , &UserPlayBool ,&choixCombin , &continueask , &npermutChoix , &mode , &Y_avancement , &npermut , &listc , &lchemin ,TabAdrComb, &nbCpmbinMot , &minute , &second , &timeFalgRunning,Name, &TailleName);
                  else{
                   if (Menu == true){

                            mode = getMode (event); 
                            SupEtAjoutFile("motInit.txt", mode);  
                            if(mode != 3){ // 
                              clavActive = true ; NameEnrer = true ; 
                              AfficheurClavierWall( TabClavier , Window, renderer , mode ); 
                              Menu = false ;
                              }
                               else if (mode == 3){
                                  AfficheBestScore(Window , renderer,  BestScore ,  TabClavier , TabTemps  , Name );
                                   Menu = false ; 
                               }

                               //programLaunched = SDL_FALSE ; 
                    }
                     
                   else{ //home button 
                            if ( (Menu == false) && (event.button.x > 940 ) && (event.button.x < WINDOW_WIDTH ) && ( event.button.y > 20)  && (event.button.y <  70)  )
                             {
                                  Menu = true ; mode = 4 ; fichInitVide = true ;
                                  GameBeginMenu(Window , renderer, TabMotInit, tabLetChangeJoueur , tabLetBut , &TailleMot , &Y_avancement , &minute , &second , &timeFalgRunning , Name , &TailleName ); 
                             }
                    
                         else{

                        if((clavActive==true)/* && (event.button.y < WINDOW_HEIGHT*2/3 + (LETTER_WIDTH )*3 + 20*2)*/ ){
                           UserChoixLetClavier ( TabClavier, Window , renderer ,event , &RectanAffMotClav ,TabMotInit , tabLetChangeJoueur , tabLetBut , Name , &TailleMot  , &TailleName , eraser ,  TabButton , &clavActive , &npermutChoix , &NameEnrer , mode , &npermut ,&minute , &second );
                           printf("im on clavier \n"); 

                        }
                        else{
                          if ((npermutChoix == true) )
                          {
                            npermut =  choixNbPermut( event ,TailleMot , Window , renderer ,&listeCombin, TabMotInit , &nbCpmbinMot ,TabAdrComb );
                            // choixNbPermut affiche les combinaisons possibles 
                            npermutChoix = false ; choixCombin = true ; 
                          }

                           else{
                            if(choixCombin == true){  // user choix combin possible from screen  then  go to machine vs player wall
                                   PlayingBackground(tabLetBut ,TabMotInit ,  &listc, &lchemin  ,  TabAdrComb ,event  , Window , renderer ,  TailleMot ,  mode ,  npermut ,  nbCpmbinMot , tabLetChangeJoueur, tabLetChangeMachine ,&choixCombin ,&UserPlayBool );   
                            }
                             else{ //joueur playing 
                                    if (( mode ==0 || mode == 2 ) ){
                                      UserPlays (Window , renderer , tabLetChangeJoueur, tabLetBut , &lchemin, tabLetChangeMachine ,   event  , npermut, TailleMot ,&Y_avancement ,  mode , &timeFalgRunning , BestScore ,  minute ,  second ,  Name ,  TailleName , bufferDate , TabTemps );
                                    }
                                      else printf("Nothing fits \n");
                                  }
                           }
                         
                        }}
                    }
                  }
                }


                  break ;

                case SDL_KEYDOWN :{
                               // Le joueur decide de jouer avec le clavier ! 
                    KeyBordPlaying(Window ,renderer ,  TabMotInit , tabLetChangeJoueur, tabLetChangeMachine  , Name , tabLetBut, &lchemin, TabButton , TabClavier ,&TailleMot , &TailleName ,  event, mode, &RectanAffMotClav , eraser, &npermut, &Y_avancement, &listeCombin   , &nbCpmbinMot , TabAdrComb ,&choixCombin  , &clavActive , &npermutChoix , &timeFalgRunning , &NameEnrer , &minute , &second , TabTemps, BestScore , bufferDate ); 

                }
                break; 

                case SDL_QUIT :{
                  saveTimerTxt( minute , second , fichInitVide); 
                  programLaunched = SDL_FALSE ; 


                  
                }
                     
                     break;
                
                 default: 
                 break ; 
            }

         }
        }
/*--------------------------------------------------------------------------------------------------------------------------*/
                                            // Destruction Liberation memoire 
/*--------------------------------------------------------------------------------------------------------------------------*/
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(Window);
    	
    TTF_Quit();
    SDL_Quit();
    
     return EXIT_SUCCESS;
}
