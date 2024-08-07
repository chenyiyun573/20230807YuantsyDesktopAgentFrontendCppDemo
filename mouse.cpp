#include <windows.h>

// Function to move the mouse to a specified position
void MoveMouse(int x, int y) {
    SetCursorPos(x, y);
}

// Function to simulate a mouse left click
void LeftClick() {
    // Structure for mouse event
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));

    // Clear the structure and set flags for left up
    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

// Function to simulate a mouse right click
void RightClick() {
    // Structure for mouse event
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &input, sizeof(INPUT));

    // Clear the structure and set flags for right up
    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));
}

int main() {
    // Example usage
    MoveMouse(200, 200); // Move mouse to screen position x=200, y=200
    Sleep(1000); // Wait for 1 second
    LeftClick(); // Perform left click
    Sleep(1000); // Wait for 1 second
    RightClick(); // Perform right click

    return 0;
}
