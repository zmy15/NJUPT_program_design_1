void student_login();
void student_sign_up();
void admin_login();

struct student
{
	char  name[10];		//����
	char  password[10];	//����
	char  ID[5];		//ѧ��
};

struct admin
{
	char  name[10];		//����
	char  password[10];	//����
	char  ID[5];		//����
};

typedef struct student STU;
typedef struct admin admin;