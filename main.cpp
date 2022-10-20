#include <iostream>
#include <stack>
#include <string.h>
#include <cmath>


using namespace std;

// Prototipos de declaración de funciones
double eval(string notPolaca, double x);
string convPolaca(string function);
bool esOperador(char letra);
int prioridadEnPila(char operador);
int prioridadEnExpresion(char operador);

// Main function
int main()
{
    int a, b, err;
    string function;

    /*
    cout << "Ingrese el límite inferior del intervalo: " << endl;
    cin >> a;

    cout << "Ingrese el límite superior del intervalo: " << endl;
    cin >> b;

    cout << "Ingrese el error absoluto admisible: " << endl;
    cin >> err;
    
    cout << "Ingrese la función a evaluar: " << endl;
    cin >> function;
    */

    function = "2+3*4";
    cout<<"Notacion polaca de la funcion: " << convPolaca(function)<<endl;

    return 0;
}

// Evaluar notación polaca
double eval(string notPolaca, double x)
{
    double result;
    int i = 0;

    // Recorrer hasta que termine la cadena
    while (notPolaca[i] != '\0')
    {
        // Evaluar el caracter
        switch(notPolaca[i]){
            case '+':
                result = result + notPolaca[i+1];
                break;
            case '-':
                result = result - notPolaca[i+1];
                break;
            case '*':
                result = result * notPolaca[i+1];
                break;
            case '/':
                result = result / notPolaca[i+1];
                break;
            case '^':
                result = pow(result, notPolaca[i+1]);
                break;
            case 'r':
                result = sqrt(result);
                break;
            case 'l':
                result = log(result);
                break;
            default:
                result = notPolaca[i];
                break;
        }
        i++;
    }
    return result;
} 


// Conversor a notación polaca
string convPolaca(string function){
    string expression = "";
    stack<char> pila;
    
    while(!function.empty()){
        char letra = function[function.length() - 1];

        if(letra == ')'){
            pila.push(letra);
        }else{
            if(letra == '('){
                while(!strcmp(pila.top(), ")")){
                    expression += pila.top();
                    pila.pop();
                }
                pila.pop();
            }else{
                if(!esOperador(letra)){
                    expression += letra;
                }else{
                    while(
                        !pila.empty() && 
                        (
                            prioridadEnExpresion(letra) < prioridadEnPila(pila.top()))
                        ){
                        expression += pila.top();
                        pila.pop();
                    }
                    pila.push(letra);
                }
            }
        }
    }

    while(!pila.empty()){
        expression += pila.top();
        pila.pop();
    }


    // return expression inverse
    string expressionInverse = "";
    for(int i = expression.length() - 1; i >= 0; i--){
        expressionInverse += expression[i];
    }
    return expressionInverse;
}

bool esOperador(char letra){
    return letra == '+' 
    || letra == '-' 
    || letra == '*'
    || letra == '/'
    || letra == '^'
    || letra == 'r'
    || letra == 'l'
    || letra == '(';
}

int prioridadEnPila(char operador){
    switch(operador){
        case 'l': return 4;
        case 'r': return 3;
        case '^': return 3;
        case '*': return 2;
        case '/': return 2;
        case '+': return 1;
        case '-': return 1;
        case '(': return 0;
        default: return 0;
    }
}

int prioridadEnExpresion(char operador){
    switch(operador){
        case 'l': return 4;
        case 'r': return 4;
        case '^': return 4;
        case '*': return 2;
        case '/': return 2;
        case '+': return 1;
        case '-': return 1;
        case '(': return 5;
        default: return 0;
    }
}

