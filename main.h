void _student_login();
void student_sign_up();
void admin_login();

struct student
{
    char ID[5];         //ѧ��
    char password[10];  //����
    char name[10];      //����
    int basketball;     //ԤԼ�����0ΪδԤԼ�����ִ����غ�
    int badminton;
    int tennis;
    int pingpang;
};

struct admin
{
	char  name[10];		//����
	char  password[10];	//����
	char  ID[5];		//����
};

typedef struct {
    char ID[5];           // ѧ��
    int site_id;          // �������ͱ�ţ�0:��ë�򳡣�1�����򳡣�2�����򳡣�3:ƹ����
    int facility_id;      // ���ر��
    int year;             // ԤԼ���
    int month;            // ԤԼ�·�
    int day;              // ԤԼ����
    int start_hour;       // ��ʼСʱ
    int end_hour;         // ����Сʱ
} Reservation;


typedef struct student STU;
typedef struct admin ADMIN;

extern STU student_login;