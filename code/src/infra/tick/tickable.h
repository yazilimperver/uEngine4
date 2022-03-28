#ifndef	TICKABLE
#define TICKABLE

class Tickable {
public:
	/* @brief Temel tetiklayici fonksiyon */
	virtual void Tick(double elapsedTimeInMsec) = 0;
};
#endif // !TICKABLE

