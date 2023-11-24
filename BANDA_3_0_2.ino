/*================================================================================
Programa de la Banda
*Este prgograma controla:
-Buzzer pasisvo
-Led 2mm
-Modulo Bluetooth HC-05
Este programa tiene como funcion automatizar todos los procesos de este sistema
================================================================================*/



/*
██╗░░░░░██╗██████╗░██████╗░███████╗██████╗░██╗░█████╗░░██████╗
██║░░░░░██║██╔══██╗██╔══██╗██╔════╝██╔══██╗██║██╔══██╗██╔════╝
██║░░░░░██║██████╦╝██████╔╝█████╗░░██████╔╝██║███████║╚█████╗░
██║░░░░░██║██╔══██╗██╔══██╗██╔══╝░░██╔══██╗██║██╔══██║░╚═══██╗
███████╗██║██████╦╝██║░░██║███████╗██║░░██║██║██║░░██║██████╔╝
╚══════╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝╚═╝╚═╝░░╚═╝╚═════╝░
*/
//Se incluyen la libreria para controlar el buzzer
#include <Tone.h>
//Se incluye la libreria para utilizar dos pines del arduino como comunicacion serial
#include <SoftwareSerial.h>


/*
██╗░░░██╗░█████╗░██████╗░██╗░█████╗░██████╗░██╗░░░░░███████╗░██████╗
██║░░░██║██╔══██╗██╔══██╗██║██╔══██╗██╔══██╗██║░░░░░██╔════╝██╔════╝
╚██╗░██╔╝███████║██████╔╝██║███████║██████╦╝██║░░░░░█████╗░░╚█████╗░
░╚████╔╝░██╔══██║██╔══██╗██║██╔══██║██╔══██╗██║░░░░░██╔══╝░░░╚═══██╗
░░╚██╔╝░░██║░░██║██║░░██║██║██║░░██║██████╦╝███████╗███████╗██████╔╝
░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚═╝╚═════╝░╚══════╝╚══════╝╚═════╝░
*/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//Se definen los pines y las variables--------------------------------------------
  /*
  █▄▄ █░█ ▀█ ▀█ █▀▀ █▀█
  █▄█ █▄█ █▄ █▄ ██▄ █▀▄
  */
  //Buzzer==========================================================================
  Tone track; //Se define la pieza musical
  #define Buzz 5 //Define el pin del buzzer
  const int t = 600;  // Half Note
  const int tt = t*2;  //Whole Note
  const int t14 = round(t*1/4); //Eight Note
  const int t24 = round(t*2/4); //Quarter Note
  const int t34 = round(t*3/4); 
  //==============================================================================
  /*
  █░█ █▀▀ ▄▄ █▀█ █▀
  █▀█ █▄▄ ░░ █▄█ ▄█
  */
  //HC-05=========================================================================
  SoftwareSerial Banda(10, 11); 	// pin 10 como RX, pin 11 como TX
  String data; //Variable donde se guardaran los datos recibidos del celular
  int h_now; //Hora actual
  int m_now; //Minuto actual
  unsigned long s_now; //Hora actual transformada a segundos
  int h_arm; //Hora de inicio de alarma
  int m_arm; //Minuto de inicio de alarma
  unsigned long s_arm; //Hora de la alarma transformada a segundos
  unsigned long s_tot =1; //Segundos totales hasta que sea la hora de la alarma
  bool inicio = false; //Toogle para indicar si se recibio informacion o no por medio de bluetooth
  int TIC = 0; //Toogle para iniciar el temporizador
  bool TOC = false; //Toogle para decir que ya se obtuvo el tiempo restante para la alarma
  bool x = false; //Toogle para cambiar la variable segundos que es la del temporizador a el tiempo obtenido restante para la alarma
  bool y = false; //Toogle para cambiar la variable segundos que es la del temporizador a 24 horas a partir de que sono la alarma
  int contador = 0; //Variable que ayuda a mantener el control de las veces que suena la alarma, en esta caso se pone 0 para que inicie de 0 y llegue a 12 haciendo que suene 12 veces en 1 hora que seria cada 5 minutos
  unsigned long tiempo; //tiempo obtenido en tiempo real del temporizador
  unsigned long SEGUNDOS; //Variable que dicta el tiempo de la funcion del temporizador
  unsigned long SEGUNDOS2 = 285; //Variable que dicta el tiempo de la funcion del que controlara la frecuencia del sonido de la alarma, se pone 285 segundos ya que sonara cada 5 minutos restandole lo qe tarda en sonar la alarma que son 15 segundos
  //==============================================================================
  /*
  █░░ █▀▀ █▀▄
  █▄▄ ██▄ █▄▀
  */
  //LED==========================================================================
  #define LED 7 //Se define el pin del LED
  unsigned long previousMillis = 0;  // Almacena el tiempo del último cambio de estado
  const long interval = 1000;  // Intervalo de tiempo para el parpadeo en milisegundos
  //==============================================================================
  //------------------------------------------------------------------------------
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>



