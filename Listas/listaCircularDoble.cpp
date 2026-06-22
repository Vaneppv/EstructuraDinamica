#include <iostream>

using namespace std;

// Plantilla para el Tipo de Dato Nodo
template <typename T>
class Node {
private:
    T dato;
    Node<T>* nextNode;
    Node<T>* prevNode;

public:
    Node(T a, Node<T>* b = nullptr, Node<T>* c = nullptr) {
        dato = a;
        nextNode = b;
        prevNode = c;
    }
    ~Node() {}

    void setDato(T a) { dato = a; }
    void setNextNode(Node<T>* next) { nextNode = next; }
    void setPrevNode(Node<T>* prev) { prevNode = prev; }

    T getDato() { return dato; }
    Node<T>* getNextNode() { return nextNode; }
    Node<T>* getPrevNode() { return prevNode; }
};

// Clase Lista que gestiona la cadena de nodos
template <typename T>
class Lista {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    Lista() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    
    ~Lista() {
        if (head == nullptr) return;

        // Rompemos el enlace circular para poder recorrer la lista como lineal
        tail->setNextNode(nullptr);

        Node<T>* actual = head;
        while (actual != nullptr) {
            Node<T>* siguiente = actual->getNextNode();
            delete actual; // Liberamos la memoria del nodo al que apunta el puntero
            actual = siguiente;
        }
        
        // resetear punteros
        head = nullptr;
        tail = nullptr;
    }

    Node<T>* getHead() { return head; }
    Node<T>* getTail() { return tail; }
    int getSize() { return size; }
    
    void setHead(Node<T>* primerNodo) { this->head = primerNodo; }
    void setTail(Node<T>* ultimoNodo) { this->tail = ultimoNodo; }
    int incrementarSize() {
        return size++;
    }

    // INSERTAR AL INICIO
    void insertarAlInicio(Node<T>* nuevo) {
        if (head == nullptr) {
            head = tail = nuevo;
            nuevo->setNextNode(nuevo);
            nuevo->setPrevNode(nuevo);
        } else {
            nuevo->setNextNode(head);
            nuevo->setPrevNode(tail);
            head->setPrevNode(nuevo);
            tail->setNextNode(nuevo);
            head = nuevo;
        }
        size++;
    }

    // INSERTAR AL FINAL
    void insertarAlFinal(Node<T>* nuevo) {
        if (head == nullptr) {
            insertarAlInicio(nuevo);
        } else {
            nuevo->setNextNode(head);
            nuevo->setPrevNode(tail);
            tail->setNextNode(nuevo);
            head->setPrevNode(nuevo);
            tail = nuevo;
            size++;
        }
    }

    // BORRAR AL INICIO
    void borrarAlInicio() {
        if (head == nullptr) return;

        if (head == tail) { // Solo un nodo
            delete head;
            head = tail = nullptr;
        } else {
            Node<T>* temp = head;
            head = head->getNextNode();
            head->setPrevNode(tail);
            tail->setNextNode(head);
            delete temp;
        }
        size--;
    }

    // BORRAR AL FINAL
    void borrarAlFinal() {
        if (head == nullptr) return;

        if (head == tail) { // Solo un nodo
            delete head;
            head = tail = nullptr;
        } else {
            Node<T>* temp = tail;
            tail = tail->getPrevNode();
            tail->setNextNode(head);
            head->setPrevNode(tail);
            delete temp;
        }
        size--;
    }

};
