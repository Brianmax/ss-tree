kernel = np.ones((3,3), np.uint8)
dilatacion = cv2.dilate(bordes, kernel)
cv2.imshow('Dilatacion', dilatacion)

#Camara y cambio de fondo

_, binaria = cv2.threshold(grises, 100, 255, cv2.THRESH_BINARY)
binaria = cv2.bitwise_not(binaria)

#separar la persona del fondo

persona = np.zeros(frame.shape, np.uint8)
for i in range(3):
persona[:, :, i] = cv2.bitwise_and(frame[:, :, i], binaria)
imshow('Persona', persona)

#Leer la imagen del fondo

fondo = cv2.imread("./img/fondo.jpg")
fondo = cv2.resize(fondo, binaria.shape[::-1])
