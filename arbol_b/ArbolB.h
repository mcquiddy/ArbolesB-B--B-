#ifndef ARBOLB_H
#define ARBOLB_H

#include <iostream>
#include "NodoB.h"

using namespace std;


template<typename T>
class ArbolB {

public:
    int orden;
    int min;
    listaArbol<NodeB<T>*>* hojaActual ;
     listaArbol<NodeB<T>*>* raiz;


    void insert(T new_data);
    void insertAux() ;
    void borrar(T pData);
    void borrarAux(listaArbol<NodeB<T>*>* temp);
    void ordenar(listaArbol<NodeB<T>*>* listtemp);
    void printTree();
    void printAux(listaArbol<NodeB<T>*>* temp);
    void CambiarHijos(listaArbol<NodeB<T>*>* temp,NodeB<T>* newNodo);
    void BorrarCaso2(listaArbol<NodeB<T>*>* temp, int pos, NodeB<T> *PadreNodo);
    void BorrarCaso3(listaArbol<NodeB<T>*>* temp, int pos, NodeB<T> *PadreNodo);
    void BorrarCaso4(listaArbol<NodeB<T>*>* temp, int pos, listaArbol<NodeB<T> *> *list_sucesor, NodeB<T> *PadreNodo);
    void BorrarCaso5(listaArbol<NodeB<T>*>* temp, int pos, NodeB<T> *PadreNodo);
    void BorrarCaso6(listaArbol<NodeB<T>*>* temp, NodeB<T> *PadreNodo, listaArbol<NodeB<T>*>* list_hermana);

    listaArbol<NodeB<T>*>* buscarLista(T dato);
     listaArbol<NodeB<T>*>* sucesorInorden( listaArbol<NodeB<T>*>* temp);
    int buscarPos(listaArbol<NodeB<T>*>* pList, T pData);
    listaArbol<NodeB<T> *> * setearHijos(listaArbol<NodeB<T> *> * temp);
    listaArbol<NodeB<T>*>* get_raiz();

    int getOrden();
    ArbolB(int pOrden);
    virtual ~ArbolB();

};


template<typename T>
/**
 * @brief ArbolB<T>::ArbolB: Inicializa los atributos a utilizar
 * @param pOrden: Tamano de la lista del arbol
 *
 */
ArbolB<T>::ArbolB(int pOrden){



     raiz=new listaArbol<NodeB<T>*>();
     hojaActual=raiz;
    orden=pOrden;
      min=orden/2;

}


template<typename T>
/**
 * @brief ArbolB<T>::insert: Inserta el dato al arbol
 * @param new_data: Nuevo dato a insertar
 */
void ArbolB<T>::insert(  T new_data ){
    int i=1;

    if(hojaActual->rove(1)==NULL){
         NodeB<T>* newNodo= new NodeB<T>(new_data);//condicion se usa para a;adir el primer nodo arbol a cada hoja
       hojaActual->insert_tail(newNodo);
       raiz=hojaActual;

       return;
    }
    else if(this->buscarLista(new_data)!=NULL){//en caso que el dato se encuentre, no se toma en cuenta

        return;
    }
    else{
        /// mueve el indice hasta obtener el dato en (i)  que es mayor que el dato ingresado
           while(hojaActual->rove(i+1)!=NULL && hojaActual->rove(i)->get_data()->get_data()<new_data && i<=orden){
               i+=1;
           }

           if(i==orden){//maneja el node del extremo derecho
               if(hojaActual->rove(i)->get_data()->getlistHijoDer()!= NULL){
                   hojaActual=hojaActual->rove(i)->get_data()->getlistHijoDer();
                   insert(new_data);
               }
               else{
                   NodeB<T>* newNodo= new NodeB<T>(new_data);
                   hojaActual->insert_tail(newNodo);
                   this->ordenar(hojaActual);
                   ///Cambiar hijos
                     this->CambiarHijos(hojaActual,newNodo);
                     ///Cambio de hijos finalizado


                   insertAux();
               }
           }
          ///maneja los nodos que tiene hijos izquierdos
           else if(hojaActual->rove(i)!=NULL &&  hojaActual->rove(i)->get_data()->getlistHijoIzq()!= NULL && hojaActual->rove(i)->get_data()->get_data()>new_data ){
               hojaActual=hojaActual->rove(i)->get_data()->getlistHijoIzq();

               insert(new_data);
           }
           ///maneja los nodos que tiene hijos izquierdos
           else if(hojaActual->rove(i)!=NULL && hojaActual->rove(i)->get_data()->getlistHijoDer()!= NULL  && hojaActual->rove(i)->get_data()->get_data()<new_data){
               hojaActual=hojaActual->rove(i)->get_data()->getlistHijoDer();
               insert(new_data);
           }


           else{
               NodeB<T>* newNodo= new NodeB<T>(new_data);
               newNodo->setPadre(hojaActual->rove(1)->get_data()->getPadre());
               hojaActual->insert_tail(newNodo);
               this->ordenar(hojaActual);

               ///Cambiar hijos
            this->CambiarHijos(hojaActual,newNodo);

      ///Cambio de hijos finalizado

               if(hojaActual->length()>orden){

                   insertAux();
               }
               hojaActual=raiz;
          }


    }

}


