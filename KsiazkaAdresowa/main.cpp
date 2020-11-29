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

struct User {
    int idUser = 0;
    string login = "", password = "";
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
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "9. Zakoäcz program" << endl;
}

void printMainMenuLoggedUser() {
    system("cls");
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wy˜wietl wszystkich adresat¢w" << endl;
    cout << "5. Usuä adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zmien haslo" << endl;
    cout << "9. Wyloguj" << endl;
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

void assignUserFields(User &user, string field, int fieldNumber) {
    switch(fieldNumber) {
    case 0:
        user.idUser = StrToInt(field);
        break;
    case 1:
        user.login = field;
        break;
    case 2:
        user.password = field;
        break;
    default:
        break;
    }
}

User getUserFromString(string line, char separator) {
    User user;
    int lineLength = line.length();
    string temp = "";
    int separatorCount = 0;
    for(int i = 0; i<lineLength; i++) {
        if(line[i]==separator) {
            assignUserFields(user,temp,separatorCount);
            temp = "";
            separatorCount++;
        } else {
            temp += line[i];
        }
    }
    return user;
}

void validateUserLogin(vector<User> users, string login, string password, int &idUser) {
    for (vector<User>::iterator it=users.begin(),
            lastUser = users.end(); it!=lastUser; ++it) {
        if(it->login == login) {
            if (it->password == password){
                idUser = it->idUser;
                break;
            } else {
                idUser = 0;
                break;
            }
        } else {
            idUser = 0;
        }
    }
}

void printUser(User user) {
    cout << user.idUser << "|";
    cout << user.login << "|";
    cout << user.password << "|";
    cout << endl;
}

void printUsers(vector<User> users) {
    for (vector<User>::iterator it=users.begin(),
            lastUser = users.end(); it!=lastUser; ++it) {
        printUser(*it);
    }
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

// reading/writing to file contacts
void readFromFile_contacts(fstream &file, vector<Contact> &contacts) {
    string line;
    while(getline(file,line)) {
        contacts.push_back( getContactFromString(line,'|') );
    }
}

void writeToFile_contacts(fstream &file, vector<Contact> &contacts) {
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

void readFromDB_contacts(fstream &file, string path, vector<Contact> &contacts) {
    if(fileOpen(file,path,1)==0) {
        cout << "bˆ¥d otwarcia pliku" << endl;
    } else {
        readFromFile_contacts(file, contacts);

        file.close();
    }
}

void writeToDB_contacts(fstream &file, string path, vector<Contact> &contacts) {
    if(fileOpen(file,path,0)==0) {
        cout << "bˆ¥d otwarcia pliku" << endl;
    } else {
        writeToFile_contacts(file, contacts);

        file.close();
    }
}

// reading/writing to file users
void readFromFile_users(fstream &file, vector<User> &users) {
    string line;
    while(getline(file,line)) {
        users.push_back( getUserFromString(line,'|') );
    }
}

void writeToFile_users(fstream &file, vector<User> &users) {
    for (vector<User>::iterator it=users.begin(),
            lastContact = users.end(); it!=lastContact; ++it) {
        file << it->idUser << "|";
        file << it->login << "|";
        file << it->password << "|";
        file << endl;
    }
}

void readFromDB_users(fstream &file, string path, vector<User> &users) {
    if(fileOpen(file,path,1)==0) {
        cout << "bˆ¥d otwarcia pliku" << endl;
    } else {
        readFromFile_users(file, users);

        file.close();
    }
}

void writeToDB_users(fstream &file, string path, vector<User> &users) {
    if(fileOpen(file,path,0)==0) {
        cout << "bˆ¥d otwarcia pliku" << endl;
    } else {
        writeToFile_users(file, users);

        file.close();
    }
}

int main() {
    vector<Contact> contacts;
    vector<User> users;
    fstream file_contacts;
    fstream file_users;

    readFromDB_users(file_users,"test_users.txt",users);

    char mainChoice;
    do {
        printMainMenu();
        cin >> mainChoice;
        switch(mainChoice) {
        case '1': {
            int loggedUserId = 0;
            system("cls");
            if (users.empty()) {
                cout << "brak uzytkownikow w bazie, zarejestruj sie" << endl;
                Sleep(1500);
            } else {
                string login, password;
                cout << "login:";
                cin >> login;
                cout << "hasło:";
                cin >> password;
                validateUserLogin(users,login,password,loggedUserId);
            }



            if(loggedUserId) {
                readFromDB_contacts(file_contacts,"test.txt",contacts);

                char loggedUserChoice;
                do {
                    printMainMenuLoggedUser();
                    cin >> loggedUserChoice;
                    switch(loggedUserChoice) {
                    case '1': {
                        Contact contact = printContactAddForm();
                        if(contacts.empty()) {
                            contact.id = 1;
                        } else {
                            vector<Contact>::iterator lastContact = contacts.end();
                            lastContact--;
                            contact.id = lastContact->id + 1;
                        }
                        contacts.push_back(contact);
                        writeToDB_contacts(file_contacts,"test.txt",contacts);

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
                        writeToDB_contacts(file_contacts,"test.txt",contacts);
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
                        writeToDB_contacts(file_contacts,"test.txt",contacts);
                        cout << "naci˜nij dowolny klawisz, aby wr¢ci† do menu gˆ¢wnego";
                        getchar();
                    }
                    break;
                    case '7': {
                        system("cls");
                        cin.ignore();
                        string passwordOld, passwordNew, passwordNewAck;
                        cout << "edycja hasla";
                        cout << "podaj hasło: ";
                        cin >> passwordOld;
                        if(users[loggedUserId-1].password == passwordOld) {
                            cout << "podaj nowe hasło: ";
                            cin >> passwordNew;
                            cout << "powtórz nowe hasło: ";
                            cin >> passwordNewAck;
                            if (passwordNew == passwordNewAck) {
                                users[loggedUserId-1].password = passwordNew;
                                writeToDB_users(file_users,"test_users.txt",users);
                                readFromDB_users(file_users,"test_users.txt",users);
                            } else {
                                cout << "hasla nie są identyczne";
                                cin.ignore();
                                getchar();
                                break;
                            }
                        } else {
                            cout << "haslo nieprawidlowe";
                            cin.ignore();
                            getchar();
                            break;
                        }
                    }
                    break;
                    case '9':
                        break;
                    default:
                        cout << "nieprawidˆowy wyb¢r!" << endl;
                        Sleep(1500);
                        break;
                    }
                } while(loggedUserChoice != '9');
            } else {
                system("cls");
                cout << "brak użytkownika w bazie, lub błędne hasło!" << endl;
                Sleep(1500);
            } // if loggedUserID
        }
        break;
        case '2': {
            string login, password, passwordAcknowledge;
            char choiceLoginRegistration = '0';
            uint8_t loginCorrect = 0;
            uint8_t loginExist = 0;
            uint8_t passwordCorrect = 0;
            uint8_t passwordIncorrect = 0;


            do {
                system("cls");
                cin.ignore();
                cout << "Rejestracja nowego użytkonika" << endl;
                cout << "Login: ";
                cin >> login;
                loginExist = 0;
                loginCorrect = 0;
                for (vector<User>::iterator it=users.begin(),
                        lastUser = users.end(); it!=lastUser; ++it) {
                    if(it->login == login) {
                        loginExist = 1;
                    }
                }

                if(loginExist) {
                    cout << "użytkownik już istnieje!" << endl;
                    cout << "1. powtórz próbę" << endl;
                    cout << "9. wróć do menu" << endl;
                    cin >> choiceLoginRegistration;
                } else {
                    loginCorrect = 1;
                }

            } while(loginExist && choiceLoginRegistration == '1');
            if (choiceLoginRegistration == '9') break;

            do {
                passwordIncorrect = 0;
                passwordCorrect = 0;
                system("cls");
                cout << "Rejestracja nowego użytkonika" << endl;
                cout << "Login: " << login << endl;

                cout << "haslo: ";
                cin >> password;
                cout << "powtorz haslo: ";
                cin >> passwordAcknowledge;

                if(password != passwordAcknowledge) {
                    passwordIncorrect = 1;
                }
                if (passwordIncorrect) {
                    cout << "hasła są różne" << endl;
                    cout << "1. powtórz próbę" << endl;
                    cout << "9. wróć do menu" << endl;
                    cin >> choiceLoginRegistration;
                } else {
                    passwordCorrect = 1;
                }

            } while(passwordIncorrect && choiceLoginRegistration == '1');
            if (choiceLoginRegistration == '9') break;

            if(loginCorrect && passwordCorrect) {
                User user;
                if(users.empty()) {
                    user.idUser = 1;
                } else {
                    vector<User>::iterator lastUser = users.end();
                    lastUser--;
                    user.idUser = lastUser->idUser + 1;
                }
                user.login = login;
                user.password = password;
                users.push_back(user);
                writeToDB_users(file_users,"test_users.txt",users);

                readFromDB_users(file_users,"test_users.txt",users);
            }

        }
        break;
        case '9': {
            cin.ignore();
            cout << "KONIEC!" << endl;
            cout << "naci˜nij dowolny klawisz, aby wr¢ci† do menu gˆ¢wnego";
            getchar();
        }
        break;
        default:
            cout << "nieprawidˆowy wyb¢r!" << endl;
            Sleep(1500);
            break;
        } // main switch


    } while(mainChoice != '9');

    return 0;
}
