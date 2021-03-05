#ifndef SINGLETON_INSTANCE_H
#define SINGLETON_INSTANCE_H

#define SingletonInstance(TYPE) \
	public: \
		static TYPE* instance() \
		{ \
			static TYPE instance; \
			return &instance; \
		} \
	private: \
		TYPE(TYPE const&); \
		TYPE& operator=(TYPE const&); \


#define SingInst(TYPE) TYPE::instance()
#endif