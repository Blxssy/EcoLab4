/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoTaskScheduler1Lab_C761620F
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoTaskScheduler1Lab_C761620F
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoTaskScheduler1Lab.h"
#include "CEcoTask1Lab.h"

/* Выделяем память под один экземпляр */
CEcoTaskScheduler1Lab_C761620F g_xCEcoTaskScheduler1Lab_C761620F = {0};

/* Резервируем область под статические задачи */
#define MAX_STATIC_TASK_COUNT   3
CEcoTask1Lab_C761620F g_xCEcoTask1List_C761620F[MAX_STATIC_TASK_COUNT] = {0};

/* Резервируем область под стеки статических задач */
#define MAX_STATIC_STACK_TASK_COUNT   4096 * MAX_STATIC_TASK_COUNT
uint64_t g_xCEcoStackTask1List_C761620F[MAX_STATIC_STACK_TASK_COUNT] = {0};

/* Контекст */
uint64_t * volatile g_pxCurrentTCB_C761620F = 0;

uint64_t g_indx = 0;

static uint32_t g_ready_q[MAX_STATIC_TASK_COUNT];
static uint32_t g_q_head = 0;
static uint32_t g_q_tail = 0;
static uint32_t g_q_count = 0;

static void ready_reset(void) {
    g_q_head = 0;
    g_q_tail = 0;
    g_q_count = 0;
}

static void ready_push(uint32_t idx) {
    if (g_q_count < MAX_STATIC_TASK_COUNT) {
        g_ready_q[g_q_tail] = idx;
        g_q_tail = (g_q_tail + 1) % MAX_STATIC_TASK_COUNT;
        g_q_count++;
    }
}

static int32_t ready_pop(void) {
    uint32_t idx;
    if (g_q_count == 0) {
        return -1;
    }
    idx = g_ready_q[g_q_head];
    g_q_head = (g_q_head + 1) % MAX_STATIC_TASK_COUNT;
    g_q_count--;
    return (int32_t)idx;
}

/*
 *
 * <сводка>
 *   Функция TaskSwitchContext
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */

/*__attribute__((naked))*/ void CEcoTaskScheduler1Lab_C761620F_TaskSwitchContext( void ) {

        //if (g_pxCurrentTCB_C761620F == (uint64_t*)&g_xCEcoTask1List_C761620F[g_indx] && g_xCEcoTask1List_C761620F[g_indx].pfunc != 0) {
            g_indx++;
            if (g_indx > 1) {
                g_indx = 0;
            }

          //  g_pxCurrentTCB_C761620F = (uint64_t*)&g_xCEcoTask1List_C761620F[g_indx];
        //}

   // g_xCEcoTaskScheduler1Lab_C761620F.m_pIArmTimer->pVTbl->Reset(g_xCEcoTaskScheduler1Lab_C761620F.m_pIArmTimer);
    g_xCEcoTask1List_C761620F[g_indx].pfunc();
}

