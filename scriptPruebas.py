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
headersCSV = ['Secuencial', 'Secuencial_improved','Paralela']
with open('resultados.csv', 'w', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=headersCSV)
        writer.writeheader()

csvfile.close()

for i in range(15):
    secuencial = subprocess.run(['./trapezoidal_secuential.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)

    secuencial_improved = subprocess.run(['./trapezoidal_secuential_improved.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)

    paralela = subprocess.run(['./trapezoidal_parallel.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)

    paralela_improved_v1 = subprocess.run(['./trapezoidal_parallel_improved_v1.exe'], 
                            capture_output=True, 
                            text=True, 
                            input=input.stdout)

    paralela_improved_v2 = subprocess.run(['./trapezoidal_parallel_improved_v2.exe'], 
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
    
    salto_paralelo_improved_v1= paralela_improved_v1.stdout.find("\n")
    tiempo_paralela_improved_v1= paralela_improved_v1.stdout[0:paralela_improved_v1]

    salto_paralelo_improved_v2= paralela_improved_v2.stdout.find("\n")
    tiempo_paralela_improved_v2= paralela_improved_v2.stdout[0:paralela_improved_v2]

    #guardar tiempos de ejecución
    '''
    tiempo_secuencial=timeit.timeit('secuencial','from __main__ import secuencial')
    tiempo_paralela=timeit.timeit('paralela','from __main__ import paralela')
     '''
    #guardar en el archivo resultados
    dict= {'Secuencial':tiempo_secuencial,'Secuencial_improved':tiempo_secuencial_improved,
                'Paralela':tiempo_paralela,'Paralela_improved_v1':tiempo_paralela_improved_v1,'Paralela_improved_v2':tiempo_paralela_improved_v2}
    with open('resultados.csv', 'a', newline='') as f_object:
        dictwriter_object = DictWriter(f_object, fieldnames=headersCSV)
        dictwriter_object.writerow(dict)
       
f_object.close()
