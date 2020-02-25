/*++

    Copyright (c) Microsoft Corporation. All rights reserved.
    Licensed under the MIT license.

Module Name:

    DmfPlatform_Win32.h

Abstract:

    Companion file to DmfPlatform_Win32.c.

    NOTE: Make sure to set "compile as C++" option.
    NOTE: Make sure to #define DMF_USER_MODE in UMDF Drivers.

Environment:

    Win32 Application

--*/

#if defined(__cplusplus)
extern "C" 
{
#endif // defined(__cplusplus)

////////////////////////////////////////////////////////////////////////////
// Win32 Primitives for Memory Allocation
////////////////////////////////////////////////////////////////////////////
//

#if defined(DMF_WIN32_MODE)

typedef struct _DMF_PLATFORM_MEMORY
{
    void* DataMemory;
    size_t Size;
    BOOLEAN NeedToDeallocate;
} DMF_PLATFORM_MEMORY;

typedef struct _DMF_PLATFORM_SPINLOCK
{
    CRITICAL_SECTION SpinLock;
} DMF_PLATFORM_SPINLOCK;

typedef struct _DMF_PLATFORM_WAITLOCK
{
    HANDLE Event;
} DMF_PLATFORM_WAITLOCK;

typedef struct _DMF_PLATFORM_TIMER
{
    PTP_TIMER PtpTimer;
    WDF_TIMER_CONFIG Config;
} DMF_PLATFORM_TIMER;

typedef struct _DMF_PLATFORM_WORKITEM
{
    // Use timer to caused deferred processing in Win32.
    //
    WDFTIMER Timer;
    WDF_WORKITEM_CONFIG Config;
} DMF_PLATFORM_WORKITEM;

typedef struct _DMF_PLATFORM_COLLECTION
{
    LIST_ENTRY List;
    ULONG ItemCount;
    WDFSPINLOCK ListLock;
} DMF_PLATFORM_COLLECTION;

typedef struct _DMF_PLATFORM_QUEUE
{
    WDF_IO_QUEUE_CONFIG Config;
} DMF_PLATFORM_QUEUE;

typedef struct _DMF_PLATFORM_DEVICE
{
    ULONG Dummy;
} DMF_PLATFORM_DEVICE;

#define PAGED_CODE()

void*
DMF_Platform_Allocate(
    size_t Size
    );

void
DMF_Platform_Free(
    void* Pointer
    );

typedef CRITICAL_SECTION DMF_PLATFORM_CRITICAL_SECTION;

BOOLEAN
DMF_Platform_CriticalSectionCreate(
    _Out_ DMF_PLATFORM_CRITICAL_SECTION* CriticalSection
    );

void
DMF_Platform_CriticalSectionEnter(
    _Out_ DMF_PLATFORM_CRITICAL_SECTION* CriticalSection
    );

void
DMF_Platform_CriticalSectionLeave(
    DMF_PLATFORM_CRITICAL_SECTION* CriticalSection
    );

void
DMF_Platform_CriticalSectionDelete(
    DMF_PLATFORM_CRITICAL_SECTION* CriticalSection
    );

extern DmfPlatform_Handlers DmfPlatformHandlersTable;

#endif // defined(DMF_WIN32_MODE)

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// eof: DmfPlatform_Win32.h
//