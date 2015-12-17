namespace Renderer
{
	bool CreateConstantBuffer(ID3D11Device* device, ID3D11Buffer** constantBuffer, UINT32 bufferSizeInBytes)
	{
		HRESULT hr;
		D3D11_BUFFER_DESC constantBufferDesc;

		// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
		constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		constantBufferDesc.ByteWidth = bufferSizeInBytes;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantBufferDesc.MiscFlags = 0;
		constantBufferDesc.StructureByteStride = 0;
	
		// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
		hr = device->CreateBuffer(&constantBufferDesc, NULL, constantBuffer);
		if(FAILED(hr))
		{
			return false;
		}

	return true;
	}

	bool CreateAscendingBuffer(ID3D11Device* device, ID3D11Buffer** dataBuffer, UINT32 count)
	{
		bool succeeded = true;
		UINT32* data = new UINT32[count];

		for(UINT32 i = 0; i < count; i++)
		{
			data[i] = i;
		}

		D3D11_BUFFER_DESC bufferDesc;
		D3D11_SUBRESOURCE_DATA dataSubresource;
		HRESULT hr;

		bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		bufferDesc.ByteWidth = sizeof(float) * count;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		dataSubresource.pSysMem = data;
		dataSubresource.SysMemPitch = 0;
		dataSubresource.SysMemSlicePitch = 0;

		hr = device->CreateBuffer(&bufferDesc, &dataSubresource, dataBuffer);
		if(FAILED(hr))
		{
			succeeded = false;
		}
		delete[] data;
		return succeeded;
	}

	bool CreateQuadMeshBuffers(ID3D11Device* device, ID3D11Buffer** vertexBuffer, ID3D11Buffer** indexBuffer)
	{
		struct vertex
		{
			float coord[4];
		};

		D3D11_BUFFER_DESC vertexBufferDesc;
		D3D11_BUFFER_DESC indexBufferDesc;
		D3D11_SUBRESOURCE_DATA vertexData;
		D3D11_SUBRESOURCE_DATA indexData;

		HRESULT hr;
		
		vertex vertices[] = 
		{
			{ 0.0f, 0.0f, 0.5f, 1.0f },
			{ 1.0f, 0.0f, 0.5f, 1.0f },
			{ 0.0f, 1.0f, 0.5f, 1.0f },
			{ 1.0f, 1.0f, 0.5f, 1.0f }
		};

		UINT32 indices[] = { 0, 1, 2, 1, 3, 2 };

	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDesc.ByteWidth = sizeof(vertex) * 4;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vertexBufferDesc, &vertexData, vertexBuffer);
	if(FAILED(hr))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * 6;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&indexBufferDesc, &indexData, indexBuffer);
	if(FAILED(hr))
	{
		return false;
	}

	return true;
	}
}