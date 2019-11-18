#ifndef DEFER_ACTION_H
#define DEFER_ACTION_H

#define UTIL_NOEXCEPT_RETURN(...) \
    noexcept(noexcept(__VA_ARGS__)) { return __VA_ARGS__; }

#define UTIL_NOEXCEPT_DECLTYPE_RETURN(...) \
    noexcept(noexcept(__VA_ARGS__)) -> decltype (__VA_ARGS__) { return __VA_ARGS__; }

#define UTIL_PP_CAT_IMPL(x, y) x##y
#define UTIL_PP_CAT(x, y) UTIL_PP_CAT_IMPL(x, y)

#include <utility>
#include <type_traits>

namespace playground_hpp::defer
{
    namespace detail
    {
        template < typename F >
        class defer_impl {
        public:
            explicit defer_impl(F f)
            : f_(std::move(f))  {}

            defer_impl(const defer_impl&) = delete;
            defer_impl& operator=(const defer_impl&) = delete;

            ~defer_impl() noexcept {
                if ( !cancelled_ ) {
                    f_();
                }
            }

            void cancel() noexcept {
                cancelled_ = true;
            }
        private:
            F f_;
            bool cancelled_{false};
        };
    }

    template < typename F >
    detail::defer_impl<std::decay_t<F>> make_defer(F&& f) {
        return detail::defer_impl<std::decay_t<F>>(std::forward<F>(f));
    }
}

#define DEFER(lambda)\
    ::playground_hpp::defer::detail::defer_impl UTIL_PP_CAT(util_auto_defer_,__LINE__){lambda};

#endif // DEFER_ACTION_H
