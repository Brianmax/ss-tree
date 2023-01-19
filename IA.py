# Sesión 3: Entrenamiento

# Se crea una tabla con los valores Q (Q, de calidad en ingles "quality") que nos van a ayudar a decidir cual es la
# mejor acción en cada casilla. Por eso vamos a tener 4 valores por cada fila y columna del laberinto (uno por cada
# acción.
valores_q = np.zeros((filas, columnas, 4))

# Parametros del entrenamiento
exploracion = 0.1   # Es un porcentaje de veces que vamos a probar algo nuevo (dejalo menor a 0.2 - 20%)
descuento = 0.9  # Es un porcentaje con el que vamos a  de las recompensas futuras
aprendizaje = 0.9  # Es la velocidad de aprendizaje, es decir, que tanto


# Es una función que nos ayuda a explorar nuevas posibilidades o a utilizar el conocimiento que ya tenemos
# para ello utiliza el parametro explorar, el cual es un porcentaje que nos ayuda a decidir que tantas veces vamos
# a utilizar valores al azar y cuantas veces vamos a usar las mejores respuestas que tenemos
def siguiente_accion(fila_actual, columna_actual, explorar):
    # if a randomly chosen value between 0 and 1 is less than epsilon,
    # then choose the most promising value from the Q-table for this state.
    if np.random.random() > explorar:
        # Se usa la funcion argmax para descubrir la mejor acción (el número más alto)
        return np.argmax(valores_q[fila_actual, columna_actual])
    else:
        # Se usa la funcion random para elegir un numero aleatorio
        return np.random.randint(4)


# -------------------------------------------------------------------------
# JUEGO - Este parte del código se modificará sesión a sesión

# Entrena tu inteligencia artificial haciendo que resuelva el laberinto 1000 veces
for episode in range(1000):
    # Elegir punto inicial del juego al azar
    x, y = punto_inicial()

    # Este ciclo va a mantener el juego abierto para poder intefactuar con el laberinto
    while True:
        # Guardar posición anterior
        x_anterior = x
        y_anterior = y

        # Accion al azar usando la función siguiente_accion
        accion = siguiente_accion(x, y, exploracion)

        # Calcular siguiente punto
        x, y = punto_siguiente(x, y, accion)

        # Obtener valor q actual para esa accion en la posición anterior
        valor_q_actual = valores_q[x_anterior, y_anterior, accion]

        # Calcular nuevo valor q
        recompensa = recompensas[x, y]
        temporal_difference = recompensa + (descuento * np.max(valores_q[x, y, :])) - valor_q_actual
        nuevo_valor_q = valor_q_actual + (aprendizaje * temporal_difference)

        # Actualizar nuevo valor q
        valores_q[x_anterior, y_anterior, accion] = nuevo_valor_q
        # Espera y fondo
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

print('¡Entrenamiento completado!')


# -------------------------------------------------------------------------
# Sesión 4 - Resultados del entrenamiento

# Define una función que va a elegir siempre el camino más corto entre un punto inicial y la meta
def camino_mas_corto(inicio_x, inicio_y):
    # No continuar si el punto inicial no es válido
    if fin_del_juego(inicio_x, inicio_y):
        return []

    # Empezar a guardar el camino
    fila_actual, columna_actual = inicio_x, inicio_y
    camino = [[fila_actual, columna_actual]]

    # Continua buscando el siguiente paso hasta llegar a la meta.
    while not fin_del_juego(fila_actual, columna_actual):
        # Obten de la tabla q la mejor acción posible para dicha posicion
        accion_actual = siguiente_accion(fila_actual, columna_actual, 0.)

        # Muevete a la siguigiente posicición
        fila_actual, columna_actual = punto_siguiente(fila_actual, columna_actual, accion_actual)

        # Guarda el valor el nuevo valor en el arreglo
        camino.append([fila_actual, columna_actual])

    # Regresa el camino completo de la posición inicial a la meta
    return camino


# Dibuja el camino más corto desde una posición hasta la meta
def dibuja_camino_mas_corto(inicio_x, inicio_y):
    # Obten el camino más corto
    camino = camino_mas_corto(inicio_x, inicio_y)

    # Dibuja posición por posición el camino más corto
    for i, j in camino:
        dibujar_laberinto(i, j)
        ventana.fill((0, 0, 0))
        dibujar_laberinto(i, j)
        pygame.display.flip()
        sleep(0.1)


# Prueba tu inteligencia artificial para resolver el laberinto desde varias posiciones iniciales
for ejemplo in range(3):
    x, y = punto_inicial()
    dibuja_camino_mas_corto(x, y)


# -------------------------------------------------------------------------
# No borres esta linea, deja esto siempre hasta el final
# Cierra el juego
pygame.quit()
