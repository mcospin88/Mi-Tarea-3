# Variable Swap en Python
# Demostración correcta e incorrecta

# Versión INCORRECTA (intento manual que falla)
print("=== Versión Incorrecta ===")
a = 10
b = 20
print(f"Valores iniciales -> a = {a}, b = {b}")
print(f"Direcciones iniciales -> a: {id(a)}, b: {id(b)}")

# Intento fallido: asignar directo sin variable temporal
a = b
b = a
print(f"Después del 'swap incorrecto' -> a = {a}, b = {b}")
print(f"Direcciones después -> a: {id(a)}, b: {id(b)}\n")

# Versión CORRECTA (usando variable temporal)
print("=== Versión Correcta ===")
a = 10
b = 20
print(f"Valores iniciales -> a = {a}, b = {b}")
print(f"Direcciones iniciales -> a: {id(a)}, b: {id(b)}")

# Usando variable temporal
temp = a
a = b
b = temp
print(f"Después del swap correcto -> a = {a}, b = {b}")
print(f"Direcciones después -> a: {id(a)}, b: {id(b)}\n")

# Versión Pythonica (extra, usando tuple unpacking)
print("=== Versión Pythonica ===")
a, b = 10, 20
print(f"Valores iniciales -> a = {a}, b = {b}")
print(f"Direcciones iniciales -> a: {id(a)}, b: {id(b)}")

a, b = b, a
print(f"Después del swap pythonico -> a = {a}, b = {b}")
print(f"Direcciones después -> a: {id(a)}, b: {id(b)}")