template<typename T>
/**
 * @brief ArbolB<T>::ordenarAux
 * @param
 */
void ArbolB<T>::insertAux() {

    int datoAux;
    datoAux=hojaActual->rove((orden/2)+1)->get_data()->get_data();

     NodeB<T>*  newNodo= new NodeB<T>(datoAux);
       hojaActual->delete_Pos((orden/2)+1);
       //Si la lista que explota es la raiz
     if(hojaActual->rove(1)->get_data()->getPadre()==NULL){

        listaArbol<NodeB<T>*>* listaP= new listaArbol<NodeB<T>*>();
        listaP->insert_tail(newNodo);

        listaP=this->setearHijos(listaP);//Setea los hijos izquierdos y derechos


        raiz=listaP;
        hojaActual=raiz;
     }
     //Si la lista que explota no es la raiz, entonces se obtiene un padre
     else{

       listaArbol<NodeB<T>*>* temp=this->buscarLista(hojaActual->rove(1)->get_data()->getPadre()->get_data());
        temp->insert_tail(newNodo);//INSERTAR NODO ALA LISTA
        temp=this->setearHijos(temp);//Setea los hijos derechos e izquierdos

         this->ordenar(temp);
         ///Cambiar hijos
       this->CambiarHijos(temp,newNodo);
///Cambio de hijos finalizado

         //Si la lista explota se llama de nuevo a la funcion de insertAux()
         if(temp->length()>orden){


                    hojaActual=temp;

             insertAux();
         }
         hojaActual=raiz;

     }

}


template<typename T>
/**
 * @brief ArbolB::borrar borra un dato del ArbolB
 * @param pData : dato a borrar
 */
