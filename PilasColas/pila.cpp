#include <iostream>

using namespace std;


// PILA (STACK)-> LAST IN FIRST OUT (LIFO)
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
class Pilas {
private:
    Node<T>* lastNode;
    int size;
public:
    Pilas(){
        lastNode = nullptr;
        size = 0;
    }
    ~Pilas() {
        while (!empty()) pop();
    }
    /* ~Pilas(){
        Node<T>* actual = lastNode;
        while (actual != nullptr) {
            Node<T>* siguiente = actual->getNextNode();
            delete actual;
            actual = siguiente;
        }
    } */

    void push(T data) {
        Node<T>* newNode = new Node<T>(data, lastNode);
        lastNode = newNode;
        size++;
    }

    T pop() {
        if (lastNode != nullptr){
            Node<T>* temp = lastNode;
            T value = temp->getDato();
            lastNode = lastNode->getNextNode();
            delete temp;
            size--;
            return value;
        }
        throw runtime_error("La pila está vacía");
    }

    bool empty() const { 
        return lastNode == nullptr;
    }
    
    T peek() const {
        if (lastNode != nullptr) {
            return lastNode->getDato();
        }
        throw runtime_error("La pila está vacía");
    }

    int getSize() const { return size; }

    // Ordena la pila actual ( resultado final peek menor, base mayor)
    void ordenarPila() {
        Pilas<int> aux;
        while (!this->empty()) {
            T temp = this->pop();
            while (!aux.empty() && aux.peek() < temp) {
                this->push(aux.pop());
            }
            aux.push(temp);
        }
        while (!aux.empty()) {
            this->push(aux.pop());
        }
    }

    T popPilaComoCola (){
        if (this->empty()) {
            throw runtime_error("La pila está vacía");
        }

        Pilas<T> pilaAux;
        T temp;

        while(!this->empty()){
           temp = this->pop();
           pilaAux.push(temp);
        }
        T retorno = pilaAux.pop();
        while(!pilaAux.empty()){
            temp = pilaAux.pop();
            this->push(temp);
        }
        return retorno;
    }

    void insertarOrdenadoPila(Pilas<int>& p, int valor) {
        // si la pila está vacía o el valor es mayor que el tope
        if (p.empty() || valor > p.peek()) {
            p.push(valor);
            return;
        }

        Si el valor es menor, sacamos el tope, guardamos en la pila de ejecución y seguimos buscando
        int temp = p.pop();
        insertarOrdenadoPila(p, valor);
        
        Al regresar de la recursión, volvemos a poner el elemento que sacamos
        p.push(temp);
    }

    void insertarOrdenadoPila(Pilas<int>& p, int valor) {
        Pilas<int> pAux;

        // 1. Movemos todo lo que sea menor al valor a la pila auxiliar
        while (!p.empty() && p.peek() < valor) {
            pAux.push(p.pop());
        }

        // 2. Insertamos el valor en su lugar
        p.push(valor);

        // 3. Regresamos lo que movimos
        while (!pAux.empty()) {
            p.push(pAux.pop());
        }
    }
};


int main() {

    Pilas<int> pila;
    int opcion = 0;
    int num;

    do {
        cout << "\nMenu:\n";
        cout << "1. Agregar numero a la pila\n";
        cout << "2. Ordenar pila y mostrar elementos\n";
        cout << "3. Simulación de Cola, sacar primer elemento\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese un numero: ";
                cin >> num;
                pila.push(num);
                break;
            case 2:
                if (pila.empty()) {
                    cout << "La pila esta vacia.\n";
                } else {
                    pila.ordenarPila();
                    cout << "Pila ordenada (de arriba hacia abajo):\n";
                    while (!pila.empty()) {
                        cout << pila.pop() << "\n";
                    }
                }
                break;
            case 3: 
                if (pila.empty()){
                    cout << "La pila esta vacia.\n";
                } else {
                    int firtIn = pila.pilaComoCola();
                    cout << "Elemento retirado: " << firtIn << endl;
                }
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    return 0;
}
