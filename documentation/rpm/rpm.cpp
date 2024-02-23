// osnoven program za merjenje števila obratov na minuto z magnetnim stikalom

// pin magnetnega stikala
#define RPM_STIKALO_PIN 5

// maksimalen RPM, ki najvrjetnjeje ne bo presežen
// se uporablja zato, da ločimo dejanski obrat od lažnih stikov stikala
#define MAX_RPM 250.0
// cas enega obrata pri MAX_RPM
#define MIN_OBRAT_CAS ((1.0 / (MAX_RPM / 60.0)) * 1000.0)

void setup()
{
    // omogoči izpis vrednosti preko serial komunikacie
    Serial.begin(9600);

    pinMode(RPM_STIKALO_PIN, INPUT);
}
// čas, ko je bilo stikalo nazadnje sklenjeno
unsigned int casZaznanegaObrata;
// čas enega obrata
unsigned int casObrata;
// vrednost RPM
double rpm;

void loop()
{
    // če je stikalo sklenjeno (LOW, ker je stikalo vezano na GND)
    if (digitalRead(RPM_STIKALO_PIN) == LOW)
    {
        // če je čas od zadnje meritve večji od minimalnega
        if (millis() - casZaznanegaObrata > MIN_OBRAT_CAS)
        {
            casObrata = millis() - casZaznanegaObrata;
            // izračun RPM
            rpm = izracunajRpm(casObrata);
            // posodobitev casZaznanegaObrata na trenutni čas
            casZaznanegaObrata = millis();
        }
    }
    // izpis rpm prek serial komunikacije
    Serial.println(rpm);
}

double izracunajRpm(int casMS)
{
    // casMS predstavlja cas enega obrata v ms
    double rpm = 60.0 / (casMS / 1000.0);
    return rpm;
}