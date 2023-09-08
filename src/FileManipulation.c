
#include <SDL.h> 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <conio.h>  
#include <stdbool.h>



#include "machine_Abstraite_Header.h"

void saveCodeMotInitFile( SDL_Surface *TabClavier[26] , int indice ){
    // USED INSIDE USER CHOIX MOT ONLY 
    FILE* fichierMotSave = fopen("motInit.txt", "a");
    if (fichierMotSave != NULL)
    {
        if (indice<10) fprintf(fichierMotSave,"0"); 
         fprintf(fichierMotSave,"%d ", indice);
         fclose(fichierMotSave);
    }
}


void saveCodeName ( int indice ){
    // USED INSIDE USER CHOIX MOT ONLY 
    FILE* fichierMotSave = fopen("motName.txt", "a");
    if (fichierMotSave != NULL)
    {
        if (indice<10 && indice >=0) fprintf(fichierMotSave,"0"); 
         fprintf(fichierMotSave,"%d ", indice);
         fclose(fichierMotSave);
    }
}




void saveCodeMotButFile( liste_combin t , int npermut  ){
    // USED INSIDE USER CHOIX MOT ONLY  

    FILE* fichierMotSave = fopen("motBut.txt", "w+");
    if (fichierMotSave != NULL)
    {
      fprintf(fichierMotSave,"%d ", npermut );
      liste c  = t->chemin ; 
        while ( c != NULL)
        {
          fprintf(fichierMotSave,"%d ", c->info);
          printf("chemin : %d \n",c->info); 
          c = c->svt2 ; 
        }
        
    }
}



int nbCharFile (const char *Strg){ 
   /* parcours du fichier */
FILE* file = fopen(Strg, "r");
 if (file != NULL){
    int compteur =  0 ;
    while(fgetc(file) != EOF)
    compteur ++; /* incrémentation du compteur */
     fclose(file);
     printf("cmp : %d \n",compteur); 
    return compteur ; 

 }
   else printf("error nb char"); 
 }


bool FichierEstVide(const char *Strg){
FILE* file = fopen(Strg, "r");
bool b ; 
if (file != NULL){
    if(nbCharFile(Strg)==0)
    b = true ; 
    else b = false ; 
    fclose(file);
    return b ; 
 }
   else printf("error nb char"); 
 }


void SupEtAjoutFile(const char *Strg , int n){
  FILE* file = fopen(Strg,"w+");
    if (file != NULL){
    fprintf(file , "%d ", n); 
    fclose(file);
 }  
}


void addFromLasteFile(const char *Strg , int n){
  FILE* file = fopen(Strg,"a");
    if (file != NULL){

    fclose(file);
 }  
}




void saveCodeMotCurntFile( int indiceperm ){
    // USED INSIDE USER plays (click bouton de permut) only 
    FILE* fichierMotSave = fopen("motCurnt.txt", "a");
    if (fichierMotSave != NULL)
    {
        fprintf(fichierMotSave , "%d ", indiceperm); 
        fclose(fichierMotSave);
    }
}


  void supprimFile(const char *Strg){
  FILE* file = fopen(Strg,"w+");
    if (file != NULL){
    fclose(file);
 }  
}



void saveTimerTxt(int minute , int second , bool fichInitVide){
  FILE* file = fopen("TimerCurnt.txt","w+");
    if (file != NULL){
      if (minute<10) fprintf(file,"0"); 
       fprintf(file , "%d ", minute); 
       if (second<10) fprintf(file,"0"); 
       fprintf(file , "%d", second); 
      
        fclose(file);
 }  
}
     // recuperer ancien timer
void OldTimer (int *minut , int *second){
   FILE *timeFile = fopen("TimerCurnt.txt", "r");
      if (timeFile != NULL){
       fscanf(timeFile, "%d ", minut);
       fscanf(timeFile, "%d ", second);
       fclose(timeFile); 
       }
}



void recupBestScore(ScoreCel BestScore [5]){
 
  int  j=0 ; 

FILE* fileScore = fopen("Score.txt","r");
if (fileScore != NULL){
     while(fgetc(fileScore) != EOF  && j< 5 ){

        // attention: bug pour la 1ere ligne lorsque min > 9 
      fscanf(fileScore , "%d ", &BestScore[j].timeScore); 
      printf("fileScore : %d\n",BestScore[j].timeScore); 


      printf("\n Date : ");
      for(int i =0 ;  i< 10 ; i++){
         BestScore[j].Date[i] =  fgetc(fileScore) ; 
        printf("%c",BestScore[j].Date[i]);   
          }
          
          printf("\n Name : "); 

      fseek(fileScore, 1 , SEEK_CUR);

      for(int i =0 ;  i< 8 ; i++){
        fscanf(fileScore , "%d", &BestScore[j].NameUser[i]); 
        if(i!=7) fseek(fileScore, 1 , SEEK_CUR); // si pas la derniere lettre du mot (car ne contient pas char blanc a la fin )
        printf("%d ",BestScore[j].NameUser[i]); 
      }
      printf("\n");
      fseek(fileScore, 1 , SEEK_CUR);
      j++ ; 
       }
      fclose(fileScore); 
    }
}

void BestScoreMiseAJours(ScoreCel BestScore [5] , int minute , int second , int Name[TailleMaxMot] , int TailleName , char bufferDate[ MAX_SIZE_Date ] ){
 FILE* fileScore = fopen("Score.txt","w");
 int j=0 , N = 0 ;
char c ; bool insert = true ;   ; 

if (fileScore != NULL){ 
  for (int i = 0 ; i< 5 ; i++){
 // rewrite the old score 
     int  timeScore ; 
       //new score achived 
     if((minute*1000 + second < BestScore[j].timeScore) && (insert == true)){
       timeScore = minute*1000+second ; 
     }
     else{ // no new score achived recuperer the old one 
        timeScore = BestScore[j].timeScore ; 
     }
    // write score 
      if(timeScore < 1000)
      fputc('0',fileScore ); 
      if(timeScore < 100)
      fputc('0',fileScore ); 
      if(timeScore< 10)
      fputc('0',fileScore ); 
      fprintf(fileScore, "%d", timeScore); 
       fputc(' ',fileScore ); 

    // write date
      for(int r =0 ; r< MAX_SIZE_Date ; r++){
        if(minute*1000 + second < BestScore[j].timeScore && insert== true)
        c = bufferDate[r]; 
        else c = BestScore[j].Date[r]; 
        fputc(c , fileScore); 
      }
      fputc(' ',fileScore ); 
      // write Name 
      for(int r = 0 ; r< TailleMaxMot ; r++){
         if(minute*1000 + second < BestScore[j].timeScore && insert == true)
         N = Name[r]; 
         else N = BestScore[j].NameUser[r];

        if(N < 10 && N >= 0 )
            fputc('0',fileScore ); 
        fprintf(fileScore , "%d" , N  ); 
        if (r==TailleMaxMot - 1) // retour a la ligne si fin de mot 
           fputc('\n',fileScore ); 
           else fputc(' ',fileScore );  // espace entre les lettres 

      }
      // pour ne reinserer la valeur deje inserer 
      if((minute*1000 + second < BestScore[j].timeScore) && (insert == true)){
         insert = false ; 
      }
      else j++ ;  // avencer dans la structure qui contient best score 

    }
      fclose(fileScore); 
  }
recupBestScore( BestScore); // mise a jour score inside BestScore structure
}