#include <iostream>

using namespace std;

template <typename T, typename A>
class Datos 
{
private:
    T dato1;
    A dato2;
public:
    Datos(T dat1, A dat2){
        dato1 = dat1;
        dato2 = dat2;
    }
    ~Datos(){

    };

    void mostrardatos(){
        cout << "Dato 1: " << dato1 << endl;
        cout << "Dato 2: " << dato2 << endl;
    }
};

template <typename R>
R sumarDatos(R a, R b){
    return a+b;
}

int main() {
    auto mivar = Datos<int, float>(2, 5.6);
    Datos<int, float> datos(2, 5.6);

    mivar.mostrardatos();
    cout << endl;    
    datos.mostrardatos();

    int r = sumarDatos<int>(4, 6);
    cout << "Suma de Datos 4 + 6 = " << r ;
    return 0;
    
}