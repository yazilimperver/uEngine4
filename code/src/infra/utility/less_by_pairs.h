/**
 * @file less_by_pairs.h.
 * @date 3.07.2022
 * @author Yazilimperver
 * @brief  Karmasik veri yapilarini map ve benzeri konteynerlerde kullanmak icin kullanailabilecek bir karsilastirma yardimcisi
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef LESS_BY_PAIRS_H
#define LESS_BY_PAIRS_H

bool LessByPairs();

template <typename T, typename U, typename ...Args>
bool LessByPairs(const T& v1, const U& v2, Args... args) {
	return v1 != v2 ? v1 < v2 : LessByPairs(args...);
}

#endif // LESS_BY_PAIRS_H
