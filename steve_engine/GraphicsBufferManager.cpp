#include "GraphicsBufferManager.h"
#include "GraphicsBuffer.h"

using namespace std;

GraphicsBufferManager::GraphicsBufferManager()
{

}
GraphicsBufferManager::~GraphicsBufferManager()
{
	cleanup();
}

void GraphicsBufferManager::init()
{
	// load graphics buffers
	const string ASSET_PATH = "..\\..\\common\\assets\\";
	createAndManageGraphicsBuffer("background", ASSET_PATH, "Woods.png");
	createAndManageGraphicsBuffer("smurph", ASSET_PATH, "smurf_sprites.png");
	createAndManageGraphicsBuffer("dean_smurph", ASSET_PATH, "dean_sprites.png");
}
void GraphicsBufferManager::cleanup()
{
	//go through all entries in map and delete
	for (auto iter : mMap)
	{
		GraphicsBuffer* pBuffer = iter.second;
		delete pBuffer;
	}

	mMap.clear();
}

GraphicsBuffer* GraphicsBufferManager::createAndManageGraphicsBuffer(const BufferKey& key, const std::string& path, const std::string& filename)
{
	GraphicsBuffer* pBuffer = NULL;

	//figure out if it exists already
	auto iter = mMap.find(key);

	//already in map?
	if (iter == mMap.end())
	{
		//not already there - just create and add it
		pBuffer = new GraphicsBuffer(path, filename);
		mMap[key] = pBuffer;
	}

	return pBuffer;
}

void GraphicsBufferManager::deleteGraphicsBuffer(const BufferKey& key)
{
	//figure out if it exists already
	auto iter = mMap.find(key);

	if (iter != mMap.end())//found
	{
		delete iter->second;
		mMap.erase(iter);
	}

}

void GraphicsBufferManager::deleteGraphicsBuffer(GraphicsBuffer* pBuffer)
{
	//go through all entries in map searching for pBuffer
	for (auto iter : mMap)
	{
		if (pBuffer == iter.second)
		{
			delete pBuffer;
			mMap.erase(iter.first);
			return;
		}
	}

}

GraphicsBuffer* GraphicsBufferManager::getGraphicsBuffer(const BufferKey& key) const
{
	auto iter = mMap.find(key);

	if (iter != mMap.end())
	{
		return iter->second;
	}
	else
	{
		// should never be here, throw an exception if the user inputs an incorrect key
		// or if the map is empty
		assert(iter != mMap.end());
		return NULL;
	}
}
