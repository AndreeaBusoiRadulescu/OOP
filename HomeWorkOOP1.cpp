#include <iostream>
#include <string>
#include <exception>
using namespace std;

class Assignment3Exception : public exception {

};

//a fidelity card class that records the number of points that a clietn will get for each payment
//clasa Card Fidelitate ce inregistreaza numarul de puncte castigate de client de fiecare data cand efectueaza o plata
class FidelityCard {
public:
	const int id;			//constant attribute - generated based on noCards value
private:
	char owner[50];
	string cardType;		//the service that provides the card (ex. Rompetrol, Mega Image, etc)

	int* points;			//points accumulated each time the client buys something
	int noPayments;			//number of pamyments done by the client

	static int noCards;		//incremented for each created card

	friend ostream& operator<<(ostream& iesire, FidelityCard& Card);
	friend istream& operator>>(istream& intrare, FidelityCard& Card);

public:
	const static int MIN_POINTS_FOR_PREMIUM = 1000;		//init with 1000 - the minimum points for becoming a premium member

		//constructors
		//constructori

	FidelityCard() :id(noCards++)	//sets name to John Doe and cardType to "None" | initializeaza numele cu John Doe si tipul cardului cu "None"
	{
		strcpy(this->owner, "John Doe");
		this->cardType = "None";
		this->noPayments = 0;
		this->points = NULL;
	}

	FidelityCard(const char* name, string cardName) :id(noCards++)
	{
		strcpy(this->owner, name);
		this->cardType = cardName;
		this->noPayments = 0;
		this->points = NULL;
	}

	FidelityCard(const char* name, string cardName, int* existingPoints, int noPoints) :id(noCards++)
	{
		strcpy(this->owner, name);
		cardType = cardName;
		points = new int[noPoints];
		for (int i = 0; i < noPoints; i++) {
			this->points[i] = existingPoints[i];
		}
		this->noPayments = noPoints;
	}

	//copy constructor
	FidelityCard(FidelityCard& fidelityCard) :id(fidelityCard.id) {
		strcpy(this->owner, fidelityCard.owner);
		cardType = fidelityCard.cardType;
		this->noPayments = fidelityCard.noPayments;
		points = new int[fidelityCard.noPayments];
		if (fidelityCard.points)
			for (int i = 0; i < this->noPayments; i++) {
				this->points[i] = fidelityCard.points[i];
			}
		else
			this->points = NULL;

	}

	//destructor

	~FidelityCard() {
		if (points != NULL)
			delete[] points;
	}

	void afisare() {

		cout << endl << "-----------------------";
		cout << endl << this->id << " - " << this->owner;
		cout << endl << "Card type: " << this->cardType;
		cout << endl << "noPoints: " << this->noPayments;

		if (this->points != NULL) {
			cout << endl << "Points: ";
			for (int i = 0; i < this->noPayments; i++) {
				cout << this->points[i] << " | ";
			}
		}
		else
			cout << endl << "Nu exista puncte";
	}

	//computes total points
	//determina numarul total de puncte

	int getTotalPoints() {
		int sum;
		sum = 0;
		if (this->noPayments != 0) {
			for (int i = 0; i < this->noPayments; i++)
				sum += this->points[i];
		}
		return sum;
	}

	//returns the owner name
	//returneaza numele de pe card

	char* getName() {
		return this->owner;
	}

	//returns number of payments/points
	//returneaza numarul de puncte

	int getNoPayments() {
		return this->noPayments;
	}

	//returns a specific payment
	//if the index is wrong the function shoud throw a new Assignment3Exception with "throw new Assignment3Exception();"
	
	//returneaza punctele asociate cu o anumita plata
	//daca indexul primit este gresit (nu se afla intre limitele 0 si numarPuncte -1 ) atunci se arunca o exceptie de tip Assignment3Exception cu "throw new Assignment3Exception();"

	int getPayment(int index) {
		if (index > this->noPayments || index < 0)
			throw new Assignment3Exception();
		else
			return this->points[index];
	}

	//returns the card name
	//returneaza tipul cardului

	string getCardType() {
		return this->cardType;
	}

	//checks is the client is a premium one - if it has more than MIN_POINTS_FOR_PREMIUM
	//verifica daca clientul este unul premium - suma punctelor depaseste MIN_POINTS_FOR_PREMIUM

