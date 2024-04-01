
cantCases=int(input())
seleccionesOficiales=[]
for i in range(1, cantCases+1):
    jugadores=[]
    for jugador in range(10):
        a= input().split() #variable simplemente para separar el input
        jugadores.append((a[0],int(a[1]),int(a[2])))
    seleccionesOficiales.append(jugadores)

 #Busco de las dos selecciones cuál tiene los atacantes que más me sirven
def mejorSeleccion(seleccion1, seleccion2):
    pAtaque1 = sum(jugador[1] for jugador in seleccion1)
    pAtaque2 = sum(jugador[1] for jugador in seleccion2)
        
    #Devuelvo el de mejor ataque
    if pAtaque1 > pAtaque2:
        return seleccion1
    elif pAtaque1 < pAtaque2:
        return seleccion2
    else: 
        
        pDefensa1 = sum(jugador[2] for jugador in seleccion1)
        pDefensa2 = sum(jugador[2] for jugador in seleccion2)
            
        #Sino, devuelvo a la que tenga a los 5 atacantes con peor defensa, pq quiero que la defensa esté maximizada
        if pDefensa1 > pDefensa2:
            return seleccion2
        elif pDefensa1 < pDefensa2:
            return seleccion1
        else:
            # Sino, devuelvo el lexicogarficamente menor
            return min(seleccion1, seleccion2)
            
        
#Dada una lista de jugadores, obtengo la combinación con los mejores 5 atacantes. 
    #Si hay empate que busque a los que tengan peor defensa (así los defensores tienen mejores puntos)
        #Si hay empate nuevamente, dame el menor lexicográficamente
def seleccionarAtacantes(listaJugadores, indice, seleccionActual):
    #Caso base: Llegue a 5 jugadores
    if len(seleccionActual) == 5:
        return seleccionActual
    
    #Caso Base: No hay mas jugadores para agregar
    if indice >= len(listaJugadores): 
        return seleccionActual

    #Caso recursivo, mi seleccion no tiene 5 jugadores asi que pruebo con agregar el siguiente o no
    jugador_tomado = listaJugadores[indice]
    seleccionActual.append(jugador_tomado)

    return mejorSeleccion(seleccionarAtacantes(listaJugadores, indice + 1, seleccionActual.copy()), #Agrego al jugador
                                  seleccionarAtacantes(listaJugadores, indice + 1, seleccionActual[:-1])) #No agrego al jugador


for i in range(cantCases):
    seleccionesOficiales[i].sort() #Los ordeno lexicograficamente
    atacantes = seleccionarAtacantes(seleccionesOficiales[i], 0, []) #Pues el ataque está maximizado
    defensores = [] #Defensa va a ser el resto de los jugadores que no son atacantes
    for jugador in seleccionesOficiales[i]:
        if jugador not in atacantes:
            defensores.append(jugador)
    seleccionesOficiales[i][:5] = atacantes[:5] #Agrego los atacantes a la matriz de seleccionesOficiales
    seleccionesOficiales[i][5:] = defensores[:5] #Agrego los defensores a la matriz de seleccionesOficiales

    print("Case "+ str(i+1)+":" )
    print("("+ ', '.join(jugador[0] for jugador in seleccionesOficiales[i][:5]) + ")")
    print("(" + ', '.join(jugador[0] for jugador in seleccionesOficiales[i][5:])+ ")")



