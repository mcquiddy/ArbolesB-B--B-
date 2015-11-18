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
    void ordenar(listaArbol<NodeB<T>*>* listtemp);
    void printTree();
    void printAux(listaArbol<NodeB<T>*>* temp);
    void CambiarHijos(listaArbol<NodeB<T>*>* temp,NodeB<T>* newNodo);

    listaArbol<NodeB<T>*>* buscarLista(T dato);
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
              cout<<" de nuevo " <<endl;

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
     int pos=this->buscarPos(temp,pData);

     if(temp!=NULL){
         ///Caso 1,2 y 3 en  que no tenga hijos
          if(temp->rove(pos)->get_data()->getlistHijoDer()==NULL){
              // Caso 1 tenga mayor o igual al minimo de elementos
             if(temp->length()>min){
                 temp->delete_Pos(pos);
             }
            /// Caso 2 y 3 que tenga menor al minimo de elementos


                 //Caso 2 que la hermana derecha tenga mayor o igual al minimo de elementos
             else if(temp->rove(pos)->get_data()->getPadre()->getlistHijoDer()->length()>min){

                 listaArbol<NodeB<T>*>* list_hermana= temp->rove(pos)->get_data()->getPadre()->getlistHijoDer();

                 listaArbol<NodeB<T>*>* list_padre=this->buscarLista( temp->rove(pos)->get_data()->getPadre()->get_data());

                 NodeB<T>*  SisterNodo= new NodeB<T>(list_hermana->rove(1)->get_data()->get_data());
                 NodeB<T>* PadreNodo=new NodeB<T>(list_padre->rove(this->buscarPos(list_padre,temp->rove(pos)->get_data()->getPadre()->get_data()))->get_data()->get_data());


                 list_hermana->delete_Pos(this->buscarPos(list_hermana,list_hermana->rove(1)->get_data()->get_data()));

                 SisterNodo->setListHijoDer(list_hermana);//Setear la lista derecha en donde esta el nodo hermana
                 SisterNodo->setListHijoIzq(temp);//Setear la lista izquierda donde se esta eliminando el dato

                 PadreNodo->newListHijoDer();//Borrar las lista derecha del padre
                 PadreNodo->newListHijoIzq();//Borrar la lista izquierda del padre

                 list_padre->delete_Pos(this->buscarPos(list_padre,temp->rove(pos)->get_data()->getPadre()->get_data()));
                 temp->delete_Pos(pos);

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

             }


     }

     }
     else{
         cout<<" El dato no se encuentra"<<endl;
     }

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
