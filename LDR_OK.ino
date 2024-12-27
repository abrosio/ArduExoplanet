// Pin della fotoresistenza
const int photoResistorPin = A0;

// Variabili per il calcolo del bias e il valore normalizzato
float bias = 0.0;
float conta = 0.0;
float s = 0.0;
int LDR_B = 0; // Valore intero della LDR

void setup() {
  // Inizializza la comunicazione seriale
  Serial.begin(250000);
  pinMode(photoResistorPin, INPUT);
}

void loop() {
  // Calcolo del bias (media dei valori letti)
  conta = 0.0; // Reset della somma
  s = 0.0;     // Reset del contatore

  for (int i = 0; i < 100; i++) {
    int piedistallo = analogRead(photoResistorPin); // Lettura della LDR
    conta += piedistallo;  // Somma i valori
    s += 1.0;              // Incrementa il conteggio
  }
  bias = conta / s; // Calcola la media

  // Lettura attuale della fotoresistenza
  int LDRValue = analogRead(photoResistorPin);

  // Calcola il valore con il bias
  int newLDR_B = (1023 - LDRValue) - round(bias);

  // Filtra le variazioni inferiori a 1
  if (abs(newLDR_B - LDR_B) >= 1.2) {
    LDR_B = newLDR_B; // Aggiorna solo se la variazione è significativa
  }

  // Stampa il valore intero per il plotter seriale
  Serial.println(LDR_B);

  // Attendi per stabilizzare il grafico
  delay(80);
}
