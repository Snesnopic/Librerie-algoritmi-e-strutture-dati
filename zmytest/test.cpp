// ...
#include "../container/container.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../zlasdtest/test.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../stack/vec/stackvec.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include <sstream>
using namespace std;
using namespace lasd;

const std::string VALID_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
default_random_engine gen;
uniform_int_distribution<int> dist(0,VALID_CHARS.size() - 1);
string GeneraStringaCasuale(unsigned int lunghezza)
{
    ostringstream oss;
    for (unsigned int i = 0; i < lunghezza; i++)
    {
        oss << VALID_CHARS[dist(gen)];
    }
    return oss.str();
}
template <typename Data>
void FoldSumLessThanN(const Data& dat, const void* _, void* acc)
{
    if(dat < *((Data*)_))
        *((Data*) acc) += dat;
}
template <typename Data>
void FoldProductMoreThanN(const Data& dat, const void* _, void* acc)
{
    if(dat > *((Data*)_))
        *((Data*) acc) *= dat;
}
template <typename Data>
void FoldConcatLessEqualN(const Data& dat, const void* _, void* acc)
{
    if(dat.length() <= *((unsigned long*)_))
        *((Data*) acc) += dat;
}
template <typename Data>
void MapPrint(Data& dat, void* _)
{
    std::cout << dat <<" ";
}
template <typename Data>
void MapDouble(Data& dat, void* _)
{
    dat = dat*2;
}
template <typename Data>
void MapSquare(Data& dat, void* _)
{
    dat = pow(dat, 2);
}
template <typename Data>
void MapUppercase(Data& dat, void* _)
{
    for(char &c : dat)
        c = toupper(c);
}

void vectorinttest()
{
    unsigned long size;
    cout<<"Quanto rendere grande il vettore di interi?: ";
    cin>>size;
    Vector<int> v(size);
    default_random_engine gen(random_device{}());
    uniform_int_distribution<int> dist(0,100);
    for(unsigned long i = 0; i < size; i++)
    {
        v[i] =dist(gen);
    }
    cout<<"Il primo elemento e' "<<v.Front()<<", l'ultimo e' "<<v.Back()<<endl;
    bool selection = false;
    int testtype;
    while(!selection)
    {
        cout<<"0. Esci"<<endl<<"1. Funzione map: Stampa tutti gli elementi"<<endl<<
            "2. Controlla esistenza di un elemento"<<endl<<"3. Funzione fold: Somma per gli interi minori di n"<<endl<<"4. Funzione map: 2n"<<endl;
        cin>>testtype;
        switch(testtype)
        {
        case 0:
            selection = true;
            break;
        case 1:
            v.Map(&MapPrint<int>,0);
            cout<<endl;
            break;
        case 2:
            cout<<endl<<"Inserisci numero da cercare:   ";
            unsigned long search;
            cin>>search;
            if(v.Exists(search))
                cout<<"Il numero e' presente!"<<endl;
            else
                cout<<"Il numero non e' presente!"<<endl;
            break;
        case 3:
        {
            cout<<endl<<"Inserisci n:   ";
            unsigned long n;
            cin>>n;
            unsigned long result = 0;
            v.Fold(&FoldSumLessThanN<int>,&n,&result);
            cout<<result<<endl;
            break;
        }
        case 4:
            v.Map(&MapDouble<int>,0);
            cout<<"Fatto, prova a stampare"<<endl;
            break;
        default:
            cout<<"Errore di input"<<endl;
        }
    }
}

