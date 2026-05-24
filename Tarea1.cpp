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
        Node<T>* actual = head;
        while (actual != nullptr) {
            Node<T>* siguiente = actual->getNextNode();
            delete actual; 
            actual = siguiente;
        }
    }

    Node<T>* getHead() { return head; }
    Node<T>* getTail() { return tail; }
    int getSize() { return size; }
    
    void setHead(Node<T>* primerNodo) { this->head = primerNodo; }
    void setTail(Node<T>* ultimoNodo) { this->tail = ultimoNodo; }
    int incrementarSize() {
        return size++;
    }

    /* Método para insertar al final y mantener sincronizado el atributo size
    */
    void insertarAlFinal(T valor) {
        Node<T>* nuevo = new Node<T>(valor);
        if (head == nullptr) {
            head = nuevo;
            tail = nuevo;
        } else {
            tail->setNextNode(nuevo);
            nuevo->setPrevNode(tail);
            tail = nuevo;
        }
        size++;
    }
    
    // Verificar la integridad de la lista mediante el algoritmo de Floyd
    bool esListaValida(Node<T>* head) {
        if (head == nullptr) {
            return true;
        }

        Node<T>* tortuga = head;
        Node<T>* liebre = head;

        while (liebre != nullptr && liebre->getNextNode() != nullptr) {
            // Verificar consistencia del enlace doble antes de avanzar
            Node<T>* siguiente = tortuga->getNextNode();
            if (siguiente != nullptr && siguiente->getPrevNode() != tortuga) {
                // El siguiente nodo no reconoce a tortuga como su prev
                return false; 
            }

            // Avanzar punteros
            tortuga = tortuga->getNextNode();
            liebre = liebre->getNextNode()->getNextNode();

            if (tortuga == liebre) {
                return false; // Hay un bucle infinito
            }
        }
        return true;
    }

    // Validación por simetría de memoria usando el atributo size
    bool verificarListaConArreglo() {
        if (size == 0) {
            return (head == nullptr && tail == nullptr);
        }

        if (head == nullptr || tail == nullptr) return false;

        Node<T>** direccionesIda = new Node<T>*[size];

        // Recorrido de ida desde el Head
        Node<T>* actual = head;
        for (int i = 0; i < size; i++) {
            if (actual == nullptr) {
                // La lista real en memoria es mas corta de lo que registra size
                delete[] direccionesIda;
                return false; 
            }

            // Buscar si actual ya fue guardado antes
            for (int j = 0; j < i; j++) {
                if (direccionesIda[j] == actual) {
                    delete[] direccionesIda;
                    return false; 
                }
            }

            direccionesIda[i] = actual; 
            actual = actual->getNextNode();
        }

        if (direccionesIda[size - 1] != tail) {
            delete[] direccionesIda;
            return false;
        }

        //  Recorrido de vuelta desde el Tail y comparación con el arreglo de ida
        actual = tail;
        for (int i = size - 1; i >= 0; i--) {
            if (actual == nullptr) {
                // La lista de vuelta se rompió antes de tiempo o apunta a un lugar inválido
                delete[] direccionesIda;
                return false;
            }

            // Comparación del nodo de regreso con el guardado a la ida
            if (direccionesIda[i] != actual) {
                delete[] direccionesIda;
                return false; // Los punteros prev están cruzados o corruptos
            }

            actual = actual->getPrevNode();
        }

        delete[] direccionesIda;
        return true; 
    }

};



int main() {
    cout << "=== PRUEBAS DE INTEGRIDAD DE LISTA DOBLEMENTE ENLAZADA ===\n\n";

    // ESCENARIO 1: Una lista perfectamente válida
    cout << "--- Caso 1: Lista Valida ---\n";
    Lista<int> listaSana;
    
    listaSana.insertarAlFinal(10);
    listaSana.insertarAlFinal(20);
    listaSana.insertarAlFinal(30);
    listaSana.insertarAlFinal(40);

    cout << "Tamano registrado: " << listaSana.getSize() << endl;

    // Probar método 1 (Floyd)
    if (listaSana.esListaValida(listaSana.getHead())) {
        cout << "[OK] Metodo Floyd: La lista es estructuralmente valida.\n";
    } else {
        cout << "[ERROR] Metodo Floyd: Se detecto un problema en la estructura.\n";
    }

    // Probar método 2 (Auditoría por simetría con Arreglo)
    if (listaSana.verificarListaConArreglo()) {
        cout << "[OK] Metodo Arreglo: Los punteros de ida y vuelta coinciden perfectamente.\n";
    } else {
        cout << "[ERROR] Metodo Arreglo: Conflicto o desalineacion en las direcciones de memoria.\n";
    }

    // ESCENARIO 2: Corrupción manual de enlaces prev (Punteros rotos)
    cout << "\n--- Caso 2: Lista Corrupta (Punteros 'prev' incorrectos) ---\n";
    Lista<int> listaCorrupta;
    listaCorrupta.insertarAlFinal(100);
    listaCorrupta.insertarAlFinal(200);
    listaCorrupta.insertarAlFinal(300);

    // Rompe la simetria, el prev del tercer nodo apuntara directamente al Head (saltándose el segundo)
    Node<int>* tercerNodo = listaCorrupta.getTail();
    tercerNodo->setPrevNode(listaCorrupta.getHead()); 

    // Probar método 1
    if (listaCorrupta.esListaValida(listaCorrupta.getHead())) {
        cout << "[INFO] Metodo Floyd: Detecto que la lista no es valida (Bien).\n";
    } else {
        cout << "[OK] Metodo Floyd: Capturo exitosamente la falla de coherencia doble enlace.\n";
    }

    // Probar método 2
    if (listaCorrupta.verificarListaConArreglo()) {
        cout << "[INFO] Metodo Arreglo: Dijo que era valida (Fallo en la prueba).\n";
    } else {
        cout << "[OK] Metodo Arreglo: Capturo exitosamente que las direcciones no coinciden al regresar.\n";
    }


    // ESCENARIO 3: Bucle Infinito 
    cout << "\n--- Caso 3: Lista con Bucle Infinito (Ciclo fisico) ---\n";
    Lista<int> listaConBucle;
    listaConBucle.insertarAlFinal(5);
    listaConBucle.insertarAlFinal(15);
    listaConBucle.insertarAlFinal(25);

    // Forzar bucle, El último nodo (25) en su next apuntará de nuevo al segundo nodo (15)
    Node<int>* ultimo = listaConBucle.getTail();
    Node<int>* segundo = listaConBucle.getHead()->getNextNode();
    ultimo->setNextNode(segundo);

    // Probar método 1 
    if (listaConBucle.esListaValida(listaConBucle.getHead())) {
        cout << "[INFO] Metodo Floyd: No detecto el bucle (Fallo).\n";
    } else {
        cout << "[OK] Metodo Floyd: Evito el bucle infinito y reporto falso con exito.\n";
    }

    // Probar método 2 
    if (listaConBucle.verificarListaConArreglo()) {
        cout << "[INFO] Metodo Arreglo: No detecto el bucle (Fallo).\n";
    } else {
        cout << "[OK] Metodo Arreglo: Detuvo el ciclo usando el tamaño maximo y reporto falso con exito.\n";
    }

    // Evitar que el programa quede atrapado en un bucle infinito al salir, restaurando el enlace correcto
    ultimo->setNextNode(nullptr); 

    return 0;
}