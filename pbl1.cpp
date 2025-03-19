#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;
struct Student {
    string name;
    string gender;
    string adress;
    string dob;
    string major;    
	string faculty ;
};
struct List {
    Student *student;
    int numstudent=0;
};

List inputstudent(List lists) {
    fstream f;
    string s;
    f.open("input.txt");
        if (f.is_open()) cout << "Mo file thanh cong\n";
        else cout << "Mo file that bai!\n";
    for (int i=1;;i++) {
        getline(f, lists.student[i].name);
        if (lists.student[i].name==s) break;
        getline(f, lists.student[i].gender);
        getline(f, lists.student[i].adress);
        getline(f, lists.student[i].dob);
        getline(f, lists.student[i].major);
        getline(f, lists.student[i].faculty);
        lists.numstudent+=1;
     }
     f.close();
     return lists;
}
struct indiviclass {
    string name;
    string gender;
    int codest; 
    
};
struct Classe {
    string name;
  indiviclass student[61];
    int numst;
    int d=1;
};
struct Major {
    string name;
    int numclass;
    Classe classes[5];
};
struct Faculty {
    string name;
    int codefaculty;
    int nummajor=0;
    Major major[5];
};



void inputuniversity(Faculty faculties[],int* numfaculty) {
    string s;
    fstream f;
    f.open("mau2.txt");
    if (f.is_open()) cout << "Chay file mau thanh cong\n";
    else cout << "Chay file khong thanh cong\n";
    for (int i=1;i<=5;i++) {
        getline(f,faculties[i].name);
        if (faculties[i].name==s) break;
        f >> faculties[i].codefaculty;
        getline(f,s);
        for (int j=1;;j++) {
            getline(f,faculties[i].major[j].name);
            if (faculties[i].major[j].name==s) break;
            f >> faculties[i].major[j].numclass;
            getline(f,s);
            for (int k=1;k<=faculties[i].major[j].numclass;k++) {
                getline(f,faculties[i].major[j].classes[k].name);
                f >> faculties[i].major[j].classes[k].numst;
                getline(f,s);
            }
            faculties[i].nummajor++;
        }
        *numfaculty+=1;
    }
    f.close();
}



void setColor(int textColor, int backColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = (backColor << 4) | textColor;
    SetConsoleTextAttribute(hConsole, colorAttribute);
}
string getFirstName(const string& fullName) {
    size_t lastSpace = fullName.find_last_of(" ");
    return (lastSpace != string::npos) ? fullName.substr(lastSpace + 1) : fullName;
}
void arrangeclass(indiviclass student[], int d){
	indiviclass temp;
    for (int i = d-1 ; i > 1; i--) {
        for (int j = 1; j < i ; j++) {
            if (getFirstName(student[j].name) > getFirstName(student[j+1].name)) {
                // Hoán đổi vị trí hai sinh viên
                temp.name = student[j].name;
                student[j].name = student[j + 1].name;
                student[j + 1].name = temp.name;
                temp.gender= student[j].gender;
                student[j].gender = student[j+1].gender;
                student[j+1].gender=temp.gender;
            }
        }
    }
}



void arrangestudent(Faculty faculties[], List lis){
    int a,b,c,d;
for(int i = 1; i<=lis.numstudent;i++){
    a=1; b=1; c=1;
    while(faculties[a].name!=lis.student[i].faculty) {
        a++;
    }
    while(faculties[a].major[b].name!=lis.student[i].major) {
        if (i==7) cout << b << endl;
        b++;
    }
    d=faculties[a].major[b].classes[c].d;
    while(faculties[a].major[b].classes[c].numst<d){
        c++;
        d=faculties[a].major[b].classes[c].d;
    }
    faculties[a].major[b].classes[c].student[d].name=lis.student[i].name;
    faculties[a].major[b].classes[c].student[d].gender=lis.student[i].gender;
    faculties[a].major[b].classes[c].d=d;
    faculties[a].major[b].classes[c].student[d].codest=faculties[a].codefaculty+d;
    for(int j = b; j>=1; j--){
        int k;
        if(j==b) k=c-1;
        else k= faculties[a].major[j].numclass;
        while(k>=1){
            faculties[a].major[b].classes[c].student[d].codest+=faculties[a].major[j].classes[k].numst;
        
            k--;
        }
    }
faculties[a].major[b].classes[c].d++;
}
}



