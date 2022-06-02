#include "../container/container.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../zlasdtest/test.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../bst/bst.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"
#include <type_traits>
#include <iostream>
#include <random>
#include <cmath>
#include <sstream>

using namespace std;
using namespace lasd;


default_random_engine gen(random_device{}());


string GeneraStringaCasuale(const unsigned int lunghezza)
{
	const string validChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	uniform_int_distribution<int> dist(0, validChars.size() - 1);
	ostringstream oss;
	for (unsigned int i = 0; i < lunghezza; i++)
	{
		oss << validChars[dist(gen)];
	}
	return oss.str();
}

template<typename Data>
void FoldSumLessThanN(const Data& dat, const void *_, void *acc)
{
	if (dat < *((Data *)_))
		*((Data *)acc) += dat;
}

template<typename Data>
void FoldSumMoreThanN(const Data& dat, const void *_, void *acc)
{
	if (dat > *((Data *)_))
		*((Data *)acc) += dat;
}

template<typename Data>
void FoldProductLessThanN(const Data& dat, const void *_, void *acc)
{
	if (dat < *((Data *)_))
		*((Data *)acc) *= dat;
}

template<typename Data>
void FoldProductMoreThanN(const Data& dat, const void *_, void *acc)
{
	if (dat > *((Data *)_))
		*((Data *)acc) *= dat;
}

template<typename Data>
void FoldConcatLessEqualN(const Data& dat, const void *_, void *acc)
{
	if (dat.length() <= *((unsigned long *)_))
		*((Data *)acc) += dat;
}

template<typename Data>
void MapPrint(Data& dat, void *_)
{
	cout << dat << " ";
}

template<typename Data>
void MapMultiply(Data& dat, void *_)
{
	dat = dat * *(short *)(_);
}

template<typename Data>
void MapPower(Data& dat, void *_)
{
	dat = pow(dat, *(short *)_);
}

template<typename Data>
void MapUppercase(Data& dat, void *_)
{
	for (char& c: dat)
		c = toupper(c);
}

template<typename Data>
void MapAppend(Data& dat, void *_)
{
	dat.append(*((string *)_));
}

template<typename Data>
void vectortest(Vector<Data>& v)
{
	cout << "Il primo elemento e' " << v[0] << ", l'ultimo e' " << v[v.Size() - 1] << endl;
	bool selection = false;
	while (!selection)
	{
		cout << "0. Torna indietro" << endl << "1. Stampa tutti gli elementi" << endl << "2. Controlla esistenza di un elemento" << endl << "3. Calcola la funzione fold relativa al dato" << endl << "4. Applica funzione map a tutti gli elementi" << endl;
		string input;
		cin >> input;
		int testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
				v.Map(&MapPrint<Data>, 0);
				cout << endl;
				break;
			case 2:
			{
				cout << endl << "Inserisci dato da cercare:   ";
				Data search;
				cin >> search;
				if (v.Exists(search))
					cout << "Trovato!" << endl;
				else
					cout << "Non trovato!" << endl;
				break;
			}
			case 3:
			{
				if constexpr (is_same<Data, int>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Somma per gli interi minori di n" << endl << "Inserisci n:   ";
					long n{};
					cin >> n;
					long result = 0;
					v.Fold(&FoldSumLessThanN<int>, &n, &result);
					cout << result << endl;
				}
				if constexpr (is_same<Data, double>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Prodotto per i double maggiori di n;" << endl << "Inserisci n:   ";
					cout << endl << "Inserisci n:   ";
					double n;
					cin >> n;
					double result = 1;
					v.Fold(&FoldProductMoreThanN<double>, &n, &result);
					cout << result << endl;
				}
				if constexpr (is_same<Data, string>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Concatenazione con lunghezza minore o uguale a n;" << endl << "Inserisci n:   ";
					unsigned long n{};
					cin >> n;
					string result = "";
					v.Fold(&FoldConcatLessEqualN<Data>, &n, &result);
					cout << result << endl;
				}
				break;
			}
			case 4:
				if constexpr (is_same<Data, int>::value)
				{
					cout << "Funzione map per questo tipo di dato: 2n" << endl;
					short a = 2;
					v.Map(&MapMultiply<int>, &a);
					cout << "Fatto, prova a stampare" << endl;
				}
				if constexpr (is_same<Data, double>::value)
				{
					cout << "Funzione map per questo tipo di dato: n^2;" << endl;
					short a = 2;
					v.Map(&MapPower<double>, &a);
					cout << "Fatto, prova a stampare" << endl;
				}
				if constexpr (is_same<Data, string>::value)
				{
					cout << "Funzione map per questo tipo di dato: uppercase;" << endl;
					v.Map(&MapUppercase<Data>, 0);
					cout << "Fatto, prova a stampare" << endl;
				}
				break;
			default:
				cout << "Errore di input" << endl;
		}
	}
}

