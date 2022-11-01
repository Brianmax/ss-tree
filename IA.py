# -------------------------------------------------------------------------
# Crack the Code
# Inteligencia Artificial con Python
# -------------------------------------------------------------------------
# Importar bibliotecas que se utilizarán - no modifiques esta sección
import cv2
import os
import numpy as np

# Carpeta con fotos de entrenamiento
dataPath = './data'
peopleList = os.listdir(dataPath)
print('Lista de personas: ', peopleList)

# -------------------------------------------------------------------------
# Escribe tu código aquí:

# Inicio de variables
labels = []
facesData = []
label = 0

# Usa ciclos for para leer todas las imágenes del set de entrenamiento
print('Leyendo las imágenes...')
for nameDir in peopleList:
    # Crea una ruta para cada carpeta en ./data
    personPath = dataPath + '/' + nameDir

    # Busca todos los archivos en cada una de las carpetas
    for fileName in os.listdir(personPath):
        print('Rostros: ', nameDir + '/' + fileName)

        # Agrega el label y la imagen del rostro a su arreglo correspondiente
        labels.append(label)
        facesData.append(cv2.imread(personPath + '/' + fileName, 0))

    # Incrementa label cuando se cambia de carpeta
    label = label + 1

# Crea el un objeto para el reconocedor de rostros
# noinspection PyUnresolvedReferences
face_recognizer = cv2.face.LBPHFaceRecognizer_create()

# Entrenando el reconocedor de rostros
print("Entrenando modelo...")
face_recognizer.train(facesData, np.array(labels))

# Almacenando el modelo obtenido
face_recognizer.write('modelo.xml')
print("Modelo almacenado.")
