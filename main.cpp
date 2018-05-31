#include <iostream>
#include <vector>
#include <cstring>
#include <pthread>

using namespace std;

class Client;
vector<int> totalClienti;
vector<Masa*> mese;

class Ciorba {
public:
    Ciorba() {
        };

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

    virtual int calcPretTotal() {
        return pretCarne + 12;
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
        return pretCarne * (gramaj / 100) + 15;
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
    Garnitura *garnitura;
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

    int getPret() {
        return comanda.pretTotal;
    }

    void Meniu() {
        char s[100];
        comanda.pretTotal = 0;
        cout<<"De baut va aduc ceva?\n";
        cin.getline(s,100);
        if(strcmp(s,"nu")==0)
            comanda.bautura = NULL;
        else
        {
            cout<<"Vin,bere sau apa?\n";
            cin.getline(s,100);
            if(strcmp(s,"vin")==0) comanda.bautura = new SticlaDeVin(13, 100, "Bourboun", "deluxe", 1998);
            else if(strcmp(s,"bere")==0) comanda.bautura= new Bere(15, 330, "Heineken", true);
            else comanda.bautura= new Bautura(8, 250, "Dorna");
            comanda.pretTotal += comanda.bautura->getPret();
        }
        cout<<"Doriti ciorba?\n";
        cin.getline(s,100);
        if(strcmp(s,"da")==0)
        {
            cout<<"De care?De burta,de legume sau de ciuperci?\n";
            cin.getline(s,100);

            if(strcmp(s,"de ciuperci")==0) { comanda.ciorba = new Ciorba("ciuperci",13); };
            if(strcmp(s,"de burta")==0) {
                    cout<<"Cu sau fara smantana?\n";
                    cin.getline(s,100);

                    if(strcmp(s,"cu")==0)
                        comanda.ciorba = new CiorbaExtra(false, true,"burta", 14);
                    else
                        comanda.ciorba = new CiorbaExtra(false, false,"burta", 12);
            }
            if(strcmp(s,"de legume")==0) {
                cout<<"Cu sau fara smantana?\n";
                    cin.getline(s,100);

                    if(strcmp(s,"cu")==0)
                        comanda.ciorba = new CiorbaExtra(false, true,"legume", 14);
                    else
                        comanda.ciorba = new CiorbaExtra(false, false,"legume", 12);
             }
            comanda.pretTotal += comanda.ciorba->getPret();
        }
        cout<<"Doriti fel principal?\n";
        cin.getline(s,100);
        if(strcmp(s,"da")==0)
        {
            cout<<"De pui sau de vita?\n";
            cin.getline(s,100);
            if(strcmp(s,"de pui")==0)
                comanda.felPrincipal = new FelPrincipal("pui", 18,"Garno");
            else comanda.felPrincipal = new FelPrincipalVita(22, "Biso", 4, 200);
            comanda.pretTotal += comanda.felPrincipal->getPret();
        }

        cout<<"Doriti garnitura?\n";
        cin.getline(s,100);
        if(strcmp(s,"da")==0)
        {
            cout<<"Cartfoi sau orez?\n";
            cin.getline(s,100);
            if(strcmp(s,"cartofi")==0)
                comanda.garnitura = new Cartofi(true, "cartofi", 9);
            else
                comanda.garnitura = new Garnitura("orez", 9);
            comanda.pretTotal += comanda.garnitura->getPret();
        }
        cout<<"Doriti desert?\n";
        cin.getline(s,100);
        if(strcmp(s,"da")==0)
        {
            cout<<"Krantz sau Inghetata?\n";
            cin.getline(s,100);
            if(strcmp(s,"krantz")==0)
                comanda.desert = new Desert(9, "krantz");
            else
                comanda.desert = new Inghetata(4, "ciocolata", 3);
            comanda.pretTotal += comanda.desert->getPret();
        }

        cout<<"Pret comanda: "<<comanda.pretTotal<<"\n\n";
    }
};

int Client::nrClienti = 0;

class Masa {
private:
    static int nrMese;
    int nrLocuri;
    int nrLocuriLibere;
    vector<Client*> clienti;
    int notaDePlata;
public:
    Masa() {
        nrMese++;
        cout<<"Dati nr de persoane la masa "<< nrMese<<" : ";
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
        cin.get();
        for(int i=0;i<clienti.size();i++)
        {
            cout<<"Comanda clientului : "<<i+1<<"\n";
            clienti[i]->Meniu();
            notaDePlata += clienti[i]->getPret();
        }

        cout<<"\nNota masa: "<<notaDePlata<<"\n";
    }

    ~Masa() {
        clienti.clear();
        nrMese--;
    }
};

int Masa::nrMese = 0;

void *PrintHello(void *threadId) {
    mese.push_back(new Masa);

    pthread_exit(NULL);
}

void run() {
    int n = 10;
    pthread_t threads[5];

    for(int i = 1; i <= 5; ++i) {
        rc = pthread_create(&threads[i], NULL, addMasa, (void *)i);

        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }

    mese[0]->Comanda();
}

int main()
{
    run();
}