void vectordoubletest()
{
    unsigned long size;
    cout<<"Quanto rendere grande il vettore di double?: ";
    cin>>size;
    Vector<double> v(size);
    default_random_engine gen(random_device{}());
    uniform_real_distribution<double> dist(0,100);
    for(unsigned long i = 0; i < size; i++)
    {
        v[i] = round(dist(gen)*1000.0)/1000.0;
    }
    cout<<"Il primo elemento e' "<<v.Front()<<", l'ultimo e' "<<v.Back()<<endl;
    bool selection = false;
    int testtype;
    while(!selection)
    {
        cout<<"0. Esci"<<endl<<"1. Funzione map: Stampa tutti gli elementi"<<endl<<
            "2. Controlla esistenza di un elemento"<<endl<<"3. Funzione fold: Prodotto per i double maggiori di n"<<endl<<"4. Funzione map: n*n"<<endl;
        cin>>testtype;
        switch(testtype)
        {
        case 0:
            selection = true;
            break;
        case 1:
            v.Map(&MapPrint<double>,0);
            cout<<endl;
            break;
        case 2:
            cout<<endl<<"Inserisci numero da cercare:   ";
            double search;
            cin>>search;
            if(v.Exists(search))
                cout<<"Il numero e' presente!"<<endl;
            else
                cout<<"Il numero non e' presente!"<<endl;
            break;
        case 3:
        {
            cout<<endl<<"Inserisci n:   ";
            unsigned long n;
            cin>>n;
            unsigned long result = 0;
            v.Fold(&FoldProductMoreThanN<double>,&n,&result);
            cout<<result<<endl;
            break;
        }
        case 4:
            v.Map(&MapSquare<double>,0);
            cout<<"Fatto, prova a stampare"<<endl;
            break;
        default:
            cout<<"Errore di input"<<endl;
        }
    }
}

void vectorstringtest()
{
    unsigned long size;
    cout<<"Quanto rendere grande il vettore di string?: ";
    cin>>size;
    Vector<string> v(size);
    default_random_engine gen;
    uniform_int_distribution<int> dist(2,5);
    for(unsigned long i = 0; i < size; i++)
    {
        v[i] = GeneraStringaCasuale(dist(gen));
    }
    cout<<"Il primo elemento e' "<<v.Front()<<", l'ultimo e' "<<v.Back()<<endl;
    bool selection = false;
    int testtype;
    while(!selection)
    {
        cout<<"0. Esci"<<endl<<"1. Funzione map: Stampa tutti gli elementi"<<endl<<
            "2. Controlla esistenza di un elemento"<<endl<<"3. Funzione fold: Concatenazione per lunghezza minore o uguale a n"<<endl<<"4. Funzione map: uppercase"<<endl;
        cin>>testtype;
        switch(testtype)
        {
        case 0:
            selection = true;
            break;
        case 1:
            v.Map(&MapPrint<string>,0);
            cout<<endl;
            break;
        case 2:
        {
            cout<<endl<<"Inserisci stringa da cercare:   ";
            string search;
            cin>>search;
            if(v.Exists(search))
                cout<<"La stringa e' presente!"<<endl;
            else
                cout<<"La stringa non e' presente!"<<endl;
            break;
        }
        case 3:
        {
            cout<<endl<<"Inserisci n:   ";
            unsigned long n;
            cin>>n;
            string result = "";
            v.Fold(&FoldConcatLessEqualN<string>,&n,&result);
            cout<<result<<endl;
            break;
        }
        case 4:
            v.Map(&MapUppercase<string>,0);
            cout<<"Fatto, prova a stampare"<<endl;
            break;
        default:
            cout<<"Errore di input"<<endl;
        }
    }
}

void listinttest()
{
    unsigned long size;
    cout<<"Quanto rendere grande la lista di interi?: ";
    cin>>size;
    List<int> l;
    default_random_engine gen(random_device{}());
    uniform_int_distribution<int> dist(0,100);
    for(unsigned long i = 0; i < size; i++)
    {
        l.InsertAtBack(dist(gen));
    }
    cout<<"Il primo elemento e' "<<l.Front()<<", l'ultimo e' "<<l.Back()<<endl;
    bool selection = false;
    int testtype;
    while(!selection)
    {
        cout<<"0. Esci"<<endl<<"1. Funzione map: Stampa tutti gli elementi"<<endl<<
            "2. Controlla esistenza di un elemento"<<endl<<"3. Funzione fold: Somma per gli interi minori di n"<<endl<<"4. Funzione map: 2n"<<endl;
        cin>>testtype;
        switch(testtype)
        {
        case 0:
            selection = true;
            break;
        case 1:
            l.Map(&MapPrint<int>,0);
            cout<<endl;
            break;
        case 2:
            cout<<endl<<"Inserisci numero da cercare:   ";
            unsigned long search;
            cin>>search;
            if(l.Exists(search))
                cout<<"Il numero e' presente!"<<endl;
            else
                cout<<"Il numero non e' presente!"<<endl;
            break;
        case 3:
        {
            cout<<endl<<"Inserisci n:   ";
            unsigned long n;
            cin>>n;
            unsigned long result = 0;
            l.Fold(&FoldSumLessThanN<int>,&n,&result);
            cout<<result<<endl;
            break;
        }
        case 4:
            l.Map(&MapDouble<int>,0);
            cout<<"Fatto, prova a stampare"<<endl;
            break;
        default:
            cout<<"Errore di input"<<endl;
        }
    }
}

