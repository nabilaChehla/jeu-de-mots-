
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


#include "machine_Abstraite_Header.h"



#define XMachineDebut (WINDOW_WIDTH /4  - 0.5* (TailleMot* 40))
#define XJoueurDebut (WINDOW_WIDTH*3 /4  - 0.5* (TailleMot* 40))
#define YDebut (WINDOW_WIDTH / 5)

// compil :  cd "d:\usthb\Alsdd\TD\TDProg\" ; if ($?) { g++ fonctionLLC.c -o Biblio_machineAbstraite } ; if ($?) { .\fonctionLLC }


/*---------------------------------------------------------------------------------*/
                 //  action : liste linaire chainée LLC 
/*---------------------------------------------------------------------------------*/

liste_combin allouer_combin( )
{
liste_combin nouv =  ((liste_combin ) malloc( sizeof( Cellule_Combine )));
 if (nouv == NULL){
        printf("Erreur memoire saturee \n");
        exit(-1);
    }
    else return nouv ; 

}


liste allouer_liste( )
{
liste nouv =  ((liste ) malloc( sizeof( Cellule)));
 if (nouv == NULL){
        printf("Erreur memoire saturee \n");
        exit(-1);
    }
     else return nouv ; 
}



/*------------------------------------------------------------------------*/
void permute(int T[8], int n, int indice)
{
    int i,cn,tmp;
    i=1; cn=n;
    while(i<=n/2)
    {
        tmp=T[indice+i-1];
        T[indice+i-1]=(-1)*T[indice+cn-1];
        T[indice+cn-1]=(-1)*tmp;
        i=i+1;
        cn=cn-1;
    }
    if(n%2==1)
        T[(indice*2-1+n)/2]=(-1)* T[(indice*2-1+n)/2];
}
/*---------------------------------------------------------------------------*/
void permuteJoueur(CelluleMot T[8], int n, int indice)
{
    int i,cn;
    CelluleMot tmp ; 
    i=1; cn=n;
    while(i<=n/2)
    {
        tmp.img=T[indice+i-1].img;
        tmp.rotationEtPos=T[indice+i-1].rotationEtPos ;

        T[indice+i-1].rotationEtPos=(-1)*T[indice+cn-1].rotationEtPos;
        T[indice+cn-1].rotationEtPos=(-1)*tmp.rotationEtPos;

        T[indice+i-1].img=T[indice+cn-1].img; 
        T[indice+cn-1].img=tmp.img;
        i=i+1;
        cn=cn-1;
    }
    if(n%2==1)
        T[(indice*2-1+n)/2].rotationEtPos=(-1)* T[(indice*2-1+n)/2].rotationEtPos;
}
/*------------------------------------------------------------------------*/
void copy_tab(int T1[10], int T2[10], int taille)
{
    int i;
    for (i=0;i<taille;i++)
    {
        T1[i]=T2[i];
    }
}


void copy_tab_img(CelluleMot T1[8], CelluleMot T2[8], int taille)
{
    int i;
    for (i=0;i<taille;i++)
    {
        T1[i].img=T2[i].img;
        T1[i].rotationEtPos=T2[i].rotationEtPos;
    }
}
/*------------------------------------------------------------------------*/
int compare_tab(int T1[8], int T2[8], int taille)
{
    int verif,i;
    i=0;verif=0;
    while(i<taille && verif!=1)
    {
        if(T1[i]!=T2[i])
            {verif=1;}
        i=i+1;
    }
    return verif;
}



int compare_Mot (CelluleMot tabLetChange[8],CelluleMot TabLet[8] ,int TailleMot){
    // return 0 if equal 1 if not 

    for (int i =0 ; i< TailleMot ; i++)
    {
        if( tabLetChange[i].img != TabLet[i].img)
            return 1 ; 
        
        if( tabLetChange[i].rotationEtPos != TabLet[i].rotationEtPos) 
           return 1 ; 
    }
    return 0 ; 
}
/*------------------------------------------------------------------------*/
liste_combin toute_combin(int T[8],int npermut ,int Taille)
{
    int i,existe;
     int nbpossible= Taille -npermut+1;
    liste_combin p,q,copietete, tete = allouer_combin() ;
    liste s,r;

    copy_tab(tete->tab,T,Taille);
    tete->svt1=NULL;
    tete->chemin=NULL;
    q=NULL;
    p=tete;
    do
    {
       for (i=0;i<nbpossible;i++)
       {
           copy_tab(T,p->tab,Taille);
           permute(T,npermut,i);
           copietete=tete;
           existe=0;
           while(copietete!=NULL && existe!=1)
           {
               if (compare_tab(T,copietete->tab,Taille)==0)
               {
                   existe=1;
               }
               copietete=copietete->svt1;
           }
           if(existe==0)
           {
               if(q==NULL)
               {
                   (p->svt1) = allouer_combin();
                   q=(p->svt1);
               }
               else
               {
                   q->svt1=allouer_combin();
                   q=q->svt1;
               }
               copy_tab(q->tab,T,Taille); q->svt1=NULL; q->chemin=NULL;
               if(p->chemin==NULL)
               {
                   q->chemin=allouer_liste();
                   s=q->chemin;
                   s->info=i;
                   s->svt2=NULL;
               }
               else
               {
                  s=p->chemin;
                  r=allouer_liste();
                  r->info=s->info;
                  r->svt2=NULL;
                  q->chemin=r;
                  s=s->svt2;
                  while (s!=NULL)
                  {
                      r->svt2=allouer_liste();
                      r=r->svt2;
                      r->info=s->info;
                      r->svt2=NULL;
                      s=s->svt2;
                  }
                  r->svt2=allouer_liste();
                  r=r->svt2;
                  r->info=i;
                  r->svt2=NULL;
               }
           }
       }
       p=p->svt1;
    }while(p!=q);
    return tete;
}
/*------------------------------------------------------------------------*/

int AfficheBool ( liste_combin p , int N  ){
 
   int i = 0 ; 



     if ((p->tab[i]) < 0 ){
        while( i < N )
     {

        if( (p->tab[i]) > 0 ){

            return 1 ; 
        } 
        i ++ ; 
     }

    }
    else{

        while( i< N )
          {

            if( (p->tab[i]) < 0 )
            {
              return 1 ; 
            } 
            i++ ; 
         }
    }

    
    
    return 0 ; 
}


/*--------------------------------------------------------------------------*/
void affiche_chemin(liste_combin p , int N )
{


       liste s ;   
       s = (p->chemin);    
       while(s!=NULL)
       {
        printf("%d ->",s->info);
        s=s->svt2;
       }
         printf("NULL");
          printf("\n\n"); 
    

    
}


void affiche_tab(int T[10], int taille)
{
    int i;
    for (i=0;i<taille;i++)
    {
        printf("%d|",T[i]);
    }
   
}




void affiche_tabMot(CelluleMot T[10] , int taille)
{
    for (int i=0 ;i<taille ;i++)
    {
        printf("%d | ",T[i]);
    }
   
}