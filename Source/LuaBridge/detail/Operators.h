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


template<typename T,typename TRight,typename TRet, EOpType opType>
class FunOperator
{
public:
	template<EOpType> static TRet doOpMath(const T & a, const TRight & b){
		return TRet;
	}

	template<> static TRet doOpMath<EOp__add>(const T & a, const TRight & b) { return a + b; }
	template<> static TRet doOpMath<EOp__sub>(const T & a, const TRight & b) { return a - b; }
	template<> static TRet doOpMath<EOp__mul>(const T & a, const TRight & b) { return a * b; }
	template<> static TRet doOpMath<EOp__div>(const T & a, const TRight & b) { return a / b; }

	template<> static TRet doOpMath<EOp__eq>(const T & a, const TRight & b) { return a == b; }
	template<> static TRet doOpMath<EOp__lt>(const T & a, const TRight & b) { return a < b; }
	template<> static TRet doOpMath<EOp__le>(const T & a, const TRight & b) { return a <= b; }

	static int sOperatorFun(lua_State * L)
	{
		T a = Stack<T>::get(L, 1);
		TRight b = Stack<TRight>::get(L, 2);

		TRet ret = doOpMath<opType>(a, b);
		Stack <TRet>::push(L, ret);
		return 1;
	}
};

#endif
