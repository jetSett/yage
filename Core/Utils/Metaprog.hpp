#ifndef METAPROG_HPP_INCLUDED
#define METAPROG_HPP_INCLUDED

#define TYPELIST_1(t1) TypeList<t1, NullType>
#define TYPELIST_2(t1, t2) TypeList<t1, TYPELIST_1(t2)>
#define TYPELIST_3(t1, t2, t3) TypeList<t1, TYPELIST_2(t2, t3)>
#define TYPELIST_4(t1, t2, t3, t4) TypeList<t1, TYPELIST_3(t2, t3, t4)>
#define TYPELIST_5(t1, t2, t3, t4, t5) TypeList<t1, TYPELIST_4(t2, t3, t4, t5)>
#define TYPELIST_6(t1, t2, t3, t4, t5, t6) TypeList<t1, TYPELIST_5(t2, t3, t4, t5, t6)>

template<class A, class B>
struct TypeList{
    typedef A Head;
    typedef B Tail;
};

struct NullType{};

template<class TList, template <class> class Handler> class ScatteredHierarchy;

template<class T1, class T2, template <class> class Handler>
class ScatteredHierarchy<TypeList<T1, T2>, Handler> : public Handler<T1>,
                                                      public ScatteredHierarchy<T2, Handler>{};

template<class T, template <class> class Handler>
class ScatteredHierarchy<TypeList<T, NullType>, Handler> : public Handler<T>{};

/// Use it to call a function with a tuple has arguments
/// How to use :
/// \example
/**
    double foo(int x, float y, double z){
        return x + y + z;
    }

    Executor<double, int, float, double> exe;
    exe.params = make_tuple(5, 5f, 5d);
    exe.func = foo;
    double ret = exe.call();
*/

template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };



template <class Ret, typename ...Args>
struct Executor
{
  std::tuple<Args...> params;
  Ret (*func)(Args...);

  Ret call()
  {
    assert(func != nullptr);
    return callFunc(typename gens<sizeof...(Args)>::type());
  }

  template<int ...S>
  Ret callFunc(seq<S...>)
  {
    return func(std::get<S>(params) ...);
  }
};

#endif // METAPROG_HPP_INCLUDED
