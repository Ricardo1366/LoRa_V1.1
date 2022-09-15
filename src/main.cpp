#include <Arduino.h>
#include <pines.h>

long intervalo = 1000;
long tiempo = 0;

void setup()
{
  // put your setup code here, to run once:
  // Configuramos el monitor serial a 115200
  Serial2.begin(115200);
  while (!Serial2);
  Serial2.println(F("Iniciando la configuración."));
  // LED_BUILTIN se ha redefinido en "pines.h" ya que no coincide con el estandar
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (millis() - tiempo >= intervalo)
  {
    tiempo += intervalo;
    Serial2.print("Paso "); Serial2.println(tiempo / intervalo);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}