#ifndef ARBOLB_H
#define ARBOLB_H

#include <iostream>
#include "NodoB.h"

using namespace std;

template<typename T>
class ArbolB {
private:
    int orden;
    listaArbol<NodeB<T>*>* raiz;



public:
    void insert(T new_data);
    void ordenar(listaArbol<NodeB<T>*>* listtemp);

    listaArbol<NodeB<T>*>* get_raiz();

    int getOrden();

    ArbolB(int pOrden);
    virtual ~ArbolB();

};

template<typename T>
/**
 * @brief ArbolB<T>::ArbolB
 */
ArbolB<T>::ArbolB(int pOrden){


    raiz=new listaArbol<NodeB<T>*>();
    orden=pOrden;

}
template<typename T>
/**
 * @brief ArbolB<T>::insert
 * @param new_data
 */
void ArbolB<T>::insert(T new_data){
    NodeB<T>* newNodo= new NodeB<T>(new_data);
    if(raiz->length()<orden){
       raiz->insert_tail(newNodo);
       this->ordenar(raiz);


//        listatemp->i

    }
    else{
//        NodeB<T>* temp=this->head;
//        newNode->set_next(temp);
//        temp->set_prev(newNode);
//        this->head=newNode;
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
/**
 * @brief arbolB<T>::~arbolB
 */
ArbolB<T>::~ArbolB(){
    delete this;
}


#endif // ARBOLB_H
