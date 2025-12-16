/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoTaskScheduler1Lab
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoTaskScheduler1Lab
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_TASK_SCHEDULER_1_LAB_H__
#define __C_ECO_TASK_SCHEDULER_1_LAB_H__

#include "IEcoTaskScheduler1.h"
#include "CEcoTask1Lab.h"
#include "IEcoSystem1.h"
#include "IdEcoTimer1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoTaskScheduler1Lab_C761620F {

    /* Таблица функций интерфейса IEcoTaskScheduler1Lab */
    IEcoTaskScheduler1VTbl* m_pVTblIScheduler;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейсная Шина */
    IEcoInterfaceBus1* m_pIBus;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    IEcoTimer1Ptr_t m_pIArmTimer;
    CEcoTask1Lab_C761620F* m_pTaskList;

} CEcoTaskScheduler1Lab_C761620F, *CEcoTaskScheduler1Lab_C761620FPtr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoTaskScheduler1Lab_C761620F(/*in*/ IEcoTaskScheduler1Ptr_t me, /* in */ IEcoUnknown* pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoTaskScheduler1Lab_C761620F(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoTaskScheduler1Ptr_t* ppITaskScheduler);
/* Удаление */
void ECOCALLMETHOD deleteCEcoTaskScheduler1Lab_C761620F(/* in */ IEcoTaskScheduler1Ptr_t pITaskScheduler);

#endif /* __C_ECO_TASK_SCHEDULER_1_LAB_H__ */
