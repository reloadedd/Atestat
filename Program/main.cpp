#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

void back();    // prototipul functiei

void intro() {
    /*  Afiseaza pe ecran o scurta descriere a modurilor de functionare a programului:
    -> 0    - Mesaj de ajutor
    -> 1    - Cripteaza textul introdus in consola
    -> 2    - Decripteaza textul introdus in consola
    -> 3    - Cripteaza textul dintr-un fisier introdus ca argument
    -> 4    - Decripteaza textul dintr-un fisier introdus ca argument
    */

    cout << "[+] Programul poate opera in unul dintre urmatoarele moduri :" << endl;
    cout << "\t1\t- Afiseaza un mesaj de ajutor pentru o descriere completa a programului" << endl;
    cout << "\t2\t- Cripteaza textul ce urmeaza a il introduce" << endl;
    cout << "\t3\t- Decripteaza textul ce urmeaza a il introduce" << endl;
    cout << "\t4\t- Cripteaza textul dintr-un fisier text specificat" << endl;
    cout << "\t5\t- Decripteaza textul dintr-un fisier text specificat" << endl;
    cout << "\t====================" << endl;
}

void mesaj_de_ajutor() {
    cout << "\n[+] Scurta introducere" << endl;
    cout << "\t====================" << endl;
    cout << "\n\t- Cifrul lui Caesar este numit dupa Julius Caesar, care, conform lui Suetonius,";
    cout << "\n\tl-a folosit, mutand cu 3 litere textul pentru a proteja mesaje cu importanta militara.";
    cout << endl;
    cout << "\n[+] Cum functioneaza?" << endl;
    cout << "\t====================" << endl;
    cout << "\n\t- Daca am presupune ca valoarea numerica a literelor ar fi: A=1, B=2, ..., Z=26, atunci:";
    cout << "\n\t- Procesul de criptare poate fi descris printr-o functie matematica, numita Cr(x).";
    cout << "\n\t- Criptarea unei litere x (A-Z) cu o cheie n (1-26), poate fi descrisa astfel:";
    cout << "\n\t\t Cr(x) = (x + n) % 26";
    cout << "\n\t- Procesul de decriptare poate fi descris printr-o functie matematica, numita Dr(x).";
    cout << "\n\t- Decriptarea unei litere x (A-Z) cu o cheie n (1-26), poate fi descrisa astfel:";
    cout << "\n\t\t Dr(x) = (x - n) % 26" << endl;
    cout << "\n[+] Informatii suplimentare" << endl;
    cout << "\t====================" << endl;
    cout << "\n\t- In mod implicit, criptarea se realizeaza mutand literele spre partea dreapta,";
    cout << "\n\tiar decriptarea spre partea stanga.";
    cout << "\n\t- De exemplu, criptarea cu cheia 3 spre stanga este echivalenta cu criptarea cu";
    cout << "\n\tcheia 23 spre dreapta.";
    cout << "\n\t- Criptarea/Decriptarea din fisier este recomandata pentru texte de dimensiuni mari.";
    cout << "\n\t\t (Sursa: https://en.wikipedia.org/wiki/Caesar_cipher)" << endl;
    cout << "\n[+] Exemplu" << endl;
    cout << "\t====================" << endl;
    cout << "\n\t- Text normal (necriptat/plaintext) : VOM ATACA LA NOAPTE";
    cout << "\n\t- Text criptat (ciphertext) cu cheia 7: CVT HAHJH SH UVHWAL" << endl;

    back();
}

void verificare_cheie(int & cheie, bool & valid) {
    /* Verifica daca cheia introdusa de la tastatura are valoarea cuprinsa in intervalul [1, 26] */

    valid = false;
    for (int i = 3; !valid && i >= 0; i--) {
        cout << "[?] Introduceti cheia >> ";      cin >> cheie;
        if (cheie < 0 || cheie > 26) {    // Verificarea validitatii cheiii
            cout << "\n[-] Cheie invalida ! Cheia poate avea valori in intervalul [1, 26] !\n";
        }else
            valid = true;
    }
}

