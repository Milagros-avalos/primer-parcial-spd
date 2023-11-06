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

int countDigit = 0;
int sube = 1;
int subePrevia = 1;
int baja = 1;
int bajaPrevia = 1;

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
  digitalWrite(MOTOR_CC, LOW);  
  printDigit(0);
  Serial.begin(9600);
}

void loop() {
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
      printCount(countDigit);
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
      printCount(countDigit);
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

void printCount(int numero)
{
  prendeDigito(APAGADOS);
  printDigit(numero / 10);
  prendeDigito(DECENA);
  prendeDigito(APAGADOS);
  printDigit(numero - 10 * (numero / 10));
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
void printDigit(int digito)
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
      break;
    }
    case 1:
    {
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;
    }
    case 2:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(G, HIGH);
      break;
    }
    case 3:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(G, HIGH);
      break;
    }
    case 4:
    {
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    }
    case 5:
    {
      digitalWrite(A, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
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
      break;
    }
    case 7:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
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