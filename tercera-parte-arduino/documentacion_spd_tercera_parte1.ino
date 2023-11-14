#define A 12
#define B 13
#define C 7
#define D 8
#define E 9
#define F 11
#define G 10
#define SUBE 4
#define BAJA 3
#define SWITCH_PIN 5
#define UNIDAD A4
#define DECENA A5
#define APAGADOS 0
#define TIMEDISPLAYON 10
#define MOTOR_CC A3
#define FOTODIODO A0

// Inicialización de variables
int countDigit = 0;
int sube = 1;
int subePrevia = 1;
int baja = 1;
int bajaPrevia = 1;
int lecturaFotodiodo = 0;
int intensidadBrillo = 0;  // Comienza con el brillo máximo


// Configuración inicial del sistema
void setup()
{
  // Configuración de pines de entrada y salida
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A0, INPUT);
  // Inicialización del motor en bajo y el display en 0
  digitalWrite(MOTOR_CC, LOW);  
  printDigit(0, 0);
  Serial.begin(9600);
}

// Función principal que se ejecuta en un bucle continuo
void loop() {
  //Lee el valor analógico del fotodiodo
  lecturaFotodiodo = analogRead(FOTODIODO);
  //Ajusta la intensidad del brillo del LED en función de la lectura del fotodiodo
  int intensidadBrillo = map(lecturaFotodiodo, 0, 85, 0, 255);

  // Lectura del estado del interruptor
  int switchState = digitalRead(SWITCH_PIN);
 
  // Comportamiento cuando el interruptor está en alto
  if (switchState == HIGH) 
  {
    digitalWrite(MOTOR_CC, LOW);
    int estado = keypressed();
    
    // Aumento del contador si se presiona el botón de subida
    if (estado == SUBE){
      countDigit++;
      if (countDigit > 99)
        countDigit = 0;
      } 
      // Disminución del contador si se presiona el botón de bajada
      else if (estado == BAJA)
      {
        countDigit--;
        if (countDigit < 0)
              countDigit = 99;
      } 
      // Impresión del contador en el display y el estado de intencidad de brillo
      printCount(countDigit, intensidadBrillo);
  }
  // Comportamiento cuando el interruptor está en bajo
  else if (switchState == LOW) 
  {
      digitalWrite(MOTOR_CC, HIGH);
    
      // Verificación de si el número actual no es primo y obtención del siguiente primo
      if (!esPrimo(countDigit))
      {
        countDigit = sigPrimo(countDigit);
      }
      int estado = keypressed();
      // Aumento del contador si se presiona el botón de subida
      if (estado == SUBE)
      {	
          countDigit++;
          if (countDigit > 99)
              countDigit = 0;
      } 
      // Disminución del contador si se presiona el botón de bajada
      else if (estado == BAJA) 
      {
          countDigit = antPrimo(countDigit);
          if (countDigit < 0)
              countDigit = 99;
      }
      // Impresión del contador en el display
      printCount(countDigit, intensidadBrillo);
  }
}

// Función para controlar el encendido de los dígitos del display
void prendeDigito(int digito)
{
  if (digito == UNIDAD)
  {
    digitalWrite(UNIDAD, LOW);
    digitalWrite(DECENA, HIGH);
    delay(TIMEDISPLAYON);
  }
  else if (digito == DECENA)
  {
    digitalWrite(UNIDAD, HIGH);
    digitalWrite(DECENA, LOW);
    delay(TIMEDISPLAYON);
  }
  else
  {
    digitalWrite(UNIDAD, HIGH);
    digitalWrite(DECENA, HIGH);
  }
}  

// Función para imprimir el número en el display
void printCount(int numero, int intensidadBrillo)
{
  prendeDigito(APAGADOS);
  printDigit(numero / 10, intensidadBrillo);
  prendeDigito(DECENA);
  prendeDigito(APAGADOS);
  printDigit(numero - 10 * (numero / 10), intensidadBrillo);
  prendeDigito(UNIDAD);
}

/*Función para verificar si un número es primo, devuelve verdadero si el número es primo, 
falso en caso contrario*/
bool esPrimo(int numero) {
    if (numero <= 1) {
        return false;
    }
    if (numero == 2) {
        return true;
    }
    if (numero % 2 == 0) {
        return false;
    }
    for (int i = 3; i * i <= numero; i += 2) {
        if (numero % i == 0){
            return false;
        }
    }
    return true;
}

// Función para obtener el siguiente número primo
int sigPrimo(int inicio) {
  int siguiente = inicio + 1;
  while (true) {
    if (esPrimo(siguiente)) {
      if (siguiente > 97) {
        return 2; //Retorna 2 ya que 0 y 1 no son un número primo
      }
      return siguiente;
    }
    siguiente++;
  }
}

