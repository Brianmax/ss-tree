# -------------------------------------------------------------------------
# Crack the Code
# Diseño de filtros con Python
# Sesión 4 - Crea tu propio filtro
# -------------------------------------------------------------------------
# Importar bibliotecas que se utilizarán - no modifiques esta sección
from imagenes import imshow
import cv2
import numpy as np

# -------------------------------------------------------------------------
# Escribe tu código aquí:

cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    cv2.imshow("Frame", frame)
    
    #Crear caricatura
    grises = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    #Crear bordes de la imagen binaria
    bordes = cv2.adaptiveThreshold(grises, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 2)
    cv2.imshow("bordes", bordes)
    
    #Limpiando bordes

    kernel = np.ones((3, 3), np.uint8)
    dilatacion = cv2.dilate(bordes, kernel)
    cv2.imshow("Dilatacion", dilatacion)

    #Ejemplo 3: Cambio de fondo
    #Creando una image binaria
    _, binaria = cv2.threshold(grises, 100, 255, cv2.THRESH_BINARY)
    binaria = cv2.bitwise_not(binaria)

    #Separar a la persona de la imagen original

    persona = np.zeros(frame.shape, np.uint8)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


# -------------------------------------------------------------------------
# Deja siempre este código hasta el final del archivo - no lo borres
# Este código sirve para mantener las ventas abiertas y
# cerrarlas cuando se presiona una tecla
cv2.waitKey(0)
cv2.destroyAllWindows()
