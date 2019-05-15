#include "ground.h"
#include <vector>
//######################################################################################################################
//
//	file load.cpp
//
//	purpose: loads 3DS and OBJ models into a vertexbuffer and also returns the vertex count
//
//		3DS and OBJ files are most common 3D files
//
//######################################################################################################################

//needed to load the model:
class submodel
	{
	public:
		USHORT *indizes;
		int ianz;
		SimpleVertex *vertices;
		int vanz;
		submodel()
			{
			indizes = NULL;
			ianz = 0;
			vertices = NULL;
			vanz = 0;
			}
		~submodel()
			{
			int z;
			z = 0;
			//if (indizes)	delete[]indizes;
			//if (vertices)	delete[]vertices;
			}
	};
bool similar_pos(XMFLOAT3 a, XMFLOAT3 b, float crit)
	{
	XMFLOAT3 c = a - b;
	if (abs(c.x) < crit && abs(c.y) < crit && abs(c.z) < crit)
		return TRUE;

	return FALSE;
	}
//***************************************************************************************************************************************************************
//
//	Load3DS
//
//	Loads a 3DS model into a vertexbuffer
//
//	usage e.g.:
//			Load3DS("rocket.3ds",g_pd3dDevice,&vertexbuffer,&vertices_count);
//
//	parameters:
//					filename	..		character array of the file name which should be in the main folder
//					g_pd3dDevice ..		the first part of the device context
//					ppVertexBuffer .. address of a vertexbuffer pointer from type  ID3D11Buffer *vertexbuffer -> &vertexbuffer
//					vertex_count .. address of an integer, to retrieve the vertex count which is needed later in the draw() call: ->draw(vertex_count,0);
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Load3DS(char *filename, ID3D11Device* g_pd3dDevice, ID3D11Buffer **ppVertexBuffer, int *vertex_count, bool gouraurd)
	{
	ID3D11Buffer *pVertexBuffer = NULL;
	bool firstinit = TRUE;
	int i; //Index variable
	FILE *l_file = fopen(filename, "rb"); //File pointer
	if (l_file == NULL) return FALSE; //Open the file

	vector<submodel> submodels;

	unsigned short l_chunk_id; //Chunk identifier
	unsigned int l_chunk_lenght; //Chunk lenght

	unsigned char l_char; //Char variable
	unsigned short l_qty; //Number of elements in each chunk


	char ready = 0;
	unsigned short l_face_flags; //Flag that stores some face information
	char str[1000];
	while (ftell(l_file) < filelength(fileno(l_file))) //Loop to scan the whole file 
		{
		//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread(&l_chunk_id, 2, 1, l_file); //Read the chunk header
		printf("ChunkID: %x\n", l_chunk_id);
		fread(&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
		printf("ChunkLenght: %x\n", l_chunk_lenght);

		switch (l_chunk_id)
			{
				case 0x0002://version
					{
					int ver;
					fread(&ver, sizeof(int), 1, l_file); //Read the lenght of the chunk
					int z;
					z = 0;
					}
					break;
				case 0x3d3e://meshversion
					{
					int ver;
					fread(&ver, sizeof(int), 1, l_file); //Read the lenght of the chunk
					int z;
					z = 0;
					}
					break;
				case 0x0100://?????????????
					{
					int ver;
					fread(&ver, sizeof(int), 1, l_file); //Read the lenght of the chunk
					int z;
					z = 0;
					}
					break;
					//----------------- 1group -----------------
					// Description: bitmap
					// Chunk ID: a300
					// Chunk Lenght: 0 + sub chunks
					//-------------------------------------------
				case 0xa300:
					{
					fscanf(l_file, "%s", str);
					}
					break;
					//----------------- MAIN3DS -----------------
					// Description: Main chunk, contains all the other chunks
					// Chunk ID: 4d4d 
					// Chunk Lenght: 0 + sub chunks
					//-------------------------------------------
				case 0x4d4d:
					{
					int z = 0;
					}
					break;

					//----------------- EDIT3DS -----------------
					// Description: 3D Editor chunk, objects layout info 
					// Chunk ID: 3d3d (hex)
					// Chunk Lenght: 0 + sub chunks
					//-------------------------------------------
				case 0x3d3d:
					break;

					//--------------- EDIT_OBJECT ---------------
					// Description: Object block, info for each object
					// Chunk ID: 4000 (hex)
					// Chunk Lenght: len(object name) + sub chunks
					//-------------------------------------------
				case 0x4000:

					{
					submodel subm;
					submodels.push_back(subm);

					}
					ready++;
					i = 0;
					do
						{
						fread(&l_char, 1, 1, l_file);
						//p_object->name[i] = l_char;
						i++;
						} while (l_char != '\0' && i < 20);

						//name.settext(p_object->name);
						firstinit = FALSE;
						break;
						break;

						//--------------- OBJ_TRIMESH ---------------
						// Description: Triangular mesh, contains chunks for 3d mesh info
						// Chunk ID: 4100 (hex)
						// Chunk Lenght: 0 + sub chunks
						//-------------------------------------------
				case 0x4100:
					{
					int i = 0;
					i = 9;
					}
					break;

					//--------------- TRI_VERTEXL ---------------
					// Description: Vertices list
					// Chunk ID: 4110 (hex)
					// Chunk Lenght: 1 x unsigned short (number of vertices) 
					//             + 3 x float (vertex coordinates) x (number of vertices)
					//             + sub chunks
					//-------------------------------------------
				case 0x4110:
					{

					int elem_no = submodels.size() - 1;


					fread(&l_qty, sizeof(unsigned short), 1, l_file);
					submodels[elem_no].vanz = l_qty;
					submodels[elem_no].vertices = new SimpleVertex[submodels[elem_no].vanz];
					for (int ii = 0; ii < submodels[elem_no].vanz; ii++)
						{
						fread(&submodels[elem_no].vertices[ii].Pos.x, sizeof(float), 1, l_file);
						fread(&submodels[elem_no].vertices[ii].Pos.y, sizeof(float), 1, l_file);
						fread(&submodels[elem_no].vertices[ii].Pos.z, sizeof(float), 1, l_file);
						}
					}
					break;
				case 0x4160://local koordinate system
					{
					char ver[100];
					fread(&ver, sizeof(BYTE) * 48, 1, l_file); //Read the lenght of the chunk
					int z;
					z = 0;
					}
					break;
					//--------------- TRI_FACEL1 ----------------
					// Description: Polygons (faces) list
					// Chunk ID: 4120 (hex)
					// Chunk Lenght: 1 x unsigned short (number of polygons) 
					//             + 3 x unsigned short (polygon points) x (number of polygons)
					//             + sub chunks
					//-------------------------------------------
				case 0x4120:
					{
					int elem_no = submodels.size() - 1;




					fread(&l_qty, sizeof(unsigned short), 1, l_file);
					submodels[elem_no].ianz = l_qty * 3;
					submodels[elem_no].indizes = new USHORT[submodels[elem_no].ianz];
					for (int ii = 0; ii < l_qty; ii++)
						{
						fread(&submodels[elem_no].indizes[ii * 3], sizeof(USHORT), 1, l_file);
						fread(&submodels[elem_no].indizes[ii * 3 + 1], sizeof(USHORT), 1, l_file);
						fread(&submodels[elem_no].indizes[ii * 3 + 2], sizeof(USHORT), 1, l_file);
						fread(&l_face_flags, sizeof(USHORT), 1, l_file);
						}
					}
					break;

					//------------- TRI_MAPPINGCOORS ------------
					// Description: Vertices list
					// Chunk ID: 4140 (hex)
					// Chunk Lenght: 1 x unsigned short (number of mapping points) 
					//             + 2 x float (mapping coordinates) x (number of mapping points)
					//             + sub chunks
					//-------------------------------------------
				case 0x4140:
					{
					int elem_no = submodels.size() - 1;

					fread(&l_qty, sizeof(unsigned short), 1, l_file);
					for (int ii = 0; ii < submodels[elem_no].vanz; ii++)
						{
						fread(&submodels[elem_no].vertices[ii].Tex.x, sizeof(float), 1, l_file);
						fread(&submodels[elem_no].vertices[ii].Tex.y, sizeof(float), 1, l_file);
						}
					}
					break;

					//----------- Skip unknow chunks ------------
					//We need to skip all the chunks that currently we don't use
					//We use the chunk lenght information to set the file pointer
					//to the same level next chunk
					//-------------------------------------------
				default:
					fseek(l_file, l_chunk_lenght - 6, SEEK_CUR);
			}


		}

	int vertex_anz = 0;
	for (int ii = 0; ii < submodels.size(); ii++)
		vertex_anz += submodels[ii].ianz;

	SimpleVertex *noIndexVer = new SimpleVertex[vertex_anz];

	int vv = 0;
	for (int uu = 0; uu < submodels.size(); uu++)
		for (int ii = 0; ii< submodels[uu].ianz; ii++)//weil 1.dreieck nix data.... anz--;oder eben ii=1 und net 0
			noIndexVer[vv++] = submodels[uu].vertices[submodels[uu].indizes[ii]];
	*vertex_count = vertex_anz;

	//perform flat light:
	for (int ii = 0; ii < vertex_anz; ii += 3)
		{
		XMFLOAT3 a, b, c;
		a = noIndexVer[ii + 1].Pos - noIndexVer[ii + 0].Pos;
		b = noIndexVer[ii + 2].Pos - noIndexVer[ii + 0].Pos;
		c = cross(a, b);
		c = normalize(c);

		noIndexVer[ii + 0].Norm = c;
		noIndexVer[ii + 1].Norm = c;
		noIndexVer[ii + 2].Norm = c;
		}

	if (gouraurd)
		{
		//first, lets have a list with flags what we already have visited:
		int *flags = new int[vertex_anz];
		for (int ii = 0; ii < vertex_anz; ii++)
			flags[ii] = 0;//not vistied

						  //lets store all similar normal vector addresses here:
		for (int ii = 0; ii < vertex_anz; ii++)
			{
			if (flags[ii] == 1)continue;
			vector<XMFLOAT3*> normals;
			//check all the others, if not already checked:
			for (int uu = ii + 1; uu < vertex_anz; uu++)
				{
				if (flags[uu] == 1)continue;
				if (similar_pos(noIndexVer[ii].Pos, noIndexVer[uu].Pos, 0.01))
					normals.push_back(&noIndexVer[uu].Norm);
				}
			//and now, lets do the average of all of them:
			XMFLOAT3 average_norm = noIndexVer[ii].Norm;
			for (int uu = 0; uu < normals.size(); uu++)
				average_norm = average_norm + *(normals[uu]);
			average_norm = normalize(average_norm);
			//re aply:
			noIndexVer[ii].Norm = average_norm;
			for (int uu = 0; uu < normals.size(); uu++)
				*normals[uu] = average_norm;
			}
		}
	//initialize d3dx verexbuff:
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * vertex_anz;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = noIndexVer;
	HRESULT hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &pVertexBuffer);
	if (FAILED(hr))
		return FALSE;
	*ppVertexBuffer = pVertexBuffer;
	return TRUE;
	}
