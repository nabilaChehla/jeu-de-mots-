
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "machine_Abstraite_Header.h"

void SDL_ExitWithError(const char *Strg){
        SDL_Log ("ERROR: %s > %s \n",Strg , SDL_GetError());
        printf("ERROR: %s > %s \n",Strg , SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
     }
     /*******************************************************************************/
     void SDL_ExitWithErrorImg(const char *Strg, SDL_Renderer *renderer , SDL_Window *Window )
       {
         SDL_DestroyRenderer(renderer);
         SDL_DestroyWindow(Window);
         //SDL_ExitWithError(Strg); 

         
       }
  /*******************************************************************************/
 void ecrireSurFenetre(const char *myString , SDL_Color *color , TTF_Font *font , SDL_Rect *rect, SDL_Renderer *renderer , SDL_Surface *surface , SDL_Texture *texture){
            surface = TTF_RenderText_Solid(font,myString, *color);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_RenderCopy(renderer, texture , NULL, rect);
            SDL_FreeSurface(surface); 
            SDL_DestroyTexture(texture); 
          }
/*******************************************************************************/
void initRect (SDL_Rect* rect , int x , int y , int w , int h ){
            rect->x = x;
            rect->y = y;
            rect->w = w;
            rect->h = h;
          } 


/*--------------------------------------------------------------------------------------------------------------------------*/
                                          //Afficher Image apartir d'une surface  
/*--------------------------------------------------------------------------------------------------------------------------*/
      void afficher(SDL_Window *Window,SDL_Renderer *renderer, SDL_Surface *image , SDL_Rect Rectangle){
        

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer , image  ); 
       // SDL_FreeSurface (image); //Attention 
        
           if (texture == NULL){ 
            SDL_ExitWithErrorImg("creation de la texture",renderer ,Window ); 
        }

       if(SDL_QueryTexture(texture, NULL , NULL , &Rectangle.w , &Rectangle.h) != 0  )
         {
            SDL_ExitWithErrorImg("impossible creer texture ",renderer ,Window );
         }


        if (SDL_RenderCopy(renderer , texture , NULL , &Rectangle)!=0){
            SDL_ExitWithErrorImg("impossible afficher texture ",renderer ,Window );
        }
        SDL_DestroyTexture(texture); 
        }

/*--------------------------------------------------------------------------------------------------------------------------*/
                                          //Afficher Le Menu 
/*--------------------------------------------------------------------------------------------------------------------------*/

     void GameBeginMenu(SDL_Window *Window , SDL_Renderer *renderer ,CelluleMot TabLet[TailleMaxMot] , CelluleMot TabChangeJoueur[TailleMaxMot], CelluleMot TabBut[TailleMaxMot]  , int *TailleMot , int *Y_avancement , int *minut , int *second , bool *flagTime , int Name[TailleMaxMot] , int *TailleName){
            //Background
      SDL_Surface *WallpaperMenu = creeSurface("../src/images/menu.jpg", Window  , renderer ); 
      SDL_Rect RectWallPaperMenu ;
      initRect(&RectWallPaperMenu , 0 , 0 , WINDOW_WIDTH , WINDOW_HEIGHT);
      afficher(Window , renderer , WallpaperMenu , RectWallPaperMenu );
      (*Y_avancement)=100 ; 
       SDL_RenderPresent(renderer); 
       SDL_FreeSurface(WallpaperMenu); 
          supprimFile("motCurnt.txt"); 
          supprimFile("motInit.txt"); 
          supprimFile("motBut.txt");
          supprimFile("motName.txt");
          int Temp = (*TailleMot) ;  
          DelTab(TabLet , TailleMot);
          (*TailleMot ) = Temp ; 
          DelTab(TabBut , TailleMot); 
          (*TailleMot ) = Temp ;
          DelTab(TabChangeJoueur , TailleMot); 
          
            // vider Name : 
          for (int i =0 ; i< TailleMaxMot ; i++){
            Name[i]= -1 ; 
          }
          (*TailleName)= 0 ; 
          resetTime(minut , second , flagTime); 
    }       
