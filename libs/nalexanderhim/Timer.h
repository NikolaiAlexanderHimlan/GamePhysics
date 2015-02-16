#ifndef Timer_h__
#define Timer_h__

#if __cplusplus < 201103L && (!defined(_MSC_VER) || _MSC_VER < 1700)
#error Timer class requires C++11 support
#else

//Timer class from: https://www.daniweb.com/software-development/cpp/code/445750/simple-timer-using-c-11s-chrono-library#post1921920
//Chrono tutorial: http://www.informit.com/articles/article.aspx?p=1881386&seqNum=2
//Chrono documentation: http://www.cplusplus.com/reference/chrono/

#include <chrono>

#include "Defines.h"

class Timer {
	typedef std::chrono::high_resolution_clock high_resolution_clock;
	typedef std::chrono::milliseconds timescale;
	typedef std::chrono::duration<Time> timeSec;

	const Time TO_SECONDS_FACTOR = 1.0 / 1000.0;//TODO: calculate factor based on timescale
public:
	explicit Timer(bool run = false)
	{
		if (run)
			Reset();
	}

	inline void Reset()
	{
		_start = high_resolution_clock::now();
	}

	inline timescale Elapsed() const
	{
		return std::chrono::duration_cast<timescale>(high_resolution_clock::now() - _start);
	}
	Time ElapsedSeconds() const
	{
		//return TO_SECONDS_FACTOR * Elapsed().count();

		return std::chrono::duration_cast<timeSec>(high_resolution_clock::now() - _start).count();
	}

	template <typename T, typename Traits>
	friend std::basic_ostream<T, Traits>& operator<<(std::basic_ostream<T, Traits>& out, const Timer& timer)
	{
		return out << timer.Elapsed().count();
	}
private:
	high_resolution_clock::time_point _start;
};
#endif
#endif // Timer_h__
