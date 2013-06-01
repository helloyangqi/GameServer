/*
 * Singleton.h
 *
 *  Created on: 2013-5-22
 *      Author: YangQi
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_


template <typename T>
class Singleton
{
public:
	static T* get_instance()
	{
		if(0 == s_instance)
			s_instance = new (T)();
		return s_instance;
	}
private:
	static T *s_instance;
};

#endif /* SINGLETON_H_ */
