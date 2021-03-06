/*
 * Copyright (c) 2014, Shogun Toolbox Foundation
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:

 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its 
 * contributors may be used to endorse or promote products derived from this 
 * software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * Written (W) 2014 Khaled Nasr
 */

#include <shogun/neuralnets/NeuralRectifiedLinearLayer.h>
#include <shogun/mathematics/Math.h>

using namespace shogun;

CNeuralRectifiedLinearLayer::CNeuralRectifiedLinearLayer() : CNeuralLinearLayer()
{
}

CNeuralRectifiedLinearLayer::CNeuralRectifiedLinearLayer(int32_t num_neurons): 
CNeuralLinearLayer(num_neurons)
{
}

void CNeuralRectifiedLinearLayer::compute_activations(float64_t* parameters,
		float64_t* previous_layer_activations)
{
	CNeuralLinearLayer::compute_activations(parameters, 
		previous_layer_activations);
	
	int32_t len = m_num_neurons*m_batch_size;
	for (int32_t i=0; i<len; i++)
	{
		if (m_activations[i] < 0)
			m_activations[i] = 0;
	}
}

void CNeuralRectifiedLinearLayer::compute_local_gradients(bool is_output, 
		float64_t* p)
{
	if (is_output) SG_ERROR("Cannot be used as an output layer");
	
	int32_t len = m_num_neurons*m_batch_size;
	for (int32_t i=0; i< len; i++)
	{
		if (m_activations[i]==0)
			m_local_gradients[i] = 0;
		else
			m_local_gradients[i] = p[i];
	}
}
