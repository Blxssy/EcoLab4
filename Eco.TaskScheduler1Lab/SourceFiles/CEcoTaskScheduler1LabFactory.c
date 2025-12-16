/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoTaskScheduler1LabFactory
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию фабрики для компонента
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoTaskScheduler1Lab.h"
#include "CEcoTaskScheduler1LabFactory.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция возвращает указатель на интерфейс
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620FFactory_QueryInterface(IEcoComponentFactory* me, const UGUID* riid, void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoComponentFactory) ) {
        *ppv = me;
    }
    else {
        *ppv = 0;
        return -1;
    }
    ((IEcoUnknown*)(*ppv))->pVTbl->AddRef((IEcoUnknown*)*ppv);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция увеличивает количество ссылок на интерфейс
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620FFactory_AddRef(/* in */ IEcoComponentFactory* me) {
    CEcoTaskScheduler1Lab_C761620FFactory* pCMe = (CEcoTaskScheduler1Lab_C761620FFactory*)me;

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
 *   Функция уменьшает количество ссылок на интерфейс
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620FFactory_Release(/* in */ IEcoComponentFactory* me) {
    CEcoTaskScheduler1Lab_C761620FFactory* pCMe = (CEcoTaskScheduler1Lab_C761620FFactory*)me;

    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    atomicdecrement_int32_t(&pCMe->m_cRef);

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        //deleteCEcoTaskScheduler1Lab_C761620FFactory(&pCMe->m_VtblICF);
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
 *   Функция инициализирует компонент с параметрами
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620FFactory_Init(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pIUnkSystem, /* in */ void* pv) {
    CEcoTaskScheduler1Lab_C761620FFactory* pCMe = (CEcoTaskScheduler1Lab_C761620FFactory*)me;
    int16_t result = -1;

    if (me == 0 ) {
        return -1;
    }

    /* Инициализация компонента */
    result = pCMe->m_pInitInstance(pv, pIUnkSystem);

    return result;
}

/*
 *
 * <сводка>
 *   Функция Alloc
 * </сводка>
 *
 * <описание>
 *   Функция создает компонент
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620FFactory_Alloc(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pISystem, /* in */ struct IEcoUnknown *pIUnknownOuter, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoTaskScheduler1Lab_C761620FFactory* pCMe = (CEcoTaskScheduler1Lab_C761620FFactory*)me;
    IEcoUnknown* pIUnk = 0;
    int16_t result = -1;

    if (me == 0 ) {
        return -1;
    }

    /* Агрегирование при условии если IID это IID_IEcoUnknown */
    if ( ( pIUnknownOuter != 0 ) && !IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        /* не поддерживает агрегирование */
        return -1;
    }

    /* Создание компонента */
    result = pCMe->m_pInstance(pISystem, pIUnknownOuter, (void**)&pIUnk);
    if ( result != 0 || pIUnk == 0) {
        return -1;
    }

    /* Инициализация компонента */
    result = me->pVTbl->Init(me, pISystem, pIUnk);
	
    /* Получение указателя на интерфейс */
    result = pIUnk->pVTbl->QueryInterface(pIUnk, riid, ppv);

    /* Уменьшение ссылки запрошенной Фабрикой компонентов */
    pIUnk->pVTbl->Release(pIUnk);

    return result;
}

/*
 *
 * <сводка>
 *   Функция get_Name
 * </сводка>
 *
 * <описание>
 *   Функция возвращает наименование компонента
 * </описание>
 *
 */
static char_t* ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620FFactory_get_Name(/* in */ struct IEcoComponentFactory* me) {
    CEcoTaskScheduler1Lab_C761620FFactory* pCMe = (CEcoTaskScheduler1Lab_C761620FFactory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Name;
}

/*
 *
 * <сводка>
 *   Функция get_Version
 * </сводка>
 *
 * <описание>
 *   Функция возвращает версию компонента
 * </описание>
 *
 */
static char_t* ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620FFactory_get_Version(/* in */ struct IEcoComponentFactory* me) {
    CEcoTaskScheduler1Lab_C761620FFactory* pCMe = (CEcoTaskScheduler1Lab_C761620FFactory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Version;
}

/*
 *
 * <сводка>
 *   Функция get_Manufacturer
 * </сводка>
 *
 * <описание>
 *   Функция возвращает наименование производителя компонента
 * </описание>
 *
 */
static char_t* ECOCALLMETHOD CEcoTaskScheduler1Lab_C761620FFactory_get_Manufacturer(/* in */ struct IEcoComponentFactory* me) {
    CEcoTaskScheduler1Lab_C761620FFactory* pCMe = (CEcoTaskScheduler1Lab_C761620FFactory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Manufacturer;
}

/* Create Virtual Table */
IEcoComponentFactoryVTbl g_x902ABA722D34417BB714322CC761620FFactoryVTbl = {
    CEcoTaskScheduler1Lab_C761620FFactory_QueryInterface,
    CEcoTaskScheduler1Lab_C761620FFactory_AddRef,
    CEcoTaskScheduler1Lab_C761620FFactory_Release,
    CEcoTaskScheduler1Lab_C761620FFactory_Alloc,
    CEcoTaskScheduler1Lab_C761620FFactory_Init,
    CEcoTaskScheduler1Lab_C761620FFactory_get_Name,
    CEcoTaskScheduler1Lab_C761620FFactory_get_Version,
    CEcoTaskScheduler1Lab_C761620FFactory_get_Manufacturer
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
CEcoTaskScheduler1Lab_C761620FFactory g_x902ABA722D34417BB714322CC761620FFactory = {
    &g_x902ABA722D34417BB714322CC761620FFactoryVTbl,
    0,
    (CreateInstance)createCEcoTaskScheduler1Lab_C761620F,
    (InitInstance)initCEcoTaskScheduler1Lab_C761620F,
    "EcoTaskScheduler1Lab\0",
    "1.0.0.0\0",
    "CompanyName\0"
};

#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr() {
    return (IEcoComponentFactory*)&g_x902ABA722D34417BB714322CC761620FFactory;
};
#elif ECO_LIB
IEcoComponentFactory* GetIEcoComponentFactoryPtr_902ABA722D34417BB714322CC761620F = (IEcoComponentFactory*)&g_x902ABA722D34417BB714322CC761620FFactory;
#endif