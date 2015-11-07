#include "ArbolB.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ArbolB<int> * arbol= new ArbolB<int>(4);
    arbol->insert(2);
    arbol->insert(3);
    arbol->insert(1);
    arbol->insert(5);
    arbol->insert(6);
    for(int i=1; i<=arbol->get_raiz()->length();i++){
   cout<< arbol->get_raiz()->rove(i)->get_data()->get_data()<<endl;
    }

    return a.exec();
}