/*--------------------------------------------------------------------------------------------------------------------------*/
                                          // Afficher les meilleurs score  
/*--------------------------------------------------------------------------------------------------------------------------*/

     void AfficheBestScore(SDL_Window *Window , SDL_Renderer *renderer, ScoreCel BestScore[5] , SDL_Surface *TabAlphabet[26],SDL_Surface *TabTemps[10], int Name[TailleMaxMot] ){
            //Background
          if(TTF_Init()==-1) {
          SDL_ExitWithErrorImg("impossible INIT TTF ",renderer ,Window );
          exit(2);
          }

        TTF_Font * font = TTF_OpenFont("ARIAL.ttf", 40);
      	SDL_Color color = { 0 , 0 , 0 };
        SDL_Texture * message = NULL ; 
        SDL_Surface *surfacettf = NULL ; 
        char temp[10]; 
      SDL_Rect Rect ; int tailleName = 0 ; 

       // afficher Wallpaper : 
      SDL_Surface *Wallpaper = creeSurface("../src/images/wallpaper.png", Window  , renderer ); 
      initRect(&Rect , 0 , 0 , WINDOW_WIDTH , WINDOW_HEIGHT);
      afficher(Window , renderer , Wallpaper , Rect );
      // afficher home button : 
      SDL_Surface *homebutton = creeSurface("../src/images/homeButton.png", Window  , renderer ); 
      initRect(&Rect , WINDOW_WIDTH - (LETTER_WIDTH + 20 )  , 20 , LETTER_WIDTH , LETTER_WIDTH) ;
      afficher(Window , renderer , homebutton , Rect); 

      
      SDL_Surface *logo = creeSurface("../src/images/logo.jpg", Window  , renderer ); 
      initRect(&Rect , WINDOW_WIDTH/2 - 315  , 15  , 630 , 242) ;
      afficher(Window , renderer , logo , Rect); 
      
      recupBestScore( BestScore); // pas forcement 


        // rect de name + score :
        initRect(&Rect , WINDOW_WIDTH/7  , WINDOW_WIDTH/4 , LETTER_WIDTH , LETTER_WIDTH);
        SDL_Rect Message_rect;
        // rect de Date: 
        initRect (&Message_rect ,WINDOW_WIDTH*3/4.5 - 2*LETTER_WIDTH ,WINDOW_WIDTH/4 ,BUTTON_WIDTH*10 , BUTTON_WIDTH );
        for(int i = 0 ; i< 5 ; i++){
          // Afficher Name :  
          afficherNameWindow(BestScore[i].NameUser,TabAlphabet , Window , renderer , Rect , calculeTailleName(BestScore[i].NameUser) );
          // afficher Time :  ---------------------------------------------------------------
          Rect.x =  WINDOW_WIDTH/2 - 2*LETTER_WIDTH; 
          // afficher minute 
          afficher(Window , renderer , TabTemps[BestScore[i].timeScore/1000] , Rect ); 
          Rect.x += BUTTON_WIDTH ; 
          afficher(Window , renderer , TabTemps[(BestScore[i].timeScore/100) % 10 ] , Rect ); 
          Rect.x += BUTTON_WIDTH ; 
          // afficher seconde
          afficher(Window , renderer , TabTemps[(BestScore[i].timeScore/10)% 10] , Rect );
          Rect.x += BUTTON_WIDTH ;  
          afficher(Window , renderer , TabTemps[BestScore[i].timeScore % 10] , Rect ); 
          // afficher Date : ------------------------------------------------------------------
          
          for(int j= 0 ; j<10 ; j++){
            // for this loop i dont know why but the bug is just fixed this way so anyway just move on 
            temp[j]= BestScore[i].Date[j]; 
          }
          printf("%s",temp); 
          ecrireSurFenetre(temp,&color ,font ,&Message_rect , renderer ,surfacettf , message) ; 

         // write on  next line : 
          Rect.y += LETTER_WIDTH + 20 ; 
          Message_rect.y = Rect.y ; 
          Rect.x =  WINDOW_WIDTH/7 ; 
        }

    SDL_RenderPresent(renderer);  
    SDL_FreeSurface(Wallpaper);
    SDL_FreeSurface(surfacettf);
    SDL_DestroyTexture(message); 
    SDL_FreeSurface(homebutton); 
    SDL_FreeSurface(logo); 
    }       


    
