import subprocess
import csv
import timeit
from csv import DictWriter
# with open('output.txt', 'w') as f:
#     p1 = subprocess.run(["./hw.exe"],  stdout=f, text=True)

# p1 = subprocess.run(["./hw.exe"],  stdout=subprocess.PIPE, text=True)

# p1 = subprocess.run(['./trapezoidal_secuential.exe', ' < input'],  capture_output=True, text=True)

# print(p1.stderr)
# print(p1.args)
# print(p1.returncode)
# print(p1.stdout)

input = subprocess.run(['cat', 'input'], 
                        capture_output=True, 
                        text=True)

# print(input.stdout)

ditc= {}
headersCSV = ['Secuencial', 'Paralela']
with open('resultados.csv', 'w', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=headersCSV)
        writer.writeheader()

csvfile.close()

for i in range(30):
    secuencial = subprocess.run(['./trapezoidal_secuential.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)

    paralela = subprocess.run(['./trapezoidal_parallel.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)

    #print(program.stdout)
    salto_secuencial= secuencial.stdout.find("\n")
    cadena_secuencial= secuencial.stdout[0:salto_secuencial]


    salto_paralelo= paralela.stdout.find("\n")
    cadena_paralela= paralela.stdout[0:salto_paralelo]
    dict= {'Secuencial':cadena_secuencial,'Paralela':cadena_paralela}
    with open('resultados.csv', 'a', newline='') as f_object:
        dictwriter_object = DictWriter(f_object, fieldnames=headersCSV)
        dictwriter_object.writerow(dict)
       
f_object.close()
'''
print(timeit.timeit('secuencial','from __main__ import secuencial'))
print(timeit.timeit('paralela','from __main__ import paralela'))
'''