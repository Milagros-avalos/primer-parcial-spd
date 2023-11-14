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

int countDigit = 0;
int sube = 1;
int subePrevia = 1;
int baja = 1;
int bajaPrevia = 1;
int lecturaFotodiodo = 0;
int intensidadBrillo = 0; 

void setup()
{
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
  digitalWrite(MOTOR_CC, LOW);  
  printDigit(0, 0);
  Serial.begin(9600);
}

void loop() {
  lecturaFotodiodo = analogRead(FOTODIODO);
  int intensidadBrillo = map(lecturaFotodiodo, 0, 85, 0, 255);
  int switchState = digitalRead(SWITCH_PIN);

  if (switchState == HIGH) 
  {
    digitalWrite(MOTOR_CC, LOW);
    int estado = keypressed();
    if (estado == SUBE){
      countDigit++;
      if (countDigit > 99)
        countDigit = 0;
      } 
      else if (estado == BAJA)
      {
        countDigit--;
        if (countDigit < 0)
              countDigit = 99;
      } 
      printCount(countDigit, intensidadBrillo);
  }
  else if (switchState == LOW) 
  {
      digitalWrite(MOTOR_CC, HIGH);
      if (!esPrimo(countDigit))
      {
        countDigit = sigPrimo(countDigit);
      }
      int estado = keypressed();
      if (estado == SUBE)
      {	
          countDigit++;
          if (countDigit > 99)
              countDigit = 0;
      } 
      else if (estado == BAJA) 
      {
          countDigit = antPrimo(countDigit);
          if (countDigit < 0)
              countDigit = 99;
      }
      printCount(countDigit, intensidadBrillo);
  }
}

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

void printCount(int numero, int intensidadBrillo)
{
  prendeDigito(APAGADOS);
  printDigit(numero / 10, intensidadBrillo);
  prendeDigito(DECENA);
  prendeDigito(APAGADOS);
  printDigit(numero - 10 * (numero / 10), intensidadBrillo);
  prendeDigito(UNIDAD);
}

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

int sigPrimo(int inicio) {
  int siguiente = inicio + 1;
  while (true) {
    if (esPrimo(siguiente)) {
      if (siguiente > 97) {
        return 2; 
      }
      return siguiente;
    }
    siguiente++;
  }
}

int antPrimo(int inicio) {
  int anterior = inicio - 1;
  while (anterior >= 2) {
    if (esPrimo(anterior)) {
      return anterior;
    }
    anterior--;
  }
  return 97;
}
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
