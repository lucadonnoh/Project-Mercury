#pragma once

#include <iostream>
#include <stdint.h>
#include <chrono>
#include "Queue.hpp"
#include "Hittable.hpp"
#include "setCursorPosition.hpp"

class Partita
{
    private:
        int length;
        int height;
        int punti;
        int x;
        int y;
        int input;
        int maxPunti;
        Auto a;
        Queue obsQueue;
        Queue boostQueue;
        //Coda coda;

        uint64_t t;
        uint64_t delay;

        int livello;
        int danno;

        void bordo();
        void stampaInfo();
        int getRandomX();
        int getRandomSpawn();
        void queueManager();
        void stampa();
        uint64_t time();
        void levelsManager();
        void end();
        void checkBound();

    public:
        Partita(int l, int h);
        void start();
};