void ArbolB<T>::borrar(T pData)
{
     listaArbol<NodeB<T>*>*  temp= this->buscarLista(pData);



     if(temp!=NULL){
         int pos=this->buscarPos(temp,pData);

         ///Caso 1,2,3 7 6 en  que no tenga hijos
          if(temp->rove(pos)->get_data()->getlistHijoDer()==NULL){
              listaArbol<NodeB<T>*>* list_padre=this->buscarLista(temp->rove(pos)->get_data()->getPadre()->get_data());
              int posPadre=this->buscarPos(list_padre,temp->rove(pos)->get_data()->getPadre()->get_data());

              // Caso 1 tenga mayor  al minimo de elementos
             if(temp->length()>min){
                   cout<<" caso 1 "<<endl;
                 temp->delete_Pos(pos);
             }
             //Caso 6 que la hermana izquierda tenga menor o igual al minimo de elementos y
             //que la lista en que se encuentra el elemento no tenga hermana derecha
             else if(list_padre->rove(posPadre)->get_data()->getlistHijoDer()==temp){
                 cout<<" caso 6  sin derecha"<<endl;
                 NodeB<T>* PadreNodo=list_padre->rove(posPadre)->get_data();
                  listaArbol<NodeB<T>*>* list_hermana= PadreNodo->getlistHijoIzq();
                  temp->delete_Pos(pos);

                  this->BorrarCaso6(temp,PadreNodo,list_hermana);

                  if(list_padre->length()<min){

                      this->borrarAux(list_padre);
                  }

             }
             //Caso 6 que la hermana derecha tenga menor o igual al minimo de elementos y
             //que la lista en que se encuentra el elemento no tenga hermana izquierda
             else if(list_padre->rove(posPadre)->get_data()->getlistHijoIzq()==temp){
                 cout<<" caso 6 si  izquierda "<<endl;
                 NodeB<T>* PadreNodo=list_padre->rove(posPadre)->get_data();
                  listaArbol<NodeB<T>*>* list_hermana= PadreNodo->getlistHijoDer();
                  temp->delete_Pos(pos);

                  this->BorrarCaso6(temp,PadreNodo,list_hermana);

                  if(list_padre->length()<min){

                      this->borrarAux(list_padre);
                  }

             }
           //Caso 2 que la hermana derecha tenga mayor  al minimo de elementos
             else if(temp->rove(pos)->get_data()->getPadre()->getlistHijoDer()->length()>min){
                   cout<<" caso 2 "<<endl;
                 NodeB<T>* PadreNodo=temp->rove(pos)->get_data()->getPadre();
                  temp->delete_Pos(pos);
                 this->BorrarCaso2(temp,pos,PadreNodo);
             }

             //Caso 3 que la hermana izquierda tenga mayor al minimo de elementos
              else  if(list_padre->rove(posPadre-1)->get_data()->getlistHijoIzq()->length()>min){
                     cout<<" caso 3 "<<endl;
                   NodeB<T>* PadreNodo=list_padre->rove(posPadre-1)->get_data();
                    temp->delete_Pos(pos);
                   this->BorrarCaso3(temp,pos,PadreNodo);
                   // Setear padre a la lista derecha
                    for(int i=1; i<=temp->length();i++){
                        temp->rove(i)->get_data()->setPadre(list_padre->rove(posPadre)->get_data());
                    }
               }
             //Caso 5 que la hermana izquierda y derecha tenga menor o igual al minimo de elementos
             else{
                   cout<<" caso 5 "<<endl;
                 NodeB<T>* PadreNodo=list_padre->rove(posPadre-1)->get_data();
                  temp->delete_Pos(pos);
                 this->BorrarCaso5(temp,pos,PadreNodo);
             }

             }
          ////Caso 4 en que la lista sucesor tenga mayor elementos que el minimo

          else{

              listaArbol<NodeB<T>*>* list_sucesor=this->sucesorInorden(temp->rove(pos)->get_data()->getlistHijoDer());
              NodeB<T>* PadreNodo=temp->rove(pos)->get_data()->getPadre();

                  cout<<" caso 4 "<<endl;
                  NodeB<T>* Nodo=temp->rove(pos)->get_data();
                   temp->delete_Pos(pos);
                this->BorrarCaso4(temp,pos,list_sucesor,Nodo);


                 temp->rove(pos)->get_data()->setPadre(PadreNodo);
               if(list_sucesor->length()<min){//Si la lista sucesor que se le retiro un elemento tenga menos del minimo de elementos

                 this->borrarAux(list_sucesor);
               }


          }
     }


     else{
         cout<<" El dato no se encuentra"<<endl;
     }

}

template<typename T>
/**
 * @brief ArbolB::borrarAux: metodo de borrar auxiliar,cuando despues de borrar un elemento
 * esta lista rompe una regla del arbol
 * @param temp: lista donde se rompio la regla
 */
