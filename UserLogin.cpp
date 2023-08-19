#include <iostream>
#include <limits>
#include <fstream>
#include "functions.h"
using namespace std;

int main() {
    int choice;
    cout << "1. Register\n2. Login\n3. Update Password\n4. Delete File\n5. Exit" << endl << "Enter your choice: ";

    while (true) {
        try {
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Invalid choice. Please enter a valid number.");
            }

            switch (choice) {
                case 1:
                    registerUser();
                    break;
                case 2:
                    loginUser();
                    break;
                case 3:
                    updatePassword();
                    break;
                case 4:
                    deleteFile();
                    break;
                case 5:
                    cout << "Thank you for using the program. Goodbye!" << endl;
                    return 0;
                default:
                    throw invalid_argument("Invalid choice. Please enter a valid number.");
            }
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }

        cout << "1. Register\n2. Login\n3. Update Password\n4. Delete File\n5. Exit" << endl << "Enter your choice: ";
    }

    cout << "Thank you for using the program. Goodbye!" << endl;
    return 0;
}
