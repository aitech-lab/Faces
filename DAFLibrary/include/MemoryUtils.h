#pragma once

template <typename T>
inline T** fdCreate2DTable(unsigned int w, unsigned int h, bool clear_table = false)
{
	T **object = new T*[w];
	for (unsigned int i=0; i<w; i++)
	{
		object[i] = new T[h];
		if (clear_table)
			memset(object[i], 0, sizeof(T)*h);
	}
	return object;
}

template <typename T>
inline void fdDestroyObject(T **object)
{
	if (*object!=NULL)
	{
		delete *object;
		*object = NULL;
	}
}

template <typename T>
inline void fdDestroyTable(T **object)
{
	if (*object!=NULL)
	{
		delete [](*object);
		*object = NULL;
	}
}

template <typename T>
inline void fdDestroy2DTable(T ***object, int w)
{
	if (*object!=NULL)
	{
		for (int i=0; i<w; i++)
			delete []((*object)[i]);
		delete [](*object);
		*object = NULL;
	}
}
