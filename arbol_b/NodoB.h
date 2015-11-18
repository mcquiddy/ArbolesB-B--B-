/*
 * nodo.h
 *
 *  Created on: Jul 29, 2015
 *      Author: santii
 */

#ifndef NODOB_H_
#define NODOB_H_
#include "linked_listTree.h"
template <typename T>
class NodeB {
private:
    NodeB<T>* next_node;
    NodeB<T>* prev_node;
      NodeB<T>* padre;
    T data;
    listaArbol<NodeB<T>*> * listHijoIzq=0;
    listaArbol<NodeB<T>*> * listHijoDer=0;
     listaArbol<NodeB<T>*> * listaAux=0;

public:
    NodeB(T dato) ;
    T get_data();
      NodeB<T> *getPadre();
     void setPadre(NodeB<T> * pPadre);
    listaArbol<NodeB<T>*> *getlistHijoIzq();

    listaArbol<NodeB<T> *> *getlistHijoDer();
    void set_next(NodeB* next_node);
    void set_prev(NodeB* prev_node);
    NodeB* get_next();
    NodeB* get_prev();
    void setListHijoIzq(listaArbol<NodeB<T> *> *value);
     void setListHijoDer(listaArbol<NodeB<T> *> *value);
     void newListHijoIzq();

     void newListHijoDer();


};
/**
 * Constructor of a Node
 * Setting nex_node and prev_node as 0 or NULL
 */
template<typename T>


NodeB<T>::NodeB(T dato){
    this->data=dato;
    this->next_node=0;
    this->prev_node=0;
    this->padre=0;
    this->listHijoIzq= 0;
    this->listHijoDer= 0;

}
/**
 * Getters and setters
 */
template<typename T>
/**
 * @brief Node<T>::get_next
 * @return
 */
NodeB<T>* NodeB<T>::get_next(){
    return this->next_node;
}
template<typename T>
/**
 * @brief Node<T>::get_prev
 * @return
 */
NodeB<T>* NodeB<T>::get_prev(){
    return this->prev_node;
}
template<typename T>
void NodeB<T>::set_next(NodeB<T>* new_next_node){
    this->next_node=new_next_node;
}
template<typename T>
void NodeB<T>::set_prev(NodeB<T>* new_prev_node){
    this->prev_node=new_prev_node;
}
template<typename T>
T NodeB<T>::get_data(){
    return this->data;
}
template<typename T>
/**
 * @brief NodeB::getPadre
 * @return
 */
 NodeB<T>*  NodeB<T>::getPadre()
{
return this->padre;
}
template<typename T>
/**
 * @brief NodeB::setPadre
 * @param pPadre
 */
void NodeB<T>::setPadre( NodeB<T> * pPadre)
{
    this->padre=pPadre;
}

template<typename T>
listaArbol<NodeB<T>*> *NodeB<T>::getlistHijoIzq()
{
    return this->listHijoIzq;
}

template<typename T>
listaArbol<NodeB<T>*> *NodeB<T>::getlistHijoDer()
{
    return this->listHijoDer;
}
template<typename T>
void NodeB<T>::setListHijoIzq(listaArbol<NodeB<T> *> *value)
{
    this->listHijoIzq = value;
}
template<typename T>
void NodeB<T>::setListHijoDer(listaArbol<NodeB<T> *> *value)
{
    this->listHijoDer= value;
}

template<typename T>
void NodeB<T>::newListHijoIzq()
{
    this->listHijoIzq = 0;
}
template<typename T>
void NodeB<T>::newListHijoDer()
{
    this->listHijoDer= 0;
}




#endif // NODOB_H
