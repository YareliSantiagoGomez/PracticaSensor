
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <DHT.h>
#include <ArduinoJson.h>

// Configuración del WiFi
#define WIFI_SSID "Galaxy A226B30"          // Cambia esto por tu red WiFi
#define WIFI_PASSWORD "YareSG0926"  // Cambia esto por la clave WiFi

// Configuración de Firebase
#define API_KEY "AIzaSyB2Mch8dI-PkN2L1FJBFRUvBewxEzHrAZU" 
#define DATABASE_URL "https://temp-10799-default-rtdb.firebaseio.com/" // URL correcta

// Autenticación de Firebase (USO DE AUTENTICACIÓN ANÓNIMA)
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    
    // Conectar a WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Conectando a WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConectado a WiFi!");

    // Configuración de Firebase
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;

    // 🔹 Activar autenticación anónima en Firebase
    Firebase.signUp(&config, &auth, "", ""); 

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    
    // Iniciar sensor DHT
    dht.begin();
}

void loop() {
    float temperatura = dht.readTemperature(); 
    float humedad = dht.readHumidity();       

    if (isnan(temperatura) || isnan(humedad)) {
        Serial.println("Error al leer el sensor DHT11");
        return;
    }

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print("°C, Humedad: ");
    Serial.print(humedad);
    Serial.println("%");

    // Guardar datos en Firebase
    if (Firebase.RTDB.setFloat(&fbdo, "/sensor/temperatura", temperatura)) {
        Serial.println("Temperatura enviada a Firebase");
    } else {
        Serial.println("Error al enviar temperatura");
    }

    if (Firebase.RTDB.setFloat(&fbdo, "/sensor/humedad", humedad)) {
        Serial.println("Humedad enviada a Firebase");
    } else {
        Serial.println("Error al enviar humedad");
    }

    delay(10000); 
}
