/*
 * <кодировка символов>
 *   Cyrillic (Windows) - Codepage 1251
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoTask1Lab
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoTask1Lab
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "CEcoTask1Lab.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoTask1Lab
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoTask1Lab_C761620F_QueryInterface(/* in */ IEcoTask1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv) {
    CEcoTask1Lab_C761620F* pCMe = (CEcoTask1Lab_C761620F*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoTask1) ) {
        *ppv = &pCMe->m_pVTblITask;
        pCMe->m_pVTblITask->AddRef((IEcoTask1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblITask;
        pCMe->m_pVTblITask->AddRef((IEcoTask1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoTask1Lab
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoTask1Lab_C761620F_AddRef(/* in */ IEcoTask1Ptr_t me) {
    CEcoTask1Lab_C761620F* pCMe = (CEcoTask1Lab_C761620F*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoTask1Lab
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoTask1Lab_C761620F_Release(/* in */ IEcoTask1Ptr_t me) {
    CEcoTask1Lab_C761620F* pCMe = (CEcoTask1Lab_C761620F*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Delay
 * </сводка>
 *
 * <описание>
 *   Функция Sleep для интерфейса IEcoTask1Lab
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoTask1Lab_C761620F_Delay(/*in*/ IEcoTask1Ptr_t me, /*in*/ double_t milliseconds) {
    /*CEcoTask1Lab_C761620F* pCMe = (CEcoTask1Lab_C761620F*)me;*/

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Yield
 * </сводка>
 *
 * <описание>
 *   Функция Sleep для интерфейса IEcoTask1Lab
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoTask1Lab_C761620F_Yield(/*in*/ IEcoTask1Ptr_t me) {
    /*CEcoTask1Lab_C761620F* pCMe = (CEcoTask1Lab_C761620F*)me;*/

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return 0;
}


/* Create Virtual Table IEcoTask1 */
IEcoTask1VTbl g_x81A466F4C27540B1B33D0661E5470F1BVTbl_C761620F = {
    CEcoTask1Lab_C761620F_QueryInterface,
    CEcoTask1Lab_C761620F_AddRef,
    CEcoTask1Lab_C761620F_Release,
    CEcoTask1Lab_C761620F_Delay,
    CEcoTask1Lab_C761620F_Yield
};

