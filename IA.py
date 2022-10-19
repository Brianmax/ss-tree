from tkinter import *

ventana = Tk()
ventana.title("Calculadora")

i = 0

entradaT = Entry(ventana, font = ("Arial 18") )
entradaT.grid(row = 0, column=0, columnspan=4, padx=5, pady=5)

def click(valor):
    global i
    entradaT.insert(i, valor)
    i = i + 1

def borrar():
    entradaT.delete(0, END)
    i = 0

def operacion():
    ecuacion = entradaT.get()
    resultado = eval(ecuacion)
    entradaT.delete(0,END)
    entradaT.insert(0, resultado)
    i = 0