template<typename Data>
void listtest(List<Data>& l)
{
	cout << "Il primo elemento e' " << l.Front() << ", l'ultimo e' " << l.Back() << endl;
	bool selection = false;
	while (!selection)
	{
		cout << "0. Torna indietro" << endl << "1. Stampa tutti gli elementi" << endl << "2. Controlla esistenza di un elemento" << endl << "3. Calcola la funzione fold relativa al dato" << endl << "4. Applica funzione map a tutti gli elementi" << endl;
		string input;
		cin >> input;
		int testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
				l.Map(&MapPrint<Data>, 0);
				cout << endl;
				break;
			case 2:
			{
				cout << endl << "Inserisci dato da cercare:   ";
				Data search;
				cin >> search;
				if (l.Exists(search))
					cout << "Trovato!" << endl;
				else
					cout << "Non trovato!" << endl;
				break;
			}
			case 3:
			{
				if constexpr (is_same<Data, int>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Somma per gli interi minori di n" << endl << "Inserisci n:   ";
					long n{};
					cin >> n;
					long result = 0;
					l.Fold(&FoldSumLessThanN<int>, &n, &result);
					cout << result << endl;
				}
				if constexpr (is_same<Data, double>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Prodotto per i double maggiori di n;" << endl << "Inserisci n:   ";
					cout << endl << "Inserisci n:   ";
					double n;
					cin >> n;
					double result = 1;
					l.Fold(&FoldProductMoreThanN<double>, &n, &result);
					cout << result << endl;
				}
				if constexpr (is_same<Data, string>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Concatenazione con lunghezza minore o uguale a n;" << endl << "Inserisci n:   ";
					unsigned long n{};
					cin >> n;
					string result = "";
					l.Fold(&FoldConcatLessEqualN<Data>, &n, &result);
					cout << result << endl;
				}
				break;
			}
			case 4:
				if constexpr (is_same<Data, int>::value)
				{
					cout << "Funzione map per questo tipo di dato: 2n" << endl;
					short a = 2;
					l.Map(&MapMultiply<int>, &a);
					cout << "Fatto, prova a stampare" << endl;
				}
				if constexpr (is_same<Data, double>::value)
				{
					cout << "Funzione map per questo tipo di dato: n^2;" << endl;
					short a = 2;
					l.Map(&MapPower<double>, &a);
					cout << "Fatto, prova a stampare" << endl;
				}
				if constexpr (is_same<Data, string>::value)
				{
					cout << "Funzione map per questo tipo di dato: uppercase;" << endl;
					l.Map(&MapUppercase<Data>, 0);
					cout << "Fatto, prova a stampare" << endl;
				}
				break;
			default:
				cout << "Errore di input" << endl;
		}
	}
}

template<typename Data>
void stacktest(Stack<Data>& s)
{
	cout << "L'elemento in cima e' " << s.Top() << endl;
	bool selection = false;
	int testtype;
	while (!selection)
	{
		cout << "0. Torna indietro" << endl << "1. Inserisci un elemento" << endl << "2. Rimuovi un elemento" << endl << "3. Visualizza e rimuovi un elemento" << endl << "4. Visualizza un elemento" << endl << "5. E' vuoto?" << endl << "6. Stampa grandezza" << endl << "7. Svuota la struttura"
			 << endl;
		string input;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
			{
				cout << "Inserisci elemento in pila:  " << endl;
				Data d;
				cin >> d;
				s.Push(d);
				break;
			}
			case 2:
			{
				s.Pop();
				cout << "Rimosso!" << endl;
				break;
			}
			case 3:
			{
				cout << "Ho rimosso " << s.TopNPop() << endl;
				break;
			}
			case 4:
			{
				cout << "L'elemento in cima e' " << s.Top() << endl;
				break;
			}
			case 5:
			{
				if (s.Empty())
					cout << "La pila e' vuota" << endl;
				else
					cout << "La pila non e' vuota" << endl;
				break;
			}
			case 6:
			{
				cout << "La pila ha " << s.Size() << " elementi" << endl;
				break;
			}
			case 7:
			{
				s.Clear();
				cout << "Svuotata!" << endl;
				break;
			}
			default:
				cout << "Errore di input" << endl;
		}
	}
}

