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
        int borrados = 0;
        while (actual != nullptr && borrados < size) {
            Node<T>* siguiente = actual->getNextNode();
            delete actual; 
            actual = siguiente;
            borrados++;
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

    // Deshabilitar copia y asignación
    Lista(const Lista&) = delete;
    Lista& operator=(const Lista&) = delete;

    void insertarAlInicio(Node<T>* nuevo) {
        if (nuevo == nullptr) return;
        if (head == nullptr){
            head= nuevo;
            tail= nuevo;
        }
        Node<T>* actual = head;
        actual->setPrevNode(nuevo);
        nuevo->setNextNode(actual);
        head = nuevo;
        size++;
    }

    // Método para insertar al final y mantener sincronizado el atributo size
    void insertarAlFinal(Node<T>* nuevo) {
        if (nuevo == nullptr) return;
        if (head == nullptr) {
            head = nuevo;
            tail = nuevo;
        } else {
            tail->setNextNode(nuevo);
            nuevo->setPrevNode(tail);
            nuevo->setNextNode(nullptr);
            tail = nuevo;
        }
        size++;
    }

    void insertarOrdenado(Node<T>* nuevo) {
        if (nuevo == nullptr) return;

        // Caso 1: Lista vacía
        if (head == nullptr) {
            head = tail = nuevo;
            nuevo->setNextNode(nullptr);
            nuevo->setPrevNode(nullptr);
            size++;
            return;
        }

        // caso 2: Insertar antes del head
        if (nuevo->getDato() < head->getDato()){
            nuevo->setPrevNode(nullptr);
            nuevo->setNextNode(head);
            head->setPrevNode(nuevo);
            head = nuevo;
            size++;
            return;
        }

        // Caso 3: Recorrer buscando la posición correcta
        Node<T>* actual = head;
        while (actual != nullptr && actual->getDato() < nuevo->getDato()) {
            actual = actual->getNextNode();
        }
        // Caso 3.1: Insertar al final
        if (actual == nullptr) {
            insertarAlFinal(nuevo);
            return;
        }
        // Caso 3.2: Insertar entre actual y su previo
        Node<T>* anterior = actual->getPrevNode();

        nuevo->setNextNode(actual);
        nuevo->setPrevNode(anterior);
        anterior->setNextNode(nuevo);
        actual->setPrevNode(nuevo);
        size++;
    }

    void borrarAlInicio() {
        if (head == nullptr) return;
        Node<T>* temp = head;
        head = head->getNextNode();
        if (head) {
            head->setPrevNode(nullptr);
        } else tail = nullptr;
        delete temp;
        size--;
    }
    
    void borrarAlFinal() {
        if (tail == nullptr) return;
        Node<T>* temp = tail;
        tail = tail->getPrevNode();
        if (tail) tail->setNextNode(nullptr);
        else head = nullptr;
        delete temp;
        size--; // Decrementar el tamaño al eliminar un nodo
    }

    void borrarNodo(Node<T>* nodo) {
        if (nodo == nullptr) return;
        if (nodo == head) {
            borrarAlInicio();
            return;
        }
        if (nodo == tail) {
            borrarAlFinal();
            return;
        }
        Node<T>* prev = nodo->getPrevNode();
        Node<T>* next = nodo->getNextNode();
        if (prev) prev->setNextNode(next);
        if (next) next->setPrevNode(prev);
        delete nodo;
        size--;
    }

    bool esListaValida() {
        // --- 1. VALIDACIÓN HACIA ADELANTE ---

        if (head !=  nullptr){
            Node<T>* lento = head;
            Node<T>* rapido = head;
            while (rapido != nullptr && rapido->getNextNode() != nullptr) {
                // Integridad: El siguiente conoce a este como su previo?
                if (lento->getNextNode() != nullptr && lento->getNextNode()->getPrevNode() != lento) 
                    return false;

                lento = lento->getNextNode();
                rapido = rapido->getNextNode()->getNextNode();
                if (lento == rapido) return false; // Hay ciclo
            }
        }

        // --- 2. VALIDACIÓN HACIA ATRÁS ---
        if (tail != nullptr) {
            Node<T>* lento = tail;
            Node<T>* rapido = tail;
            while (rapido != nullptr && rapido->getPrevNode() != nullptr) {
                // Integridad: El previo conoce a este como su siguiente?
                if (lento->getPrevNode() != nullptr && lento->getPrevNode()->getNextNode() != lento) 
                    return false;

                lento = lento->getPrevNode();
                rapido = rapido->getPrevNode()->getPrevNode();
                if (lento == rapido) return false; // Hay ciclo
            }
        }
    return true;
    }

    void invertirLista() {
        if (head == nullptr || head == tail) return;

        Node<T>* actual = head;
        Node<T>* temp = nullptr;

        // Intercambiamos prev y next para cada nodo
        while (actual != nullptr) {
            temp = actual->getPrevNode();
            actual->setPrevNode(actual->getNextNode());
            actual->setNextNode(temp);
            
            // Avanzamos al siguiente nodo (que ahora es el que estaba en prev)
            actual = actual->getPrevNode();
        }

        // Finalmente, intercambiamos los punteros head y tail de la lista
        temp = head;
        head = tail;
        tail = temp;
    }

    Node<T>* saltarCiclo(Node<T>* headCiclo) {
        Node<T>* curr = headCiclo;
        // Recorremos hasta encontrar el nodo que cierra el ciclo
        while (curr->getNextNode() != headCiclo && curr->getNextNode() != nullptr) {
            curr = curr->getNextNode();
        }
        return curr->getNextNode(); // Devuelve el nodo que sigue al ciclo
    }

    void extraerCiclos(Node<T>** arregloHeads, Lista<T>* listaSola) {
        // 1. Primera pasada: contar ciclos
        int tamano = 0;
        Node<T>* actual = head;
        while (actual != nullptr) {
            Node<T>* sig = actual->getNextNode();
            // Si el siguiente nodo tiene un 'prev' diferente, es una bifurcación/ciclo
            if (sig != nullptr && sig->getPrevNode() != actual) {
                tamano++;
                // Saltar el ciclo para no contarlo como lineal
                actual = saltarCiclo(sig); 
            } else {
                actual = sig;
            }
        }

        // 2. Segunda pasada: extraer
        actual = head;
        int index = 0;
        while (actual != nullptr) {
            Node<T>* sig = actual->getNextNode();
            
            if (sig != nullptr && sig->getPrevNode() != actual) {
                // Es inicio de ciclo
                arregloHeads[index++] = sig;
                
                // Desconectar el ciclo de la lista principal
                actual->setNextNode(nullptr);
                sig->setPrevNode(nullptr);
                
                // Saltar el ciclo en el recorrido para no procesarlo como lineal
                actual = saltarCiclo(sig);
            } else {
                // Es un nodo lineal: lo movemos a la nueva lista
                Node<T>* temp = actual;
                actual = sig; // Avanzamos antes de desconectar
                
                // Desconectar y mover
                temp->setNextNode(nullptr);
                temp->setPrevNode(nullptr);
                listaSola->insertarAlFinal(temp);
            }
        }
    }

    void dividirEnNPartes(int N, Lista<T>* arregloListas[], bool permitirRedundancia) {
        if (head == nullptr || N <= 0) return;

        // Calcular tamaño objetivo por lista
        int basePorLista = size / N;
        int resto = size % N;
        int objetivoPorLista = (resto > 0 && permitirRedundancia) ? (basePorLista + 1) : basePorLista;

        Node<T>* actual = head;

        for (int i = 0; i < N; i++) {
            arregloListas[i] = new Lista<T>();
            int contador = 0;

            // Llenar hasta el objetivo
            while (contador < objetivoPorLista) {
                Node<T>* nodoInsertar = nullptr;

                if (actual != nullptr) {
                    // Hay nodos originales disponibles
                    nodoInsertar = permitirRedundancia ? new Node<T>(actual->getDato()) : actual;
                    
                    if (!permitirRedundancia) {
                        // Si no permitimos redundancia, desvinculamos el nodo actual
                        actual = actual->getNextNode();
                    } else {
                        // Si permitimos redundancia, simplemente avanzamos
                        actual = actual->getNextNode();
                    }
                } else if (permitirRedundancia) {
                    // No quedan nodos, pero se permite redundancia: clonamos el último dato
                    // (O podríamos clonar desde el head para rellenar)
                    nodoInsertar = new Node<T>(head->getDato());
                }

                if (nodoInsertar) {
                    // Si movemos (no redundancia), limpiamos enlaces antes de insertar
                    if (!permitirRedundancia) {
                        nodoInsertar->setNextNode(nullptr);
                        nodoInsertar->setPrevNode(nullptr);
                    }
                    arregloListas[i]->insertarAlFinal(nodoInsertar);
                    contador++;
                }
            }
        }

        // Limpiar original si no hubo redundancia
        if (!permitirRedundancia) {
            head = nullptr;
            tail = nullptr;
            size = 0;
        }
    }

};
