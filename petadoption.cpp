#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Pet;

// Abstract class
class AnimalShelter {
private:
    double Capacity;
    string KindsOfAnimals;
    int Workers;
    Pet* pets[100]; // Array to store up to 100 pets
    int petCount;

public:
    AnimalShelter(double cap, string kinds, int w) : Capacity(cap), KindsOfAnimals(kinds), Workers(w), petCount(0) {}

    // Function overloading by reference
    void addPet(Pet* pet);
    void addPet(Pet& pet);

    void displayShelterInfo() const {
        cout << "-> Information about the shelter:" << endl;
        cout << "Shelter Capacity: " << Capacity << endl;
        cout << "Kinds of Animals: " << KindsOfAnimals << endl;
        cout << "Number of Staff: " << Workers << endl;
        cout << "Number of Pets Available: " << petCount << endl;
    }

    void displayAllPets() const;

    void removePet(int index);

    string getShelterName() const {
        return KindsOfAnimals;
    }

    Pet* getPet(int index) const {
        if (index < 0 || index >= petCount) {
            cout << "Invalid pet index." << endl;
            return NULL;
        }
        return pets[index];
    }

    int getPetCount() const {
        return petCount;
    }
};

class AdoptionApplication {
private:
    AdoptionApplication() {}
    ~AdoptionApplication() {
        cout << "The Application has been destroyed" << endl;
    }
    friend class AdoptionManager;
};

class AdoptionManager {
private:
    AdoptionApplication app;
public:
    void processApplication() {
        cout << "Processing adoption application..." << endl;
    }
};

class Pet {
public:
    string name;
    int age;
    string species;
    AnimalShelter* shelter; // Pointer to AnimalShelter

    Pet(string name, int age, string species, AnimalShelter* shelter) : name(name), age(age), species(species), shelter(shelter) {}
    
    // Default constructor
    Pet() : name(""), age(0), species(""), shelter(NULL) {}

    // Copy constructor
    Pet(const Pet& other) : name(other.name), age(other.age), species(other.species), shelter(other.shelter) {}

    virtual void displayInfo() const {
        cout << "Name: " << name << ", Age: " << age << ", Species: " << species << endl;
        if (shelter) {
            cout << "Shelter: " << shelter->getShelterName() << endl;
        }
    }
    virtual ~Pet(){}
};

class Dog : public Pet {
    string breed;
public:
    Dog(string n, int a, string sp, string b, AnimalShelter* shelter) : Pet(n, a, sp, shelter), breed(b) {}
    void displayInfo() const {
        cout << "Dog: " << name << ", Age: " << age << ", Species: " << species << ", Breed: " << breed << endl;
        if (shelter) {
            cout << "Shelter: " << shelter->getShelterName() << endl;
        }
    }
};

class Cat : public Pet {
    string color;
public:
    Cat(string n, int a, string sp, string color, AnimalShelter* shelter) : Pet(n, a, sp, shelter), color(color) {}
    void displayInfo() const {
        cout << "Cat: " << name << ", Age: " << age << ", Species: " << species << ", Color: " << color << endl;
        if (shelter) {
            cout << "Shelter: " << shelter->getShelterName() << endl;
        }
    }
};

// Example of multi-level inheritance
class Person {
private:
    string name;
    int age;
public:
    Person(string name, int age) : name(name), age(age) {}
    virtual ~Person() {}

    virtual void displayInfo() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    string getName() const {
        return name;
    }
};

class Staff : public Person {
protected:
    int staffId;
    string gender;
public:
    Staff(string name, int age, int id, string g) : Person(name, age), staffId(id), gender(g) {}
};

class VolunteerStaff : public Staff {
private:
    float WorkHours;
public:
    VolunteerStaff(string name, int age, int id, string g, float hours) : Staff(name, age, id, g), WorkHours(hours) {}
    void displayInfo() const {
        Person::displayInfo();
        cout << "Volunteer Staff ID: " << staffId << ", Gender: " << gender << ", Work Hours: " << WorkHours << endl;
    }
};

class PermanentStaff : public Staff {
private:
    string AreaOfWork;
public:
    PermanentStaff(string name, int age, int id, string g, string area) : Staff(name, age, id, g), AreaOfWork(area) {}
    void displayInfo() const {
        Person::displayInfo();
        cout << "Permanent Staff ID: " << staffId << ", Gender: " << gender << ", Area of Work: " << AreaOfWork << endl;
    }
};