/*
 *
 * <сводка>
 *   Функция TimerHandler
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void CEcoTaskScheduler1Lab_C761620F_TimerHandler(void) {
    asm volatile ("NOP\n\t" ::: "memory");
}



/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoTaskScheduler1Lab
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620F_QueryInterface(/* in */ IEcoTaskScheduler1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoTaskScheduler1) ) {
        *ppv = &pCMe->m_pVTblIScheduler;
        pCMe->m_pVTblIScheduler->AddRef((IEcoTaskScheduler1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIScheduler;
        pCMe->m_pVTblIScheduler->AddRef((IEcoTaskScheduler1*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoTaskScheduler1Lab
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620F_AddRef(/* in */ IEcoTaskScheduler1Ptr_t me) {
    CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return atomicincrement_int32_t(&pCMe->m_cRef);
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoTaskScheduler1Lab
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620F_Release(/* in */ IEcoTaskScheduler1Ptr_t me) {
    CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    atomicdecrement_int32_t(&pCMe->m_cRef);

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoTaskScheduler1Lab_C761620F((IEcoTaskScheduler1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620F_Init(/*in*/IEcoTaskScheduler1Ptr_t me, /*in*/ IEcoInterfaceBus1Ptr_t pIBus) {
    /*CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;*/

    /* Проверка указателей */
    if (me == 0 || pIBus == 0) {
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция InitWith
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620F_InitWith(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ IEcoInterfaceBus1Ptr_t pIBus, /*in*/ voidptr_t heapStartAddress, /*in*/ uint32_t size) {
    CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || pIBus == 0) {
        return -1;
    }

    /* Инициализация данных */
    pCMe->m_pTaskList = g_xCEcoTask1List_C761620F;
    pCMe->m_pIBus = pIBus;

    /* FCFS: сброс очереди готовых задач и индекса */
    ready_reset();
    g_indx = 0;
    g_pxCurrentTCB_C761620F = 0;

    /* Получение интерфейса для работы с программируемым таймером */
    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoTimer1, 0, &IID_IEcoTimer1, (void**) &pCMe->m_pIArmTimer);
    /* Проверка */
    if (result != 0 || pCMe->m_pIArmTimer == 0) {
        return result;
    }

    /* Установка обработчика прерывания программируемого таймера */
    pCMe->m_pIArmTimer->pVTbl->set_Interval(pCMe->m_pIArmTimer, 1000000);
    pCMe->m_pIArmTimer->pVTbl->set_IrqHandler(pCMe->m_pIArmTimer, (voidptr_t*)CEcoTaskScheduler1Lab_C761620F_TimerHandler);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция NewTask
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620F_NewTask(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ voidptr_t address, /*in*/ voidptr_t data, /*in*/ uint32_t stackSize, /* out */ IEcoTask1** ppITask) {
    /*CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;*/
    int32_t indx = 0;
    int32_t reg = 30;
    uint64_t* pxTopOfStack = 0;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    /* Проверяем указатель пула статических задач */
    for (indx = 0; indx < 3; indx++) {
        if (g_xCEcoTask1List_C761620F[indx].pfunc == 0) {
            g_xCEcoTask1List_C761620F[indx].pfunc = address;
            g_xCEcoTask1List_C761620F[indx].m_cRef = 1;
            g_xCEcoTask1List_C761620F[indx].m_sp = (byte_t*)&g_xCEcoStackTask1List_C761620F[indx*4096];
            pxTopOfStack = g_xCEcoTask1List_C761620F[indx].m_sp;
            while (reg > 0) {
                pxTopOfStack--;
                reg--;
            }
            *pxTopOfStack = (uint64_t)g_xCEcoTask1List_C761620F[indx].pfunc;
            *ppITask = (IEcoTask1*)&g_xCEcoTask1List_C761620F[indx];
            ready_push((uint32_t)indx);
return 0;
            break;
        }
    }
    return -1;
}

/*
 *
 * <сводка>
 *   Функция DeleteTask
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620F_DeleteTask(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ uint16_t taskId) {
    /*CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;*/

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция SuspendTask
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620F_SuspendTask(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ uint16_t taskId) {
    /*CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;*/

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция ResumeTask
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620F_ResumeTask(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ uint16_t taskId) {
    /*CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;*/

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция RegisterInterrupt
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620F_RegisterInterrupt(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ uint16_t number, /*in*/ voidptr_t handlerAddress, /*in*/ int32_t flag) {
    /*CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;*/

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция UnRegisterInterrupt
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620F_UnRegisterInterrupt(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ uint16_t number) {
    /*CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;*/

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Start
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620F_Start(/*in*/ IEcoTaskScheduler1Ptr_t me) {
    CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;
    int32_t idx = -1;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    while (1) {
        idx = ready_pop();
        if (idx < 0) {
            /* Нет готовых задач — простаиваем */
            asm volatile ("NOP\n\t" ::: "memory");
            continue;
        }

        /* Текущая задача */
        g_pxCurrentTCB_C761620F = (uint64_t*)&pCMe->m_pTaskList[idx];

        if (pCMe->m_pTaskList[idx].pfunc != 0) {
            /* Выполняем задачу до завершения (возврата из функции) */
            pCMe->m_pTaskList[idx].pfunc();

            /* Чтобы задача не запускалась повторно */
            pCMe->m_pTaskList[idx].pfunc = 0;
        }
    }
}


/*
 *
 * <сводка>
 *   Функция Stop
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620F_Stop(/*in*/ struct IEcoTaskScheduler1* me) {
    /*CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;*/

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoTaskScheduler1Lab_C761620F(/*in*/ IEcoTaskScheduler1Ptr_t me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    /*CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)me;*/

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    return 0;
}

IEcoTaskScheduler1VTbl g_x155C975395654F85B9AA27D5F377A79EVTbl_C761620F = {
    CEcoTaskScheduler1Lab_C761620F_QueryInterface,
    CEcoTaskScheduler1Lab_C761620F_AddRef,
    CEcoTaskScheduler1Lab_C761620F_Release,
    CEcoTaskScheduler1Lab_C761620F_Init,
    CEcoTaskScheduler1Lab_C761620F_InitWith,
    CEcoTaskScheduler1Lab_C761620F_NewTask,
    CEcoTaskScheduler1Lab_C761620F_DeleteTask,
    CEcoTaskScheduler1Lab_C761620F_SuspendTask,
    CEcoTaskScheduler1Lab_C761620F_ResumeTask,
    CEcoTaskScheduler1Lab_C761620F_RegisterInterrupt,
    CEcoTaskScheduler1Lab_C761620F_UnRegisterInterrupt,
    CEcoTaskScheduler1Lab_C761620F_Start,
    CEcoTaskScheduler1Lab_C761620F_Stop
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoTaskScheduler1Lab_C761620F(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoTaskScheduler1Ptr_t* ppITaskScheduler) {
    int16_t result = -1;
    CEcoTaskScheduler1Lab_C761620F* pCMe = 0;

    /* Проверка указателей */
    if (ppITaskScheduler == 0) {
        return result;
    }

    /* Получение указателя на структуру компонента расположенной в области инициализированных данных */
    pCMe = &g_xCEcoTaskScheduler1Lab_C761620F;

    if (pCMe->m_cRef == 0) {
        /* Установка счетчика ссылок на компонент */
        pCMe->m_cRef = 1;

        /* Создание таблицы функций интерфейса IEcoTaskScheduler1 */
        pCMe->m_pVTblIScheduler = &g_x155C975395654F85B9AA27D5F377A79EVTbl_C761620F;

        result = 0;
    }

    /* Возврат указателя на интерфейс */
    *ppITaskScheduler = (IEcoTaskScheduler1*)pCMe;

    return result;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoTaskScheduler1Lab_C761620F(/* in */ IEcoTaskScheduler1Ptr_t pITaskScheduler) {
    /*CEcoTaskScheduler1Lab_C761620F* pCMe = (CEcoTaskScheduler1Lab_C761620F*)pITaskScheduler;*/

}
