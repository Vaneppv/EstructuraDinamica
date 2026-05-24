#include <iostream>

using namespace std;

// 1. Plantilla para el Tipo de Dato Nodo
template <typename T>
class Node {
private:
    T dato;
    Node<T>* nextNode;

public:
    Node(T a, Node<T>* b = nullptr) {
        dato = a;
        nextNode = b;
    }
    ~Node() {}

    void setDato(T a) { dato = a; }
    void setNextNode(Node<T>* next) { nextNode = next; }
    
    T getDato() { return dato; }
    Node<T>* getNextNode() { return nextNode; }
};

// 2. Clase Lista que gestiona la cadena de nodos
template <typename T>
class Lista {
private:
    Node<T>* head; 
public:
    Lista() {
        head = nullptr;
    }
    ~Lista() {}

    Node<T>* getHead() {
        return head;
    }

    void setHead(Node<T>* primerNodo) {
        this->head = primerNodo;
    }

    Node<T>* conectarNodo(Node<T>* deLista, Node<T>* suelto) {
        if (head == nullptr) {
            head = deLista;
        }
        if (deLista == nullptr) {
            deLista->setNextNode(suelto);
            return head;
        }

        Node<T>* temp = deLista;

        while (temp->getNextNode() != nullptr) {
            temp = temp->getNextNode();
        }
        temp->setNextNode(suelto);

        return head;
    }
};

int main() {
    Lista<int> miLista;

    Node<int>* nodo1 = new Node<int>(10);
    Node<int>* nodo2 = new Node<int>(20);
    Node<int>* nodo3 = new Node<int>(30); 
    
    
    miLista.setHead(nodo1);
    nodo1->setNextNode(nodo2);

    cout << "Direccion original del Head: " << miLista.getHead() << " (Valor: " << miLista.getHead()->getDato() << ")" << endl;

    Node<int>* elHead = miLista.conectarNodo(nodo2, nodo3);

    cout << "Direccion devuelta por la funcion: " << elHead << " (Valor: " << elHead->getDato() << ")" << endl;
    
    Node<int>* actual = elHead;
    cout << "Trayecto de la lista: ";
    while(actual != nullptr) {
        cout << actual->getDato() << " -> ";
        actual = actual->getNextNode();
    }
    cout << "NULL" << endl;

    delete nodo1;
    delete nodo2;
    delete nodo3;

    return 0;
}

