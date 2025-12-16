/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoVFB1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoMemoryManager1Lab.h"
#include "IEcoVirtualMemory1.h"
#include "IEcoTaskScheduler1.h"
#include "IdEcoTaskScheduler1Lab.h"
#include "IdEcoTimer1.h"
#include "IEcoSystemTimer1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "IdEcoIPCCMailbox1.h"
#include "IdEcoVFB1.h"
#include "IEcoVBIOS1Video.h"
#include "IdEcoMutex1Lab.h"
#include "IdEcoSemaphore1Lab.h"

/* Начало свободного участка памяти */
extern char_t __heap_start__;

/* Указатель на интерфейс для работы c мьютекс */
IEcoMutex1* g_pIMutex = 0;
/* Указатель на интерфейс для работы c семафор */
IEcoSemaphore1* g_pISemaphore = 0;

/* Указатель на интерфейсы */
IEcoVBIOS1Video* g_pIVideo = 0;
IEcoSystemTimer1* g_pISysTimer = 0;

char_t g_strTask[2] = {0};

#define TASK_DUR_US  (5000000ul)
#define BAR_LEN      (40)
#define SEG_LEN      (20)
uint64_t g_t0 = 0;

static void u64_to_dec(uint64_t v, char_t* out, uint32_t out_sz) {
    char_t tmp[32];
    uint32_t i = 0, j = 0;
    if (out == 0 || out_sz == 0) return;
    if (v == 0) {
        if (out_sz >= 2) { out[0] = '0'; out[1] = 0; }
        return;
    }
    while (v > 0 && i < sizeof(tmp)) {
        tmp[i++] = (char_t)('0' + (v % 10));
        v /= 10;
    }
    if (i + 1 > out_sz) i = out_sz - 1;
    while (i > 0) {
        out[j++] = tmp[--i];
    }
    out[j] = 0;
}

static void draw_bar(uint8_t taskId, uint32_t filled, uint32_t total) {
    char_t bar[BAR_LEN + 1];
    uint32_t i;
    if (filled > total) filled = total;
    for (i = 0; i < BAR_LEN; ++i) {
        uint32_t threshold = (uint32_t)((uint64_t)filled * BAR_LEN / (total ? total : 1));
        bar[i] = (i < threshold) ? '#' : ' ';
    }
    bar[BAR_LEN] = 0;

    {
        uint16_t y = (uint16_t)(2 + (taskId - 1));
        char_t label[8] = {'T', (char_t)('0' + taskId), ':', ' ', 0, 0, 0, 0};
        g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, 0, y, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, label, 4);
        g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, 4, y, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, bar, BAR_LEN);
    }
}

static void draw_timeline(uint8_t taskId, uint32_t filled, uint32_t total) {
    char_t seg[SEG_LEN + 1];
    uint32_t i;
    uint16_t x0 = (uint16_t)(10 + (taskId - 1) * SEG_LEN);
    uint16_t y = 8;
    if (filled > total) filled = total;
    for (i = 0; i < SEG_LEN; ++i) {
        uint32_t threshold = (uint32_t)((uint64_t)filled * SEG_LEN / (total ? total : 1));
        seg[i] = (i < threshold) ? (char_t)('0' + taskId) : '.';
    }
    seg[SEG_LEN] = 0;
    g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, x0, y, CHARACTER_ATTRIBUTE_FORE_COLOR_YELLOW, seg, SEG_LEN);
}

static void draw_status(const char_t* msg) {
    g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, 0, 0,
    CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE,
    "                                                                                ", 80);

    g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, 0, 0, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, "Status: ", 8);
    if (msg != 0) {
        uint16_t i = 0;
        while (msg[i] != 0 && i < 60) { i++; }
        g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, 8, 0, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, (char_t*)msg, i);
    }
}