template<typename Data>
void queuetest(Queue<Data>& q)
{
	cout << "L'elemento in cima e' " << q.Head() << endl;
	bool selection = false;
	int testtype;
	while (!selection)
	{
		cout << "0. Torna indietro" << endl << "1. Inserisci un elemento" << endl << "2. Rimuovi un elemento" << endl << "3. Visualizza e rimuovi un elemento" << endl << "4. Visualizza un elemento" << endl << "5. E' vuoto?" << endl << "6. Stampa grandezza" << endl << "7. Svuota la struttura"
			 << endl;
		string input;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
			{
				cout << "Inserisci elemento in coda:  " << endl;
				Data d;
				cin >> d;
				q.Enqueue(d);
				break;
			}
			case 2:
			{
				q.Dequeue();
				cout << "Rimosso!" << endl;
				break;
			}
			case 3:
			{
				cout << "Ho rimosso " << q.HeadNDequeue() << endl;
				break;
			}
			case 4:
			{
				cout << "L'elemento in cima e' " << q.Head() << endl;
				break;
			}
			case 5:
			{
				if (q.Empty())
					cout << "La coda e' vuota" << endl;
				else
					cout << "La coda non e' vuota" << endl;
				break;
			}
			case 6:
			{
				cout << "La coda ha " << q.Size() << " elementi" << endl;
				break;
			}
			case 7:
			{
				q.Clear();
				cout << "Svuotata!" << endl;
				break;
			}
			default:
				cout << "Errore di input" << endl;
		}
	}
}

template<typename Data>
void binarytreetest(BinaryTree<Data>& bt)
{
	bool selection = false;
	int testtype;
	cout << endl << "Seleziona il tipo di operazione" << endl;
	while (!selection)
	{
		cout << "0. Torna indietro" << endl << "1. Visualizza in ampiezza" << endl << "2. Visualizza in pre-ordine" << endl << "3. Visualizza in ordine" << endl << "4. Visualizza in post-ordine" << endl << "5. Controlla esistenza di un valore" << endl
			 << "6. Calcola la funzione fold relativa al dato" << endl << "7. Applica funzione map a tutti gli elementi" << endl;
		string input;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
			{
				bt.MapBreadth(&MapPrint<Data>, 0);
				cout << endl;
				break;
			}
			case 2:
			{
				bt.MapPreOrder(&MapPrint<Data>, 0);
				cout << endl;
				break;
			}
			case 3:
			{
				bt.MapInOrder(&MapPrint<Data>, 0);
				cout << endl;
				break;
			}
			case 4:
			{
				bt.MapPostOrder(&MapPrint<Data>, 0);
				cout << endl;
				break;
			}
			case 5:
			{
				Data search{};
				cout << "Inserisci l'elemento da cercare: ";
				cin >> search;
				if (!bt.Exists(search))
					cout << "Non trovato!" << endl;
				else
					cout << "Trovato!" << endl;
				break;
			}
			case 6:
			{
				if constexpr (is_same<Data, int>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Prodotto per gli interi minori di n" << endl << "Inserisci n:   ";
					int n{};
					cin >> n;
					long result = 1;
					bt.Fold(&FoldProductLessThanN<Data>, &n, &result);
					cout << result << endl;
				}
				if constexpr (is_same<Data, double>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Somma per i double maggiori di n;" << endl << "Inserisci n:   ";
					double n{};
					cin >> n;
					double result = 0;
					bt.Fold(&FoldSumMoreThanN<Data>, &n, &result);
					cout << result << endl;
				}
				if constexpr (is_same<Data, string>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Concatenazione con lunghezza minore o uguale a n;" << endl << "Inserisci n:   ";
					unsigned long n{};
					cin >> n;
					string result = "";
					bt.Fold(&FoldConcatLessEqualN<Data>, &n, &result);
					cout << result << endl;
				}
				break;
			}
			case 7:
			{
				if constexpr (is_same<Data, int>::value)
				{
					cout << "Funzione map per questo tipo di dato: 3n" << endl;
					short a = 3;
					bt.Map(&MapMultiply<Data>, &a);
					cout << "Fatto, prova a stampare" << endl;
				}
				if constexpr (is_same<Data, double>::value)
				{
					cout << "Funzione map per questo tipo di dato: n^3;" << endl;
					short a = 2;
					bt.Map(&MapPower<Data>, &a);
					cout << "Fatto, prova a stampare" << endl;
				}
				if constexpr (is_same<Data, string>::value)
				{
					cout << "Funzione map per questo tipo di dato: n + str;" << endl << "Inserisci str:   ";
					string n = "";
					cin >> n;
					bt.Map(&MapAppend<Data>, &n);
					cout << "Fatto, prova a stampare" << endl;
				}
				break;
			}
			default:
				cout << "Errore di input" << endl;
		}
	}
}