/*
░██████╗███████╗████████╗██╗░░░██╗██████╗░
██╔════╝██╔════╝╚══██╔══╝██║░░░██║██╔══██╗
╚█████╗░█████╗░░░░░██║░░░██║░░░██║██████╔╝
░╚═══██╗██╔══╝░░░░░██║░░░██║░░░██║██╔═══╝░
██████╔╝███████╗░░░██║░░░╚██████╔╝██║░░░░░
╚═════╝░╚══════╝░░░╚═╝░░░░╚═════╝░╚═╝░░░░░
*/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// CONFIGURACIONES----------------------------------------------------------------
void setup() {
  Serial.begin(9600); //Inicia el porto serial
  /*
  █▄▄ █░█ ▀█ ▀█ █▀▀ █▀█
  █▄█ █▄█ █▄ █▄ ██▄ █▀▄
  */
  //Buzzer==========================================================================
  pinMode(2, OUTPUT);  // buzzer ground pin
  track.begin(Buzz);  // buzzer signal pin
  //==============================================================================
  /*
  █░█ █▀▀ ▄▄ █▀█ █▀
  █▀█ █▄▄ ░░ █▄█ ▄█
  */
  //HC-05=========================================================================
  Banda.begin(38400); 	// se inicia la velocidad de comunicacion del HC-05
  //==============================================================================
  /*
  █░░ █▀▀ █▀▄
  █▄▄ ██▄ █▄▀
  */
  //LED==========================================================================
  pinMode(LED, OUTPUT); //Se define el pin  de señal del LED
  //==============================================================================
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*
███╗░░░███╗░█████╗░██╗███╗░░██╗
████╗░████║██╔══██╗██║████╗░██║
██╔████╔██║███████║██║██╔██╗██║
██║╚██╔╝██║██╔══██║██║██║╚████║
██║░╚═╝░██║██║░░██║██║██║░╚███║
╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝
*/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//PROGRAMA PRINCIPAL////////////////////////////////////////////////////////////////
void loop() {

  if (Banda.available()>0){ //Si llega un mensaje del celular
    data= Banda.readString(); //Se lee el mensaje
    inicio = true; //Indica que se recibio una señal por medio de bluetooth
    if (data.startsWith("<")){ //Solo se activa si biene codificada la hora: <hn,mn,ha,ma>
      data.remove(0,1); //Remieve ek <
      h_now=(data.toInt()); //Lee el hn
      data.remove(0,((data.indexOf(","))+1)); //Remueve el hm y la ,
      m_now=(data.toInt()); //Lee el mn
      data.remove(0,((data.indexOf(","))+1)); //Remueve el mn y la ,
      h_arm=(data.toInt()); //Lee el ha
      data.remove(0,((data.indexOf(","))+1)); //Remueve el ha y la ,
      m_arm=(data.toInt()); //Lee el ma
      data.remove(0,((data.indexOf(">"))+1)); //Remueve el ma y el >
    }
    s_now=h_now*3600+m_now*60; //Convierte la hora actual a segundos
    s_arm=h_arm*3600+m_arm*60; //Convierte la hora de la alarma en segundos
    s_tot=s_arm-s_now; //Hace la operacion para obtener los segundos faltantes para la hora de la alarma
    if(s_tot<0){ //Si es que la operacion sale negativa es porque es del siguiente dia la hora
      s_tot=s_tot+86400; //Por lo que se le suman 24 horas en segundos
    }
    TIC ++;
    if (TIC%2 == 0 && TIC !=0){
      TOC = false; //Se activa el toogle para decir que ya se obtuvo el tiempo restante para la alarma
    }
    if (TIC%2 != 0 && TIC !=0){
      TOC = true; //Se activa el toogle para decir que ya se obtuvo el tiempo restante para la alarma
    }
  }
  if (TOC == true && inicio == true){ //Si ya se obtuvo el tiempo restante para la alarma:
    if (x == false){ //Este toogle sirve para que solo se cambie la variable global segundos 1 sola vez cuando se corra el programa
      SEGUNDOS = s_tot; //Se cambia la variable segundos que es la del temporizador a el tiempo obtenido restante para la alarma
      x= true; //Se cambia el toogle para que no se vuelva a activar
      contador = 0; //Cambia el contador a 0 para que inicie otra vez los 12 ciclos de alarma
      y= false; //Reinica el toogle para la funcion de alarma
    }
    tiempo=TEMPORIZADOR(); //Se obtiene el tiempo restante corriendo en el temporizador
    if(tiempo<=0){ //Si el tiempo llega a 0
      ALARMA(); //Inicia la funcion que hace sonar a la alarma a lo largo de una hora cada 5 minutos
    }
  }
  else if (TOC == false && inicio == true){ //Si ya se obtuvo el tiempo restante para la alarma:
    if (x == true){ //Este toogle sirve para que solo se cambie la variable global segundos 1 sola vez cuando se corra el programa
      SEGUNDOS = s_tot; //Se cambia la variable segundos que es la del temporizador a el tiempo obtenido restante para la alarma
      x= false; //Se cambia el toogle para que no se vuelva a activar
      contador = 0; //Cambia el contador a 0 para que inicie otra vez los 12 ciclos de alarma
      y= false; //Reinica el toogle para la funcion de alarma
    }
    tiempo=TEMPORIZADOR(); //Se obtiene el tiempo restante corriendo en el temporizador
    if(tiempo<=0){ //Si el tiempo llega a 0
      ALARMA(); //Inicia la funcion que hace sonar a la alarma a lo largo de una hora cada 5 minutos
    }
  }
  Serial.print("tot: ");
  Serial.println(tiempo);
}
///////////////////////////////////////////////////////////////////////////////////
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>



/*
░██████╗██╗░░░██╗██████╗░░░░░░░███████╗██╗░░░██╗███╗░░██╗░█████╗░██╗░█████╗░███╗░░██╗███████╗░██████╗
██╔════╝██║░░░██║██╔══██╗░░░░░░██╔════╝██║░░░██║████╗░██║██╔══██╗██║██╔══██╗████╗░██║██╔════╝██╔════╝
╚█████╗░██║░░░██║██████╦╝█████╗█████╗░░██║░░░██║██╔██╗██║██║░░╚═╝██║██║░░██║██╔██╗██║█████╗░░╚█████╗░
░╚═══██╗██║░░░██║██╔══██╗╚════╝██╔══╝░░██║░░░██║██║╚████║██║░░██╗██║██║░░██║██║╚████║██╔══╝░░░╚═══██╗
██████╔╝╚██████╔╝██████╦╝░░░░░░██║░░░░░╚██████╔╝██║░╚███║╚█████╔╝██║╚█████╔╝██║░╚███║███████╗██████╔╝
╚═════╝░░╚═════╝░╚═════╝░░░░░░░╚═╝░░░░░░╚═════╝░╚═╝░░╚══╝░╚════╝░╚═╝░╚════╝░╚═╝░░╚══╝╚══════╝╚═════╝░
*/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*
░█▀▀█ ─█▀▀█ ░█▀▀▀█ ▀█▀ ░█▀▀█ ─█▀▀█ ░█▀▀▀█ 
░█▀▀▄ ░█▄▄█ ─▀▀▀▄▄ ░█─ ░█─── ░█▄▄█ ─▀▀▀▄▄ 
░█▄▄█ ░█─░█ ░█▄▄▄█ ▄█▄ ░█▄▄█ ░█─░█ ░█▄▄▄█
*/
/*
█▄▄ █░█ ▀█ ▀█ █▀▀ █▀█
█▄█ █▄█ █▄ █▄ ██▄ █▀▄
*/
// Procesos de Buzzer-------------------------------------------------------------
  //Pausa=========================================================================
  void wait(Tone t){
  while (t.isPlaying()) { }  
  }
  //==============================================================================

  //Cancion=======================================================================
  void Lullaby(void) {
    track.play(NOTE_A4, t24);
      wait(track);
    track.play(NOTE_A4, t24);
      wait(track);
    LEDON();
    track.play(NOTE_C5, tt);
      wait(track);
    LEDOFF();
    track.play(NOTE_A4, t24);
      wait(track);
    track.play(NOTE_A4, t24);
      wait(track);
    LEDON();
    track.play(NOTE_C5, tt);
      wait(track);
    LEDOFF();
    track.play(NOTE_A4, t24);
      wait(track);
    track.play(NOTE_C5, t24);
      wait(track);
    LEDON();
    track.play(NOTE_F5, t);
      wait(track);
      LEDOFF();
    track.play(NOTE_E5, t);
      wait(track);
      LEDON();
    track.play(NOTE_D5, t);
      wait(track);
      LEDOFF();
    track.play(NOTE_D5, t);
      wait(track);
      LEDOFF();
    track.play(NOTE_C5, t);
      wait(track);
      LEDON();
    track.play(NOTE_G4, t24);
      wait(track);
    track.play(NOTE_A4, t24);
      wait(track);
      LEDOFF();
    track.play(NOTE_AS4, t);
      wait(track);
      LEDON();
    track.play(NOTE_G4, t);
      wait(track);
      LEDOFF();
    track.play(NOTE_G4, t24);
      wait(track);
    track.play(NOTE_A4, t24);
      wait(track);
      LEDON();
    track.play(NOTE_AS4, tt);
      wait(track);
      LEDOFF();
    track.play(NOTE_G4, t24);
      wait(track);
    track.play(NOTE_AS4, t24);
      wait(track);
      LEDON();
    track.play(NOTE_E5, t24);
      wait(track);
    track.play(NOTE_D5, t24);
      wait(track);
      LEDOFF();
    track.play(NOTE_C5, t);
      wait(track);
      LEDON();
    track.play(NOTE_E5, t);
      wait(track);
      LEDOFF();
    track.play(NOTE_F5, tt);
      wait(track);
  }
  //==============================================================================
  //--------------------------------------------------------------------------------

  /*
  █░░ █▀▀ █▀▄
  █▄▄ ██▄ █▄▀
  */
  //LED---------------------------------------------------------------------------
  //Encendido del LEDr=============================================================
  void LEDON(void) {  //Enciende el LED
  digitalWrite(LED,HIGH);
  }
  //==============================================================================

  //Apagado del LEDr==============================================================
  void LEDOFF(void) {  //Apaga el LED
  digitalWrite(LED,LOW);
  }
  //==============================================================================
  //------------------------------------------------------------------------------

/*
░█▀▀▀█ ░█─░█ ░█▀▀█ ░█▀▀█ ░█▀▀█ ░█▀▀▀█ ░█▀▀█ ░█▀▀▀ ░█▀▀▀█ ░█▀▀▀█ ░█▀▀▀█ 
─▀▀▀▄▄ ░█─░█ ░█▀▀▄ ░█▄▄█ ░█▄▄▀ ░█──░█ ░█─── ░█▀▀▀ ─▀▀▀▄▄ ░█──░█ ─▀▀▀▄▄ 
░█▄▄▄█ ─▀▄▄▀ ░█▄▄█ ░█─── ░█─░█ ░█▄▄▄█ ░█▄▄█ ░█▄▄▄ ░█▄▄▄█ ░█▄▄▄█ ░█▄▄▄█
*/

/*
▀█▀ █▀▀ █▀▄▀█ █▀█ █▀█ █▀█ █ ▀█ ▄▀█ █▀▄ █▀█ █▀█
░█░ ██▄ █░▀░█ █▀▀ █▄█ █▀▄ █ █▄ █▀█ █▄▀ █▄█ █▀▄
*/
// Temporizadores GLOBALES-------------------------------------------------------- 
  //Temporizador del tiempo hasta que suene la alarma=============================
  unsigned long TEMPORIZADOR(){
  static long ultimo_cambio = 0;
  long hora = millis();
    while (SEGUNDOS > 0){
      if (hora - ultimo_cambio > 1000){
	      ultimo_cambio = hora;
        SEGUNDOS --;
    }
    return SEGUNDOS;
    }
  }  
  //==============================================================================
  //Temporizador de 5 minutos del intervalo de activacion de la alarma============
  unsigned long TEMPORIZADOR2(){
  static long ultimo_cambio = 0;
  long hora = millis();
    while (SEGUNDOS2 > 0){
      if (hora - ultimo_cambio > 1000){
	      ultimo_cambio = hora;
        SEGUNDOS2 --;
    }
    return SEGUNDOS2;
    }
  }  
  //==============================================================================
  //------------------------------------------------------------------------------

/*
▄▀█ █░░ ▄▀█ █▀█ █▀▄▀█ ▄▀█
█▀█ █▄▄ █▀█ █▀▄ █░▀░█ █▀█
*/ 
// ALARMA-------------------------------------------------------------------------
  //Proceso de encendido de la alrma==============================================
  void ALARMA(){
    unsigned long TIME; //Tiempo en el que se guardara la cuenta regresiva del temporizador de 5 minutos
    Lullaby(); //Suena la cancion
    while (contador < 12){ //Loop para que suene la cancion 12 veces en una hora
      TIME=TEMPORIZADOR2(); //Se obtiene el tiempo restante corriendo en el temporizador de 5 minutos
      if(TIME<=0){ //Si el tiempo llega a 0
        Lullaby(); //Se activa el Buzzer
        contador ++; //Se reduce un ciclo de los 12
        SEGUNDOS2 = 285; //Reinicia el temporizador
      }
      Serial.print("TIME: ");
      Serial.println(TIME);
      if (Banda.available()>0){ //Si llega un mensaje del celular
        contador = 12; //Se acaba el while y reprograma la hora
      }
      if (y == false){ //Este toogle sirve para que solo se cambie la variable global segundos 1 sola vez cuando se corra el programa
        SEGUNDOS = 82800;; //Se cambia la variable segundos que es la del temporizador a el tiempo obtenido restante para la alarma
        y= true; //Se cambia el toogle para que no se vuelva a activar
      }
    }
  }
  //==============================================================================
  //------------------------------------------------------------------------------
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
