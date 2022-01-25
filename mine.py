from ursina import *
from ursina.prefabs.first_person_controller import FirstPersonController
"""
class Boton_prueba(Button):
    def __init__(self):
        super().__init__(
            model = "circle",
            texture = "brick",
            color = color.red,
            highlight_color = color.blue,
            pressed_color = color.green
        )

    def input(self, tecla):
        if self.hovered:
            if tecla == "left mouse down":
                print("Hola")
test = Boton_prueba()
"""

app = Ursina()

grass_texture = load_texture('assets/grass_block.png')
stone_texture = load_texture('assets/stone_block.png')
dirt_texture = load_texture('assets/dirt_block.png')
brick_texture = load_texture('assets/brick_block.png')

class Voxel(Button):
    def __init__(self, position=(0,0,0), texture = grass_texture):
        super().__init__(
            parent = scene,
            position = position,
            model = "assets/block",
            origin_y = 0.5,
            texture = texture,
            color = color.white,
            scale = 0.5
        )

    def input(self, tecla):
        if self.hovered:
            if tecla == "left mouse down":
                Voxel(position = self.position + mouse.normal)



for z in range(20):
    for x in range(20):
        voxel = Voxel(position=(x,0,z))

player = FirstPersonController()


app.run()
