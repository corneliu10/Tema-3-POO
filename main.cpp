#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Client;
vector<int> totalClienti;

class Ciorba {
public:
    Ciorba() {};

    Ciorba(string pnume, int ppret) : pret(ppret) {
        nume = pnume;
    }
    friend ostream& operator<< (ostream &out, Ciorba &c) {
        out<<c.nume<<" "<<c.pret<<"\n";
        return out;
    }

    int getPret() {
        return pret;
    }

protected:
    int pret;
    string nume;
};

class CiorbaExtra : public Ciorba {
public:
    CiorbaExtra() {};

    CiorbaExtra(bool cuSm, bool cuArd, string pnume, int ppret) : Ciorba(pnume, ppret) {
        cuSmantana = cuSm;
        cuArdei = cuArd;
    }
    bool cuSmantana;
    bool cuArdei;
};

class FelPrincipal;
class Comanda;

class Garnitura {
friend FelPrincipal;
protected:
    int pret;
    string nume;
public:
    Garnitura() {}
    Garnitura(string pnume, int pret) : pret(pret) {
        nume = pnume;
    }

    friend ostream& operator<<(ostream &out, Garnitura &g) {
        out<<g.nume<<" "<<g.pret;
        return out;
    }

    Garnitura& operator=(const Garnitura& other) {
        pret = other.pret;
        nume = other.nume;

        return *this;
    }

    int getPret() {
        return pret;
    }
};

class Cartofi : public Garnitura{
private:
    bool prajiti; // daca nu sunt prajiti atunci vor fi piure
public:
    Cartofi() {};

    Cartofi(bool prajiti, string nume, int pret) : Garnitura(nume, pret) {
        this->prajiti = prajiti;
    }
};

class FelPrincipal {

friend Garnitura;
protected:
    string carne;
    int pretCarne;
    string nume;
    Garnitura *garnitura;
public:
    FelPrincipal() {};

    int getPret() {
        return pretCarne;
    }

    FelPrincipal(string carne, int pret, string nume) {
        this->carne = carne;
        this->pretCarne = pret;
        this->nume = nume;
    }

    void adaugaGarnitura(Garnitura *g) {
        this->garnitura = g;
    }

    virtual int calcPretTotal() {
        return pretCarne + garnitura->pret;
    }
};

class FelPrincipalVita : public FelPrincipal {
private:
    unsigned int catDeBineFacut; // 0 - 10
    int gramaj;
public:
    FelPrincipalVita() {};

    FelPrincipalVita(int pret, string nume, unsigned int catDeBine, int gramaj) : FelPrincipal("vita", pret, nume) {
        catDeBineFacut = catDeBine;
        this->gramaj = gramaj;
    }

    virtual int calcPretTotal() {
        return pretCarne * (gramaj / 100) + garnitura->getPret();
    }
};

class Desert {
protected:
    int pret;
    string nume;

public:
    int getPret() {
        return pret;
    }

    Desert() {};
    Desert(int pret, string nume) : pret(pret), nume(nume) {}

    virtual int calcPret() {
        return pret;
    }
};

class Inghetata : public Desert {
private:
    int cupe; // 3 - 5 cupe
public:
    Inghetata() {};
    Inghetata(int pret, string nume, int cupe) : Desert(pret, nume), cupe(cupe) {}

    virtual int calcPret() {
        return pret*cupe;
    }
};

class Bautura {
protected:
    int pret;
    int cantitate;
    string nume;
public:
    Bautura() {};
    Bautura(int pret, int cantitate, string nume) : pret(pret), cantitate(cantitate), nume(nume) {}
    void operator=(const Bautura *&other) {
        pret = other->pret;
        cantitate = other->cantitate;
        nume = other->nume;

    }

    int getPret() {
        return pret;
    }
};

