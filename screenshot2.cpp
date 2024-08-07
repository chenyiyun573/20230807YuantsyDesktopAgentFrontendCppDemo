#include <windows.h>
#include <iostream>

// Define the implementation before including stb_image_write.h
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Function to capture the entire screen and save it as a PNG file
bool TakeScreenshot(const char* filename) {
    // Get the device context of the entire screen
    HDC hScreenDC = GetDC(NULL);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN) * 2;
    int screenHeight = GetSystemMetrics(SM_CYSCREEN) * 2;
    // I have to multiple it by 2 to take the whole screen, unknow reasons. - Yiyun at 20240806 2353 PT

    // Create a compatible DC and a new bitmap for capturing
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, screenWidth, screenHeight);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

    // Copy from screen to the bitmap
    if (!BitBlt(hMemoryDC, 0, 0, screenWidth, screenHeight, hScreenDC, 0, 0, SRCCOPY)) {
        std::cerr << "BitBlt failed!" << std::endl;
        return false;
    }

    // Prepare to save the bitmap
    BITMAPINFOHEADER bi = {0};
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = screenWidth;
    bi.biHeight = -screenHeight;  // Negative indicates top-down bitmap
    bi.biPlanes = 1;
    bi.biBitCount = 32;           // 4 bytes per pixel (RGBA)
    bi.biCompression = BI_RGB;
    
    BYTE* lpBits = new BYTE[screenWidth * screenHeight * 4];  // 4 channels: RGBA
    if (!GetDIBits(hMemoryDC, hBitmap, 0, screenHeight, lpBits, (BITMAPINFO*)&bi, DIB_RGB_COLORS)) {
        std::cerr << "GetDIBits failed!" << std::endl;
        delete[] lpBits;
        return false;
    }

    // Yiyun at 20240806 2355 PT
    // I found the output of screenshot.png's color is weird, so I changed the order. 
    // Assuming lpBits contains the bitmap data
    for (int i = 0; i < screenWidth * screenHeight; ++i) {
        BYTE* pixel = lpBits + i * 4;  // Pointer to the pixel (4 bytes per pixel)
        BYTE temp = pixel[0];          // Store the blue value (first byte)
        pixel[0] = pixel[2];           // Set blue to red (third byte)
        pixel[2] = temp;               // Set red to blue (stored value)
    }


    // Save the captured bitmap as a PNG
    if (!stbi_write_png(filename, screenWidth, screenHeight, 4, lpBits, screenWidth * 4)) {
        std::cerr << "Failed to write PNG file!" << std::endl;
        delete[] lpBits;
        return false;
    }

    // Clean up
    delete[] lpBits;
    SelectObject(hMemoryDC, oldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);

    return true;
}

int main() {
    if (TakeScreenshot("screenshot.png")) {
        std::cout << "Screenshot saved successfully." << std::endl;
    } else {
        std::cout << "Failed to take screenshot." << std::endl;
    }
    return 0;
}