template<typename Data>
void bsttest(BST<Data>& bst)
{
	bool selection = false;
	int testtype;
	cout << endl << "Seleziona il tipo di operazione" << endl;
	while (!selection)
	{
		cout << "0. Torna indietro" << endl << "1. Visualizza in ampiezza" << endl << "2. Visualizza in pre-ordine" << endl << "3. Visualizza in ordine" << endl << "4. Visualizza in post-ordine" << endl << "5. Controlla esistenza di un valore" << endl
			 << "6. Calcola la funzione fold relativa al dato" << endl << "7. Rimuovi un valore" << endl << "8. Stampa la size" << endl;
		string input;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
			{
				bst.MapBreadth(&MapPrint<Data>, 0);
				cout << endl;
				break;
			}
			case 2:
			{
				bst.MapPreOrder(&MapPrint<Data>, 0);
				cout << endl;
				break;
			}
			case 3:
			{
				bst.MapInOrder(&MapPrint<Data>, 0);
				cout << endl;
				break;
			}
			case 4:
			{
				bst.MapPostOrder(&MapPrint<Data>, 0);
				cout << endl;
				break;
			}
			case 5:
			{
				Data search{};
				cout << "Inserisci l'elemento da cercare: ";
				cin >> search;
				if (!bst.Exists(search))
					cout << "Non trovato!" << endl;
				else
					cout << "Trovato!" << endl;
				break;
			}
			case 6:
			{
				if constexpr (is_same<Data, int>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Prodotto per gli interi minori di n" << endl << "Inserisci n:   ";
					int n{};
					cin >> n;
					long result = 1;
					bst.Fold(&FoldProductLessThanN<Data>, &n, &result);
					cout << result << endl;
				}
				if constexpr (is_same<Data, double>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Somma per i double maggiori di n;" << endl << "Inserisci n:   ";
					double n{};
					cin >> n;
					double result = 0;
					bst.Fold(&FoldSumMoreThanN<Data>, &n, &result);
					cout << result << endl;
				}
				if constexpr (is_same<Data, string>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Concatenazione con lunghezza minore o uguale a n;" << endl << "Inserisci n:   ";
					unsigned long n{};
					cin >> n;
					string result = "";
					bst.Fold(&FoldConcatLessEqualN<Data>, &n, &result);
					cout << result << endl;
				}
				break;
			}
			case 7:
			{
				Data search{};
				cout << "Inserisci l'elemento da rimuovere: ";
				cin >> search;
				if (!bst.Remove(search))
					cout << "Valore non trovato!" << endl;
				else
					cout << "Valore trovato e eliminato!" << endl;
				break;
			}
			case 8:
				cout << "Il BST ha size: " << bst.Size() << endl;
				break;
			default:
				cout << "Errore di input" << endl;
		}
	}
}