	bool isPremiumClient() {
		if (this->getTotalPoints() >= MIN_POINTS_FOR_PREMIUM)
			return true;
		else
			return false;
	}

	//allow you to change a specific entry in the points array
	//if the index is wrong or the value is a negative one the function shoud throw a new Assignment3Exception with "throw new Assignment3Exception();"

	//permite modificarea numarului de puncte de la o pozitie data
	//daca indexul primit este gresit (nu se afla intre limitele 0 si numarPuncte -1 ) si valoarea este negativa atunci se arunca o exceptie de tip Assignment3Exception cu "throw new Assignment3Exception();"

	void changePoints(int index, int value) {
		if (value<0 || index>this->noPayments || index < 0)
			throw new Assignment3Exception();
		else
			this->points[index] = value;
	}

	//allow you to change the owner name
	//if newOwnerName has less than 3 chars and more than 49 the function shoud throw a new Assignment3Exception

	//permite modificarea numelui proprietarului
	//daca newOwnerName are mai putin de 3 caractere si mai mult de 49 se arunca o exceptie de tip Assignment3Exception cu "throw new Assignment3Exception();"
	
	void changeOwner(const char* newOwnerName) {
		if (strlen(newOwnerName) <= 3 || strlen(newOwnerName) > 48)
			throw new Assignment3Exception();
		else
			strcpy(this->owner, newOwnerName);
	}

	//adds (concatenates) the newPoints array to the existing one; if the existing one is NULL then it's created and takes the values
	// if newPoints is NULL then throw a new Assignment3Exception

	//adauga (concateneaza) vectorul newPoints la cel existent; daca cel existent este NULL, atunci este creat si ia valorile
	//daca newPoints este NULL atunci arunca o exceptie Assignment3Exception
	//without | fara MEMORY LEAKS

	void transferPoints(int* newPoints, int noPoints) {
		if (newPoints != NULL)
			if (this->points == NULL) {
				this->points = new int[noPoints];
				this->noPayments = noPoints;
				for (int i = 0; i < noPoints; i++)
					this->points[i] = newPoints[i];
			}
			else {
				int* array = new int[this->noPayments + noPoints];
				for (int i = 0; i < this->noPayments; i++)
				{
					array[i] = this->points[i];
				}
				for (int i = 0; i < noPoints; i++)
				{
					array[i + noPayments] = newPoints[i];
				}
				delete[] this->points;
				this->points = array;
				this->noPayments = this->noPayments + noPoints;
			}

		else {
			throw new Assignment3Exception();
		}
	}

	//the function allows clients to use the points to buy bew services/products
	//the function will remove the first n values from the points array wich sum are >= amount
	//if amount is <= 0 or > than the points sum then throw a new Assignment3Exception

	// functia permite clientilor sa utilizeze punctele pentru a cumpara servicii / produse noi 
	// functia va elimina primele n valori din vectorul de puncte, a caror suma este >= cu amount
	// daca amount este <= 0 sau > suma tuturor punctelor se arunca o exceptie Assignment3Exception
	
	void usePoints(int amount) {
		if (amount <= 0 || amount > this->getTotalPoints())
			throw new Assignment3Exception();
		else
		{
			int numarare = 0;
			int contor = 0;
			int j = 0;
			while (numarare < amount) {
				numarare += this->points[contor];
				contor++;
			}
			int*nou;
			nou = new int[this->noPayments - contor];
			for (int i = contor; i < this->noPayments; i++) {
				nou[j] = this->points[i];
				j++;
			}
			delete[] this->points;
			this->points = nou;
			this->noPayments = (this->noPayments - contor);
		}
	}

	//functie pt operatori

	void removePoints() {
		if (this->points != NULL) {
			if (this->noPayments == 1) {
				delete[] this->points;
				this->points = NULL;
			}
			else
			{
				this->noPayments--;
				int* vectorNou;
				vectorNou = new int[this->noPayments];
				for (int i = 0; i < this->noPayments; i++) {
					vectorNou[i] = this->points[i];
				}
				delete[] this->points;
				this->points = vectorNou;
			}
		}
	}

	//operators
	//operatori

	FidelityCard operator=(const FidelityCard& card) {
		strcpy(this->owner, card.owner);
		cardType = card.cardType;
		this->noPayments = card.noPayments;
		points = new int[card.noPayments];
		if (card.points != NULL) {
			for (int i = 0; i < this->noPayments; i++)
				this->points[i] = card.points[i];
		}
		else
			this->points = NULL;
		return *this;
	}


