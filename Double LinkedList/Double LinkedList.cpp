#include <iostream>
#include <fstream>
#include <stack>

struct List {

	struct Node {

		Node* next;
		Node* prev;
		int key;

	};

	Node* first = nullptr;
	Node* last = nullptr;


	void push_back(int key) {

		Node* newNode = new Node;
		newNode->key = key;
		newNode->next = nullptr;

		if (first == NULL) {
			newNode->prev = nullptr;
			first = newNode;
			last = newNode;
		}
		else {

			last->next = newNode;
			newNode->prev = last;
			last = newNode;

		}


	}

	void push_front(int key) {

		Node* newNode = new Node;

		newNode->key = key;

		newNode->next = nullptr;
		newNode->prev = nullptr;

		if (first == nullptr) {
			first = newNode;
			last = newNode;
		}
		else {
			newNode->next = first;
			first->prev = newNode;
			first = newNode;

		}
	}
	void pop_front() {

		Node* p = first;

		if (first != nullptr) {
			first = first->next;
			first->prev = nullptr;
			delete p;
		}

	}

	void pop_back() {

		Node* p = last;

		if (last != nullptr) {
			last = last->prev;
			last->next = nullptr;
			delete p;
		}

	}

	Node* find(int key) {

		Node* p = first;

		while (p != NULL) {

			if (p->key == key)
				return p;

			p = p->next;
		}
		return NULL;
	}

	void erase(Node* nod) {


		if (first == nullptr || nod == nullptr)
			return;
		if (first == nod)
			first = nod->next;
		if (nod->next != nullptr)
			nod->next->prev = nod->prev;
		if (nod->prev != nullptr)
			nod->prev->next = nod->next;
		if (last == nod)
			last = nod->prev;

		delete nod;
	}

	void remove(int key) {

		Node* p = first;
		Node* tmp = first;

		while (p != nullptr) {

			if (p->key == key) {
				tmp = tmp->next;
				erase(p);
				p = tmp;

			}
			else {
				tmp = tmp->next;
				p = p->next;
			}
		}

	}

	void insert(Node* nod, int val) {

		if (first == nod) {
			push_front(val);
			return;
		}

		Node* p = new Node;
		p->key = val;

		/*
		nod->prev->next = p;
		nod->prev = p;
		p->next = nod;*/
		p->prev = nod->prev;
		nod->prev->next = p;
		nod->prev = p;
		p->next = nod;

	}

	void empty() {

		if (first == NULL)
			std::cout << "\nLista e vida!\n";
		else
			std::cout << "\nLista nu e vida\n";

	}

	void clear() {

		Node* p = first;
		Node* tmp = first;
		while (p != NULL) {
			tmp = tmp->next;
			erase(p);
			p = tmp;
		}

	}

	void print() {

		Node* p = first;

		while (p != NULL) {
			std::cout << p->key << " ";
			p = p->next;
		}
		std::cout << std::endl;
	}

	int size() {

		Node* p = first;
		int size = 0;
		while (p != NULL) {
			size++;
			p = p->next;
		}
		return size;
	}
};


void meniu(int numarLista, List lista1, List lista2);

bool estePalindrom(List lista) {

	auto nod = lista.first;
	auto nod2 = lista.first;

	std::stack<int> st;

	while (nod != nullptr) {
		st.push(nod->key);
		nod = nod->next;
	}
	while (nod2 != nullptr) {
		int element = st.top();
		st.pop();
		if (nod2->key != element)
			return false;

		nod2 = nod2->next;

	}
	return true;
}

bool compare(List lista1, List lista2) {

	if (lista1.size() != lista2.size())
		return false;

	auto nod1 = lista1.first;
	auto nod2 = lista2.first;

	while (nod1 != nullptr || nod2 != nullptr) {

		if (nod1 == nullptr && nod2 != nullptr)
			return false;
		if (nod2 == nullptr && nod1 != nullptr)
			return false;

		if (nod1->key != nod2->key)
			return false;

		nod1 = nod1->next;
		nod2 = nod2->next;
	}

	return true;
}



