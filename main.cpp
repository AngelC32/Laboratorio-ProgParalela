#include <iostream>
#include <stack>
#include <string.h>
#include <cmath>

using namespace std;

// Prototipos de declaración de funciones
double evalPolaca(string notPolaca);
double operacion(char letra, double num1, double num2);
bool esOperador(char letra);
int prioridadEnPila(char operador);
int prioridadEnExpresion(char operador);
string convPolaca(string function);

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

    function = "((21*2^3)-10)*2";
    
    string respuestaConv = convPolaca(function);
    cout<<"Notación polaca de la función: "<< respuestaConv << endl;
    double respuestaEval = evalPolaca(respuestaConv);
    cout<<"Evaluación de la notación polaca: " << respuestaEval <<endl;

    return 0;
}

// Evaluar notación polaca
double evalPolaca(string expPol){
    stack<char> pila;
    for(int i=expPol.length()-1; i>=0; i--){
        char letra = expPol[i];

        if(!esOperador(letra)){
            pila.push((double)letra - 48);
        }else{
            double num1 = (double)pila.top();
            pila.pop();
            double num2 = (double)pila.top();
            pila.pop();
            double num3 = operacion(letra, num1, num2);
            pila.push(num3);
        }
    }
    return (double)pila.top();
} 


// Conversor a notación polaca
string convPolaca(string function){
    string expression = "";
    stack<char> pila;
    
    while(!function.empty()){
        char letra = function[function.length() - 1];
        
        //Recortar la expresion
        function = function.substr(0, function.size() - 1);

        if(letra == ')'){
            pila.push(letra);
        }else{
            if(letra == '('){
                while( pila.top() != ')'){
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


// Funciones auxiliares
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

double operacion(char letra, double num1, double num2){
    switch(letra){
        case '*': return num1*num2;
        case '/': return num1/num2;
        case '+': return num1+num2;
        case '-': return num1-num2;
        case '^': return pow(num1,num2);
        // case 'r': return sqrt(num1*num2);
        // case 'l': return num1*num2;
        default: return 0;
    }
}

// create a new function