void ArbolB<T>::borrarAux(listaArbol<NodeB<T> *> *temp)
{



        ///Caso 1,2 y 3 en  que no tenga hijos

             listaArbol<NodeB<T>*>* list_padre=this->buscarLista(temp->rove(1)->get_data()->getPadre()->get_data());
             int posPadre=this->buscarPos(list_padre,temp->rove(1)->get_data()->getPadre()->get_data());

              if(list_padre->rove(posPadre)->get_data()->getlistHijoIzq()==temp){
                  if(list_padre->rove(posPadre)->get_data()->getlistHijoDer()->length()>min){
                      cout<<" caso 2 Aux hermana derecha con elementos"<<endl;

                     NodeB<T>* PadreNodo=temp->rove(1)->get_data()->getPadre();

                     this->BorrarCaso2(temp,1,PadreNodo);

                  }
                  else{
                      cout<<" caso 6.1 Aux "<<endl;
                      NodeB<T>* PadreNodo=list_padre->rove(posPadre)->get_data();
                       listaArbol<NodeB<T>*>* list_hermana= PadreNodo->getlistHijoDer();

                      this->BorrarCaso6(temp,PadreNodo,list_hermana);

                       if(list_padre->length()<min){

                           this->borrarAux(list_padre);
                       }

                  }

             }
              else{
                  if(list_padre->rove(posPadre)->get_data()->getlistHijoIzq()->length()>min){
                      cout<<" caso 3 Aux hermana izquierda con elementos"<<endl;

                     NodeB<T>* PadreNodo=temp->rove(1)->get_data()->getPadre();

                     this->BorrarCaso3(temp,1,PadreNodo);
                  }
                  else{

                          cout<<" caso 6.2  Aux"<<endl;
                          NodeB<T>* PadreNodo=list_padre->rove(posPadre)->get_data();
                           listaArbol<NodeB<T>*>* list_hermana= PadreNodo->getlistHijoIzq();
                          this->BorrarCaso6(temp,PadreNodo,list_hermana);

                           if(list_padre==raiz){
                               raiz=list_hermana;
                           }
                           if(list_hermana->length()<min){
                               this->borrarAux(list_hermana);
                           }


                  }

              }

//           else if(list_padre->rove(posPadre)->get_data()->getlistHijoIzq()->length()>min){
//                cout<<" caso 6 "<<endl;
//                NodeB<T>* PadreNodo=list_padre->rove(posPadre)->get_data();
//                 temp->delete_Pos(pos);
//                this->BorrarCaso6(temp,pos,PadreNodo);

//            }


}


template<typename T>
/**
 * @brief ArbolB<T>::ordenar:Ordena la lista de menor a mayor
 * @param temp: lista a ordenar
 */
void ArbolB<T>::ordenar(listaArbol<NodeB<T> *> *listtemp)
{

     Node<NodeB<T>*> *temp=listtemp->get_head();
     Node<NodeB<T>*> *swaptemp;



         while(temp->get_next()!=NULL){
             swaptemp=temp->get_next();
             if(temp->get_data()->get_data() >swaptemp->get_data()->get_data()){

                 listtemp->swap(temp,swaptemp);
                 temp=listtemp->get_head();
                 swaptemp=temp->get_next();
             }
             else{
                 temp=temp->get_next();


             }

         }
}


template<typename T>
/**
 * @brief ArbolB<T>::printTree
 * @param temp
 */

void ArbolB<T>::printTree(){
hojaActual=raiz;
this->printAux(hojaActual);

}

template<typename T>
/**
 * @brief ArbolB<T>::printAux :recorre el arbol recursivamente
 * @param temp: lista actual en que se encuentra el puntero
 */
void ArbolB<T>::printAux(listaArbol<NodeB<T> *> *temp)

{







    if(temp!=NULL){

         cout<<"################"<<endl;
        for(int i=1;i<=temp->length();i++){
           if(i==1){
            printAux(temp->rove(i)->get_data()->getlistHijoIzq());
           }

            if(temp->rove(i)->get_data()->getlistHijoDer()==NULL){
                cout<<temp->rove(i)->get_data()->get_data()<<endl;
            }
           printAux(temp->rove(i)->get_data()->getlistHijoDer());

        }
        if(temp->rove(1)->get_data()->getPadre()!=NULL){
             cout<<"  "<<temp->rove(1)->get_data()->getPadre()->get_data()<<endl;
        }


}

}


template<typename T>
/**
 * @brief ArbolB<T>::CambiarHijos: Cambiar los hijos de la lista con los de la par
 * @param temp: lista que intercambiara los hijos izquierdos y derechos
 * @param newNodo: Nodo del nuevo dato
 */