void listdoubletest()
{
    unsigned long size;
    cout<<"Quanto rendere grande la lista di double?: ";
    cin>>size;
    List<double> l;
    default_random_engine gen(random_device{}());
    uniform_real_distribution<double> dist(0,100);
    for(unsigned long i = 0; i < size; i++)
    {
        l.InsertAtBack(round(dist(gen)*1000.0)/1000.0);
    }
    cout<<"Il primo elemento e' "<<l.Front()<<", l'ultimo e' "<<l.Back()<<endl;
    bool selection = false;
    int testtype;
    while(!selection)
    {
        cout<<"0. Esci"<<endl<<"1. Funzione map: Stampa tutti gli elementi"<<endl<<
            "2. Controlla esistenza di un elemento"<<endl<<"3. Funzione fold: Prodotto per i double maggiori di n"<<endl<<"4. Funzione map: n*n"<<endl;
        cin>>testtype;
        switch(testtype)
        {
        case 0:
            selection = true;
            break;
        case 1:
            l.Map(&MapPrint<double>,0);
            cout<<endl;
            break;
        case 2:
            cout<<endl<<"Inserisci numero da cercare:   ";
            double search;
            cin>>search;
            if(l.Exists(search))
                cout<<"Il numero e' presente!"<<endl;
            else
                cout<<"Il numero non e' presente!"<<endl;
            break;
        case 3:
        {
            cout<<endl<<"Inserisci n:   ";
            unsigned long n;
            cin>>n;
            unsigned long result = 0;
            l.Fold(&FoldProductMoreThanN<double>,&n,&result);
            cout<<result<<endl;
            break;
        }
        case 4:
            l.Map(&MapSquare<double>,0);
            cout<<"Fatto, prova a stampare"<<endl;
            break;
        default:
            cout<<"Errore di input"<<endl;
        }
    }
}

void liststringtest()
{
    unsigned long size;
    cout<<"Quanto rendere grande la lista di string?: ";
    cin>>size;
    List<string> l;
    default_random_engine gen;
    uniform_int_distribution<int> dist(2,5);
    for(unsigned long i = 0; i < size; i++)
    {
        l.InsertAtBack(GeneraStringaCasuale(dist(gen)));
    }
    cout<<"Il primo elemento e' "<<l.Front()<<", l'ultimo e' "<<l.Back()<<endl;
    bool selection = false;
    int testtype;
    while(!selection)
    {
        cout<<"0. Esci"<<endl<<"1. Funzione map: Stampa tutti gli elementi"<<endl<<
            "2. Controlla esistenza di un elemento"<<endl<<"3. Funzione fold: Concatenazione per lunghezza minore o uguale a n"<<endl<<"4. Funzione map: uppercase"<<endl;
        cin>>testtype;
        switch(testtype)
        {
        case 0:
            selection = true;
            break;
        case 1:
            l.Map(&MapPrint<string>,0);
            cout<<endl;
            break;
        case 2:
        {
            cout<<endl<<"Inserisci stringa da cercare:   ";
            string search;
            cin>>search;
            if(l.Exists(search))
                cout<<"La stringa e' presente!"<<endl;
            else
                cout<<"La stringa non e' presente!"<<endl;
            break;
        }
        case 3:
        {
            cout<<endl<<"Inserisci n:   ";
            unsigned long n;
            cin>>n;
            string result = "";
            l.Fold(&FoldConcatLessEqualN<string>,&n,&result);
            cout<<result<<endl;
            break;
        }
        case 4:
            l.Map(&MapUppercase<string>,0);
            cout<<"Fatto, prova a stampare"<<endl;
            break;
        default:
            cout<<"Errore di input"<<endl;
        }
    }
}