void verificare_fisier(ifstream &fin, bool &ok) {
    /* Verifica daca fisierul introdus de la tastatura exista si poate fi deschis
    pentru citirea datelor */

    char nume_fisier[256];
    int incercari = 3;
    ok = false;

    while (!ok && incercari >= 0) {
        cin.get();
        cout << "[?] Introduceti numele fisierului >> ";
        cin.get(nume_fisier, 256);
        fin.open(nume_fisier);
        if (fin.good()) {
            incercari = -1;
            ok = true;
        }else {
            cout << "[-] Fisierul specificat nu exista !" << endl;
            incercari--;
        }
    }
}

void clear_screen() {
    /* "Curata" consola de tot textul care era inainte */

    for (int n = 0; n < 10; n++)
        cout << "\n\n\n\n\n\n\n\n\n\n";
}

void cripteaza_consola() {
    /* Cripteaza textul introdus de la tastatura.
     * Criptarea se realizeaza prin adunarea codului ASCII al fiecarui caracter
     * introdus de la tastatura cu cheia intr-o variabila numita ascii. La fiecare pas
     * se scade 90 din acea valoare si se aduna 64 (in cazul literelor mici). Acelasi
     * procedeu este implementat si in cazul literelor mari, doar ca sunt folosite
     * valorile corespunzatoare.
     */

    bool valid;
    int cheie;
    verificare_cheie(cheie, valid);

    if (valid) {
        char text[256];
        cin.get();
        cout << "[?] Introduceti textul >> ";        cin.get(text, 255);

        for(unsigned int i = 0; i < strlen(text); i++) {
            int ascii = int(text[i]) + cheie;
            if (isupper(text[i])) {          // verificare pentru litera mare
                if (ascii > 90)
                    text[i] = (char)ascii - 90 + 64;    // 64 inseamna inclusiv "A"
                else
                    text[i] = (char)ascii;
            }else if (islower(text[i])) {      // verificare pentru litera mica
                if (ascii > 122)
                    text[i] = (char)ascii - 122 + 96;   // 96 inseamna inclusiv "a"
                else
                    text[i] = (char)ascii;
            }
        }
        cout << "\n\t[!] Textul criptat >>> " << text << endl;
    }
    back();
}

void decripteaza_consola() {
    /* Decripteaza textul introdus de la tastatura.
    Decriptarea se realizeaza adunand succesiv codul ASCII al caracterelor textului
    cu cheia(cate un caracter la fiecare pas) in variabila ascii. Daca caracterul
    de la acel pas este litera mare se verifica daca valoarea variabilei ascii depaseste
    valoarea 90 (insemnand litera Z), in caz afirmativ se va scadea 90 si aduna 64 din
    variabila ascii, rezultand astfel litera decriptata conform cheii. Acelasi
    lucru se intampla si in cazul literelor mici, caz in care se scade 122 si se aduna 96
    din variabila ascii.
    */

    bool valid;
    int cheie;
    verificare_cheie(cheie, valid);

    if (valid) {
        char text[256];
        cin.get();
        cout << "[?] Introduceti textul >> ";        cin.get(text, 255);

        cheie = 26 - cheie;     // Pentru decriptare, se muta caracterele in partea stanga
        for(unsigned int i = 0; i < strlen(text); i++) {
            int ascii = int(text[i]) + cheie;
            if (isupper(text[i])) {          // verificare pentru litera mare
                if (ascii > 90)
                    text[i] = (char)ascii - 90 + 64;    // 64 inseamna inclusiv "A"
                else
                    text[i] = (char)ascii;
            }else if (islower(text[i])) {      // verificare pentru litera mica
                if (ascii > 122)
                    text[i] = (char)ascii - 122 + 96;   // 96 inseamna inclusiv "a"
                else
                    text[i] = (char)ascii;
            }
        }
        cout << "\n\t[!] Textul decriptat >>> " << text << endl;
    }
    back();
}

