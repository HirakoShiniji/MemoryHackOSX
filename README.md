# MemoryHackOSX
A memory read/write wrapper assembled for darwin/osx systems

# Firstly call the imports
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

# get task_for_pid for reading/writing. (a type of openProcess for windows)

kern_return_t kret = task_for_pid(current_task(), pid, &task);
    if(!kret==KERN_SUCCESS){
        printf("kern fail.");
    }else{
         printf("success kern");
    }
    
 # vm_protect get all access from memory address
 vm_protect(task,address, 12, 0, VM_PROT_READ | VM_PROT_WRITE | VM_PROT_ALL);