void ArbolB<T>::CambiarHijos( listaArbol<NodeB<T>*>*  temp,NodeB<T>* newNodo)
{
    ///Cambiar hijos
  int i=1;
    while(temp->rove(i+1)!=NULL && temp->rove(i)->get_data()->get_data()!=newNodo->get_data() && i<=orden){// mueve el indice hasta obtener el dato en (i)
        i+=1;
    }
    if(  temp->rove(i)->get_prev()!=NULL){//Cambiar los hijos izquierdos

        NodeB<T>* aux=temp->rove(i)->get_prev()->get_data();
        aux->setListHijoDer(  temp->rove(i)->get_data()->getlistHijoIzq());
    }
    if(  temp->rove(i)->get_next()!=NULL){//Cambiar los hijos derechos

         NodeB<T>* aux=temp->rove(i)->get_next()->get_data();
         aux->setListHijoIzq(  temp->rove(i)->get_data()->getlistHijoDer());
    }
    ///Cambio de hijos finalizado
}
template<typename T>
/**
 * @brief ArbolB<T>::BorrarCaso2: Metodo de borrar en caso de que el elemento a borrar esta en una lista que
 * es menor al minimo de elementos y le hermana  @derecha@ esta en una lista mayor al minimo de elementos
 * @param temp: lista donde se encuentra el dato a borrar
 */
void ArbolB<T>::BorrarCaso2(listaArbol<NodeB<T> *> *temp,int pos,NodeB<T>* PadreNodo)
{
    listaArbol<NodeB<T>*>* list_hermana= PadreNodo->getlistHijoDer();

    listaArbol<NodeB<T>*>* list_padre=this->buscarLista( PadreNodo->get_data());

     NodeB<T>* SisterNodo=list_hermana->rove(1)->get_data();
     listaArbol<NodeB<T>*>* listIzqSisterNodo=SisterNodo->getlistHijoIzq();
    list_hermana->delete_Pos(this->buscarPos(list_hermana,list_hermana->rove(1)->get_data()->get_data()));

    SisterNodo->setListHijoDer(list_hermana);//Setear la lista derecha en donde esta el nodo hermana
    SisterNodo->setListHijoIzq(temp);//Setear la lista izquierda donde se esta eliminando el dato

    PadreNodo->newListHijoDer();//Borrar las lista derecha del padre
    PadreNodo->newListHijoIzq();//Borrar la lista izquierda del padre

    list_padre->delete_Pos(this->buscarPos(list_padre,PadreNodo->get_data()));


    temp->insert_tail(PadreNodo);
    this->ordenar(temp);
    // Setear padre a la lista derecha
    for(int i=1; i<=list_hermana->length();i++){
        list_hermana->rove(i)->get_data()->setPadre(SisterNodo);
    }
   // Setear padre a la lista izquierda
    for(int i=1; i<=temp->length();i++){
        temp->rove(i)->get_data()->setPadre(SisterNodo);
    }

     list_padre->insert_tail(SisterNodo);//INSERTAR el nodo hermana a la lista del padre
     this->ordenar(list_padre);

      ///Cambiar hijos
    this->CambiarHijos(list_padre,SisterNodo);
     ///Cambio de hijos finalizado

     int posNodo=this->buscarPos(temp,PadreNodo->get_data());
      ///Setear hijos
       if(temp->rove(posNodo-1)->get_data()->getlistHijoIzq()!=NULL){//En caso que los vecinos tengan hijos
             listaArbol<NodeB<T>*>*  listaArbolTempIzq= temp->rove(posNodo-1)->get_data()->getlistHijoDer();
             for(int i=1; i<=listaArbolTempIzq->length();i++){

               listaArbolTempIzq->rove(i)->get_data()->setPadre(temp->rove(posNodo)->get_data());

             }
             temp->rove(posNodo)->get_data()->setListHijoIzq(listaArbolTempIzq);


                 listaArbol<NodeB<T>*>*  listaArbolTempDer=  listIzqSisterNodo;
                 for(int i=1; i<=listaArbolTempDer->length();i++){

                   listaArbolTempDer->rove(i)->get_data()->setPadre(temp->rove(posNodo)->get_data());

                 }
                temp->rove(posNodo)->get_data()->setListHijoDer(listaArbolTempDer);

       }
}
template<typename T>
/**
 * @brief ArbolB<T>::BorrarCaso2: Metodo de borrar en caso de que el elemento a borrar esta en una lista que
 * es menor al minimo de elementos y le hermana @izquierda@ esta en una lista mayor al minimo de elementos
 * @param temp: lista donde se encuentra el dato a borrar
 */
