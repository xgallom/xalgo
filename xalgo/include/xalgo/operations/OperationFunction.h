//
// Created by xgallom on 4/23/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONFUNCTION_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONFUNCTION_H

#include <vector>
#include <cstdint>

namespace Operations {
	namespace Function {
		using Empty = double();
		using EmptyInterface = double (*)();

		template<typename Parameter>
		using WithParameter = double(const Parameter *);
		using WithParameterInterface = double (*)(const void *);

		using Unary = double(double);
		using UnaryInterface = double (*)(double);

		template<typename Parameter>
		using UnaryWithParameter = double(double, const Parameter *);
		using UnaryWithParameterInterface = double (*)(double, const void *);

		using Binary = double(double, double);
		using BinaryInterface = double (*)(double, double);

		template<typename Parameter>
		using BinaryWithParameter = double(double, double, const Parameter *);
		using BinaryWithParameterInterface = double (*)(double, double, const void *);

		using Interface = void *;
	}

	namespace FunctionType {
		enum Enum : uint8_t {
			Empty = 0,
			WithParameter,
			Unary,
			UnaryWithParameter,
			Binary,
			BinaryWithParameter,

			Count
		};
	}

	namespace FunctionTypesDetail
	{
		enum Position {
			HighPosition = 0x00u,
			LowPosition = 0x01u
		};

		static constexpr uint8_t

				PositionMask = 0x01u,

				EnumMask = 0x0fu,
				EnumOffset = 4u;
	}

	class FunctionTypesIterator {
		const uint8_t *m_data = nullptr;
		uint8_t m_position = FunctionTypesDetail::HighPosition;

	public:
		explicit FunctionTypesIterator(
				const uint8_t *data,
				FunctionTypesDetail::Position position = FunctionTypesDetail::HighPosition
		) noexcept;

		FunctionTypesIterator() noexcept = default;
		FunctionTypesIterator(const FunctionTypesIterator &) noexcept = default;
		FunctionTypesIterator(FunctionTypesIterator &&) noexcept = default;

		FunctionTypesIterator &operator=(const FunctionTypesIterator &) noexcept = default;
		FunctionTypesIterator &operator=(FunctionTypesIterator &&) noexcept = default;

		void advance() noexcept;

		FunctionType::Enum operator++() noexcept;
		FunctionType::Enum operator++(int) noexcept;

		FunctionType::Enum operator--() noexcept;
		FunctionType::Enum operator--(int) noexcept;

		[[nodiscard]] FunctionType::Enum get() const noexcept;
		FunctionType::Enum operator*() const noexcept;
		explicit operator FunctionType::Enum() const noexcept;
	};

	class FunctionTypes {
		std::vector<uint8_t> m_data;
		uint8_t m_position = FunctionTypesDetail::LowPosition;

	public:
		[[nodiscard]] size_t byteSize() const noexcept;
		[[nodiscard]] size_t size() const noexcept;

		[[nodiscard]] FunctionTypesIterator begin() const noexcept;
		[[nodiscard]] FunctionTypesIterator end() const noexcept;

		void push_back(FunctionType::Enum value);

	private:
		[[nodiscard]] uint8_t *data() noexcept;
		[[nodiscard]] const uint8_t *data() const noexcept;
		uint8_t &lastByte() noexcept;
	};
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONFUNCTION_H
