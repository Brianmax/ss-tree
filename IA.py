# -------------------------------------------------------------------------
# Sesión 3: Entrenamiento

# Tabla con los valores Q y parametros del entrenamiento
# Escribe aquí tu codigo


# Es una función que nos ayuda a explorar nuevas posibilidades o a utilizar el conocimiento que ya tenemos
# para ello utiliza el parametro explorar, el cual es un porcentaje que nos ayuda a decidir que tantas veces vamos
# a utilizar valores al azar y cuantas veces vamos a usar las mejores respuestas que tenemos
def siguiente_accion(fila_actual, columna_actual, explorar):
    # Escribe aquí tu código
    pass


# -------------------------------------------------------------------------
# JUEGO - Este parte del código se modificará sesión a sesión

# Elegir punto inicial del juego al azar
x, y = punto_inicial()

# Ciclo para mantener el juego abierto y poder intefactuar con el
while True:
    # Accion al azar usando la función punto_siguiente
    accion = np.random.randint(4)

    # Calcular siguiente punto
    x, y = punto_siguiente(x, y, accion)

    # Espera y fondo
    sleep(0.4)  # Dejar mas tiempo para poder ver los resultados
    ventana.fill((0, 0, 0))

    # Diujar laberinto
    dibujar_laberinto(x, y)
    pygame.display.flip()

    # Condición del fin del juego
    if fin_del_juego(x, y):
        if recompensas[x, y] == 100:
            print("¡Has ganado!")
        else:
            print("¡Has perdido!")
        break


# -------------------------------------------------------------------------
# Sesión 4 - Resultados del entrenamiento

# Define una función que va a elegir siempre el camino más corto entre un punto inicial y la meta
def camino_mas_corto(inicio_x, inicio_y):
    # Escribe aquí tu codigo
    pass


# Dibuja el camino más corto desde una posición hasta la meta
def dibuja_camino_mas_corto(inicio_x, inicio_y):
    # Escribe aquí tu codigo
    pass


# Prueba tu inteligencia artificial para resolver el laberinto desde varias posiciones iniciales
# Escribe aquí tu codigo


# -------------------------------------------------------------------------
# No borres esta linea, deja esto siempre hasta el final
# Cierra el juego
pygame.quit()
