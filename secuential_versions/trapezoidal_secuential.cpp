#include <iostream>
#include <string>
#include <stack>
#include <bits/stdc++.h>
#include <cmath>
#include <vector>
#include <ctype.h>
#include <chrono>

using namespace std;

int getPriority(string operador);
bool isOperator(string operador);
vector <string> toPolacExp(vector <string> inf_exp);
double operateBinomialExp(char op, double a, double b);
double operatePolacExp(vector <string> exp, double var);
double getIntegralByTrapezoidRule(double a, double b, int n, vector <string> f);

/*
    Entradas:

        a b         --> intervalo
        err_abs_adm	--> error absoluto admisible
        str_func    --> funcion a integrar

    Salidas:

        gn         --> valor de la integral
        n           --> particiones necesarias (precision)
*/

int main() {
    string str_input="",concatenado="";
	vector <string>str_inf_exp,str_polac_exp;
    double err, err_abs_adm;
    double gn, gn_plus_one;
    int a, b, n=1;

    cin >> a >> b;
    cin >> err_abs_adm;
    cin >> str_input;
    //convierte la cadena a un vector de cadenas
    for(int i=0;i<str_input.size();i++){
        concatenado=string(1,str_input[i]);
        int prioridad1= getPriority(string(1,str_input[i]));
        //verifica si el caracter evaluado y el que le continua en la cadena, son operadores matematicos o parentesis
        if(isdigit(str_input[i])||str_input[i]=='.'||prioridad1==0){
            //si la prioridad es 0 solo se toman en cuenta digitos numericos y el punto decimal
            while(isdigit(str_input[i+1])||str_input[i+1]=='.'){
                concatenado=concatenado+string(1,str_input[i+1]);
                //itera al siguiente caracter de la cadena ingresada
                i++;
            }
            //se agrega al vector los numeros concatenados
            str_inf_exp.push_back(concatenado);
        }else{
            //se agrega al vector los operadores o parentesis ingresados
            str_inf_exp.push_back(concatenado);
        }
    }
    str_polac_exp = toPolacExp(str_inf_exp);
    auto start = chrono::steady_clock::now();
    while(true) {
        gn = getIntegralByTrapezoidRule(a, b, n, str_polac_exp);
        gn_plus_one = getIntegralByTrapezoidRule(a, b, n+1, str_polac_exp);
        err = abs(gn - gn_plus_one);

        if(err <= err_abs_adm) {
            break;
        }
        n++;
    }
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;

	cout << elapsed_seconds.count() <<endl;
    cout << gn <<endl;
    cout << n <<endl;

	return 0;
}

/*
	Formula usada:

	 b
	S| f(x)dx  =~ (dx/2) * [f(x0) + 2f(x1) + ... + 2f(n-1) + f(xn)]
	 a
*/


double getIntegralByTrapezoidRule(double a, double b, int n, vector <string> f) {
    double sum=0, dx, xi[n-1];

    dx = ((b - a)*1.0)/n;

    // calculando los limites
    for (int i = 0; i < n-1; i++) {
        xi[i] = a + ((i+1)*dx);
    }

    for (int i = 0; i < n-1; i++) {
        sum += 2*operatePolacExp(f, xi[i]);
    }

    sum += operatePolacExp(f, a) + operatePolacExp(f, b);
    sum *= dx/2;

    return sum;
}

// Obtiene la prioridad de las operaciones a ejecutar
int getPriority(string operador) {
    char c;
    c=operador[0];
	switch (c) {
		case '(': return -1;
		case '+': case '-':
			return 1;
		case '*': case '/':
			return 2;
		case '^': case 'r': case 'l':
			return 3;
		default:
			return 0;
	}
	return 0;
}

// Es o no operador
bool isOperator(string operador) {
    char c;
    c=operador[0];
	return c == '*' || c == '/' || c == '+' || c == '-' ||
			c == '^' || c == 'r' || c == 'l';
}

//Tansformación a expresion polaca
vector <string> toPolacExp(vector <string> inf_exp) {

    stack<string> stack_sign;
    vector<string> exp_convert;
	string num;

	string c;
    reverse(inf_exp.begin(), inf_exp.end());
    for (int i=0; i < inf_exp.size(); i++) {
		c = inf_exp[i];

		// Todos los ')' entran en la pila
        if (c == ")") {
            stack_sign.push(c);
        }

        else if (c == "(") {
            while (!stack_sign.empty() && stack_sign.top() != ")") {
                //para mantener el orden de los operandos
			    exp_convert.push_back(stack_sign.top());
                stack_sign.pop();
            }

            // Quita el '(' si hubiese uno
			if(!stack_sign.empty()) {
				stack_sign.pop();
			}

        }

        // Si no es operador lo agregamos al string de salida
        else if (!isOperator(c)) {
            exp_convert.push_back(c);
        }

		//Si es operador
        else {
			// Ordenamos el operador entrante segun el orden de precedencia
            while(!stack_sign.empty() &&
				getPriority(c) <=getPriority(stack_sign.top())) {

                exp_convert.push_back(stack_sign.top());
                stack_sign.pop();
            }
			// Pusheamos el operador guardado tras el ordenamiento
            stack_sign.push(c);
        }
    }

    // Para validar signos faltantes
    while (!stack_sign.empty()) {
        exp_convert.push_back(stack_sign.top());
        stack_sign.pop();
    }
    reverse(exp_convert.begin(), exp_convert.end());
	//devuelve todo el bloque armado
    return exp_convert;
}

//Realiza una operación entre 2 numeros dados
double operateBinomialExp(string operador, double a, double b) {
    char op=operador[0];
    switch (op) {
        case '+': return a + b; break;
        case '-': return a - b; break;
        case '*': return a * b; break;
        case '/': return a / b; break;
        case '^': return pow(a, b); break;
        case 'r': return pow(a, 1.0 / b); break;
        case 'l': return log(a) / log(b);
    }
	return 0;
}

//Opera a partir de una expresion polaca dada y una variable (opcional)
double operatePolacExp(vector <string> exp, double var) {
    double op1, op2, res;
    stack<double> out_stack;
    string c;
    double num;

    //Evaluar
    for (int i=exp.size()-1; i >= 0; i--) {
        c = exp[i];

        if(getPriority(c)>0) {
            op1 = out_stack.top();
            out_stack.pop();
            op2 = out_stack.top();
            out_stack.pop();

            res = operateBinomialExp(c, op1, op2);
            out_stack.push(res);

        } else if (isdigit(c[0])) {
			//arma los numeros en caso de ser > a 1 cifra
            num=atof(c.c_str());
            out_stack.push(num);

        } else if (isalpha(c[0])) { //validar variable
			out_stack.push(var);
		}
    }
    return out_stack.top();
}
