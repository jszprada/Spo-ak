#include<iostream>

using namespace std;

enum plec{K,M};

class Osoba{
    private:
        string imie_, nazwisko_;
        float waga_, wzrost_;
        int wiek_;
    protected:
        plec plec_;
    public:
        Osoba(){};
        Osoba(string, string, float, float, int, plec);
        void wyswietlOsoba(){ cout<<imie_<<" "<<nazwisko_<<" "<<waga_<<" "<<wzrost_<<" "<<wiek_<<" "<<plec_; };
        float getBMI(){
            return (waga_/((wzrost_/100)*(wzrost_/100))); 
        };
        int getwiek(){
            return wiek_; 
        };
        string getimie(){
            return imie_; 
        };
        string getnazwisko(){
            return nazwisko_; };
};
Osoba::Osoba(string imie,string nazwisko,float waga,float wzrost,int wiek,plec plec):
imie_(imie),nazwisko_(nazwisko),waga_(waga),wzrost_(wzrost),wiek_(wiek),plec_(plec){
}
class Student:public Osoba{
    public:
        static const int rozmiar_ = 10;
    private:
        string index_;
        int rok_,iloscocen;
        double oceny_[rozmiar_];
    public:
        Student(){ index_="";};
        Student(string, string, float, float, int, plec, string, int, double[]);
        double srednaiA();
        string getIndex(){
            return index_; 
        };
        int getrok(){ 
            return rok_; 
        };
};
Student::Student(string imie,string nazwisko,float waga,float wzrost,int wiek,plec plec,string index, int rok, double oceny[])
: Osoba(imie, nazwisko, waga, wzrost, wiek, plec), index_(index), rok_(rok){
    iloscocen = 0;
    for(int i = 0; i <rozmiar_ ; i++){
        iloscocen++;
        oceny_[i] = oceny[i];
    } 
}
double Student::srednaiA(){
    double suma = 0;
    for(int i = 0; i < iloscocen; i++){
        suma += oceny_[i];
    }
    return suma/iloscocen;
}
class Kierunek{
    public:
        static const int maxstudentow_ = 10;
        static const int lata_ = 5;
    private:
        string imie_;
        Student studentow_[maxstudentow_][lata_];
        int studentownarok_[lata_] ;
        int ilosstudentow_;
        void updateStudentow(bool);
    public:
        Kierunek(){};
        Kierunek(string, Student[maxstudentow_][lata_], int);
        void dodajstudenta(Student);
        void usunstudenta(Student);
        void operator==(int);
        void wyswietlnajstudenta(int);
};
Kierunek::Kierunek(string imie, Student studentow[maxstudentow_][lata_], int ilosstudentow=0){
    imie_ = imie;
    studentownarok_[lata_] ={0};
    for(int i = 0; i < maxstudentow_; i++){
        for(int k = 0; k < lata_; k++){
            studentow_[i][k] = studentow[i][k];
            if(studentow_[i][k].getIndex() != "")studentownarok_[k]++;
        }
    }
    ilosstudentow_ = ilosstudentow;
}
void Kierunek::dodajstudenta(Student nowyStudent){
    int rok = nowyStudent.getrok()-1;
    if(studentownarok_[rok] >= maxstudentow_) return;
    studentow_[studentownarok_[rok]++][rok];
    updateStudentow(1);
}
void Kierunek::updateStudentow(bool opcja){
    if(opcja) ilosstudentow_++;
    ilosstudentow_--;
}
void Kierunek::usunstudenta(Student student){
    int rok = student.getrok()-1;
    for(int i = 0; i < studentownarok_[rok]; i++){
        if(student.getIndex() == studentow_[i][rok].getIndex()){
            studentow_[i][rok] = studentow_[studentownarok_[rok]-1][rok];
            studentownarok_[rok]--;
            updateStudentow(0);
            return;
        }
    }
}
void Kierunek::operator==(int rok){
    rok-=1;
    for(int i = 0; i < studentownarok_[rok]; i++){
        for(int k = i+1; k < studentownarok_[rok]; k++){
            if(studentow_[i][rok].srednaiA() < studentow_[k][rok].srednaiA()) 
            swap(studentow_[i][rok], studentow_[k][rok]);
        }
    }
}
void Kierunek::wyswietlnajstudenta(int rok){
    *this==rok;
    rok-=1;
    for(int i = 0; i < 3; i++){
        cout<<studentow_[i][rok].getIndex()<<" "<<studentow_[i][rok].getimie()<<" "<<studentow_[i][rok].getnazwisko()<<" ";
    }
}
class Pracownik:public Osoba{
      private:
        string nfirmy_;
        string posada_;
        float placa_;
        float czaspracy_;
    public:
        Pracownik(){};
        Pracownik(string, string, float, float, int, plec, string, string, float, float);
        int latadoemerytury();
};  
Pracownik::Pracownik(string imie,string nazwisko,float waga,float wzrost,int wiek,plec plec, string nfirmy, string posada, float placa, float czaspracy)
: Osoba(imie, nazwisko, waga, wzrost, wiek, plec), nfirmy_(nfirmy), posada_(posada), placa_(placa), czaspracy_(czaspracy){
}
int Pracownik::latadoemerytury(){
    if(plec_ == M) return (65-getwiek());
    return 60-getwiek();
}
plec zamianaplec(char z){
    if(z=='M') return M;
    return K;
}
int main()
{
    string nkierunku;
    cin>>nkierunku;
    const int size1 = 10, size2 = 5;
    Student studentow[size1][size2];
    for(int i = 0; i < 10; i++){
        string imie, nazwisko;
        float waga, wzrost;
        int wiek;
        char plecPP;
        plec plecp;
        string index;
        int rok;
        double oceny[5];
        cin>>imie>>nazwisko>>waga>>wzrost>>wiek>>plecPP>>index>>rok;
        plecp=zamianaplec(plecPP);
        for(int i = 0; i < 5; i++) cin>>oceny[i];
        studentow[i][rok-1] = Student(imie, nazwisko, waga, wzrost, wiek, plecp, index, rok, oceny);
    }
    Kierunek kier(nkierunku, studentow);
    int rok;
    cin>>rok;
    kier.wyswietlnajstudenta(rok);
    const int pSize = 2;
    Pracownik p[pSize];
    for(int i = 0; i < pSize; i++){
        string imie, nazwisko;
        float waga, wzrost;
        int wiek;
        char plecPP;
        plec plecp;
        string nfirmy, posada;
        float placa, czaspracy;
        cin>>imie>>nazwisko>>waga>>wzrost>>wiek>>plecPP>>nfirmy>>posada>>placa>>czaspracy;
        plecp=zamianaplec(plecPP);
        p[i] = Pracownik(imie, nazwisko, waga, wzrost, wiek, plecp, nfirmy, posada, placa, czaspracy);
        cout<<p[i].latadoemerytury()<<" ";
    }
    return 0;
}