// Función para obtener el número primo anterior
int antPrimo(int inicio) {
  int anterior = inicio - 1;
  while (anterior >= 2) {
    if (esPrimo(anterior)) {
      return anterior;
    }
    anterior--;
  }
  return 97; //Retorna 97 ya que 0 y 1 no son un número primo
}

// Función para imprimir un dígito en el display de 7 segmentos
void printDigit(int digito, int intensidadBrillo)
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);

  
  switch (digito)
  {
    case 0:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      // Ajustar la intensidad de brillo para los segmentos encendidos
      analogWrite(A, intensidadBrillo);
      analogWrite(B, intensidadBrillo);
      analogWrite(C, intensidadBrillo);
      analogWrite(D, intensidadBrillo);
      analogWrite(E, intensidadBrillo);
      analogWrite(F, intensidadBrillo);
      break;
    }
    case 1:
    {
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      analogWrite(B, intensidadBrillo);
      analogWrite(C, intensidadBrillo);
      break;
    }
    case 2:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(G, HIGH);
      // Ajustar la intensidad de brillo para los segmentos encendidos
      analogWrite(A, intensidadBrillo);
      analogWrite(B, intensidadBrillo);
      analogWrite(D, intensidadBrillo);
      analogWrite(E, intensidadBrillo);
      analogWrite(G, intensidadBrillo);
      break;
    }
    case 3:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(G, HIGH);
      // Ajustar la intensidad de brillo para los segmentos encendidos
      analogWrite(A, intensidadBrillo);
      analogWrite(B, intensidadBrillo);
      analogWrite(C, intensidadBrillo);
      analogWrite(D, intensidadBrillo);
      analogWrite(G, intensidadBrillo);
      break;
    }
    case 4:
    {
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      // Ajustar la intensidad de brillo para los segmentos encendidos
      analogWrite(B, intensidadBrillo);
      analogWrite(C, intensidadBrillo);
      analogWrite(F, intensidadBrillo);
      analogWrite(G, intensidadBrillo);
      break;
    }
    case 5:
    {
      digitalWrite(A, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      // Ajustar la intensidad de brillo para los segmentos encendidos
      analogWrite(A, intensidadBrillo);
      analogWrite(C, intensidadBrillo);
      analogWrite(D, intensidadBrillo);
      analogWrite(F, intensidadBrillo);
      analogWrite(G, intensidadBrillo);
      break;
    }
    case 6:
    {
      digitalWrite(A, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      // Ajustar la intensidad de brillo para los segmentos encendidos
      analogWrite(A, intensidadBrillo);
      analogWrite(C, intensidadBrillo);
      analogWrite(D, intensidadBrillo);
      analogWrite(E, intensidadBrillo);
      analogWrite(F, intensidadBrillo);
      analogWrite(G, intensidadBrillo);
      break;
    }
    case 7:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      // Ajustar la intensidad de brillo para los segmentos encendidos
      analogWrite(A, intensidadBrillo);
      analogWrite(B, intensidadBrillo);
      analogWrite(C, intensidadBrillo);
      break;
    }
    case 8:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      // Ajustar la intensidad de brillo para los segmentos encendidos
      analogWrite(A, intensidadBrillo);
      analogWrite(B, intensidadBrillo);
      analogWrite(C, intensidadBrillo);
      analogWrite(D, intensidadBrillo);
      analogWrite(E, intensidadBrillo);
      analogWrite(F, intensidadBrillo);
      analogWrite(G, intensidadBrillo);
      break;
    }
    case 9:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      // Ajustar la intensidad de brillo para los segmentos encendidos
      analogWrite(A, intensidadBrillo);
      analogWrite(B, intensidadBrillo);
      analogWrite(C, intensidadBrillo);
      analogWrite(D, intensidadBrillo);
      analogWrite(F, intensidadBrillo);
      analogWrite(G, intensidadBrillo);
      break;
    }
  }
}

/*Función para verificar si se presiona algún botón Devuelve 0 si no se ha presionado ningún botón, 
SUBE si se presiona el botón de subir, BAJA si se presiona el botón de bajar */
int keypressed(void)
{
  sube = digitalRead(SUBE);
  baja = digitalRead(BAJA);
	
  if (sube)
    subePrevia = 1;
  if (baja)
    bajaPrevia = 1;
  
  if (sube == 0 && sube != subePrevia)
  {
    subePrevia = sube;
    return SUBE;
  }
  if (baja == 0 && baja != bajaPrevia)
  {
    bajaPrevia = baja;
    return BAJA;
  }
  return 0;
}