template<typename Data>
void hashtabletest(HashTable<Data>& hash)
{
	bool selection = false;
	int testtype;
	cout << endl << "Seleziona il tipo di operazione" << endl;
	while (!selection)
	{
		cout << "0. Torna indietro" << endl << "1. Stampa tutti gli elementi" << endl << "2. Inserisci un valore" << endl << "3. Controlla esistenza di un valore" << endl << "4. Calcola la funzione fold relativa al dato" << endl << "5. Rimuovi un valore" << endl << "6. Stampa la size" << endl;
		string input;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
			{
				hash.Map(&MapPrint<Data>, 0);
				cout << endl;
				break;
			}
			case 2:
			{
				Data insert{};
				cout << "Inserisci l'elemento da inserire: ";
				cin >> insert;
				if (!hash.Insert(insert))
					cout << "Non inserito (probabilmente è già presente)!" << endl;
				else
					cout << "Inserito!" << endl;
				break;
			}
			case 3:
			{
				Data search{};
				cout << "Inserisci l'elemento da cercare: ";
				cin >> search;
				if (!hash.Exists(search))
					cout << "Non trovato!" << endl;
				else
					cout << "Trovato!" << endl;
				break;
			}
			case 4:
			{
				if constexpr (is_same<Data, int>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Prodotto per gli interi minori di n" << endl << "Inserisci n:   ";
					int n{};
					cin >> n;
					long result = 1;
					hash.Fold(&FoldProductLessThanN<Data>, &n, &result);
					cout << result << endl;
				}
				if constexpr (is_same<Data, double>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Somma per i double maggiori di n;" << endl << "Inserisci n:   ";
					double n{};
					cin >> n;
					double result = 0;
					hash.Fold(&FoldSumMoreThanN<Data>, &n, &result);
					cout << result << endl;
				}
				if constexpr (is_same<Data, string>::value)
				{
					cout << "Funzione fold per questo tipo di dato: Concatenazione con lunghezza minore o uguale a n;" << endl << "Inserisci n:   ";
					unsigned long n{};
					cin >> n;
					string result = "";
					hash.Fold(&FoldConcatLessEqualN<Data>, &n, &result);
					cout << result << endl;
				}
				break;
			}
			case 5:
			{
				Data search{};
				cout << "Inserisci l'elemento da rimuovere: ";
				cin >> search;
				if (!hash.Remove(search))
					cout << "Valore non trovato!" << endl;
				else
					cout << "Valore trovato e eliminato!" << endl;
				break;
			}
			case 6:
				cout << "La hashmap ha size: " << hash.Size() << endl;
				break;
			default:
				cout << "Errore di input" << endl;
		}
	}
}

void vectortest()
{
	unsigned long size;
	cout << "Quanto rendere grande il vettore?: ";
	string input;
	cin >> input;
	size = stoi(input);
	int testtype;
	bool selection = false;
	while (!selection)
	{
		cout << endl << "Che tipo di dato vuoi usare?" << endl << "1. Test su Int" << endl << "2. Test su Double" << endl << "3. Test su String" << endl << "0. Torna indietro" << endl;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
			{
				uniform_int_distribution<int> dist(-100, 100);
				Vector<int> v(size);
				for (unsigned long i = 0; i < size; i++)
				{
					v[i] = dist(gen);
				}
				vectortest(v);
				break;
			}
			case 2:
			{
				uniform_real_distribution<double> dist(0, 100);

				Vector<double> v(size);
				for (unsigned long i = 0; i < size; i++)
				{
					v[i] = round(dist(gen) * 1000.0) / 1000.0;
				}
				vectortest(v);
				break;
			}
			case 3:
			{
				uniform_int_distribution<int> dist(2, 5);

				Vector<string> v(size);
				for (unsigned long i = 0; i < size; i++)
				{
					v[i] = GeneraStringaCasuale(dist(gen));
				}
				vectortest(v);
				break;
			}
			default:
				cout << "Input non valido" << endl;
		}
	}
}

void listtest()
{
	unsigned long size;
	cout << "Quanto rendere grande la lista?: ";
	cin >> size;
	int testtype;
	bool selection = false;
	while (!selection)
	{
		cout << endl << "Che tipo di dato vuoi usare?" << endl << "1. Test su Int" << endl << "2. Test su Double" << endl << "3. Test su String" << endl << "0. Torna indietro" << endl;
		string input;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
			{
				uniform_int_distribution<int> dist(-100, 100);
				List<int> l;
				for (unsigned long i = 0; i < size; i++)
				{
					l.InsertAtBack(dist(gen));
				}
				listtest(l);
				break;
			}
			case 2:
			{
				uniform_real_distribution<double> dist(0, 100);

				List<double> l;
				for (unsigned long i = 0; i < size; i++)
				{
					l.InsertAtBack(round(dist(gen) * 1000.0) / 1000.0);
				}
				listtest(l);
				break;
			}
			case 3:
			{
				uniform_int_distribution<int> dist(2, 5);
				List<string> l;
				for (unsigned long i = 0; i < size; i++)
				{
					l.InsertAtBack(GeneraStringaCasuale(dist(gen)));
				}
				listtest(l);
				break;
			}
			default:
				cout << "Input non valido" << endl;
		}
	}
}