class Adopter : public Person {
private:
    string Address;
    double ContactNum;
    bool hasAdoptedPet;
public:
    Adopter(string name, int age, string ad, double cn) : Person(name, age), Address(ad), ContactNum(cn), hasAdoptedPet(false) {}
    
    void setHasAdoptedPet(bool adopted) {
        hasAdoptedPet = adopted;
    }

    bool getHasAdoptedPet() const {
        return hasAdoptedPet;
    }

    void displayInfo() const {
        Person::displayInfo();
        cout << "Address: " << Address << ", Contact Number: " << ContactNum << endl;
    }
};

// Implementing methods of AnimalShelter that use Pet class
void AnimalShelter::addPet(Pet* pet) {
    if (petCount < 100) {
        pets[petCount++] = pet;
    } else {
        cout << "Shelter is full! Cannot add more pets." << endl;
    }
}

void AnimalShelter::addPet(Pet& pet) {
    addPet(&pet);
}

void AnimalShelter::displayAllPets() const {
    for (int i = 0; i < petCount; i++) {
        pets[i]->displayInfo();
    }
}

void AnimalShelter::removePet(int index) {
    if (index < 0 || index >= petCount) {
        cout << "Invalid pet index." << endl;
        return;
    }
    for (int i = index; i < petCount - 1; i++) {
           pets[i] = pets[i + 1];
    }
    petCount--;
}

// Example of operator overloading
ostream& operator<<(ostream& os, const AnimalShelter& shelter) {
    shelter.displayShelterInfo();
    return os;
}

// Function declarations for menus
void displayMenu();
void displayShelterManagementMenu(AnimalShelter& shelter);
void displayAdoptionManagementMenu(AnimalShelter& shelter, vector<Adopter>& adopters, vector<Pet*>& adoptedPets);
void displayStaffManagementMenu();
void displayAdopterManagementMenu(vector<Adopter>& adopters, vector<Adopter>& adoptersWhoAdopted);
void displayReportsAndAnalyticsMenu();

