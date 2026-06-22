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

    /*Crear una funcion que reciba dos heads de diferentes listas doble enlazada y devuelva el head 
    de la fusion de ambas listas en order de menor a mayor eliminando duplicados */

    Node<T>* fusion2ListasDobles (Node<T>* head1, Node<T>* head2 ){
        if (head1 == nullptr) return head2;
        if (head2 == nullptr) return head1;

        Node<T>* p1 = head1;
        Node<T>* p2 = head2;
        Node<T>* newHead = nullptr;
        Node<T>* newTail = nullptr;

        auto appendNode = [&](Node<T>* node){
            node->setPrevNode(newTail);
            node->setNextNode(nullptr);
            if (newTail) newTail->setNextNode(node);
            newTail = node;
            if (!newHead) newHead = node;
        };

        auto deleteNode = [&](Node<T>* node){
            if (!node) return;
            node->setPrevNode(nullptr);
            node->setNextNode(nullptr);
            delete node;
        };

        while (p1 != nullptr && p2 != nullptr) {
            if (p1->getDato() < p2->getDato()) {
                Node<T>* next = p1->getNextNode();
                if (newTail == nullptr || newTail->getDato() != p1->getDato()) {
                    appendNode(p1);
                } else {
                    deleteNode(p1);
                }
                p1 = next;
            } else if (p2->getDato() < p1->getDato()) {
                Node<T>* next = p2->getNextNode();
                if (newTail == nullptr || newTail->getDato() != p2->getDato()) {
                    appendNode(p2);
                } else {
                    deleteNode(p2);
                }
                p2 = next;
            } else { // equal
                Node<T>* next1 = p1->getNextNode();
                Node<T>* next2 = p2->getNextNode();
                if (newTail == nullptr || newTail->getDato() != p1->getDato()) {
                    appendNode(p1);
                    // delete the duplicate from list2
                    deleteNode(p2);
                } else {
                    // value already present at tail: delete both nodes
                    deleteNode(p1);
                    deleteNode(p2);
                }
                p1 = next1;
                p2 = next2;
            }
        }

        while (p1 != nullptr) {
            Node<T>* next = p1->getNextNode();
            if (newTail == nullptr || newTail->getDato() != p1->getDato()) appendNode(p1);
            else deleteNode(p1);
            p1 = next;
        }

        while (p2 != nullptr) {
            Node<T>* next = p2->getNextNode();
            if (newTail == nullptr || newTail->getDato() != p2->getDato()) appendNode(p2);
            else deleteNode(p2);
            p2 = next;
        }

        return newHead;
    }
};

template <typename T>
void printList(Node<T>* head) {
    Node<T>* cur = head;
    while (cur != nullptr) {
        cout << cur->getDato() << " ";
        cur = cur->getNextNode();
    }
    cout << endl;
}


int main() {
    // Crear lista 1: 1 -> 3 -> 5 -> 7
    Node<int>* a1 = new Node<int>(1);
    Node<int>* a2 = new Node<int>(3);
    Node<int>* a3 = new Node<int>(5);
    Node<int>* a4 = new Node<int>(7);
    a1->setNextNode(a2); a2->setPrevNode(a1);
    a2->setNextNode(a3); a3->setPrevNode(a2);
    a3->setNextNode(a4); a4->setPrevNode(a3);

    // Crear lista 2: 2 -> 3 -> 6 -> 7 -> 8 (contiene duplicados 3 y 7)
    Node<int>* b1 = new Node<int>(2);
    Node<int>* b2 = new Node<int>(3);
    Node<int>* b3 = new Node<int>(6);
    Node<int>* b4 = new Node<int>(7);
    Node<int>* b5 = new Node<int>(8);
    b1->setNextNode(b2); b2->setPrevNode(b1);
    b2->setNextNode(b3); b3->setPrevNode(b2);
    b3->setNextNode(b4); b4->setPrevNode(b3);
    b4->setNextNode(b5); b5->setPrevNode(b4);

    cout << "Lista 1: "; printList(a1);
    cout << "Lista 2: "; printList(b1);

    Lista<int> helper;
    Node<int>* merged = helper.fusion2ListasDobles(a1, b1);

    cout << "Fusion (sin duplicados): "; printList(merged);

    // Liberar memoria de la lista resultante
    Node<int>* cur = merged;
    while (cur != nullptr) {
        Node<int>* next = cur->getNextNode();
        delete cur;
        cur = next;
    }

    return 0;
}