void stacktest()
{
	bool usevec{};
	int testtype = 0;
	cout << endl << "Che implementazione usare?" << endl << "1. Vettore" << endl << "2. Lista" << endl;
	while (testtype != 1 && testtype != 2)
	{
		string input;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 1:
				usevec = true;
				break;
			case 2:
				usevec = false;
				break;
			default:
				cout << "Input non valido" << endl;
		}
	}
	testtype = 0;
	unsigned long size;
	cout << "Quanto rendere grande lo stack?: ";
	string input;
	cin >> input;
	size = stoi(input);
	cout << endl << "Che tipo di dato vuoi usare?" << endl << "1. Test su Int" << endl << "2. Test su Double" << endl << "3. Test su String" << endl << "0. Torna indietro" << endl;
	bool selection = false;
	while (!selection)
	{
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
			{
				uniform_int_distribution<int> dist(-100, 100);
				if (usevec)
				{
					StackVec<int> s;
					for (unsigned long i = 0; i < size; i++)
					{
						s.Push(dist(gen));
					}
					stacktest(s);
				}
				else
				{
					StackLst<int> s;
					stacktest(s);
				}
				break;
			}
			case 2:
			{
				uniform_real_distribution<double> dist(0, 100);
				if (usevec)
				{
					StackVec<double> s;
					for (unsigned long i = 0; i < size; i++)
					{
						s.Push(round(dist(gen) * 1000.0) / 1000.0);
					}
					stacktest(s);
				}
				else
				{
					StackLst<double> s;
					for (unsigned long i = 0; i < size; i++)
					{
						s.Push(round(dist(gen) * 1000.0) / 1000.0);
					}
					stacktest(s);
				}
				break;
			}
			case 3:
			{
				uniform_int_distribution<int> dist(2, 5);
				if (usevec)
				{
					StackVec<string> s;
					for (unsigned long i = 0; i < size; i++)
					{
						s.Push(GeneraStringaCasuale(dist(gen)));
					}
					stacktest(s);
				}
				else
				{
					StackLst<string> s;
					for (unsigned long i = 0; i < size; i++)
					{
						s.Push(GeneraStringaCasuale(dist(gen)));
					}
					stacktest(s);
				}
				break;
			}
			default:
				cout << "Input non valido" << endl;
		}
	}
}

void queuetest()
{
	bool usevec{};
	int testtype = 0;
	cout << endl << "Che implementazione usare?" << endl << "1. Vettore" << endl << "2. Lista" << endl;
	while (testtype != 1 && testtype != 2)
	{
		cin >> testtype;
		switch (testtype)
		{
			case 1:
				usevec = true;
				break;
			case 2:
				usevec = false;
				break;
			default:
				cout << "Input non valido" << endl;
		}
	}
	testtype = 0;
	unsigned long size;
	cout << "Quanto rendere grande la queue?: ";
	string input;
	cin >> input;
	size = stoi(input);
	cout << endl << "Che tipo di dato vuoi usare?" << endl << "1. Test su Int" << endl << "2. Test su Double" << endl << "3. Test su String" << endl << "0. Torna indietro" << endl;
	bool selection = false;
	while (!selection)
	{
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
			{
				uniform_int_distribution<int> dist(-100, 100);
				if (usevec)
				{
					QueueVec<int> q;
					for (unsigned long i = 0; i < size; i++)
					{
						q.Enqueue(dist(gen));
					}
					queuetest(q);
				}
				else
				{
					QueueLst<int> q;
					for (unsigned long i = 0; i < size; i++)
					{
						q.Enqueue(dist(gen));
					}
					queuetest(q);
				}
				break;
			}
			case 2:
			{
				uniform_real_distribution<double> dist(0, 100);
				if (usevec)
				{
					QueueVec<double> q;
					for (unsigned long i = 0; i < size; i++)
					{
						q.Enqueue(round(dist(gen) * 1000.0) / 1000.0);
					}
					queuetest(q);
				}
				else
				{
					QueueLst<double> q;
					for (unsigned long i = 0; i < size; i++)
					{
						q.Enqueue(round(dist(gen) * 1000.0) / 1000.0);
					}
					queuetest(q);
				}
				break;
			}
			case 3:
			{
				uniform_int_distribution<int> dist(2, 5);
				if (usevec)
				{
					QueueVec<string> q;
					for (unsigned long i = 0; i < size; i++)
					{
						q.Enqueue(GeneraStringaCasuale(dist(gen)));
					}
					queuetest(q);
				}
				else
				{
					QueueLst<string> q;
					for (unsigned long i = 0; i < size; i++)
					{
						q.Enqueue(GeneraStringaCasuale(dist(gen)));
					}
					queuetest(q);
				}
				break;
			}
			default:
				cout << "Input non valido" << endl;
		}
	}
}

