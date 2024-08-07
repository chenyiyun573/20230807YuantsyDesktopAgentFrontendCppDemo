#include <windows.h>

// Function to simulate a key press and release
void SendKeystroke(WORD vk, bool shift = false) {
    INPUT inputs[4] = {};
    int inputCount = 0;

    // Setup a keyboard event for the shift key if needed
    if (shift) {
        inputs[inputCount].type = INPUT_KEYBOARD;
        inputs[inputCount].ki.wVk = VK_SHIFT;
        inputs[inputCount].ki.dwFlags = 0; // Shift key down
        inputCount++;
    }

    // Key down event
    inputs[inputCount].type = INPUT_KEYBOARD;
    inputs[inputCount].ki.wVk = vk;
    inputs[inputCount].ki.dwFlags = 0; // Key down
    inputCount++;

    // Key up event
    inputs[inputCount].type = INPUT_KEYBOARD;
    inputs[inputCount].ki.wVk = vk;
    inputs[inputCount].ki.dwFlags = KEYEVENTF_KEYUP;
    inputCount++;

    // Shift key up if it was pressed
    if (shift) {
        inputs[inputCount].type = INPUT_KEYBOARD;
        inputs[inputCount].ki.wVk = VK_SHIFT;
        inputs[inputCount].ki.dwFlags = KEYEVENTF_KEYUP;
        inputCount++;
    }

    // Send the sequence of key events
    SendInput(inputCount, inputs, sizeof(INPUT));
}

// Function to automate opening Edge, typing a URL, and navigating
void OpenEdgeAndNavigate() {
    // Press and release the Windows key to open the start menu
    SendKeystroke(VK_LWIN);
    Sleep(2000); // Sleep for 2 seconds

    // Type "Edge"
    SendKeystroke(0x45); // E
    SendKeystroke(0x44); // D
    SendKeystroke(0x47); // G
    SendKeystroke(0x45); // E
    Sleep(2000); // Sleep for 2 seconds

    // Press Enter to launch Edge
    SendKeystroke(VK_RETURN);
    Sleep(2000); // Sleep for 2 seconds

    // Type "yuantsy.com"
    SendKeystroke(0x59); // Y
    SendKeystroke(0x55); // U
    SendKeystroke(0x41); // A
    SendKeystroke(0x4E); // N
    SendKeystroke(0x54); // T
    SendKeystroke(0x53); // S
    SendKeystroke(0x59); // Y
    SendKeystroke(VK_OEM_PERIOD); // .
    SendKeystroke(0x43); // C
    SendKeystroke(0x4F); // O
    SendKeystroke(0x4D); // M
    Sleep(2000); // Sleep for 2 seconds

    // Press Enter to navigate
    SendKeystroke(VK_RETURN);
    Sleep(2000); // Sleep for 2 seconds
}

int main() {
    OpenEdgeAndNavigate();
    return 0;
}
