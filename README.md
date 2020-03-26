# MemoryHackOSX
A memory read/write wrapper assembled for darwin/osx systems

compiled with Xcode's latest version you can get it from apple's app store (Developer Tools)


# objective-c source
<pre style='color:#000000;background:#ffffff;'><span style='color:#808080; '>//</span>
<span style='color:#808080; '>//  main.cpp</span>
<span style='color:#808080; '>//  external</span>
<span style='color:#808080; '>//</span>
<span style='color:#808080; '>//  Created by Liab on 20.01.2020.</span>
<span style='color:#808080; '>//  Copyright © 2020 LiabSecurity. All rights reserved.</span>
<span style='color:#808080; '>//</span>

<span style='color:#000084; '>#</span><span style='color:#000084; '>include </span><span style='color:#0000ff; '>&lt;</span><span style='color:#3f3fbf; '>iostream</span><span style='color:#0000ff; '>></span>
<span style='color:#000084; '>#</span><span style='color:#000084; '>include </span><span style='color:#0000ff; '>&lt;</span><span style='color:#3f3fbf; '>stdio.h</span><span style='color:#0000ff; '>></span>
<span style='color:#000084; '>#</span><span style='color:#000084; '>include </span><span style='color:#0000ff; '>&lt;</span><span style='color:#3f3fbf; '>mach/mach_init.h</span><span style='color:#0000ff; '>></span>
<span style='color:#000084; '>#</span><span style='color:#000084; '>include </span><span style='color:#0000ff; '>&lt;</span><span style='color:#3f3fbf; '>mach/mach_vm.h</span><span style='color:#0000ff; '>></span>
<span style='color:#000084; '>#</span><span style='color:#000084; '>include </span><span style='color:#0000ff; '>&lt;</span><span style='color:#3f3fbf; '>sys/types.h</span><span style='color:#0000ff; '>></span>
<span style='color:#000084; '>#</span><span style='color:#000084; '>include </span><span style='color:#0000ff; '>&lt;</span><span style='color:#3f3fbf; '>mach/mach.h</span><span style='color:#0000ff; '>></span>
<span style='color:#000084; '>#</span><span style='color:#000084; '>include </span><span style='color:#0000ff; '>&lt;</span><span style='color:#3f3fbf; '>sys/ptrace.h</span><span style='color:#0000ff; '>></span>
<span style='color:#000084; '>#</span><span style='color:#000084; '>include </span><span style='color:#0000ff; '>&lt;</span><span style='color:#3f3fbf; '>sys/wait.h</span><span style='color:#0000ff; '>></span>
<span style='color:#000084; '>#</span><span style='color:#000084; '>include </span><span style='color:#0000ff; '>&lt;</span><span style='color:#3f3fbf; '>Security/Authorization.h</span><span style='color:#0000ff; '>></span>
<span style='color:#000084; '>#</span><span style='color:#000084; '>include </span><span style='color:#0000ff; '>&lt;</span><span style='color:#3f3fbf; '>sstream</span><span style='color:#0000ff; '>></span>
<span style='color:#000084; '>#</span><span style='color:#000084; '>include </span><span style='color:#0000ff; '>&lt;</span><span style='color:#3f3fbf; '>fstream</span><span style='color:#0000ff; '>></span>
<span style='color:#000084; font-weight:bold; '>using</span> <span style='color:#000084; font-weight:bold; '>namespace</span> std;

