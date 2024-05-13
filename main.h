#include "cJSON.h"

void student_login();
void student_sign_up();
void admin_login();

cJSON* readJSONFile(const char* filename);
int writeJSONFile(const char* filename, cJSON* root);

struct student
{
	char  name[10];		//ĞÕÃû
	char  password[10];	//ÃÜÂë
	char  ID[5];		//Ñ§ºÅ
};

struct admin
{
	char  name[10];		//ĞÕÃû
	char  password[10];	//ÃÜÂë
	char  ID[5];		//¹¤ºÅ
};

typedef struct student STU;
typedef struct admin admin;