void cripteaza_fisier() {
    /* Utilizeaza acelasi principiu precum functia cripteaza_consola(), diferenta constand in faptul
    ca citirea datelor se face dintr-un fisier */

    bool valid, ok;
    int cheie;
    verificare_cheie(cheie, valid);

    if (valid) {
        ifstream fisier;

        // Verificarea existentei si accesibilitatii fisierului
        verificare_fisier(fisier, ok);

        if (ok) {
            ofstream criptat("criptat.txt");
            char x;
            while (fisier >> noskipws >> x) {   // Citeste din fisier si spatiile
                int ascii = int(x) + cheie;
                if (isupper(x)) {          // verificare pentru litera mare
                    if (ascii > 90)
                        x = (char)ascii - 90 + 64;    // 64 inseamna inclusiv "A"
                    else
                        x = (char)ascii;
                }else if (islower(x)) {      // verificare pentru litera mica
                    if (ascii > 122)
                        x = (char)ascii - 122 + 96;   // 96 inseamna inclusiv "a"
                    else
                        x = (char)ascii;
                }
                criptat << x;
            }
            clear_screen();
            cout << "\t\t##################################################" << endl;
            cout << "\t\t#\t[!] Criptare reusita !\t\t\t #" << endl;
            cout << "\t\t#\t[!] Mesajul criptat in > [criptat.txt]\t #" << endl;
            cout << "\t\t##################################################" << endl;
            criptat.close();
        }
    }
    back();
}

void decripteaza_fisier() {
    /* Utilizeaza acelasi principiu precum functia decripteaza_consola(), diferenta constand in faptul
    ca citirea datelor se face dintr-un fisier */

    bool valid, ok;
    int cheie;
    verificare_cheie(cheie, valid);

    if (valid) {
        ifstream fisier;

        // Verificarea existentei si accesibilitatii fisierului
        verificare_fisier(fisier, ok);

        if (ok) {
            ofstream decriptat("decriptat.txt");
            char x;
            cheie = 26 - cheie;     // Pentru decriptare, se muta caracterele in partea stanga
            while (fisier >> noskipws >> x) {
                int ascii = int(x) + cheie;
                if (isupper(x)) {          // verificare pentru litera mare
                    if (ascii > 90)
                        x = (char)ascii - 90 + 64;    // 64 inseamna inclusiv "A"
                    else
                        x = (char)ascii;
                }else if (islower(x)) {      // verificare pentru litera mica
                    if (ascii > 122)
                        x = (char)ascii - 122 + 96;   // 96 inseamna inclusiv "a"
                    else
                        x = (char)ascii;
                }
                decriptat << x;
            }
            clear_screen();
            cout << "\t\t####################################################" << endl;
            cout << "\t\t#\t[!] Decriptare reusita !\t\t   #" << endl;
            cout << "\t\t#\t[!] Mesajul decriptat in > [decriptat.txt] #" << endl;
            cout << "\t\t####################################################" << endl;
            decriptat.close();
        }
    }
    back();
}

int main() {
    int mod, incercari = 3;  // Modul de operare al programului => functia intro() contine valorile

    intro();	// contine meniul programului (o serie de afisari)

    while (incercari > 0) {
        cout << "[?] Introduceti optiunea dorita >> ";     cin >> mod;
        if (mod >= 1 && mod <= 5)   // verific daca modul de corespunde cerintelor
            incercari = 1;  // in caz afirmativ, numarul de incercari va deveni 1,
					// caz in care se va apela functia corespunzatoare optiunii cerute

        switch(mod) {
            case 1:
                mesaj_de_ajutor();
                break;
            case 2:
                cripteaza_consola();
                break;
            case 3:
                decripteaza_consola();
                break;
            case 4:
                cripteaza_fisier();
                break;
            case 5:
                decripteaza_fisier();
                break;
            default:	// caz in care optiunea introdusa nu este corecta
                cout << "\n[-] Modul de operare introdus este invalid !\n";
                break;
        }
        incercari--;	// pentru fiecare optiune introdusa gresit, nr de
    }				    // incercari se va micsora cu 1
    return 0;
}


void back() {
    /* Solicita utilizatorul cu privire la dorinta de a se intoarce la meniul principal.
    Utilizatorului ii sunt acordate 3 incercari pentru a alege optiunea corespunzatoare
    dorintei sale. */

    char optiune[10];
    int incercari = 3;  // numarul de incercari

    while (incercari >= 0) {
        cout << "Doriti sa va intoarceti inapoi la meniu ? [Y/N] >>> ";
        cin >> optiune;

        if (strcmp(optiune, "Y") == 0 || strcmp(optiune, "N") == 0)
            incercari = -1;
        else
            incercari--;
    }

    if (strcmp(optiune, "Y") == 0) {
        clear_screen();
        main();
    }
}