void binarytreetest()
{
	bool usevec{};
	int testtype = 0;
	cout << endl << "Che implementazione usare?" << endl << "1. Vettore" << endl << "2. Lista" << endl;
	while (testtype != 1 && testtype != 2)
	{
		string input;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 1:
				usevec = true;
				break;
			case 2:
				usevec = false;
				break;
			default:
				cout << "Input non valido" << endl;
		}
	}
	testtype = 0;
	unsigned long size;
	cout << "Quanto rendere grande l'albero?: ";
	cin >> size;
	bool selection = false;
	while (!selection)
	{
		cout << endl << "Che tipo di dato vuoi usare?" << endl << "1. Test su Int" << endl << "2. Test su Double" << endl << "3. Test su String" << endl << "0. Torna indietro" << endl;
		string input;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
			{
				uniform_int_distribution<int> dist(-100, 100);
				if (usevec)
				{
					Vector<int> v(size);
					for (unsigned long i = 0; i < size; i++)
					{
						v[i] = dist(gen);
					}
					BinaryTreeVec<int> bt(v);
					binarytreetest(bt);
				}
				else
				{
					List<int> l;
					for (unsigned long i = 0; i < size; i++)
					{
						l.InsertAtFront(dist(gen));
					}
					BinaryTreeLnk<int> bt(l);
					binarytreetest(bt);
				}
				break;
			}
			case 2:
			{
				uniform_real_distribution<double> dist(0, 100);
				if (usevec)
				{
					Vector<double> v(size);
					for (unsigned long i = 0; i < size; i++)
					{
						v[i] = round(dist(gen) * 1000.0) / 1000.0;
					}
					BinaryTreeVec<double> bt(v);
					binarytreetest(bt);
				}
				else
				{
					List<double> l;
					for (unsigned long i = 0; i < size; i++)
					{
						l.InsertAtFront(round(dist(gen) * 1000.0) / 1000.0);
					}
					BinaryTreeLnk<double> bt(l);
					binarytreetest(bt);
				}
				break;
			}
			case 3:
			{
				uniform_int_distribution<int> dist(2, 5);
				if (usevec)
				{
					Vector<string> v(size);
					for (unsigned long i = 0; i < size; i++)
					{
						v[i] = GeneraStringaCasuale(dist(gen));
					}
					BinaryTreeVec<string> bt(v);
					binarytreetest(bt);
				}
				else
				{
					List<string> l;
					for (unsigned long i = 0; i < size; i++)
					{
						l.InsertAtFront(GeneraStringaCasuale(dist(gen)));
					}
					BinaryTreeLnk<string> bt(l);
					binarytreetest(bt);
				}
				break;
			}
			default:
				cout << "Input non valido" << endl;
		}
	}
}

