#ifndef ENTT_CORE_TYPE_INFO_HPP
#define ENTT_CORE_TYPE_INFO_HPP


#include "../config/config.h"
#include "hashed_string.hpp"


namespace entt {


/**
 * @brief Types identifiers.
 * @tparam Type Type for which to generate an identifier.
 */
template<typename Type, typename = void>
struct type_info {
    /**
     * @brief Returns the numeric representation of a given type.
     * @return The numeric representation of the given type.
     */
#if defined _MSC_VER
    static constexpr ENTT_ID_TYPE id() ENTT_NOEXCEPT {
        return entt::hashed_string{__FUNCSIG__};
    }
#elif defined __GNUC__
    static constexpr ENTT_ID_TYPE id() ENTT_NOEXCEPT {
        return entt::hashed_string{__PRETTY_FUNCTION__};
    }
#else
    static ENTT_ID_TYPE id() ENTT_NOEXCEPT;
};


/**
 * @cond TURN_OFF_DOXYGEN
 * Internal details not to be documented.
 */


namespace internal {


struct type_id_generator {
    static ENTT_ID_TYPE next() ENTT_NOEXCEPT {
        static ENTT_ID_TYPE value{};
        return value++;
    }
};


}


/**
 * Internal details not to be documented.
 * @endcond TURN_OFF_DOXYGEN
 */


template<typename Type, typename Cond>
ENTT_ID_TYPE type_info<Type, Cond>::id() ENTT_NOEXCEPT {
    static const ENTT_ID_TYPE value = internal::type_id_generator::next();
    return value;
#endif
};


}


#endif