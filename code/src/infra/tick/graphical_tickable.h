/**
 * @file graphical_tickable.h.
 * @date 27.03.2022
 * @author Yazilimperver
 * @brief  Girdi/guncellem ve goruntuleme tetikleyicileri icin kullanilacak arayuz sinif
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef GRAPHICAL_TICKABLE
#define GRAPHICAL_TICKABLE

class GraphicalTickable {
public:
	/* @brief Temel girdi tetiklayici fonksiyonu */
	virtual void Input(double elapsedTimeInMsec) = 0;

	/* @brief Temel guncelleme fonksiyonu */
	virtual void Update(double elapsedTimeInMsec) = 0;

	/* @brief Temel cizdirme tetikleyici fonksiyonu */
	virtual void Display(double elapsedTimeInMsec) = 0;
};

#endif // !GRAPHICAL_TICKABLE

