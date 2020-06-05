#pragma once

/**
 * \brief Runs a 1 dimensional gaussian blur upon provided data
 *        For use in a Filter class
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
void GaussianBlur(float const* const aInput, float* const aOutput, size_t aSize, size_t aStride)
{
	size_t const kernel_size = 3;
	float const kernel[] = { 0.27901, 0.44198, 0.27901 };
	
	for(size_t x = 0; x < aSize; ++x)
	{
		for(int k = 0; k < kernel_size; ++k)
		{
			int const texel = x * aStride;
			int const kernel_texel = ((k - kernel_size / 2) + x) * aStride;
			if (kernel_texel < 0 || kernel_texel >= aSize * aStride) continue;
			aOutput[texel] += aInput[kernel_texel] * kernel[k];
		}
	}
}
