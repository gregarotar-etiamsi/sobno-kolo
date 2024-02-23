// osnoven program za merjenje električnega toka z senzorjem ACS712

// pin na katerega je priključen senzor
#define TOK_PIN 32
// napetost na VIN pinu, ki se spreminja z napajalniki
#define NAPETOST_NAPAJANJA 4.76
// odstopanja so umerjena ekspirimentalno
#define TOK_ODSTOPANJE -0.12
#define TOK_NAPETOST_ODSTOPANJE -0.165
// delilnik napetosti na izhodu ACS712
#define TOK_UPOR_MERITEV 20000
#define TOK_UPOR_REFERENCA 10000

void setup() {
  	// omogoči izpis vrednosti preko serial komunikacie
  	Serial.begin(9600);
  	// nastavi pin za tok na input
	pinMode(TOK_PIN, INPUT);
}

double tok;
void loop() {
  tok = pridobiIzhodniTok();  
  // izpis toka prek serial komunikacije
  Serial.println(tok);	
  // program počaka 1 sekundo (1000ms)
  delay(1000);
}


double pridobiIzhodniTok() {
  // napetost na ESP32 pinu z upoštevanjem odstopanj
  // pridobiNapetostNaPin --> glej poglavje funkcije
  double napetostNaPin = pridobiNapetostNaPin(TOK_PIN) - TOK_NAPETOST_ODSTOPANJE;
  // dejanska napetost brez delinika napetosti
  // pretvoriVDejanskoNapetost --> glej poglavje funkcije
  double dejanskaNapetost = pretvoriVDejanskoNapetost(napetostNaPin, TOK_UPOR_REFERENCA, TOK_UPOR_MERITEV);
  // izračunan tok z upoštevanjem odstopanj
  double tok = (dejanskaNapetost - (NAPETOST_NAPAJANJA / 2)) / 0.1 - TOK_ODSTOPANJE;
  return tok;
}


// pridobitev napetosti na analognem pinu
double pridobiNapetostNaPin(int pin) {
  int analog = analogRead(pin);
  double napetost = (3.3 / 4095) * analog;
  return napetost;
}

// pretvori napetost iz delilnika napetosti v dejansko napetost
double pretvoriVDejanskoNapetost(double napetost, double uporReferenca, double uporMeritev) {
  double dejanskaNapetost = napetost * (1 + (uporReferenca / uporMeritev));
  return dejanskaNapetost;
}