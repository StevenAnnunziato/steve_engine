#pragma once

#include <string>
#include <unordered_map>
#include <Trackable.h>


class GraphicsBuffer;

typedef std::string BufferKey;

class GraphicsBufferManager : public Trackable
{
public:
	GraphicsBufferManager();
	~GraphicsBufferManager();

	void init();
	void cleanup();

	GraphicsBuffer* createAndManageGraphicsBuffer(const BufferKey& key, const std::string& path, const std::string& filename);
	void deleteGraphicsBuffer(const BufferKey& key);
	void deleteGraphicsBuffer(GraphicsBuffer* pBuffer);

	GraphicsBuffer* getGraphicsBuffer(const BufferKey& key) const;

private:
	std::unordered_map<BufferKey, GraphicsBuffer*> mMap;

};
