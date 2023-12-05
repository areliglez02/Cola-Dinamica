#include <iostream>
#include <string>

//const int TAM = 100;

template<class T>
class COLA;

template <class T>
class node {
private:
    T data;
    node<T>* sig;
public: 
    node() :sig(nullptr) {};
    friend class COLA<T>;
};

class alumno {
private:
    std::string nombre;
    std::string carrera;
    int materiasAprobadas;
    float promedio;
public:
    alumno() {};

    bool operator == (const alumno& e) const {
        return nombre == e.nombre;
    }
    bool operator != (const alumno& e) const {
        return nombre != e.nombre;
    }
    bool operator < (const alumno& e) const {
        return nombre < e.nombre;
    }
    bool operator <= (const alumno& e) const {
        return nombre <= e.nombre;
    }
    bool operator > (const alumno& e) const {
        return nombre > e.nombre;
    }
    bool operator >= (const alumno& e) const {
        return nombre >= e.nombre;
    }

    void operator=(alumno& x){
        nombre = x.nombre;
        carrera = x.carrera;
        materiasAprobadas = x.materiasAprobadas;
        promedio = x.promedio;

    }
    friend std::ostream& operator<<(std::ostream& o, alumno& p) {
        o << "nombre: " << p.nombre << "\t carrera: " << p.carrera << "\t materias aprobadas: " << p.materiasAprobadas << "\t promedio: " << p.promedio << std::endl;
        return o;
    }
    friend std::istream& operator>>(std::istream& o, alumno& p){
        std::cout << "\nInserta nombre: ";
        o >> p.nombre;
        std::cout << "\nInserta carrera: ";
        std::cin.ignore();
        o >> p.carrera;
        std::cout << "\nMaterias aprobadas: ";
        std::cin.ignore();
        o >> p.materiasAprobadas;
        std::cout << "\nPromedio: ";
        std::cin.ignore();
        o >> p.promedio;
        return o;
    }
    bool operator==(alumno& p) {
        return p.nombre == nombre && p.carrera == carrera && p.materiasAprobadas == materiasAprobadas && p.promedio == promedio;
    }

};

template<class T>
class COLA {
private:
    alumno datos;
    node<T>* cola;
    int ult;
    int cont;
public:
    COLA() :ult(-1), cont(0) {}
    bool vacia()const;
    bool llena();
    node<T>* ultimo()const;
    void inserta(node<T>* pos, T elem);
    bool elimina(node<T>* pos);
    void enqueue(T elem);
    node<T>* dequeue();
    void imprime()const;
    void imprimirPrimero()const;
};

template<class T>
bool COLA<T>::vacia() const {
    return ult == -1;
}

template<class T>
bool COLA<T>::llena() {
    return cont == 99;
}

template<class T>
node<T>* COLA<T>::ultimo() const {
    if (vacia()) {
        return nullptr;
    }
    node<T>* aux = cola;
    while (aux->sig != nullptr) {
        aux = aux->sig;
    }
    return aux;
}

template<class T>
void COLA<T>::inserta(node<T>* pos, T elem){
    node<T>* aux = new node<T>;
    aux->data = elem;
    if (pos == nullptr) {
        aux->sig = cola;
        cola = aux;
    }else {
        aux->sig = pos->sig;
        pos->sig = aux;
    }
}

template<class T>
bool COLA<T>::elimina(node<T>* pos) {
    if (vacia() || pos == nullptr) 
        return false;
    if (pos == cola)
        cola = cola->sig;
    else
        anterior(pos)->sig = pos->sig;
    delete pos;
    return true;
}

template<class T>
void COLA<T>::enqueue(T elem) {
    //inserta(node<T>* pos, T elem);
    if (!llena()) {
        inserta(ultimo(), elem);
        ult++;
        cont++;
    }else
        std::cout << "\nLa cola esta llena." << std::endl;
}

template <class T>
node<T>* COLA<T>::dequeue() {
    if (vacia()) {
        std::cout << "\n La cola esta vacia" << std::endl;
        return nullptr;
    }else {
        node<T>* dequeuedNode = cola;
        cola = cola->sig;
        ult--;
        return dequeuedNode;
    }
}

template <class T>
void COLA<T>::imprime()const {
    node<T>* aux = cola;
    while (aux != nullptr) {
        std::cout << std::endl;
        std::cout << aux->data << " " << std::endl;
        aux = aux->sig;
    }
}

template<class T>
void COLA<T>::imprimirPrimero()const {
    node<T>* aux = cola;
    std::cout << std::endl;
    std::cout << aux->data << " " << std::endl;
}

int main() {
    int opc, repite = 1;
    COLA<alumno> solicitudCola;
    alumno datos;
    do {
        std::cout << "\n\t\tSOLICITUD DE CONSTANCIAS DE ALUMNOS\n" << std::endl;
        std::cout << "\n[1]. Agregar solicitud" << std::endl;
        std::cout << "\n[2]. Solicitud completada" << std::endl;
        std::cout << "\n[3]. Mostrar solicitudes" << std::endl;
        std::cout << "\n[4]. Salir" << std::endl;
        std::cout << "\nOpcion: " << std::endl;
        std::cin >> opc;
        switch (opc) {
        case 1:
            std::cout << "\nIngrese los datos solicitados..." << std::endl;
            std::cin >> datos;
            solicitudCola.enqueue(datos);
            break;
        case 2:
            if (!solicitudCola.vacia()) {
                solicitudCola.imprimirPrimero();
                solicitudCola.dequeue();  // Quitar la solicitud de la cola.
                std::cout << "Solicitud completada " << std::endl;
            }
            else {
                std::cout << "La cola de solicitudes está vacía." << std::endl;
            }
            break;
        case 3:
            solicitudCola.imprime();
            break;
        case 4:
            repite = 0;
            break;
        default:
            std::cout << "\nOPCION INVALIDA" << std::endl;
            break;
        }

    } while (repite);
    return 0;
}