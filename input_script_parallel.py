import subprocess

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

program = subprocess.run(['./trapezoidal_parallel.exe'], 
                        capture_output=True, 
                        text=True, 
                        input=input.stdout)

x=program.stdout.find("\n")
cadena=program.stdout[x+1:]
print(cadena)
with open('output_parallel.txt', 'w') as f:
    f.write(cadena)
f.close()