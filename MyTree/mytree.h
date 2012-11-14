//Template Arboles Multirama
//Juan Carlos Ruiz González
//Universidad de Guanajauto

#include <iostream>
#include <vector>
#include <queue>
#include <list>


using namespace std;

template<class U>
class node
{
public:
    //constructor
    node(U dat,node<U> *p=NULL):data(dat),parent(p){childs.clear();}

    //atributos del Nodo
    U data; //sera una estructura vertex,cost para el caso del A*
    node<U> *parent; //Nodo al padre
    vector<node<U>*> childs; //Vector de nodos hijos
};


template<class T>
class mytree
{

private:

    queue< node<T>*> q; //Cola utilizada para la inserción
    node<T> *root;
    node<T> *actual;

public:
    mytree():root(NULL),actual(NULL){}
    ~mytree(){} //pendiente
    node<T> *initTree(T data); //inicializa el arbol con su nodo Root
    vector<node<T> *> insert(node<T> *ref,vector<T> data, int size); //inserta el grupo de nodos en la posición indicada
    void verbose(); //imprime el arbol en anchura

    list<T> backtracking(); //devuelve una lista desde el nodo donde nos encontramos hasta el root
    node<T> * back(); //vuelve de la posición actual a la posición anterior
    node<T> *getRoot(); //devuelve la raiz del arbol

};


template <class T>
node<T>* mytree<T>::initTree(T data)
{
    if(root==NULL)
    {
        node<T> *newNode=new node<T>(data);        
        root=newNode;
        actual=root;

    }
    else
    {
        cout<<"El arbol ya esta inicializado, imposible realizar operación"<<endl;
    }

    return actual;
}


template <class T>
vector<node<T> *> mytree<T>::insert(node<T> *ref,vector<T> data, int size)
{
    vector<node<T>* > myExpand;
    actual=ref;


    for(int i=0;i<size;i++)
    {
        node<T> *newNode=new node<T>(data.at(i));
        newNode->parent=actual; //creando relacíon al padre
        actual->childs.push_back(newNode); //creando relación del padre al hijo
        myExpand.push_back(newNode);
    }

    return myExpand;

}


template <class T>
list<T> mytree<T>::backtracking()
{
    list<T> backT;


    while(actual!=root)
    {
        backT.push_back(actual->data);
        actual=actual->parent;
    }

    backT.push_back(actual->data); //inseción del root a la lista

    return backT;
}


template <class T>
node<T> *mytree<T>::back()
{
    actual=actual->parent;

    return actual;
}



template <class T>
void mytree<T>::verbose()
{

    queue< node<T>*> auxQ; //pila auxiliar para el recorrido del arbol
    node<T> *aux;

    aux=root;
    auxQ.push(aux);


    while(!auxQ.empty())
    {
        aux=auxQ.front();
        cout<<aux->data; //impresión del nodo
        auxQ.pop();
        for(unsigned int i=0;i<aux->childs.size();i++)
        {
            auxQ.push(aux->childs.at(i));
        }

        cout<<endl;

    }    

}


template <class T>
node<T>* mytree<T>::getRoot()
{
    return root;
}
