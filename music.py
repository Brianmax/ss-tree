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

cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

faceClassif = cv2.CascadeClassifier("rostros.xml")

contador = 0

while True:
    ret, frame = cap.read()

    if not ret:
        break

    frame = imutils.resize(frame, width=640)

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = faceClassif.detectMultiScale(gray,
                                         scaleFactor =  1.1,
                                         minNeighbors = 5,
                                         minSize = (120,120),
                                         maxSize = (1000, 1000))
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x,y), (x+w,y+h),(0,255, 0), 2)

        auxFrame = frame.copy()
        rostro = auxFrame[y:y+h, x:x+w]
        rostro = cv2.resize(rostro, (150,150),interpolation=cv2.INTER_CUBIC)

        cv2.imwrite(personPath+"/rostro_{}.jpg".format(contador), rostro)
        print("rostor_{}.jpg".format(contador) + " guardado")

        contador= contador + 1

    cv2.imshow("frame", frame)

    if contador >=300 or cv2.waitKey(1) & 0xFF == ord("q"):
        break

# --------------------------------------------------------------------------
# Cierra la cámara y las ventanas - no borres estas lineas
# Deja estas lineas hasta abajo
cv2.destroyAllWindows()
cap.release()
