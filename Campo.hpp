class Campo
{
    private:
        const int row = 15;
        const int col = 50;
        char campo[15][50];
        void inizializza();
        void bordi();

    public:
        void stampa();
        void inserisci(char c, int x, int y);
        void aggiorna();

        Campo();
};