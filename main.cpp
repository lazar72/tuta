#include <bits/stdc++.h> 
using namespace std;

/*
 Funkcija za ispis trenutnog stanja lavirinta.
 Prikazuje igru u konzoli, sa pozicijama:
 - C = Cilj
 - U = Igrač
 - M = Mumija
 - 1 = Zid
 - 0 = Prazno
*/
void ispis(int a[][11], int n, int m, int cr, int ck, int ur, int uk, int mr, int mk) {
    system("cls"); // Briše ekran pri svakom ispisu
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == cr && j == ck) {
                cout << "C" << " ";
            }
            else if (i == ur && j == uk) {
                cout << "U" << " "; // Igrač
            }
            else if (i == mr && j == mk) {
                cout << "M" << " "; // Mumija
            }
            else {
                cout << a[i][j] << " "; // Zid ili prolaz
            }
        }
        cout << endl;
    }
    cout << endl << endl;
}

/*
 Funkcija za pomeranje igrača u skladu sa unetom komandom.
 Komande: "gore", "dole", "levo", "desno".
 Proverava da li je sledeće polje prolazno (nije zid).
*/
bool potez(int nivo[][11], string komanda, int& ur, int& uk) {
    if (komanda == "gore" && nivo[ur - 1][uk] != 1) {
        ur--; return true;
    }
    else if (komanda == "dole" && nivo[ur + 1][uk] != 1) {
        ur++; return true;
    }
    else if (komanda == "levo" && nivo[ur][uk - 1] != 1) {
        uk--; return true;
    }
    else if (komanda == "desno" && nivo[ur][uk + 1] != 1) {
        uk++; return true;
    }
    else if (komanda == "ostani") {
            return true;}
    else {
        cout << "probaj opet." << endl; // Ako je pokušano kretanje u zid
        return false;
    }
}

/*
 Funkcija za pomeranje mumije.
 Mumija se kreće prvo horizontalno ka igraču, pa ako ne može, ide vertikalno.
 Kreće se dva puta po potezu igrača.
*/
void mumija(int nivo[][11], int ur, int uk, int& mr, int& mk) {
    if (uk < mk && nivo[mr][mk - 1] == 0) {
        mk--; // Levo
    }
    else if (uk > mk && nivo[mr][mk + 1] == 0) {
        mk++; // Desno
    }
    else {
        if (ur < mr && nivo[mr - 1][mk] == 0) {
            mr--; // Gore
        }
        else if (ur > mr && nivo[mr + 1][mk] == 0) {
            mr++; // Dole
        }
    }
}

int main() {
    string komanda;       // Komanda koju igrač unosi
    int ur1 = 1, uk1 = 1; // ur1, uk1 = pozicija igrača (U) na mapi
    int cr1 = 9, ck1 = 9; // cr1, ck1 = pozicija cilja (C)
    int mr1 = 1, mk1 = 9; // mr1, mk1 = pozicija mumije (M)
    bool pomeri = false; // Flag koji označava da li je igrač uspešno napravio potez

    // Definicija nivoa - lavirint 11x11 (1 = zid, 0 = prolaz)
    int nivo1[11][11] = {
                         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                         {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                         {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
                         {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
                         {1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1},
                         {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
                         {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                         {1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1},
                         {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
                         {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    // Početni prikaz
    ispis(nivo1, 11, 11, cr1, ck1, ur1, uk1, mr1, mk1);

    /*
     Glavna petlja igre:
     - Igrač se pomera sve dok ne dođe do cilja (levo od C) ili ga ne stigne mumija.
    */
    while ((ur1 != cr1 || uk1 != (ck1 - 1)) && (ur1 != mr1 || uk1 != mk1)) {
        while (pomeri == false) { // Ponavlja unos dok igrač ne napravi ispravan potez
            cin >> komanda;
            pomeri =potez(nivo1, komanda, ur1, uk1);
            ispis(nivo1, 11, 11, cr1, ck1, ur1, uk1, mr1, mk1);
        }
        // Mumija se pomera dva puta nakon svakog uspešnog poteza igrača
        mumija(nivo1, ur1, uk1, mr1, mk1);
        mumija(nivo1, ur1, uk1, mr1, mk1);
        ispis(nivo1, 11, 11, cr1, ck1, ur1, uk1, mr1, mk1);
        pomeri = false;
    }
}
