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
#headersCSV = ['Secuencial', 'Secuencial_improved','Paralela','Paralala_improved']
headersCSV = ['Secuencial', 'Secuencial_improved','Paralela']
with open('resultados.csv', 'w', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=headersCSV)
        writer.writeheader()

csvfile.close()
#iteracion trapezoidal_secuential
lista_secuencial=[]
for i in range(15):
    proceso = subprocess.run(['./trapezoidal_secuential.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)
    salto= proceso .stdout.find("\n")
    tiempo= proceso .stdout[0:salto]
    lista_secuencial.append(tiempo)
#iteracion trapezoidal_secuential_improved
lista_secuencial_improved=[]
for i in range(15):
    proceso = subprocess.run(['./trapezoidal_secuential_improved.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)
    salto= proceso .stdout.find("\n")
    tiempo= proceso .stdout[0:salto]
    lista_secuencial_improved.append(tiempo)
    
#iteracion trapezoidal_parallel
lista_trapezoidal_parallel=[]
for i in range(15):
    proceso = subprocess.run(['./trapecio_parallel.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)
    salto= proceso .stdout.find("\n")
    tiempo= proceso .stdout[0:salto]
    dict= {'Paralela':proceso}
    lista_trapezoidal_parallel.append(tiempo)

for i in range (15):
        dict= {'Secuencial':lista_secuencial[i],'Secuencial_improved':lista_secuencial_improved[i],
                'Paralela':lista_trapezoidal_parallel[i]
        }       
        with open('resultados.csv', 'a', newline='') as f_object:
                dictwriter_object = DictWriter(f_object, fieldnames=headersCSV)
                dictwriter_object.writerow(dict)
        f_object.close()

'''
#iteracion trapezoidal_parallel_improved
lista_trapezoidal_parallel_improved=[]
for i in range(15):
    proceso = subprocess.run(['./trapezoidal_parallel_improved.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)
    salto= proceso .stdout.find("\n")
    tiempo= proceso .stdout[0:salto]
    dict= {'Paralela_improved':proceso}
    with open('resultados.csv', 'a', newline='') as f_object:
        dictwriter_object = DictWriter(f_object, fieldnames=headersCSV)
        dictwriter_object.writerow(dict)
    f_object.close()
'''
    #guardar tiempos de ejecución
'''
    tiempo_secuencial=timeit.timeit('secuencial','from __main__ import secuencial')
    tiempo_paralela=timeit.timeit('paralela','from __main__ import paralela')
     '''
    #guardar en el archivo resultados

'''
    dict= {'Secuencial':tiempo_secuencial,'Secuencial_improved':tiempo_secuencial_improved,
                'Paralela':tiempo_paralela,'Paralela_improved':tiempo_paralela_improved}
    with open('resultados.csv', 'a', newline='') as f_object:
        dictwriter_object = DictWriter(f_object, fieldnames=headersCSV)
        dictwriter_object.writerow(dict)
       '''