<span style='color:#808080; '>//Memory Base 1.0</span>
<span style='color:#808080; '>//Author: Hirako Shiniji</span>
<span style='color:#808080; '>//last tested: 3.0</span>
<span style='color:#808080; '>//Made for educational purposes.</span>
<span style='color:#808080; '>//Platform: Darwin/OSX</span>
<span style='color:#000084; font-weight:bold; '>bool</span> gotScan=<span style='color:#000084; font-weight:bold; '>false</span>;
<span style='color:#000084; font-weight:bold; '>bool</span> kernstats=<span style='color:#000084; font-weight:bold; '>false</span>;
<span style='color:#000084; font-weight:bold; '>string</span> GetStringSh1t(<span style='color:#000084; font-weight:bold; '>char</span>* a, <span style='color:#000084; font-weight:bold; '>int</span> size)
{
    <span style='color:#000084; font-weight:bold; '>int</span> i;
    <span style='color:#000084; font-weight:bold; '>string</span> s = <span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>"</span>;
    <span style='color:#000084; font-weight:bold; '>for</span> (i = 0; i &lt; size; i++) {
        s = s + a[i];
    }
    <span style='color:#000084; font-weight:bold; '>return</span> s;
}
<span style='color:#000084; font-weight:bold; '>int</span> patternScan(pid_t pid,<span style='color:#000084; font-weight:bold; '>long</span> StartAddress,<span style='color:#000084; font-weight:bold; '>string</span> patternToScan){
    pointer_t buf;
            uint32_t sz;

            task_t task;
           
            kern_return_t kret = task_for_pid(current_task(), pid, &amp;task);
            <span style='color:#000084; font-weight:bold; '>if</span>(!kret==KERN_SUCCESS){
                kernstats=<span style='color:#000084; font-weight:bold; '>false</span>;
                
            }<span style='color:#000084; font-weight:bold; '>else</span>{
                kernstats=<span style='color:#000084; font-weight:bold; '>true</span>;
      
            }
    std::<span style='color:#000084; font-weight:bold; '>string</span> hexValue = <span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>0x10AD00000</span><span style='color:#0000ff; '>"</span>;

    std::<span style='color:#000084; font-weight:bold; '>istringstream</span> converter { hexValue };

    <span style='color:#000084; font-weight:bold; '>long</span> <span style='color:#000084; font-weight:bold; '>long</span> <span style='color:#000084; font-weight:bold; '>int</span> addresses = 0; <span style='color:#808080; '>// Variable to hold the new value</span>

    converter >> std::hex >> addresses; <span style='color:#808080; '>// Extract the hex value</span>

    std::<span style='color:#000084; font-weight:bold; '>cout</span> &lt;&lt; addresses &lt;&lt; <span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>\n</span><span style='color:#0000ff; '>"</span>;
    StartAddress=addresses;
    
    
    <span style='color:#000084; font-weight:bold; '>char</span> nop[]   ={
                <span style='color:#0000ff; '>'\xF3'</span>,<span style='color:#0000ff; '>'\x00'</span>,<span style='color:#0000ff; '>'\x00'</span>,<span style='color:#0000ff; '>'\x00'</span>
                
            };

            <span style='color:#000084; font-weight:bold; '>char</span> value[]  = {
                <span style='color:#0000ff; '>'\xF3'</span>,<span style='color:#0000ff; '>'\x00'</span>,<span style='color:#0000ff; '>'\x00'</span>,<span style='color:#0000ff; '>'\x00'</span>
                
            };

            <span style='color:#000084; font-weight:bold; '>char</span> test1[12];

    <span style='color:#000084; font-weight:bold; '>do</span>{
        ++StartAddress;
        <span style='color:#000084; font-weight:bold; '>try</span>{
            vm_protect(task,StartAddress, 12, 0, VM_PROT_READ | VM_PROT_WRITE | VM_PROT_ALL);
                       kret = vm_write(task, StartAddress, (pointer_t)999, 12);
                        <span style='color:#000084; font-weight:bold; '>memcpy</span>(test1,nop,13);
                    <span style='color:#000084; font-weight:bold; '>if</span> (vm_write(current_task(), StartAddress, (pointer_t)value, 12) == KERN_SUCCESS) {
                        <span style='color:#000084; font-weight:bold; '>printf</span>(<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>%s</span><span style='color:#0000ff; '>\n</span><span style='color:#0000ff; '>"</span>, nop);
                        <span style='color:#808080; '>//getchar();</span>
                    }
           
                    <span style='color:#000084; font-weight:bold; '>if</span> (vm_read(task, StartAddress, <span style='color:#000084; font-weight:bold; '>sizeof</span>(<span style='color:#000084; font-weight:bold; '>char</span>) * 12, &amp;buf, &amp;sz) == KERN_SUCCESS) {
                        
                        <span style='color:#000084; font-weight:bold; '>memcpy</span>(test1, (<span style='color:#000084; font-weight:bold; '>const</span> <span style='color:#000084; font-weight:bold; '>void</span> *)buf, sz);
                        <span style='color:#000084; font-weight:bold; '>cout</span>&lt;&lt;<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>scanning address: </span><span style='color:#0000ff; '>"</span> &lt;&lt; StartAddress&lt;&lt;<span style='color:#000084; font-weight:bold; '>endl</span>;
                        <span style='color:#000084; font-weight:bold; '>printf</span>(<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>%s</span><span style='color:#0000ff; '>"</span>, test1);
                        <span style='color:#000084; font-weight:bold; '>int</span> convertedShit = <span style='color:#000084; font-weight:bold; '>sizeof</span>(test1) / <span style='color:#000084; font-weight:bold; '>sizeof</span>(<span style='color:#000084; font-weight:bold; '>char</span>);
                                   <span style='color:#000084; font-weight:bold; '>string</span> MemString = GetStringSh1t(test1, convertedShit);
                                   <span style='color:#000084; font-weight:bold; '>if</span>(MemString.<span style='color:#000084; font-weight:bold; '>find</span>(patternToScan) != <span style='color:#000084; font-weight:bold; '>string</span>::<span style='color:#000084; font-weight:bold; '>npos</span>){
                                       gotScan=<span style='color:#000084; font-weight:bold; '>true</span>;
                                   }
                                   <span style='color:#000084; font-weight:bold; '>if</span>(test1==patternToScan){
                                       gotScan=<span style='color:#000084; font-weight:bold; '>true</span>;
                                      
                                   }
                                          <span style='color:#000084; font-weight:bold; '>if</span>(value==patternToScan){
                                             
                                              gotScan=<span style='color:#000084; font-weight:bold; '>true</span>;
                                          }
                        std::<span style='color:#000084; font-weight:bold; '>ofstream</span> ofs;
                        ofs.open (<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>scan.txt</span><span style='color:#0000ff; '>"</span>, std::<span style='color:#000084; font-weight:bold; '>ofstream</span>::out | std::<span style='color:#000084; font-weight:bold; '>ofstream</span>::app);
                        
                        ofs &lt;&lt; test1;

                        ofs.close();
                    }
        }<span style='color:#000084; font-weight:bold; '>catch</span>(<span style='color:#000084; font-weight:bold; '>int</span> lol){
            
        }
       
       
        
        
    }<span style='color:#000084; font-weight:bold; '>while</span> (gotScan==<span style='color:#000084; font-weight:bold; '>false</span>) ;
          <span style='color:#000084; font-weight:bold; '>printf</span>(<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>found address that you were scanning!</span><span style='color:#0000ff; '>"</span>);
    
    
    <span style='color:#000084; font-weight:bold; '>return</span> 1337;
}
<span style='color:#000084; font-weight:bold; '>int</span> <span style='color:#000084; font-weight:bold; '>WriteProcessMemory</span>(pid_t pid,vm_address_t address){
    <span style='color:#000084; font-weight:bold; '>char</span> nop[]   ={
        <span style='color:#0000ff; '>'\xF3'</span>,<span style='color:#0000ff; '>'\x00'</span>,<span style='color:#0000ff; '>'\x00'</span>,<span style='color:#0000ff; '>'\x00'</span>
        
    };

    <span style='color:#000084; font-weight:bold; '>char</span> value[]  = {
        <span style='color:#0000ff; '>'\xF3'</span>,<span style='color:#0000ff; '>'\x00'</span>,<span style='color:#0000ff; '>'\x00'</span>,<span style='color:#0000ff; '>'\x00'</span>
        
    };

    <span style='color:#000084; font-weight:bold; '>char</span> test1[12];

    pointer_t buf;
    uint32_t sz;

    task_t task;
   
    kern_return_t kret = task_for_pid(current_task(), pid, &amp;task);
    <span style='color:#000084; font-weight:bold; '>if</span>(!kret==KERN_SUCCESS){
        <span style='color:#000084; font-weight:bold; '>printf</span>(<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>kern fail.</span><span style='color:#0000ff; '>"</span>);
    }<span style='color:#000084; font-weight:bold; '>else</span>{
         <span style='color:#000084; font-weight:bold; '>printf</span>(<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>success kern</span><span style='color:#0000ff; '>"</span>);
    }
-
    vm_protect(task,address, 12, 0, VM_PROT_READ | VM_PROT_WRITE | VM_PROT_ALL);
       kret = vm_write(task, address, (pointer_t)999, 12);
        <span style='color:#000084; font-weight:bold; '>memcpy</span>(test1,nop,13);
    <span style='color:#000084; font-weight:bold; '>if</span> (vm_write(current_task(), address, (pointer_t)value, 12) == KERN_SUCCESS) {
        <span style='color:#000084; font-weight:bold; '>printf</span>(<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>%s</span><span style='color:#0000ff; '>\n</span><span style='color:#0000ff; '>"</span>, nop);
        <span style='color:#808080; '>//getchar();</span>
    }

    <span style='color:#000084; font-weight:bold; '>if</span> (vm_read(task, address, <span style='color:#000084; font-weight:bold; '>sizeof</span>(<span style='color:#000084; font-weight:bold; '>char</span>) * 12, &amp;buf, &amp;sz) == KERN_SUCCESS) {
        
        <span style='color:#000084; font-weight:bold; '>memcpy</span>(test1, (<span style='color:#000084; font-weight:bold; '>const</span> <span style='color:#000084; font-weight:bold; '>void</span> *)buf, sz);
        <span style='color:#000084; font-weight:bold; '>printf</span>(<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>%s</span><span style='color:#0000ff; '>"</span>, test1);
    }
   
    <span style='color:#000084; font-weight:bold; '>return</span> kret;
}

<span style='color:#000084; font-weight:bold; '>int</span> <span style='color:#000084; font-weight:bold; '>main</span>(<span style='color:#000084; font-weight:bold; '>int</span> argc, <span style='color:#000084; font-weight:bold; '>const</span> <span style='color:#000084; font-weight:bold; '>char</span> * argv[]) {
    <span style='color:#000084; font-weight:bold; '>int</span> get_pid=<span style='color:#000084; font-weight:bold; '>system</span>(<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>pgrep Growtopia</span><span style='color:#0000ff; '>"</span>);
    <span style='color:#000084; font-weight:bold; '>cout</span>&lt;&lt;get_pid&lt;&lt;<span style='color:#000084; font-weight:bold; '>endl</span>;
    pid_t pid = argc >= 2 ? <span style='color:#000084; font-weight:bold; '>atoi</span>(argv[1]) : 1;
    std::<span style='color:#000084; font-weight:bold; '>string</span> command;
    std::<span style='color:#000084; font-weight:bold; '>string</span> pattern;
    std::getline (std::<span style='color:#000084; font-weight:bold; '>cin</span>,command);
    <span style='color:#000084; font-weight:bold; '>if</span>(command==<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>-dump</span><span style='color:#0000ff; '>"</span>){
        <span style='color:#000084; font-weight:bold; '>printf</span>(<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>starting growtopia memory dump operation... but first gimme some relief</span><span style='color:#0000ff; '>"</span>);
       
    }
    <span style='color:#000084; font-weight:bold; '>if</span>(command==<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>-scan</span><span style='color:#0000ff; '>"</span>){
         std::getline (std::<span style='color:#000084; font-weight:bold; '>cin</span>,pattern);
        <span style='color:#000084; font-weight:bold; '>cout</span>&lt;&lt;<span style='color:#0000ff; '>"</span><span style='color:#0000ff; '>gonna scan for: </span><span style='color:#0000ff; '>"</span> &lt;&lt; pattern&lt;&lt;<span style='color:#000084; font-weight:bold; '>endl</span>;
         patternScan(pid, 0x111111111, pattern);
        
    }
    
    <span style='color:#808080; '>//WriteProcessMemory(pid,0x1078B2A4E);</span>

    <span style='color:#000084; font-weight:bold; '>return</span> 0;
}
</pre>
<!--Created using ToHtml.com on 2020-03-26 15:54:58 UTC -->
