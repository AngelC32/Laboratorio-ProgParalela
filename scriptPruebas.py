import subprocess
import csv
from csv import DictWriter

input = subprocess.run(['cat', 'input'], 
                        capture_output=True, 
                        text=True)

dict= {}
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
    #guardar tiempos de ejecución
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
    #guardar tiempos de ejecución
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
    #guardar tiempos de ejecución
    tiempo= proceso .stdout[0:salto]
    dict= {'Paralela':proceso}
    lista_trapezoidal_parallel.append(tiempo)

for i in range (15):
        dict= {'Secuencial':lista_secuencial[i],'Secuencial_improved':lista_secuencial_improved[i],
                'Paralela':lista_trapezoidal_parallel[i]
        }       
         #guardar en el archivo resultados
        with open('resultados.csv', 'a', newline='') as f_object:
                dictwriter_object = DictWriter(f_object, fieldnames=headersCSV)
                dictwriter_object.writerow(dict)
        f_object.close()

    
   