void stackinttest(const Stack<Data> &s)
{
    unsigned long size;
    cout<<"Quanto rendere grande lo stack di interi?: ";
    cin>>size;
    default_random_engine gen(random_device{}());
    uniform_int_distribution<int> dist(0,100);
    for(unsigned long i = 0; i < size; i++)
    {
        s.Push(dist(gen));
    }
    cout<<"L'elemento in cima e' "<<s.Top();
    bool selection = false;
    int testtype;
    while(!selection)
    {
        cout<<"0. Esci"<<endl<<"1. Inserisci un elemento"<<endl<<
            "2. Rimuovi un elemento"<<endl<<"3. Visualizza e rimuovi un elemento"<<endl<<"4. Visualizza un elemento"<<endl<<"5. E' vuoto?"<<endl<<"6. Stampa grandezza"<<endl<<
            "7. Svuota la struttura"<<endl;
        cin>>testtype;
        switch(testtype)
        {
        case 0:
            selection = true;
            break;
        case 1:
            l.Map(&MapPrint<int>,0);
            cout<<endl;
            break;
        case 2:
            cout<<endl<<"Inserisci numero da cercare:   ";
            unsigned long search;
            cin>>search;
            if(l.Exists(search))
                cout<<"Il numero e' presente!"<<endl;
            else
                cout<<"Il numero non e' presente!"<<endl;
            break;
        case 3:
        {
            cout<<endl<<"Inserisci n:   ";
            unsigned long n;
            cin>>n;
            unsigned long result = 0;
            l.Fold(&FoldSumLessThanN<int>,&n,&result);
            cout<<result<<endl;
            break;
        }
        case 4:
            l.Map(&MapDouble<int>,0);
            cout<<"Fatto, prova a stampare"<<endl;
            break;
        default:
            cout<<"Errore di input"<<endl;
        }
    }
}

void stackdoubletest(const Stack<double> &s)
{
    unsigned long size;
    cout<<"Quanto rendere grande lo stack di double?: ";
    cin>>size;
    default_random_engine gen(random_device{}());
    uniform_real_distribution<double> dist(0,100);
    for(unsigned long i = 0; i < size; i++)
    {
        s.Push(round(dist(gen)*1000.0)/1000.0);
    }
    cout<<"Il primo elemento e' "<<l.Front()<<", l'ultimo e' "<<l.Back()<<endl;
    bool selection = false;
    int testtype;
    while(!selection)
    {
        cout<<"0. Esci"<<endl<<"1. Funzione map: Stampa tutti gli elementi"<<endl<<
            "2. Controlla esistenza di un elemento"<<endl<<"3. Funzione fold: Prodotto per i double maggiori di n"<<endl<<"4. Funzione map: n*n"<<endl;
        cin>>testtype;
        switch(testtype)
        {
        case 0:
            selection = true;
            break;
        case 1:
            l.Map(&MapPrint<double>,0);
            cout<<endl;
            break;
        case 2:
            cout<<endl<<"Inserisci numero da cercare:   ";
            double search;
            cin>>search;
            if(l.Exists(search))
                cout<<"Il numero e' presente!"<<endl;
            else
                cout<<"Il numero non e' presente!"<<endl;
            break;
        case 3:
        {
            cout<<endl<<"Inserisci n:   ";
            unsigned long n;
            cin>>n;
            unsigned long result = 0;
            l.Fold(&FoldProductMoreThanN<double>,&n,&result);
            cout<<result<<endl;
            break;
        }
        case 4:
            l.Map(&MapSquare<double>,0);
            cout<<"Fatto, prova a stampare"<<endl;
            break;
        default:
            cout<<"Errore di input"<<endl;
        }
    }
    */
}

