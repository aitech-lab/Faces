unsigned char *ReadPGM(const char *name, int &w, int &h, bool adjustToEightMultiple);
bool WritePGM(const char *name, int w, int h, unsigned char *data);

int GetMagicNumber(int n);

