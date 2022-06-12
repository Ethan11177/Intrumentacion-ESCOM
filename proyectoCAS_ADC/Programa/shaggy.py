#####################################################Llamada a las librerias que sirven para la ejecucion del serial y el ploteado de graficos#######################################################
from multiprocessing.sharedctypes import Value
from turtle import color
import serial
import numpy as np
import time
import matplotlib.pyplot as plt
#######################################################################################################################################################################################################

arduino = serial.Serial(port='COM3', baudrate=115200, timeout=0)    #aqui es donde se obtiene los valores que manda el 
                                                                    #arduino por medio de una variable de seria que declaramos
arduino.flush()                                                     #por medio de flush se escucha cuando se manda un valor del arduino
##################Declaracion de variables##########################
si = 0
i = 0
pru = 0
j = 0
value2 = 0
values = [0,0,0,0,0] 
####################################################################

##################Funcion que hace la lectura del dato que manda el arduino y la incerta en una variable
def read():
    data = arduino.readline()
    time.sleep(0.95)
    return data
#########################################################################################################

def impri(value2, j):
    print("valor original",value2)
    ###################En esta seccion es donde se hace las operaciones para obtener el valor del voltaje del sensor y el HR%#########################################
    vsal = value2 * 0.0196087                    
    vsen = vsal/1.5151
    hr = vsen/0.033
    value2 = hr
    #####################################################################################################################################################################
    print("valor de humedad: ",value2," voltaje del sensor: ",vsen)      #Aqui se hace la impresion de los resultados
    ##############################################################En esta seccion se hace la impresion  de los datos por medio de una grafica######################################
    plt.scatter(j,value2,color='r',zorder=1)
    plt.plot(j,value2,color='b',zorder=2)
    plt.pause(0.05)
    plt.axis([0, 150, 0, 100])
    ##############################################################################################################################################################################
    if j == 0:
        plt.show()


while True:     #Se inicia un ciclo infinito para mandar a leer los datos, hacer la conversion de binario a decimal y le impresion de datos 
    
    value = read()          #se manda a llamar a la funcion de lectura de datos para obtener el valor que sigue al sismtema
    
    if value != b'':        #Por medio de una comparacion tomamos en cuanta si es que el los datos que manda el sistema no son binario vacios
        
        if pru != 0:
        
            values[i] = int(float(value))       #En esta parte de aqui es donde se hace la conversion de datos de binarios a deciamal
    ################################Aqui se hace la validacion y un promedio de los valores dados para saca una señal############################################################# 
            print(i, value2, values[i])
            
            value3=(values[0]+values[1]+values[2]+values[3]+values[4])/5

            if i==4:

                value2=(values[0]-values[1])-(values[1]-values[2])-(values[2]-values[3])-(values[3]-values[4])

                if value2 >=-10 or value2 <=10:       #Se establecen limites de como es que el valor puede comportarse en cierto rango de operacion
                    value2=(values[0]+values[1]+values[2]+values[3]+values[4])/5       #Aqui se hace la conversion de datos que si se pueden guardar en el rango de operacion
                    impri(value2, j)
                    j = j + 1
                values[0]=0
                values[1]=0
                values[2]=0
                values[3]=0
                values[4]=0
                value2 = 0
                #Si el valor no esta en el rango de operacion se asigna un cero el elemento en curso
                i=0
            else:
                i = 1 + i

        ##############################################################################################################################
        else:

            values[i] = int(float(value))       #En esta parte de aqui es donde se hace la conversion de datos de binarios a deciamal
    ################################Aqui se hace la validacion y un promedio de los valores dados para saca una señal############################################################# 
            print(i, value2, values[i])

            valueprue = values[i]

            if valueprue+30 >= values[i] and valueprue-30 <= values[i]:

                value2=(values[0]-values[1])-(values[1]-values[2])-(values[2]-values[3])-(values[3]-values[4])

                if value2 >=-10 or value2 <=10:       #Se establecen limites de como es que el valor puede comportarse en cierto rango de operacion
                    value2=(values[0]+values[1]+values[2]+values[3]+values[4])/5       #Aqui se hace la conversion de datos que si se pueden guardar en el rango de operacion
                    impri(value2, j)
                    j = j + 1
                values[0]=0
                values[1]=0
                values[2]=0
                values[3]=0
                values[4]=0
                #Si el valor no esta en el rango de operacion se asigna un cero el elemento en curso
                i=0
            else:
                i = 1 + i