//***************************************************************************************************************************************************************
//
//	LoadOBJ
//
//	Loads a 3DS model into a vertexbuffer
//
//	usage e.g.:
//			LoadOBJ("rocket.3ds",g_pd3dDevice,&vertexbuffer,&vertices_count);
//
//	parameters:
//					filename	..		character array of the file name which should be in the main folder
//					g_pd3dDevice ..		the first part of the device context
//					ppVertexBuffer .. address of a vertexbuffer pointer from type  ID3D11Buffer *vertexbuffer -> &vertexbuffer
//					vertex_count .. address of an integer, to retrieve the vertex count which is needed later in the draw() call: ->draw(vertex_count,0);
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
bool LoadOBJ(char * filename, ID3D11Device * g_pd3dDevice, ID3D11Buffer ** ppVertexBuffer, int * vertex_count)
	{
	ID3D11Buffer *pVertexBuffer = NULL;
	ifstream file(filename);
	if (file.fail())
		{
		return false;
		}
	struct Vertex
		{
		float x, y, z;
		}v;
	struct Face
		{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
		}f;

	std::vector<Vertex> vertices, texcoords, normals;
	std::vector<Face> faces;
	char l_char;

	file.get(l_char);
	while (!file.eof()) //Loop to scan the whole file 
		{
		switch (l_char)
			{
				case 'v':
					{
					file.get(l_char);
					switch (l_char)
						{
							case ' ':
								{
								file >> v.x >> v.y >> v.z;
								v.z = v.z * -1.0f;
								vertices.push_back(v);
								break;
								}
							case 't':
								{
								file >> v.x >> v.y;
								v.y = 1.0f - v.y;
								texcoords.push_back(v);
								break;
								}
							case 'n':
								{
								file >> v.x >> v.y >> v.z;
								v.z = v.z * -1.0f;
								normals.push_back(v);
								break;
								}
						}
					break;
					}
				case 'f':
					{
					file.get(l_char);
					if (l_char == ' ')
						{
						file >> f.vIndex3 >> l_char >> f.tIndex3 >> l_char >> f.nIndex3
							>> f.vIndex2 >> l_char >> f.tIndex2 >> l_char >> f.nIndex2
							>> f.vIndex1 >> l_char >> f.tIndex1 >> l_char >> f.nIndex1;
						faces.push_back(f);
						}
					break;
					}
				default:
					{
					while (l_char != '\n')
						{
						file.get(l_char);
						}
					file.get(l_char);
					}
			}
		}
	file.close();
	int faceSize = faces.size();
	*vertex_count = 3 * faceSize;

	int vIndex, tIndex, nIndex;
	SimpleVertex* Vertices;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	HRESULT result;
	int i;
	// Create the vertex array.
	Vertices = new SimpleVertex[*vertex_count];
	if (!Vertices)
		{
		return false;
		}
	for (int i = 0; i < faceSize; i++)
		{
		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;

		Vertices[3 * i].Pos.x = vertices[vIndex].x;
		Vertices[3 * i].Pos.y = vertices[vIndex].y;
		Vertices[3 * i].Pos.z = vertices[vIndex].z;
		Vertices[3 * i].Tex.x = texcoords[tIndex].x;
		Vertices[3 * i].Tex.y = texcoords[tIndex].y;
		/*Vertices[3 * i].Norm.x = normals[nIndex].x;
		Vertices[3 * i].Norm.y = normals[nIndex].y;
		Vertices[3 * i].Norm.z = normals[nIndex].z;*/

		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].tIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;

		Vertices[3 * i + 1].Pos.x = vertices[vIndex].x;
		Vertices[3 * i + 1].Pos.y = vertices[vIndex].y;
		Vertices[3 * i + 1].Pos.z = vertices[vIndex].z;
		Vertices[3 * i + 1].Tex.x = texcoords[tIndex].x;
		Vertices[3 * i + 1].Tex.y = texcoords[tIndex].y;
		/*Vertices[3 * i + 1].Norm.x = normals[nIndex].x;
		Vertices[3 * i + 1].Norm.y = normals[nIndex].y;
		Vertices[3 * i + 1].Norm.z = normals[nIndex].z;*/

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;

		Vertices[3 * i + 2].Pos.x = vertices[vIndex].x;
		Vertices[3 * i + 2].Pos.y = vertices[vIndex].y;
		Vertices[3 * i + 2].Pos.z = vertices[vIndex].z;
		Vertices[3 * i + 2].Tex.x = texcoords[tIndex].x;
		Vertices[3 * i + 2].Tex.y = texcoords[tIndex].y;
		//Vertices[3 * i + 2].Norm.x = normals[nIndex].x;
		//Vertices[3 * i + 2].Norm.y = normals[nIndex].y;
		//Vertices[3 * i + 2].Norm.z = normals[nIndex].z;
		}
	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(SimpleVertex) * (*vertex_count);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = Vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = g_pd3dDevice->CreateBuffer(&vertexBufferDesc, &vertexData, ppVertexBuffer);
	if (FAILED(result))
		{
		return false;
		}
	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] Vertices;
	Vertices = 0;
	return true;
	}

