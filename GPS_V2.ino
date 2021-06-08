#include <SoftwareSerial.h>

#include <TinyGPS.h>

String ubi = "";

TinyGPS gps;
SoftwareSerial ss(4, 3);

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
  
  Serial.println("Iniciando...");
  Serial.println();
}

void loop()
{
  bool newData = false;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
        ubicacion(newData);
    }
  }

  
}

void ubicacion(boolean newData){
  if (newData)
  {
    ubi = "https://www.google.com.mx/maps/place/";
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    ubi+=String(flat,6);
    ubi+=" ";
    ubi+=String(flon,6);
    Serial.println(ubi);
    ubi="";
    delay(1000);
  }  
}
