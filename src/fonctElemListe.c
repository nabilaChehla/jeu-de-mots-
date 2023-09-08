

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


#include "machine_Abstraite_Header.h"




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
void permute(int T[TailleMaxMot], int n, int indice)
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
void DelTab(CelluleMot T[TailleMaxMot], int *Taille)
{
    while ((*Taille)!=0)
    {
        T[(*Taille)-1].img=NULL ;
        T[(*Taille)-1].rotationEtPos=0 ; 
        (*Taille)-- ; 
    }

}

/*---------------------------------------------------------------------------*/
void permuteJoueur(CelluleMot T[TailleMaxMot], int n, int indice)
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
void copy_tab(int T1[TailleMaxMot], int T2[TailleMaxMot], int taille)
{
    int i;
    for (i=0;i<taille;i++)
    {
        T1[i]=T2[i];
    }
}


void copy_tab_img(CelluleMot T1[TailleMaxMot], CelluleMot T2[TailleMaxMot], int taille)
//  T1 <- T2
{
    int i;
    for (i=0;i<taille;i++)
    {
        T1[i].img=T2[i].img;
        T1[i].rotationEtPos=T2[i].rotationEtPos;
    }
}
/*------------------------------------------------------------------------*/

int compare_tab(int T1[TailleMaxMot], int T2[TailleMaxMot], int taille)
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



int compare_Mot (CelluleMot tabLetChange[TailleMaxMot],CelluleMot TabLet[TailleMaxMot] ,int TailleMot){
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
liste_combin toute_combin(int T[TailleMaxMot],int npermut ,int Taille)
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
    printf("finish\n"); 
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
void affiche_chemin(liste_combin p )
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


void affiche_tab(int T[TailleMaxMot], int taille)
{
    int i;
    for (i=0;i<taille;i++)
    {
        printf("%d|",T[i]);
    }
   
}


/*---------------------------------------------------------------------------------*/
                 //  action : liste linaire chainée LLC 
/*---------------------------------------------------------------------------------*/


void affiche_tabMot(CelluleMot T[TailleMaxMot] , int taille)
{
    for (int i=0 ;i<taille ;i++)
    {
        printf("%d | ",T[i]);
    }
   
}




void ajouterTete (liste *tete,int Val){

liste nouv = allouer_liste();
(nouv->svt2) = *tete;
        (nouv->info) = Val;
        *tete = nouv;
}


void ajouterApresAdress(liste *adr , int Val){
liste nouv = allouer_liste();
   // Liste Adr = *adr ;
    nouv->svt2 = (*adr)->svt2 ;
    (*adr)->svt2 = nouv ;
    nouv->info = Val ;
}



int calculeTailleName(int Name [TailleMaxMot]){
int Taille = 0 ; 
while(Name[Taille]>=0){
  Taille ++ ; 
}
return Taille ; 
}