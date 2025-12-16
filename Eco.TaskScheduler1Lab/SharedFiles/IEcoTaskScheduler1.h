/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoTaskScheduler1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoTaskScheduler1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_TASK_SCHEDULER_1_H__
#define __I_ECO_TASK_SCHEDULER_1_H__

#include "IEcoBase1.h"
#include "IEcoMemoryAllocator1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoTask1.h"

/* IEcoTaskScheduler1 IID = {29B5D3D7-C692-4DB7-BA3E-1D11B08B6C7F} */
#ifndef __IID_IEcoTaskScheduler1
static const UGUID IID_IEcoTaskScheduler1 = {0x01, 0x10, {0x29, 0xB5, 0xD3, 0xD7, 0xC6, 0x92, 0x4D, 0xB7, 0xBA, 0x3E, 0x1D, 0x11, 0xB0, 0x8B, 0x6C, 0x7F}};
#endif /* __IID_IEcoTaskScheduler1 */

typedef struct IEcoTaskScheduler1* IEcoTaskScheduler1Ptr_t;

typedef struct IEcoTaskScheduler1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoTaskScheduler1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoTaskScheduler1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoTaskScheduler1Ptr_t me);

    /* IEcoTaskScheduler1 */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ IEcoInterfaceBus1Ptr_t pIBus);
    int16_t (ECOCALLMETHOD *InitWith)(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ IEcoInterfaceBus1Ptr_t pIBus, /*in*/ voidptr_t heapStartAddress, /*in*/ uint32_t size);
    int16_t (ECOCALLMETHOD *NewTask)(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ voidptr_t address, /*in*/ voidptr_t data, /*in*/ uint32_t stackSize, /* out */ IEcoTask1** ppITask);
    int16_t (ECOCALLMETHOD *DeleteTask)(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ uint16_t taskId);
    int16_t (ECOCALLMETHOD *SuspendTask)(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ uint16_t taskId);
    int16_t (ECOCALLMETHOD *ResumeTask)(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ uint16_t taskId);
    int16_t (ECOCALLMETHOD *RegisterInterrupt)(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ uint16_t number, /*in*/ voidptr_t handlerAddress, /*in*/ int32_t flag);
    int16_t (ECOCALLMETHOD *UnRegisterInterrupt)(/*in*/ IEcoTaskScheduler1Ptr_t me, /*in*/ uint16_t number);
    int16_t (ECOCALLMETHOD *Start)(/*in*/ IEcoTaskScheduler1Ptr_t me);
    int16_t (ECOCALLMETHOD *Stop)(/*in*/ IEcoTaskScheduler1Ptr_t me);

} IEcoTaskScheduler1VTbl, *IEcoTaskScheduler1VTblPtr;

interface IEcoTaskScheduler1 {
    struct IEcoTaskScheduler1VTbl *pVTbl;
} IEcoTaskScheduler1;

#endif /* __I_ECO_TASK_SCHEDULER_1_H__ */