/*--------------------------------------------------------------------------------------------------------------------------*/
                                          //Creation Surface a partir du path 
/*--------------------------------------------------------------------------------------------------------------------------*/




        SDL_Surface *creeSurface(const char *pathImg, SDL_Window *Window  ,  SDL_Renderer *renderer ){

        SDL_Surface *image = IMG_Load(pathImg);
        if (image == NULL){
            SDL_ExitWithErrorImg("chargement de l'image",renderer ,Window ); 
        }
        return image ; 
        }
/*--------------------------------------------------------------------------------------------------------------------------*/
                                            // Affichge mot a l'envers 
/*--------------------------------------------------------------------------------------------------------------------------*/
    
void inverserImg(SDL_Window *Window ,  SDL_Renderer *renderer, SDL_Surface *img , SDL_Rect *Rectan, double angle ){

         SDL_Texture *textureimg = SDL_CreateTextureFromSurface( renderer , img  ); 
        // SDL_FreeSurface (image); //Attention 
           if (textureimg == NULL){ 
            SDL_ExitWithErrorImg("creation de la texture",renderer ,Window ); 
        }
        
        SDL_RenderCopyEx(renderer, textureimg,  NULL , Rectan, angle  , NULL, SDL_FLIP_NONE);
        SDL_DestroyTexture(textureimg); 
}
  


/*--------------------------------------------------------------------------------------------------------------------------*/
                                            // Charger les photos dans TabLet ( le Mot ) 
/*--------------------------------------------------------------------------------------------------------------------------*/

void RemplirTabOfImg_LeMot(SDL_Window *Window , SDL_Renderer *renderer , int *TailleMot , CelluleMot tabLet[TailleMaxMot] , const char *imgPath ){

     tabLet[*TailleMot].img =  creeSurface(imgPath, Window , renderer);
     tabLet[*TailleMot].rotationEtPos = (*TailleMot) + 1 ; 
     (*TailleMot)++ ; 

}
     

void RemplirTabOfInt_Button (SDL_Window *Window , SDL_Renderer *renderer , int *nbButton , SDL_Surface *tabButton[7] , const char *imgPath ){

     tabButton[*nbButton] =creeSurface(imgPath, Window , renderer)    ;
     (*nbButton)++ ; 

}

void RemplirTabOfInt_Temps (SDL_Window *Window , SDL_Renderer *renderer , int *nbButton , SDL_Surface *tabButton[9] , const char *imgPath ){

     tabButton[*nbButton] =creeSurface(imgPath, Window , renderer)    ;
     (*nbButton)++ ; 

}

void RemplirTabOfInt_Clavier (SDL_Window *Window , SDL_Renderer *renderer , int indice , SDL_Surface *tabClavier[26] , const char *imgPath ){

     tabClavier[indice] =creeSurface(imgPath, Window , renderer)    ; 

}


void afficherTabWindow(CelluleMot T[TailleMaxMot] , SDL_Window *Window, SDL_Renderer *renderer  , SDL_Rect Rectangle, int Taille){
    
    int i = 0 ; 
  if (Taille == 0 ){
          printf("Le mot est vide \n");
    }
    else{
        while(Taille != 0 ){
        if(T[i].rotationEtPos >= 0 )
        afficher(Window ,renderer , T[i].img ,Rectangle); 
        else inverserImg(Window , renderer, T[i].img , &Rectangle , 180 ); 
        i++ ; 
        Taille -- ; 
        Rectangle.x += LETTER_WIDTH ; 
        }
    }
    }

