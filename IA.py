# -------------------------------------------------------------------------
# Crack the Code
# Inteligencia Artificial con Python
# Sesion 2 - Captura de datos
# -------------------------------------------------------------------------
# Importar bibliotecas que se utilizarán - no modifiques esta sección
import cv2
import os
import imutils
from camera import getcamera

# Crear carpeta de persona:
print('Escribe tu nombre: ')
personName = input()
dataPath = './data'
personPath = dataPath + '/' + personName

# Muestra acción a tomar dependiendo del nombre agregado
if os.path.exists(personPath):
    print('Persona ya registrada, sobreescribiendo datos...')
else:
    os.makedirs(personPath)
    print('Nueva persona, capturando datos...')

# -------------------------------------------------------------------------
# Escribe tu código aquí:

# Actividad 0: instalar imutils
# pip install imutils

# Actividad 1: copia el codigo de la sesion 1

# Abrir camara web
camera = getcamera()
cap = cv2.VideoCapture(camera, cv2.CAP_DSHOW)

# Carga el archivo para utilizar el detector de rostros
faceClassif = cv2.CascadeClassifier("rostros.xml")

# Actividad 3a: Inicia contador (para set de entrenamiento)
contador = 0

# Ciclo para tomar fotos de forma continua
while True:
    # Tomar fotografía
    ret, frame = cap.read()

    # Comprobar que exista una imagen
    if not ret:
        break

    # Actividad 2: Cambia el tamaño de la foto tomada
    frame = imutils.resize(frame, width=640)

    # Crea una imagen en escala de grises a partir de la foto
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Utiliza el detector en la imagen de escala de grises
    faces = faceClassif.detectMultiScale(gray,
                                         scaleFactor=1.1,
                                         minNeighbors=5,
                                         minSize=(120, 120),
                                         maxSize=(1000, 1000))

    # Ciclo por cada rostro detectado en la imagen
    for (x, y, w, h) in faces:
        # Dibuja un rectángulo al rededor del rostro
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

        # Actividad 4a: Crea una copia de la imagen
        auxFrame = frame.copy()

        # Actividad 4b: Obtiene el recuadro del rostro
        rostro = auxFrame[y:y + h, x:x + w]
        rostro = cv2.resize(rostro, (150, 150), interpolation=cv2.INTER_CUBIC)

        # Actividad 5: Guarda el rostro como imagen
        cv2.imwrite(personPath + '/rotro_{}.jpg'.format(contador), rostro)
        print('rotro_{}.jpg'.format(contador) + ' guardado')

        # Actividad 3b: Incrementa el contador de imagenes
        contador = contador + 1

    # Mostrar la imagen en pantalla
    cv2.imshow('frame', frame)

    # Espera a que toques una tecla para cerrar la ventana
    # Actividad 3c: termina el programa cuando el contador llegue a 300
    if contador >= 300 or cv2.waitKey(1) & 0xFF == ord('q'):
        break

# --------------------------------------------------------------------------
# Cierra la cámara y las ventanas - no borres estas lineas
# Deja estas lineas hasta abajo
cv2.destroyAllWindows()
cap.release()
