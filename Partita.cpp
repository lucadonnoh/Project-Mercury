#include "windows.h"
#include "Partita.hpp"


using namespace std;

uint64_t Partita::time()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Partita::bordo()
{
    for(int i = 0; i<length; i++)
    {
        setCursorPosition(i, height, 247);
        cout << "-";
    }
    for(int i = 0; i<=height; i++)
    {
        setCursorPosition(length, i, 247);
        cout << "|";
        setCursorPosition(0, i, 247);
        cout << "|";
    }
}

Partita::Partita(int l, int h)
{
    length = l; //lunghezza campo
    height = h; //altezza campo

    //pos iniziale auto
    x = length/2; 
    y = height-1;

    a = Auto(x, y);

    //creazione coda di ostacoli e di boost
    obsQueue = Queue();
    boostQueue = Queue();

    input = 0;

    //temporizzazione ticks
    t = time();
    delay = 200;

    //inizializzazione punteggio
    punti = 0;
    livello = 0;

    //stampa bordo
    bordo();
}

void Partita::processInput(int c)
{
    switch(c)   // Gli spostamenti sono limitati all'asse X
    {
        case 77:
            if (x>=length)
                x=length;
            else
                x++;
            break;

        case 75:
            if (x<=0)
                x=0;
            else
                x--;
            break;

        case 27:
            livello = 0;
            break;
    }
}

void Partita::stampaInfo()
{
    int l = 70;

    setCursorPosition(l,0,95);
	cout << "dimensione coda: " << obsQueue.getDim() << " ";

    setCursorPosition(l, 1,95);
    cout << "dimensione lista: " << boostQueue.getDim() << " ";

    if(obsQueue.checkCollision(a.getX(), a.getY()) || boostQueue.checkCollision(a.getX(), a.getY()))
    {
        setCursorPosition(l,2,95);
        cout << "collisione:  true";
    }
    else
    {
        setCursorPosition(l,2,95);
        cout << "collisione: false";
    }

    setCursorPosition(l,3,95);
    cout << "punteggio: " << punti << " ";

    setCursorPosition(l,4,95);
    cout << "livello: " << livello << " ";

    if(!obsQueue.isEmpty())
    {
        setCursorPosition(l,5,95);
        cout << "danno: " << obsQueue.getTesta().getPoints() << " ";
    }


    setCursorPosition(l,6,95);
    cout << "delay: " << delay << " ";
}

int Partita::getRandomX()
{
	int r = rand() % (length - 1) + 1;
	return r;
}

int Partita::getRandomSpawn()
{
    int level;
    level = livello;

    if (level >= 10)
        level = 10;

    int r = rand()% (13 - level) + 1;
    return r;
}

void Partita::stampa()
{
    setCursorPosition(0, 0, 0); //toglie i flickering
    obsQueue.print();
    boostQueue.print();
    a.stampa();
}

void Partita::levelsManager()
{
    livello = punti/100;
    int maxDelay = 200;
    if(maxDelay-livello*10 >= 0)
    {
        delay = maxDelay-livello*10;
    }

    danno = livello*20+20;
}

void Partita::queueManager()
{
    if (getRandomSpawn() == 1)
    {
        //creazione boost
        Hittable b(getRandomX(), 15, false);
        boostQueue.enQ(b);
    }
    //////////////////////////////////
    boostQueue.move();
    boostQueue.checkLimit(height);

    //creazione ostacolo
    Hittable o(getRandomX(), danno, true);
    obsQueue.enQ(o);
    obsQueue.move();
    obsQueue.checkLimit(height);

    setCursorPosition(70, 20, 0);
    if (boostQueue.checkCollision(a.getX(), a.getY()))
    {
        punti += boostQueue.getTesta().getPoints();
    }
    if (obsQueue.checkCollision(a.getX(), a.getY()))
    {
        punti -= obsQueue.getTesta().getPoints();
    }
}

void Partita::end()
{
    cls();
    setCursorPosition(length-10, height/2, 16);
    cout << "perso sfigato gay";
    // setCursorPosition(length-3, (height/2) + 1, 16);
    // cout << maxspawn;
    Sleep(3000);
}

void Partita::checkBound()
{
    if (a.getX() == 0 || a.getX() == (length))
        punti -= 2;
}

void Partita::start()
{

    //TODO: vedere cosa farci
    Hittable b(getRandomX(), 15, false);
    boostQueue.enQ(b);

    while (1)
	{
		int newInput = getInput();
		if (newInput != 0)
		{
			input = newInput;
		}

		stampa();

		processInput(input);
		input = 0;

		a.setPos(x,y);

        if(time() - t > delay)
        {
            bordo();
            t = time();
            punti += 1;
            checkBound();
            levelsManager();
            queueManager();
        }

        if(punti < 0) break;
        stampaInfo();
    }
    end();
}