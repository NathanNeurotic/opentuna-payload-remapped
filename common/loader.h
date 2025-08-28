#ifndef LOADER_H
#define LOADER_H

void wipeUserMem(void);
void ResetIOP(void);
void InitPS2(void);
void LoadElf(char *filename, char *party);
int file_exists(char filepath[]);

#endif /* LOADER_H */
