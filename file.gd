extends KinematicBody2D

# Variables que usaremos
export (int) var Velocidad
var movimiento

# Funcion de actualización por fotograma
func _process(delta):
	movimiento = Vector2()
	
	## Este codigo nos ayudarán a mover nuestro personaje por el nivel
	if Input.is_action_pressed("ui_right"):
		movimiento.x += 1
	
	############################################
	# Escribe debajo de esta linea el resto del código
	if Input.is_action_pressed("ui_left"):
		movimiento.x -= 1
	
	if Input.is_action_pressed("ui_up"):
		movimiento.y -= 1
	if Input.is_action_pressed("ui_down"):
		movimiento.y += 1
	
	if (movimiento.x <0):
		$AnimatedSprite.animation = "izquierda"
	elif (movimiento.x>0):
		$AnimatedSprite.animation = "derecha"
	
	
	
	
	
	

	# Este codigo nos ayuda a actualizar nuestro personaje utilizando física
	movimiento = movimiento.normalized() * Velocidad
	movimiento = move_and_slide(movimiento)
