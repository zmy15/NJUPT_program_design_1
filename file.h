#include "cJSON.h"
#include"main.h"

cJSON* readJSONFile(const char* filename);
int writeJSONFile(const char* filename, cJSON* root);
int parseJSONToStudents(cJSON* root, STU students[], int max_students);
void addStudentToJSON(cJSON* root, const STU* student);

void ui(char* file);
void Encrypted_input_STU(STU* student);
void Encrypted_input_ADMIN(ADMIN* admin);

char* read_file(const char* filename);
void write_file(const char* filename, const char* content);

void print_daily_schedule(cJSON* site_json, int year, int month, int day);
void update_site_status(cJSON* site_json, int site_id, int facility_id, int status);