void afficherNameWindow(int Name[TailleMaxMot] , SDL_Surface *TabAlphabet[26] , SDL_Window *Window, SDL_Renderer *renderer  , SDL_Rect Rectangle, int TailleName){
    
    int i = 0 ; 
    printf("\n");
  if (TailleName == 0 ){
          printf("Le mot est vide \n");
    }
    else{
        while(TailleName != 0 ){
        afficher(Window ,renderer , TabAlphabet[Name[i]] ,Rectangle); 
        i++ ; 
        TailleName -- ; 
        Rectangle.x += LETTER_WIDTH ; 
        }
    }
    }




 void BackgroundPlayerVsMachine(CelluleMot TabLet[TailleMaxMot], liste_combin *listc ,   SDL_Window *Window , SDL_Renderer *renderer , int TailleMot , int npermut ){

      SDL_Rect Rectan ;
      SDL_Surface *Wallpaper = creeSurface("../src/images/wallpaper.png", Window  , renderer );
      SDL_Rect RectWallPaper ;
      initRect(&Rectan , 0 , 0 , WINDOW_WIDTH , WINDOW_HEIGHT);
      afficher(Window , renderer , Wallpaper , Rectan );


      SDL_Surface *resume = creeSurface("../src/images/resume.png", Window  , renderer );
      initRect(&Rectan , WINDOW_WIDTH/2 +80 , 10 , 50, 50);
      afficher(Window , renderer , resume , Rectan );

      SDL_Surface *pause = creeSurface("../src/images/pause.png", Window  , renderer );
      initRect(&Rectan , WINDOW_WIDTH/2- 120 , 10 , LETTER_WIDTH, LETTER_WIDTH);
      afficher(Window , renderer , pause , Rectan );

     afficherLogoMini( Window , renderer , &Rectan); 

     // afficher machine 
       SDL_Surface *machineimg = creeSurface("../src/images/machine.png", Window  , renderer );
      initRect(&Rectan , WINDOW_WIDTH/4 - 350/2  , WINDOW_HEIGHT/6 , LETTER_WIDTH, LETTER_WIDTH);
      afficher(Window , renderer , machineimg , Rectan );

      // afficher mot a trouver : 
      SDL_Surface *motTrouv = creeSurface("../src/images/motToFind.png", Window  , renderer );
      initRect(&Rectan , WINDOW_WIDTH/6   , WINDOW_HEIGHT/10 , LETTER_WIDTH, LETTER_WIDTH);
      afficher(Window , renderer , motTrouv , Rectan );
      


    SDL_Surface *Joueurimg = creeSurface("../src/images/joueur.png", Window  , renderer );
    initRect(&Rectan , WINDOW_WIDTH*3/4 - 350/2  , WINDOW_HEIGHT/6 , LETTER_WIDTH, LETTER_WIDTH);
    afficher(Window , renderer , Joueurimg , Rectan );

    SDL_Surface *TabButton[7];


     int nbButton = 0 ;  
   //  int npermut = 2 ; 
       
       //les lignes 
       if (SDL_SetRenderDrawColor(renderer , 125 , 25 , 33 , SDL_ALPHA_OPAQUE) != 0)
         SDL_ExitWithError("Color Draw Changing");

      if(SDL_RenderDrawLine(renderer , WINDOW_WIDTH /2 ,  WINDOW_HEIGHT /4  ,WINDOW_WIDTH /2 ,  WINDOW_HEIGHT  ) != 0)
        SDL_ExitWithError("Line Draw");
        if(SDL_RenderDrawLine(renderer , WINDOW_WIDTH  ,  WINDOW_HEIGHT /4  , 0 ,  WINDOW_HEIGHT/4  ) != 0)
        SDL_ExitWithError("Line Draw");


     chargerLesBoutonsOnMemoire(Window , renderer , &nbButton , TabButton ); // ?
    // pour machine 
     initRect(&Rectan , XMachineDebut , YDebut  , LETTER_WIDTH , LETTER_WIDTH ); 
     afficherTabWindow( TabLet , Window, renderer , Rectan , TailleMot )  ;

     //pour utilisateur 
     initRect(&Rectan , XJoueurDebut, YDebut + 50  , LETTER_WIDTH , LETTER_WIDTH ); 
     afficherTabWindow( TabLet, Window, renderer , Rectan , TailleMot  )  ;


     // afficher Home Button :
     initRect(&Rectan , WINDOW_WIDTH - (LETTER_WIDTH + 20 )  , 20 , LETTER_WIDTH , LETTER_WIDTH) ;
     SDL_Surface *homebutton = creeSurface("../src/images/homeButton.png", Window  , renderer ); 
      afficher(Window , renderer , homebutton , Rectan); 

      //affichage des bouttons 
     initRect(&Rectan , XJoueurDebut, YDebut  , LETTER_WIDTH , LETTER_WIDTH ); 
     afficherTabButtonWindow( TabButton , Window, renderer , Rectan , TailleMot , npermut  )  ;
      //  les etapes de la resolution machine
      liste_combin save = (*listc ); 
      MachinePlays (Window , renderer ,TabLet, *listc  , npermut , 100 , TailleMot , XMachineDebut , 0 ) ; 
     (*listc ) = save ; 
     SDL_RenderPresent(renderer); 
     
     SDL_FreeSurface(Wallpaper); 
     SDL_FreeSurface(homebutton); 
     SDL_FreeSurface(pause) ;
     SDL_FreeSurface(resume); 
     SDL_FreeSurface(machineimg); 
     SDL_FreeSurface(Joueurimg); 
     SDL_FreeSurface(motTrouv); 

 }   


