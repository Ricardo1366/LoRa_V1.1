#include <Arduino.h>
#include <pines.h>

void despertar();

volatile bool despierto;
long intervalo = 1000;
long tiempo = 0;

void setup()
{
  delay(10000);
  // put your setup code here, to run once:
  // Configuramos el monitor serial a 115200
  Serial2.begin(115200);
  while (!Serial2)
    ;
  Serial2.println(F("Iniciando la configuración."));

  // LED_BUILTIN se ha redefinido en "pines.h" ya que no coincide con el estandar
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TPL5010_DONE, OUTPUT);

  // Configuramos la interrupción de control del temporizador
  attachInterrupt(digitalPinToInterrupt(TPL5010_WAKE), despertar, RISING);
  // Enviamos el primer "DONE" para evitar que el temporizador nos resetee antes de que envíe
  // la siguiente señal de "despierta".
  digitalWrite(TPL5010_DONE, HIGH);
  Serial2.println(F("Evitando el reseteo. --------------------------------------"));
  digitalWrite(TPL5010_DONE, LOW);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (millis() - tiempo >= intervalo)
  {
    tiempo += intervalo;
    Serial2.print("Paso ");
    Serial2.println(tiempo / intervalo);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  if (despierto)
  {
    digitalWrite(TPL5010_DONE, HIGH);
    Serial2.println(F("Evitando el reseteo. --------------------------------------"));
    digitalWrite(TPL5010_DONE, LOW);
    despierto = false;
  }
}

void despertar()
{
  despierto = true;
}