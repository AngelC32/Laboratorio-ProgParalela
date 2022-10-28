#include <iostream>
#include <omp.h>
#include <string>
#include <stack>
#include <cmath>
#include <ctype.h>
#include <chrono>

using namespace std;

int getPriority(char c);
bool isOperator(char c);
string toPolacExp(string inf_exp);
double operateBinomialExp(char op, double a, double b);
double operatePolacExp(string exp, double x);
double getIntegralByTrapezoidRule(int a, int b, int n, string f);

/*
    Entradas:

        a b         --> intervalo
        err_abs_adm	--> error absoluto admisible
        str_func    --> funcion a integrar

    Salidas:

        gn          --> valor de la integral
        n           --> particiones necesarias (precision)
*/

int main() {
	string str_inf_exp, str_polac_exp;
    double err, err_abs_adm;
    double gn, gn_plus_one;
    int a, b, n=1;

    // INPUTS
    cin >> a >> b;
    cin >> err_abs_adm;
    cin >> str_inf_exp;

    str_polac_exp = toPolacExp(str_inf_exp);
    cout << "Expresión polaca: " << str_polac_exp << endl;
    auto start = chrono::steady_clock::now();
    // Calculo de la integral
    while(true) {
        gn = getIntegralByTrapezoidRule(a, b, n, str_polac_exp);
        gn_plus_one = getIntegralByTrapezoidRule(a, b, n+1, str_polac_exp);
        err = abs(gn_plus_one - gn);
        if(err < err_abs_adm) break;
        n++;
    }

    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;

	cout <<"Duración del cálculo: "<<  elapsed_seconds.count() <<endl;
    // OUTPUTS
    cout << gn <<endl;
    cout << n <<endl;
    //cout << " Duración del cálculo: " << elapsed_seconds.count() << endl;
	return 0;
}

/*
	Formula usada:
	
	 b
	S| f(x)dx  =~ (dx/2) * [f(x0) + 2f(x1) + ... + 2f(n-1) + f(xn)]
	 a
*/
double getIntegralByTrapezoidRule(int a, int b, int n, string f) {
    double sum=0, dx, xi[n-1]; 
    // Para n = 4
    // xi = [x1, x2, x3]

    dx = (float) (b - a)/n;

    // calculando los limites
    for(int i = 0; i < n-1; i++) {
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
int getPriority(char c) {
	switch (c) {
		case '(':
			return 0;
		case '+': case '-':
			return 1;
		case '*': case '/':
			return 2;
		case '^': case 'r': case 'l':
			return 3;
		default:
			return 4;
	}
	return 0;
}

// Es o no operador
bool isOperator(char c) {
	return c == '*' || c == '/' || c == '+' || c == '-' || 
			c == '^' || c == 'r' || c == 'l';
}

//Tansformación a expresion polaca(prefija)
string toPolacExp(string inf_exp) {

    stack<char> stack_sign;
    stack<string> stack_op;
	string num;

	char c;
	string op1, op2;

    for (int i=0; i < inf_exp.length(); i++) {
		
		c = inf_exp[i];

		// Todos los '(' entran en la pila
        if (c == '(') {
            stack_sign.push(c);
        }

        else if (c == ')') {
            while (!stack_sign.empty() && stack_sign.top() != '(') {
                //para mantener el orden de los operandos
			    op1 = stack_op.top();
                stack_op.pop();
                op2 = stack_op.top();
                stack_op.pop();
				
                string op = string(1, stack_sign.top());
                stack_sign.pop();

				// lo añadimos a la pila de salida como un bloque
                string tmp = op + " " + op2 + op1;
                stack_op.push(tmp);
            }

            // Quita el '(' si hubiese uno
			if(!stack_sign.empty()) {
				stack_sign.pop();
			}
            
        }

        // Si no es operador lo agregamos al string de salida
        else if (!isOperator(c)) {
            //Validar si existen numeros de mas de 1 cifra
            /*while ( isdigit(inf_exp[i]) || inf_exp[i] == '.' || 
                    inf_exp[i] == 'x' || inf_exp[i] == 'X') {*/

            while ( isdigit(inf_exp[i]) || inf_exp[i] == '.' || (!isOperator(inf_exp[i]) && isalpha(inf_exp[i]))) {
                num += string(1, inf_exp[i]);
                i++;
            }
            stack_op.push(num + " ");
            i--;        //devolviendo la posicion anterior al operador encontrado
            num = "";
        }

		//Si es operador
        else {
			// Ordenamos el operador entrante segun el orden de precedencia
            while(!stack_sign.empty() && 
				getPriority(c) < getPriority(stack_sign.top())) {

                op1 = stack_op.top();
                stack_op.pop();
                op2 = stack_op.top();
                stack_op.pop();
				
                string op = string(1, stack_sign.top());
                stack_sign.pop();

                string tmp = op + " " + op2 + op1;
                stack_op.push(tmp);
            }
			// Pusheamos el operador guardado tras el ordenamiento
            stack_sign.push(c);
        }
    }
 
    // Para validar signos faltantes
    while (!stack_sign.empty()) {
        op1 = stack_op.top();
        stack_op.pop();
        op2 = stack_op.top();
        stack_op.pop();

        string op = string(1, stack_sign.top());
        stack_sign.pop();

        string tmp = op + " " + op2 + op1;
        stack_op.push(tmp);
    }
 
	//devuelve todo el bloque armado
    return stack_op.top();
}

//Realiza una operación entre 2 numeros dados
double operateBinomialExp(char op, double a, double b) {
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
double operatePolacExp(string exp, double x) {
    double op1, op2, res;
    stack<double> out_stack;
	string num = "";
    char c;
    
    // Reemplazar variable
    for (int i=0; i < exp.length(); i++) {
        c = exp[i];

        // if(c == 'x' || c == 'X') {
        if(!isOperator(c) && isalpha(c)) {
            exp.replace(i, 1, to_string(x));
        }
    }

    //Evaluar
    for (int i=exp.length()-1; i >= 0; i--) {
        c = exp[i];

        if(isOperator(c)) {
            op1 = out_stack.top();
            out_stack.pop();
            op2 = out_stack.top();
            out_stack.pop();

            res = operateBinomialExp(c, op1, op2);
            out_stack.push(res);

        } else if (isdigit(c)) {
            while (exp[i] != ' ') {
                num = string(1, exp[i]) + num;
                i--;
            }
            out_stack.push(stod(num));       
            num = "";
        }
    }

    return out_stack.top();
}