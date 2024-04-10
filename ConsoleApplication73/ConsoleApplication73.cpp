#include <iostream>
#include <string>
#include <cmath>
#include <bitset>

using namespace std;
void print(int num, int n) 
{
    string binario = bitset<32>(num).to_string().substr(32-n, n);
    cout<<binario<<endl;
}

int decimal_a_binario(int decimal, int n) 
{
    return decimal & ((1<<n)-1);
}

int complemento_2(int num, int n) 
{
    return (1<<n) - num;
}

int adicion_binaria(int num1, int num2, int n) 
{
    int resultado = num1+num2;
    return resultado & ((1<<n)-1);
}

int subtraccion_binaria(int minuendo, int subtraendo, int n) 
{
    subtraendo = complemento_2(subtraendo, n); 
    return adicion_binaria(minuendo, subtraendo, n);
}

int corrimiento_aritmetico(int num, int n) 
{
    int signo = (num>>(n-1))&1;
    int resultado = (num>>1)&((1<<(n-1))-1); 
    resultado = (signo<<(n-1)); 
    return resultado;
}

int multiplicacion(int multiplicando, int multiplicador, int n) 
{
    int M = multiplicando;
    int A = 0;
    int Q = multiplicador;
    int Q_1negativo = (Q<0) ? decimal_a_binario(-Q, n) : decimal_a_binario(Q, n);
    int S = (Q<0) ? decimal_a_binario(-M, n) : decimal_a_binario(M, n);
    int Qn_1 = 0;
    int Qn_2 = 0;

    for (int i = 0; i < n; i++) 
    {
        int Q_n = (Q>>(n-1-i))&1;
        if (Q_n == 1 && Qn_1 == 0) {
            A = subtraccion_binaria(A, S, n);
            A = corrimiento_aritmetico(A, n);
            Q = corrimiento_aritmetico(Q, n);
        }
        else if (Q_n == 0 && Qn_1 == 1) {
            A = adicion_binaria(A, S, n);
            A = corrimiento_aritmetico(A, n);
            Q = corrimiento_aritmetico(Q, n);
        }
        else if ((Q_n == 0 && Qn_1 == 0) || (Q_n == 1 && Qn_1 == 1)) {
            A = corrimiento_aritmetico(A, n);
            Q = corrimiento_aritmetico(Q, n);
        }
        Qn_1 = Q_n;
    }

    if (Q_1negativo & (1<<(n-1))){
        return complemento_2(A, n);
    }
    return A;
}

int main() 
{
    int n;
    int multiplicando;
    int multiplicador;
    cout << "Ingrese la cantida de bits: " <<endl; 
    cin >> n;
    cout << "Ingrese el multiplicando: " <<endl;
    cin >> multiplicando;
    cout << "Ingrese el multiplicador: " << endl;
    cin >> multiplicador;

    int resultado;
    resultado = multiplicacion(multiplicando, multiplicador, n);
    cout << "El resultado en decimal es: " << resultado << endl;
    cout << "El resultado en binario es: ";
    print(resultado, n);
    return 0;
}
