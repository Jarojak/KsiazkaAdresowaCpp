#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Contact {
    int id = 0, idUser = 0;
    string name = "", surname = "", phoneNumber = "", email = "", address = "";
};

string IntToStr(int intNumber) {
    ostringstream ss;
    ss << intNumber;
    string stringNumber = ss.str();
    return stringNumber;
}

int StrToInt(string stringNumber) {
    int intNumber;
    istringstream iss(stringNumber);
    iss >> intNumber;
    return intNumber;
}

void printMainMenu() {
    system("cls");
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wy˜wietl wszystkich adresat¢w" << endl;
    cout << "5. Usuä adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "9. Zakoäcz program" << endl;
}

Contact printContactAddForm() {
    Contact contact;
    system("cls");
    cout << "dodawanie kontaktu" << endl;
    cin.ignore();
    cout << "podaj imi©: ";
    getline(cin,contact.name);
    cout << "podaj nazwisko: ";
    getline(cin,contact.surname);
    cout << "podaj numer telefonu: ";
    getline(cin,contact.phoneNumber);
    cout << "podaj adres email: ";
    getline(cin,contact.email);
    cout << "podaj adres zamieszkania: ";
    getline(cin,contact.address);
    return contact;
}

void assignContactFields(Contact &contact, string field, int fieldNumber) {
    switch(fieldNumber) {
    case 0:
        contact.id = StrToInt(field);
        break;
    case 1:
        contact.name = field;
        break;
    case 2:
        contact.surname = field;
        break;
    case 3:
        contact.phoneNumber = field;
        break;
    case 4:
        contact.email = field;
        break;
    case 5:
        contact.address = field;
        break;
    default:
        break;
    }
}

Contact getContactFromString(string line, char separator) {
    Contact contact;
    int lineLength = line.length();
    string temp = "";
    int separatorCount = 0;
    for(int i = 0; i<lineLength; i++) {
        if(line[i]==separator) {
            assignContactFields(contact,temp,separatorCount);
            temp = "";
            separatorCount++;
        } else {
            temp += line[i];
        }
    }
    return contact;
}

void printContact(Contact contact) {
    cout << contact.id << "|";
    cout << contact.name << "|";
    cout << contact.surname << "|";
    cout << contact.phoneNumber << "|";
    cout << contact.email << "|";
    cout << contact.address << "|";
    cout << endl;
}

void printContacts(vector<Contact> contacts) {
    for (vector<Contact>::iterator it=contacts.begin(),
            lastContact = contacts.end(); it!=lastContact; ++it) {
        printContact(*it);
    }
}

void findContactsByName(vector<Contact> contacts, string name) {
    for (vector<Contact>::iterator it=contacts.begin(),
            lastContact = contacts.end(); it!=lastContact; ++it) {
        if(it->name == name) {
            printContact(*it);
        }
    }
}

void findContactsBySurname(vector<Contact> contacts, string surname) {
    for (vector<Contact>::iterator it=contacts.begin(),
            lastContact = contacts.end(); it!=lastContact; ++it) {
        if(it->surname == surname) {
            printContact(*it);
        }
    }
}

void deleteContactById(vector<Contact> &contacts, int id) {
    for (vector<Contact>::iterator it=contacts.begin(),
            lastContact = contacts.end(); it!=lastContact; ++it) {
        if(it->id == id) {
            cout << "usun¥† kontakt t/n?" << endl;
            printContact(*it);
            cin.ignore();
            if(getchar()=='t'){
                contacts.erase(it);
            }
        }
    }
}

void editContactById(vector<Contact> &contacts, int id) {
    for (vector<Contact>::iterator it=contacts.begin(),
            lastContact = contacts.end(); it!=lastContact; ++it) {
        if(it->id == id) {
            cout << "kontakt do edycji: " << endl;
            printContact(*it);
            cout << "wybierz dane do edycji:" << endl;
            cout << "1. imi©" << endl;
            cout << "2. nazwisko" << endl;
            cout << "3. numer telefonu" << endl;
            cout << "4. email" << endl;
            cout << "5. adres" << endl;
            cout << "6. powr¢t do menu" << endl;
            char choice;
            cin >> choice;
            cin.ignore();
            switch(choice){
            case '1':
                getline(cin,it->name);
                break;
            case '2':
                getline(cin,it->surname);
                break;
            case '3':
                getline(cin,it->phoneNumber);
                break;
            case '4':
                getline(cin,it->email);
                break;
            case '5':
                getline(cin,it->address);
                break;
            case '6':
                break;
            default:
                cout << "niewˆa˜ciwy wyb¢r" << endl;
                Sleep(1500);
                break;
            }
        }
    }
}