void bsttest()
{
	int testtype;
	unsigned long size;
	cout << "Quanto rendere grande l'albero?: ";
	cin >> size;
	bool selection = false;
	while (!selection)
	{
		cout << endl << "Che tipo di dato vuoi usare?" << endl << "1. Test su Int" << endl << "2. Test su Double" << endl << "3. Test su String" << endl << "0. Torna indietro" << endl;
		string input;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
			{
				uniform_int_distribution<int> dist(-100, 100);
				BST<int> bst;
				for (; bst.Size() < size;)
				{
					while (!bst.Insert(dist(gen)))
					{

					}
				}
				bsttest(bst);
				break;
			}
			case 2:
			{
				uniform_real_distribution<double> dist(0, 100);
				BST<double> bst;
				for (; bst.Size() < size;)
				{
					bst.Insert(round(dist(gen) * 1000.0) / 1000.0);
				}
				bsttest(bst);
				break;
			}
			case 3:
			{
				uniform_int_distribution<int> dist(2, 5);
				BST<string> bst;
				for (; bst.Size() < size;)
				{
					bst.Insert(GeneraStringaCasuale(dist(gen)));
				}
				bsttest(bst);
				break;
			}
			default:
				cout << "Input non valido" << endl;
		}
	}
}

void hashtabletest()
{
	bool openaddr{};
	int testtype = 0;
	cout << endl << "Che implementazione usare?" << endl << "1. Indirizzamento aperto" << endl << "2. Indirizzamento chiuso" << endl;
	while (testtype != 1 && testtype != 2)
	{
		string input;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 1:
				openaddr = true;
				break;
			case 2:
				openaddr = false;
				break;
			default:
				cout << "Input non valido" << endl;
		}
	}
	testtype = 0;
	unsigned long size;
	cout << "Quanto rendere grande l'hash table?: ";
	cin >> size;
	bool selection = false;
	while (!selection)
	{
		cout << endl << "Che tipo di dato vuoi usare?" << endl << "1. Test su Int" << endl << "2. Test su Double" << endl << "3. Test su String" << endl << "0. Torna indietro" << endl;
		string input;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
			{
				uniform_int_distribution<int> dist(-100, 100);
				if (openaddr)
				{
					HashTableOpnAdr<int> hash;
					while (hash.Size() < size)
						hash.Insert(dist(gen));
					hashtabletest(hash);
				}
				else
				{
					HashTableClsAdr<int> hash(size);
					while (hash.Size() < size)
						hash.Insert(dist(gen));
					hashtabletest(hash);
				}
				break;
			}
			case 2:
			{
				uniform_real_distribution<double> dist(0, 100);
				if (openaddr)
				{
					HashTableOpnAdr<double> hash;
					while (hash.Size() < size)
						hash.Insert(round(dist(gen) * 1000.0) / 1000.0);
					hashtabletest(hash);
				}
				else
				{
					HashTableClsAdr<double> hash(size);
					while (hash.Size() < size)
						hash.Insert(round(dist(gen) * 1000.0) / 1000.0);
					hashtabletest(hash);
				}

				break;
			}
			case 3:
			{
				uniform_int_distribution<int> dist(2, 6);
				if (openaddr)
				{
					HashTableOpnAdr<string> hash;
					while (hash.Size() < size)
						hash.Insert(GeneraStringaCasuale(dist(gen)));
					hashtabletest(hash);
				}
				else
				{
					HashTableClsAdr<string> hash(size);
					while (hash.Size() < size)
						hash.Insert(GeneraStringaCasuale(dist(gen)));
					hashtabletest(hash);
				}
				break;
			}
			default:
				cout << "Input non valido" << endl;
		}
	}
}

void mytest()
{
	bool selection = false;
	int testtype = 0;
	while (!selection)
	{
		cout << endl << "Test menu' " << endl << "0. Esci" << endl << "1. Test su List" << endl << "2. Test su Vector" << endl << "3. Test su Stack" << endl << "4. Test su Queue" << endl << "5. Test su Binarytree" << endl << "6. Test su BST" << endl << "7. Test su Hashmap" << endl
			 << "8. Test del professore" << endl;
		string input;
		cin >> input;
		testtype = stoi(input);
		switch (testtype)
		{
			case 0:
				selection = true;
				break;
			case 1:
				listtest();
				break;
			case 2:
				vectortest();
				break;
			case 3:
				stacktest();
				break;
			case 4:
				queuetest();
				break;
			case 5:
				binarytreetest();
				break;
			case 6:
				bsttest();
				break;
			case 7:
				hashtabletest();
				break;
			case 8:
			{
				lasdtest();
				break;
			}
			default:
				cout << "Input non valido" << endl;
		}
	}
}
