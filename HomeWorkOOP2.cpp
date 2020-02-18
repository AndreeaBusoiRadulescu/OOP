#include<iostream>
#include<string>
#include<math.h>
using namespace std;

class MySpecialException : public exception
{
	string mesaj;

public:
	MySpecialException(const char* mesaj) {
		this->mesaj = string(mesaj);
	}

	virtual const char* what() const throw () {
		return mesaj.c_str();
	}
};

class Punct {
	int x = 0;
	int y = 0;
	int z = 0;
public:

	Punct(int x, int y) {
		this->x = x;
		this->y = y;
	}

	Punct(int x, int y, int z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	int getx() {
		return this->x;
	}

	int gety() {
		return this->y;
	}

	int getz() {
		return this->z;
	}

	void setx(int x) {
		this->x = x;
	}

	void sety(int y) {
		this->x = x;
	}

	void setz(int z) {
		this->z = z;
	}
};

class IPrintabilLaConsola {
public:
	virtual void PrintConsola() = 0;
	virtual bool intersectieSpatiu2D() = 0;
};

class FiguraGeometricaAbstracta {
protected:
	string tipFigura = "";
	bool este2D;
	int numarColturi = 0;
	Punct* vectorColturi[8];

	virtual float arie() = 0;
	virtual float perimetru() = 0;

public:

	FiguraGeometricaAbstracta(string tipFigura, bool este2D, int numarColturi, Punct* vectorColturi[]) {

		if (numarColturi < 0)
		{
			throw new MySpecialException("Numarul de colturi nu poate fi negativ!");
		}
		if (vectorColturi == NULL)
		{
			throw new MySpecialException("Vector de colturi invalid!");
		}
		if (tipFigura.length() < 3)
		{
			throw new MySpecialException("Tipul figurii poate avea minim 3 litere!");
		}

		this->tipFigura = tipFigura;
		this->este2D = este2D;
		this->numarColturi = numarColturi;
		for (int i = 0; i < numarColturi; i++)
			this->vectorColturi[i] = vectorColturi[i];
	}

	FiguraGeometricaAbstracta(FiguraGeometricaAbstracta& figura) {
		this->tipFigura = figura.tipFigura;
		this->este2D=figura.este2D;
		this->numarColturi = figura.numarColturi;
		for (int i = 0; i < numarColturi; i++)
			this->vectorColturi[i] = figura.vectorColturi[i];
	}

	void AdaugaColt(Punct &punct)
	{
		vectorColturi[numarColturi] = &punct;
		numarColturi++;
	}

	void getTip() {
		cout << "Figura " << this->tipFigura;
		if (this->este2D) {
			cout << "este 2D";
		}
		else {
			cout << "este 3D";
		}
	}

	FiguraGeometricaAbstracta &operator=(FiguraGeometricaAbstracta &figura)
	{
		if (this == &figura)
			return *this;
		this->tipFigura = figura.tipFigura;
		this->este2D = figura.este2D;
		this->numarColturi = figura.numarColturi;
		for (int i = 0; i < numarColturi; i++) {
			this->vectorColturi[i] = figura.vectorColturi[i];
		}
		return *this;
	}

	void getColturi() {
		if (este2D)
			for (int i = 0; i < numarColturi; i++)
				cout << "(" << (*vectorColturi[i]).getx() << "," << (*vectorColturi[i]).gety() << "); " << endl;
		else
			for (int i = 0; i < numarColturi; i++)
				cout << "(" << (*vectorColturi[i]).getx() << "," << (*vectorColturi[i]).gety() << "," << (*vectorColturi[i]).getz() << "); " << endl;
	}
	
	~FiguraGeometricaAbstracta() {
		cout << "apel destructor";
	}
};

class Triunghi : public FiguraGeometricaAbstracta, public IPrintabilLaConsola{
protected:
	int inaltime;
	int baza;

public:
	Triunghi(string tipFigura, bool este2D, int numarColturi, Punct* vectorColturi[3], int inaltime, int baza) :FiguraGeometricaAbstracta(tipFigura, este2D, numarColturi, vectorColturi) {
		
		if (inaltime < 0)
		{
			throw new MySpecialException("Inaltimea nu poate fi un numar negativ!");
		}

		if (baza < 0)
		{
			throw new MySpecialException("Baza nu poate fi un numar negativ!");
		}
		
		this->inaltime = inaltime;
		this->baza = baza;
	}

	float arie() {
		return (float)(this->baza * this->inaltime / 2);
	}

