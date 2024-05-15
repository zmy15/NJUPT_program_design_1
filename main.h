void _student_login();
void student_sign_up();
void admin_login();
void student_l_s();
void update_site_info();

struct student
{
    char ID[5];         //学号
    char password[10];  //密码
    char name[10];      //姓名
};

struct admin
{
	char  name[10];		//姓名
	char  password[10];	//密码
	char  ID[5];		//工号
};

typedef struct {
    char ID[5];           // 学号
    int site_id;          // 场地类型编号，0:羽毛球场，1：网球场，2：篮球场，3:乒乓球场
    int facility_id;      // 场地编号
    int year;             // 预约年份
    int month;            // 预约月份
    int day;              // 预约日期
    int start_hour;       // 开始小时
    int end_hour;         // 结束小时
    double fee;           // 费用
} Reservation;

typedef struct student STU;
typedef struct admin ADMIN;

extern STU student_login;
extern double fee_rates[];