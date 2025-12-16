/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoTaskScheduler1Lab
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoTaskScheduler1Lab
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

#ifndef __ID_ECO_TASK_SCHEDULER_1_LAB_H__
#define __ID_ECO_TASK_SCHEDULER_1_LAB_H__

#include "IEcoBase1.h"
#include "IEcoTaskScheduler1.h"

/* EcoTaskScheduler1Lab CID = {902ABA72-2D34-417B-B714-322CC761620F} */
#ifndef __CID_EcoTaskScheduler1Lab
static const UGUID CID_EcoTaskScheduler1Lab = {0x01, 0x10, {0x90, 0x2A, 0xBA, 0x72, 0x2D, 0x34, 0x41, 0x7B, 0xB7, 0x14, 0x32, 0x2C, 0xC7, 0x61, 0x62, 0x0F} };
#endif /* __CID_EcoTaskScheduler1Lab */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_902ABA722D34417BB714322CC761620F;
#endif

#endif /* __ID_ECO_TASK_SCHEDULER_1_LAB_H__ */
