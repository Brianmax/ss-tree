import pygame

class Game:
    screen = None
    aliens = []
    rockets = []
    perdio = False
    gano = False

    def __init__(self, width, height, dificultad):
        pygame.init()
        self.width = width
        self.height = height
        self.screen = pygame.display.set_mode((width, height))
        self.clock = pygame.time.Clock()
        self.fondo = pygame.image.load("fondo.png")
        pygame.mixer.music.load("song.wav")
        pygame.mixer.music.play(-1)
        pygame.mixer.music.set_volume(0.2)
        done = False

        hero = Hero(self, width / 2, height - 20)
        generator = Generator(self, dificultad)
        rocket = None

        while not done:
            if len(self.aliens) == 0:
                self.gano = True
                self.displayText("Victory achieved")
            pressed = pygame.key.get_pressed()
            if pressed[pygame.K_LEFT]:
                hero.x -= 2 if hero.x > 20 else 0
            elif pressed[pygame.K_RIGHT]:
                hero.x += 2 if hero.x < width - 20 else 0
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    done = True
                if event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE and not self.perdio:
                    self.rockets.append(Rocket(self, hero.x, hero.y))

            pygame.display.flip()
            self.clock.tick(60)
            self.screen.blit(self.fondo, (0,0))
            for alien in self.aliens:
                alien.draw()
                alien.checkCollision(self)
                if (alien.y > height):
                    self.perdio = True
                    self.displayText("You died")

            for rocket in self.rockets:
                if not self.perdio:
                    rocket.draw()
                if rocket.y <= 0:
                    self.rockets.remove(rocket)
            if not self.perdio:
                hero.draw()


    def displayText(self, text):
            pygame.font.init()
            font = pygame.font.SysFont('Arial', 50)
            textsurface = font.render(text, False, (255, 255, 255))
            self.screen.blit(textsurface, (100, 160))




class Alien:
    def __init__(self, game, x, y, velocidad):
        self.x = x
        self.game = game
        self.y = y
        self.size = 30
        self.velocity = velocidad
        self.image = pygame.image.load("alien.png")

    def draw(self):
        #pygame.draw.rect(self.game.screen,
                         #(81, 43, 88),
                         #pygame.Rect(self.x, self.y, self.size, self.size))
        self.game.screen.blit(self.image, (self.x, self.y))
        self.y += self.velocity
    def checkCollision(self, game):
        for rocket in game.rockets:
            if (rocket.x < self.x + self.size and
                    rocket.x > self.x - self.size and
                    rocket.y < self.y + self.size and
                    rocket.y > self.y - self.size):
                game.rockets.remove(rocket)
                game.aliens.remove(self)


class Hero:
    def __init__(self, game, x, y):
        self.x = x
        self.game = game
        self.y = y
    def draw(self):
        pygame.draw.rect(self.game.screen,(210, 250, 251),pygame.Rect(self.x, self.y, 8, 5))


class Rocket:
    def __init__(self, game, x, y):
        self.x = x
        self.y = y
        self.game = game

    def draw(self):
        pygame.draw.rect(self.game.screen,
                         (254, 52, 110),
                         pygame.Rect(self.x, self.y, 2, 4))
        self.y -= 2


class Generator:
    def __init__(self, game, velocity):
        margin = 30
        width = 50
        for x in range(margin, game.width - margin, width):
            for y in range(margin, int(game.height / 2), width):
                game.aliens.append(Alien(game, x, y, velocity))


def easy():
    Game(600,400, 0.1)
def medium():
    Game(600, 400, 0.2)
def hard():
    Game(600, 400, 0.3)
if __name__ == '__main__':
    game = Game(600, 400, 0.8)
