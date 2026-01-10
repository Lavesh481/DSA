#include <stdio.h>
#include <string.h>
struct Student {
    char name[20];
    int roll_no;
    float marks;
};


union Data {
    char name[20];
    int a;
    float b;
};

int main(){
    struct Student s[3];
    strcpy(s[0].name,"lavesh");
    s[0].roll_no =1;
    s[0].marks=90.0;
    strcpy(s[1].name,"ram");
    s[1].roll_no=2;
    s[1].marks=95.0;
    strcpy(s[2].name,"shyam");
    s[2].roll_no=3;
    s[2].marks=98.0;
    for(int i=0 ;i<3;i++){
        printf("Student:%d\n ", i+1 );
        printf(" name :%s\n  Rollno: %d\n  😰Marks:%f\n",s[i].name,s[i].roll_no,s[i].marks);
    };
    printf("%d\n");
    union Data d;
    strcpy(d.name,"ramu");
    printf("%s\n",d.name);
    d.a=1;
    printf("%d\n",d.a);
    d.b=9.2;
    printf("%.6f\n",d.b);
    printf("%s\n",d.name);


     return 0;

}