class SticlaDeVin : public Bautura {
private:
    string marca;
    int anVechime;
public:
    SticlaDeVin() {};
    SticlaDeVin(int pret, int cantitate, string nume, string marca, int an) : Bautura(pret, cantitate, nume),
                                                                              marca(marca), anVechime(an) {}
};

class Bere : public Bautura {
private:
    bool cuAlcool;

public:
    Bere() {};
    Bere(int pret, int cantitate, string nume, bool cuAl) : Bautura(pret, cantitate, nume), cuAlcool(cuAl) {}
};


class Comanda {
public:
    Bautura *bautura;
    Ciorba *ciorba;
    FelPrincipal *felPrincipal;
    Desert *desert;
    int pretTotal;

    int getPretTotal() {
        return pretTotal;
    }

    Comanda() {};

    Comanda(Bautura *b, Ciorba *c, FelPrincipal *f) {
        bautura = b;
    }

    Comanda& operator=(const Comanda &other) {
        bautura = other.bautura;
        ciorba = other.ciorba;
        felPrincipal = other.felPrincipal;

        return *this;
    }
};

class Client {
private:
    static int nrClienti;
    Comanda comanda;
public:
    Client() {nrClienti++;}
    void adaugaComanda(Comanda cmd) {
        comanda = cmd;
    }
    int getNrClienti() {
        return nrClienti;
    }

    void Meniu() {
        cin.get();
        char s[100];
        cout<<"De baut va aduc ceva?\n";
        cin.getline(s,100);
        if(strcmp(s,"Nu")==0)
            comanda.bautura = NULL;
        else
        {
            cout<<"Vin,bere sau apa?\n";
            cin.getline(s,100);
            if(strcmp(s,"Vin")==0) comanda.bautura = new SticlaDeVin;
            else if(strcmp(s,"Bere")==0) comanda.bautura= new Bere;
            else comanda.bautura= new Bautura;
            comanda.pretTotal += comanda.bautura->getPret();
        }
        cout<<"Doriti ciorba?\n";
        cin.getline(s,100);
        if(strcmp(s,"Da")==0)
        {
            comanda.ciorba = new Ciorba;
            comanda.pretTotal += comanda.ciorba->getPret();
        }
        cout<<"Doriti fel principal?\n";
        cin.getline(s,100);
        if(strcmp(s,"Da")==0)
        {
            cout<<"De pui sau de vita?\n";
            cin.getline(s,100);
            if(strcmp(s,"De pui")==0)
                comanda.felPrincipal = new FelPrincipal;
            else comanda.felPrincipal = new FelPrincipalVita;
            comanda.pretTotal += comanda.felPrincipal->getPret();
        }
        cout<<"Doriti garnitura?\n";
        cin.getline(s,100);
        if(strcmp(s,"Da")==0)
        {
            comanda.felPrincipal->adaugaGarnitura(new Garnitura);
            comanda.pretTotal += comanda.felPrincipal->getPret();
        }
        cout<<"Doriti desert?\n";
        cin.getline(s,100);
        if(strcmp(s,"Da")==0)
        {
            comanda.desert = new Desert;
            comanda.pretTotal += comanda.desert->getPret();
        }
    }
};

int Client::nrClienti = 0;

class Masa {
private:
    int nrLocuri;
    int nrLocuriLibere;
    vector<Client*> clienti;
    int notaDePlata;
public:
    Masa() {
        cout<<"Dati nr de persoane la o masa: ";
        cin>>nrLocuri;
        Client *c;

        for(int i=0; i < nrLocuri; i++) {
            c = new Client;
            clienti.push_back(c);
        }
        nrLocuriLibere = 0;
        notaDePlata = 0;
    }

    void Comanda() {
        for(int i=0;i<clienti.size();i++)
            clienti[i]->Meniu();
    }

    ~Masa() {
        clienti.clear();
    }
};

void run() {
    int n = 10;
    vector<Masa*> mese;
    mese.push_back(new Masa);
    mese[0]->Comanda();
}

int main()
{
    run();
}