void stackstringtest(const Stack<string> &s)
{
    unsigned long size;
    cout<<"Quanto rendere grande la lista di string?: ";
    cin>>size;
    default_random_engine gen;
    uniform_int_distribution<int> dist(2,5);
    for(unsigned long i = 0; i < size; i++)
    {
        s.Push(GeneraStringaCasuale(dist(gen)));
    }
    cout<<"Il primo elemento e' "<<l.Front()<<", l'ultimo e' "<<l.Back()<<endl;
    bool selection = false;
    int testtype;
    while(!selection)
    {
        cout<<"0. Esci"<<endl<<"1. Funzione map: Stampa tutti gli elementi"<<endl<<
            "2. Controlla esistenza di un elemento"<<endl<<"3. Funzione fold: Concatenazione per lunghezza minore o uguale a n"<<endl<<"4. Funzione map: uppercase"<<endl;
        cin>>testtype;
        switch(testtype)
        {
        case 0:
            selection = true;
            break;
        case 1:
            l.Map(&MapPrint<string>,0);
            cout<<endl;
            break;
        case 2:
        {
            cout<<endl<<"Inserisci stringa da cercare:   ";
            string search;
            cin>>search;
            if(l.Exists(search))
                cout<<"La stringa e' presente!"<<endl;
            else
                cout<<"La stringa non e' presente!"<<endl;
            break;
        }
        case 3:
        {
            cout<<endl<<"Inserisci n:   ";
            unsigned long n;
            cin>>n;
            string result = "";
            l.Fold(&FoldConcatLessEqualN<string>,&n,&result);
            cout<<result<<endl;
            break;
        }
        case 4:
            l.Map(&MapUppercase<string>,0);
            cout<<"Fatto, prova a stampare"<<endl;
            break;
        default:
            cout<<"Errore di input"<<endl;
        }
    }
    */
}

void queueinttest(const Queue<int> &q)
{
    unsigned long size;
    cout<<"Quanto rendere grande la queue di interi?: ";
    cin>>size;
    default_random_engine gen(random_device{}());
    uniform_int_distribution<int> dist(0,100);
    for(unsigned long i = 0; i < size; i++)
    {
        q.Enqueue(dist(gen));
    }
    cout<<"Il primo elemento e' "<<l.Front()<<", l'ultimo e' "<<l.Back()<<endl;
    bool selection = false;
    int testtype;
    while(!selection)
    {
        cout<<"0. Esci"<<endl<<"1. Funzione map: Stampa tutti gli elementi"<<endl<<
            "2. Controlla esistenza di un elemento"<<endl<<"3. Funzione fold: Somma per gli interi minori di n"<<endl<<"4. Funzione map: 2n"<<endl;
        cin>>testtype;
        switch(testtype)
        {
        case 0:
            selection = true;
            break;
        case 1:
            l.Map(&MapPrint<int>,0);
            cout<<endl;
            break;
        case 2:
            cout<<endl<<"Inserisci numero da cercare:   ";
            unsigned long search;
            cin>>search;
            if(l.Exists(search))
                cout<<"Il numero e' presente!"<<endl;
            else
                cout<<"Il numero non e' presente!"<<endl;
            break;
        case 3:
        {
            cout<<endl<<"Inserisci n:   ";
            unsigned long n;
            cin>>n;
            unsigned long result = 0;
            l.Fold(&FoldSumLessThanN<int>,&n,&result);
            cout<<result<<endl;
            break;
        }
        case 4:
            l.Map(&MapDouble<int>,0);
            cout<<"Fatto, prova a stampare"<<endl;
            break;
        default:
            cout<<"Errore di input"<<endl;
        }
    }
    */
}

