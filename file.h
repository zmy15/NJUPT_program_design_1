#include "cJSON.h"

cJSON* readJSONFile(const char* filename);
int writeJSONFile(const char* filename, cJSON* root);
int parseJSONToStudents(cJSON* root, STU students[], int max_students);
void addStudentToJSON(cJSON* root, const STU* student);
void ui(char* file);
void Encrypted_input(STU* student);