static void run_task(uint8_t taskId) {
    uint64_t start = g_pISysTimer->pVTbl->get_SingleTimerCounter(g_pISysTimer);
    uint64_t now = start;
    uint64_t end = start + TASK_DUR_US;
    {
        char_t st[32] = "RUNNING T?";
        st[9] = (char_t)('0' + taskId);
        draw_status(st);
    }
    {
        char_t num[24] = {0};
        char_t prefix[12] = {'t', (char_t)('0' + taskId), ' ', 's','t','a','r','t','=', ' ', 0, 0};
        uint16_t len_num = 0;
        uint64_t rel = (g_t0 == 0) ? start : (start - g_t0);
        u64_to_dec(rel, num, sizeof(num));
        while (num[len_num] != 0 && len_num < 23) { len_num++; }
        g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, 0, 6, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, prefix, 10);
        g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, 10, 6, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, num, len_num);
        g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, 10 + len_num, 6, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, " us", 3);
    }

    while (end >= now) {
        uint64_t elapsed = now - start;
        uint32_t step = (uint32_t)(elapsed / 50000ul);
        uint32_t total = (uint32_t)(TASK_DUR_US / 50000ul);
        draw_bar(taskId, step, total);
        draw_timeline(taskId, step, total);
        now = g_pISysTimer->pVTbl->get_SingleTimerCounter(g_pISysTimer);
    }

    {
        char_t st[32] = "DONE    T?";
        st[9] = (char_t)('0' + taskId);
        draw_status(st);
    }
    {
        char_t num[24] = {0};
        char_t prefix[10] = {'t', (char_t)('0' + taskId), ' ', 'e','n','d','=', ' ', 0, 0};
        uint16_t len_num = 0;
        uint64_t t = g_pISysTimer->pVTbl->get_SingleTimerCounter(g_pISysTimer);
        uint64_t rel = (g_t0 == 0) ? t : (t - g_t0);
        u64_to_dec(rel, num, sizeof(num));
        while (num[len_num] != 0 && len_num < 23) { len_num++; }
        g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, 25, 6, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, prefix, 8);
        g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, 33, 6, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, num, len_num);
        g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, 33 + len_num, 6, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, " us", 3);
    }
}



void TimerHandler(void) {
    if (g_pIMutex != 0) {
        g_pIMutex->pVTbl->Lock(g_pIMutex);
    }

    if (g_strTask[0] == '\\') {
        g_strTask[0] = '|';
    }
    else if (g_strTask[0] == '|') {
        g_strTask[0] = '/';
    }
    else if (g_strTask[0] == '/') {
        g_strTask[0] = '-';
    }
    else  {
        g_strTask[0] = '\\';
    }

    if (g_pIVideo != 0) {
        g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, 20, 0, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, g_strTask, 1);
    }

    if (g_pIMutex != 0) {
        g_pIMutex->pVTbl->UnLock(g_pIMutex);
    }
}

void printProgress() {
    if (g_strTask[0] == '\\') {
        g_strTask[0] = '|';
    }
    else if (g_strTask[0] == '|') {
        g_strTask[0] = '/';
    }
    else if (g_strTask[0] == '/') {
        g_strTask[0] = '-';
    }
    else  {
        g_strTask[0] = '\\';
    }
    g_pIVideo->pVTbl->WriteString(g_pIVideo, 0, 0, 1, 0, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, g_strTask, 1);
}

void Task1() {
    run_task(1);
}


void Task2() {
    run_task(2);
}


void Task3() {
    run_task(3);
}


