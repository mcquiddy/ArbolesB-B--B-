#include "ArbolB.h"
#include <QApplication>
#include <linked_listTree.h>

int main(int argc, char *argv[])
{
 QApplication a(argc, argv);






    ArbolB<int> * arbol= new ArbolB<int>(4);

arbol->insert(190);
arbol->insert(57);
arbol->insert(89);
arbol->insert(90);
arbol->insert(121);


arbol->insert(170);

arbol->insert(35);




arbol->insert(48);

arbol->insert(91);

 //arbol->insert(22);
 /*
arbol->insert(126);
arbol->insert(132);
arbol->insert(80);
*/

  //  arbol->insert(89);
 //  arbol->insert(90);
//    arbol->insert(150);
//    arbol->insert(60);
//    arbol->insert(160);
//    arbol->insert(80);
//    arbol->insert(200);
//    arbol->insert(1);

arbol->hojaActual=arbol->get_raiz();

/*
for(int i=1;i<=arbol->hojaActual->length();i++){
   cout<< arbol->hojaActual->rove(i)->get_data()->get_data()<<endl;
}
*/

   for(int i=1;i<=arbol->hojaActual->length();i++){

       if(arbol->hojaActual->rove(i)->get_data()->getlistHijoIzq()!=NULL){
       for(int j=1;j<=arbol->hojaActual->rove(i)->get_data()->getlistHijoIzq()->length();j++){
            cout<<" "<<arbol->hojaActual->rove(i)->get_data()->getlistHijoIzq()->rove(j)->get_data()->get_data()<<endl;

       }

       }
         cout<<arbol->hojaActual->rove(i)->get_data()->get_data()<<endl;

       if(arbol->hojaActual->rove(i)->get_data()->getlistHijoDer()!=NULL){
           for(int j=1;j<=arbol->hojaActual->rove(i)->get_data()->getlistHijoDer()->length();j++){
                cout<<" "<<arbol->hojaActual->rove(i)->get_data()->getlistHijoDer()->rove(j)->get_data()->get_data()<<endl;
           }
       }
   }




  //  arbol->printTree(arbol->get_raiz()->get_head()->get_data()->getlistHijoIzq(),arbol->get_raiz()->get_head(),arbol->get_raiz()->get_head()->get_data()->getlistHijoDer());
  //  arbol->insert(121);



  //arbol->insert(170);

//    arbol->insert(35);
//    arbol->insert(48);
//    arbol->insert(91);
//    arbol->insert(22);
//    arbol->insert(126);
//    arbol->insert(132);
//    arbol->insert(80);

    //arbol->printTree(arbol->get_raiz());







    return 0;
}
