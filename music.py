import discord
import clave
import random
from discord.ext import commands

bot = commands.Bot(command_prefix=">", description="Es un Bot de ayuda.")
n = 0
contador = 1
intentos = 10
palabra = ""
lista_letras = []


@bot.command()
async def adivina(contexto):
    global n
    n = random.randint(1, 10)
    await contexto.send("Adivina un numero entre 1 y 10.")

    print(n)


@bot.command()
async def num(contexto, num):
    global contador
    if num.isdigit():
        if int(num) != n:
            await contexto.send("Número equivocado")
            contador += 1
        else:
            await contexto.send("Felicidades, adivinaste el número en el intento {}".format(contador))
    else:
        await contexto.send("¡Ingrese un número!")


lista = ["Juventus", "Madrid", "Barcelona", "Manchester"]


@bot.command()
async def adivinaPalabras(contexto):
    global palabra
    global lista_letras
    palabra = random.choice(lista)
    lista_letras = []
    await contexto.send("La palabra a adivinar tiene {} letras.".format(len(palabra)))


@bot.command()
async def letra(contexto, ltr):
    global intentos
    global lista_letras
    status = ""
    if ltr.isalpha():
        lista_letras.append(ltr)
        if ltr in palabra:
            await contexto.send("La letra si esta en la palabra")
        else:
            intentos = intentos - 1
            await contexto.send("La letra no esta en la palabra")
    else:
        await contexto.send("Ingresa una letra!")

    for letra in palabra:
        if letra in lista_letras:
            status = status + letra
        else:
            status = status + "* "
    if status == palabra:
        await contexto.send("Felicidades, ganaste!")
    else:
        if intentos != 0:
            await contexto.send(status)
        else:
            await contexto.send("Ya no te quedan mas intentos")

bot.run(clave.tok)
