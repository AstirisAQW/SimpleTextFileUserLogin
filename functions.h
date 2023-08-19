// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>

// Function prototypes
std::string encrypt(const std::string& text, char key);
bool isLoggedIn(const std::string& username, const std::string& password, const std::string& filename);
void registerUser();
void loginUser();
void updatePassword();
void deleteFile();

// Function to encrypt a string using a simple XOR technique
std::string encrypt(const std::string& text, char key) {
    std::string result = "";

    // Iterate through each character in the text and apply XOR with the key
    for (const auto& ch : text) {
        result += ch ^ key;
    }
    return result;
}

// Function to check if a user is registered and their password is correct
bool isLoggedIn(const std::string& username, const std::string& password, const std::string& filename) {
    std::string encryptedUsername, encryptedPassword, un, pw;
    const char encryptionKey = 'K'; // Set the encryption key

    // Encrypt the username and password using the encryption key
    encryptedUsername = encrypt(username, encryptionKey);
    encryptedPassword = encrypt(password, encryptionKey);

    // Read the registered user data from the file
    std::ifstream infile(filename);
    if (infile.is_open()) {
        // Loop through each line in the file and compare the encrypted data
        while (std::getline(infile, un) && std::getline(infile, pw)) {
            if (un == encryptedUsername && pw == encryptedPassword) {
                infile.close();
                return true;
            }
        }
        infile.close();
    }
    return false;
}

// Function for user registration
void registerUser() {
    std::string username, password, filename;

    // Check if the file already exists and prompt for a unique filename
    bool uniqueFile = false;
    while (!uniqueFile) {
        std::cout << "Enter a filename for your account: ";
        std::cin >> filename;
        std::ifstream infile(filename);
        if (!infile.good()) {
            uniqueFile = true;
        } else {
            std::cout << "Error: Filename already exists. Please choose another filename." << std::endl;
        }
        infile.close();
    }

    std::cout << "Enter a username: ";
    std::cin >> username;
    std::cout << "Enter a password: ";
    std::cin >> password;

    // Encrypt the username and password using the encryption key
    const char encryptionKey = 'K';
    std::string encryptedUsername = encrypt(username, encryptionKey);
    std::string encryptedPassword = encrypt(password, encryptionKey);

    // Save the encrypted registration details to a text file
    std::ofstream outfile(filename, std::ios::app);
    if (outfile.is_open()) {
        outfile << encryptedUsername << std::endl << encryptedPassword << std::endl;
        outfile.close();
        std::cout << "Registration successful." << std::endl;
    } else {
        std::cout << "Error: Unable to open file." << std::endl;
    }
}

// Function for user login
void loginUser() {
    std::string username, password, filename;
    std::cout << "Enter the filename of your account: ";
    std::cin >> filename;

    // Check if the file exists
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "Error: File not found. Please make sure you entered the correct filename." << std::endl;
    } else {
        infile.close();
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter your password: ";
        std::cin >> password;

        // Check if the user is registered and the password is correct
        if (isLoggedIn(username, password, filename)) {
            std::cout << "Login successful." << std::endl;
        } else {
            std::cout << "Incorrect username or password." << std::endl;
        }
    }
}

// Function for updating password
void updatePassword() {
    std::string username, oldPassword, newPassword, filename;
    std::cout << "Enter the filename for your account: ";
    std::cin >> filename;

    // Check if the file exists
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "Error: File not found. Please make sure you entered the correct filename." << std::endl;
    } else {
        infile.close();
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter your current password: ";
        std::cin >> oldPassword;

        // Check if the user is registered and the password is correct
        if (isLoggedIn(username, oldPassword, filename)) {
            std::cout << "Enter your new password: ";
            std::cin >> newPassword;

            // Update the password in the file
            std::ofstream outfile(filename);
            if (outfile.is_open()) {
                outfile << encrypt(username, 'K') << std::endl << encrypt(newPassword, 'K') << std::endl;
                outfile.close();
                std::cout << "Successfully changed password." << std::endl;
            } else {
                std::cout << "Error: Unable to open file." << std::endl;
            }
        } else {
            std::cout << "Incorrect username or password." << std::endl;
        }
    }
}

// Function for deleting File
void deleteFile() {
    std::string username, password, filename;
    std::cout << "Enter the filename for your account: ";
    std::cin >> filename;

    // Check if the file exists
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "Error: File not found. Please make sure you entered the correct filename." << std::endl;
    } else {
        infile.close();
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter your password: ";
        std::cin >> password;

        // Check if the user is registered and the password is correct
        if (isLoggedIn(username, password, filename)) {
            // Delete the file
            if (remove(filename.c_str()) == 0) {
                std::cout << "Successfully deleted your account." << std::endl;
            } else {
                std::cout << "Error: Unable to delete file." << std::endl;
            }
        } else {
            std::cout << "Incorrect username or password." << std::endl;
        }
    }
}

#endif
