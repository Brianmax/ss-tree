def dibujar_laberinto(jugador_x, jugador_y):
    for i in range(0, recompensas.shape[0]):
        for j in range(0, recompensas.shape[1]):
            if recompensas[i, j] == -100:
                ventana.blit(img_muro, (j * size, i * size))
            if recompensas[i, j] == 100:
                ventana.blit(img_meta, (j * size, i * size))
    ventana.blit(img_jugador, (jugador_y * size, jugador_x * size))
