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
using namespace std;

//Memory Base 1.0
//Author: Hirako Shiniji
//last tested: 3.0
//Made for educational purposes.
//Platform: Darwin/OSX

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
    WriteProcessMemory(pid,0x1078B2A4E);
    return 0;
}
