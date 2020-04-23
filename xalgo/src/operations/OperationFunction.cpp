//
// Created by xgallom on 4/23/20.
//

#include <xalgo/operations/OperationFunction.h>

namespace Operations {
	size_t FunctionTypes::byteSize() const noexcept
	{
		return m_data.size();
	}

	size_t FunctionTypes::size() const noexcept
	{
		// Two per byte - 1 if high
		return (byteSize() << 1u) - (m_position ? 0 : 1);
	}

	FunctionTypesIterator FunctionTypes::begin() const noexcept
	{
		return FunctionTypesIterator(data());
	}

	FunctionTypesIterator FunctionTypes::end() const noexcept
	{
		// If LowPosition, return next HighPosition
		const uint8_t *dataEnd = data() + byteSize();
		FunctionTypesDetail::Position position = FunctionTypesDetail::HighPosition;

		if(!m_position) {
			// If HighPosition, return current LowPosition
			--dataEnd;
			position = FunctionTypesDetail::LowPosition;
		}

		return FunctionTypesIterator(dataEnd, position);
	}

	void FunctionTypes::push_back(FunctionType::Enum value)
	{
		if(m_position)
			// If LowPosition, add a byte
			m_data.push_back(uint8_t(value) << FunctionTypesDetail::EnumOffset);
		else
			// If HighPosition, set LowPosition
			lastByte() |= uint8_t(value);

		m_position ^= FunctionTypesDetail::PositionMask;
	}

	uint8_t *FunctionTypes::data() noexcept
	{
		return m_data.data();
	}

	const uint8_t *FunctionTypes::data() const noexcept
	{
		return m_data.data();
	}

	uint8_t &FunctionTypes::lastByte() noexcept
	{
		return *(data() + byteSize() - 1);
	}



	FunctionTypesIterator::FunctionTypesIterator(
			const uint8_t *data,
			FunctionTypesDetail::Position position
	) noexcept :
			m_data{data},
			m_position(position) {}

	void FunctionTypesIterator::advance() noexcept
	{
		// Toggle position bit
		m_position ^= FunctionTypesDetail::PositionMask;

		if(!m_position)
			// If HighPosition, advance data pointer
			++m_data;
	}

	// ++iter
	FunctionType::Enum FunctionTypesIterator::operator++() noexcept
	{
		// Toggle position bit
		m_position ^= FunctionTypesDetail::PositionMask;

		uint8_t result;

		if(m_position)
			// If LowPosition, get current packed byte
			result = *m_data;
		else
			// If HighPosition, advance and get high part of next packed byte
			result = (*++m_data) >> FunctionTypesDetail::EnumOffset;

		// Remove upper part of result
		return static_cast<FunctionType::Enum>(result & FunctionTypesDetail::EnumMask);
	}

	// iter++
	FunctionType::Enum FunctionTypesIterator::operator++(int) noexcept
	{
		// Get current packed byte
		uint8_t result = *m_data;

		if(m_position)
			// If LowPosition, advance data pointer
			m_data++;
		else
			// If HighPosition, get high part of packed byte
			result >>= FunctionTypesDetail::EnumOffset;

		// Toggle position bit
		m_position ^= FunctionTypesDetail::PositionMask;

		// Remove upper part of result
		return static_cast<FunctionType::Enum>(result & FunctionTypesDetail::EnumMask);
	}

	// --iter
	FunctionType::Enum FunctionTypesIterator::operator--() noexcept
	{
		// Toggle position bit
		m_position ^= FunctionTypesDetail::PositionMask;

		uint8_t result;

		if(m_position)
			// If LowPosition, get previous packed byte
			result = *--m_data;
		else
			// If HighPosition, get high part of current packed byte
			result = *m_data >> FunctionTypesDetail::EnumOffset;

		// Remove upper part of result
		return static_cast<FunctionType::Enum>(result & FunctionTypesDetail::EnumMask);
	}

	// iter--
	FunctionType::Enum FunctionTypesIterator::operator--(int) noexcept
	{
		// Get current packed byte
		uint8_t result = *m_data;

		if(!m_position) {
			// If HighPosition, unadvance data pointer and get high part of current packed byte
			--m_data;
			result >>= FunctionTypesDetail::EnumOffset;
		}

		// Toggle position bit
		m_position ^= FunctionTypesDetail::PositionMask;

		// Remove upper part of result
		return static_cast<FunctionType::Enum>(result & FunctionTypesDetail::EnumMask);
	}

	FunctionType::Enum FunctionTypesIterator::get() const noexcept
	{
		// Get current packed byte
		uint8_t result = *m_data;

		if(!m_position)
			// If HighPosition, get high part of result
			result >>= FunctionTypesDetail::EnumOffset;

		// Remove upper part of result
		return static_cast<FunctionType::Enum>(result & FunctionTypesDetail::EnumMask);
	}

	FunctionType::Enum FunctionTypesIterator::operator*() const noexcept
	{
		return get();
	}

	FunctionTypesIterator::operator FunctionType::Enum() const noexcept
	{
		return get();
	}
}

