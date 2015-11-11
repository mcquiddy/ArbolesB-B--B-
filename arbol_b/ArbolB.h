#ifndef ARBOLB_H
#define ARBOLB_H

#include <iostream>
#include "NodoB.h"

using namespace std;

template<typename T>
class ArbolB {
//private:
public:
    int orden;
    listaArbol<NodeB<T>*>* hojaActual ;
      listaArbol<NodeB<T>*>* raiz;
      
//public:
    void insert(T new_data);
    void insertAux() ;
    void ordenar(listaArbol<NodeB<T>*>* listtemp);
    void printTree(listaArbol<NodeB<T> *>* LIzq,Node<NodeB<T> *>* Praiz,listaArbol<NodeB<T> *>* LDer);
    listaArbol<NodeB<T>*>* buscarLista(T dato);

    listaArbol<NodeB<T>*>* get_raiz();

    int getOrden();
    void prueba();

    ArbolB(int pOrden);
    virtual ~ArbolB();

};

template<typename T>
/**
 * @brief ArbolB<T>::ArbolB
 */
ArbolB<T>::ArbolB(int pOrden){


    hojaActual=new listaArbol<NodeB<T>*>();
     raiz=new listaArbol<NodeB<T>*>();
    orden=pOrden;

}

template<typename T>
/**
 * @brief ArbolB<T>::insert
 * @param new_data
 */
