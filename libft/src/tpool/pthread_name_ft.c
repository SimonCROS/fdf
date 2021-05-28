#include "private/use_gnu.h"
#include <pthread.h>

#if defined __APPLE__
int	pthread_setname_ft(char *name)
{
	return (pthread_setname_np(name));
}

int	pthread_getname_ft(char *name, size_t buffer_len)
{
	return (pthread_getname_np(pthread_self(), name, buffer_len));
}

#elif defined __linux__
int	pthread_setname_ft(char *name)
{
	return (pthread_setname_np(pthread_self(), name));
}

int	pthread_getname_ft(char *name, size_t buffer_len)
{
	return (pthread_getname_np(pthread_self(), name, buffer_len));
}
#endif
