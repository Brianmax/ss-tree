# -------------------------------------------------------------------------
# Crack the Code
# Aprendizaje por reforzamiento
# -------------------------------------------------------------------------
# Importar bibliotecas que se utilizarán - no modifiques esta sección
import pygame
from pygame.locals import *
import numpy as np
from time import sleep
import laberintos

# -------------------------------------------------------------------------
# Sesión 1: Laberintos, acciones y recompensas

# Recompensas - Elige un laberinto para utilizarlo
recompensas = laberintos.laberinto_1

# Tamaño del laberinto (recompensas)
filas = recompensas.shape[0]
columnas = recompensas.shape[1]

# Tamanos de imagen y ventana
size = 32  # Es el tamano de las imagenes (jugador.jpg, meta.jpg, muro.jpg)
ventana_alto = columnas * size
ventana_ancho = filas * size

# Iniciar pygame y crear ventana
pygame.init()
ventana = pygame.display.set_mode((ventana_alto, ventana_ancho), pygame.HWSURFACE)

# Cargar imagenes del muro, jugador y la meta
img_muro = pygame.image.load("Imagenes/Muro.jpg").convert()
img_jugador = pygame.image.load("Imagenes/Jugador.jpg").convert()
img_meta = pygame.image.load("Imagenes/Meta.jpg").convert()


# Función para dibujar el estado actual del laberinto y la posición del jugador
def dibujar_laberinto(jugador_x, jugador_y):
    for i in range(0, recompensas.shape[0]):
        for j in range(0, recompensas.shape[1]):
            if recompensas[i, j] == -100:
                ventana.blit(img_muro, (j * size, i * size))
            if recompensas[i, j] == 100:
                ventana.blit(img_meta, (j * size, i * size))
    ventana.blit(img_jugador, (jugador_y * size, jugador_x * size))


# -------------------------------------------------------------------------
# Sesión 2: Fin del juego, punto inicial y punto siguiente

# Define la condición final
# Si la recompensa es -1 (es una casilla vacia) entonces el juego sigue
# Si choca con un muro (pierde) o llega a la meta (gana) el juego termina
def fin_del_juego(fila_actual, columna_actual):
    if recompensas[fila_actual, columna_actual] == -1.:
        return False
    else:
        return True


# Inicia el juego desde una posición aleatoria
def punto_inicial():
    while True:
        # Busca un valor de fila y columna donde empezar el juego
        fila_actual = np.random.randint(filas)
        columna_actual = np.random.randint(columnas)

        # Si la posición elegida no es un muro o la meta deten la búsqueda y utiliza ese valor
        if not fin_del_juego(fila_actual, columna_actual):
            break

    # Regresa el resultado encontrado
    return fila_actual, columna_actual


# Esta función nos ayuda a elegir una acción facilmente y calcular la nueva posición utilizando solo un numero
def punto_siguiente(fila_actual, columna_actual, indice_de_accion):
    # Se guardan los valores actuales
    nueva_fila = fila_actual
    nueva_columna = columna_actual

    # Acciones: 0 = arriba, 1 = derecha, 2 = abajo, 3 = izquierda
    acciones = ['arriba', 'derecha', 'abajo', 'izquierda']

    # Después se modifica la fila o la columna que corresponde a la acción
    if acciones[indice_de_accion] == 'arriba' and fila_actual > 0:
        nueva_fila -= 1
    elif acciones[indice_de_accion] == 'derecha' and columna_actual < columnas - 1:
        nueva_columna += 1
    elif acciones[indice_de_accion] == 'abajo' and fila_actual < filas - 1:
        nueva_fila += 1
    elif acciones[indice_de_accion] == 'izquierda' and columna_actual > 0:
        nueva_columna -= 1

    # Y al final se devuelve la nueva posicion
    return nueva_fila, nueva_columna


# -------------------------------------------------------------------------
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
