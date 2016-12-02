//------------------------------------------------------------------------------
/*
  https://github.com/vinniefalco/LuaBridge

  Copyright 2012, Vinnie Falco <vinnie.falco@gmail.com>
  Copyright 2007, Nathan Reed

  License: The MIT License (http://www.opensource.org/licenses/mit-license.php)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
//==============================================================================

//------------------------------------------------------------------------------
/**
    Receive the lua_State* as an argument.
*/
template <>
struct Stack <lua_State*>
{
  static lua_State* get (lua_State* L, int)
  {
    return L;
  }
};

//------------------------------------------------------------------------------
/**
    Push a lua_CFunction.
*/
template <>
struct Stack <lua_CFunction>
{
  static void push (lua_State* L, lua_CFunction f)
  {
    lua_pushcfunction (L, f);
  }

  static lua_CFunction get (lua_State* L, int index)
  {
    return lua_tocfunction (L, index);
  }
};

//------------------------------------------------------------------------------
/**
    Stack specialization for `int`.
*/
template<typename T>
struct Stack_DefaultInt
{
	static inline void push(lua_State* L, T value)
	{
		lua_pushinteger(L, static_cast <lua_Integer> (value));
	}

	static inline T get(lua_State* L, int index)
	{
		return static_cast<int> (luaL_checkinteger(L, index));
	}
};

template<>struct Stack<int> : public Stack_DefaultInt<int> {};
template<>struct Stack<int const> : public Stack_DefaultInt<int> {};
template<>struct Stack<int const &> : public Stack_DefaultInt<int> {};

template<>struct Stack<unsigned int> : public Stack_DefaultInt<unsigned int> {};
template<>struct Stack<unsigned int const> : public Stack_DefaultInt<unsigned int> {};
template<>struct Stack<unsigned int const &> : public Stack_DefaultInt<unsigned int> {};

template<>struct Stack<char> : public Stack_DefaultInt<char> {};
template<>struct Stack<char const> : public Stack_DefaultInt<char> {};
template<>struct Stack<char const &> : public Stack_DefaultInt<char> {};

template<>struct Stack<unsigned char> : public Stack_DefaultInt<unsigned char> {};
template<>struct Stack<unsigned char const> : public Stack_DefaultInt<unsigned char> {};
template<>struct Stack<unsigned char const &> : public Stack_DefaultInt<unsigned char> {};

template<>struct Stack<short> : public Stack_DefaultInt<short> {};
template<>struct Stack<short const> : public Stack_DefaultInt<short> {};
template<>struct Stack<short const &> : public Stack_DefaultInt<short> {};

template<>struct Stack<unsigned short> : public Stack_DefaultInt<unsigned short> {};
template<>struct Stack<unsigned short const> : public Stack_DefaultInt<unsigned short> {};
template<>struct Stack<unsigned short const &> : public Stack_DefaultInt<unsigned short> {};

template<>struct Stack<long> : public Stack_DefaultInt<long> {};
template<>struct Stack<long const> : public Stack_DefaultInt<long> {};
template<>struct Stack<long const &> : public Stack_DefaultInt<long> {};

template<>struct Stack<unsigned long> : public Stack_DefaultInt<unsigned long> {};
template<>struct Stack<unsigned long const> : public Stack_DefaultInt<unsigned long> {};
template<>struct Stack<unsigned long const &> : public Stack_DefaultInt<unsigned long> {};

template<>struct Stack<long long> : public Stack_DefaultInt<long long> {};
template<>struct Stack<long long const> : public Stack_DefaultInt<long long> {};
template<>struct Stack<long long const &> : public Stack_DefaultInt<long long> {};

template<>struct Stack<unsigned long long> : public Stack_DefaultInt<unsigned long long> {};
template<>struct Stack<unsigned long long const> : public Stack_DefaultInt<unsigned long long> {};
template<>struct Stack<unsigned long long const &> : public Stack_DefaultInt<unsigned long long> {};


template <typename T>
struct Stack_DefaultFloat
{
	static inline void push(lua_State* L, T value)
	{
		lua_pushnumber(L, static_cast <lua_Number> (value));
	}

	static inline T get(lua_State* L, int index)
	{
		return static_cast <T> (luaL_checknumber(L, index));
	}
};

template <>	struct Stack <float> :public Stack_DefaultFloat<float> {};
template <>	struct Stack <float const> :public Stack_DefaultFloat<float> {};
template <>	struct Stack <float const &> :public Stack_DefaultFloat<float> {};

template <>	struct Stack <double> :public Stack_DefaultFloat<double> {};
template <>	struct Stack <double const> :public Stack_DefaultFloat<double> {};
template <>	struct Stack <double const &> :public Stack_DefaultFloat<double> {};

//------------------------------------------------------------------------------
/**
    Stack specialization for `bool`.
*/


struct Stack_DefaultBool {
  static inline void push (lua_State* L, bool value)
  {
		lua_pushboolean (L, value ? 1 : 0);
  }
  
  static inline bool get (lua_State* L, int index)
  {
    return lua_toboolean (L, index) ? true : false;
  }
};

template<> struct Stack<bool> : public Stack_DefaultBool{};
template<> struct Stack<bool const> : public Stack_DefaultBool{};
template<> struct Stack<bool const &> : public Stack_DefaultBool{};

//------------------------------------------------------------------------------
/**
    Stack specialization for `float`.
*/
struct Stack_DefaultSzChar
{
  static inline void push (lua_State* L, char const* str)
  {
    if (str != 0)
      lua_pushstring (L, str);
    else
      lua_pushnil (L);
  }

  static inline char const* get (lua_State* L, int index)
  {
    return lua_isnil (L, index) ? 0 : luaL_checkstring (L, index);
  }
};


template<> struct Stack<char * > : public Stack_DefaultSzChar {};
template<> struct Stack<const char * > : public Stack_DefaultSzChar{};


struct Stack_stdstring
{
  static inline void push (lua_State* L, std::string const& str)
  {
    lua_pushlstring (L, str.c_str (), str.size());
  }

  static inline std::string get (lua_State* L, int index)
  {
    size_t len;
    const char *str = luaL_checklstring(L, index, &len);
    return std::string (str, len);
  }
};

//------------------------------------------------------------------------------
/**
    Stack specialization for `std::string const&`.
*/
template <>	struct Stack <std::string> : public Stack_stdstring {};
template <>	struct Stack <std::string const> : public Stack_stdstring {};
template <>	struct Stack <std::string const &> : public Stack_stdstring {};

