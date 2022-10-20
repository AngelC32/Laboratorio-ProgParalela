// Algoritmo valido para funciones con coeficientes
// y constantes no mayores de 1 cifra

#include <iostream>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

int getPriority(char c);
bool isOperator(char c);
string to_polac(string inf_exp);
double do_op(char op, double a, double b);
double operate_exp(string exp, int x);

int main() {
	string str_inf_exp = "(3*X^2+2*x)r2";
	string str_polac_exp;
    double res;
    int x = 5;
    // cin >> str_inf_exp;

    str_polac_exp = to_polac(str_inf_exp);
    cout << str_polac_exp <<endl;

    res = operate_exp(str_polac_exp, x);
    cout << res;

	return 0;
}

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
}

bool isOperator(char c) {
	return c == '*' || c == '/' || c == '+' || c == '-' || 
			c == '^' || c == 'r' || c == 'l';
}

string to_polac(string inf_exp) {

    stack<char> stack_sign;
    stack<string> stack_op;

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
                char op = stack_sign.top();
                stack_sign.pop();

				// lo añadimos a la pila de salida como un bloque
                string tmp = op + op2 + op1;
                stack_op.push(tmp);
            }

            // Quita el '(' si hubiese uno
			if(!stack_sign.empty()) {
				stack_sign.pop();
			}
            
        }

        // Si no es operador lo agregamos al string de salida
        else if (!isOperator(c)) {
            stack_op.push(string(1, c));
        }

		//Si es operador
        else {
			// Ordenamos el operador entrante segun el orden de precedencia
            while(!stack_sign.empty() && 
				getPriority(c) <= getPriority(stack_sign.top())) {

                op1 = stack_op.top();
                stack_op.pop();
                op2 = stack_op.top();
                stack_op.pop();
                char op = stack_sign.top();
                stack_sign.pop();

                string tmp = op + op2 + op1;
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

        char op = stack_sign.top();
        stack_sign.pop();

        string tmp = op + op2 + op1;
        stack_op.push(tmp);
    }
 
	//devuelve todo el bloque armado
    return stack_op.top();
}

double do_op(char op, double a, double b) {
    switch (op) {
        case '+': return a + b; break;
        case '-': return a - b; break;
        case '*': return a * b; break;
        case '/': return a / b; break;
        case '^': return pow(a, b); break;
        case 'r': return pow(a, 1.0 / b); break;
        case 'l': return log(a) / log(b);
    }
}

double operate_exp(string exp, int x) {
    double op1, op2, res;
    stack<double> out_stack;
    char c;
    
    // Reemplazar variable
    for (int i=0; i < exp.length(); i++) {
        c = exp[i];

        if(c == 'x' || c == 'X') {
            exp[i] = (char) (x + 48);
        }
    }
    cout << exp<<endl;

    //Evaluar
    for (int i=exp.length()-1; i >= 0; i--) {
        c = exp[i];

        if(isOperator(c)) {
            op1 = out_stack.top();
            out_stack.pop();
            op2 = out_stack.top();
            out_stack.pop();

            res = do_op(c, op1, op2);
            out_stack.push(res);

        } else {
            out_stack.push(((double) c)- 48);
        }
    }

    return out_stack.top();
}