void ArbolB<T>::BorrarCaso3(listaArbol<NodeB<T> *> *temp,int pos,NodeB<T>* PadreNodo)
{
    listaArbol<NodeB<T>*>* list_hermana= PadreNodo->getlistHijoIzq();

    listaArbol<NodeB<T>*>* list_padre=this->buscarLista( PadreNodo->get_data());

     NodeB<T>* SisterNodo=list_hermana->rove(list_hermana->length())->get_data();
       listaArbol<NodeB<T>*>* listDerSisterNodo=SisterNodo->getlistHijoDer();
    list_hermana->delete_Pos(this->buscarPos(list_hermana,list_hermana->rove(list_hermana->length())->get_data()->get_data()));

    SisterNodo->setListHijoDer(temp);//Setear la lista derecha donde se esta eliminando el dato
    SisterNodo->setListHijoIzq(list_hermana);//Setear la lista izquierda en donde esta el nodo hermana

    PadreNodo->newListHijoDer();//Borrar las lista derecha del padre
    PadreNodo->newListHijoIzq();//Borrar la lista izquierda del padre

    list_padre->delete_Pos(this->buscarPos(list_padre,PadreNodo->get_data()));


    temp->insert_tail(PadreNodo);
    this->ordenar(temp);
    // Setear padre a la lista izquierda
    for(int i=1; i<=list_hermana->length();i++){
        list_hermana->rove(i)->get_data()->setPadre(SisterNodo);
    }


     list_padre->insert_tail(SisterNodo);//INSERTAR el nodo hermana a la lista del padre
     this->ordenar(list_padre);

      ///Cambiar hijos
    this->CambiarHijos(list_padre,SisterNodo);
     ///Cambio de hijos finalizado

     int posNodo=1;
      ///Setear hijos
       if(temp->rove(posNodo+1)->get_data()->getlistHijoIzq()!=NULL){//En caso que los vecinos tengan hijos
             listaArbol<NodeB<T>*>*  listaArbolTempDer= temp->rove(posNodo+1)->get_data()->getlistHijoIzq();
             for(int i=1; i<=listaArbolTempDer->length();i++){

               listaArbolTempDer->rove(i)->get_data()->setPadre(temp->rove(posNodo)->get_data());

             }
             temp->rove(posNodo)->get_data()->setListHijoDer(listaArbolTempDer);


                 listaArbol<NodeB<T>*>*  listaArbolTempIzq=  listDerSisterNodo;
                 for(int i=1; i<=listaArbolTempIzq->length();i++){

                   listaArbolTempIzq->rove(i)->get_data()->setPadre(temp->rove(posNodo)->get_data());

                 }
                temp->rove(posNodo)->get_data()->setListHijoIzq(listaArbolTempIzq);

       }

}
template<typename T>
/**
 * @brief ArbolB::BorrarCaso4: Caso en que el elemento a eliminar tenga hijos y
 * la lista sucesor tenga mayor elementos que el minimo
 * @param temp: lista en que se encuentra ele elemento a eliminar
 * @param pos: posicion en que se encuentre el elemento a eliminar
 * @param list_sucesor: lista en que se encuentra el sucesor
 */
void ArbolB<T>::BorrarCaso4(listaArbol<NodeB<T> *> *temp, int pos, listaArbol<NodeB<T> *> *list_sucesor, NodeB<T> *PadreNodo)
{


     NodeB<T>* SucesorNodo=list_sucesor->rove(1)->get_data();

    list_sucesor->delete_Pos(1);

    SucesorNodo->setListHijoDer(PadreNodo->getlistHijoDer());//Setear la lista derecha al sucesor
    SucesorNodo->setListHijoIzq(PadreNodo->getlistHijoIzq());//Setear la lista izquierda al sucesor

    PadreNodo->newListHijoDer();//Borrar las lista derecha del padre
    PadreNodo->newListHijoIzq();//Borrar la lista izquierda del padre]


    // Setear padre a la lista derecha
    for(int i=1; i<=SucesorNodo->getlistHijoDer()->length();i++){
        if(temp->length()>=1){
             SucesorNodo->getlistHijoDer()->rove(i)->get_data()->setPadre(temp->rove(1)->get_data());
        }
        else{
            SucesorNodo->getlistHijoDer()->rove(i)->get_data()->setPadre(SucesorNodo);
        }

    }

   // Setear padre a la lista izquierda
    for(int i=1; i<=SucesorNodo->getlistHijoIzq()->length();i++){
        SucesorNodo->getlistHijoIzq()->rove(i)->get_data()->setPadre(SucesorNodo);
    }

    temp->insert_tail(SucesorNodo);
    this->ordenar(temp);
    ///Cambiar hijos
  this->CambiarHijos(temp,SucesorNodo);
   ///Cambio de hijos finalizado



}
template<typename T>
/**
 * @brief ArbolB::BorrarCaso5: Caso en que el elemento a borrar no tenga hermanos izquierdas y derechas mayores al
 * minimo de elementos
 * @param temp: lista en donde se encuentra el elemento a borrar
 * @param pos:posicion donde se encuetra el elemento a borrar
 * @param PadreNodo: padre del nodo  eliminar
 */