void afficherLogoMini( SDL_Window *Window , SDL_Renderer *renderer ,SDL_Rect *Rect){
  SDL_Surface *logoUp = creeSurface("../src/images/logoUp.png", Window  , renderer );
  initRect(Rect , 10 , 10 , 130 , 50);
  afficher(Window , renderer , logoUp , *Rect );
  SDL_FreeSurface(logoUp); 
}

void BackgroundMachine (CelluleMot TabLet[TailleMaxMot], liste_combin *listc ,   SDL_Window *Window , SDL_Renderer *renderer , int TailleMot , int npermut )
{

      SDL_Surface *Wallpaper = creeSurface("../src/images/wallpaper.png", Window  , renderer );
      SDL_Rect RectWallPaper ;

      //afficher wallpaper
      initRect(&RectWallPaper , 0 , 0 , WINDOW_WIDTH , WINDOW_HEIGHT);
      afficher(Window , renderer , Wallpaper , RectWallPaper );

            // afficher logo 
     afficherLogoMini( Window , renderer , &RectWallPaper); 


    SDL_Rect Rectan ;
       SDL_Surface *machineimg = creeSurface("../src/images/machine.png", Window  , renderer );
      initRect(&Rectan , WINDOW_WIDTH/2- 350/2  , WINDOW_HEIGHT/8-15 , LETTER_WIDTH, LETTER_WIDTH);
      afficher(Window , renderer , machineimg , Rectan );

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

      // Home Button :
        initRect(&Rectan , WINDOW_WIDTH - (LETTER_WIDTH + 20 )  , 20 , LETTER_WIDTH , LETTER_WIDTH) ;
        SDL_Surface *homebutton = creeSurface("../src/images/homeButton.png", Window  , renderer ); 
        afficher(Window , renderer , homebutton , Rectan); 


         // afficher mot init 
        // initRect(&Rectan ,(WINDOW_WIDTH/2)-(TailleMot/2)   , WINDOW_HEIGHT/3-20, LETTER_WIDTH, LETTER_WIDTH);
          initRect(&Rectan , XDebut, YDebut - 0.4*LETTER_WIDTH+20  , LETTER_WIDTH , LETTER_WIDTH );
         afficherTabWindow(TabLet , Window , renderer , Rectan , TailleMot); 
      //affichage des bouttons     
     MachinePlays(Window , renderer ,TabLet, *listc  , npermut , 50 , TailleMot , ((WINDOW_WIDTH-LETTER_WIDTH*TailleMot)*0.5),1) ;

     SDL_RenderPresent(renderer);
     SDL_FreeSurface(Wallpaper); 
     SDL_FreeSurface(homebutton); 
    SDL_FreeSurface(machineimg); 
    SDL_FreeSurface(motTrouv);
     
}



