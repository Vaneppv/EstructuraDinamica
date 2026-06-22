#include <iostream>
using namespace std;

// COLA (QUEUE) -> FIRST IN FIRST OUT (FIFO)

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

    void ordenarCola() {
        int n = this->getSize();
        for (int i = 0; i < n; i++) {
            T minVal;

            // Encontrar el valor mínimo rotando la cola
            for (int j = 0; j < n - i; j++) {
                T valor = this->pop();
                if (valor < minVal) minVal = valor;
                this->push(valor);
            }
            // Extraer solo la primera instancia del mínimo
            bool extraido = false;
            for (int j = 0; j < n - i; j++) {
                T valor = this->pop();
                if (valor == minVal && !extraido) {
                    extraido = true;
                } else {
                    this->push(valor);
                }
            }
            // Colocar el mínimo al final de la parte "ya ordenada"
            this->push(minVal);
        }
    }

    void popPilaComoPila(){
    Colas<T> colaAux;
    int n = this->getSize;

    for (int i = 0; i < n-1; i++){
        colaAux.push(this->pop())
    }
    
    T valor = this->pop();

    while (!colaAux.empty()){
        this->push(colaAux.pop())
    }
    return valor
    }

    void insertarOrdenadoCola(Colas<int>& c, int valor) {
        int n = c.getSize();
        bool insertado = false;

        // Rotamos la cola 'n' veces
        for (int i = 0; i < n; i++) {
            int actual = c.pop();
            
            // Si encontramos la posición y aún no lo hemos metido, metemos el nuevo valor
            if (!insertado && valor < actual) {
                c.push(valor);
                insertado = true;
            }
            c.push(actual);
        }
        if (!insertado) {
            c.push(valor);
        }
    }

};

int main() {
    Colas<int> cola;
    cola.push(8);
    cola.push(3);
    cola.push(5);
    cola.push(1);

    cout << "Cola antes de ordenar: ";
    int sizeBefore = cola.getSize();
    for (int i = 0; i < sizeBefore; i++) {
        int valor = cola.pop();
        cout << valor << " ";
        cola.push(valor);
    }
    cout << endl;

    cola.ordenarCola();

    cout << "Cola ordenada: ";
    while (!cola.empty()) {
        cout << cola.pop() << " ";
    }
    cout << endl;

    return 0;
}
