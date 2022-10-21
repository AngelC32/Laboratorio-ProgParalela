#include <iostream>
#include <string>
#include <stack>
#include <bits/stdc++.h>
#include <cmath>
#include <vector>

using namespace std;
int obtener_prioridad(string operador);
vector <string> convertirA_Polaca(vector <string> exp_infija);
float evaluar_expresion(vector <string> exp);

int main(){

    string expresion="",concatenado="",x;
    cout<<"f(x)=";
    //expresion="4+4^2";
    // expresion="2*(1+(4*(2+1)+3))";
    //expresion="3*(1+3^4)";
    // expresion="(2*x^3)+25";
    // expresion="25+(2*3^3)";s
    cin>>expresion;
    cout<<"x=";
    cin>>x;
    expresion.replace(expresion.find("x"),1, x);
    //vector de tipo string que contendrá los caracteres de la cadena de entrada
    vector <string> expresion_convertida,expresion_prefija;

    //convierte la cadena a un vector de cadenas
    for(int i=0;i<expresion.size();i++){
        concatenado=string(1,expresion[i]);
        int prioridad1= obtener_prioridad(string(1,expresion[i]));
        int prioridad2= obtener_prioridad(string(1,expresion[i+1]));
        //verifica si el caracter evaluado y el que le continua en la cadena, son operadores matematicos o parentesis
        if(isdigit(expresion[i])||expresion[i]=='.'){
            //si la prioridad es 0 solo se toman en cuenta digitos numericos y el punto decimal
            while(isdigit(expresion[i+1])||expresion[i+1]=='.'){
                concatenado=concatenado+string(1,expresion[i+1]);
                //itera al siguiente caracter de la cadena ingresada
                i++;
            }
            //se agrega al vector los numeros concatenados
            expresion_convertida.push_back(concatenado);
        }else{
            //se agrega al vector los operadores o parentesis ingresados
            expresion_convertida.push_back(concatenado);
        }
    }

    expresion_prefija=(convertirA_Polaca(expresion_convertida));
    for(int i=0;i<expresion_prefija.size();i++){
        cout<<expresion_prefija[i];
    }
    float resultado = evaluar_expresion(expresion_prefija);
    cout<<"\nResultado: "<<resultado;
}
int obtener_prioridad(string operador){
    char caracter;
    // convierte el string ingresado en un caracter, para poder evaluarlo en el switch
    // en el caso de numeros de más de una cifra se toma la primera
    caracter=operador[0];
    switch(caracter){
        case '^': return 4;
        case '*':
        case '/': return 3;
        case '+':
        case '-': return 2;
        case '(': return -1;
        case ')': return 1;
        default: return 0;
    }
}
vector <string>convertirA_Polaca(vector <string> exp){ //notacion polaca es notacion prefija
    stack <string> pila_operadores;
    vector <string> exp_convertido;
    //invirtiendo la expresion infija
    reverse(exp.begin(), exp.end());
    //recorriendo los strings almacenados en el vector
    for(int i=0;i<exp.size();i++){
        //si el caracter no es operador matematico
        if(obtener_prioridad(exp[i])<=1){
            //si el caracter es parentesis empuja a la pila
            if(obtener_prioridad(exp[i])==1){
                pila_operadores.push(exp[i]);
            }
            else if(exp[i]=="("){
                //mientras que la pila no este vacia o no encuentre un parantesis cerrado
                while(!pila_operadores.empty()&&obtener_prioridad(pila_operadores.top())!=1){
                        exp_convertido.push_back(pila_operadores.top());
                        pila_operadores.pop();
                }
                pila_operadores.pop();// elmina el parentesis cerrado
            }
            //si el caracter es un numero concatena a la cadena salida
            else if(obtener_prioridad(exp[i])==0){
                exp_convertido.push_back(exp[i]);
            }
        }
        else{
            if(!pila_operadores.empty()){
                //si la prioridad del caracter o string es menor o igual que el de la pila
                if(obtener_prioridad(exp[i])<=obtener_prioridad(pila_operadores.top())){
                    //desapila hasta que la prioridad del elemento sea menor o igual que el caracter o string del vector
                    while(!pila_operadores.empty()&&obtener_prioridad(exp[i])<obtener_prioridad(pila_operadores.top())){
                        exp_convertido.push_back(pila_operadores.top());
                        pila_operadores.pop();
                    }
                }
            }
            pila_operadores.push(exp[i]);
        }
    }
    //desapila los elementos que faltan
    while(!pila_operadores.empty()){
        exp_convertido.push_back(pila_operadores.top());
        pila_operadores.pop();
    }
    reverse(exp_convertido.begin(), exp_convertido.end());
    return exp_convertido;
}
float evaluar_expresion(vector <string> exp){
    stack<float> pila_operacion;
    reverse(exp.begin(), exp.end());
    float num1,num2,resultado,numero_convertido;
    for(int i=0;i<exp.size();i++){
        char caracter;
         if(exp[i].size()>1){
             caracter=exp[i][exp[i].size()-1];
        }else{
             caracter=exp[i][0];
        }
        switch(caracter){
            case '^':
                num1=pila_operacion.top();
                pila_operacion.pop();
                num2=pila_operacion.top();
                pila_operacion.pop();
                resultado=pow(num1,num2);
                pila_operacion.push(resultado);
                break;
            case '*':
                num1=pila_operacion.top();
                pila_operacion.pop();
                num2=pila_operacion.top();
                pila_operacion.pop();
                resultado=num1*num2;
                pila_operacion.push(resultado);
                break;
            case '/':
                num1=pila_operacion.top();
                pila_operacion.pop();
                num2=pila_operacion.top();
                pila_operacion.pop();
                resultado=num1/num2;
                pila_operacion.push(resultado);
                break;
            case '+':
                num1=pila_operacion.top();
                pila_operacion.pop();
                num2=pila_operacion.top();
                pila_operacion.pop();
                resultado=num1+num2;
                pila_operacion.push(resultado);
                break;
            case '-':
                num1=pila_operacion.top();
                pila_operacion.pop();
                num2=pila_operacion.top();
                pila_operacion.pop();
                resultado=num1-num2;
                pila_operacion.push(resultado);
                break;
            default:
                numero_convertido=atof(exp[i].c_str());
                pila_operacion.push(numero_convertido);
                break;
        }
    }
    resultado= pila_operacion.top();
    pila_operacion.pop();
    return resultado;
}