void PlayingBackground(CelluleMot tabLetBut[TailleMaxMot] ,CelluleMot TabMotInit[TailleMaxMot] , liste_combin *listc,liste *lchemin , liste_combin TabAdrComb[15] ,SDL_Event event  ,  SDL_Window *Window , SDL_Renderer *renderer , int TailleMot , int mode , int npermut , int nCombinMot ,CelluleMot tabLetChangeJoueur[TailleMaxMot] ,CelluleMot tabLetChangeMachine[TailleMaxMot] ,bool *choixCombin , bool *UserPlayBool  ){

//void UserChoixMotBut(CelluleMot tabLetBut[8],CelluleMot TabMotInit[8], liste_combin *listecomb  ,liste_combin TabAdrComb[15] , SDL_Window *Window , SDL_Renderer *renderer , SDL_Event event , int TailleMot  , int nCombinMot ,CelluleMot tabLetChangeJoueur[8] ,CelluleMot tabLetChangeMachine[8] ){

if(mode == 0 ){// player vs machine 
  UserChoixMotBut(tabLetBut , TabMotInit, listc  , TabAdrComb , Window , renderer , event , TailleMot , nCombinMot , tabLetChangeJoueur, tabLetChangeMachine ) ; 
  if ((*listc)!= NULL){
    (*lchemin) =  (*listc)->chemin ;
    saveCodeMotButFile( (*listc) , npermut);
    BackgroundPlayerVsMachine(TabMotInit, listc ,  Window , renderer , TailleMot , npermut ) ; 
    (*choixCombin) = false ; 
    (*UserPlayBool)= true ; 
   // saveMotFile(tabLetBut, TailleMot); 
  }
}
else{
  if (mode == 1 )//machine plays
  {
   UserChoixMotBut(tabLetBut , TabMotInit, listc  , TabAdrComb , Window , renderer , event , TailleMot , nCombinMot , tabLetChangeJoueur, tabLetChangeMachine ) ; 
  if ((*listc)!= NULL){
        saveCodeMotButFile( (*listc) , npermut );
         BackgroundMachine (TabMotInit, listc ,  Window , renderer , TailleMot , npermut ); 
         (*choixCombin) = false ; 
         (*UserPlayBool)= true ; 
  }
  }
  else{ if(mode == 2 ){
        // user alone 
         }
  }

}

  
}

