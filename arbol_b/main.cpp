#include "ArbolB.h"
#include <QApplication>
#include <linked_listTree.h>

int main(int argc, char *argv[])
{
 QApplication a(argc, argv);






    ArbolB<int> * arbol= new ArbolB<int>(5);

arbol->insert(190);
arbol->insert(57);
arbol->insert(89);
arbol->insert(90);
arbol->insert(121);


arbol->insert(170);

arbol->insert(35);




arbol->insert(48);

arbol->insert(91);

 arbol->insert(22);

arbol->insert(126);
arbol->insert(132);
arbol->insert(80);
arbol->printTree();










    return 0;
}
