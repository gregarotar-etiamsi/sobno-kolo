// osnoven program za merjenje električne napetosti do maksimalno 330V

#define NAPETOST_PIN 35

// delilnik napetosti na za maksimalno 330V
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
void loop() {
    napetost = pridobiIzhodnoNapetost();
    Serial.println(napetost);
    delay(1000);

}


// pridobitev izhodne napetosti
double pridobiIzhodnoNapetost()
{
    double pinVoltage = pridobiNapetostNaPin(NAPETOST_PIN);
    return pretvoriVDejanskoNapetost(pinVoltage, NAPETOST_UPOR_REFERENCA, NAPETOST_UPOR_MERITEV);
}

// pridobitev napetosti na analognem pinu
double pridobiNapetostNaPin(int pin)
{
    int analog = analogRead(pin);
    double napetost = (3.3 / 4095) * analog;
    return napetost;
}

// pretvori napetost iz delilnika napetosti v dejansko napetost
double pretvoriVDejanskoNapetost(double napetost, double uporReferenca, double uporMeritev)
{
    double dejanskaNapetost = napetost * (1 + (uporReferenca / uporMeritev));
    return dejanskaNapetost;
}