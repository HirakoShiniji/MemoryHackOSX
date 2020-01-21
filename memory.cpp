//
//  main.cpp
//  external
//
//  Created by Liab on 20.01.2020.
//  Copyright © 2020 LiabSecurity. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <mach/mach_init.h>
#include <mach/mach_vm.h>
#include <sys/types.h>
#include <mach/mach.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <Security/Authorization.h>
#include <sstream>
#include <fstream>
using namespace std;

//Memory Base 1.0
//Author: Hirako Shiniji
//last tested: 3.0
//Made for educational purposes.
//Platform: Darwin/OSX
bool gotScan=false;
bool kernstats=false;
string GetStringSh1t(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}
int patternScan(pid_t pid,long StartAddress,string patternToScan){
    pointer_t buf;
            uint32_t sz;

            task_t task;
           
            kern_return_t kret = task_for_pid(current_task(), pid, &task);
            if(!kret==KERN_SUCCESS){
                kernstats=false;
                
            }else{
                kernstats=true;
      
            }
    std::string hexValue = "0x10AD00000";

    std::istringstream converter { hexValue };

    long long int addresses = 0; // Variable to hold the new value

    converter >> std::hex >> addresses; // Extract the hex value

    std::cout << addresses << "\n";
    StartAddress=addresses;
    
    
    char nop[]   ={
                '\xF3','\x00','\x00','\x00'
                
            };

            char value[]  = {
                '\xF3','\x00','\x00','\x00'
                
            };

            char test1[12];

    do{
        ++StartAddress;
        try{
            vm_protect(task,StartAddress, 12, 0, VM_PROT_READ | VM_PROT_WRITE | VM_PROT_ALL);
                       kret = vm_write(task, StartAddress, (pointer_t)999, 12);
                        memcpy(test1,nop,13);
                    if (vm_write(current_task(), StartAddress, (pointer_t)value, 12) == KERN_SUCCESS) {
                        printf("%s\n", nop);
                        //getchar();
                    }
           
                    if (vm_read(task, StartAddress, sizeof(char) * 12, &buf, &sz) == KERN_SUCCESS) {
                        
                        memcpy(test1, (const void *)buf, sz);
                        cout<<"scanning address: " << StartAddress<<endl;
                        printf("%s", test1);
                        int convertedShit = sizeof(test1) / sizeof(char);
                                   string MemString = GetStringSh1t(test1, convertedShit);
                                   if(MemString.find(patternToScan) != string::npos){
                                       gotScan=true;
                                   }
                                   if(test1==patternToScan){
                                       gotScan=true;
                                      
                                   }
                                          if(value==patternToScan){
                                             
                                              gotScan=true;
                                          }
                        std::ofstream ofs;
                        ofs.open ("scan.txt", std::ofstream::out | std::ofstream::app);
                        
                        ofs << test1;

                        ofs.close();
                    }
        }catch(int lol){
            
        }
       
       
        
        
    }while (gotScan==false) ;
          printf("found address that you were scanning!");
    
    
    return 1337;
}
int WriteProcessMemory(pid_t pid,vm_address_t address){
    char nop[]   ={
        '\xF3','\x00','\x00','\x00'
        
    };

    char value[]  = {
        '\xF3','\x00','\x00','\x00'
        
    };

    char test1[12];

    pointer_t buf;
    uint32_t sz;

    task_t task;
   
    kern_return_t kret = task_for_pid(current_task(), pid, &task);
    if(!kret==KERN_SUCCESS){
        printf("kern fail.");
    }else{
         printf("success kern");
    }
-
    vm_protect(task,address, 12, 0, VM_PROT_READ | VM_PROT_WRITE | VM_PROT_ALL);
       kret = vm_write(task, address, (pointer_t)999, 12);
        memcpy(test1,nop,13);
    if (vm_write(current_task(), address, (pointer_t)value, 12) == KERN_SUCCESS) {
        printf("%s\n", nop);
        //getchar();
    }

    if (vm_read(task, address, sizeof(char) * 12, &buf, &sz) == KERN_SUCCESS) {
        
        memcpy(test1, (const void *)buf, sz);
        printf("%s", test1);
    }
   
    return kret;
}

int main(int argc, const char * argv[]) {
    int get_pid=system("pgrep Growtopia");
    cout<<get_pid<<endl;
    pid_t pid = argc >= 2 ? atoi(argv[1]) : 1;
    std::string command;
    std::string pattern;
    std::getline (std::cin,command);
    if(command=="-dump"){
        printf("starting growtopia memory dump operation... but first gimme some relief");
       
    }
    if(command=="-scan"){
         std::getline (std::cin,pattern);
        cout<<"gonna scan for: " << pattern<<endl;
         patternScan(pid, 0x111111111, pattern);
        
    }
    
    //WriteProcessMemory(pid,0x1078B2A4E);

    return 0;
}
