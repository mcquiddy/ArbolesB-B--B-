#include <QCoreApplication>
#include "ArbolB.h"
#include <linked_listTree.h>
#include "iostream"

using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ArbolB<int> * arbol= new ArbolB<int>(4);

    int num=0;
    string l="";
    cout<<" inserte numero : ";
    cin>>num;
    while(true){
        if(num==-5){
            arbol->printTree();
        }

if(num>0){
        arbol->insert(num);

}
if(num==-8){
    cout<<" inserte numero a eliminar : ";
    cin>>num;
    arbol->borrar(num);

}

        cout<<" inserte numero : ";
        cin>>num;

    }

        arbol->printTree();

    return a.exec();
}