	float calculLungimeLatura(int punct1, int punct2) {
		int x1, x2, y1, y2;

		x1 = (*vectorColturi[punct1]).getx();
		x2 = (*vectorColturi[punct2]).getx();
		y1 = (*vectorColturi[punct1]).gety();
		y2 = (*vectorColturi[punct2]).gety();

		return (float)sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	}

	float perimetru() {
		return  this->calculLungimeLatura(0, 1) + this->calculLungimeLatura(1, 2) + this->calculLungimeLatura(0, 2);
	}

	float razaCercInscrisTriunghiului() {
		return 2 * (this->arie() / this->perimetru());
	}

	void PrintConsola() {
		cout << "Tip figura: " << this->tipFigura << endl;
		cout << "Colturile figurii: " << endl;
		this->getColturi();
		cout << "Perimetrul figurii: ";
		cout << this->perimetru() << endl;
		cout << "Aria figurii: ";
		cout << this->arie();
		cout << endl;
	}

	bool intersectieSpatiu2D()
	{
		return true;
	}

};

class TriunghiEchilateral :public Triunghi {
public:
	TriunghiEchilateral(string tipFigura, bool este2D, int numarColturi,
		Punct* vectorColturi[3], int inaltime, int baza) :Triunghi(tipFigura,
			este2D, numarColturi, vectorColturi, inaltime, baza) {
		cout << "apel constructor";
	}

	float arie() {
		return (float) (pow(this->baza, 2) * sqrt(3) / 4);
	}

	float perimetru() {
		return (float) (this->baza * 3);
	}

	float  razaCerculuiCircumscris() {
		return (float) (this->arie() / sqrt(3));
	}
};

class Dreptunghi : public FiguraGeometricaAbstracta, public IPrintabilLaConsola {
protected:
	int laturaMica;
	int laturaMare;
public:
	Dreptunghi(string tipFigura, bool este2D, int numarColturi, Punct* vectorColturi[4], int laturaMica, int laturaMare) :FiguraGeometricaAbstracta(tipFigura, este2D, numarColturi, vectorColturi) {
		
		if (laturaMare < 0 || laturaMica < 0)
		{
			throw new MySpecialException("Laturile nu pot fi un numar negativ!");
		}

		this->laturaMica = laturaMica;
		this->laturaMare = laturaMare;
	}

	float arie() {
		return (float) this->laturaMare * this->laturaMica;
	}

	float perimetru() {
		return (float) ((this->laturaMare * 2) + (this->laturaMica * 2));
	}

	float calculDiagonala() {
		return (float) sqrt(pow(this->laturaMare, 2) + pow(laturaMica, 2));
	}

	void PrintConsola() {
		cout << "Tip figura: " << this->tipFigura << endl;
		cout << "Colturile figurii: " << endl;
		this->getColturi();
		cout << "Perimetrul figurii: ";
		cout << this->perimetru() << endl;
		cout << "Aria figurii: ";
		cout << this->arie();
		cout << endl;
	}

	bool intersectieSpatiu2D()
	{
		return true;
	}

};

class Patrat :public Dreptunghi{
public:
	Patrat(string tipFigura, bool este2D, int numarColturi, Punct* vectorColturi[4],
		int latura) :Dreptunghi(tipFigura, este2D, numarColturi,
			vectorColturi, latura, 0) {
	
		//cout << "apel constructor";
	}

	float arie() {
		return (float) pow(this->laturaMica, 2);
	}

	float perimetru() {
		return (float) this->laturaMica * 4;
	}

	float diagonala() {
		return (float) sqrt(2)*this->laturaMica;
	}

	void PrintConsola() {
		cout << "Tip figura: " << this->tipFigura << endl;
		cout << "Colturile figurii: " << endl;
		this->getColturi();
		cout << "Perimetrul figurii: ";
		cout << this->perimetru() << endl;
		cout << "Aria figurii: ";
		cout << this->arie();
		cout << endl;
	}

	bool intersectieSpatiu2D()
	{
		return true;
	}

};

class Cerc : public FiguraGeometricaAbstracta {
	int raza;
public:
	Cerc(string tipFigura, bool este2D, int numarColturi, Punct* vectorColturi[1], int raza) :FiguraGeometricaAbstracta(tipFigura, este2D, numarColturi, vectorColturi) {
		
		if (raza < 0)
		{
			throw new MySpecialException("Raza nu poate fi un numar negativ!");
		}

		this->raza = raza;
	}

	float arie() {
		return (float) (this->raza * 3.14 * 2);
	}

	float perimetru() {
		return (float) (this->raza * 2 * 3.14); //lungimea cercului
	}

