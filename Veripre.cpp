/*
  Nombre del archivo: Veripre.cpp
  Copyright (C) 2025 Mauricio Sebastian Araya Pavela (Mapzero)

  Este programa es software libre: puedes redistribuirlo y/o modificarlo
  bajo los términos de la Licencia Pública General Affero de GNU
  publicada por la Free Software Foundation versión 3.

  Este programa se distribuye con la esperanza de que sea útil,
  pero SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita
  de COMERCIALIZACIÓN o IDONEIDAD PARA UN PROPÓSITO PARTICULAR.

  Para más detalles, consulta la Licencia Pública General Affero de GNU.
  Puedes verla en: <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    char opcion;

    do {
        string presuncion;
        vector<string> sentencias;
        vector<char> respuestas;
        char respuesta;

        cout << "Escribe una presuncion: ";
        getline(cin, presuncion);

        // Recolectar sentencias y respuestas
        while (true) {
            cout << "Escribe una sentencia que asevere dicha presuncion: ";
            string sentencia;
            getline(cin, sentencia);
            sentencias.push_back(sentencia);

            cout << "¿Es la presuncion verdadera (v), falsa (f) o improbable (i)? (Escribe 'r' para ver el resultado): ";
            cin >> respuesta;
            cin.ignore(); // limpiar el buffer

            if (respuesta == 'v' || respuesta == 'f' || respuesta == 'i') {
                respuestas.push_back(respuesta);
            } else if (respuesta == 'r') {
                // Contar respuestas
                vector<int> v_idx, f_idx, i_idx;

                for (size_t i = 0; i < respuestas.size(); ++i) {
                    if (respuestas[i] == 'v') v_idx.push_back(i);
                    else if (respuestas[i] == 'f') f_idx.push_back(i);
                    else if (respuestas[i] == 'i') i_idx.push_back(i);
                }

                // Cancelar v y f mutuamente
                int cancel_count = min(v_idx.size(), f_idx.size());
                v_idx.resize(v_idx.size() - cancel_count);
                f_idx.resize(f_idx.size() - cancel_count);

                // Cancelar i si v mayor a f o viceversa
                if (v_idx.size() > f_idx.size()) {
                    int cancel_i = min(i_idx.size(), v_idx.size());
                    i_idx.resize(i_idx.size() - cancel_i);
                } else if (f_idx.size() > v_idx.size()) {
                    int cancel_i = min(i_idx.size(), f_idx.size());
                    i_idx.resize(i_idx.size() - cancel_i);
                }

                // Resultado basado en la mayoría
                if (v_idx.size() > f_idx.size() && v_idx.size() > i_idx.size()) {
                    cout << "\nLa premisa está cerca de la realidad.\n";
                    cout << "Estas fueron las sentencias que más se acercan:\n";
                    for (int idx : v_idx)
                        cout << "- " << sentencias[idx] << endl;
                } else if (f_idx.size() > v_idx.size() && f_idx.size() > i_idx.size()) {
                    cout << "\nLa premisa no se acerca a la realidad.\n";
                    cout << "Estas fueron las sentencias que más se acercan:\n";
                    for (int idx : f_idx)
                        cout << "- " << sentencias[idx] << endl;
                } else if (i_idx.size() > v_idx.size() && i_idx.size() > f_idx.size()) {
                    cout << "\nNo se puede determinar con precisión.\n";
                    cout << "Estas fueron las sentencias que más se acercan:\n";
                    for (int idx : i_idx)
                        cout << "- " << sentencias[idx] << endl;
                } else {
                    cout << "\nNo hay una tendencia que prevalezca en las respuestas.\n";
                }

                break;
            } else {
                cout << "Respuesta no válida. Intenta de nuevo.\n";
                sentencias.pop_back(); // Eliminar sentencia mal ingresada
            }
        }

        // Validar opción del usuario para continuar o salir
        while (true) {
            cout << "\nEscribe 's' para salir del programa o 'n' para nuevo análisis: ";
            cin >> opcion;
            cin.ignore();

            // Convertir a minúscula por si el usuario escribe 'S' o 'N'
            opcion = tolower(opcion);

            if (opcion == 's' || opcion == 'n') {
                break;
            } else {
                cout << "Opción no válida. Por favor escribe solo 's' o 'n'.\n";
            }
        }

    } while (opcion == 'n');

    // Mensaje de salida
    cout << "¡Gracias por usar el programa!\n";
    cout << "Presiona Enter para salir...";
	cin.get();
    return 0;
}
