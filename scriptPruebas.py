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
headersCSV = ['Secuencial', 'Secuencial_improved','Paralela','Paralala_improved']
with open('resultados.csv', 'w', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=headersCSV)
        writer.writeheader()

csvfile.close()
#iteracion trapezoidal_secuential
for i in range(15):
    secuencial = subprocess.run(['./trapezoidal_secuential.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)

#iteracion trapezoidal_secuential_improved
for i in range(15):
    secuencial_improved = subprocess.run(['./trapezoidal_secuential_improved.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)

#iteracion trapezoidal_parallel
for i in range(15):
    paralela = subprocess.run(['./trapezoidal_parallel.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)

#iteracion trapezoidal_parallel_improved
for i in range(15):
    paralela_improved = subprocess.run(['./trapezoidal_parallel_improved.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)

    # captura las primeras lineas de las salidas
    salto_secuencial= secuencial.stdout.find("\n")
    tiempo_secuencial= secuencial.stdout[0:salto_secuencial]

    salto_secuencial_improved = secuencial_improved.stdout.find("\n")
    tiempo_secuencial_improved = secuencial_improved.stdout[0:salto_secuencial_improved]

    salto_paralelo= paralela.stdout.find("\n")
    tiempo_paralela= paralela.stdout[0:salto_paralelo]
    
    salto_paralelo_improved= paralela_improved.stdout.find("\n")
    tiempo_paralela_improved= paralela_improved.stdout[0:paralela_improved]


    #guardar tiempos de ejecución
    '''
    tiempo_secuencial=timeit.timeit('secuencial','from __main__ import secuencial')
    tiempo_paralela=timeit.timeit('paralela','from __main__ import paralela')
     '''
    #guardar en el archivo resultados
    dict= {'Secuencial':tiempo_secuencial,'Secuencial_improved':tiempo_secuencial_improved,
                'Paralela':tiempo_paralela,'Paralela_improved':tiempo_paralela_improved}
    with open('resultados.csv', 'a', newline='') as f_object:
        dictwriter_object = DictWriter(f_object, fieldnames=headersCSV)
        dictwriter_object.writerow(dict)
       
f_object.close()
