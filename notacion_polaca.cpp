#include <iostream>
#include <string>
#include <stack>
#include <bits/stdc++.h>
#include <cmath>
#include <stdlib.h>

using namespace std;
int obtener_prioridad(char operador);
string convertirA_Polaca(string exp_infija);
float evaluar_expresion(string exp);

int main(){

    //string expresion="2*(1+(4*(2+1)+3))";
    //string expresion="3*(1+3^4)";
    string expresion;
    cin>>expresion;
    string expresion_prefija;
    expresion_prefija=(convertirA_Polaca(expresion));
    cout<<expresion_prefija<<endl;
    float resultado = evaluar_expresion(expresion_prefija);
    cout<<"Resultado:"<<resultado;
}
int obtener_prioridad(char operador){
    switch(operador){
        case '^': return 4;
        case '*':
        case '/': return 3;
        case '+':
        case '-': return 2;
        case ')': return 1;
        default: return 0;
    }
}
string convertirA_Polaca(string exp){ //notacion polaca es notacion prefija
    stack <char> pila_operadores;
    string exp_convertido="";
    //invirtiendo la expresion infija
    reverse(exp.begin(), exp.end());
    //recorriendo los caracteres del string
    int prioridad=0;
    for(int i=0;i<exp.size();i++){
        //si el caracter no es operador matematico
        if(obtener_prioridad(exp[i])<=1){
            //si el caracter es parentesis empuja a la pila
            if(obtener_prioridad(exp[i])==1){
                pila_operadores.push(exp[i]);
            }
            else if(exp[i]=='('){
                //mientras que la pila no este vacia o no encuentre un parantesis cerrado
                while(!pila_operadores.empty()&&obtener_prioridad(pila_operadores.top())!=1){
                        exp_convertido=exp_convertido+pila_operadores.top();
                        pila_operadores.pop();
                }
                pila_operadores.pop();// elmina el parentesis cerrado
            }
            //si el caracter es un numero concatena a la cadena salida
            else if(obtener_prioridad(exp[i])==0){
                exp_convertido=exp_convertido+exp[i];
            }
        }
        else{
            if(!pila_operadores.empty()){
                if(obtener_prioridad(exp[i])<=obtener_prioridad(pila_operadores.top())){
                    while(!pila_operadores.empty()&&obtener_prioridad(exp[i])<obtener_prioridad(pila_operadores.top())){
                        exp_convertido=exp_convertido+pila_operadores.top();
                        pila_operadores.pop();
                    }
                }
            }
            pila_operadores.push(exp[i]);
        }
    }
    while(!pila_operadores.empty()){
        exp_convertido=exp_convertido+pila_operadores.top();
        pila_operadores.pop();
    }
    reverse(exp_convertido.begin(), exp_convertido.end());
    return exp_convertido;
}
float evaluar_expresion(string exp){
    stack<float> pila_operacion;
    reverse(exp.begin(), exp.end());
    float num1,num2,resultado,numero_convertido;
    for(int i=0;i<exp.size();i++){
        switch(exp[i]){
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
                numero_convertido=atof(string(1,exp[i]).c_str());
                pila_operacion.push(numero_convertido);
        }
    }
    resultado= pila_operacion.top();
    pila_operacion.pop();
    return resultado;
}
