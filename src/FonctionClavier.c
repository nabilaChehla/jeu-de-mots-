

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


#include "machine_Abstraite_Header.h"




/*---------------------------------------------------------------------------------*/
                 //   Fonction Clavier 
/*---------------------------------------------------------------------------------*/

void chargerClavierOnMemoire(SDL_Window *Window , SDL_Renderer *renderer  , SDL_Surface *TabLettres[26]){


     RemplirTabOfInt_Clavier(Window ,renderer , 0 , TabLettres, "../src/images/A.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 1 , TabLettres, "../src/images/B.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 2 , TabLettres, "../src/images/C.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 3 , TabLettres, "../src/images/D.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 4 , TabLettres, "../src/images/E.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 5 , TabLettres, "../src/images/F.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 6 , TabLettres, "../src/images/G.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 7 , TabLettres, "../src/images/H.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 8 , TabLettres, "../src/images/I.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 9 , TabLettres, "../src/images/J.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 10 , TabLettres, "../src/images/K.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 11 , TabLettres, "../src/images/L.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 12 , TabLettres, "../src/images/M.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 13 , TabLettres, "../src/images/N.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 14 , TabLettres, "../src/images/O.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 15 , TabLettres, "../src/images/P.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 16 , TabLettres, "../src/images/Q.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 17 , TabLettres, "../src/images/R.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 18 , TabLettres, "../src/images/S.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 19 , TabLettres, "../src/images/T.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 20 , TabLettres, "../src/images/U.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 21 , TabLettres, "../src/images/V.png" );
     RemplirTabOfInt_Clavier(Window ,renderer , 22 , TabLettres, "../src/images/W.png" );
     RemplirTabOfInt_Clavier(Window ,renderer , 23 , TabLettres, "../src/images/X.png" );  
     RemplirTabOfInt_Clavier(Window ,renderer , 24 , TabLettres, "../src/images/Y.png" ); 
     RemplirTabOfInt_Clavier(Window ,renderer , 25 , TabLettres, "../src/images/Z.png" ); 
}


  void afficherClavierWindow(SDL_Surface *TabLettres[26] , SDL_Window *Window, SDL_Renderer *renderer  , SDL_Rect Rectangle){
    for (int i =0 ; i< 10 ; i++){
        afficher(Window ,renderer , TabLettres[i] ,Rectangle); 
        Rectangle.x += LETTER_WIDTH ; 
    }
       Rectangle.y += LETTER_WIDTH + 20 ; 
       Rectangle.x -= LETTER_WIDTH*10 ;

    for (int i =10 ; i< 20 ; i++){
        afficher(Window ,renderer , TabLettres[i] ,Rectangle); 
        Rectangle.x += LETTER_WIDTH ; 
    }  

    Rectangle.y += LETTER_WIDTH + 20 ;
    Rectangle.x -= LETTER_WIDTH*8 ;

    for (int i =20 ; i< 26 ; i++){
        afficher(Window ,renderer , TabLettres[i] ,Rectangle); 
        Rectangle.x += LETTER_WIDTH ; 
    }  
    SDL_RenderPresent(renderer); 

  }


void AfficheurClavierWall(SDL_Surface *TabLettres[26] , SDL_Window *Window, SDL_Renderer *renderer , int mode ){
      //Background
      SDL_Surface *Wallpaper = creeSurface("../src/images/wallpaper.png", Window  , renderer );
      SDL_Rect Rect ;

      initRect(&Rect , 0 , 0 , WINDOW_WIDTH , WINDOW_HEIGHT);
      afficher(Window , renderer , Wallpaper , Rect );
       // mini logo : 
       afficherLogoMini( Window , renderer , &Rect); 
     //entrer button
     SDL_Surface *OkButton = creeSurface("../src/images/OkButton.png", Window  , renderer );
     initRect(&Rect , WINDOW_WIDTH/2 + 3.5*LETTER_WIDTH , WINDOW_HEIGHT*2/3+2*LETTER_WIDTH + 20*2 , LETTER_WIDTH*2 , LETTER_WIDTH); 
     afficher(Window , renderer , OkButton ,Rect );
     //delite button 
     SDL_Surface *DelButton = creeSurface("../src/images/Delite.png", Window  , renderer );
     initRect(&Rect , WINDOW_WIDTH/2 - 3.5*LETTER_WIDTH -50 , WINDOW_HEIGHT*2/3+2*LETTER_WIDTH + 20*2 , LETTER_WIDTH*2 , LETTER_WIDTH); 
     afficher(Window , renderer , DelButton ,Rect );
 
      //afficheur
      SDL_Surface *afficheur  = creeSurface("../src/images/ecranClav.png", Window  , renderer ); 
      initRect(&Rect , WINDOW_WIDTH/2 - 4*LETTER_WIDTH , WINDOW_HEIGHT*2/3 - 70 , LETTER_WIDTH*8 , LETTER_WIDTH  ); 
      afficher(Window , renderer , afficheur , Rect );

      //Entrez name: si mode player ou palyer vs machine 
      if(mode == 0 || mode == 2 ){
      SDL_Surface *EnterName  = creeSurface("../src/images/EntrezNom.png", Window  , renderer ); 
      initRect(&Rect , WINDOW_WIDTH/2 - 250/2 , WINDOW_HEIGHT*2/3 - 120 , 40 , 250 ); 
      afficher(Window , renderer , EnterName , Rect );
      SDL_FreeSurface(EnterName); 
      } 
      else{
      SDL_Surface *EnterMotInit  = creeSurface("../src/images/entrezMotInit.png", Window  , renderer ); 
      initRect(&Rect , WINDOW_WIDTH/2 - 250/2 , WINDOW_HEIGHT*2/3 - 120 , 40 , 250 ); 
      afficher(Window , renderer , EnterMotInit , Rect );
      SDL_FreeSurface(EnterMotInit); 
      }

      //home button 
      initRect(&Rect , WINDOW_WIDTH - (LETTER_WIDTH + 20 )  , 20 , LETTER_WIDTH , LETTER_WIDTH) ; 
      SDL_Surface *homebutton = creeSurface("../src/images/homeButton.png", Window  , renderer ); 
      afficher(Window , renderer , homebutton , Rect); 


      initRect(&Rect , WINDOW_WIDTH/2 - 5*LETTER_WIDTH , WINDOW_HEIGHT*2/3 , LETTER_WIDTH*8 , LETTER_WIDTH ); 

      afficherClavierWindow(TabLettres , Window, renderer  , Rect); 
                
      SDL_RenderPresent(renderer); 


      SDL_FreeSurface(Wallpaper);
      SDL_FreeSurface(OkButton); 
      SDL_FreeSurface(DelButton); 
      SDL_FreeSurface(afficheur); 
      SDL_FreeSurface(homebutton); 

      
  }

void afficherBoutonsPermite(SDL_Window *Window , SDL_Renderer *renderer , SDL_Surface *TabButton[MaxButton]  ,  int TailleMot ){
//int minButton = TailleMot/2 ; 
//int maxButton = TailleMot - 1 ; 
SDL_Rect rectButton ; 
if(TailleMot/2 == 1)// cas speciale mot de 3 lettres
{
initRect(&rectButton , WINDOW_WIDTH/2 - BUTTON_WIDTH*0.5  , WINDOW_HEIGHT - 70 , BUTTON_WIDTH , BUTTON_WIDTH); 
afficher(Window , renderer , TabButton[1] , rectButton ) ; 
}
else{
int D = (TailleMot) - (TailleMot/2); // la distance = nombre de bouttons  
initRect(&rectButton , WINDOW_WIDTH/2 - BUTTON_WIDTH*(D-1.5)  , WINDOW_HEIGHT - 70 , BUTTON_WIDTH , BUTTON_WIDTH); 
for(int i = 0 ; i < D ; i++ ){
afficher(Window , renderer , TabButton[TailleMot/2 + i - 1] , rectButton ) ; 
rectButton.x += BUTTON_WIDTH ; 
}
}


}


int choixNbPermut(SDL_Event event , int TailleMot , SDL_Window *Window, SDL_Renderer *renderer, liste_combin *t, CelluleMot tabLet[TailleMaxMot],int *nbcombpossible, liste_combin TabAdrComb[15]){
int D ; // nombre de buttons 
 int indice = -1 ; 
D = (TailleMot) - (TailleMot/2);
if ((event.button.x >  WINDOW_WIDTH/2 - BUTTON_WIDTH*(D-1.5)) && (event.button.x <  WINDOW_WIDTH/2 + BUTTON_WIDTH*(D+0.5)) && (event.button.y >  WINDOW_HEIGHT - 70 ) && (event.button.y < WINDOW_HEIGHT - 70 + BUTTON_WIDTH )  ){
  if(TailleMot/2 == 1)// cas speciale mot de 3 lettres
      indice = 1 ; 
   else{
    indice = (event.button.x - (WINDOW_WIDTH/2 - BUTTON_WIDTH*(D-1.5)))/ BUTTON_WIDTH ; 
    // npermut = TailleMot/2 + indice
   } 
   AfficheCombinPossibles(Window , renderer , t , tabLet , TailleMot/2 + indice ,  TailleMot , nbcombpossible ,TabAdrComb);
}


    return (TailleMot/2 + indice) ; 
}


void UserChoixLetClavier (SDL_Surface *TabAlohabet[26]  , SDL_Window *Window , SDL_Renderer *renderer ,SDL_Event event , SDL_Rect *RectanAffMotClav ,CelluleMot TabLet[TailleMaxMot],CelluleMot tabLetChangeJoueur[TailleMaxMot], CelluleMot tabLetBut[TailleMaxMot], int Name[TailleMaxMot] ,  int *TailleMot , int *TailleName   , SDL_Surface *eraser ,  SDL_Surface *TabButton[7] , bool *clavActive , bool* npermutChoix , bool *NameEnter , int mode , int *npermut , int *minut , int *second){
    if(mode==1){
       (*NameEnter) = false ;  // la machine ne saisie pas son nom 
    }

                    int  indiceTabClavier ; 
                    int donothing = 1 ; 
                    
                int Taille ; 
                if((*NameEnter)== true) {
                  Taille = (*TailleName) ;// user enter Name 
                  }  
                 else{
                   Taille = (*TailleMot) ;  // user enter mot init 
                 }


                    // cadrage clavier 
                    if((event.button.x >  WINDOW_WIDTH /2 - LETTER_WIDTH * 5 ) && (event.button.x < WINDOW_WIDTH /2 + LETTER_WIDTH * 5  ) &&  (event.button.y > WINDOW_HEIGHT*2/3  )  && (event.button.y < WINDOW_HEIGHT*2/3 + (LETTER_WIDTH +20 )*3)  ){


                    if(event.button.y < WINDOW_HEIGHT*2/3 + LETTER_WIDTH  ) 
                          indiceTabClavier = ((int) (( event.button.x- (WINDOW_WIDTH /2 - LETTER_WIDTH * 5) )) / LETTER_WIDTH)  ; 
                    
                       else{ 
                        
                            if((event.button.y > WINDOW_HEIGHT*2/3 + (LETTER_WIDTH +20 )*2)  ){
                                if(event.button.x > (WINDOW_WIDTH /2 - LETTER_WIDTH * 3)    && event.button.x < (WINDOW_WIDTH /2 + LETTER_WIDTH * 3)  ){
                                 indiceTabClavier = ((int) (( event.button.x- (WINDOW_WIDTH /2 - LETTER_WIDTH * 3) )) / LETTER_WIDTH + 20 )   ;
                                }
                                 else // ok button 
                                   if((Taille>=3) && (event.button.x > WINDOW_WIDTH/2 + 3*LETTER_WIDTH)  && (event.button.x < WINDOW_WIDTH/2 + 5*LETTER_WIDTH) && (event.button.y> WINDOW_HEIGHT*2/3+ 2*LETTER_WIDTH + 20*2) && (event.button.y< WINDOW_HEIGHT*2/3 + LETTER_WIDTH*3 +20*3) ){

                                            if((*NameEnter)== true && Taille>=3 ){ // user a enteree le Nom 
                                                donothing =  0 ;  

                                                     for(int i = (*TailleName) ; i< TailleMaxMot ; i++){
                                                       saveCodeName (-1 ) ; // lettres vide == -1 dans fichier 
                                                     }

                                               /**/   // rect milieu pret pour mot init     
                                                (*NameEnter) = false ;

                                                if(mode == 0 ){ 
                                                      // afficher entrez nom init si pas mode user alone (user alone dont choose his word the computer do it randomly instead ) 
                                                       // afficher : Entrez mot init: ----------------------------------------------------------------
                                                         initRect(RectanAffMotClav , WINDOW_WIDTH/3 ,  WINDOW_HEIGHT*2/3 - 70 , LETTER_WIDTH ,  LETTER_WIDTH );  // Apres entrer le nom on a besoin de réecrire dur le meme clavier 
                                                        SDL_Surface *EnterMotInit  = creeSurface("../src/images/entrezMotInit.png", Window  , renderer ); 
                                                        initRect(RectanAffMotClav , WINDOW_WIDTH/2 - 250/2 , WINDOW_HEIGHT*2/3 - 120 , 40 , 250 ); 
                                                        afficher(Window , renderer , EnterMotInit , *RectanAffMotClav );
                                                        //---------------------------------------------------------------------------------------------
                                                        // afficher afficheur vide  : 
                                                      SDL_Surface *afficheur  = creeSurface("../src/images/ecranClav.png", Window  , renderer ); 
                                                      initRect(RectanAffMotClav , WINDOW_WIDTH/2 - 4*LETTER_WIDTH , WINDOW_HEIGHT*2/3 - 70 , LETTER_WIDTH*8 , LETTER_WIDTH  ); 
                                                      afficher(Window , renderer , afficheur , *RectanAffMotClav );
                                                      SDL_FreeSurface(afficheur); 
                                                     SDL_FreeSurface(EnterMotInit); 
                                                }
                                                // else afficher loading 
                                              
                                                  else if(mode == 2 ){ // user  alone 
                                                  (*clavActive)=false ;
                                                   BackgroundPlayer (TabLet, tabLetChangeJoueur,tabLetBut,TabAlohabet, Window , renderer , TailleMot ,  npermut , minut , second ); 
                                                }
                                            } 
                                            else{
                                              if((*NameEnter)== false && Taille>=3 ) // user a entree le mot init 
                                              {
                                               afficherBoutonsPermite(Window , renderer , TabButton , Taille) ; 
                                               donothing =  0 ; 
                                               (*clavActive) = false ; 
                                               (*npermutChoix) = true ;   
                                              }
                                            }
                                        } 
                                        else { // Delite Button 
                                           if( (event.button.x > WINDOW_WIDTH/2 - 3.5*LETTER_WIDTH -50)  && (event.button.x < WINDOW_WIDTH/2 - 3.5*LETTER_WIDTH  ) && (event.button.y> WINDOW_HEIGHT*2/3+2*LETTER_WIDTH + 20*2) && (event.button.y<WINDOW_HEIGHT*2/3+2*LETTER_WIDTH + 20*2 + 50 ) ){
                                                donothing =  0 ;
                                            if((*NameEnter)==true && Taille >0 ){
                                              (*TailleName) = 0 ; 
                                               AfficheurClavierWall(TabAlohabet, Window, renderer , mode );
                                              // vider Name : 
                                                  for (int i =0 ; i< TailleMaxMot ; i++){
                                                        Name[i]= -1 ; 
                                                    }
                                                  (*TailleName)= 0 ; 
                                            }
                                            else{ // delite mot init 
                                              if((*NameEnter)==false && Taille > 0){
                                                 destruction(Window ,  renderer ,TabAlohabet,  TabLet ,  TailleMot , mode ); 
                                                 SupEtAjoutFile("motInit.txt" , mode ); // vide ancien mot du fichier et garder le mode 

                                                 Taille = 0 ; 
                                              } 
                                            }
                                            } 
                                        }                
                               }
                                else indiceTabClavier = ((int) (( event.button.x- (WINDOW_WIDTH /2 - LETTER_WIDTH * 5) )) / LETTER_WIDTH +10)  ;                         

                                                 
                        

                        }


                    if (donothing == 1 && Taille < TailleMaxMot){

                        if((*NameEnter)== true){ // les mot construit == le nom de l'utilisateur 
                        saveCodeName( indiceTabClavier)  ; // save mot init 
                          Name[Taille] = indiceTabClavier ; 
                          (*TailleName) ++ ;
                        }
                        else{ // si le mot entree est mot init
                        saveCodeMotInitFile(TabAlohabet , indiceTabClavier)  ; // save mot init 
                        TabLet[Taille].img = TabAlohabet[indiceTabClavier] ;
                        (*TailleMot) ++ ;
                        TabLet[Taille].rotationEtPos = Taille + 1 ; 
                        }
                            
                            Taille ++ ; 

                          (RectanAffMotClav->x)  = WINDOW_WIDTH/2 - Taille*LETTER_WIDTH/2 ;

                        for(int i=0 ; i<Taille ; i++){
                            afficher( Window, renderer ,eraser,  *RectanAffMotClav  )  ;
                            if((*NameEnter)== true){
                              afficher( Window, renderer ,TabAlohabet[Name[i]] ,  *RectanAffMotClav  )  ;  
                            }
                            else afficher( Window, renderer ,TabLet[i].img ,  *RectanAffMotClav  )  ;// afficher mot init 
                            (RectanAffMotClav->x)  += LETTER_WIDTH ;

                        }


                    }



                }
                    SDL_RenderPresent(renderer);
}
                 
                    

/*---------------------------------------------------------------------------------*/
                 //   Fonction Button 
/*---------------------------------------------------------------------------------*/

  void chargerLesBoutonsOnMemoire(SDL_Window *Window , SDL_Renderer *renderer , int* nbButton , SDL_Surface *TabButton[7]){


     RemplirTabOfInt_Button(Window ,renderer , nbButton , TabButton, "../src/images/1.png" ); 
     RemplirTabOfInt_Button(Window ,renderer , nbButton , TabButton, "../src/images/2.png" ); 
     RemplirTabOfInt_Button(Window ,renderer , nbButton , TabButton, "../src/images/3.png" ); 
     RemplirTabOfInt_Button(Window ,renderer , nbButton , TabButton, "../src/images/4.png" ); 
     RemplirTabOfInt_Button(Window ,renderer , nbButton , TabButton, "../src/images/5.png" ); 
     RemplirTabOfInt_Button(Window ,renderer , nbButton , TabButton, "../src/images/6.png" ); 
     RemplirTabOfInt_Button(Window ,renderer , nbButton , TabButton, "../src/images/7.png" ); 
}

void chargerTempsPhotoEnMemoire(SDL_Window *Window , SDL_Renderer *renderer , SDL_Surface *TabTemps[TailleMaxMot]){

     TabTemps[0] =creeSurface("../src/images/0.png", Window , renderer)    ;
     TabTemps[1] =creeSurface("../src/images/1.png", Window , renderer)    ;
     TabTemps[2] =creeSurface("../src/images/2.png", Window , renderer)    ;
     TabTemps[3] =creeSurface("../src/images/3.png", Window , renderer)    ;
     TabTemps[4] =creeSurface("../src/images/4.png", Window , renderer)    ;
     TabTemps[5] =creeSurface("../src/images/5.png", Window , renderer)    ;
     TabTemps[6] =creeSurface("../src/images/6.png", Window , renderer)    ;
     TabTemps[7] =creeSurface("../src/images/7.png", Window , renderer)    ;
     TabTemps[8] =creeSurface("../src/images/8.png", Window , renderer)    ;
     TabTemps[9] =creeSurface("../src/images/9.png", Window , renderer)    ;
}

    

void afficherTabButtonWindow(SDL_Surface *T[MaxButton] , SDL_Window *Window, SDL_Renderer *renderer  , SDL_Rect Rectangle, int Taille , int npermut){
    
    int i = 0 ; 
    printf("\n");
  if (Taille == 0 ){
          printf("Le mot est vide \n");
    }
    else{
        while(Taille - npermut + 1 != 0 ){
        afficher(Window ,renderer , T[i] ,Rectangle);  
        i++ ; 
        Taille -- ; 
        Rectangle.x += LETTER_WIDTH ; 
        }
        printf("\n");
    }
    }
              // else : u found it ! 
            


void UserChoixMotBut(CelluleMot tabLetBut[TailleMaxMot],CelluleMot TabMotInit[TailleMaxMot], liste_combin *listecomb  ,liste_combin TabAdrComb[15] , SDL_Window *Window , SDL_Renderer *renderer , SDL_Event event , int TailleMot  , int nCombinMot ,CelluleMot tabLetChangeJoueur[TailleMaxMot] ,CelluleMot tabLetChangeMachine[TailleMaxMot] ){
    
                    int  indiceTabadrCombin ; 
                    int PosY ; 

                    PosY =(int) ((event.button.y -100) / (LETTER_WIDTH + 20 )) ; 

                    if(event.button.x < WINDOW_WIDTH / 3 ){

                        indiceTabadrCombin =PosY *3 + (int) (( event.button.x- 40 )) / (WINDOW_WIDTH/3) ; 
                    }
                    else if(event.button.x > WINDOW_WIDTH*2 / 3 ){

                            indiceTabadrCombin = PosY *3 + ((int) (( event.button.x- 40 )) / (WINDOW_WIDTH/3) )  ; 
                            
                         }else{
                                    indiceTabadrCombin = PosY *3 + ((int) (( event.button.x- 40 )) / (WINDOW_WIDTH/3) )  ; 
                              }

                        


                        if(indiceTabadrCombin < nCombinMot ){
                            (*listecomb) = TabAdrComb[indiceTabadrCombin] ; 
                            transferTabToMot(tabLetBut, TabMotInit , TabAdrComb[indiceTabadrCombin], TailleMot); 

                             copy_tab_img(tabLetChangeJoueur , TabMotInit , TailleMot ); 
                             copy_tab_img(tabLetChangeMachine, TabMotInit , TailleMot); 
                        }
                        

                    
}            

/*------------------------------------------------------------------------------------------------------------*/
                             // fonctions jouer avec clavier physique 
/*------------------------------------------------------------------------------------------------------------*/

void KeyBordChoixLetMotInit(SDL_Window *Window ,SDL_Renderer *renderer ,  CelluleMot TabLet[TailleMaxMot],CelluleMot tabLetchange[TailleMaxMot] , CelluleMot tabLetBut[TailleMaxMot], int Name[TailleMaxMot] , SDL_Surface* TabButton[7] ,  SDL_Surface *TabClavier[26] ,int *TailleMot ,int *TailleName , SDL_Event event, SDL_Rect *RectanAffMotClav , SDL_Surface *eraser , bool *clavActive , bool *npermutChoix , bool *NameEnter , int mode , int *npermut , int *minute , int *second  ){
int Taille = 0 ; 

if(mode == 1 )(*NameEnter) = false ; // machine ne saisie pas son nom 

if((*NameEnter)==true){// entrer Name {
Taille = (*TailleName); 
}

else{
Taille = (*TailleMot); // enter Mot init 
} 

if((*clavActive)==true && Taille < TailleMaxMot && (event.key.keysym.sym >96) && (event.key.keysym.sym <123)  ){
   

   //  Remplissage avec :    A = 122 / Z = 123
   if((*NameEnter)==true){
   Name[ Taille] = event.key.keysym.sym - 97  ;
   (*TailleName) ++; 
    saveCodeName( event.key.keysym.sym - 97 ) ;  

   }


  else{
   TabLet[ Taille].img = TabClavier[event.key.keysym.sym - 97 ] ; 
   (*TailleMot) ++ ; 
   TabLet[Taille].rotationEtPos = (*TailleMot) ; 

   saveCodeMotInitFile( TabClavier , event.key.keysym.sym - 97 ) ;  
  }

  Taille ++ ; 
   // affichage 
   
 (RectanAffMotClav->x)  = WINDOW_WIDTH/2 - Taille*LETTER_WIDTH/2 ;
                        for(int i=0 ; i<Taille ; i++){
                            afficher( Window, renderer ,eraser,  *RectanAffMotClav  )  ;
                            if((*NameEnter )==  false ){ // afficher mot init 
                              afficher( Window, renderer ,TabLet[i].img ,  *RectanAffMotClav  )  ;  
                              }
                                // afficher Name 
                            else {
                             afficher( Window, renderer ,TabClavier[Name[i]] ,  *RectanAffMotClav  )  ;  
                            }
                            (RectanAffMotClav->x)  += LETTER_WIDTH ;
                        }
   // si fin de Mot : 
}
else if ((*clavActive) ==true && (Taille >= 3) && (event.key.keysym.sym == SDLK_RETURN )){ 
    // clicker ok : fin mot init 
    if((*NameEnter)== false && Taille >=3 ){
      
     afficherBoutonsPermite(Window , renderer , TabButton , Taille) ; 
    (*clavActive) = false ; 
    (*npermutChoix) = true ;
    (*TailleName) = Taille ; 
    }
    else { 
     if((*NameEnter)== true && Taille >=3){
                     
                  for(int i = (*TailleName) ; i< TailleMaxMot ; i++){
                   saveCodeName (-1 ) ; // lettres vide == -1 dans fichier 
                   }
  if(mode == 0 ){ 
        // afficher : Entrez mot init: ----------------------------------------------------------------
        initRect(RectanAffMotClav , WINDOW_WIDTH/3 ,  WINDOW_HEIGHT*2/3 - 70 , LETTER_WIDTH ,  LETTER_WIDTH );  // Apres entrer le nom on a besoin de réecrire dur le meme clavier 
        SDL_Surface *EnterMotInit  = creeSurface("../src/images/entrezMotInit.png", Window  , renderer ); 
        initRect(RectanAffMotClav , WINDOW_WIDTH/2 - 250/2 , WINDOW_HEIGHT*2/3 - 120 , 40 , 250 ); 
        afficher(Window , renderer , EnterMotInit , *RectanAffMotClav );
        //---------------------------------------------------------------------------------------------
       // afficher afficheur vide  : 
        SDL_Surface *afficheur  = creeSurface("../src/images/ecranClav.png", Window  , renderer ); 
        initRect(RectanAffMotClav , WINDOW_WIDTH/2 - 4*LETTER_WIDTH , WINDOW_HEIGHT*2/3 - 70 , LETTER_WIDTH*8 , LETTER_WIDTH  ); 
        afficher(Window , renderer , afficheur , *RectanAffMotClav );
        SDL_FreeSurface(afficheur); 
        SDL_FreeSurface(EnterMotInit); 
       }
  
      initRect(RectanAffMotClav , WINDOW_WIDTH/3 ,  WINDOW_HEIGHT*2/3 - 70 , LETTER_WIDTH ,  LETTER_WIDTH );  // Apres entrer le nom on a besoin de réecrire dur le meme clavier 
     (*NameEnter) = false ; 
      (*TailleName) = Taille ; 

        if(mode == 2 ){ // user  alone 
               (*clavActive)=false ; 
                BackgroundPlayer (TabLet, tabLetchange ,tabLetBut,TabClavier, Window , renderer , TailleMot ,  npermut , minute , second ); 
        }
     }

    }

}


                SDL_RenderPresent(renderer);

}


int KeyBordChoixNpermut(SDL_Window *Window ,SDL_Renderer *renderer  , CelluleMot TabLet[TailleMaxMot],int TailleMot, SDL_Event event, liste_combin *listeCombin   , int *nbCpmbinMot ,liste_combin TabAdrComb[15], bool *clavActive , bool* npermutChoix , bool *choixCombin){
                          // SDLK_0 == 48 / SDLK_0 == 49 / ........
                         if(event.key.keysym.sym >= SDLK_2 && event.key.keysym.sym - SDLK_0 <=TailleMot-1){
                          int npermut ; 
 
                          if((TailleMot > 3)){
                           (*npermutChoix)=false ; 
                           (*choixCombin)=true ;  
                        	npermut =  (event.key.keysym.sym  - 48 ) ; 
                          }

                           else if(TailleMot == 3 && (event.key.keysym.sym ==  SDLK_2 )) // Taille Mot == 3 est un cas particulier 
                           {
                            (*npermutChoix)=false ;
                             (*choixCombin)=true ;  
                              npermut =  2  ; 
                           }

                          AfficheCombinPossibles(Window , renderer , listeCombin , TabLet , npermut ,  TailleMot , nbCpmbinMot ,TabAdrComb);
                          return npermut ; 
                         }


}


void UserPlaysWithKeybored(SDL_Window *Window, SDL_Renderer *renderer, CelluleMot tabLetChange[TailleMaxMot], CelluleMot TabBut[TailleMaxMot],CelluleMot tabLetChangeMachine[TailleMaxMot], SDL_Event event,liste *lchemin, int npermut, int TailleMot, int *Y_avancement, int mode, int minute , int second  , bool *flagTime , SDL_Surface *TabTemps[10], ScoreCel BestScore [5], int Name[TailleMaxMot] , int TailleName, char bufferDate[ MAX_SIZE_Date ]){
     
selection(Window , renderer, event, flagTime);   // menu Timer selection

if((*flagTime)==true){
int x;
  if (mode == 0)
    x = XJoueurDebut;
  else
    x = XDebut;

  if (event.key.keysym.sym >= SDLK_1 && event.key.keysym.sym  <= SDLK_0 +TailleMot - npermut + 1 )
  {
    SDL_Rect Recatn;

    if (compare_Mot(tabLetChange, TabBut, TailleMot) != 0)
    {

      int indiceTabBoutons = event.key.keysym.sym - SDLK_1 ; //pas SDLK_0 car indice tab commance par 0
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
         SDL_Surface *scroll  = creeSurface("../src/images/wallpaper.png", Window  , renderer ); 
         afficher(Window , renderer , scroll , Recatn ); 
         SDL_FreeSurface(scroll); 
         (*Y_avancement) += 50;
      }
      /*initRect(&Recatn, x, YDebut + (*Y_avancement), LETTER_WIDTH, LETTER_WIDTH);
      (*Y_avancement) += 50;*/

      afficherTabWindow(tabLetChange, Window, renderer, Recatn, TailleMot);
      saveCodeMotCurntFile(indiceTabBoutons);
      // we stop timer if we find the correct word 
      if  (compare_Mot(tabLetChange, TabBut, TailleMot) == 0){
         BestScoreMiseAJours(BestScore ,  minute ,  second ,  Name ,  TailleName , bufferDate);
        (*flagTime)=false ; 
            // partie termineé donc vider les fichiers : 
          supprimFile("motCurnt.txt"); 
          supprimFile("motInit.txt"); 
          supprimFile("motBut.txt");
          supprimFile("motName.txt");

           SDL_Rect rect ; // afficher u won : 
          SDL_Surface *bravo = creeSurface("../src/images/bravo.png", Window  , renderer ); 
 
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
      // machine plays also : 
      else if (mode == 0 ) MachinePlaysWithUser(Window , renderer , tabLetChangeMachine , lchemin , npermut , Y_avancement , TailleMot); 
 
    }
  }
    // else : u found it !
  }
        SDL_RenderPresent(renderer);

}


void KeyBordPlaying(SDL_Window *Window ,SDL_Renderer *renderer ,  CelluleMot TabLet[TailleMaxMot] ,CelluleMot tabLetChangeJoueur[TailleMaxMot],CelluleMot tabLetChangeMachine[TailleMaxMot],int Name[TailleMaxMot],CelluleMot tabLetBut[TailleMaxMot],liste *lchemin, SDL_Surface* TabButton[7] ,  SDL_Surface *TabClavier[26] ,int *TailleMot , int *TailleName  , SDL_Event event, int mode ,  SDL_Rect *Recatn , SDL_Surface *eraser, int *npermut, int *Y_avancement, liste_combin *listeCombin   , int *nbCpmbinMot ,liste_combin TabAdrComb[15],bool *choixCombin  , bool *clavActive , bool *npermutChoix , bool *timeFalgRunning , bool *NameEnter ,int *minute ,int *seconde, SDL_Surface *TabTemps[10], ScoreCel BestScore [5] , char bufferDate[ MAX_SIZE_Date ]  )
{
    if((*clavActive)==true){
     KeyBordChoixLetMotInit(Window ,renderer ,  TabLet, tabLetChangeJoueur , tabLetBut , Name , TabButton , TabClavier , TailleMot , TailleName ,  event , Recatn , eraser , clavActive , npermutChoix , NameEnter , mode , npermut , minute , seconde ); 

    }
    else if((*npermutChoix)==true){
    }
    else{
        if ((*choixCombin)==false){
        UserPlaysWithKeybored (Window , renderer , tabLetChangeJoueur, tabLetBut , tabLetChangeMachine ,   event ,lchemin , *npermut, *TailleMot ,Y_avancement ,  mode, *minute , *seconde , timeFalgRunning  ,TabTemps , BestScore , Name, *TailleName , bufferDate );//XJoueurDebut 
        }
    }
}
