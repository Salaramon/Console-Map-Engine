#pragma once

template<class T>
class Identity
{
public:
	Identity();
	static unsigned int getCount();

	template<class T>
	static unsigned int getID();
protected:
	unsigned int getID();

	enum class Mode{
		UNIQUE,
		RECYCLE
	};

private:
	unsigned int thisID;
	static unsigned int counter;
};

template<class T>
Identity<T>::Identity()
{
	thisID = counter;
	counter++;
}
