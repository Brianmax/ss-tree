import pygame

class Game:
    screen = None
    aliens = []

    def __init__(self, width, height):
        pygame.init()
        self.width = width
        self.height = height
        self.screen = pygame.display.set_mode((width, height))
        self.clock = pygame.time.Clock()
        done = False

        hero = Hero(self, width / 2, height - 20)

        while not done:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    done = True
            pygame.display.flip()
            self.clock.tick(60)
            self.screen.fill((0,0,0))

class Alien:
    def __init__(self, game, pos_x, pos_y):
        self.game = game
        self.pos_x = pos_x
        self.pos_y = pos_y
        self.size = 30

    def draw(self):
        pygame.draw.rect(self.game.screen, (81,43,88),
                         pygame.Rect(self.pos_x, self.pos_y, self.size,self.size))


class Hero:
    def __init__(self, game, pos_x, pos_y):
        self.game = game
        self.pos_x = pos_x
        self.pos_y = pos_y
        self.size = 5

    def draw(self):
        pygame.draw.rect(self.game.screen, (210,250,251),
                         pygame.Rect(self.pos_x, self.pos_y, self.size,self.size))

class Generator:
    def __init__(self, game):
        margin = 30
        width = 50
        for x in range(margin, game.width-margin, width):
            for y in range(margin, int(game.height/2), width):
                game.aliens.append(Alien(game, x, y))
