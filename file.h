#include "cJSON.h"

cJSON* readJSONFile(const char* filename);
int writeJSONFile(const char* filename, cJSON* root);
void ui(char* file);
void Encrypted_input(STU* student);