// osnoven program za merjenje električne napetosti do maksimalno 330V

#define NAPETOST_PIN 35

// delilnik napetosti za maksimalno 330V
#define NAPETOST_UPOR_REFERENCA 660000
#define NAPETOST_UPOR_MERITEV 6600

void setup()
{
    // omogoči izpis vrednosti preko serial komunikacie
    Serial.begin(9600);
    // nastavi pin za napetost na input
    pinMode(NAPETOST_PIN, INPUT);
}

double napetost;
void loop()
{
    // pridobitev napetosti
    napetost = pridobiIzhodnoNapetost();
    // izpis napetosti prek serial komunikacije
    Serial.println(napetost);
    // program počaka 1 sekundo (1000ms)
    delay(1000);
}

// pridobitev izhodne napetosti
double pridobiIzhodnoNapetost()
{
    // pridobiNapetostNaPin --> glej poglavje Programske funkcije za branje analognih vhodov
    double pinVoltage = pridobiNapetostNaPin(NAPETOST_PIN);
    // dejanska napetost brez delinika napetosti
    // pretvoriVDejanskoNapetost --> glej poglavje Programske funkcije za branje analognih vhodov
    return pretvoriVDejanskoNapetost(pinVoltage, NAPETOST_UPOR_REFERENCA, NAPETOST_UPOR_MERITEV);
}

// pridobitev napetosti na analognem pinu
double pridobiNapetostNaPin(int pin)
{
    // analogRead vrne 12 bitno število
    int analog = analogRead(pin);
    double napetost = (3.3 / 4095) * analog;
    return napetost;
}

// pretvori napetost iz delilnika napetosti v dejansko napetost
double pretvoriVDejanskoNapetost(double napetost, double uporReferenca, double uporMeritev)
{
    // uporReferenca predstavlja referenci upor, na katerem ne merimo napetosti
    // uporMeritev predstavlja upor, na katerem merimo napetost
    double dejanskaNapetost = napetost * (1 + (uporReferenca / uporMeritev));
    return dejanskaNapetost;
}