	FidelityCard operator+(int x) {
		FidelityCard cardNou;
		cardNou = *this;
		cardNou.transferPoints(&x, 1);
		return cardNou;
	}

	FidelityCard operator+=(int x) {
		this->transferPoints(&x, 1);
		return *this;
	}

	FidelityCard operator-(int x) {
		FidelityCard cardNou;
		cardNou = *this;
		cardNou.usePoints(x);
		return cardNou;
	}

	FidelityCard operator-=(int x) {
		this->usePoints(x);
		return *this;
	}

	FidelityCard operator*(int x) {
		FidelityCard cardNou;
		cardNou = *this;
		if (cardNou.points != NULL) {
			for (int i = 0; i < cardNou.noPayments; i++)
				cardNou.points[i] *= 2;
		}
		return cardNou;
	}

	FidelityCard operator++(int) {
		FidelityCard cardNou;
		cardNou = *this;
		int valoare = 10;
		this->transferPoints(&valoare, 1);
		return cardNou;
	}

	FidelityCard operator++() {
		int valoare = 10;
		this->transferPoints(&valoare, 1);
		return *this;
	}

	FidelityCard operator--(int) {
		FidelityCard cardNou;
		cardNou = *this;
		this->removePoints();
		return cardNou;
	}

	FidelityCard operator--() {
		this->removePoints();
		return *this;
	}

	bool operator>(FidelityCard& card) {
		if (this->getTotalPoints() > card.getTotalPoints())
			return true;
		else
			return false;
	}

	bool operator<(FidelityCard& card) {
		if (this->getTotalPoints()<card.getTotalPoints())
			return true;
		else
			return false;
	}

	bool operator==(FidelityCard& card) {
		if (this->getTotalPoints() == card.getTotalPoints())
			return true;
		else
			return false;
	}

	bool operator>=(FidelityCard& card) {
		if (this->getTotalPoints() >= card.getTotalPoints())
			return true;
		else
			return false;
	}

	operator int() {
		return this->getTotalPoints();
	}

	int& operator [](int x) {
		if (this->points != NULL && x < noPayments && x>0)
			return this->points[x];
	}

	int operator()(int start, int finish) {
		if (start > 0 && finish <= this->noPayments && start <= finish) {
			int sum = 0;
			if (this->points != NULL) {
				for (int i = start; i <= finish; i++)
					sum += this->points[i];
			}
			return sum;
		}
		else {
			throw "Parametrii nevalizi";
		}
	}

	FidelityCard operator!=(FidelityCard card) {
		strcpy(this->owner, card.owner);
		cardType = card.cardType;
		this->noPayments = card.noPayments;
		return *this;
	}

	//TO DO
	//implement the required operators as class member functions or global functions so the examples from main will work
	//implementeaza operatorii indicati in main ca functii membre in clasa sau functii globale, astfel încat exemplele din main vor rula
};

FidelityCard operator+(int x, const FidelityCard& card) {
	FidelityCard card_nou;
	card_nou = card;
	int val = x;
	card_nou.transferPoints(&val, 1);
	return card_nou;
}

ostream& operator<<(ostream& iesire, FidelityCard& card) {
	iesire << endl << "-------------------------------";
	iesire << endl << card.id << " - " << card.owner;
	iesire << endl << "Card type: " << card.cardType;
	iesire << endl << "noPoints: " << card.noPayments;
	if (card.points != NULL) {
		iesire << endl << "Points: ";
		for (int i = 0; i < card.noPayments; i++) {
			iesire << card.points[i] << " | ";
		}
	}
	else
		iesire << endl << "Nu exista puncte";
	return iesire;
}

istream& operator>>(istream& intrare,FidelityCard& card){
	cout << endl << "Introduceti nume client: ";
	char nume[100];
	intrare >> nume;
	card.changeOwner(nume);
	
	cout << endl << "Introduceti tipul cardului: ";
	intrare >> card.cardType;

	cout << endl << "Introduceti numarul de plati: ";
	intrare >> card.noPayments;

	cout << endl << "Introduceti punctele";
	int*v;
	v = new int[card.noPayments];
	for (int i = 0; i < card.noPayments; i++)
	{
		cout << "puncte pentru plata numarul " << i << " este ";
		intrare >> v[i];
	}

	card.points=v;

	return intrare;
}

int FidelityCard::noCards = 0;