void interfaceBegin(SDL_Window *Window , SDL_Renderer *renderer , int *Y_avancement , bool *continueask , bool *Menu ,CelluleMot TabLet[TailleMaxMot],CelluleMot TabLetChangeJoueur[TailleMaxMot], CelluleMot TabBut[TailleMaxMot] , int TailleMot,int *minut ,int *second ,bool *flag ,int  Name[TailleMaxMot] ,int *TailleName){
if(nbCharFile("motInit.txt")>2 &&  nbCharFile("motBut.txt")> 2 ){
 SDL_Surface *Wallpaper = creeSurface("../src/images/continueAsk.jpg", Window  , renderer );
      SDL_Rect Rect ;
      initRect(&Rect , 0 , 0 , WINDOW_WIDTH , WINDOW_HEIGHT);
      afficher(Window , renderer , Wallpaper , Rect );

      //afficher logo 
      SDL_Surface *logo = creeSurface("../src/images/logo.jpg", Window  , renderer ); 
      initRect(&Rect , WINDOW_WIDTH/2 - 315  , 15  , 630 , 242) ;
      afficher(Window , renderer , logo , Rect); 

      // afficher oui
      initRect(&Rect , WINDOW_WIDTH/4 - 50 , WINDOW_HEIGHT *3/4 , 100 , 100);
      SDL_Surface *Oui = creeSurface("../src/images/oui.png", Window  , renderer );
      afficher(Window , renderer , Oui , Rect );

      //affiher non 
      initRect(&Rect , WINDOW_WIDTH*3/4 - 50 , WINDOW_HEIGHT *3/4 , 100 , 100);
      SDL_Surface *Non = creeSurface("../src/images/Non.png", Window  , renderer );
      afficher(Window , renderer , Non , Rect );

      SDL_RenderPresent(renderer); 

      SDL_FreeSurface(Wallpaper); 
      SDL_FreeSurface(Oui); 
      SDL_FreeSurface(Non); 
      SDL_FreeSurface(logo); 
}
else {
  GameBeginMenu(Window , renderer , TabLet, TabLetChangeJoueur , TabBut , &TailleMot, Y_avancement ,minut , second , flag , Name , TailleName ); 
  (*continueask)= false ; 
  (*Menu)= true ; 
}
}

void askContinue(SDL_Window *Window , SDL_Renderer *renderer , SDL_Event event,CelluleMot TabMotInit[TailleMaxMot] ,CelluleMot tabLetBut[TailleMaxMot],CelluleMot tabLetChangeJoueur[TailleMaxMot], CelluleMot tabLetChangemachine[TailleMaxMot] ,int *TailleMot ,SDL_Surface *TabClavier[26], SDL_Surface *TabButton[7], bool *clavActive  , bool *Menu  , bool *UserPlayBool , bool *choixCombin , bool *continueask , bool *npermutChoix , int *mode , int *Y_avancement , int *npermut , liste_combin *listc, liste *lchemin ,liste_combin TabAdrComb[15], int *nbCpmbinMot,int *minute, int *second ,bool *timeFlag , int Name[TailleMaxMot] ,int *TailleName){
          //clicker oui
      if((event.button.x > WINDOW_WIDTH/4 - 50) && (event.button.x < WINDOW_WIDTH/4 + 50) && (event.button.y >WINDOW_HEIGHT *3/4) && (event.button.y < WINDOW_HEIGHT *3/4 +100 )){
          oriantationAfterSaving (Window , renderer,TabMotInit , tabLetBut, tabLetChangeJoueur, tabLetChangemachine ,TailleMot ,TabClavier,  clavActive  , Menu  , UserPlayBool , choixCombin , mode , Y_avancement , npermut , listc, lchemin ,  TabAdrComb, nbCpmbinMot , minute , second  , timeFlag , Name , TailleName); 
          (*continueask)=false ; 
      }
         // clicker Non
      else{
         if ((event.button.x > WINDOW_WIDTH*3/4 - 50) && (event.button.x < WINDOW_WIDTH*3/4 + 50) && (event.button.y >WINDOW_HEIGHT *3/4) && (event.button.y < WINDOW_HEIGHT *3/4 +100)){
     //  if((event.button.x > 200 ) && (event.button.x < 300) && (event.button.y >0) && (event.button.y < 100)){
          printf("im in non\n"); 

          GameBeginMenu(Window , renderer,TabMotInit, tabLetChangeJoueur ,tabLetBut,TailleMot,Y_avancement, minute , second , timeFlag ,  Name , TailleName); 
          (*continueask)= false ; 
          (*Menu)= true ; 
          printf("here\n"); 

      }
      } 
      
      
}