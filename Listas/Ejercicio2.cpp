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

void invertirLista() {
        if (head == nullptr) return;

        Node<T>* actual = head;
        Node<T>* siguiente = head->getNextNode();
        Node<T>* temp = nullptr;

        // Intercambiamos prev y next para cada nodo
        while (actual != nullptr) {
            actual->setNextNode(siguiente->getNextNode());
            siguiente->setNextNode(actual);
            temp = siguiente;
            siguiente = actual->getNextNode();
        }
        head = temp; // El nuevo head es el último nodo procesado
        return head;
    }
};