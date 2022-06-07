#Creando los botones uno por uno.
boton1 = Button(calculadora, text="1", width=5, height=2, command= lambda:click(1)) #el botón tendra un cierto número como texto, así como un ancho y alto específico.
boton2 = Button(calculadora, text="2", width=5, height=2, command= lambda:click(2))
boton3 = Button(calculadora, text="3", width=5, height=2, command= lambda:click(3))
boton4 = Button(calculadora, text="4", width=5, height=2, command= lambda:click(4))
boton5 = Button(calculadora, text="5", width=5, height=2, command= lambda:click(5))
boton6 = Button(calculadora, text="6", width=5, height=2, command= lambda:click(6))
boton7 = Button(calculadora, text="7", width=5, height=2, command= lambda:click(7))
boton8 = Button(calculadora, text="8", width=5, height=2, command= lambda:click(8))
boton9 = Button(calculadora, text="9", width=5, height=2, command= lambda:click(9))
boton0 = Button(calculadora, text="0", width=13, height=2, command= lambda:click(0))  #el botón del número 0 tendrá un ancho especial ya que irá al final de todo.

#Los botones especiales para borrar, añadir paréntesis y un punto decimal.
botonBorrar = Button(calculadora, text="⌫", width=5, height=2, command= lambda:borrar())
botonParentesis1 = Button(calculadora, text="(", width=5, height=2, command= lambda:click("("))
botonParentesis2 = Button(calculadora, text=")", width=5, height=2, command= lambda:click(")"))
botonPunto = Button(calculadora, text=".", width=5, height=2, command= lambda:click("."))

#Los botones de las operaciones matemáticas básicas.
botonDiv = Button(calculadora, text="÷", width=5, height=2, command= lambda:click("/"))
botonMult = Button(calculadora, text="×", width=5, height=2, command= lambda:click("*"))
botonSuma = Button(calculadora, text="+", width=5, height=2, command= lambda:click("+"))
botonResta = Button(calculadora, text="-", width=5, height=2, command= lambda:click("-"))
botonIgual = Button(calculadora, text="=", width=5, height=2, command= lambda:operacion())

#Ubicar los botones en la pantalla
#Agregando
botonBorrar.grid(row=1, column=0, padx=5, pady=5)
botonParentesis1.grid(row=1, column=1, padx=5, pady=5)
botonParentesis2.grid(row=1, column=2, padx=5, pady=5)
botonDiv.grid(row=1, column=3, padx=5, pady=5)

boton7.grid(row=2, column=0, padx=5, pady=5)
boton8.grid(row=2, column=1, padx=5, pady=5)
boton9.grid(row=2, column=2, padx=5, pady=5)
botonMult.grid(row=2, column=3, padx=5, pady=5)

boton4.grid(row=3, column=0, padx=5, pady=5)
boton5.grid(row=3, column=1, padx=5, pady=5)
boton6.grid(row=3, column=2, padx=5, pady=5)
botonResta.grid(row=3, column=3, padx=5, pady=5)

boton1.grid(row=4, column=0, padx=5, pady=5)
boton2.grid(row=4, column=1, padx=5, pady=5)
boton3.grid(row=4, column=2, padx=5, pady=5)
botonSuma.grid(row=4, column=3, padx=5, pady=5)

boton0.grid(row=5, column=0, columnspan=2, padx=5, pady=5)
botonPunto.grid(row=5, column=2, padx=5, pady=5)
botonIgual.grid(row=5, column=3, padx=5, pady=5)
