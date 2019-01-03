
//declaramos los puertos que tienen un led conectado
int led1= 13;
int led2 = 12;
int led3 = 8;
int led4 = 7;
//declaramos los puertos que tienen un pulsador conectado
int Pin1 = 5;
int estado1;
int Pin2 = 4;
int estado2;
int Pin3 = 3;
int estado3;
int Pin4 = 2;
int estado4;
int valores[4]={2,3,1,4}; //vector con la contraseña correcta
int acertado=0; //contador de intentos de insercion de la contraseña. Si es igual a 3 se dispara la alarma, por tanto hay 3 intentos para escribirla correctamente

void efectoLuminoso(){ //en caso de exito mostramos un recorrido de luz entre los leds
  for(int i=0; i<=60; i++){ //durante un minuto la alarma se encuentra desactivada para permitir las operaciones necesarias
  digitalWrite(led1,HIGH);
  delay(1000);
  digitalWrite(led2,HIGH);
  delay(1000);
  digitalWrite(led3,HIGH);
  delay(1000);
  digitalWrite(led4,HIGH);
  delay(1000);
  digitalWrite(led1,LOW);
  delay(1000);
  digitalWrite(led2,LOW);
  delay(1000);
  digitalWrite(led3,LOW);
  delay(1000);
  digitalWrite(led4,LOW);
  delay(1000);  
  }
}

void efectoFallido(){ //Efecto luminoso en caso de que detectar una entrada erronea
  for(int j=0; j<=15; j++){
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH); //activamos todos los leds a la vez durante un segundo y lo volvemos a apagar
  digitalWrite(led4,HIGH);
  delay(1000);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  delay(1000);
  }
}

int botonPulsado(){
  int v; //nº de boton pulsado
  estado1=LOW;
  estado2=LOW;
  estado3=LOW;
  estado4=LOW;
  while(estado1==LOW&&estado2==LOW&&estado3==LOW&&estado4==LOW){
   estado1= digitalRead(Pin1); 
   estado2= digitalRead(Pin2); //leemos el valor de la entrada digital
   estado3= digitalRead(Pin3); 
   estado4= digitalRead(Pin4); 
   }
    if(estado1==HIGH)   {
      v=1;
    }
    if(estado2==HIGH)   {
      v=2;
    }
    if(estado3==HIGH)   {
      v=3;
    }
    if(estado4==HIGH)   {
      v=4;
    }
  
  delay(1000);
  return v;
}

//Cargamos la configuracion por defecto
void setup() {
  Serial.begin(9600);
  // inicializamos los leds como salida
  pinMode(led1, OUTPUT);     
  pinMode(led2, OUTPUT);     
  pinMode(led3, OUTPUT);     
  pinMode(led4, OUTPUT);     
  //los pulsadores por defecto estn inicializados como entrada por tanto no necesitamos hacer este codigo:
  /*pinMode(Pin1, INPUT);
  pinMode(Pin2, INPUT);
  pinMode(Pin3, INPUT);
  pinMode(Pin4, INPUT);*/
}

//bucle infinito
void loop() {
  Serial.print("Introduce codigo\n");
  int boton=botonPulsado(); //almacenamos el boton pulsado
  Serial.print("Boton pulsado ");
  Serial.print (boton);
  if(boton==valores[0]){
    Serial.print (" Correcto\n");
    boton=botonPulsado();
    Serial.print("Boton pulsado ");
    Serial.print (boton);
    if(boton==valores[1]){
      Serial.print (" Correcto\n");
      boton=botonPulsado();
      Serial.print("Boton pulsado ");
      Serial.print (boton);
      if(boton==valores[2]){
        Serial.print (" Correcto\n");
        boton=botonPulsado();
        Serial.print("Boton pulsado ");
        Serial.print (boton);
          if(boton==valores[3]){
            Serial.print(" Alarma desactivada\n");
            efectoLuminoso();
            acertado=1;
            }
          }      
      }
    }
   if(acertado<3){
     acertado++;
   }
  if(acertado==3){
    for(int k=0; k<=5;k++){
    Serial.print("ALARMA SILENCIOSA ACTIVA\n");
    Serial.print("¡¡INTRUSO DETECTADO!!\n");
    Serial.print("Contactando con las FFCCSE\n");
    delay(5000);
    }
    //Mientras hacemos este bucle el hipotetico ladron seguira intentando manipular la alarma, aprovechamos ese tiempo para contactar con la policia y acto seguido
    //lo asustamos con el encendido de luces haciendole creer que en ese momento hemos activado la alarma, sin embargo como podemos ver lleva un rato conectada
    Serial.print("Activando sistema de luces disuasor\n");
    efectoFallido();    
  }
  acertado==0;
  
}
