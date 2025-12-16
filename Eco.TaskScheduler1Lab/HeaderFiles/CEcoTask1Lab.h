/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoTask1Lab
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoTask1Lab
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_TASK_1_LAB_H__
#define __C_ECO_TASK_1_LAB_H__

#include "IEcoTaskScheduler1.h"
#include "IEcoSystem1.h"

/* Определение структуры задачи */
typedef struct CEcoTask1Lab_C761620F {
    /* Таблица функций интерфейса IEcoTask1 */
    IEcoTask1VTbl* m_pVTblITask;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Стэк */
    volatile byte_t* m_sp;

    /* Данные экземпляра */
    void (*pfunc) (void);

} CEcoTask1Lab_C761620F, *CEcoTask1Lab_C761620F_Ptr;

#endif /* __C_ECO_TASK_1_LAB_H__ */
