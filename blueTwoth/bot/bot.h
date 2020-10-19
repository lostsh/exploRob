typedef struct {
  int yPot;
  int xPot;
  byte btn;
} Data;

void moove(int, int);
void readData(Data* dta, unsigned long *tNow, unsigned long *tLast);
void resetData(Data *dta);
