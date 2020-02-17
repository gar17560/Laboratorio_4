#Laboratorio 3
#Electrónica Digital 2
#Miguel García   17560


from tkinter import *
import serial
import time
import sys


#----------------------------------------------------------------
puerto = 'COM3'
ser = serial.Serial(port = puerto, baudrate = 9600,
                    parity = serial.PARITY_NONE,
                    stopbits = serial.STOPBITS_ONE,
                    bytesize = serial. EIGHTBITS, timeout = 0)
#-----------------------------------------------------------------
color_fondo = '#DCDCDC'
voltaje1 = 0
voltaje2 = 0
voltaje3 = 250


    
#------------------------------------------------------------
def gra1():
    global voltaje3
    if voltaje3 < 255:
        voltaje3 = voltaje3 + 1
    voltaje_3.config(text = str(voltaje3))
    numero = int(voltaje3)
    numero = numero.to_bytes(1,'little')
    ser.write(numero)
    ser.flushOutput()
    print(str(voltaje3))
    ventana.update()
    time.sleep(.05)

def gra2():
    global voltaje3
    print(contador.get())
    voltaje = int(contador.get())

    if voltaje > 255:
        print("El valor es mayor que 255")
    elif voltaje < 0:
        print("El valor es menor que 0")
    else:
        voltaje3 = voltaje
    
    voltaje_3.config(text = str(voltaje3))
    numero = int(voltaje3)
    numero = numero.to_bytes(1,'little')
    ser.write(numero)
    ser.flushOutput()
    print(str(voltaje3))
    ventana.update()
    time.sleep(.05)
    

def rep1():
    global voltaje3
    if voltaje3 > 0:
        voltaje3 = voltaje3 - 1
    voltaje_3.config(text = str(voltaje3))
    numero = int(voltaje3)
    numero = numero.to_bytes(1,'little')
    ser.write(numero)
    ser.flushOutput()
    print(str(voltaje3))
    ventana.update()
    time.sleep(.05)


#------------------ventana-------------------
ventana = Tk()
ventana.title("Laboratorio 3")
ventana.geometry("300x200")
ventana.resizable(width=FALSE, height=FALSE)
ventana.config(bg=color_fondo)


#------------------labels-------------------
rut1 = Label(ventana, text="Pot1:", background = color_fondo, font=('Comics', 16)).place(x=60,y=20)
rut2 = Label(ventana, text="Pot2:", background = color_fondo, font=('Comics', 16)).place(x=60,y=45)
rut3 = Label(ventana, text="Contador:", background = color_fondo, font=('Comics', 16)).place(x=60,y=70)
nombre1 = Label(ventana, text="Miguel García \n17560", background = color_fondo, font=('Times', 14)).place(x=90,y=140)

#-----------------Botones---------------------
grabar1 = Button(ventana, text = "Enviar", command=gra2).place(x=250,y=75)

grabar2 = Button(ventana, text = "+", command=gra1).place(x=250,y=110)
repro1 = Button(ventana, text = "-", command=rep1).place(x=270,y=110)

#------------------variables-----------------
voltaje_1 = Label(ventana,text=str(voltaje1) ,fg="red",font=(18))
voltaje_1.place(x=180,y=20)

voltaje_2 = Label(ventana,text=str(voltaje2) ,fg="red",font=(18))
voltaje_2.place(x=180,y=45)

voltaje_3 = Label(ventana,text=str(voltaje3) ,fg="red",font=(18))
voltaje_3.place(x=180,y=110)


voltaje_1_1 = Label(ventana,text="V" ,fg="red",font=(18))
voltaje_1_1.place(x=225,y=20)

voltaje_2_1 = Label(ventana,text="V" ,fg="red",font=(18))
voltaje_2_1.place(x=225,y=45)

contador = Entry(ventana, justify= CENTER, width=3)
contador.place(x=200,y=80)



while True:
    dato = ser.read()
    try:
        if dato == '':
            pass
        else:
            dato1 = ser.read()
            dato2 = ser.read()

            valor1 = ord(dato1)
            valor2 = ord(dato2)

            print(str(valor1) + ',' + str(valor2))
            ser.flushInput()
            time.sleep(.05)
            
    except:
        print('.')
    voltaje1 = (5.00*valor1)/254.50
    voltaje2 = (5.00*valor2)/254.50
    voltaje_1.config(text = str(voltaje1)[0:4])
    voltaje_2.config(text = str(voltaje2)[0:4])
    voltaje_3.config(text = str(voltaje3))
    ventana.update_idletasks()
    ventana.update() 
    time.sleep(.2)

ventana.mainloop()