void displayMenu() {
    cout << "\n************************" << endl;
    cout << "           MENU           " << endl;
    cout << "**************************" << endl;
    cout << "1. Shelter Management" << endl;
    cout << "2. Adoption Process" << endl;
    cout << "3. Adopter Management" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to verify staff PIN
bool verifyPIN() {
    string PIN = "1234"; // PIN code for staff
    string pin;
    cout << "Enter PIN code to access the management system: ";
    cin >> pin;
    return pin == PIN;
}

void displayShelterManagementMenu(AnimalShelter& shelter) {
    if (!verifyPIN()) {
        cout << "Incorrect PIN. Access denied." << endl;
        return;
    }
    int option;

    cout << "\n************************" << endl;
    cout << "     SHELTER MANAGEMENT   " << endl;
    cout << "**************************" << endl;
    cout << "1. Display Shelter Information" << endl;
    cout << "2. Add New Pet" << endl;
    cout << "3. Display All Pets" << endl;
    cout << "4. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> option;

    switch (option) {
        case 1:
            shelter.displayShelterInfo();
            break;
        case 2: {
            string name, species, breed_or_color;
            int age;
            cout << "Enter Pet Details:" << endl;
            cout << "Name: ";
            cin >> name;
            cout << "Age: ";
            cin >> age;
            cout << "Species (Dog/Cat): ";
            cin >> species;
            cout << "Breed/Color: ";
            cin >> breed_or_color;
            if (species == "Dog" || species == "DOG" || species == "dog") {
                Dog* dog = new Dog(name, age, species, breed_or_color, &shelter);
                shelter.addPet(dog);
            } else if (species == "Cat" || species == "cat" || species == "CAT") {
                Cat* cat = new Cat(name, age, species, breed_or_color, &shelter);
                shelter.addPet(cat);
            } else {
                cout << "Invalid species. Only 'Dog' or 'Cat' allowed." << endl;
            }
            break;
        }
        case 3:
            shelter.displayAllPets();
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice. Try again." << endl;
    }
}

void displayAdoptionManagementMenu(AnimalShelter& shelter, vector<Adopter>& adopters, vector<Pet*>& adoptedPets) {
    int option;
    cout << "\n*********************" << endl;
    cout << "    ADOPTION PROCESS   " << endl;
    cout << "************************" << endl;
    cout << "1. View All Pets for Adoption" << endl;
    cout << "2. View All Adopted Pets" << endl;
    cout << "3. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> option;

    AdoptionManager manager;
    switch (option) {
        case 1:
            shelter.displayAllPets();
            cout << "1. Adopt a Pet" << endl;
            cout << "2. Back to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> option;
            if (option == 1) {
                // Adopt a Pet
                string adopterName, adopterAddress;
                double adopterContactNum;
                int petIndex;

                cout << "Enter your full name: ";
                cin.ignore();
                getline(cin, adopterName);
                cout << "Enter your address: ";
                getline(cin, adopterAddress);
                cout << "Enter your phone number: ";
                cin >> adopterContactNum;

                cout << "Select a pet by index to adopt:" << endl;
                for (int i = 0; i < shelter.getPetCount(); ++i) {
                    cout << i + 1 << ". ";
                    shelter.getPet(i)->displayInfo();
                }
                cout << "Enter the index of the pet you want to adopt: ";
                cin >> petIndex;
                if (petIndex >= 1 && petIndex <= shelter.getPetCount()) {
                    Pet* petToAdopt = shelter.getPet(petIndex - 1);
                    cout << "You have chosen to adopt: ";
                    petToAdopt->displayInfo();
                    cout << "Confirm adoption (yes/no): ";
                    string confirm;
                    cin >> confirm;
                    if (confirm == "yes"||confirm == "YES"||confirm == "Yes") {
                        // Process adoption
                        manager.processApplication();
                        cout << "Congratulations! Pet adopted successfully." << endl;
                        adoptedPets.push_back(petToAdopt);
                        shelter.removePet(petIndex - 1);
                    } else {
                        cout << "Adoption canceled." << endl;
                    }
                } else {
                    cout << "Invalid pet index." << endl;
                }
            }
            break;
        case 2:
            if (adoptedPets.empty()) {
                cout << "No pets adopted." << endl;
            } else {
                cout << "List of Adopted Pets:" << endl;
                for (vector<Pet*>::const_iterator it = adoptedPets.begin(); it != adoptedPets.end(); ++it) {
                    (*it)->displayInfo();
                }
            }
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice. Try again." << endl;
    }
}

void displayAdopterManagementMenu(vector<Adopter>& adopters, vector<Adopter>& adoptersWhoAdopted) {
    if (!verifyPIN()) {
        cout << "Incorrect PIN. Access denied." << endl;
        return;
    }
    int option;
    cout << "\n************************" << endl;
    cout << "     ADOPTER MANAGEMENT   " << endl;
    cout << "**************************"<< endl;
    cout << "1. Display Added Adopters" << endl;
    cout << "2. Add Adopter" << endl; // Added option to add adopter
    cout << "3. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> option;

    switch (option) {
        case 1:
            cout << "Displaying all adopters:" << endl;
            for (vector<Adopter>::const_iterator it = adopters.begin(); it != adopters.end(); ++it) {
                it->displayInfo();
            }
            break;
        case 2: { // Adding adopter
            string name, address;
            double contactNum;
            int age;
            cout << "Enter adopter details:" << endl;
            cout << "Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Age: ";
            cin >> age;
            cout << "Address: ";
            cin.ignore();
            getline(cin, address);
            cout << "Contact Number: ";
            cin >> contactNum;
            adopters.push_back(Adopter(name, age, address, contactNum));
            cout << "Adopter added successfully." << endl;
            break;
        }
       
            break;
        case 3:
            return;
        default:
            cout << "Invalid option. Please try again." << endl;
    }
}

int main() {
    AnimalShelter shelter(50, "Dogs and Cats", 10);
    vector<Adopter> adopters;
    vector<Adopter> adoptersWhoAdopted; 
    vector<Pet*> adoptedPets;
    
    cout << "===============================================================================================================" << endl;
    cout << "===============================================================================================================" << endl << endl;
    cout << "                                                  ANIMAL SHELTER" << endl << endl;
    cout << "===============================================================================================================" << endl;
    cout << "===============================================================================================================" << endl;
    Dog dog1("Buddy", 3, "Dog", "Labrador", &shelter);
    Dog dog2("Max", 5, "Dog", "Beagle", &shelter);
    Dog dog3("Rocky", 2, "Dog", "Poodle", &shelter);
    Cat cat1("Luna", 4, "Cat", "Siamese", &shelter);
    Cat cat2("Bella", 3, "Cat", "Persian", &shelter);

    shelter.addPet(&dog1);
    shelter.addPet(&dog2);
    shelter.addPet(&dog3);
    shelter.addPet(&cat1);
    shelter.addPet(&cat2);

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                displayShelterManagementMenu(shelter);
                break;
            case 2:
                displayAdoptionManagementMenu(shelter, adopters, adoptedPets);
                break;
            case 3:
                displayAdopterManagementMenu(adopters, adoptersWhoAdopted);
                break;
            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
