#include <iostream>
using namespace std;

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

    Node(){}
    ~Node() {}

    void setDato(T a) { dato = a; }
    void setNextNode(Node<T>* next) { nextNode = next; }
    T getDato() { return dato; }
    Node<T>* getNextNode() { return nextNode; }
};

template <typename T>
class Colas {
private:
    Node<T>* firstNode;
    Node<T>* lastNode;
    int size;
public:
    Colas() {
        firstNode = nullptr;
        lastNode = nullptr;
        size = 0;
    }
    ~Colas() {
        Node<T>* actual = firstNode;
        while (actual != nullptr) {
            Node<T>* siguiente = actual->getNextNode();
            delete actual;
            actual = siguiente;
        }
    }

    void push(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (empty()) {
            firstNode = newNode;
        } else {
            lastNode->setNextNode(newNode);
        }
        lastNode = newNode;
        size++;
    }

    T pop() {
        if (firstNode != nullptr) {
            Node<T>* temp = firstNode;
            T value = temp->getDato();
            firstNode = firstNode->getNextNode();
            if (firstNode == nullptr) {
                lastNode = nullptr;
            }
            delete temp;
            size--;
            return value;
        }
        throw runtime_error("La cola esta vacia");
    }

    int getSize() const {
        return size;
    }

    bool empty() const {
        return (firstNode == nullptr)? true : false;
    }

};

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

template<typename T>
class ColaPrioridadArray {
private:
    Colas<T> colas[6]; 
public:
    ColaPrioridadArray() {}

    bool empty() {
        for (int i = 0; i < 6; i++) {
            if (!colas[i].empty()) {
                return false;
            }
        }
        return true;
    }

    void insertar(T valor, int prioridad) {
        if (prioridad < 0) prioridad = 0;
        if (prioridad > 5) prioridad = 5;
        colas[prioridad].push(valor);
    }

    T sacar() {
        for (int i = 0; i <= 5; i++) {
            if (!colas[i].empty()) {
                T valor = colas[i].pop(); 
                return valor; 
            }
        }
        throw std::runtime_error("Cola de prioridad vacia");
    }
};

template<typename T>
class ColaPrioridadLista {
private:
    Lista<Colas<T>*> listaHeaders; 

public:
    ColaPrioridadLista() {
        for (int i = 0; i < 6; i++) {
            Colas<T>* nuevaCola = new Colas<T>();
            Node<Colas<T>*>* nuevoHeader = new Node<Colas<T>*>(nuevaCola);
            listaHeaders.insertarAlFinal(nuevoHeader);
        }
    }

    ~ColaPrioridadLista() {
        Node<Colas<T>*>* actual = listaHeaders.getHead();
        while (actual != nullptr) {
            delete actual->getDato(); 
            actual = actual->getNextNode();
        }
    }
    
    void insertar(T valor, int prioridad) {
        if (prioridad < 0) prioridad = 0;
        if (prioridad > 5) prioridad = 5;

        Node<Colas<T>*>* temp = listaHeaders.getHead();
        for (int i = 0; i < prioridad; i++) {
            temp = temp->getNextNode();
        }
        temp->getDato()->push(valor);
    }

    T sacar() {
        Node<Colas<T>*>* temp = listaHeaders.getHead();
        while (temp != nullptr) {
            if (!temp->getDato()->empty()) {
                return temp->getDato()->pop();
            }
            temp = temp->getNextNode();
        }
        throw std::runtime_error("Cola de prioridad vacia");
    }

    bool empty() {
        Node<Colas<T>*>* temp = listaHeaders.getHead();
        while (temp != nullptr) {
            if (!temp->getDato()->empty()) return false;
            temp = temp->getNextNode();
        }
        return true;
    }
};

int main() {
    cout << "=== Probando ColaPrioridadArray ==="<< endl;
    ColaPrioridadArray<int> miColaArray;
    
    miColaArray.insertar(10, 5); 
    miColaArray.insertar(20, 0); 
    miColaArray.insertar(30, 2); 
    miColaArray.insertar(40, 0); 
    
    while (!miColaArray.empty()) {
        cout << "Procesando de Array: " << miColaArray.sacar() << endl;
    }

    cout << endl;

    cout << "=== Probando ColaPrioridadLista ==" << endl;
    ColaPrioridadLista<int> miColaLista;
    
    miColaLista.insertar(10, 5);
    miColaLista.insertar(20, 0);
    miColaLista.insertar(30, 2);
    miColaLista.insertar(40, 0);
    
    while (!miColaLista.empty()) {
        cout << "Procesando de Lista: " << miColaLista.sacar() << endl;
    }

    return 0;
}