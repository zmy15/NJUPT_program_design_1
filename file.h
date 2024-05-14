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
void display_facilities(cJSON* root, const char* facility_name);
void change_status(cJSON* root, const char* facility_name, int court_id, int new_status);
const char* status_to_string(int status);

char* read_file_order(const char* filename);
void write_file_order(const char* filename, const char* content);
void add_reservation(cJSON* root, const Reservation* reservation);
void get_current_time(int* year, int* month, int* day, int* hour);
void process_reservation(cJSON* facility_status, cJSON* student_data, Reservation* reservation);