void queuedoubletest(const Queue<double> &q)
{
    unsigned long size;
    cout<<"Quanto rendere grande la lista di double?: ";
    cin>>size;
    default_random_engine gen(random_device{}());
    uniform_real_distribution<double> dist(0,100);
    for(unsigned long i = 0; i < size; i++)
    {
        q.Enqueue(round(dist(gen)*1000.0)/1000.0);
    }
    cout<<"Il primo elemento e' "<<l.Front()<<", l'ultimo e' "<<l.Back()<<endl;
    bool selection = false;
    int testtype;
    while(!selection)
    {
        cout<<"0. Esci"<<endl<<"1. Funzione map: Stampa tutti gli elementi"<<endl<<
            "2. Controlla esistenza di un elemento"<<endl<<"3. Funzione fold: Prodotto per i double maggiori di n"<<endl<<"4. Funzione map: n*n"<<endl;
        cin>>testtype;
        switch(testtype)
        {
        case 0:
            selection = true;
            break;
        case 1:
            l.Map(&MapPrint<double>,0);
            cout<<endl;
            break;
        case 2:
            cout<<endl<<"Inserisci numero da cercare:   ";
            double search;
            cin>>search;
            if(l.Exists(search))
                cout<<"Il numero e' presente!"<<endl;
            else
                cout<<"Il numero non e' presente!"<<endl;
            break;
        case 3:
        {
            cout<<endl<<"Inserisci n:   ";
            unsigned long n;
            cin>>n;
            unsigned long result = 0;
            l.Fold(&FoldProductMoreThanN<double>,&n,&result);
            cout<<result<<endl;
            break;
        }
        case 4:
            l.Map(&MapSquare<double>,0);
            cout<<"Fatto, prova a stampare"<<endl;
            break;
        default:
            cout<<"Errore di input"<<endl;
        }
    }
}

void queuestringtest(Queue<string> &q)
{

    unsigned long size;
    cout<<"Quanto rendere grande la lista di string?: ";
    cin>>size;
    default_random_engine gen;
    uniform_int_distribution<int> dist(2,5);
    for(unsigned long i = 0; i < size; i++)
    {
        q.Enqueue(GeneraStringaCasuale(dist(gen)));
    }
    cout<<"Il primo elemento e' "<<l.Front()<<", l'ultimo e' "<<l.Back()<<endl;
    bool selection = false;
    int testtype;
    while(!selection)
    {
        cout<<"0. Esci"<<endl<<"1. Funzione map: Stampa tutti gli elementi"<<endl<<
            "2. Controlla esistenza di un elemento"<<endl<<"3. Funzione fold: Concatenazione per lunghezza minore o uguale a n"<<endl<<"4. Funzione map: uppercase"<<endl;
        cin>>testtype;
        switch(testtype)
        {
        case 0:
            selection = true;
            break;
        case 1:
            l.Map(&MapPrint<string>,0);
            cout<<endl;
            break;
        case 2:
        {
            cout<<endl<<"Inserisci stringa da cercare:   ";
            string search;
            cin>>search;
            if(l.Exists(search))
                cout<<"La stringa e' presente!"<<endl;
            else
                cout<<"La stringa non e' presente!"<<endl;
            break;
        }
        case 3:
        {
            cout<<endl<<"Inserisci n:   ";
            unsigned long n;
            cin>>n;
            string result = "";
            l.Fold(&FoldConcatLessEqualN<string>,&n,&result);
            cout<<result<<endl;
            break;
        }
        case 4:
            l.Map(&MapUppercase<string>,0);
            cout<<"Fatto, prova a stampare"<<endl;
            break;
        default:
            cout<<"Errore di input"<<endl;
        }
    }
}

void vectortest()
{
    cout << endl << "Che tipo di dato vuoi usare?"<< endl<<"1. Test su Int"<<endl<<"2. Test su Double"<<endl<<"3. Test su String"<<endl;
    bool selection = false;
    int testtype = 0;
    while(!selection)
    {
        cin>>testtype;
        switch(testtype)
        {
        case 1:
            vectorinttest();
            selection = true;
            break;
        case 2:
            vectordoubletest();
            selection = true;
            break;
        case 3:
            vectorstringtest();
            selection = true;
            break;
        default:
            cout<<"Input non valido"<<endl;
        }
    }
}

void listtest()
{
    cout << endl << "Che tipo di dato vuoi usare?"<< endl<<"1. Test su Int"<<endl<<"2. Test su Double"<<endl<<"3. Test su String"<<endl;
    bool selection = false;
    int testtype = 0;
    while(!selection)
    {
        cin>>testtype;
        switch(testtype)
        {
        case 1:
            listinttest();
            selection = true;
            break;
        case 2:
            listdoubletest();
            selection = true;
            break;
        case 3:
            liststringtest();
            selection = true;
            break;
        default:
            cout<<"Input non valido"<<endl;
        }
    }
}

