/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoTask1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейсов IEcoTask1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_TASK_1_H__
#define __I_ECO_TASK_1_H__

#include "IEcoBase1.h"

/* IEcoTask1 IID = {81A466F4-C275-40B1-B33D-0661E5470F1B} */
#ifndef __IID_IEcoTask1
static const UGUID IID_IEcoTask1 = { 0x01, 0x10, {0x81, 0xa4, 0x66, 0xf4, 0xc2, 0x75, 0x40, 0xb1, 0xb3, 0x3d, 0x6, 0x61, 0xe5, 0x47, 0xf, 0x1b} };
#endif /* __IID_IEcoTask1 */

typedef struct IEcoTask1* IEcoTask1Ptr_t;

typedef struct IEcoTask1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface )(/* in */ IEcoTask1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef )(/* in */ IEcoTask1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release )(/* in */ IEcoTask1Ptr_t me);

    /* IEcoTask1 */

    /* <метод>
     *   Delay
     * </метод>
     * <описание>
     *   Блокировка задачи на заданный интервал времени
     * </описание>
     */
    int16_t (ECOCALLMETHOD *Delay)(/*in*/ IEcoTask1Ptr_t me, /*in*/ double_t milliseconds);

    /* <метод>
     *   Yield
     * </метод>
     * <описание>
     *   Передать выполнение другой задачи
     * </описание>
     */
    int16_t (ECOCALLMETHOD *Yield)(/*in*/ IEcoTask1Ptr_t me);

} IEcoTask1VTbl, *IEcoTask1VTblPtr;

interface IEcoTask1 {
    struct IEcoTask1VTbl *pVTbl;
} IEcoTask1;

#endif /* __I_ECO_TASK_1_H__ */