//***************************************************************
//
//	handy functions for matrix/vector operations
//
//***************************************************************
	float length(const XMFLOAT3 &v)
		{
		return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
		}
	float dot(XMFLOAT3 a, XMFLOAT3 b)
		{
		return a.x*b.x + a.y*b.y + a.z*b.z;
		}

	XMFLOAT3 cross(XMFLOAT3 a, XMFLOAT3 b)
		{
		XMFLOAT3 c = XMFLOAT3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
		return c;
		}
	
	XMFLOAT3 normalize(const  XMFLOAT3 &a)
		{
		XMFLOAT3 c = a;
		float len = length(a);
		c.x /= len;
		c.y /= len;
		c.z /= len;
		return c;
		}

	XMFLOAT3 operator+(const XMFLOAT3 lhs, const XMFLOAT3 rhs)
		{
		XMFLOAT3 c = XMFLOAT3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
		return c;
		}
	XMFLOAT2 operator+(const XMFLOAT2 lhs, const XMFLOAT2 rhs)
		{
		XMFLOAT2 c = XMFLOAT2(lhs.x + rhs.x, lhs.y + rhs.y);
		return c;
		}
	XMFLOAT3 operator-(const XMFLOAT3 lhs, const XMFLOAT3 rhs)
		{
		XMFLOAT3 c = XMFLOAT3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
		return c;
		}
	XMFLOAT3 mul(const XMMATRIX &M, const XMFLOAT3 &rhs)
		{
		XMFLOAT3 c = rhs;
		XMVECTOR f = XMLoadFloat3(&c);
		f = XMVector3TransformCoord(f, M);
		XMStoreFloat3(&c, f);
		return c;
		}
	XMMATRIX mul(const XMMATRIX &lhs, const XMMATRIX &rhs)
		{
		XMMATRIX M = XMMatrixMultiply(lhs, rhs);
		return M;
		}