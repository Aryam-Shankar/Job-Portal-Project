// Cleaned-up and improved version of the Job Portal System
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string Cun, Cpw, Aun, Apw; // Global login info

class Company {
    string name, about;
public:
    bool login();
    void reg();
    void updateInfo();
    void viewInfo();
};

class Applicant {
    string name, phoneNum, resume;
public:
    bool login();
    void reg();
    void updateInfo();
    void viewInfo();
};

class Vacancy : public Company, public Applicant {
    string vacancyDetails;
    int vacancyCount = 0;
public:
    void readVacancyCount();
    void writeVacancyCount();
    void postVacancy();
    void viewVacancy();
};

bool Company::login() {
    string username, password;
    cout << "Enter Username: "; cin >> Cun;
    cout << "Enter Password: "; cin >> Cpw;

    ifstream read("company/" + Cun + ".txt");
    if (!read.is_open()) {
        cout << "\nLogin failed: account not found.\n";
        return false;
    }
    getline(read, username);
    getline(read, password);

    if (username == Cun && password == Cpw) {
        cout << "\nCompany Login Successful :)\n";
        return true;
    }
    cout << "\nCompany Login Failed :((\n";
    return false;
}

void Company::reg() {
    cout << "Pick Username: "; cin >> Cun;
    cout << "Pick Password: "; cin >> Cpw;

    ofstream file("company/" + Cun + ".txt");
    file << Cun << "\n" << Cpw;
    file.close();
    cout << "\nCompany Registered Successfully :)\n";
}

void Company::updateInfo() {
    cout << "Enter Company Name: ";
    getline(cin >> ws, name);
    cout << "Enter About Company: ";
    getline(cin >> ws, about);

    ofstream nameFile("Cname/" + Cun + ".txt");
    nameFile << name;
    nameFile.close();

    ofstream infoFile("Cinfo/" + Cun + ".txt");
    infoFile << "Name: " << name << "\nAbout: " << about;
    infoFile.close();
}

void Company::viewInfo() {
    ifstream file("Cinfo/" + Cun + ".txt");
    if (!file.is_open()) {
        cout << "No company info available.\n";
        return;
    }
    string line;
    while (getline(file, line)) cout << line << "\n";
    file.close();
}

bool Applicant::login() {
    string username, password;
    cout << "Enter Username: "; cin >> Aun;
    cout << "Enter Password: "; cin >> Apw;

    ifstream read("applicant/" + Aun + ".txt");
    if (!read.is_open()) {
        cout << "\nLogin failed: account not found.\n";
        return false;
    }
    getline(read, username);
    getline(read, password);

    if (username == Aun && password == Apw) {
        cout << "\nApplicant Login Successful :)\n";
        return true;
    }
    cout << "\nApplicant Login Failed :((\n";
    return false;
}

void Applicant::reg() {
    cout << "Pick Username: "; cin >> Aun;
    cout << "Pick Password: "; cin >> Apw;

    ofstream file("applicant/" + Aun + ".txt");
    file << Aun << "\n" << Apw;
    file.close();
    cout << "\nApplicant Registered Successfully :)\n";
}

void Applicant::updateInfo() {
    cout << "Enter Full Name: ";
    getline(cin >> ws, name);
    cout << "Enter Phone Number: "; cin >> phoneNum;
    cout << "Enter Resume Link: ";
    getline(cin >> ws, resume);

    ofstream file("Ainfo/" + Aun + ".txt");
    file << "Name: " << name << "\nPhone: " << phoneNum << "\nResume: " << resume;
    file.close();
}

void Applicant::viewInfo() {
    ifstream file("Ainfo/" + Aun + ".txt");
    if (!file.is_open()) {
        cout << "No applicant info available.\n";
        return;
    }
    string line;
    while (getline(file, line)) cout << line << "\n";
    file.close();
}

void Vacancy::readVacancyCount() {
    ifstream file("Vac_Count.txt");
    if (file.is_open()) file >> vacancyCount;
    file.close();
}

void Vacancy::writeVacancyCount() {
    ofstream file("Vac_Count.txt");
    file << vacancyCount;
    file.close();
}

void Vacancy::postVacancy() {
    readVacancyCount();
    vacancyCount++;
    writeVacancyCount();

    cout << "Enter Job Vacancy Details: ";
    getline(cin >> ws, vacancyDetails);

    ifstream cnameFile("Cname/" + Cun + ".txt");
    string cname; getline(cnameFile, cname); cnameFile.close();

    ofstream file("Vacancy.txt", ios::app);
    file << vacancyCount << ". " << cname << " >> " << vacancyDetails << "\n";
    file.close();
    cout << "Vacancy Posted Successfully!\n";
}

void Vacancy::viewVacancy() {
    ifstream file("Vacancy.txt");
    if (!file.is_open()) {
        cout << "No vacancies available yet.\n";
        return;
    }
    char ch;
    while (file.get(ch)) cout << ch;
    file.close();
}

void applicantMenu() {
    Vacancy v;
    Applicant a;
    while (true) {
        int choice;
        cout << "\n\n--- APPLICANT MENU ---\n";
        cout << "1. View Vacancies\n2. View Info\n3. Update Info\n4. Logout\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: v.viewVacancy(); break;
            case 2: a.viewInfo(); break;
            case 3: a.updateInfo(); break;
            case 4: return;
            default: cout << "Invalid option.\n";
        }
    }
}

void companyMenu() {
    Vacancy v;
    Company c;
    while (true) {
        int choice;
        cout << "\n\n--- COMPANY MENU ---\n";
        cout << "1. Post Vacancy\n2. View Info\n3. Update Info\n4. Logout\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: v.postVacancy(); break;
            case 2: c.viewInfo(); break;
            case 3: c.updateInfo(); break;
            case 4: return;
            default: cout << "Invalid option.\n";
        }
    }
}

int main() {
    while (true) {
        cout << "\n\n====== JOB PORTAL SYSTEM ======\n";
        cout << "1. Applicant Login\n2. Applicant Register\n3. Company Login\n4. Company Register\n5. Exit\nChoice: ";

        int option;
        cin >> option;

        Applicant a;
        Company c;

        switch (option) {
            case 1:
                if (a.login()) applicantMenu();
                break;
            case 2:
                a.reg();
                break;
            case 3:
                if (c.login()) companyMenu();
                break;
            case 4:
                c.reg();
                break;
            case 5:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
    return 0;
}
