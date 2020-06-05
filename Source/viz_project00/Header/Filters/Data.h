// Author: Matthew Gilbert
#pragma once

#include <vector>

struct Data
{
	size_t total_elements = 0; /*!< total number of elements in data */
	size_t element_stride; /*!< how much to offset to reach next underlying type */
	float* data = nullptr; /*!< pointer to the buffer */
	std::vector<size_t> dimensions; /*!< number of elements in each dimension */
	//std::vector<size_t> offsets; /*!< start of data for each channel */
	//std::vector<size_t> strides; /*!< how far to step to reach the start of the next section in each dimension */
};