int main() {

	List* liste = new List[2];
	List lista1;
	List lista2;

	liste[0] = lista1;
	liste[1] = lista2;


	bool online = true;
	auto nod = lista1.first;
	int numarLista = 0, optiune, valoare;
	meniu(numarLista, liste[0], liste[1]);

	while (online) {

		std::cin >> optiune;

		switch (optiune) {

		case -1:
			meniu(numarLista, liste[0], liste[1]);
			break;
		case 0:
			online = false;
			break;
		case 1:
			std::cout << "Ati selectat: PUSH_FRONT\nValoare: "; std::cin >> valoare;
			liste[numarLista].push_front(valoare);
			meniu(numarLista, liste[0], liste[1]);
			break;
		case 2:
			std::cout << "Ati selectat: PUSH_BACK\nValoare: "; std::cin >> valoare;
			liste[numarLista].push_back(valoare);
			meniu(numarLista, liste[0], liste[1]);
			break;
		case 3:
			liste[numarLista].pop_front();
			meniu(numarLista, liste[0], liste[1]);
			break;
		case 4:
			liste[numarLista].pop_back();
			meniu(numarLista, liste[0], liste[1]);
			break;
		case 5:
			std::cout << "Ati selectat: FIND\nValoare: "; std::cin >> valoare;
			nod = liste[numarLista].find(valoare);

			if (nod != NULL)
				std::cout << "Elementul a fost gasit! Acesta va fi folosit la optiunile erase si insert!\n\nIntroduceti optiunea -1 pentru a reveni la meniu: ";
			else
				std::cout << "Elementul NU a fost gasit!\n\nIntroduceti optiunea -1 pentru a reveni la meniu: ";
			break;
		case 6:
			// Se foloseste la remove.. (erase)
			if (nod == NULL)
				break;
			liste[numarLista].erase(nod);
			meniu(numarLista, liste[0], liste[1]);
			break;
		case 7:
			std::cout << "Ati selectat: REMOVE\nValoare: "; std::cin >> valoare;
			liste[numarLista].remove(valoare);
			meniu(numarLista, liste[0], liste[1]);
			break;
		case 8:
			if (nod == NULL)
				break;
			std::cout << "Ati selectat: INSERT\nValoare: "; std::cin >> valoare;
			liste[numarLista].insert(nod, valoare);
			meniu(numarLista, liste[0], liste[1]);
			break;
		case 9:
			liste[numarLista].empty();
			std::cout << "\nIntroduceti optiunea -1 pentru a reveni la meniu: ";
			break;
		case 10:
			liste[numarLista].clear();
			std::cout << "Lista a fost golita!\n\nIntroduceti optiunea -1 pentru a reveni la meniu: ";
			break;
		case 11:
			liste[numarLista].print();
			break;
		case 12:
			std::cout << "Size-ul listei este " << liste[numarLista].size() << "\nIntroduceti optiunea -1 pentru a reveni la meniu: ";
			break;
		case 13:
			if (estePalindrom(liste[numarLista]))
				std::cout << "\nLista este palindrom!\n";
			else
				std::cout << "\nLista NU este palindrom!\n";
			std::cout << "\nIntroduceti optiunea -1 pentru a reveni la meniu: ";
			break;
		case 14:
			if (compare(liste[0], liste[1]))
				std::cout << "\nListele sunt identice!\n";
			else
				std::cout << "\nListele NU sunt identice!\n";
			std::cout << "\nIntroduceti optiunea -1 pentru a reveni la meniu: ";
			break;
		case 15:
			if (numarLista == 0)
				numarLista = 1;
			else
				numarLista = 0;
			meniu(numarLista, liste[0], liste[1]);
			break;
		default:
			std::cout << "\nAceasta optiune nu exista!\nIntroduceti optiunea -1 pentru ajutor!\n";
			break;
		}

	}

	return 0;
}

void meniu(int numarLista, List lista1, List lista2) {

	std::cout << "################################# Double LinkedList ################################\n\n";

	std::cout << "Lista selectata: " << numarLista + 1 << "\n\n";

	std::cout << "Lista 1: ";
	lista1.print();
	std::cout << "Lista 2: ";
	lista2.print();

	std::cout << "\n0 - EXIT\n1 - push_front\n2 - push_back\n3 - pop_front\n4 - pop_back\n5 - find\n6 - erase (Node-ul trebuie selectat folosing optiunea FIND)\n7 " <<
		"- remove\n8 - insert (Node-ul trebuie selectat folosing optiunea FIND)\n9 - empty\n10 - clear\n11 - print\n12 - size\n13 - palindrom\n14 - compare\n15 - schimbare lista";

	std::cout << "\n\n################################# Double LinkedList #################################\n\n";
	std::cout << "Optiune: ";

}