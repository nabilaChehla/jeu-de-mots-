
#include <SDL.h> 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <conio.h>  
#include <stdbool.h>
#include <time.h>

#include "machine_Abstraite_Header.h"

//int minute=0,second=0;     //global variables

void delay(int ms)  //delay function
{
    clock_t timeDelay = ms + clock();    //Step up the difference from clock delay
    while (timeDelay > clock());         //stop when the clock is higher than time delay
}


void count_time(int *minute , int *second ){
  /*the test if we need to increase or not is done in PP*/
                if((*second) > 59){         //after (*second) is greater than 59, reset (*second) and increase 1 (*minute)
                    (*second) = 0;
                    (*minute)=+1;
                    }
                  //   affiche_time(Window ,renderer,font);
                    delay(1000);
                    //printf("%d : %d\n", (*minute), (*second) ); 
                     (*second) += 1;
}

void affiche_time(SDL_Window *Window , SDL_Renderer *renderer, SDL_Surface *TabTemps[10] , int *minute , int *second ,SDL_Rect *RectangleTemp)
{
         //SDL_Surface *Ecran = creeSurface("../src/images/eraserEcran.jpg" , Window ,renderer);
         SDL_Surface *Ecran = creeSurface("../src/images/eraserEcran.jpg" , Window ,renderer);
         //afficher les minutes
         initRect (RectangleTemp , WINDOW_WIDTH/2-35 ,10 ,30,30 );
         afficher (Window , renderer , Ecran,(*RectangleTemp));
         afficher (Window , renderer , TabTemps[(*minute)%10],(*RectangleTemp));
         initRect (RectangleTemp, WINDOW_WIDTH/2-70 ,10 ,30,30 );
         afficher (Window , renderer , Ecran,(*RectangleTemp));
         afficher (Window , renderer , TabTemps[(*minute)/10],(*RectangleTemp));

        //afficher les secondes 
         initRect (RectangleTemp , WINDOW_WIDTH/2+40 ,10 ,30,30 );
         afficher (Window , renderer , Ecran,(*RectangleTemp));
         afficher (Window , renderer , TabTemps[(*second)%10],(*RectangleTemp));
         initRect (RectangleTemp, WINDOW_WIDTH/2+5 ,10 ,30,30 );
         afficher (Window , renderer , Ecran,(*RectangleTemp));
         afficher (Window , renderer , TabTemps[(*second)/10],(*RectangleTemp));

    // afficher eraser image so we don't see previous time
      // ecrie sur fenetre the time
        SDL_FreeSurface(Ecran); 
        SDL_RenderPresent(renderer);
}

void selection(SDL_Window *Window , SDL_Renderer *renderer,SDL_Event event,bool *flag){      // menu selection

            if( (event.button.x > WINDOW_WIDTH/2- 120)  && (event.button.x <WINDOW_WIDTH/2- 120 +50 ) && (event.button.y>  10 ) && (event.button.y<10+50))
            { // cas pause 
                (*flag) =false;
                printf("im here pause\n"); 
            }
            if((event.button.x >WINDOW_WIDTH/2 +80)  && (event.button.x <WINDOW_WIDTH/2 +80+50) && (event.button.y> 10) && (event.button.y<10+50))
            { //cas resume 
                (*flag) =true;
            }
            if ((event.button.x > 322)  && (event.button.x < 702) && (event.button.y> 492) && (event.button.y<577))
            {
                (*flag) =false;
                exit(0);
            }
}




void resetTime(int *minute , int *second ,bool *flag ){
(*minute)=0 ; 
(*second)=0 ; 
(*flag)=true ; 
}