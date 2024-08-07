#include <windows.h>
#include <iostream>
#include <cstring>

// Define the implementation
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Function to take a screenshot
bool TakeScreenshot(const char* filename) {
    // Get the device context of the screen
    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    // Create a compatible bitmap from the Screen DC
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);

    // Select the new bitmap into the memory DC
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

    // Bit blit from screen to memory device context
    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
    hBitmap = (HBITMAP)SelectObject(hMemoryDC, hOldBitmap);

    // Save the bitmap to a file
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  // Negative to place origin at top left
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    BYTE* lpBits = new BYTE[width * height * 4];
    GetDIBits(hMemoryDC, hBitmap, 0, height, lpBits, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    // Write to PNG using stb_image_write
    stbi_write_png(filename, width, height, 4, lpBits, width * 4);

    // Clean up
    delete[] lpBits;
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);

    return true;
}

int main() {
    if (TakeScreenshot("screenshot.png")) {
        std::cout << "Screenshot saved as screenshot.png" << std::endl;
    } else {
        std::cout << "Failed to take screenshot." << std::endl;
    }
    return 0;
}
