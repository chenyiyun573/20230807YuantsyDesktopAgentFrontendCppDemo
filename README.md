Ensure MinGW is installed on your windows and added into path.


1. Keyboard:
```
g++ keyboard.cpp -o OpenYuantsyWeb.exe -luser32
```

2. Screenshot:
Download the `std_image_write.h` from https://github.com/nothings/stb/blob/master/stb_image_write.h



```
g++ -o screenshot.exe screenshot.cpp -lgdi32 -luser32
g++ -o screenshot2.exe screenshot2.cpp -lgdi32 -luser32
```


3. Mouse:

```
g++ -o mouse.exe mouse.cpp
```

4. Http request:
Use MSYS2, and in the terminal of MSYS2:
After installing all packages by MSYS pacman:
using:
```
g++ -fdiagnostics-color=always -g -o http_request.exe http_request.cpp \
-L/mingw64/lib -lcurl -lssl -lcrypto -lidn2 -lnghttp2 -lnghttp3 -lz -lbrotlidec -lbrotlicommon -lzstd -lssh2 -llber -lldap -lbcrypt -lws2_32 -lcrypt32 -lunistring -lpsl
```

