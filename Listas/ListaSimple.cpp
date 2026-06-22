#include <iostream>

using namespace std;

// Plantilla para el Tipo de Dato Nodo
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

// Clase Lista que gestiona la cadena de nodos
template <typename T>
class Lista {
private:
    Node<T>* head; 
public:
    Lista() {
        head = nullptr;
    }
    ~Lista() {
        Node<T>* actual = head;
        while (actual != nullptr) {
            Node<T>* siguiente = actual->getNextNode();
            delete actual;
            actual = siguiente;
        }
    }

    Node<T>* getHead() {
        return head;
    }

    void setHead(Node<T>* primerNodo) {
        this->head = primerNodo;
    }

    Node<T>* insertarAlInicio(Node<T>* nodo) {
        if (nodo == nullptr) return head;

        if (head == nullptr) {
            head = nodo;
            return head;
        } 

        nodo->setNextNode(head);
        head = nodo;

        return head;
    }

    Node<T>* insertarAlFinal(Node<T>* nodo) {
        if (nodo == nullptr) return head;

        if (head == nullptr) {
            head = nodo;
            return head;
        } 

        Node<T>* temp = head;
        while (temp->getNextNode() != nullptr) {
            temp = temp->getNextNode();
        }
        temp->setNextNode(nodo);
        return head;
    }    

    void insertarOrdenado(Node<T>* nuevo) {
        if (nuevo == nullptr) return;

        // Caso 1: Lista vacía o insertar antes del head
        if (head == nullptr || nuevo->getDato() < head->getDato()) {
            nuevo->setNextNode(head);
            head = nuevo;
            return;
        }

        // Caso 2: Recorrer buscando la posición correcta
        Node<T>* actual = head;
        Node<T>* anterior = nullptr;

        // Avanzamos mientras el dato del nodo actual sea menor al nuevo
        while (actual != nullptr && actual->getDato() < nuevo->getDato()) {
            anterior = actual;
            actual = actual->getNextNode();
        }

        // Insertamos entre 'anterior' y 'actual'
        anterior->setNextNode(nuevo);
        nuevo->setNextNode(actual);
    }

    Node<T>* conectarNodo(Node<T>* NodoEnLista, Node<T>* NodoSuelto) {
        
        if (NodoSuelto == nullptr) return head;
        
        if (head == nullptr) {
            head = NodoEnLista;
        }
        
        if (NodoEnLista == nullptr) {
            head = NodoSuelto;
            return head;
        }

        Node<T>* temp = NodoEnLista;

        while (temp->getNextNode() != nullptr) {
            temp = temp->getNextNode();
        }
        temp->setNextNode(NodoSuelto);
        NodoSuelto->setNextNode(nullptr); // Asegurar que el nuevo nodo suelto no apunte a nada más
        return head;
    }

    Node<T>* eliminarNodo(Node<T>* nodoAEliminar) {
        if (head == nullptr || nodoAEliminar == nullptr) return head;

        if (head == nodoAEliminar) {
            head = head->getNextNode();
            delete nodoAEliminar;
            return head;
        }

        Node<T>* temp = head;
        while (temp->getNextNode() != nullptr && temp->getNextNode() != nodoAEliminar) {
            temp = temp->getNextNode();
        }

        if (temp->getNextNode() == nodoAEliminar) {
            Node<T>* nodoSiguiente = nodoAEliminar->getNextNode();
            delete nodoAEliminar;
            temp->setNextNode(nodoSiguiente);
        }

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
    
    return 0;
}

