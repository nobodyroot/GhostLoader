#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <windows.h>

extern "C" {
    NTSTATUS NtOpenProcess(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, 
                          POBJECT_ATTRIBUTES ObjectAttributes, PCLIENT_ID ClientId);
    
    NTSTATUS NtAllocateVirtualMemory(HANDLE ProcessHandle, PVOID* BaseAddress, 
                                   ULONG_PTR ZeroBits, PSIZE_T RegionSize, 
                                   ULONG AllocationType, ULONG Protect);
    
    NTSTATUS NtWriteVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, 
                                 PVOID Buffer, SIZE_T NumberOfBytesToWrite, 
                                 PSIZE_T NumberOfBytesWritten);
    
    NTSTATUS NtProtectVirtualMemory(HANDLE ProcessHandle, PVOID* BaseAddress, 
                                   PSIZE_T RegionSize, ULONG NewProtect, 
                                   PULONG OldProtect);
    
    NTSTATUS NtCreateThreadEx(PHANDLE ThreadHandle, ACCESS_MASK DesiredAccess,
                             POBJECT_ATTRIBUTES ObjectAttributes, HANDLE ProcessHandle,
                             PVOID StartRoutine, PVOID Argument, ULONG CreateFlags,
                             SIZE_T ZeroBits, SIZE_T StackSize, SIZE_T MaximumStackSize,
                             PVOID AttributeList);
    
    NTSTATUS NtWaitForSingleObject(HANDLE Handle, BOOLEAN Alertable, PLARGE_INTEGER Timeout);
    
    NTSTATUS NtTraceEvent(HANDLE TraceHandle, ULONG Flags, ULONG FieldSize, PVOID Fields);
    
    NTSTATUS NtDelayExecution(BOOLEAN Alertable, PLARGE_INTEGER DelayInterval);
}

#endif
