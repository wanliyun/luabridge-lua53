#ifndef LUA_BRIDGE_OPERATORS
#define LUA_BRIDGE_OPERATORS

enum EOpType
{
	EOp__add	 ,
	EOp__sub	 ,
	EOp__mul	 ,
	EOp__div	 ,
	EOp__mod	 ,
	EOp__pow	 ,
	EOp__unm	 ,
	EOp__idiv	 ,
	EOp__band	 ,
	EOp__bor	 ,
	EOp__bxor	 ,
	EOp__bnot	 ,
	EOp__shl	 ,
	EOp__shr	 ,
	EOp__concat	 ,
	EOp__len	 ,
	EOp__eq		 ,
	EOp__lt		 ,
	EOp__le		 ,
};


template<typename T, typename TRight, typename TRet, EOpType opType>
class FunOperatorImplement
{
public:
	static TRet doOpMath(const T & a, const TRight & b)
	{
		assert(false);
	}
};

template<typename T, typename TRight, typename TRet>
class FunOperatorImplement<T,TRight,TRet,EOp__add>
{
public:
	static TRet doOpMath(const T & a, const TRight & b)
	{
		return a + b;
	}
};

template<typename T, typename TRight, typename TRet>
class FunOperatorImplement<T, TRight, TRet, EOp__sub>
{
public:
	static TRet doOpMath(const T & a, const TRight & b)
	{
		return a - b;
	}
};


template<typename T, typename TRight, typename TRet>
class FunOperatorImplement<T, TRight, TRet, EOp__mul>
{
public:
	static TRet doOpMath(const T & a, const TRight & b)
	{
		return a * b;
	}
};


template<typename T, typename TRight, typename TRet>
class FunOperatorImplement<T, TRight, TRet, EOp__div>
{
public:
	static TRet doOpMath(const T & a, const TRight & b)
	{
		return a / b;
	}
};

template<typename T, typename TRight, typename TRet>
class FunOperatorImplement<T, TRight, TRet, EOp__eq>
{
public:
	static TRet doOpMath(const T & a, const TRight & b)
	{
		return a == b;
	}
};

template<typename T, typename TRight, typename TRet>
class FunOperatorImplement<T, TRight, TRet, EOp__lt>
{
public:
	static TRet doOpMath(const T & a, const TRight & b)
	{
		return a < b;
	}
};


template<typename T, typename TRight, typename TRet>
class FunOperatorImplement<T, TRight, TRet, EOp__le>
{
public:
	static TRet doOpMath(const T & a, const TRight & b)
	{
		return a <= b;
	}
};

template<typename T,typename TRight,typename TRet, EOpType opType>
class FunOperator
{
public:
	static int sOperatorFun(lua_State * L)
	{
		T a = Stack<T>::get(L, 1);
		TRight b = Stack<TRight>::get(L, 2);

		TRet ret = FunOperatorImplement<T, TRight, TRet, opType>::doOpMath(a, b);
		Stack <TRet>::push(L, ret);
		return 1;
	}
};

#endif
