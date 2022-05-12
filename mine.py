# -------------------------------------------------------------------------
# Crack the Code
# Inteligencia Artificial con Python
# -------------------------------------------------------------------------
# Importar bibliotecas que se utilizarán - no modifiques esta sección
import cv2
import os
from camera import getcamera

# Estructura del codigo - busca donde empezar tu código no modifiques el resto

# Encontrar nombres de las personas guardadas
dataPath = './data'
imagePaths = os.listdir(dataPath)
print('imagePaths=', imagePaths)

# Creando el modelo y leyendo el modelo
# noinspection PyUnresolvedReferences
face_recognizer = cv2.face.LBPHFaceRecognizer_create()
face_recognizer.read('modelo.xml')

# Crear clasificador de rostros
faceClassif = cv2.CascadeClassifier('rostros.xml')

# Abrir camara:
camera = getcamera()
cap = cv2.VideoCapture(camera, cv2.CAP_DSHOW)

# Utiliza la camara hasta que la tecla q es presionada
while True:
    # Toma una fotografía y la muestra en pantalla
    ret, frame = cap.read()

    # comprobar que exista una imagen
    if not ret:
        break

    # Crea una imagen en escala de grises a partir de la foto
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Crea una copia de la imagen en blanco y negro
    auxFrame = gray.copy()

    # Utiliza el detector en la imagen de escala de grises
    faces = faceClassif.detectMultiScale(gray, 1.3, 5)

    # -------------------------------------------------------------------------
    # Escribe tu código aquí:

    # Procesamiento por cada rostro reconocido
    for (x, y, w, h) in faces:

        # Extraer rostro de la imagen original
        rostro = auxFrame[y:y + h, x:x + w]

        # Modificar tamaño de la imagen (150x150)
        rostro = cv2.resize(rostro, (150, 150))

        # Utilizar el modelo entrenado para diferenciar el rostro
        result = face_recognizer.predict(rostro)

        # Anotar resultados numéricos en pantalla
        cv2.putText(frame, '{}'.format(result), (x, y - 5), 1, 1, (255, 255, 0))

        # Mostrar resultados escritos en pantalla
        if result[1] < 75:
            # Escribe el nombre de la persona identificada arriba de su rostro
            cv2.putText(frame, '{}'.format(imagePaths[result[0]]), (x, y - 25), 2, 1, (0, 255, 0))
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)  # Crea rectangulo verde
        else:
            # Escribe la palabra desconocido si no se identifica a ninguna persona
            cv2.putText(frame, 'Desconocido', (x, y - 20), 2, 1, (0, 0, 255))
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)  # Crea rectangulo rojo

    # -------------------------------------------------------------------------
    # No modifiques el codigo debajo de esta linea:
    cv2.imshow('frame', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# --------------------------------------------------------------------------
# Cierra la cámara y las ventanas - no borres estas lineas
# Deja estas lineas hasta abajo
cv2.destroyAllWindows()
cap.release()