void main() {

	//test class functions
	int nrPuncte = 4;
	int puncte[] = { 10,20,5,10 };
	FidelityCard cardA;
	FidelityCard cardB("Owner2", "Sensiblu");
	FidelityCard cardC("Owner3", "Sensiblu", puncte, nrPuncte);
	cardA.afisare();
	cardB.afisare();
	cardC.afisare();

	cout << endl;
	cout << endl << "Card type: " << cardC.getCardType();
	cout << endl << "Name: " << cardC.getName();
	cout << endl << "Number of paiments: " << cardC.getNoPayments();
	cout << endl << "Number of points of 1 payment:" << cardC.getPayment(1);
	cout << endl << "Total points: " << cardC.getTotalPoints();

	if (cardC.isPremiumClient())
		cout << endl << "is a premium client";
	else
		cout << endl << "is not a premium client";

	cardC.changeOwner("Gigel");
	cardC.afisare();

	cardC.changePoints(1, 100);
	cardC.afisare();

	int nr = 3;
	int vector[] = { 100,32,6 };
	cardC.transferPoints(vector, nr);
	cardC.afisare();
	cardB.transferPoints(vector, nr);
	cardB.afisare();

	cardC.usePoints(100);
	cardC.afisare();

	//test destructor

	//operators section

	FidelityCard card1("No Name", "Blank");
	FidelityCard card2 = card1;
	cout << card1;
	 cout << card2;
	 cin >> card1;
	 cout << card1;

	int somePoints[] = { 15,5,10,30 };
	int noPoints = 4;
	FidelityCard card3("John", "ACME Inc", somePoints, noPoints);
	FidelityCard card4 = card3;

	//operator =
	//without MEMORY LEAKS
	card2 = card1;			//copy data to card 1 from card 2 | copiaza datele cardului 1 in cardul 2
	 cout << card2;
	 cout << card1;

	card1 = card3 + 15; //adds new points | adauga puncte noi
	cout << card3;

	cout << card1;
	card1 = 20 + card1; //adds new points | adauga puncte noi
	cout << card1;
	card1 += 10;		//adds new points | adauga puncte noi
	cout << card1;

	FidelityCard card5("No Name", "Blank");
	card5 = card1 - 20;		//spends 20 points | utilizeaza 20 de puncte de pe card
	card5 -= 10;			//spends 10 more points | utilizeaza inca 10 de puncte de pe card
	cout << card5;

	card5 = card5 * 2;			//doubles all existing points | dubleaza toate punctele existente
	cout << card5;

	FidelityCard card6("No Name", "Blank");

	//postincrement
	cout << card6;
	cout << card3;
	card6 = card3++;		// adds 10 more points | adauga inca 10 puncte
	cout << card6;
	cout << card3;


	//preincrement
	card6 = ++card3;		// adds 10 more points | adauga inca 10 puncte
	cout << card6;
	cout << card3;

	//postdecrement
	card6 = card3--;		// removes the last entr in the points array
	cout << card6;
	cout << card3;


	//predecrement
	card6 = --card3;		// removes the last entry in the points array
	cout << card6;
	cout << card3;

	cout << card6;
	cout << card2;

	if (card6 > card2) {
		cout << endl << card6.getName() << " has more points than " << card2.getName();
	}

	if (card6 < card2) {
		cout << endl << card6.getName() << " has less points than " << card2.getName();
	}

	if (card6 == card2) {
		cout << endl << card6.getName() << " has the same amount of points as " << card2.getName();
	}

	if (card6 >= card2) {
		cout << endl << card6.getName() << " has more or equal points than " << card2.getName();
	}


	//explicit cast
	cout << card3;
	int totalPoints = (int)card3;		//get total points on the card | determina numarul total de puncte


	int somePoints2 = card3[1];			//returns the number of points from the array on index 1 | intorce numarul de puncte de pe pozitia 1 din vectorul de puncte
	card3[0] = 25;						//allows you to change the points value at index 0 in the array | iti permite sa modifici numarul de puncte de la index 0 in vectorul de puncte					

	int partialSum = card3(1, 3);			//determines the sum of points from index 1 to 3 (including 3) | determina numarul de puncte de la indexul 1 pana la 3 (inclusiv)

	card6 != card3;						//returns a copy of card with 0 points | returneaza o copie a cardului 3 fara a pastra punctele
	cout << card6 << card3;
}