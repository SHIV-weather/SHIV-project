#pragma once

#include "Data.h"

/**
 * \brief Callback filter function type "FilterFunctionPointer"
 *
 * This defines the structure needed for a filter function
 * 
 * \param aInput 
 *        Data that the filter will be applied to
 * \param aOutput 
 *        Result of filtering aInput
 * \param aDataSize 
 *        Size of the data to filter (one dimensional)
 * \param aStride 
 *        Distance between single elements
 */
typedef void(*FilterFunctionPointer)(float const* const, float* const, size_t, size_t);

/*!*****************************************************************************
 * \class BaseFilter
 * \brief Defines the base structure for all filters
 ******************************************************************************/
class BaseFilter
{
public:
    /*!*****************************************************************************
    * The only constructor. Binds a function pointer to the given function
    ******************************************************************************/
	explicit BaseFilter(FilterFunctionPointer aFilterFunction);

    /*!*****************************************************************************
    * Called to run the filter
    ******************************************************************************/
	virtual void operator()(Data const& aInput, Data& aOutput) = 0;
	virtual ~BaseFilter() = default;

protected:
	FilterFunctionPointer filter_function = nullptr; //pointer to the underlying 1D filter function

};

inline BaseFilter::BaseFilter(FilterFunctionPointer aFilterFunction)
{
	filter_function = aFilterFunction;
}
