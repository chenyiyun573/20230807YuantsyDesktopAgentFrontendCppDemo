For the HTTP request cpp, using MinGW:
Trying History on 20240807 PT:

Download the lib curl, https://curl.se/download.html; or from here: http://public2.yuantsy.com/Software/curl-8.9.1.zip
Extract. 
```
g++ -o http_request http_request.cpp -IC:\Users\yiyun\Downloads\curl-8.9.1\curl-8.9.1\include -LC:\Users\yiyun\Downloads\curl-8.9.1\curl-8.9.1\lib -lcurl -lws2_32 -lwldap32 -lcrypt32
```
Errors happened:
```
PS C:\Users\yiyun\Desktop\FrontendCppDemo> g++ -o http_request http_request.cpp -IC:\Users\yiyun\Downloads\curl-8.9.1\curl-8.9.1\include -LC:\Users\yiyun\Downloads\curl-8.9.1\curl-8.9.1\lib -lcurl -lws2_32 -lwldap32 -lcrypt32
c:/mingw/bin/../lib/gcc/mingw32/6.3.0/../../../../mingw32/bin/ld.exe: cannot find -lcurl
collect2.exe: error: ld returned 1 exit status
PS C:\Users\yiyun\Desktop\FrontendCppDemo> 
```


Download here: 
https://curl.se/windows/
Extract it and add `C:\Users\yiyun\Downloads\curl-8.9.1_1-win64-mingw\curl-8.9.1_1-win64-mingw\bin` into Windows Environment Variable Path.
```bash
g++ -o http_request http_request.cpp -IC:\Users\yiyun\Downloads\curl-8.9.1_1-win64-mingw\curl-8.9.1_1-win64-mingw\include -LC:\Users\yiyun\Downloads\curl-8.9.1_1-win64-mingw\curl-8.9.1_1-win64-mingw\lib -lcurl -lws2_32 -lwldap32 -lcrypt32
```


Got the following errors:
```
PS C:\Users\yiyun\Desktop\FrontendCppDemo> g++ -o http_request http_request.cpp -IC:\Users\yiyun\Downloads\curl-8.9.1_1-win64-mingw\curl-8.9.1_1-win64-mingw\include -LC:\Users\yiyun\Downloads\curl-8.9.1_1-win64-mingw\curl-8.9.1_1-win64-mingw\lib -lcurl -lws2_32 -lwldap32 -lcrypt32
C:\Users\yiyun\AppData\Local\Temp\ccQ3GBZC.o:http_request.cpp:(.text+0x58): undefined reference to `_imp__curl_global_init'
C:\Users\yiyun\AppData\Local\Temp\ccQ3GBZC.o:http_request.cpp:(.text+0x5f): undefined reference to `_imp__curl_easy_init'
C:\Users\yiyun\AppData\Local\Temp\ccQ3GBZC.o:http_request.cpp:(.text+0x89): undefined reference to `_imp__curl_easy_setopt'
C:\Users\yiyun\AppData\Local\Temp\ccQ3GBZC.o:http_request.cpp:(.text+0xa6): undefined reference to `_imp__curl_easy_setopt'
C:\Users\yiyun\AppData\Local\Temp\ccQ3GBZC.o:http_request.cpp:(.text+0xc2): undefined reference to `_imp__curl_easy_setopt'
C:\Users\yiyun\AppData\Local\Temp\ccQ3GBZC.o:http_request.cpp:(.text+0xcf): undefined reference to `_imp__curl_easy_perform'
C:\Users\yiyun\AppData\Local\Temp\ccQ3GBZC.o:http_request.cpp:(.text+0xe5): undefined reference to `_imp__curl_easy_strerror'
C:\Users\yiyun\AppData\Local\Temp\ccQ3GBZC.o:http_request.cpp:(.text+0x146): undefined reference to `_imp__curl_easy_cleanup'
C:\Users\yiyun\AppData\Local\Temp\ccQ3GBZC.o:http_request.cpp:(.text+0x14d): undefined reference to `_imp__curl_global_cleanup'
collect2.exe: error: ld returned 1 exit status
PS C:\Users\yiyun\Desktop\FrontendCppDemo> 
```

20240808 0219 PT
Try the following for http request cpp, it works in MSYS, but the exe does not work outside MSYS:

After installing all packages by MSYS pacman:
using:
```
g++ -fdiagnostics-color=always -g -o http_request.exe http_request.cpp \
-L/mingw64/lib -lcurl -lssl -lcrypto -lidn2 -lnghttp2 -lnghttp3 -lz -lbrotlidec -lbrotlicommon -lzstd -lssh2 -llber -lldap -lbcrypt -lws2_32 -lcrypt32 -lunistring -lpsl
```

However, the exe works to send request in MSYS2, but does not work in windows PowerShell. I guess it was due to the dll and lib issues. 
This version of code is stored as 1.0.1