void ArbolB<T>::BorrarCaso5(listaArbol<NodeB<T> *> *temp, int pos, NodeB<T> *PadreNodo)
{
    listaArbol<NodeB<T>*>* list_hermana= PadreNodo->getlistHijoIzq();

    listaArbol<NodeB<T>*>* list_padre=this->buscarLista( PadreNodo->get_data());



    PadreNodo->newListHijoDer();//Borrar las lista derecha del padre
    PadreNodo->newListHijoIzq();//Borrar la lista izquierda del padre
    int posNext=this->buscarPos(list_padre,PadreNodo->get_data())+1;
    list_padre->delete_Pos(this->buscarPos(list_padre,PadreNodo->get_data()));

    list_hermana->insert_tail(temp->rove(1)->get_data());
    list_hermana->insert_tail(PadreNodo);
    temp->rove(1)->get_data()->getPadre()->setListHijoIzq(list_hermana);
    this->ordenar(list_hermana);
    // Setear padre a la lista izquierda

    for(int i=1; i<=list_hermana->length();i++){
        list_hermana->rove(i)->get_data()->setPadre(temp->rove(1)->get_data()->getPadre());
    }



}


template<typename T>
/**
 * @brief ArbolB<T>::BorrarCaso6:Caso en que el elemento a borrar, no tenga hermana izquierda y
 * la hermana derecha no tenga mayor de elementos que el minimo
 * @param temp: lista donde se encuentra el elemento a borrar
 * @param pos: posicion donde sen encuentra el elemento a borrar
 * @param PadreNodo: padre del elemento a borrar
 */
void ArbolB<T>::BorrarCaso6(listaArbol<NodeB<T> *> *temp, NodeB<T> *PadreNodo,listaArbol<NodeB<T>*>* list_hermana)
{


    listaArbol<NodeB<T>*>* list_padre=this->buscarLista( PadreNodo->get_data());

    PadreNodo->newListHijoDer();//Borrar las lista derecha del padre
    PadreNodo->newListHijoIzq();//Borrar la lista izquierda del padre

    list_padre->delete_Pos(this->buscarPos(list_padre,PadreNodo->get_data()));




    for(int i=1;i<=temp->length();i++){//Inserta toda la lista de temp
        list_hermana->insert_tail(temp->rove(i)->get_data());
    }

    list_hermana->insert_tail(PadreNodo);
    this->ordenar(list_hermana);

    // Setear padre a la lista derecha

    for(int i=1; i<=list_hermana->length();i++){
        if(list_padre->length()>=1){
        list_hermana->rove(i)->get_data()->setPadre(list_padre->rove(1)->get_data());
        }else{
            list_hermana->rove(i)->get_data()->setPadre(NULL);
        }
    }

        int posNodo=this->buscarPos(list_hermana,PadreNodo->get_data());
         ///Setear hijos
          if(list_hermana->rove(posNodo+1)->get_data()->getlistHijoDer()!=NULL){//En caso que los vecinos tengan hijos
                listaArbol<NodeB<T>*>*  listaArbolTempDer= list_hermana->rove(posNodo+1)->get_data()->getlistHijoIzq();
                list_hermana->rove(posNodo)->get_data()->setListHijoDer(listaArbolTempDer);

                if(posNodo>1){
                    listaArbol<NodeB<T>*>*  listaArbolTempIzq=  list_hermana->rove(posNodo-1)->get_data()->getlistHijoDer();
                    for(int i=1; i<=listaArbolTempIzq->length();i++){

                      listaArbolTempIzq->rove(i)->get_data()->setPadre(list_hermana->rove(posNodo)->get_data());

                    }
                   list_hermana->rove(posNodo)->get_data()->setListHijoIzq(listaArbolTempIzq);
               }
          }


}