/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoMemoryManager1* pIMemMgr = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoVirtualMemory1* pIVrtMem = 0;
    /* Указатель на интерфейс для работы с планировщиком */
    IEcoTaskScheduler1* pIScheduler = 0;
    IEcoTask1* pITask1 = 0;
    IEcoTask1* pITask2 = 0;
    IEcoTask1* pITask3 = 0;
    /* Указатель на интерфейс для работы c буфером кадров видеоустройства */
    IEcoVFB1* pIVFB = 0;
    ECO_VFB_1_SCREEN_MODE xScreenMode = {0};
    IEcoVBIOS1Video* pIVideo = 0;
    /* Указатель на интерфейс для работы c системным таймером */
    IEcoSystemTimer1* pISysTimer = 0;
    /* Указатель на интерфейс для работы c таймером */
    IEcoTimer1* pITimer = 0;

    /* Создание экземпляра интерфейсной шины */
    result = GetIEcoComponentFactoryPtr_00000000000000000000000042757331->pVTbl->Alloc(GetIEcoComponentFactoryPtr_00000000000000000000000042757331, 0, 0, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    /* Проверка */
    if (result != 0 && pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с памятью */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoMemoryManager1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_0000000000000000000000004D656D31);
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoMemoryManager1Lab, (IEcoUnknown*)GetIEcoComponentFactoryPtr_81589BFED0B84B1194524BEE623E1838);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с ящиком прошивки */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoIPCCMailbox1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_F10BC39A4F2143CF8A1E104650A2C302);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Запрос расширения интерфейсной шины */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        /* Установка расширения менаджера памяти */
        pIMemExt->pVTbl->set_Manager(pIMemExt, &CID_EcoMemoryManager1);
        //pIMemExt->pVTbl->set_Manager(pIMemExt, &CID_EcoMemoryManager1Lab);
        /* Установка разрешения расширения пула */
        pIMemExt->pVTbl->set_ExpandPool(pIMemExt, 1);
    }

    /* Получение интерфейса управления памятью */
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryManager1, (void**) &pIMemMgr);
    //pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1Lab, 0, &IID_IEcoMemoryManager1, (void**) &pIMemMgr);
    if (result != 0 || pIMemMgr == 0) {
        /* Возврат в случае ошибки */
        return result;
    }

    /* Выделение области памяти 512 КБ */
    pIMemMgr->pVTbl->Init(pIMemMgr, &__heap_start__, 0x080000);

    /* Получение интерфейса для работы с виртуальной памятью */
    result = pIMemMgr->pVTbl->QueryInterface(pIMemMgr, &IID_IEcoVirtualMemory1, (void**)&pIVrtMem);
    if (result == 0 && pIVrtMem != 0) {
        /* Инициализация виртуальной памяти */
        result = pIVrtMem->pVTbl->Init(pIVrtMem);
        /* TO DO */
    }
    /* Регистрация статического компонента для работы с планировщиком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoTaskScheduler1Lab, (IEcoUnknown*)GetIEcoComponentFactoryPtr_902ABA722D34417BB714322CC761620F);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с таймером */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoTimer1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_8DB93F3DF5B947D4A67F7C100B569723);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с VBF */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoVFB1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_939B1DCDB6404F7D9C072291AF252188);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с мьютекс */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoMutex1Lab, (IEcoUnknown*)GetIEcoComponentFactoryPtr_2F48BBCBE4884CC08ECFC45990017215);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с семафор */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoSemaphore1Lab, (IEcoUnknown*)GetIEcoComponentFactoryPtr_0741985B8FD0476C867CAE177CD26E7C);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса для работы с планировщиком */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoTaskScheduler1Lab, 0, &IID_IEcoTaskScheduler1, (void**) &pIScheduler);
    /* Проверка */
    if (result != 0 || pIScheduler == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Инициализация */
    pIScheduler->pVTbl->InitWith(pIScheduler, pIBus, &__heap_start__+0x090000, 0x080000);

    /* Создание статических задач */
    pIScheduler->pVTbl->NewTask(pIScheduler, Task1, 0, 0x100, &pITask1);
    pIScheduler->pVTbl->NewTask(pIScheduler, Task2, 0, 0x100, &pITask2);
    pIScheduler->pVTbl->NewTask(pIScheduler, Task3, 0, 0x100, &pITask3);

    /* Получение интерфейса для работы с мьютекс */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMutex1Lab, 0, &IID_IEcoMutex1, (void**) &g_pIMutex);
    /* Проверка */
    if (result != 0 || g_pIMutex == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса для работы с семафор */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoSemaphore1Lab, 0, &IID_IEcoSemaphore1, (void**) &g_pISemaphore);
    /* Проверка */
    if (result != 0 || g_pISemaphore == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса для работы с системным таймером */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoTimer1, 0, &IID_IEcoSystemTimer1, (void**) &pISysTimer);
    /* Проверка */
    if (result != 0 || pISysTimer == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    g_pISysTimer = pISysTimer;
    g_t0 = g_pISysTimer->pVTbl->get_SingleTimerCounter(g_pISysTimer);


    /* Установка обработчика прерывания программируемого таймера */
    result = pISysTimer->pVTbl->QueryInterface(pISysTimer, &IID_IEcoTimer1, (void**)&pITimer);
    /* Проверка */
    if (result != 0 || pITimer == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    pITimer->pVTbl->set_Interval(pITimer, 100000);
    pITimer->pVTbl->set_IrqHandler(pITimer, TimerHandler);
    pITimer->pVTbl->Start(pITimer);

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoVFB1, 0, &IID_IEcoVFB1, (void**) &pIVFB);
    if (result != 0 || pIVFB == 0) {
        goto Release;
    }

    result = pIVFB->pVTbl->get_Mode(pIVFB, &xScreenMode);
    pIVFB->pVTbl->Create(pIVFB, 0, 0, xScreenMode.Width, xScreenMode.Height);
    result = pIVFB->pVTbl->QueryInterface(pIVFB, &IID_IEcoVBIOS1Video, (void**) &pIVideo);

    g_pIVideo = pIVideo;
    pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 7, CHARACTER_ATTRIBUTE_FORE_COLOR_YELLOW, "Timeline: [T1][T2][T3]", 22);

    pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 10, 8, CHARACTER_ATTRIBUTE_FORE_COLOR_YELLOW,
        "............................................................", 60);

    pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 10 + SEG_LEN - 1, 8, CHARACTER_ATTRIBUTE_FORE_COLOR_YELLOW, "|", 1);
    pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 10 + 2*SEG_LEN - 1, 8, CHARACTER_ATTRIBUTE_FORE_COLOR_YELLOW, "|", 1);


    pIScheduler->pVTbl->Start(pIScheduler);

    while(1) {
        asm volatile ("NOP\n\t" ::: "memory");
    }

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение интерфейса VFB */
    if (pIVFB != 0) {
        pIVFB->pVTbl->Release(pIVFB);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

