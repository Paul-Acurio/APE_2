#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// definición de la Clase Estudiante
class Estudiante {
private:
    string cedula;
    string nombres;
    string apellidos;
    string fechaNacimiento;
    vector<double> notas;
    static const int MAX_NOTAS = 7; 

public:
    // constructor
    Estudiante(string _ced, string _nom, string _ape, string _fec) {
        cedula = _ced;
        nombres = _nom;
        apellidos = _ape;
        fechaNacimiento = _fec;
    }

    // getters
    string getCedula() const { return cedula; }
    string getNombreCompleto() const { return nombres + " " + apellidos; }
    vector<double>& getNotas() { return notas; }
    
    // setters
    void setNombres(string n) { nombres = n; }
    void setApellidos(string a) { apellidos = a; }

    bool tieneEspacioParaNotas() { return notas.size() < MAX_NOTAS; }

    //metodo de eliminarnota
    void eliminarNota(int indice) {
        if (indice >= 0 && indice < notas.size()) {
            notas.erase(notas.begin() + indice);
            cout << "Nota eliminada con exito." << endl;
        } else {
            cout << "Indice no valido." << endl;
            cout << " " <<endl;
        }
    }

    double calcularPromedio() {
        if (notas.empty()) return 0.0;
        double suma = 0;
        for (int i = 0; i < notas.size(); i++) {
            suma += notas[i];
        }
        return suma / notas.size();
    }
};

// variables Globales en vectores
vector<Estudiante> listaEstudiantes;
const int MAX_CUPOS = 20;

int buscarEstudiantePorCedula(string ced) {
    for (int i = 0; i < listaEstudiantes.size(); i++) {
        if (listaEstudiantes[i].getCedula() == ced) return i;
    }
    return -1;
}

void gestionarEstudiantes() {
    int subOp;
    cout << "\n--- LISTADO ---" << endl;
    for (int i = 0; i < listaEstudiantes.size(); i++) {
        cout << (i + 1) << ". " << listaEstudiantes[i].getCedula() << " - " << listaEstudiantes[i].getNombreCompleto() << endl;
    }

    cout << "\n1. Insertar | 2. Eliminar | 3. Volver: ";
    cin >> subOp; cin.ignore();

    if (subOp == 1) {
        if (listaEstudiantes.size() < MAX_CUPOS) {
            string c, n, a, f;
            cout << "Cedula: "; getline(cin, c);
            cout << "Nombres: "; getline(cin, n);
            cout << "Apellidos: "; getline(cin, a);
            cout << "Fecha Nac.: "; getline(cin, f);
            listaEstudiantes.push_back(Estudiante(c, n, a, f));
            cout << "Estudiante registrado." << endl;
            cout << " " <<endl;
        } else {
            cout << "Cupo lleno." << endl;
            cout << " " <<endl;
        }
    }  
    else if (subOp == 2 && !listaEstudiantes.empty()) {
        int id; cout << "Numero ID a eliminar: "; cin >> id;
        if (id > 0 && id <= listaEstudiantes.size()) {
            listaEstudiantes.erase(listaEstudiantes.begin() + (id - 1));
            cout << "Registro eliminado." << endl;
            cout << " " <<endl;
        }
    }
}

void registroCalificaciones() {
    string ced;
    cout << "Ingrese cedula del estudiante: "; 
    getline(cin, ced);
    int idx = buscarEstudiantePorCedula(ced);

    if (idx != -1) {
        Estudiante &e = listaEstudiantes[idx];
        int opt;
        do {
            cout << "\nEstudiante: " << e.getNombreCompleto() << "\nNotas: ";
            for (int i = 0; i < e.getNotas().size(); i++) {
                cout << "[" << i + 1 << "]: " << e.getNotas()[i] << "  ";
                cout << " " <<endl;
            }
            
            cout << "\n1. Nueva nota | 2. Eliminar nota | 3. Salir: ";
            cout << " " <<endl;
            cin >> opt;

            if (opt == 1) { 
                if (e.tieneEspacioParaNotas()) {
                    double n;
                    cout << "Valor de la nota: "; cin >> n;
                    e.getNotas().push_back(n);
                    cout << " " <<endl;
                } else {
                    cout << "Maximo de 7 notas alcanzado." << endl;
                    cout << " " <<endl;
                }
            } 
            else if (opt == 2) { 
                if (!e.getNotas().empty()) {
                    int idxNota;
                    cout << "Ingrese el numero de nota a eliminar (1 a " << e.getNotas().size() << "): ";
                    cout << " " <<endl;
                    cin >> idxNota;
                    e.eliminarNota(idxNota - 1);
                } else {
                    cout << "El estudiante no tiene notas registradas." << endl;
                    cout << " " <<endl;
                }
            }
        } while (opt != 3);
    } else {
        cout << "Cedula no encontrada. 1. Reintentar | 2. Menu Principal: ";
        cout << " " <<endl;
        int r; cin >> r; cin.ignore();
        if (r == 1) registroCalificaciones();
    }
}

void promedioIndividual() {
    string ced;
    cout << "Ingrese cedula: "; cin >> ced;
    int idx = buscarEstudiantePorCedula(ced);
    if (idx != -1) {
        cout << "Estudiante: " << listaEstudiantes[idx].getNombreCompleto() << endl;
        cout << "Promedio: " << fixed << setprecision(2) << listaEstudiantes[idx].calcularPromedio() << endl;
        cout << " " <<endl;
    } else {
        cout << "No encontrado." << endl;
        cout << " " <<endl;
    }
}

void promedioGeneral() {
    double sumaTotal = 0;
    int cantNotas = 0;
    for (int i = 0; i < listaEstudiantes.size(); i++) {
        vector<double>& notas = listaEstudiantes[i].getNotas();
        for (int j = 0; j < notas.size(); j++) {
            sumaTotal += notas[j];
            cantNotas++;
        }
    }
    if (cantNotas > 0){
	
        cout << "Promedio del curso: " << (sumaTotal / cantNotas) << endl;
        cout << " " <<endl;
    
	}else{
	
        cout << "No se han registrado calificaciones de estudiantes." << endl;
        cout << " " <<endl;
    }
}

int main() {
    int opcion;
    do {
        cout << "\n||||||=== GESTOR DE PERSONAS ===|||||" << endl;
        cout << "1 Estudiantes\n2 Registro de calificaciones\n";
        cout << "3 Determinar el promedio de notas de un estudiante\n";
        cout << "4 Determinar el promedio de notas del curso\n";
        cout << "0 Salir.\nTeclee su opcion (1-4): ";
        
        cin >> opcion; cin.ignore();
		cout << " " <<endl;
        switch (opcion) {
            case 1: gestionarEstudiantes(); break;
            case 2: registroCalificaciones(); break;
            case 3: promedioIndividual(); break;
            case 4: promedioGeneral(); break;
        }
    } while (opcion != 0);

    return 0;
}