void addStudent(Faculty faculties[], int numfaculty, List &lis, string name, string gender, string adress, string dob, string major, string faculty) {
    int a = 1, b = 1, c = 1;
    while (a <= numfaculty && faculties[a].name != faculty) a++;
    if (a > numfaculty) {
        cout << "get wrong faculty !\n";
        return;
    }
    
    while (b <= faculties[a].nummajor && faculties[a].major[b].name != major) b++;
    if (b > faculties[a].nummajor) {
        cout << "get wrong major !\n";
        return;
    }
    
    while (faculties[a].major[b].classes[c].numst < faculties[a].major[b].classes[c].d) c++;
    int d = faculties[a].major[b].classes[c].d;
    
    // Thêm sinh viên vào danh sách lớp
    faculties[a].major[b].classes[c].student[d].name = name;
    faculties[a].major[b].classes[c].student[d].gender = gender;
    faculties[a].major[b].classes[c].d=d;
    faculties[a].major[b].classes[c].student[d].codest = faculties[a].codefaculty + d;

    for(int j = b; j>=1; j--){
        int k;
        if(j==b) k=c-1;
        else k= faculties[a].major[j].numclass;
        while(k>=1){
            faculties[a].major[b].classes[c].student[d].codest+=faculties[a].major[b].classes[c].numst;
            k--;
        }
    }
    faculties[a].major[b].classes[c].d++;
    
    // Thêm vào danh sách tổng quát
    lis.student[lis.numstudent].name = name;
    lis.student[lis.numstudent].gender = gender;
    lis.student[lis.numstudent].adress = adress;
    lis.student[lis.numstudent].dob = dob;
    lis.student[lis.numstudent].major = major;
    lis.student[lis.numstudent].faculty = faculty;
    lis.numstudent++;
    
    // Sắp xếp lại danh sách lớp theo tên
    arrangeclass(faculties[a].major[b].classes[c].student, faculties[a].major[b].classes[c].d);
    
    
}
  
void deletestudent(int codest,Faculty fa[],int num) {
    int i=1,j=1,k=1,t=1, a=1;
    while (i<=num) {
        while (j<=fa[i].nummajor) {
            while (k<=fa[i].major[j].numclass) {
                while (t<=fa[i].major[j].classes[k].d) {
                    if (codest==fa[i].major[j].classes[k].student[t].codest) {
                    a=0;
                    break;
                    
                    }
                    t++;
                }
                if(a==0) break;
                k++;
            }
            if(a==0) break;
            j++;
        }
        if(a==0) break;
        i++;
    }
    while (t<=fa[i].major[j].classes[k].d-1) {
        fa[i].major[j].classes[k].student[t].name=fa[i].major[j].classes[k].student[t+1].name;
        fa[i].major[j].classes[k].student[t].codest=fa[i].major[j].classes[k].student[t+1].codest;
        fa[i].major[j].classes[k].student[t].gender=fa[i].major[j].classes[k].student[t+1].gender;
       
    }
    fa[i].major[j].classes[k].d--;
 }


void cach(int a, int n,char c) {
    
 
    for (int i=1;i<=n-a;i++)  {
        setColor(1,0);
        cout << c;
    }
}
 void outlist(Faculty fa[],int num) {
 
    char a=186;
    cach(0,1,201);
    cach(0,57,205);
    cach(0,1,187);
    cout << endl;
    for (int i=1;i<=num;i++) {
        setColor(1,0);
        cout<< a;
        setColor(2,0);
         cout<<"                 "<<fa[i].name;

         cach(fa[i].name.size(),40,' ');
         setColor(1,0);
         cout<<a<<endl;
         setColor(1,0);
         cout << a;

         setColor(1,0);
         cach(0,57,205);
         cout << a;
     

    cout<<endl;
        for (int j=1;j<=fa[i].nummajor;j++) {

            for (int k=1;k<=fa[i].major[j].numclass;k++) {
                for (int t=1;t<fa[i].major[j].classes[k].d;t++) {
                    setColor(1,0);
                cout << a ;
                setColor(13,0);
                cout << " " << fa[i].major[j].classes[k].student[t].name;
                cach(fa[i].major[j].classes[k].student[t].name.size(),27,' ');
                setColor(1,0);
                cout << a ;
                setColor(3,0);
                cout << " " << fa[i].major[j].classes[k].student[t].gender;
                cach(fa[i].major[j].classes[k].student[t].gender.size(),4,' ');
                setColor(1,0);
                cout << a ;
                setColor(13,0);

                cout << " " << fa[i].major[j].classes[k].student[t].codest;
                setColor(1,0);

                cout << a ;
                setColor(3,0);
               cout  << " " << fa[i].major[j].classes[k].name;
                cach(fa[i].major[j].classes[k].name.size(),10,' ');
                cout << a;
                cout << endl;
             }
            }
        }
        setColor(1,0);
         cout << a;

         setColor(1,0);
         cach(0,57,205);
         cout << a;
     

    cout<<endl;
    }
   }
    
 
   

   