void readFromFile(fstream &file, vector<Contact> &contacts) {
    string line;
    while(getline(file,line)) {
        contacts.push_back( getContactFromString(line,'|') );
    }
}

void writeToFile(fstream &file, vector<Contact> &contacts) {
    for (vector<Contact>::iterator it=contacts.begin(),
            lastContact = contacts.end(); it!=lastContact; ++it) {
        file << it->id << "|";
        file << it->name << "|";
        file << it->surname << "|";
        file << it->phoneNumber << "|";
        file << it->email << "|";
        file << it->address << "|";
        file << endl;
    }
}

int fileOpen(fstream &file, string path, int mode) {
    if(mode == 1) {
        file.open(path,ios::in);
    } else if(mode == 0) {
        file.open(path,ios::out);
    } else if(mode == 2) {
        file.open(path,ios::out|ios::app);
    }

    if(file.good()==false) {
        return 0;
    } else {
        return 1;
    }
}

void readFromDB(fstream &file, string path, vector<Contact> &contacts) {
    if(fileOpen(file,path,1)==0) {
        cout << "bˆ¥d otwarcia pliku" << endl;
    } else {
        readFromFile(file, contacts);

        file.close();
    }
}

void writeToDB(fstream &file, string path, vector<Contact> &contacts) {
    if(fileOpen(file,path,0)==0) {
        cout << "bˆ¥d otwarcia pliku" << endl;
    } else {
        writeToFile(file, contacts);

        file.close();
    }
}

int main() {
    vector<Contact> contacts;
    fstream file;

    readFromDB(file,"test.txt",contacts);

    char choice;
    do {
        printMainMenu();
        cin >> choice;
        switch(choice) {
        case '1': {
            Contact contact = printContactAddForm();
            if(contacts.empty()){
                contact.id = 1;
            } else {
                vector<Contact>::iterator lastContact = contacts.end();
                lastContact--;
                contact.id = lastContact->id + 1;
            }
            contacts.push_back(contact);
            writeToDB(file,"test.txt",contacts);

        }
        break;
        case '2': {
            system("cls");
            string name;
            cout << "wyszukaj kontakt po imieniu: ";
            cin.ignore();
            getline(cin,name);
            findContactsByName(contacts,name);
            cout << "naci˜nij dowolny klawisz, aby wr¢ci† do menu gˆ¢wnego";
            getchar();
        }
            break;
        case '3': {
            system("cls");
            string surname;
            cout << "wyszukaj kontakt po nazwisku: ";
            cin.ignore();
            getline(cin,surname);
            findContactsBySurname(contacts,surname);
            cout << "naci˜nij dowolny klawisz, aby wr¢ci† do menu gˆ¢wnego";
            getchar();
        }
            break;
        case '4':
            system("cls");
            printContacts(contacts);
            cin.ignore();
            cout << "naci˜nij dowolny klawisz, aby wr¢ci† do menu gˆ¢wnego";
            getchar();
            break;
        case '5': {
            system("cls");
            int id;
            cout << "usuwanie kontatku, podaj ID: ";
            cin.ignore();
            cin >> id;
            deleteContactById(contacts,id);
            writeToDB(file,"test.txt",contacts);
            cout << "naci˜nij dowolny klawisz, aby wr¢ci† do menu gˆ¢wnego";
            getchar();
        }
            break;
        case '6': {
            system("cls");
            int id;
            cout << "edycja kontaktu, podaj ID: ";
            cin.ignore();
            cin >> id;
            cin.ignore();
            editContactById(contacts,id);
            writeToDB(file,"test.txt",contacts);
            cout << "naci˜nij dowolny klawisz, aby wr¢ci† do menu gˆ¢wnego";
            getchar();
        }
            break;
        case '9':
            break;
        default:
            cout << "nieprawidˆowy wyb¢r!" << endl;
            Sleep(1500);
            break;
        }
    } while(choice != '9');

    return 0;
}