template<typename T>

listaArbol<NodeB<T>*>* ArbolB<T>::buscarLista(T dato){

    listaArbol<NodeB<T>*>* temp;
    temp=raiz;
    int i;
    while(temp!=NULL){
         i=1;
    while(temp->rove(i+1)!=NULL && temp->rove(i)->get_data()->get_data()<dato && i<orden){// mueve el indice hasta obtener el dato en (i)  que es mayor que el dato ingresado
        i+=1;
    }
    if(temp->rove(i)->get_data()->get_data()==dato){
        return temp;
    }
    else if(temp->rove(i)->get_data()->get_data()<dato){
        temp=temp->rove(i)->get_data()->getlistHijoDer();

    }
    else {
        temp=temp->rove(i)->get_data()->getlistHijoIzq();

    }


   }
    return temp;
}
template<typename T>
/**
 * @brief ArbolB<T>::sucesorInorden: busca la lista que tenga el menor elemento de los mayores
 * @param temp: lista en donde se empieza a buscar
 * @return : lista que contenga el elemento menor de los mayores
 */
listaArbol<NodeB<T> *> *ArbolB<T>::sucesorInorden(listaArbol<NodeB<T> *> *temp)
{
  while(true){
      if(temp->rove(1)->get_data()->getlistHijoIzq()==NULL){
          break;
      }
      temp = temp->rove(1)->get_data()->getlistHijoIzq();

  }
  return temp;
}
template<typename T>
/**
 * @brief ArbolB::buscarPos: Busca la posicion en que se encuentra el dato en una listaArbol
 * @param pList: listaArbol en que se encuentra el dato
 * @param pData: dato averiguar la posicion en la lista
 * @return: posicion del dato
 *
 */
int ArbolB<T>::buscarPos(listaArbol<NodeB<T> *> *pList, T pData)
{
    int pos=0;
for(int i=1; i<=pList->length();i++){
    if(pList->rove(i)->get_data()->get_data()==pData){
        pos=i;
        break;
    }

}
return pos;
}


template<typename T>
/**
 * @brief ArbolB<T>::setearHijos: setea los hijos izquierdo y derechos a la lista temp
 * @param temp: lista que se le seteara lis hijos
 * @return : lista con los hijos seteados
 */
listaArbol<NodeB<T> *> *ArbolB<T>::setearHijos(listaArbol<NodeB<T> *> *temp)
{
    listaArbol<NodeB<T>*>*  listaArbolTempIzq= new listaArbol<NodeB<T>*>();


      for(int i=1; i<=orden/2;i++){
          listaArbolTempIzq->insert_tail(hojaActual->rove(i)->get_data());
          listaArbolTempIzq->get_tail()->get_data()->setPadre(temp->get_tail()->get_data());

      }
      listaArbol<NodeB<T>*>*  listaArbolTempDer= new listaArbol<NodeB<T>*>();

      for(int i=(orden/2)+1; i<=orden;i++){
          listaArbolTempDer->insert_tail(hojaActual->rove(i)->get_data());
          listaArbolTempDer->get_tail()->get_data()->setPadre(temp->get_tail()->get_data());
      }
///Setear hijos
      temp->get_tail()->get_data()->setListHijoIzq(listaArbolTempIzq);
      temp->get_tail()->get_data()->setListHijoDer(listaArbolTempDer);
      return temp;
}



template<typename T>
/**
 * @brief ArbolB<T>::get_raiz
 * @return: lista raiz del arbol
 */
listaArbol<NodeB<T> *> *ArbolB<T>::get_raiz(){
    return this->raiz;
}


template<typename T>
/**
 * @brief ArbolB::getOrden
 * @return: orden del maximo de item que aguanta una lista del arbol
 */
int ArbolB<T>::getOrden()
{
  return this->orden;
}




/**
 * @brief arbolB<T>::~arbolB
 * destructor
 */
template<typename T>
ArbolB<T>::~ArbolB(){
    delete this;
}


#endif // ARBOLB_H