void outfile(Faculty fa[],int num) {
    fstream f;
    int d = 1;
    f.open("text1.txt");
    
    f << "+===+============================+===========+==========+===========+";
   f << "\n";
   f << "|Stt";
   f << "|" << " " << "Ho ten";
  for (int h=1;h<=21;h++) f << " ";
   f << "|" << " " << "Gioi tinh ";
   f << "|" << " " << "MSSV     ";
   f << "|" << " " << "Lop";
   for (int h=1;h<=7;h++) f << " ";
   f << "|";
   f << "\n";
   f << "+===+============================+===========+==========+===========+";
   f << endl;
    for (int i=1;i<=num;i++) {
      
        f << "|                          " << fa[i].name;
        for (int h=1;h<=59-18-fa[i].name.size();h++) f << " ";
        f << "|";
        f << "\n";
        f << "+===+============================+===========+==========+===========+";
        f << "\n";
        for (int j=1;j<=fa[i].nummajor;j++) {
            for (int k=1;k<=fa[i].major[j].numclass;k++) {
                for (int t=1;t<fa[i].major[j].classes[k].d;t++) {
                    if(d<10) f<< "|" << d <<"  ";
                    else f<< "|" << d << " ";
                    d++;
                    f << "|" << " " << fa[i].major[j].classes[k].student[t].name;
                    
                for (int h=1;h<=27-fa[i].major[j].classes[k].student[t].name.size();h++) f << " ";
                    f << "|" << " " << fa[i].major[j].classes[k].student[t].gender;
                   for (int h=1;h<=10-fa[i].major[j].classes[k].student[t].gender.size();h++) f << " ";
                    f << "|" << " " << fa[i].major[j].classes[k].student[t].codest;
                    f << "|" << " " << fa[i].major[j].classes[k].name;
                    //cach(khoa[i].nganh[j].lop[k].ten.size(),10,' ');
                    for (int h=1;h<=10-fa[i].major[j].classes[k].name.size();h++) f << " ";
                    f << "|";
                    f << "\n";
                }
            }
        }
        f << "+===+============================+===========+==========+===========+";
        f << "\n";
    }
  f.close();
 }







 int main() {
   Faculty faculties[10];
    int numfaculty=0,d,a,b,c;
    inputuniversity(faculties,&numfaculty);
    List lis;
    lis.student= new struct Student[500];
    lis= inputstudent(lis);
    
    arrangestudent(faculties,lis);
for(int n = 1; n<=numfaculty; n++){
     for(int m=1; m<=faculties[n].nummajor;m++){
       for(int p = 1; p<=faculties[n].major[m].numclass;p++){

        arrangeclass(faculties[n].major[m].classes[p].student,faculties[n].major[m].classes[p].d);
       }
    }
}

int m;
cin >> m;
if (m) {
system("cls");

outlist(faculties,numfaculty);
}
setColor(6,0);
string l,na,ge,ad,date,ma,fac;
again1:
cout<<"add another student?"<<" yes/no "<<endl;
cin>>l;
cin.ignore();
if(l=="yes") {
cout<< "pls enter student's individual information"<<"-> MUST enter (name, gender, adress, dob, major, faculty)"<<endl;
    getline(cin,na);
    getline(cin,ge);
    getline(cin,ad);
    getline(cin,date);
    getline(cin,ma);

    getline(cin,fac);

    addStudent(faculties, numfaculty,lis, na, ge,ad, date,ma,fac);
    goto again1;
}

if (m) {
    system("cls");
    
    outlist(faculties,numfaculty);
    }
    string z;
    int code;
    again2:
    setColor(6,0);
    cout<<"delete another student?"<<" yes/no"<<endl;
    cin>>z;
    if(z=="yes"){
        cout<<"enter code student:"<<endl;
        cin>>code;
        deletestudent(code,faculties,numfaculty);
       
        goto again2;
    }
    if (m) {
        system("cls");
        
        outlist(faculties,numfaculty);
        }
  outfile(faculties,numfaculty);
  setColor(6,0);
  cout<<"file is ready"<<endl;
    
  

    return 0;
}

 