void stacktest()
{
    bool usevec;
    int testtype = 0;
    cout << endl << "Che implementazione usare?"<< endl  <<"1. Vettore"<< endl <<"2. Lista"<< endl;
    while(testtype != 1 && testtype != 2)
    {
        cin>>testtype;
        switch(testtype)
        {
            case 1:
                usevec = true;
                break;
            case 2:
                usevec = false;
                break;
            default:
                cout<<"Input non valido"<<endl;
        }
    }
    testtype = 0;
    cout << endl << "Che tipo di dato vuoi usare?"<< endl <<"1. Test su Int"<< endl <<"2. Test su Double"<< endl <<"3. Test su String"<< endl;
    bool selection = false;
    while(!selection)
    {
        cin>>testtype;
        switch(testtype)
        {
            case 1:

                if(usevec)
                {
                    StackVec<int> s;
                    stackinttest(s);
                }
                else
                {
                    StackLst<int> s;
                    stackinttest(s);
                }
                selection = true;
                break;
            case 2:
                if(usevec)
                {
                    StackVec<double> s;
                    stackdoubletest(s);
                }
                else
                {
                    StackLst<double> s;
                    stackdoubletest(s);
                }
                selection = true;
                break;
            case 3:
                if(usevec)
                {
                    StackVec<string> s;
                    stackstringtest(s);
                }
                else
                {
                    StackLst<string> s;
                    stackstringtest(s);
                }
                selection = true;
                break;
            default:
                cout<<"Input non valido"<<endl;

        }
    }
}

void queuetest()
{
    bool usevec;
    int testtype = 0;
    cout << endl << "Che implementazione usare?"<< endl  <<"1. Vettore"<< endl <<"2. Lista"<< endl;
    while(testtype != 1 && testtype != 2)
    {
        cin>>testtype;
        switch(testtype)
        {
            case 1:
                usevec = true;
                break;
            case 2:
                usevec = false;
                break;
            default:
                cout<<"Input non valido"<<endl;
        }
    }
    testtype = 0;
    cout << endl << "Che tipo di dato vuoi usare?"<< endl <<"1. Test su Int"<< endl <<"2. Test su Double"<< endl <<"3. Test su String"<< endl;
    bool selection = false;
    while(!selection)
    {
        cin>>testtype;
        switch(testtype)
        {
            case 1:
                if(usevec)
                {
                    QueueVec<int> q;
                    queueinttest(q);
                }

                else
                {
                    QueueLst<int> q;
                    queueinttest(q);
                }
                selection = true;
                break;
            case 2:
                if(usevec)
                {
                    QueueVec<double> q;
                    queuedoubletest(q);
                }
                else
                {
                    QueueLst<double> q;
                    queuedoubletest(q);
                }
                selection = true;
                break;
            case 3:
                if(usevec)
                {
                    QueueVec<string> q;
                    queuestringtest(q);
                }
                else
                {
                    QueueLst<string> q;
                    queuestringtest(q);
                }
                selection = true;
                break;
            default:
                cout<<"Input non valido"<<endl;
        }
    }
}

void mytest()
{
    cout << endl << "Test menu' "<< endl<<"1. Test su Liste"<<endl<<"2. Test su Vector"<<endl<<"3. Test su Stack"<<endl<<"4. Test su Queue"<<endl<<"5. Test del professore"<<endl;
    bool selection = false;
    int testtype = 0;
    while(!selection)
    {
        cin>>testtype;
        switch(testtype)
        {
        case 1:
            listtest();
            selection = true;
            break;
        case 2:
            vectortest();
            selection = true;
            break;
        case 3:
            stacktest();
            selection = true;
            break;
        case 4:
            queuetest();
            selection = true;
            break;
        case 5:
            lasdtest();
            selection = true;
            break;
        default:
            cout<<"Input non valido"<<endl;
        }
    }
}
