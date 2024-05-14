void student_login();
void student_sign_up();
void admin_login();

struct student
{
    char ID[5];         //学号
    char password[10];  //密码
    char name[10];      //姓名
    int basketball;     //预约情况，0为未预约，数字代表场地号
    int badminton;
    int pingpang;
};

struct admin
{
	char  name[10];		//姓名
	char  password[10];	//密码
	char  ID[5];		//工号
};

typedef struct student STU;
typedef struct admin ADMIN;