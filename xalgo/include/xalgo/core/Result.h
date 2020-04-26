//
// Created by xgallom on 4/25/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_CORE_RESULT_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_CORE_RESULT_H

#include <string>

namespace xalgo::core {
	template<typename T>
	class Result {
		bool m_valid = false;
		T m_value = {};

	public:
		Result() = default;
		Result(const Result &) = default;
		Result(Result &&) noexcept = default;

		Result &operator=(const Result &) = default;
		Result &operator=(Result &&) noexcept = default;

		~Result() = default;

		template<typename _T, typename std::enable_if_t<
		        std::is_trivially_copyable_v<_T> && std::is_same_v<T, _T>, bool> = true>
		Result(_T value) noexcept : m_valid{true}, m_value{value} {}
		template<typename _T, typename std::enable_if_t<
				!std::is_trivially_copyable_v<_T> && std::is_same_v<T, _T>, bool> = true>
		Result(_T &&value) noexcept : m_valid{true}, m_value{std::move(value)} {}

		[[nodiscard]] bool isValid() const noexcept { return m_valid; }
		explicit operator bool() const noexcept { return isValid(); }

		T &value() noexcept { return m_value; }
		const T &value() const noexcept { return m_value; }
		T &operator()() noexcept { return value(); }
		const T &operator()() const noexcept { return value(); }
	};
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_CORE_RESULT_H
