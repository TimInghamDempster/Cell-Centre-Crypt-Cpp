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

	bool CreateInstancingMatrixBuffer(ID3D11Device* device, ID3D11Buffer** dataBuffer, UINT32 count)
	{
		bool succeeded = true;
		float* data = new float[16 * count];

		D3D11_BUFFER_DESC bufferDesc;
		D3D11_SUBRESOURCE_DATA dataSubresource;
		HRESULT hr;

		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = sizeof(float) * 16 * count;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
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

	struct Vertex
	{
		float coord[4];
		float normal[4];
	};

	struct MeshData
	{
		Vertex* vertices;
		UINT32* indices;

		int vertexCount;
		int indexCount;
	};	

	MeshData LoadMeshDataFromFile(std::string filename)
	{
		std::ifstream file;
		
		file.open(filename);
		
		std::string line;
		int vertsCount = 0;
		int facesCount = 0;
		int normalCount = 0;

		while(getline(file, line))
		{
			std::stringstream lineStream(line);
			std::string word;

			getline(lineStream, word, ' ');

			if(word == "v")
			{
				vertsCount++;
			}
			else if(word == "vn")
			{
				normalCount++;
			}
			else if(word == "f")
			{
				facesCount++;
			}
		}

		struct norm
		{
			float normal[3];
		};

		MeshData mesh;

		mesh.vertices = new Vertex[vertsCount];
		mesh.indices = new UINT32[facesCount * 3];
		mesh.vertexCount = vertsCount;
		mesh.indexCount = facesCount * 3;

		norm* normals = new norm[normalCount];

		file.clear();
		file.seekg(0, std::ios_base::beg);

		int vertIndex = 0;
		int normalIndex = 0;
		int faceIndex = 0;

		while(getline(file, line))
		{
			std::stringstream lineStream(line);
			std::string word;
			
			getline(lineStream, word, ' ');
			
			if(word == "v")
			{
				Vertex& vert = mesh.vertices[vertIndex];
				vertIndex++;
				
				getline(lineStream, word, ' ');
				vert.coord[0]  = stof(word);
				
				getline(lineStream, word, ' ');
				vert.coord[1]  = stof(word);
				
				getline(lineStream, word, ' ');
				vert.coord[2]  = stof(word);

				vert.coord[3] = 1.0f;
			}
			else if(word == "vn")
			{
				norm& normal = normals[normalIndex];
				normalIndex++;
								
				getline(lineStream, word, ' ');
				normal.normal[0]  = stof(word);
				
				getline(lineStream, word, ' ');
				normal.normal[1]  = stof(word);
				
				getline(lineStream, word, ' ');
				normal.normal[2]  = stof(word);
			}
			else if(word == "f")
			{
				getline(lineStream, word, ' ');

				std::stringstream subStream(word);
				std::string subword;
				
				getline(subStream, subword, '/');
				int vIndex = stoi(subword) - 1;
				mesh.indices[faceIndex * 3] = vIndex;
				char temp;
				subStream >> temp;
				int normIndex;
				subStream >> normIndex;
				normIndex--;
				mesh.vertices[vIndex].normal[0] = normals[normIndex].normal[0];
				mesh.vertices[vIndex].normal[1] = normals[normIndex].normal[1];
				mesh.vertices[vIndex].normal[2] = normals[normIndex].normal[2];
				mesh.vertices[vIndex].normal[3] = 1.0f;

				getline(lineStream, word, ' ');
				subStream = std::stringstream(word);
				getline(subStream, subword, '/');
				vIndex = stoi(subword) - 1;
				mesh.indices[faceIndex * 3 + 1] = vIndex;
				subStream >> temp;
				subStream >> normIndex;
				normIndex--;
				mesh.vertices[vIndex].normal[0] = normals[normIndex].normal[0];
				mesh.vertices[vIndex].normal[1] = normals[normIndex].normal[1];
				mesh.vertices[vIndex].normal[2] = normals[normIndex].normal[2];
				mesh.vertices[vIndex].normal[3] = 1.0f;

				getline(lineStream, word, ' ');
				subStream = std::stringstream(word);
				getline(subStream, subword, '/');
				vIndex = stoi(subword) - 1;
				mesh.indices[faceIndex * 3 + 2] = vIndex;
				subStream >> temp;
				subStream >> normIndex;
				normIndex--;
				mesh.vertices[vIndex].normal[0] = normals[normIndex].normal[0];
				mesh.vertices[vIndex].normal[1] = normals[normIndex].normal[1];
				mesh.vertices[vIndex].normal[2] = normals[normIndex].normal[2];
				mesh.vertices[vIndex].normal[3] = 1.0f;

				faceIndex++;
			}
		}

		delete[] normals;

		return mesh;
	}

	bool LoadMeshBuffersFromFile(ID3D11Device* device, ID3D11Buffer** vertexBuffer, ID3D11Buffer** indexBuffer, std::string filename, int& numVerts)
	{
		

		D3D11_BUFFER_DESC vertexBufferDesc;
		D3D11_BUFFER_DESC indexBufferDesc;
		D3D11_SUBRESOURCE_DATA vertexData;
		D3D11_SUBRESOURCE_DATA indexData;

		MeshData mesh = LoadMeshDataFromFile(filename);

		numVerts = mesh.indexCount;

		vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		vertexBufferDesc.ByteWidth = sizeof(Vertex) * mesh.vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		vertexData.pSysMem = mesh.vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		HRESULT hr = device->CreateBuffer(&vertexBufferDesc, &vertexData, vertexBuffer);
		if(FAILED(hr))
		{
			return false;
		}

		indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		indexBufferDesc.ByteWidth = sizeof(int) * mesh.indexCount;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		indexData.pSysMem = mesh.indices;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		hr = device->CreateBuffer(&indexBufferDesc, &indexData, indexBuffer);
		if(FAILED(hr))
		{
			return false;
		}

		delete[] mesh.indices;
		delete[] mesh.vertices;

		return true;
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