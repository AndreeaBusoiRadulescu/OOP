#include<iostream>
#include<string>
#include<math.h>
using namespace std;

//Sa se realizeze o aplicație C++ pentru a simula diferite elemente de grafica care sa implementeze ierarhia de clase descrisă si care să respecte următoarele cerințe
//
//
//
//1. Soluția definește o excepție proprie prin clasa MySpecialException ce extinde exception.Excepția este aruncată în toate situațiile în care valorile de intrare nu respectă regulile de validare
//
//2. Clasa Punct descrie un punct într - un spațiu 2D / 3D și conține
//
//x – atribut de tip întreg
//y – atribut de tip întreg
//z – atribut de tip întreg
//Atributele sunt inițializate implicit cu 0
//Clasa nu are constructor default
//Clasa are 2 constructori: unul care solicita X si Y si altul care solicită toate valorile
//Clasa are metode de tip get si set pentru cele 3 valori
//
//
//Fiecare figură geometrică este definită de un număr dat de colțuri(liniile ce le unesc definesc figura geometrică)
//
//3. Clasa FiguraGeometricaAbstracta conține
//
//tip Figura – atribut de tip string
//este2D – atribut de tip boolean
//număr colțuri – atribut de tip întreg
//vector Colțuri – vector dinamic de obiecte de tip Punct
//arie() – metodă virtuală pură ce determină aria figurii geometrice
//perimetru() – metodă virtuală pură ce determină aria figurii geometrice
//getColturi() – metoda ce afișează colțurile figurii geometrice folosind șablonul(X, Y) pentru 2D si(X, Y, Z) pentru 3D
//adaugaColt() – metodă ce adaugă un nou colt
//getTip() – metodă ce returnează un string ce reprezintă tipul figurii geometrice și dacă este 2D / 3D
//clasa definește un constructor ce primește minim tipul figurii(se accepta și constructor care să primească un vector de puncte existent)
//destructor, operator= si constructor de copiere care sa evite shallow copy si memory leaks
//
//
//4. Se vor implementa minim 5 clase care sa reprezinte diferite tipuri de figuri geometrice 2D(minim 3 cum ar fi trapez, triunghi, dreptunghi, elipsa) sau 3D(minim 2 cum ar fi cub, prisma, sfera, cilindru etc)
//
//Clasele definite la acest nivel :
//
//vor supradefini metodele arie si perimetru
//vor oferi constructori particulari
//vor adaugă o metodă proprie specifică figurii geometrice în cauza(la alegere)
//5. La alegere 2 sau 3 clase din cele definite la punctul anterior se vor particulariza prin extinderea lor(de exemplu triunghi se extinde in triunghi echilateral, isoscel sau dreptunghic; sau dreptunghi se extinde in patrat; etc)
//
//Clasele definite la acest nivel :
//
//vor supradefini metodele arie si perimetru
//vor oferi constructori particulari
//vor adaugă o metodă proprie specifică figurii geometrice în cauza(la alegere)
//
//
//6. In programul principal, clasele definite la punctul anterior vor fi folosite pentru a construi și inițializa un vector dinamic de figuri geometrice.Dimensiunea si datele figurilor geometrice sunt preluate de la consola sau dintr - un fișier text(la alegere - fiecare are libertatea de a decide cum preia datele de intrare)
//
//Pentru fiecare element din vector va fi afișat tipul, lista de colțuri și apoi vor fi afișate datele cu privire la perimetru și suprafața
//Se definește interfața IPrintabilLaConsola (clasa abstractă ce conține doar metode virtuale pure) ce definește metoda virtuala pura:
//
//PrintConsola() ce afisează figura geometrică la consola(grafică ASCII sau orice altă soluție – chiar și text; exemplu http ://www.asciiworld.com/-Geometry-.html) NU este obligatorie partea de grafică ASCII însă trebuie aleasă o soluție care să afișeze la consola datele figurii geometrice

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