#pragma once

#include "BaseFilter.h"

/*!*****************************************************************************
 * \class Filter2D
 * \brief Defines the base structure for all 2Dfilters
 ******************************************************************************/
class Filter2D : BaseFilter
{
public:
    /*!*****************************************************************************
    * Call the base constructor
    ******************************************************************************/
	explicit Filter2D(FilterFunctionPointer aFunctionPointer);

    /*!*****************************************************************************
    * Called to run the filter over 2 dimensional data
    ******************************************************************************/
	void operator()(Data const& aInput, Data& aOutput) override;
	virtual ~Filter2D() = default;
};

inline Filter2D::Filter2D(FilterFunctionPointer aFunctionPointer)
	: BaseFilter(aFunctionPointer)
{
}

inline void Filter2D::operator()(Data const& aInput, Data& aOutput)
{
	//TODO - dimension validation
	memset(aOutput.data, 0, aInput.total_elements * sizeof(float));
	
	size_t const num_dimensions = 2;

	size_t const width = aInput.dimensions[1];
	size_t const height = aInput.dimensions[0];

	size_t const stride_within_row = aInput.element_stride;
	size_t const stride_between_rows = width * stride_within_row;
	for (size_t pass = 0; pass < height; ++pass)
	{
		size_t const pass_start = pass * stride_between_rows;

		filter_function(aInput.data + pass_start, aOutput.data + pass_start,
			width, stride_within_row);
	}

	size_t const stride_within_column = aInput.element_stride * width;
	size_t const stride_between_columns = 1;
	for (size_t pass = 0; pass < width; ++pass)
	{
		size_t const pass_start = pass * stride_between_columns;

		filter_function(aInput.data + pass_start, aOutput.data + pass_start,
			height, stride_within_column);
	}

	for (size_t i = 0; i < aInput.total_elements; ++i)
	{
		aOutput.data[i] /= 2;
	}
}