void ArbolB<T>::insert(  T new_data ){
    int i=1;

    if(hojaActual->rove(1)==NULL){
         NodeB<T>* newNodo= new NodeB<T>(new_data);//condicion se usa para a;adir el primer nodo arbol a cada hoja
       hojaActual->insert_tail(newNodo);
       raiz=hojaActual;

       return;
    }
    else if(hojaActual->rove(i)->get_data()->get_data()==new_data){//en caso que el dato se encuentre, no se toma en cuenta

        return;
    }
    else{
           while(hojaActual->rove(i)!=NULL && hojaActual->rove(i)->get_data()->get_data()<new_data && i<=orden){// mueve el indice hasta obtener el dato en (i)  que es mayor que el dato ingresado
               i+=1;
           }
           if(i==orden && hojaActual->rove(i-1)->get_data()->get_next()!= NULL && hojaActual->rove(i)->get_data()->get_data()<new_data){//maneja el node del extremo derecho
               if(hojaActual->rove(i)->get_data()->getlistHijoDer()!= NULL){
                   hojaActual=hojaActual->rove(i)->get_data()->getlistHijoDer();
                   insert(new_data);
               }
               else{
                   NodeB<T>* newNodo= new NodeB<T>(new_data);
                   hojaActual->setPos(i+1,newNodo);
                   cout<<":P"<<endl;
                   insertAux();
               }
           }
           else if(hojaActual->rove(i)!=NULL &&  hojaActual->rove(i)->get_data()->getlistHijoIzq()!= NULL){//maneja los nodos que tiene hijos
               hojaActual=hojaActual->rove(i)->get_data()->getlistHijoIzq();
               insert(new_data);
           }
           else if(hojaActual->rove(i)==NULL && hojaActual->rove(i-1)->get_data()->getlistHijoDer()!= NULL){
               hojaActual=hojaActual->rove(i-1)->get_data()->getlistHijoDer();
               insert(new_data);
           }


           else{
               NodeB<T>* newNodo= new NodeB<T>(new_data);
               hojaActual->setPos(i,newNodo);
               if(hojaActual->rove(1)->get_data()->get_data()>new_data){
                   hojaActual->rove(1)->get_data()->setPadre(hojaActual->rove(2)->get_data()->getPadre());
                   hojaActual->rove(2)->get_data()->setPadre(NULL);
                   hojaActual->rove(1)->get_data()->getPadre()->setListHijoIzq(hojaActual);

                   if(hojaActual->length()>orden){
                      insertAux();
                   }
               }

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
     if(hojaActual->rove(1)->get_data()->getPadre()==NULL){

        listaArbol<NodeB<T>*>* listaP= new listaArbol<NodeB<T>*>();
        listaP->insert_head(newNodo);

        listaArbol<NodeB<T>*>*  listaArbolTempIzq= new listaArbol<NodeB<T>*>();

        for(int i=1; i<=orden/2;i++){
            listaArbolTempIzq->insert_tail(hojaActual->rove(i)->get_data());

        }
        listaArbol<NodeB<T>*>*  listaArbolTempDer= new listaArbol<NodeB<T>*>();

        for(int i=(orden/2)+1; i<=orden;i++){
            listaArbolTempDer->insert_tail(hojaActual->rove(i)->get_data());
        }



        listaArbolTempIzq->rove(1)->get_data()->setPadre(listaP->rove(1)->get_data());
        listaArbolTempDer->rove(1)->get_data()->setPadre(listaP->rove(1)->get_data());
        listaP->rove(1)->get_data()->setListHijoIzq(listaArbolTempIzq);
        listaP->rove(1)->get_data()->setListHijoDer(listaArbolTempDer);

        raiz=listaP;
        hojaActual=raiz;
     }
     else{

         listaArbol<NodeB<T>*>*  listaArbolTempIzq= new listaArbol<NodeB<T>*>();

         for(int i=1; i<=orden/2;i++){
             listaArbolTempIzq->insert_tail(hojaActual->rove(i)->get_data());

         }
         listaArbol<NodeB<T>*>*  listaArbolTempDer= new listaArbol<NodeB<T>*>();

         for(int i=(orden/2)+1; i<=orden;i++){
             listaArbolTempDer->insert_tail(hojaActual->rove(i)->get_data());
         }

         newNodo->setListHijoIzq(listaArbolTempIzq);
         newNodo->setListHijoDer(listaArbolTempDer);
         listaArbol<NodeB<T>*>* temp=this->buscarLista(hojaActual->rove(1)->get_data()->getPadre()->get_data());
          int m=1;
         while(temp->rove(m)!=NULL && temp->rove(m)->get_data()->get_data()<newNodo->get_data() && m<=orden){// mueve el indice hasta obtener el dato en (i)  que es mayor que el dato ingresado
             m+=1;
         }

         listaArbolTempIzq->rove(1)->get_data()->setPadre(newNodo);
         listaArbolTempDer->rove(1)->get_data()->setPadre(newNodo);



         temp->setPos(m, newNodo);

         if(newNodo->get_prev()!=NULL){
             newNodo->get_prev()->setListHijoDer(newNodo->getlistHijoIzq());
         }
         if(newNodo->get_next()!=NULL){
             newNodo->get_next()->setListHijoIzq(newNodo->getlistHijoDer());
         }


         if(temp->length()>orden){
             hojaActual=temp;
             insertAux();
         }





     }



}

template<typename T>
/**
 * @brief ArbolB<T>::ordenar
 * @param temp
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

void ArbolB<T>::printTree(listaArbol<NodeB<T> *>* LIzq,Node<NodeB<T>*> * Praiz,listaArbol<NodeB<T> *>* LDer){

//    for(int i=1;i<=raiz->length();i++){
    if(LIzq!=NULL){
        // cout<<"hola"<<Praiz->get_data()->get_data()<<endl;
        printTree(LIzq->get_head()->get_data()->getlistHijoIzq(),LIzq->get_head(),LIzq->get_head()->get_data()->getlistHijoDer());
    }
    cout<<Praiz->get_data()->get_data()<<endl;


    if(Praiz->get_next()!=NULL){
       Node<NodeB<T>*> * temp= Praiz->get_next();
       printTree(temp->get_data()->getlistHijoIzq(),temp,temp->get_data()->getlistHijoDer());
    }
    if(LDer!=NULL){
      printTree(LDer->get_head()->get_data()->getlistHijoIzq(),LDer->get_head(),LDer->get_head()->get_data()->getlistHijoDer());
    }


//}

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
 * @brief ArbolB<T>::get_raiz
 * @return
 */
listaArbol<NodeB<T> *> *ArbolB<T>::get_raiz(){
    return this->raiz;
}
template<typename T>
/**
 * @brief ArbolB::getOrden
 * @return
 */
int ArbolB<T>::getOrden()
{
  return this->orden;
}
template<typename T>
void ArbolB<T>::prueba(){

    hojaActual->print_list();



}



/**
 * @brief arbolB<T>::~arbolB
 */
template<typename T>
ArbolB<T>::~ArbolB(){
    delete this;
}


#endif // ARBOLB_H
