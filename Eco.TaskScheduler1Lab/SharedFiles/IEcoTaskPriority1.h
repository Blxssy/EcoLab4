/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoTaskPriority1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейсов IEcoTaskPriority1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_TASK_1_PRIORITY_H__
#define __I_ECO_TASK_1_PRIORITY_H__

#include "IEcoBase1.h"

/* IEcoTaskPriority1 IID = {E1A32355-BC4C-428F-AF17-76CFCAE2C36E} */
#ifndef __IID_IEcoTaskPriority1
static const UGUID IID_IEcoTaskPriority1 = { 0x01, 0x10, {0xE1, 0xA3, 0x23, 0x55, 0xBC, 0x4C, 0x42, 0x8F, 0xAF, 0x17, 0x76, 0xCF, 0xCA, 0xE2, 0xC3, 0x6E} };
#endif /* __IID_IEcoTaskPriority1 */

typedef struct IEcoTaskPriority1* IEcoTaskPriority1Ptr_t;

typedef struct IEcoTaskPriority1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface )(/* in */ IEcoTaskPriority1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef )(/* in */ IEcoTaskPriority1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release )(/* in */ IEcoTaskPriority1Ptr_t me);

    /* IEcoTaskPriority1 */

} IEcoTaskPriority1VTbl, *IEcoTaskPriority1VTblPtr;

interface IEcoTaskPriority1 {
    struct IEcoTaskPriority1VTbl *pVTbl;
} IEcoTaskPriority1;

#endif /* __I_ECO_TASK_1_PRIORITY_H__ */