	int diametru() {
		return this->raza * 2;
	}
};

class Cub : public FiguraGeometricaAbstracta {
	int vectorLatura[2];
public:
	Cub(string tipFigura, bool este2D, int numarColturi, Punct* vectorColturi[8], int* vectorLatura) :FiguraGeometricaAbstracta(tipFigura, este2D, numarColturi, vectorColturi) {
		
		if (vectorLatura == NULL)
		{
			throw new MySpecialException("Vectorul de laturi este invalid!");
		}

		this->vectorLatura[0] = vectorLatura[0];
		this->vectorLatura[1] = vectorLatura[1];
	}

	float calculLungimeLatura() {
		int x1, x2, y1, y2;

		x1 = (*vectorColturi[vectorLatura[0]]).getx();
		x2 = (*vectorColturi[vectorLatura[1]]).getx();
		y1 = (*vectorColturi[vectorLatura[0]]).gety();
		y2 = (*vectorColturi[vectorLatura[1]]).gety();

		return (float) (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
	}

	float arie() {
		return pow(this->calculLungimeLatura(), 2) * 6;
	}

	float perimetru() {
		return this->calculLungimeLatura() * 12;
	}

	float volum() {
		return pow(this->calculLungimeLatura(), 3);
	}
};

class Sfera : public FiguraGeometricaAbstracta {
private:
	int raza;

public:
	Sfera(string tipFigura, bool este2D, int numarColturi, Punct* vectorColturi[1], int raza) :FiguraGeometricaAbstracta(tipFigura, este2D, numarColturi, vectorColturi) {
		
		if (raza < 0)
		{
			throw new MySpecialException("Raza nu poate fi un numar negativ!");
		}

		this->raza = raza;
	}

	float arie() {
		return (float) (pow(raza, 2) * 4 * 3.14);
	}

	float perimetru() {
		return (float) (this->raza * 2 * 3.14); //lungimea unui cerc cu raza sferei 
	}

	float volum() {
		return (float) (pow(raza, 3) * 4 * 3.14 / 3);
	}

};


int  main() {
	Punct p1(2, 3);
	Punct p2(4, 5);
	Punct p3(1, 0);
	Punct p4(2, 4);

	Punct* colturiDate[4];
	colturiDate[0] = &p1;
	colturiDate[1] = &p2;
	colturiDate[2] = &p3;
	colturiDate[3] = &p4;
	//vectorFiguriGeometrice[1] = new Sfera("sfera", false, 1, &(colturiDate[0]), 10);
	
	FiguraGeometricaAbstracta* vectorFiguriGeometrice[3];
	int numarColturi = 4;

	cout <<endl<< "----Testare exceptii-----" << endl;

	try {
		vectorFiguriGeometrice[0] = new Dreptunghi("dreptunghi", true, -1, colturiDate, 3, 4);
	}
	catch (MySpecialException *ex)
	{
		cout<< endl<< ex->what() << endl;
	}

	try {
		vectorFiguriGeometrice[1] = new Triunghi("triunghi", true, 3, NULL, 5, 6);
	}
	catch (MySpecialException *ex)
	{
		cout << endl << ex->what() << endl;
	}

	cout << endl << "----Testare afisari + operator= -----" << endl;

	vectorFiguriGeometrice[0] = new Dreptunghi("dreptunghi", true, numarColturi, colturiDate, 3, 4);
	vectorFiguriGeometrice[1] = new Triunghi("triunghi", true, 3, colturiDate, 5, 6);
	vectorFiguriGeometrice[2] = new Patrat("patrat", true, 4, colturiDate, 5);

	((Dreptunghi*)vectorFiguriGeometrice[0])->PrintConsola();
	((Triunghi*)vectorFiguriGeometrice[1])->PrintConsola();
	((Patrat*)vectorFiguriGeometrice[2])->PrintConsola();
	Dreptunghi *d2 = ((Dreptunghi*)vectorFiguriGeometrice[0]);
	d2->PrintConsola();

	cout << endl << "----Testare functie adaugat/afisat colturi -----" << endl;

	for (int i = 0; i < 3; i++)
	{
		Punct *p = new Punct(4, 5, 6);
		vectorFiguriGeometrice[i]->AdaugaColt(*p);
		vectorFiguriGeometrice[i]->getColturi();
		cout << endl;
	}

	cout << endl << "----Testare polimorfism IPrintabilLaConsola -----" << endl;

	IPrintabilLaConsola *vector_printabil[2];
	vector_printabil[0] = new Dreptunghi("dreptunghi", true, numarColturi, colturiDate, 20, 40);
	vector_printabil[1] = new Patrat("patrat", true, 4, colturiDate, 20);
	for (int i = 0; i < 2; i++)
	{
		vector_printabil[i]->PrintConsola();
		cout << endl;
	}
}